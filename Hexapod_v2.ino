#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

#include <SoftwareSerial.h>
#include "Cytron_PS2Shield.h"

//SERVOMIN  650
//SERVOMAX  2350
// 1075 for middle min
// 1925 for middle max

const int LEDpin = 13;
int fastver = 100;
int speed = 125;
//int current = 1;
//int last = 1;

Cytron_PS2Shield ps2(2, 3); // SoftwareSerial: Rx and Tx pin

float SERVOFREQ = 50;
float pulseconstant;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


void servoWrite(uint8_t n, float pulse)
{
	float pulsetick;
	pulsetick = pulse / pulseconstant;
	//Serial.println(pulsetick);
	pwm.setPWM(n, 0, pulsetick);
}
void idleMode()
{
	servoWrite(0, 1500);
	servoWrite(1, 1500);
	servoWrite(2, 1500);
	servoWrite(3, 1500);
	servoWrite(4, 1500);
	servoWrite(5, 1500);
	servoWrite(6, 1075);
	servoWrite(7, 1075);
	servoWrite(8, 1075);
	servoWrite(9, 1075);
	servoWrite(10, 1075);
	servoWrite(11, 1075);
}
void turnRight()
{
	servoWrite(6, 1500);
	servoWrite(8, 1500);
	servoWrite(10, 1500);
	delay(speed);

	servoWrite(0, 1925);
	servoWrite(1, 1500);
	servoWrite(2, 1925);
	servoWrite(3, 1500);
	servoWrite(4, 1925);
	servoWrite(5, 1500);

	delay(speed);

	servoWrite(6, 1075);
	servoWrite(8, 1075);
	servoWrite(10, 1075);

	delay(speed);

	//Next
	if(ps2.readButton(PS2_RIGHT) == 0)
	{
		servoWrite(7, 1500);
		servoWrite(9, 1500);
		servoWrite(11, 1500);
		delay(speed);

		servoWrite(0, 1500);
		servoWrite(1, 1925);
		servoWrite(2, 1500);
		servoWrite(3, 1925);
		servoWrite(4, 1500);
		servoWrite(5, 1925);

		delay(speed);

		servoWrite(7, 1075);
		servoWrite(9, 1075);
		servoWrite(11, 1075);

		delay(speed);
	}
	else
	{
		idleMode();
	}
}
void turnLeft()
{
	servoWrite(6, 1500);
	servoWrite(8, 1500);
	servoWrite(10, 1500);
	delay(speed);

	servoWrite(0, 1075);
	servoWrite(1, 1500);
	servoWrite(2, 1075);
	servoWrite(3, 1500);
	servoWrite(4, 1075);
	servoWrite(5, 1500);

	delay(speed);

	servoWrite(6, 1075);
	servoWrite(8, 1075);
	servoWrite(10, 1075);

	delay(speed);

	//Next

	if(ps2.readButton(PS2_LEFT) == 0)
	{
		servoWrite(7, 1500);
		servoWrite(9, 1500);
		servoWrite(11, 1500);

		delay(speed);

		servoWrite(0, 1500);
		servoWrite(1, 1075);
		servoWrite(2, 1500);
		servoWrite(3, 1075);
		servoWrite(4, 1500);
		servoWrite(5, 1075);

		delay(speed);

		servoWrite(7, 1075);
		servoWrite(9, 1075);
		servoWrite(11, 1075);

		delay(speed);
	}
	else
	{
		idleMode();
	}
}
void goForward()
{
	servoWrite(6, 1500);
	servoWrite(8, 1500);
	servoWrite(10, 1500);
	delay(speed);

	servoWrite(0, 1500);
	servoWrite(1, 1300);
	servoWrite(2, 1800);
	servoWrite(3, 1700);
	servoWrite(4, 1300);
	servoWrite(5, 1800);

	delay(speed);

	servoWrite(6, 1075);
	servoWrite(8, 1075);
	servoWrite(10, 1075);

	delay(speed);

	//Next

	servoWrite(7, 1500);
	servoWrite(9, 1500);
	servoWrite(11, 1500);

	delay(speed);

	servoWrite(0, 1200);
	servoWrite(1, 1700);
	servoWrite(2, 1500);
	servoWrite(3, 1300);
	servoWrite(4, 1700);
	servoWrite(5, 1500);

	delay(speed);

	servoWrite(7, 1075);
	servoWrite(9, 1075);
	servoWrite(11, 1075);

	delay(speed);
}
void goBackward()
{
	idleMode();
	// Not here yet
}

void setup()
{
	ps2.begin(9600);
	pinMode(LEDpin, OUTPUT);
	pulseconstant = (1000000 / SERVOFREQ) / 4096;
	pwm.begin();
	pwm.setPWMFreq(SERVOFREQ);
	Serial.begin(9600);
	idleMode();
	delay(1000);
}

void loop()
{

	//	Serial.println();

	// Belly Flop
	if(ps2.readButton(PS2_CROSS) == 0)
	{
		servoWrite(0, 1500);
		servoWrite(1, 1500);
		servoWrite(2, 1500);
		servoWrite(3, 1500);
		servoWrite(4, 1500);
		servoWrite(5, 1500);
		servoWrite(6, 1925);
		servoWrite(7, 1925);
		servoWrite(8, 1925);
		servoWrite(9, 1925);
		servoWrite(10, 1925);
		servoWrite(11, 1925);
		delay(250);
		while(true)
		{
			if(ps2.readButton(PS2_CROSS) == 0)
			{
				idleMode();
				delay(250);
				break;
			}
			delay(15);
		}

	}

	// Debouncer
	/**
	if(ps2.readButton(PS2_SQUARE) == 0)
	{
		if(last == 1)
		{
			current = 2;
		}
		else
		{
			current = 1;
		}
		delay(5);
	}
	*/
	
	// Speed Boost
	if(ps2.readButton(PS2_SQUARE) == 0)
	{
		if(speed == 125)
		{
			speed = 75;
		}
		else
		{
			speed = 125;
		}
		
		//last = current;
		delay(5);
	}

	
	// Leg test
	if(ps2.readButton(PS2_TRIANGLE) == 0)
	{
		servoWrite(6, 1925);
		delay(fastver);
		servoWrite(0, 1925);
		delay(fastver);
		servoWrite(0, 1075);
		delay(fastver);
		servoWrite(6, 1075);
		delay(fastver);
		servoWrite(0, 1500);
		delay(fastver);
		servoWrite(7, 1925);
		delay(fastver);
		servoWrite(1, 1925);
		delay(fastver);
		servoWrite(1, 1075);
		delay(fastver);
		servoWrite(7, 1075);
		delay(fastver);
		servoWrite(1, 1500);
		delay(fastver);
		servoWrite(8, 1925);
		delay(fastver);
		servoWrite(2, 1925);
		delay(fastver);
		servoWrite(2, 1075);
		delay(fastver);
		servoWrite(8, 1075);
		delay(fastver);
		servoWrite(2, 1500);
		delay(fastver);
		servoWrite(9, 1925);
		delay(fastver);
		servoWrite(3, 1925);
		delay(fastver);
		servoWrite(3, 1075);
		delay(fastver);
		servoWrite(9, 1075);
		delay(fastver);
		servoWrite(3, 1500);
		delay(fastver);
		servoWrite(10, 1925);
		delay(fastver);
		servoWrite(4, 1925);
		delay(fastver);
		servoWrite(4, 1075);
		delay(fastver);
		servoWrite(10, 1075);
		delay(fastver);
		servoWrite(4, 1500);
		delay(fastver);
		servoWrite(11, 1925);
		delay(fastver);
		servoWrite(5, 1925);
		delay(fastver);
		servoWrite(5, 1075);
		delay(fastver);
		servoWrite(11, 1075);
		delay(fastver);
		servoWrite(5, 1500);
		delay(fastver);
	}
	
	if(ps2.readButton(PS2_UP) == 0)
	{
		while(ps2.readButton(PS2_UP) == 0)
		{
			goForward();
		}
		idleMode();
	}

	if(ps2.readButton(PS2_DOWN) == 0)
	{
		while(ps2.readButton(PS2_DOWN) == 0)
		{
			goBackward();
		}
		idleMode();
	}

	if(ps2.readButton(PS2_LEFT) == 0)
	{
		while(ps2.readButton(PS2_LEFT) == 0)
		{
			turnLeft();
		}
		idleMode();
	}

	if(ps2.readButton(PS2_RIGHT) == 0)
	{
		while(ps2.readButton(PS2_RIGHT) == 0)
		{
			turnRight();
		}
		idleMode();
	}

	delay(15);

}
