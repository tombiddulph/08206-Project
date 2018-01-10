#include "temp_thresh.h"
#include "lcd.h"

#define TEN_INCREMENT   0x01
#define TEN_DECREMENT   0x02
#define UNIT_INCREMENT  0x04
#define UNIT_DECREMENT 0x08
#define SAVE 0x10
#define MAX_TEMP 124
#define MIN_TEMP -54


char threshold[7];;
int threshold_temp_LHS = 0;
int threshold_temp_RHS = 0;
bool quit;


void update_threshold(char choice)
{
    switch(choice)
    {
        case(TEN_INCREMENT):
            if(threshold_temp_LHS == MAX_TEMP)
            {
                threshold_temp_LHS = MIN_TEMP;
                
            }
            else
            {
                threshold_temp_LHS++;
            }
            break;
        case (TEN_DECREMENT):
            if(threshold_temp_LHS == MIN_TEMP)
            {
                threshold_temp_LHS = MAX_TEMP;
            }
            else
            {
                threshold_temp_LHS--;
            }
            break;
        case (UNIT_INCREMENT):
            if(threshold_temp_RHS == 99)
            {
                threshold_temp_RHS = 0;
                
                if(threshold_temp_LHS == MAX_TEMP)
                {
                    threshold_temp_LHS = MIN_TEMP;
                }
                else
                {
                    threshold_temp_LHS++;
                }
            }
            else
            {
                threshold_temp_RHS++;
            }
            break;
        case (UNIT_DECREMENT):
            if(threshold_temp_RHS == 0)
            {
                threshold_temp_RHS = 99;
                
                if(threshold_temp_LHS == MIN_TEMP)
                {
                    threshold_temp_LHS = MAX_TEMP;
                }
                else
                {
                    threshold_temp_LHS--;
                }
            }
            else
            {
                threshold_temp_RHS--;
            }     
        break;
        
        case (SAVE):
        quit = true;
        break;
    }
    
}

void tempThreshLoop()
{
    quit = false;
    clear_lines();
    while(1)
    {
        Write_line("Thresh:", 0);
        char buf[16];
        sprintf(buf, "%03d.%02d%cC", threshold_temp_LHS, threshold_temp_RHS, 248);
        Write_line(buf, 1);
        
        char  escape  = ((PORTE & BUTTON_MASK) << 4) | (PORTB & BUTTON_MASK) ;
        char  choice  = (PORTB & BUTTON_MASK);
        
        char combined = (choice | escape);
        updateVariables();
         
        if(single_key_pressed(escape))
        {
            update_threshold(escape);
           
            
            if(quit)
            {
                clear_lines();
                
                char buf[16];
                sprintf(buf ,"set to: %03d.%02d", threshold_temp_LHS, threshold_temp_RHS );
                
                sprintf(threshold ,"%d.%d", threshold_temp_LHS, threshold_temp_RHS );
                
                Write_line("Thresh", 0);
                Write_line(buf, 1);
                Write_line("Press a button", 2);
                Write_line("to continue", 3);
                        
                while ((!(PORTB & BUTTON_MASK)) && (!(PORTE & BUTTON_MASK)))
                {
                    /* do nothing */
                }
                
                break;
            }
        }
    }   
}