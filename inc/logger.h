#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h> // mkdir
#include <mqueue.h>
#include <time.h>
#include <sys/syscall.h>

FILE *file_ptr;

#define LOG_PATH "./log_folder/"

#define LOG_MESSAGE(file_name,...) { \
						  fprintf(file_ptr, ##__VA_ARGS__);\
						  fflush(file_ptr);\
						  }


#define QUEUE_NAME "/msg_queue"
#define MAX_BUFFER_SIZE	100


typedef struct
{
	char *file_name;
	char *file_path;	
}file_descriptors;

mqd_t msg_queue;

pthread_t logger_thread;

char *time_stamp();

void logger_init(char *);

void *logger_thread_callback(void *);

float get_temperature();

float get_lux();
#endif