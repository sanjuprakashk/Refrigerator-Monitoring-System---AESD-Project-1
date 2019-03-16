/*****************************************************************
						Includes
*****************************************************************/
#include "POSIX_timer.h"


// FIFO file path 
 char * Temp = "/tmp/tmp_to_main";
 char * Lux = "/tmp/lux_to_main";
 char * log_t = "/tmp/log_to_main";
 
/*****************************************************************
					POSIX Timer Handler
*****************************************************************/

void temp_timer_handler(union sigval val)
{
	FLAG_READ_TEMP = 1;

	kick_timer(timer_id_temp, Delay_NS);
}

/*****************************************************************
					POSIX Timer Handler
*****************************************************************/

void lux_timer_handler(union sigval val)
{

	FLAG_READ_LUX = 1;

	kick_timer(timer_id_lux, Delay_NS);
}

/*****************************************************************
					POSIX Timer configuration
*****************************************************************/
int setup_timer_POSIX(timer_t *timer_id,void (*handler)(union sigval))
{
	struct 	sigevent sev;
	sev.sigev_notify = SIGEV_THREAD; //Upon timer expiration, invoke sigev_notify_function
	sev.sigev_notify_function = handler; //this function will be called when timer expires
	sev.sigev_notify_attributes = NULL;
	sev.sigev_value.sival_ptr = &timer_id;


	if(timer_create(CLOCK_REALTIME, &sev, timer_id) != 0) //on success, timer id is placed in timer_id
	{
		printf("Error on creating timer\n");
	}  




    return 0;
}

/*****************************************************************
					Start configuration
			Parameter : delay in nano secs
*****************************************************************/
int kick_timer(timer_t timer_id, int interval_ns)
{
   struct itimerspec in;

	in.it_value.tv_sec = 0;
    in.it_value.tv_nsec = interval_ns; //sets initial time period
    in.it_interval.tv_sec = 0;
    in.it_interval.tv_nsec = interval_ns; //sets interval
    
    //issue the periodic timer request here.
    int status = timer_settime(timer_id, 0, &in, NULL) ;
    if( status != 0)
    {
    	printf("Error on settime function\n");
    	return status;
    }
    return 0;
}

/*****************************************************************
					Destroy Timer
*****************************************************************/
int stop_timer(timer_t timer_id)
{
	timer_delete(timer_id);

    return 0;
}
