#pragma config(Motor,  port2,           RIGHT_TOP,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RIGHT_BOTTOM,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LEFT_BOTTOM,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LEFT_TOP,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           ARM_LEFT,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           ARM_RIGHT,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LAUNCHER,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           ELEVATOR,      tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define FULL_SPEED 127

bool autonRunning = false;

void KillSwitch()
{
	motor[RIGHT_BOTTOM] = 0;
	motor[LEFT_BOTTOM] = 0;
	motor[LEFT_TOP] = 0;
	motor[RIGHT_TOP] = 0;
	motor[ARM_LEFT] = 0;
	motor[ARM_RIGHT] = 0;
	stopAllTasks();
}

task usercontrol()
{

	while(1 == 1)
	{

		motor[LEFT_BOTTOM]  = (vexRT[Ch3] + vexRT[Ch4])/2;  // (y + x)/2
		motor[LEFT_TOP] = (vexRT[Ch3] - vexRT[Ch4])/2;  // (y - x)/2

		motor[RIGHT_BOTTOM] = (vexRT[Ch2] + vexRT[Ch1])/2;
		motor[RIGHT_TOP] = (vexRT[Ch2] + vexRT[Ch1])/2;

		// Go top
		if(vexRT[Btn8U])
		{
			// GO UP FOR 45 DEGRESS ADD TIMER!
			motor[ARM_LEFT] = ceil(FULL_SPEED * (3.0/4.0));
			motor[ARM_RIGHT] = ceil(FULL_SPEED * (3.0/4.0));
		}
		// Go bottom
		else if(vexRT[Btn8D])
		{
			// GO DOWN FOR 45 DEGREES ADD TIMER!
			motor[ARM_LEFT] = -1 * floor(FULL_SPEED * (3.0/4.0));
			motor[ARM_RIGHT] = -1 * floor(FULL_SPEED * (3.0/4.0));
		}
		else
		{
			motor[ARM_LEFT] = 0;
			motor[ARM_RIGHT] = 0;
		}

		if(vexRT[Btn6U] || vexRT[Btn6D])
		{
			motor[LAUNCHER] = 127;
		}
		else
		{
			motor[LAUNCHER] = 0;
		}

		if(vexRT[Btn5U])
		{
			motor[ELEVATOR] = ceil(FULL_SPEED * (3.0/4.0));
		}
		else if(vexRT[Btn5D])
		{
				motor[ELEVATOR] = -1 * floor(FULL_SPEED * (3.0/4.0));
		}
		else
		{
			motor[ELEVATOR] = 0;
		}

		// Kill button
		if(vexRT[Btn7U])
		{
			KillSwitch();
		}

	}
}

task autonomous()
{
	autonRunning = false;
}

#ifndef COMPETITION
task main()
{
	startTask(usercontrol);
	while(true)
	{
		if(vexRT[Btn7D])
		{
			stopTask(usercontrol);
			startTask(autonomous);
			autonRunning = true;
			while(autonRunning)
			{
				sleep(10);
			}
			startTask(usercontrol);
		}
		sleep(10);
	}
}
#endif
