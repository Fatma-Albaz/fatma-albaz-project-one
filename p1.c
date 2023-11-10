/*
 * p1.c
 *
 *  Created on: Aug 12, 2023
 *      Author: fatma albaz
 */
/*
 * Global vaariables
 */
#define ON 1
#define OFF 0
#define WITH_ENGINE_CONTROLLER 1
int Engine =OFF;
int AC =OFF;
int VehicleSpeed=0;
float RoomTemp= 35;
int EngineTempController= WITH_ENGINE_CONTROLLER;
float EngineTemp= 90;


#include <stdio.h>
void printAllValues (void);
char EngineOff (char ActionToPerform);
char TurnOnSys(void);
int QuitSys ();


void trarricLightColot();
void RoomTempFunction ();
void EngineTempFunction();


int main (void){
	/*
	 * the variable action to perform is responsible on the choice of the first menu
	 * the variable action on second stage is responsible on the choice in the sensor menu
	 */
	char ActionToPerform, ActionOnSecStage=0;
	int flag=1;
	printf("a. Turn on the vehicle engine \n");
	printf("b. Turn off the vehicle engine \n");
	printf("c. Quit the system\n");
	fflush(stdout);
	scanf(" %c", &ActionToPerform);
	while (flag){
		if (ActionToPerform== 'c'){
			/*
			 * the flag value will be zero thus breaking the while loop and terminating the system
			 */
			flag= QuitSys();
		}
		else if (ActionToPerform== 'b'){
			ActionToPerform= EngineOff(ActionToPerform);
		}
		else if (ActionToPerform=='a'){
			ActionOnSecStage= TurnOnSys();
			switch (ActionOnSecStage){
			case 'a':
				/*
				 * to break looping around ActionOnSecStage and return to
				 * the original variable ActionToPerform
				 */
				ActionToPerform= EngineOff('b');
				break;
			case 'b':
				trarricLightColot();
				break;
			case 'c':
				RoomTempFunction();
				break;
				/*
				 * if the WITH_ENGINE_CONTROLLER =0 then eliminate the engine temp function calling code
				 */
#if WITH_ENGINE_CONTROLLER
			case 'd':
				EngineTempFunction();
				break;
#endif
			}
		}
	}
	return 0;
}

char EngineOff (char ActionToPerform){
	VehicleSpeed=0;
	Engine= OFF;
	while (ActionToPerform== 'b'){
		printf("Turn off vehicle engine \n \n");
		printf("a. Turn on the vehicle engine \n");
		printf("b. Turn off the vehicle engine \n");
		printf("c. Quit the system\n");
		fflush(stdout);
		scanf(" %c", &ActionToPerform);
	}
	return ActionToPerform;
}
int QuitSys (){
	printf("Quit the system");
	return 0;
}
/*
 * funciton to turn on the system
 */
char TurnOnSys(void){
	Engine =ON;
	char ActionOnSecStage;
	printf("Turn on the vehicle engine \n \n");
	fflush(stdout);
	while (1){
		/*
		 * now we are in the sensor menu, so we will take another value from the user to read sensors inputs
		 */
		printf("a. Turn off the engine \n");
		printf("b. Set the traffic light color. \n");
		printf("c. Set the room temperature (Temperature Sensor) \n");
		/*
		 * if the WITH_ENGINE_CONTROLLER =0 then eliminate printing the option of controlling the engine temperature
		 */
#if WITH_ENGINE_CONTROLLER
		printf("d. Set the engine temperature (Engine Temperature Sensor)\n \n");
#endif
		fflush(stdout);
		scanf(" %c", &ActionOnSecStage);
		break;
	}
	return ActionOnSecStage;
}
/*
 * function to control vehicle speed
 */
void trarricLightColot(){
	char color;
	printf("enter the required color: \n \n");
	fflush(stdout);
	scanf(" %c", &color);
	/*
	 * taking the color of the traffic light from user to update the vehicle speed
	 */
	switch (color){
	case 'g':
		VehicleSpeed=100;
		break;
	case 'o':
		VehicleSpeed=30;
		break;
	case 'r':
		VehicleSpeed=0;
		break;
	}
	printAllValues();
}
/*
 * Room temp function
 */

void RoomTempFunction (){
	printf("enter the req temp: \n \n");
	fflush(stdout);
	scanf("%f", &RoomTemp);
	if (RoomTemp>30){
		AC=ON;
		RoomTemp=20;
	}
	else if (RoomTemp<10){
		AC=ON;
		RoomTemp=20;
	}
	else {
		AC=OFF;
	}
	printAllValues();
}
/*
 * function to control engine temp
 */
void EngineTempFunction(){
	printf("enter the engine temp value: \n \n");
	fflush (stdout);
	scanf("%f", &EngineTemp);
	if (EngineTemp<100){
		EngineTemp=125;
		EngineTempController= ON;
	}
	else if (EngineTemp>150){
		EngineTemp=125;
		EngineTempController= ON;
	}
	else {
		EngineTempController= OFF;
	}
	printAllValues();
}
/*
 * function to print all values
 */
void printAllValues (void){
	if (VehicleSpeed==30){
		if (AC== OFF){
			AC=ON;
		}
		RoomTemp= ((float)5/4)*RoomTemp+1;
		/*
		 * eliminating engine temp adjustment if the engine controller is deactivated
		 */
#if WITH_ENGINE_CONTROLLER
		if (EngineTempController== OFF){
			EngineTempController=ON;
		}
		EngineTemp= ((float)5/4)*EngineTemp+1;
#endif
	}
	if (Engine== ON){
		printf("Engine is ON \n");
	}
	else {
		printf("Engine is OFF \n");
	}
	if (AC== ON){
		printf("AC is ON \n");
	}
	else {
		printf("AC is OFF \n");
	}
	printf("Vehicle speed is %d\n",VehicleSpeed);
	printf("Room temp is %f \n", RoomTemp);
	/*
	 * if the WITH_ENGINE_CONTROLLER =0 then eliminate printing any data related to the engine temp control
	 */
#if WITH_ENGINE_CONTROLLER
	if (EngineTempController== ON){
		printf("Engine Temp Controller is ON \n");
	}
	else {
		printf("Engine Temp Controller is OFF \n");
	}
	printf("Engine temp :%f \n", EngineTemp);
#endif
}
