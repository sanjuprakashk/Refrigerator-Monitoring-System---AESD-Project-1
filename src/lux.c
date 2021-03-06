/**
 * @\file	lux.c
 * @\author	Steve Antony X
 * @\brief	This files contains the function definition for lux timer register byte access function
 * @\date	03/30/2019
 *
 */
/*****************************************************************
						Includes
*****************************************************************/
#include "lux.h"

/*****************************************************************
						GLOBAL
*****************************************************************/
pthread_mutex_t lock_res;


/*****************************************************************
					setting up lux sensor
*****************************************************************/
int byte_access_lux_register(int fd, uint8_t register_address,int mode , uint8_t *reg_data, uint8_t flags)
{
	int ret_status;

	if(mode == 1) //write mode
	{

		pthread_mutex_lock(&lock_res);
		ret_status = write(fd, reg_data, 1);
		pthread_mutex_unlock(&lock_res);

		if ( ret_status == ERROR)
		{
			perror("Error on writing the temp register\n");
			return ERROR;
		}
		return SUCCESS;

	}
	else if (mode == 0) //read mode
	{
		*reg_data = 0x00;
		pthread_mutex_lock(&lock_res);
		ret_status = read(fd, reg_data, 1);
		pthread_mutex_unlock(&lock_res);

		/*reading CH1 value lower byte*/
		if ( ret_status == ERROR)
		{
			perror("Error on reading register\n");
			return ERROR;
		}
		return SUCCESS;
	}
	else if (mode == 2) //command mode
	{
		uint8_t  command;
		command = WRITE_COMMAND | register_address | flags;

		pthread_mutex_lock(&lock_res);
		ret_status = write(fd, &command, 1);
		pthread_mutex_unlock(&lock_res);

		if ( ret_status == ERROR)
		{
			perror("Error on writing the temp register\n");
			return ERROR;
		}
		return SUCCESS;
	}
	else
	{
		printf("unknown mode\n");
		return ERROR;
	}
}

