#include "lux_wrapper.h"
#include "lux.h"
#include "temp.h"
#include <assert.h>
#include "common.h"
#include <stdio.h>
#include "led.h"
#include "logger.h"

#define MAX_BUFFER_SIZE 100

int file_des_lux;
uint8_t register_data;
int ret_status;

int unit_lux()
{
	printf("Begin lux sensor test\n");


	i2c_setup(&file_des_lux,2,0x39);

	/*CONTROL_REGISTER*/
	ret_status = byte_access_lux_register(file_des_lux, CONTROL_REGISTER,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);

	register_data = 0x03;
	ret_status = byte_access_lux_register(file_des_lux, NONE,WRITE , &register_data, NONE );
	assert(ret_status == SUCCESS);
	

	ret_status = byte_access_lux_register(file_des_lux, CONTROL_REGISTER,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);

	register_data = 0;
	ret_status = byte_access_lux_register(file_des_lux, NONE,READ , &register_data, NONE );
	printf("REGISTER DATA after write%x\n",register_data );
	assert(register_data ==  0x33);//reserved set as 3
	
	/******************************************************/
	ret_status =  byte_access_lux_register(file_des_lux, TIMING_REGISTER,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);	
	
	register_data = 0x02;
	ret_status = byte_access_lux_register(file_des_lux, NONE,WRITE , &register_data, NONE );
	assert(ret_status == SUCCESS);	

	ret_status = byte_access_lux_register(file_des_lux, TIMING_REGISTER,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);

	register_data = 0;
	ret_status = byte_access_lux_register(file_des_lux, NONE,READ , &register_data, NONE );
	printf("REGISTER DATA after write%x\n",register_data );
	assert(register_data ==  0x02);


	/******************************************************/
	ret_status =  byte_access_lux_register(file_des_lux, INTERRUPT,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);	
	
	register_data = 0x11;
	ret_status = byte_access_lux_register(file_des_lux, NONE,WRITE , &register_data, NONE );
	assert(ret_status == SUCCESS);	

	ret_status = byte_access_lux_register(file_des_lux, INTERRUPT,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);

	register_data = 0;
	ret_status = byte_access_lux_register(file_des_lux, NONE,READ , &register_data, NONE );
	printf("REGISTER DATA after write%x\n",register_data );
	assert(ret_status == SUCCESS);
	assert(register_data ==  0x11);

	
	/******************************************************/

	ret_status =  byte_access_lux_register(file_des_lux, INDICATION_REGISTER,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);	
	

	register_data = 0;
	ret_status = byte_access_lux_register(file_des_lux, NONE,READ , &register_data, NONE );
	printf("REGISTER DATA - Indication register -%x\n",register_data );
	assert(ret_status == SUCCESS);

	
	/******************************************************/
	ret_status =  byte_access_lux_register(file_des_lux, DATA0LOW_REGISTER,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);	
	

	register_data = 0;
	ret_status = byte_access_lux_register(file_des_lux, NONE,READ , &register_data, NONE );
	printf("REGISTER DATA - DATA0LOW_REGISTER- %x\n",register_data );
	assert(ret_status == SUCCESS);

	
	/******************************************************/
	ret_status =  byte_access_lux_register(file_des_lux, DATA0HIGH_REGISTER,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);	
	

	register_data = 0;
	ret_status = byte_access_lux_register(file_des_lux, NONE,READ , &register_data, NONE );
	printf("REGISTER DATA - DATA0HIGH_REGISTER %x\n",register_data );
	assert(ret_status == SUCCESS);

	
	/******************************************************/
	ret_status =  byte_access_lux_register(file_des_lux, DATA1LOW_REGISTER,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);	
	

	register_data = 0;
	ret_status = byte_access_lux_register(file_des_lux, NONE,READ , &register_data, NONE );
	printf("REGISTER DATA - DATA1LOW_REGISTER %x\n",register_data );
	assert(ret_status == SUCCESS);

	
	/******************************************************/
	ret_status =  byte_access_lux_register(file_des_lux, DATA1HIGH_REGISTER,COMMAND , &register_data, NONE );
	assert(ret_status == SUCCESS);	
	

	register_data = 0;
	ret_status = byte_access_lux_register(file_des_lux, NONE,READ , &register_data, NONE );
	printf("REGISTER DATA - DATA1HIGH_REGISTER %x\n",register_data );
	assert(ret_status == SUCCESS);

	
	/******************************************************/
	uint16_t word;
	/*command to write as a word for high threshold register */
	ret_status = word_access_lux_register(file_des_lux, THRESHHIGHLOW,COMMAND , &word, NONE );
	assert(ret_status == SUCCESS);

	/*Writing to threshold register*/
	word = 0x0BB8; //set to 3000
	ret_status = word_access_lux_register(file_des_lux, NONE,WRITE , &word, NONE );
	assert(ret_status == SUCCESS);

	ret_status = word_access_lux_register(file_des_lux, THRESHHIGHLOW,COMMAND , &word, NONE );
	assert(ret_status == SUCCESS);

	/*Writing to threshold register*/
	ret_status = word_access_lux_register(file_des_lux, NONE,READ , &word, NONE );
	assert(ret_status == SUCCESS);
	printf("REGISTER DATA - THRESHHIGHLOW %x\n",word );
	assert(word == 0x0BB8);
	/******************************************************/
	/*command to write as a word for high threshold register */
	ret_status = word_access_lux_register(file_des_lux, THRESHLOWLOW,COMMAND , &word, NONE );
	assert(ret_status == SUCCESS);

	/*Writing to threshold register*/
	word = 0x0101; //set to 3000
	ret_status = word_access_lux_register(file_des_lux, NONE,WRITE , &word, NONE );
	assert(ret_status == SUCCESS);

	ret_status = word_access_lux_register(file_des_lux, THRESHLOWLOW,COMMAND , &word, NONE );
	assert(ret_status == SUCCESS);

	/*Writing to threshold register*/
	ret_status = word_access_lux_register(file_des_lux, NONE,READ , &word, NONE );
	assert(ret_status == SUCCESS);
	printf("REGISTER DATA - THRESHLOWLOW %x\n",word );
	assert(word == 0x0101);




	printf("Ending lux sensor test\n");
	return SUCCESS;

}


int unit_temp()
{
	printf("Begin temperature sensor test\n");
	uint16_t configuration;

	/******************************************************/
	/* Testing temperature init */
	ret_status = temp_sensor_init();
	assert(ret_status == SUCCESS);

	/******************************************************/
	/* Writing default value 0x60A0 to the control register */
	ret_status = config_reg_write_default();
	assert(ret_status == SUCCESS);

	ret_status = config_reg_read(&configuration);
	assert(ret_status == SUCCESS);

	assert(configuration == 0x60A0);

	/******************************************************/
	/* Writing 10 degree celcius to tlow register */
	ret_status = tlow_reg_write(10);
	assert(ret_status == SUCCESS);	


	ret_status = tlow_reg_read();
	assert(ret_status == 160); // (160 * 0.0625 = 10 degree C)


	/******************************************************/
	/* Writing 100 degree celcius to tlow register */
	ret_status = thigh_reg_write(100);
	assert(ret_status == SUCCESS);

	ret_status = thigh_reg_read();
	assert(ret_status == 1600); // (1600 * 0.0625 = 100 degree C)


	/******************************************************/
	/* Configuring sensor to work in shutdown mode */
	ret_status = config_sd();
	assert(ret_status == SUCCESS);

	config_reg_read(&configuration);
	assert(configuration == 0xE1A0);

	/******************************************************/
	/* Configuring sensor to work in continuous conversion mode */
	ret_status = config_sd_continuous();
	assert(ret_status == SUCCESS);

	config_reg_read(&configuration);
	assert(configuration == 0x60A0);

	/******************************************************/
	/* Configuring sensor to alert after 6 fault queue updates */
	ret_status = config_fault_bits_6();
	assert(ret_status == SUCCESS);

	config_reg_read(&configuration);
	assert(configuration == 0x78A0);

	/******************************************************/
	/* Configuring sensor to work in 12 bit mode */
	ret_status = config_em_normal();
	assert(ret_status == SUCCESS);

	config_reg_read(&configuration);
	assert(configuration == 0x78A0);

	/******************************************************/
	/* Configuring sensor to work in 13 mode */
	ret_status = config_em_extended();
	assert(ret_status == SUCCESS);

	config_reg_read(&configuration);
	assert(configuration == 0x78B0);

	/******************************************************/
	/* Configuring sensor to sample at 8hz */
	ret_status = config_conversion_rate_8HZ();
	assert(ret_status == SUCCESS);

	config_reg_read(&configuration);
	assert(configuration == 0x78F0);

	/******************************************************/
	/* Configuring sensor alert pin to be active high */
	ret_status = config_pol_alert_active_high();
	assert(ret_status == SUCCESS);

	config_reg_read(&configuration);
	assert(configuration == 0x7CD0);

	/******************************************************/
	/* Configuring sensor alert pin to be active high */
	ret_status = config_pol_alert_active_low();
	assert(ret_status == SUCCESS);

	config_reg_read(&configuration);
	assert(configuration == 0x78F0);

	/******************************************************/
	/* Reading alert pin (alert pin is active low) */
	ret_status = config_read_alert();
	assert(ret_status == 1);

	printf("Ending temperature sensor test\n");

	return SUCCESS;

}

int unit_logger(char *file_name)
{
	printf("Begin logger test\n");
	logger_init(file_name);
	char buffer[MAX_BUFFER_SIZE];

	strcpy(buffer,"UNIT TESTING");
	
	mq_send(msg_queue, buffer, MAX_BUFFER_SIZE, 0);
	
	mq_receive(msg_queue, buffer, MAX_BUFFER_SIZE, 0);

	assert(strcmp(buffer,"UNIT TESTING") == 0);
	

	mq_close(msg_queue);
    mq_unlink(QUEUE_NAME);

    printf("Ending logger test\n");
	// assert(ret_status == SUCCESS);

	return SUCCESS;
}	

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		perror("Please enter the <log file name> follwed by <log file folder name>");
		exit(ERROR);
	}
	char *file_name_main = argv[1];
	char *file_path = argv[2];
	char file_name[MAX_BUFFER_SIZE];
	sprintf(file_name,"%s%s/%s",LOG_PATH, file_path, file_name_main);

	int ret_val;

	ret_val = unit_logger(file_name);

	if(!ret_val)
		printf("Logger unit test passed\n");

	ret_val = unit_temp();
	if(!ret_val)
		printf("Temperature unit test passed\n");


	ret_val = unit_lux();
	if(!ret_val)	
		printf("Lux unit test passed\n");



	return 0;
}