#include<stdio.h>
#include<stdlib.h>

#define WITH_ENGINE_TEMP_CONTROLLER 0

typedef enum {Quit , Turn_Off , Turn_On}Car ;
typedef enum {Ac_OFF , Ac_ON}Ac ;
typedef enum {E_OFF , E_ON}Engine_Control ;

// Function Prototypes:
void Traffic_LightSet(int *sp) ;
void Room_Temp(Ac *Ac , int *R) ;
void Engine_Temp(Engine_Control *Eng , int *E) ;
void TurnOFF(Car *c) ;
void Display(Car c , Ac Ac , int sp , int R , Engine_Control Eng , int E );


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);

	// Initialization:
	int Speed = 20 , R_Temperature = 25 , E_Temperature = 90 , Set_Menu = 0 ;
	Car Condition = Quit ;
	Ac Ac_Con = Ac_OFF ;
	Engine_Control Eng_Control = E_OFF;
	int Flag = 0 ;

	// Code:
	printf("Please Choose your condition: Quit = 0 , Turn off = 1 , turn on = 2\n");
	scanf("%d" , &Condition) ;

	while(1)
	{
		switch(Condition) // Switch case to chose the Right State
		{
		case Quit:
			printf("Close The Program") ;
			return 0 ;
		case Turn_Off:
			TurnOFF(&Condition);
			break ;
		case Turn_On:
			Condition = Turn_On ;
			break;
		}

		while(Condition == Turn_On) // Check that car state is on
		{
			printf("\nSensors set menu\n");
			printf("1.Turn off the engine\n");
			printf("2.Set the traffic light color\n");
			printf("3.Set the room temperature (Temperature Sensor)\n");
#if WITH_ENGINE_TEMP_CONTROLLER
			printf("4.Set the engine temperature (Engine Temperature Sensor)\n");
#endif
			scanf("%d" , &Set_Menu) ;

			switch(Set_Menu)
			{
			case 1 :
				TurnOFF(&Condition);
				Flag = 0 ;
				break ;
			case 2 :
				Traffic_LightSet(&Speed) ;
				Flag = 1 ;
				break ;
			case 3 :
				Room_Temp(&Ac_Con , &R_Temperature);
				Flag = 1 ;
				break ;
#if WITH_ENGINE_TEMP_CONTROLLER
			case 4 :
				Engine_Temp(&Eng_Control , &E_Temperature);
				Flag = 1 ;
				break ;
#endif
			}

			if(Flag == 1) // Never Enter here if Engine is Turn off
			{
				if(Speed == 30)
				{
					if(Ac_Con == Ac_OFF)
					{
						Ac_Con = Ac_ON ;
						R_Temperature = (R_Temperature*(5/4)) + 1 ;
					}
#if WITH_ENGINE_TEMP_CONTROLLER
					if(Eng_Control == E_OFF)
					{
						Eng_Control = E_ON ;
						E_Temperature = (E_Temperature*(5/4)) + 1 ;
					}
#endif
				}

				Display(Condition,Ac_Con,Speed,R_Temperature,Eng_Control,E_Temperature);
			}
		}
	}
}

void Traffic_LightSet(int *sp) // Set Traffic Light
{
	char Traffic_Light ;

	printf("\nSet the traffic light color\n");
	scanf(" %c" , &Traffic_Light) ;

	switch(Traffic_Light)
	{
	case 'g':
		*sp = 100 ;
		break ;
	case 'o' :
		*sp = 30 ;
		break ;
	case 'r' :
		*sp = 0 ;
		break ;
	default:
		break;
	}
}

void Room_Temp(Ac *Ac , int *R) // Set Room Temperature
{
	printf("\nSet the room temperature (Temperature Sensor)\n");
	scanf("%d" , R) ;
	if(*R < 10)
	{
		*Ac = Ac_ON ;
		*R = 20 ;
	}
	else if(*R > 30)
	{
		*Ac = Ac_ON ;
		*R = 20 ;
	}
	else
	{
		*Ac = Ac_OFF ;
	}

}

void Engine_Temp(Engine_Control *Eng , int *E)  // Set Engine Temperature
{
	printf("\nSet the engine temperature (Engine Temperature Sensor)\n");
	scanf("%d" , E) ;
	if(*E < 100)
	{
		*Eng = E_ON ;
		*E = 125 ;
	}
	else if(*E > 150)
	{
		*Eng = E_ON ;
		*E = 125 ;
	}
	else
	{
		*Eng = E_OFF ;
	}
}

void TurnOFF(Car *c)  // Turn off State
{
	printf("Please Choose your condition: Quit = 0 , Turn off = 1 , turn on = 2\n");
	scanf("%d" , c) ;
}

void Display(Car c , Ac Ac , int sp , int R , Engine_Control Eng , int E ) // Display the Data
{
	if(c == Turn_On)
	{
		printf("\nEngine State: ON\n") ;
	}
	else
	{
		printf("Engine State: OFF\n") ;
	}

	if(Ac == Ac_ON)
	{
		printf("AC: ON\n") ;
	}
	else
	{
		printf("AC: OFF\n") ;
	}

	printf("Vehicle Speed: %d Km/hr\n" , sp) ;
	printf("Room Temperature: %d c\n" , R) ;

#if WITH_ENGINE_TEMP_CONTROLLER
	printf("Engine Temperature: %d c\n" , E) ;

	if(Eng == E_ON)
	{
		printf("Engine Temperature Control: ON\n") ;
	}
	else
	{
		printf("Engine Temperature Control: OFF\n") ;
	}
#endif
}
