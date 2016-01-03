/*
 * Flink.c
 *
 * Created: 01.12.2015 11:08:03
 * Author : Raphael Lauber
 */ 

#include "board.h"
//#include "SPI.h"
#include "flinklib.h"
#include "types.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint8_t val;
	char description[48];
	initBoard();
	//flink_spi_init();
	
	
	flink_dev*    dev;
	flink_subdev* subdev;
	uint8_t subdevice_id = 1;
	int error = 0;
	
	dev = flink_open();
	
	subdev = flink_get_subdevice_by_unique_id(dev, 3); // info device
	error = flink_info_get_description(subdev, description);
	
	subdev = flink_get_subdevice_by_unique_id(dev, 1); // GPIO device
	error = flink_dio_set_direction(subdev, 0x02, 0x01);
	
	
	
	
	while(1) {
 		
 		PORTA = (PINA & 0x01)^0x01;	// Toggle LED
 		error = flink_dio_get_value(subdev,0x00,&val);	// SW0 --> LEDR0
		error = flink_dio_set_value(subdev,0x02,val);
 		_delay_ms(500);
		 
 	}
	
// 	flink_dev	 myFdev;
// 	flink_subdev* myFsubdevs[3];
// 	flink_subdev myGPIO;
// 	flink_subdev myPWM;
// 	flink_subdev myInfo;
// 	
// 	myFdev.nof_subdevices = 3;		/// Number of subdevices
// 	myFdev.subdevices = (flink_subdev*)myFsubdevs;

// 	myGPIO.id = 1;					/// Identifies a subdevice within a device
// 	myGPIO.function_id = 0x05;			/// Identifies the function of the subdevice
// 	myGPIO.sub_function_id = 0;		/// Identifies the subtype of the subdevice
// 	myGPIO.function_version = 0;	/// Version of the function
// 	myGPIO.base_addr = 0x180;			/// Base address (logical)
// 	myGPIO.mem_size=0x40;			/// Address space size
// 	myGPIO.nof_channels=0x04;		/// Number of channels
// 	myGPIO.unique_id=1;			/// Unique id, must be unique for a certain subdevice
// 	myGPIO.parent=&myFdev;				/// The device this subdevice belongs to
// 	myFsubdevs[0] = &myGPIO;
// 	
// 	myPWM.id = 2;					/// Identifies a subdevice within a device
// 	myPWM.function_id = 0x0c;			/// Identifies the function of the subdevice
// 	myPWM.sub_function_id = 0;		/// Identifies the subtype of the subdevice
// 	myPWM.function_version = 0;	/// Version of the function
// 	myPWM.base_addr = 0x00;			/// Base address (logical)
// 	myPWM.mem_size=0x100;			/// Address space size
// 	myPWM.nof_channels=0x01;		/// Number of channels
// 	myPWM.unique_id=2;			/// Unique id, must be unique for a certain subdevice
// 	myPWM.parent=&myFdev;				/// The device this subdevice belongs to
// 	myFsubdevs[2] = &myPWM;
// 	
// 	myInfo.id = 3;					/// Identifies a subdevice within a device
// 	myInfo.function_id = 0x00;			/// Identifies the function of the subdevice
// 	myInfo.sub_function_id = 0;		/// Identifies the subtype of the subdevice
// 	myInfo.function_version = 0;	/// Version of the function
// 	myInfo.base_addr = 0x100;			/// Base address (logical)
// 	myInfo.mem_size=0x80;			/// Address space size
// 	myInfo.nof_channels=0;		/// Number of channels
// 	myInfo.unique_id=3;			/// Unique id, must be unique for a certain subdevice
// 	myInfo.parent=&myFdev;				/// The device this subdevice belongs to
// 	myFsubdevs[3] = &myInfo;
// 	
// 	flink_dio_set_direction(&myGPIO, 0x02, 0x01);	// LEDR0
// 	flink_dio_set_direction(&myGPIO, 0x03, 0x01);	// LEDR1
// 	
// 	flink_pwm_set_period(&myPWM,1,125);
// 	flink_pwm_set_hightime(&myPWM,1,10);
// 	
// 	flink_info_get_description(&myInfo, description);
// 	
// 	while(1) {
// 		
// 		PORTA = (PINA & 0x01)^0x01;	// Toggle LED
// 		
// 		flink_dio_get_value(&myGPIO,0x00,&val);	// SW0 --> LEDR0
// 		flink_dio_set_value(&myGPIO,0x02,val);
// 		flink_dio_get_value(&myGPIO,0x01,&val);	// SW1 --> LEDR1
// 		flink_dio_set_value(&myGPIO,0x03,val);
// 		
// 		_delay_ms(500);
// 	}
// 	
//     uint8_t data[8];
// 	uint8_t val[4];
// 	static uint8_t dataR[200];
// 	uint8_t i;
// 	
// 	
// 	
// 	// Configure GPIO as output
//  	data[0]  = 0x80;
//  	data[1]  = 0x00;
//  	data[2]  = 0x01;
//  	data[3]  = 0xa0;
//  	data[4]  = 0x00;
//  	data[5]  = 0x00;
//  	data[6]  = 0x00;
//  	data[7]  = 0x0c;
//  	SPI_Write(data, 8);
// 		 
//     while (1) 
//     {
// 		PORTA = (PINA & 0x01)^0x01;	// Toggle LED
// 		_delay_ms(500);
// 		
// 		// Read Range
// 		for (i = 0; i < 0x40 ; i+=0x04) {
// 			data[0] = 0x00;	// Read
// 			data[1] = 0x00;
// 			data[2] = 0x01;
// 			data[3] = 0x80 + i;
// 		
// 			SPI_WriteRead(data, 4, (dataR + i), 4);
// 			_delay_us(10);
// 		} // for
// 
// 		// Read GPIO
// 		data[0]  = 0x00;
//   		data[1]  = 0x00;
//   		data[2]  = 0x01;
//   		data[3]  = 0xa4;
// 		SPI_WriteRead(data, 4, val, 4);
// 		
// 		// Set GPIO
//   		data[0]  = 0x80;
//  		data[1]  = 0x00;
//  		data[2]  = 0x01;
//  		data[3]  = 0xa4;
//  		data[4]  = 0x00;
//  		data[5]  = 0x00;
//  		data[6]  = 0x00;
//  		data[7]  = ((val[3] & 0x3) << 2) | (val[3] & 0x3);
//  		SPI_Write(data, 8);
// 		
//     }
}

