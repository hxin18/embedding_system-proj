#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define uchar unsigned char
#define lightPin 4
#define LedPinGreen 2
#define LedPinBlue 3
#define soundPin 0
// Function to initialize of the PWM output for the LED module
void ledInit(void)
{
softPwmCreate(LedPinGreen,0, 100);
softPwmCreate(LedPinBlue, 0, 100);
}

// Function to set the duty ratio of PWM output for the LED module
void ledColorSet(uchar g_val, uchar b_val) 
{
softPwmWrite(LedPinGreen, g_val);
softPwmWrite(LedPinBlue, b_val);
}

int main(void)
{
   int i;
   if(wiringPiSetup() == -1)
      { //when initialize wiring failed, print message to screen
         printf("setup wiringPi failed !");
        return 1; 
       }
      ledInit();

      pinMode(lightPin, INPUT);                                               
      ledColorSet(0x00,0x00); 

    while(1)
    {
        //judge if there is light, if no, continue the process
        if(digitalRead(lightPin)==0)
        {
            while (1)
            {
                delay(10);
                //judge again if there is light, if no, continue the process
                if(digitalRead(lightPin)==0)
                {
                    //judge if there is sound, if yes, actuate the LED module
                    if(digitalRead(soundPin)==1)
                    {
                        ledColorSet(0xff,0xff);
                        printf("light!\n");
                        delay(5000);
                        ledColorSet(0x00,0x00); 
                        break;
                    }
                }
            }
        }
    }
    return 0;
}