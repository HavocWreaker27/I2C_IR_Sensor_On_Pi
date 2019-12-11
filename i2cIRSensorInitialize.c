//Compile by running these commands in terminal:
//gcc i2cIRSensorInitialize.c -o i2cIRSensor
//chmod +x newtest
//./i2cIRSensor

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int fd;														// File descrition
char *fileName = "/dev/i2c-1";								// Name of the port we will be using
int  address = 0x58;										// Address of the SRF08 shifted right 1 bit
unsigned char data_buf[16];
unsigned char buf[16];											// Buffer for data being read/ written on the i2c bus
int Ix[4];
int Iy[4];
int s;
int val[0];

void i2c_camera_settings(){
	
	int fd;														// File descrition
	char *fileName = "/dev/i2c-1";								// Name of the port we will be using
	int  address = 0x58;										// Address of the SRF08 shifted right 1 bit
	unsigned char buf[16];										// Buffer for data being read/ written on the i2c bus


	if ((fd = open(fileName, O_RDWR)) < 0) {					// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}
	
	if (ioctl(fd, I2C_SLAVE, address) < 0) {					// Set the port options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}

	else {
		
		printf("Successfully opened I2C.");
	}


	unsigned char buffed[16];

	buffed[0] = 0x30;													// Commands for performing a ranging on the SRF08
	buffed[1] = 0x08;
	if ((write(fd, buffed, 2)) != 2) {								// Write commands to the i2c port
		printf("Error writing to i2c slave. Step 1\n");
		exit(1);
	}
	usleep(750000);		
	
	buffed[0] = 0x00;													// Commands for performing a ranging on the SRF08
	
	buffed[1] = 0x00;
	buffed[2] = 0x00;													// Commands for performing a ranging on the SRF08
	buffed[3] = 0x00;
	buffed[4] = 0x00;													// Commands for performing a ranging on the SRF08
	buffed[5] = 0x00;
	buffed[6] = 0x00;													// Commands for performing a ranging on the SRF08
	buffed[7] = 0x90;
	buffed[8] = 0x00;
	buffed[9] = 0x41;
	if ((write(fd, buffed, 10)) != 10) {								// Write commands to the i2c port
		printf("Error writing to i2c slave. Step 2\n");
		exit(1);
	}
	usleep(750000);	

	buffed[0] = 0x1A;													// Commands for performing a ranging on the SRF08
	buffed[1] = 0x40;
	buffed[2] = 0x00;
	if ((write(fd, buffed, 3)) != 3) {								// Write commands to the i2c port
		printf("Error writing to i2c slave. Step 3\n");
		exit(1);
	}
	usleep(750000);	

	buffed[0] = 0x1A;													// Commands for performing a ranging on the SRF08
	buffed[1] = 0x40;
	buffed[2] = 0x00;
	if ((write(fd, buffed, 3)) != 3) {								// Write commands to the i2c port
		printf("Error writing to i2c slave. Step 4\n");
		exit(1);
	}
	usleep(750000);	

	buffed[0] = 0x33;													// Commands for performing a ranging on the SRF08
	buffed[1] = 0x33;
	if ((write(fd, buffed, 2)) != 2) {								// Write commands to the i2c port
		printf("Error writing to i2c slave. Step 5\n");
		exit(1);
	}
	usleep(750000);

	buffed[0] = 0x30;													// Commands for performing a ranging on the SRF08
	buffed[1] = 0x08;
	if ((write(fd, buffed, 2)) != 2) {								// Write commands to the i2c port
		printf("Error writing to i2c slave. Step 6\n");
		exit(1);
	}
	usleep(750000);


	
}


int main(int argc, char **argv)
{

	
	i2c_camera_settings();
	//printf("Sleeping");
	usleep(750000);

	if ((fd = open(fileName, O_RDWR)) < 0) {						// Open port for reading and writing
		printf("Failed to open i2c port\n");
		exit(1);
	}
	
	if (ioctl(fd, I2C_SLAVE, address) < 0) {						// Set the port options and set the address of the device we wish to speak to
		printf("Unable to get bus access to talk to slave\n");
		exit(1);
	}

	else {
		
		printf("Successfully opened I2C.");
	}

	int inf;
	for (inf=0;inf=10;inf=inf+1){
		buf[0] = 0x36;												// This is the register we wish to read from			
												
		if ((write(fd, buf, 1)) != 1) {								// Send register to read from
			printf("Error writing to i2c slave. 0x36. Step 7\n");
			exit(1);
		}
	
		if (read(fd, data_buf, 16) != 16) {									// Read back data into buf[]
			printf("Unable to read from slave. Can't get 16 bytes\n");
			exit(1);
		}
		else {
			
			Ix[0] = data_buf[1];
        	Iy[0] = data_buf[2];
        	s = data_buf[3];
        	//Ix[0] += (s & 0x30) <<4;
        	Ix[0] = data_buf[1] | ((data_buf[3] >> 4) & 0x03) << 8;
        	Iy[0] = data_buf[2] | ((data_buf[3] >> 6) & 0x03) << 8;
        	//Ix[0] = Ix[0] / test;

			Ix[1] = data_buf[4];
			Iy[1] = data_buf[5];
			s = data_buf[6];
			Ix[1] += (s & 0x30) <<4;
			Iy[1] += (s & 0xC0) <<2;

			Ix[2] = data_buf[7];
			Iy[2] = data_buf[8];
			s = data_buf[9];
			Ix[2] += (s & 0x30) <<4;
			Iy[2] += (s & 0xC0) <<2;

			Ix[3] = data_buf[10];
			Iy[3] = data_buf[11];
			s = data_buf[12];
			Ix[3] += (s & 0x30) <<4;
			Iy[3] += (s & 0xC0) <<2;

			printf("%u",Ix[0]);
			printf(",%u",Iy[0]);
			printf(",%u",Ix[1]);
			printf(",%u",Iy[1]);
			printf(",%u",Ix[2]);
			printf(",%u",Iy[2]);
			printf(",%u",Ix[3]);
			printf(",%u \n",Iy[3]);
				
			

			
		}
	}
	
}
