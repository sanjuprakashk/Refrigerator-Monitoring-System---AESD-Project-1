/*****************************************************************
						Includes
*****************************************************************/

#include "logger.h"


timer_t timer_id_log;
int FLAG_LOG;

/*****************************************************************
                             Globals
*****************************************************************/
const char *log_level[10] = {"DEBUG", "INFO", "WARN", "ERROR"};


 /* Logger level enum */
typedef enum log_level_enum{
    Nolog = -1,
    Debug = 0,
    Info,
    Warn,
    Error
}log_level_enum;

const int user_select_log_level = Error; // Threshold log level

int fd3_w; // FIFO descriptor

pthread_mutex_t lock; // Lock for message queue

char time_stam[30];



/***********************************************
  Signal handler for killing logger thread
***********************************************/
void hanler_kill_log(int num)
{
    printf("Encountered SIGALRM signal\n");
    static int FLAG = 1;

    if((logger_thread_creation == 1) && (FLAG == 1))
    {
        printf("\nExiting log thread\n");
        mq_close(msg_queue);
        mq_unlink(QUEUE_NAME);
        close(fd3_w);
        fclose(file_ptr);
        stop_timer(timer_id_log);
        pthread_cancel(logger_thread); 
        FLAG = 0;
    }
    else
    {
        printf("Logger thread already dead\n");
    }

}

/* Function to format the time stamp */
char *time_stamp()
{
	
    memset(time_stam,'\0',30);
	time_t timer;
	timer = time(NULL);
	strftime(time_stam, 26, "%Y-%m-%d %H:%M:%S", localtime(&timer));
	return time_stam;	
}

/* Function to initialize the logger */
void logger_init(char *file_path)
{
	file_ptr = fopen(file_path, "w+");
	fprintf(file_ptr,"Queue Init\n\n");
    fclose(file_ptr);

    if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        perror("Mutex init failed\n"); 
    }


    struct mq_attr mq_attributes;

    /* Setting the message queue attributes */
    mq_attributes.mq_flags = 0;
    mq_attributes.mq_maxmsg = 100;
    mq_attributes.mq_msgsize = MAX_BUFFER_SIZE;
    mq_attributes.mq_curmsgs = 100;

    msg_queue = mq_open(QUEUE_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0666, &mq_attributes);
}

/* Thread callback function for logger */
void *logger_thread_callback(void *arg)
{
	
    char buffer[MAX_BUFFER_SIZE];
    char file_name[MAX_BUFFER_SIZE];
    char logger_level[10];

    int received_log_level;
    
    file_descriptors *fd = (file_descriptors *)arg;

    sprintf(file_name,"%s%s/%s",LOG_PATH,fd->file_path,fd->file_name);
   	printf("File name = %s\n",file_name);

    if((setup_timer_POSIX(&timer_id_log,log_timer_handler)) == ERROR)
    {
        perror("Error on creating timer for logger\n");
        pthread_cancel(logger_thread); 
    }

    if((kick_timer(timer_id_log, Delay_NS)) == ERROR)
    {
        perror("Error on kicking timer for logger\n");
        pthread_cancel(logger_thread); 
    }

    /* Opening a FIFO to write logger heartbeat */    
    fd3_w = open(log_t, O_WRONLY | O_NONBLOCK | O_CREAT, 0666);
   	if(fd3_w == ERROR)
    {
        perror("Error on creating FIFO fd3_w for loger\n");
        pthread_cancel(logger_thread); 
    }

   	while(1)
   	{

        if(FLAG_LOG)
        {
            if((write(fd3_w, "G", 1)) == ERROR)
            {
                perror("Error on write of logger heartbeat\n");
            }

            FLAG_LOG = 0;
        }

        /* Check if message is received in message queue */
	    if(mq_receive(msg_queue, buffer, MAX_BUFFER_SIZE, 0) > 0)
	    {
			pthread_mutex_lock(&lock);

            sscanf(buffer,"%s",logger_level);

            /* Check user specified log level */
            if(strcmp(logger_level, "ERROR") == 0)
                received_log_level = Error;
            else if(strcmp(logger_level, "WARN") == 0)
                received_log_level = Warn;
            else if(strcmp(logger_level, "DEBUG") == 0)
                received_log_level = Debug;
            else if(strcmp(logger_level, "INFO") == 0)
                received_log_level = Info;
            else
                received_log_level = Nolog;

            if(received_log_level >= user_select_log_level)
                LOG_MESSAGE(file_name,"\n%s -----> [TIMESTAMP] %s\n", buffer, time_stamp());
			
            memset(buffer,0,MAX_BUFFER_SIZE);
            pthread_mutex_unlock(&lock);
	    }
	}

    mq_close(msg_queue);
    mq_unlink(QUEUE_NAME);
    close(fd3_w);
}

