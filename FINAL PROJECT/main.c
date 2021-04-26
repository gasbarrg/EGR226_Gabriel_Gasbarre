/*=============================================================================
 |   Assignment:  Final Project
 |       Author:  Gabriel Gasbarre
 |
 |       Course:  EGR 226
 |   Instructor:  Prof. Ekin
 |
 |  Description:  LCD and Keypad integrated control system that accepts
 | user input to control multiple electronic components, such as LED’s, a servo, and a DC motor.
 |
 |
 *===========================================================================*/
#include "msp.h"
#include "stdio.h"
#include "SysTick_Library.h"
#include "LCD_Library.h"
#include "Keypad_Library.h"
#include "Motor_Library.h"
#include "LED_Library.h"
#include "Arm_Library.h"


    //********PINS********//
    //********LCD*********//
    // P5.7 -> LCD PWM Brightness controller (OUTPUT)    -- TimerA through transistor
    // P6.0 -> LCD ADC Brightness Controller (INPUT)     -- Potetiometer
    // P4.3 -> LCD D4
    // P4.4 -> LCD D5
    // P4.5 -> LCD D6
    // P4.6 -> LCD D7
    // P4.2 -> LCD E
    // P4.1 -> LCD RW
    // P4.0 -> LCD RS

    //******SERVOS******//
    //P2.4- P2.7 = MG902S (PWM)
    //******CLAW BUTTON****//
    //P3.6 pull up resistor
    //P6.5 RED LED
    //P6.4 GREEN LED

    //**POTENTIOMETERS**//
    //Arm Servo Controllers: P5.0, P5.4, P5.5 (ADC)

    //*****RGB LEDs*****//
    //P7.4 -    (PWM) TA1.4
    //P7.5 -    (PWM) TA1.3
    //P7.6 -    (PWM) TA1.2
    //P1.6 -    LED TOGGLE (pull up)
    //*****DC MOTOR*****//
    //P8.2 = TA3.2
    //P1.7  E STOP (pull up)
    //******KEYPAD******//
    //Rows:
        //P5.6, P6.6, P6.7 ,P2.3
    //Columns
        //P5.1, P3.5, P3.7

    //*******GLOBAL VARS*******//


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer


	//*******RUN INITIALIZATION FUNCTIONS*********//
	SysTickInit_NoInterrupts();
	lcdInit();
	Keypad_Init();
	Motor_TA_Init();
	Timer32_Init();
	LCDbacklight_Init();
	Potentiometer_Init();
	LED_Init();
	Servo_Init();
	Button_Init();
 lcdWriteCmd(DISPLAY_100);                              //Turn off cursor
	//********INTERRUPT VECTORS********//
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);           //ADC14
    NVIC->ISER[0] = 1 << ( (T32_INT1_IRQn)  & 31);      //Timer32
    NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);           // Enable Port 1 interrupt on the NVIC
    NVIC->ISER[1] = 1 << ((PORT3_IRQn) & 31);           // Enable Port 3 interrupt on the NVIC
    __enable_irq();




	while(1){
	        //********Main Menu*******//
                prntMenu();                         //Print Main Menu
                KeypadWaitUntilHigh();              //Wait for user input
                    //1.) Door/Arm
                    if (Keypad_Read() == 1 )
                    {
                        ArmMenu();                              //Print LCD Arm Menu
                        KeypadWaitUntilLow();                   //Wair for end of keypad input
                        while (Keypad_Read() != 10)             //Enter Arm loop (Exit on * press)
                        {
                            //Claw on Pin interrupt - no code needed here
                            UpdateArmPos();                     //Read ADC values and Update TimerA
                        }
                    }


                    //2.) Motor
                    if (Keypad_Read() == 2 )
                    {
                        int speed=0;                            //Motor Speed Variable
                        BeltMenu();                             //Print Belt Menu
                        KeypadWaitUntilLow();                   //Wair for end of keypad input
                        KeypadWaitUntilHigh();                  //Wait for user input
                            while (Keypad_Read() != 10)         //* = Exit command
                            {
                                speed = Keypad_Read();          //Motor Speed Variable
                                Motor_TA(speed);                //enter speed 0-9 for motor
                                if (speed == 11)
                                    {
                                        lcdSetText("Speed: ERR  ",0 ,2 );       //Error message if user presses "#"
                                    }
                                else
                                    {
                                    //Print Entered Speed
                                    lcdSetText("Speed:     ",0 ,2 );
                                    lcdSetInt(speed, 8, 2);
                                    }
                                KeypadWaitUntilLow();                   //Wair for end of keypad input
                                KeypadWaitUntilHigh();                  //Wait for user input
                            }
5.7
                    }


                //3.) Lights
                    if (Keypad_Read() == 3 )
                        {
                        int select;                             //LED Selection Variable
                        lcdClear();                             //Clear LCD
                        prntLEDMenu();                          //Print LED Menu
                        KeypadWaitUntilLow();                   //Wair for end of keypad input
                        KeypadWaitUntilHigh();                  //Wait for user input
                        while (Keypad_Read() != 10)             //Enter LED menu Loop
                        {
                             select = Keypad_Read();            //LED Select Variable
                             KeypadWaitUntilLow();              //Wair for end of keypad input
                             if (select == 1)                   //RED LED LOOP
                                 {
                                     prntLEDMenu();
                                     RedLEDMenu();                  //Selects Red, Prints Duty Cycle, and will remove extra numbers if a smaller number is printed
                                 }
                             else if (select == 2)
                                 {
                                     prntLEDMenu();
                                     GreenLEDMenu();                //Selects Green, Prints Duty Cycle, and will remove extra numbers if a smaller number is printed
                                 }
                             else if (select == 3)
                                 {
                                     prntLEDMenu();
                                     BlueLEDMenu();                 //Selects Blue, Prints Duty Cycle, and will remove extra numbers if a smaller number is printed
                                 }
                             else
                                 prntLEDMenu();

                             KeypadWaitUntilHigh();                  //Wait for user input
                          }
                        }
	}
}
