#include "main.h"

/*
direction encoder should read about 85
strafe encoder should read about 35

//note these values are defined because of the checkpoint I have choosen.
*/
/*
©Tad Keller, Ultrasonic Test(USTest)
A prototype project acting as a checkpoint system for the skills auton run. Vex 2018-2019 game Turning Point.
*/

//change these values based on how your checkpoint is layed out,
//these specify an acceptable range for the ultrasonic sensors to know when to stop the motors.
#define DIR_MIN_DIST 30
#define DIR_MAX_DIST 40

#define STR_MIN_DIST 80
#define STR_MAX_DIST 90

void operatorControl()
{
	//never ending loop, duh.
	while (true)
	{
			//check both encoders within a range to see if we even need to do anything besides stop the motors.
			if(ultrasonicGet(directionUS) < STR_MIN_DIST || ultrasonicGet(directionUS) > STR_MAX_DIST || ultrasonicGet(strafeUS) < DIR_MIN_DIST || ultrasonicGet(strafeUS) > DIR_MAX_DIST)
			{
				//if the strafe encoder is out of range, the two if statments inside here turn on the motors reverse or forward based if
				//we are forward or backward out of range.
				if(ultrasonicGet(strafeUS) < DIR_MIN_DIST || ultrasonicGet(strafeUS) > DIR_MAX_DIST)
				{
					//going deeper into the "tree"
					if(ultrasonicGet(strafeUS) < DIR_MIN_DIST)
					{
						//note one motor is reversed because I was to lazy to physically switch it.
						motorSet(STR_BACK_MOT, -30);
						motorSet(STR_FRONT_MOT, 30);
					}
					else
					{
						if(ultrasonicGet(strafeUS) > DIR_MAX_DIST)
						{
							//note one motor is reversed because I was to lazy to physically switch it.
							motorSet(STR_BACK_MOT, 30);
							motorSet(STR_FRONT_MOT, -30);
						}
					}
				}
				else
				{
					//stop just the strafe motors if the strafe ultrasonic sensor is in range.
					motorStop(STR_BACK_MOT);
					motorStop(STR_FRONT_MOT);
				}
				//if the direction encoder is out of range, the two if statments inside here turn on the motors reverse or forward based if
				//we are forward or backward out of range.
				if(ultrasonicGet(directionUS) < STR_MIN_DIST || ultrasonicGet(directionUS) > STR_MAX_DIST)
				{
					//going deeper into the "tree"
					if(ultrasonicGet(directionUS) < STR_MIN_DIST)
					{
						motorSet(DIR_L_MOT, 30);
						motorSet(DIR_R_MOT, 30);
					}
					else
					{
						if(ultrasonicGet(directionUS) > STR_MAX_DIST)
						{
							motorSet(DIR_L_MOT, -30);
							motorSet(DIR_R_MOT, -30);
						}
					}
				}
				else
				{
					//stop just the strafe motors if the direction ultrasonic sensor is in range.
					motorStop(DIR_L_MOT);
					motorStop(DIR_R_MOT);
				}
			}
			//if both of the encoders are in range, stop all motors.
			else
			{
				motorStop(DIR_L_MOT);
				motorStop(DIR_R_MOT);
				motorStop(STR_BACK_MOT);
				motorStop(STR_FRONT_MOT);
			}
			//printing the ultrasonic sensor values to the PROS CLI for debugging.
			printf("direction : %d\n", ultrasonicGet(directionUS));
			printf("strafe : %d\n", ultrasonicGet(strafeUS));

			//may want to add a delay to prevent the constant motor shaking.
	}
}
