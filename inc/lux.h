#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>

#define CONTROL_REGISTER (0X00)
#define TIMING_REGISTER (0X01)
#define DATA0LOW_REGISTER (0X0C)
#define DATA0HIGH_REGISTER (0X0D)
#define DATA1LOW_REGISTER (0X0E)
#define DATA1HIGH_REGISTER (0X0F)

#define WRITE_COMMAND (0x80)

int i2c_setup(int ,int );
int lux_sensor_setup();
int read_channel_0();
int read_channel_1();
float lux_measurement(float , float );