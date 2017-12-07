//experiment purpose: familiar how to use clock chip DS1302       
//first set time and date:second(08),minute(58),hour(05),day(13),month(01),year(55)   
//six LED display time and date,default display time,differentiate hour and min,min and second with decimal dot 
//when press RB1 not relax,display switch to date.     
//hardware request: SW S9,S5,S6 all ON,S1 the seventh bit ON,the other bits OFF,the other SWS OFF.




#include<pic.h>                        //include MCU head file     
//__PROG_CONFIG(0x1832);       
//__CONFIG( _DEBUG_OFF&_CP_ALL&_WRT_HALF&_CPD_ON&_LVP_OFF&_BODEN_OFF&_PWRTE_ON&_WDT_OFF&_HS_OSC);
__CONFIG( FOSC_HS & WDTE_OFF & PWRTE_ON & BOREN_OFF & LVP_OFF );

#define RTC_IO   RB4                      //1302I_O           
#define RTC_CLK  RB0                      //1302 clock        
#define RTC_RST  RB5                      //1302 enable bit   

#define RTC_CONTROL_WRITE   0x8E
#define RTC_LOW_MASK        0x0F
#define RTC_HIGH_MASK       0xF0
//unsigned char time_rx;
unsigned char time_rx @ 0x30;        //define receive reg.
static volatile bit time_rx7   @ (unsigned)&time_rx*8+7;   //receive reg highest.//defined name time_rx7 for most significant bit (bit 7) for variable time_rx. After symbol @ there are calculation for the that bit address: &time_rx give us the address of variable time_rx, after multiplying with 8 we have the bit address of bit 0 of time_rx, and adding 7 give us the bit address of bit 7 of time_rx. Type casting (unsigned) used for avoiding signed result of multiplying operation.
//static volatile bit temp0     @ (unsigned)&temp*8+0;

void Port_init_rtc();                      //port initilize subroutine.
void ds1302_init();                    //DS1302 initilize subroutine.
void Set_time_rtc();                       //set time subroutine.
void Get_time_rtc();                       //get time subroutine.
void Display_7_seg_rtc();                        //display subroutine.
void write_time_rtc(unsigned char time_tx);    //write one byte subroutine.
unsigned char  read_time_rtc();          //read one byte subroutine.
void delay_rtc();                          //delay subroutine.
//define the time: sec,min,hour,day,month,week,year,control word.
const char rtc_table[]={0x00,0x58,0x12,0x81,0x3,0x06,0x06,0x00};
//define the read time and date save table.
char rtc_table1[7];
//define the display code for display 0-9
const char rtc_7_seg_display_table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90}; 

//----------------------------------------------
//main routine.
void main()
  {
    
   // time_rx7 @ (unsigned)&time_rx*8+7;
     Port_init_rtc();                     //port initilize.
     ds1302_init();                   //DS1302 initilize.
     Set_time_rtc();                      //set time
     while(1)
        {
          Get_time_rtc();                 
          Display_7_seg_rtc();                  
        }
  }

//---------------------------------------------
//DS1302 initilize.
void ds1302_init()
  {
   RTC_CLK=0;                            //pull low clock
   RTC_RST =0;                            //reset DS1302
   RTC_RST=1;                             //enable DS1302
   write_time_rtc(RTC_CONTROL_WRITE);                //send control command
   write_time_rtc(0);                   //enable write DS1302
   RTC_RST=0;                             //reset
  }

//---------------------------------------------
//set time.
void Set_time_rtc()
  {
   int i;                             //define the loop counter.
   RTC_RST=1;                             //enable DS1302
   write_time_rtc(0xbe);                //
   for(i=0;i<8;i++)                   //continue to write 8 bytes.
     {
       write_time_rtc(rtc_table[i]);        //write one byte
     }
   RTC_RST=0;                             //reset
   }

//---------------------------------------------
//get time.
void Get_time_rtc()
 {
   int i;                             //set loop counter.
   RTC_RST=1;                             //enable DS1302
   write_time_rtc(0xbf);                //
   for(i=0;i<7;i++)                   //continue to read 7 bytes.
     {
        rtc_table1[i] = read_time_rtc();      //
     }
    RTC_RST=0;                            //reset DS1302
 }

//--------------------------------------------
//write one byte
void write_time_rtc(unsigned char time_tx)
 {
    int j;                            //set the loop counter.
    for(j=0;j<8;j++)                  //continue to write 8bit
      {
        RTC_IO=0;                        //
        RTC_CLK=0;                       //pull low clk
        if(time_tx&0x01)              //judge the send bit is 0 or 1.
          {
            RTC_IO=1;                    //is 1
          }
        time_tx=time_tx>>1;           //rotate right 1 bit.
        RTC_CLK=1;                       //pull high clk
       }
      RTC_CLK=0;                         //finished 1 byte,pull low clk
  }

//---------------------------------------------
//read one byte.
unsigned char read_time_rtc()
 {
   int j;                            //set the loop counter.  
   TRISB4=1;                         //continue to write 8bit 
   for(j=0;j<8;j++)                  
      {
        RTC_CLK=0;                       //pull low clk                   
        time_rx=time_rx>>1;           //judge the send bit is 0 or 1.  
        time_rx7=RTC_IO;                //put the received bit into the reg's highest.
       RTC_CLK=1;                       //pull high clk                 
      }                                                              
    TRISB4=0;                        //finished 1 byte,pull low clk  
    RTC_CLK=0;                          
    return(time_rx);                 
  }

//--------------------------------------------
//pin define func
void Port_init_rtc()
  {
    TRISA=0x00;                     //a port all output
    TRISD=0X00;                     //d port all output
    ADCON1=0X06;                    //a port all i/o
    TRISB=0X02;                     //rb1 input, others output
  //  OPTION=0X00;                    //open b port internal pull high.
    PORTA=0XFF;               
    PORTD=0XFF;                     //clear all display
   }

//-------------------------------------------
//display
void Display_7_seg_rtc()
   {
     int i;
     char *p;
     
     p = RB1 == 0 ? rtc_table1 : rtc_table1 + 2;//define table variable.
//     if(RB1==0)                     //judge rb1.
//       {
//          rtc_table1[0]=rtc_table1[3];     
//          rtc_table1[1]=rtc_table1[4];
//          rtc_table1[2]=rtc_table1[6];
//       }
     
     
     
     i = *p & RTC_LOW_MASK;             //sec's low.
     PORTD=rtc_7_seg_display_table[i];              //send to port d.
     PORTA=0x1f;                   //light on sec's low.
     delay_rtc();                      //delay some times.
     i = *p & RTC_HIGH_MASK;             //sec's high
     i = i>>4;                       //rotate right for 4 bits.
     PORTD=rtc_7_seg_display_table[i];              //send to port d.    
     PORTA=0x2f;                   //light on sec's high.
     delay_rtc();                      //delay some times.  
     p++;
     
     i = *p & RTC_LOW_MASK;             //min's low.                 
     PORTD=rtc_7_seg_display_table[i]&0x7f;         //send to port d.            
     PORTA=0x37;                   //light on min's low.        
     delay_rtc();                      //delay some times.          
     i = *p & RTC_HIGH_MASK;             //min's high                 
     i = i>>4;                       //rotate right for 4 bits.   
     PORTD=rtc_7_seg_display_table[i];              //send to port d.            
     PORTA=0x3b;                   //light on min's high.       
     delay_rtc();                      //delay some times.          

     p++;
     
     i = *p & RTC_LOW_MASK;             //hour's low.                 
     PORTD=rtc_7_seg_display_table[i]&0x7f;         //send to port d.            
     PORTA=0x3d;                   //light on hour's low.        
     delay_rtc();                      //delay some times.          
     i = *p & RTC_HIGH_MASK;             //hour's high                 
     i = i>>4;                       //rotate right for 4 bits.   
     PORTD=rtc_7_seg_display_table[i];              //send to port d.            
     PORTA=0x3e;                   //light on hour's high.       
     delay_rtc();                      //delay some times.          
   }

//------------------------------------------------------------------
//delay
void  delay_rtc()              //
    {
     int i;                 //define variable
     for(i=0x64;i--;);     //delay
    }
