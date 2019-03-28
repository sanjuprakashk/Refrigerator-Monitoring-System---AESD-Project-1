/*****************************************************************
						Includes
*****************************************************************/

#include "logger.h"


const char *log_level[10] = {"INFO", "ERROR", "DEBUG"};

pthread_mutex_t lock;

char *time_stamp()
{
	char *time_stam = malloc(sizeof(char)*30);
	time_t timer;
	timer = time(NULL);
	strftime(time_stam, 26, "%Y-%m-%d %H:%M:%S", localtime(&timer));
	return time_stam;	
}

float get_temperature()
{
	return 25.064;
}

float get_lux()
{
	return 2.56;
}

void logger_init(char *file_path)
{
	FILE *file_ptr;
	file_ptr = fopen(file_path, "w+");
	fprintf(file_ptr,"Queue Init\n\n");
    fclose(file_ptr);

    if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        perror("Mutex init failed\n"); 
        return; 
    }


    struct mq_attr mq_attributes;

    mq_attributes.mq_flags = 0;
    mq_attributes.mq_maxmsg = 10;
    mq_attributes.mq_msgsize = MAX_BUFFER_SIZE;
    mq_attributes.mq_curmsgs = 10;

    msg_queue = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &mq_attributes);
}

void *logger_thread_callback(void *arg)
{
	char buffer[MAX_BUFFER_SIZE];
    char file_name[MAX_BUFFER_SIZE];
    
    file_descriptors *fd = (file_descriptors *)arg;

    sprintf(file_name,"%s%s/%s",LOG_PATH,fd->file_path,fd->file_name);
   	printf("File name = %s\n",file_name);
    
   	
   	while(1)
   	{
	    if(mq_receive(msg_queue, buffer, MAX_BUFFER_SIZE, 0))
	    {
			pthread_mutex_lock(&lock);
			LOG_MESSAGE(file_name,"%s %s %s\n", log_level[0], time_stamp(), buffer);
			pthread_mutex_unlock(&lock);
	    }
	}

    mq_close(msg_queue);
    mq_unlink(QUEUE_NAME);
}
