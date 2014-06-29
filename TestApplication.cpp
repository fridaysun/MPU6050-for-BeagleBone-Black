/* 2014-0629 by Frank.gao
 * Test application for BBB_I2C
 *
 * Check:device ID access,
 *	initialize,
 *	read speed,
 *	cycle read,
 *	FUNCTIONS... 
 *
 * Copyright 2014 Frank.gao, fridaysun@msn.com
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL I
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include "BBB_I2C.h"
#include "MPU6050.h"

int16_t ax,ay,az;
int16_t gx,gy,gz;

using namespace std;

int main(int argc, char *argv[]){
	MPU6050 MPU;
	BBB_I2C BBB_I2C;
	uint8_t rxbuf;
	uint8_t txbuf = 0xaa;
	uint8_t addr = 0x54;  // i2c slave address for E2PROM A[2:0]=3'b000
//	uint8_t addr = 0x68;  // i2c slave address for MPU6050
	uint8_t offset = 0x55;
	uint8_t bitnum = 0x00;
	uint8_t DEV_ID;
	
	uint8_t bitlength = 0x04;
	uint8_t bitstart = 0x00;
	
	cout << "Testing the MPU6050 00.00.01" << endl;

	if (MPU.testConnection() < 1){
		printf ("Device ID not match!\n");
		exit(1);
	}
	
	if (MPU.initialize() < 1) {
		printf ("MPU initialize fail!\n");
		exit(1);
	}
	
	struct timespec start, end, timepcs;
	clock_gettime( CLOCK_REALTIME, &start );	//must linked with the "librt" library to use these functions

//read 1000 times 
	for(int i=0;i<1000;i++){
	MPU.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
 	}
   	clock_gettime( CLOCK_REALTIME, &end );
     	double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000.0d;
	printf ("Take [ %f ] Sec to finish 1000 times read\n", difference);
		

// cycle read
/*	while(1){
	MPU.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    	clock_gettime( CLOCK_REALTIME, &timepcs );
    	double difference = (timepcs.tv_sec - start.tv_sec) + (double)(timepcs.tv_nsec - start.tv_nsec)/1000000000.0d;
	printf ("ax\tay\taz\t:\tgx\tgy\tgz [Time:%f Sec]\n", difference);
	printf ("%d\t%d\t%d\t:\t%d\t%d\t%d\n",ax,ay,az,gx,gy,gz);
	}
*/	
	return 0;
}

