/*
 Name:		SpineX.ino
 Created:	7/5/2015 12:31:03 PM
 Author:	mik
*/



/******* Orientation Sensor Interface Module *********/

#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial mySerial(2, 3); // RX, TX

//Endereco I2C do MPU6050
const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void setup()
{
	//Inicializa
	Wire.begin();
	Wire.beginTransmission(MPU);
	Wire.write(0x6B); 
   
	//Inicializa o MPU-6050
	Wire.write(0); 
	Wire.endTransmission(true);

	Serial.begin(9600);
	while(!Serial)
	{
		;// wait for serial port to connect. Needed for Leonardo only
	}


	// set the data rate for the SoftwareSerial port
	mySerial.begin(9600);
	mySerial.println("Hello, world?");
}

void loop()
{

	Wire.beginTransmission(MPU);
	Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
	Wire.endTransmission(false);
	
	// request to start
	Wire.requestFrom(MPU,14,true);  
	
	//values from sensor
	AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
	AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
	AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
	Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
	GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
	GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
	GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
   
	int nBluetooth = mySerial.available();
	char buffer[32];

	// Accelerometer X value
	//Serial.print("Gyro:");
	//Serial.print("AcX = "); Serial.print(AcX);
	if(nBluetooth > 0)
	{
		itoa (AcX,buffer,10);
		mySerial.write("AcX = "); mySerial.write(buffer);
	}

	// Accelerometer Y value
	//Serial.print(" | AcY = "); Serial.print(AcY);
	if(nBluetooth > 0)	
	{
		itoa (AcY,buffer,10);
		mySerial.write(" | AcY = "); mySerial.write(buffer);
	}

	// Accelerometer Z value
	//Serial.print(" | AcZ = "); Serial.print(AcZ);
	if(nBluetooth > 0)	
	{
		itoa (AcZ,buffer,10);
		mySerial.write(" | AcZ = "); mySerial.write(buffer);
	}

	// Temperature in Celsius
	//Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
	if(nBluetooth > 0)	
	{
		itoa (Tmp/340.00+36.53,buffer,10);
		mySerial.write(" | Tmp = "); mySerial.write(buffer);
	}

	// Gyroscope X value
	Serial.print("GyX = "); Serial.print(GyX);
    if(nBluetooth > 0)
	{
		itoa (GyX,buffer,10);
		mySerial.write(" | GyX = "); mySerial.write(buffer);
	}

	// Gyroscope Y value
	Serial.print(", GyY = "); Serial.print(GyY);
	if(nBluetooth > 0)	
	{
		itoa (GyY,buffer,10);
		mySerial.write(" | GyY = "); mySerial.write(buffer);
	}

	// Gyroscope Z value
	Serial.print(", GyZ = "); Serial.println(GyZ); 
	if(nBluetooth > 0)	
	{
		itoa (GyZ,buffer,10);
		mySerial.write(" | GyZ = "); mySerial.write(buffer); mySerial.write("\n");
	}

	delay(50);
}




/*** Bluetooth Module Interface ****/
/*
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(9600);
	while(!Serial)
	 {
		 ;// wait for serial port to connect. Needed for Leonardo only
	 }


	// set the data rate for the SoftwareSerial port
	mySerial.begin(9600);
	mySerial.println("Hello, world?");
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	int nByte = 0;
	
	if(Serial.available())
	{
		nByte = Serial.read();

		Serial.print("Byte: "); 
		Serial.println(nByte); Serial.print("");

		int nBluetooth = mySerial.available();

		Serial.print("Bluetooth: "); 
		Serial.println(nBluetooth); Serial.print("");

		if(nBluetooth > 0)
		{
			mySerial.write(nByte);
			if(nByte > 0)
			{
				Serial.write(nByte);
				Serial.print("Data Send to Bluetooth: ");
				Serial.println(nByte); Serial.print("");
			}
		}
		
		delay(100);
	}
}

*/