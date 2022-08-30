sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;

// Pin direction
sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;

//variables
volatile sbit ok at RA0_bit;
volatile sbit num at RA1_bit;
volatile sbit chng at RA2_bit;

volatile char password[4]={0};
volatile char i,j;
volatile char res;

//prototypes
void EEP_wr(char *password);
char compare(char *password);
void enter_pass();
void chng_pass();

void main()
{
     LCD_INIT();
     LCD_CMD(_LCD_CLEAR);
     LCD_CMD(_LCD_CURSOR_OFF);

     TRISA=0xff;
     PORTA=0x00;
     adcon0=0x00;
     adcon1=0x06;
     for (i=0;i<4;i++)
     {
         EEADR=i;
         EEDATA=i+1;
         EECON1=0x04;
         EECON2=0x55;
         EECON2=0xAA;
         EECON1=0x06;
         while(EECON1.WR==1);

     }
        EECON1.WREN=0;
   while(1)
   {
      LCD_OUT(1,1,"ok to enter pass");

      if(ok)
      {
          while(ok);
          enter_pass();
       }

           else if (chng)
              {
                chng_pass();
              }

           }
}
void enter_pass()
{
     LCD_CMD(_LCD_CLEAR);
         LCD_OUT(1,1,"ENTER PASSWORD : ");

         for (j=0;j<4;j++)
         {
             while(!ok)
             {
                  if(num)
                  {
                     while(num);
                     password[j] = password[j]+1;
                     LCD_OUT(2,j,'0'+password[j]);
                  }
             }

           }
           res=compare(password);
              if (res)
                  {   LCD_CMD(_LCD_CLEAR);
                      LCD_OUT(1,1,"WELCOME");
                  }
              else
                  {
                      LCD_CMD(_LCD_CLEAR);
                      LCD_OUT(1,1,"WRONG PASS");
                  }

}
void chng_pass()
{
        LCD_CMD(_LCD_CLEAR);
                LCD_OUT(1,1,"change pass");
                while (chng);
                  for (j=0;j<4;j++)
                      {
                        while(!ok)
                         {
                           if (num)
                               { while(num);
                                  password[j]= password[j] +1;
                                  LCD_OUT(2,j,+'0'+password[j]);
                               }


                         }

                      }
                      EEP_wr(password);
                      delay_ms(100);
                      LCD_CMD(_LCD_CLEAR);
                      LCD_OUT(1,1,"PASS CHANGED");

}
char compare(char *password)
{
   for (i=0x00;i<0x04;i++)
     {
         EEADR=i;
         EECON1=0x01;
         while(EECON1.RD==1);
         if (EEDATA != password[i])
         {
          break;
         }
     }
        if (i>3)
        {
        return 1;
        }
       else
        {
          return 0;
        }
 }
void EEP_wr(char *password)
{

 for (i=0;i<4;i++)
     {
         EEADR=i;
         EEDATA=password[i];
         EECON1=0x04;
         EECON2=0x55;
         EECON2=0xAA;
         EECON1=0x06;
         while(EECON1.WR==1);

     }
     EECON1.WREN=0;
}