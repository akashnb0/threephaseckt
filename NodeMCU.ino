#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



#define BLYNK_TEMPLATE_ID "TMPL3nsTBLq-P"
#define BLYNK_TEMPLATE_NAME "Three Phase Fault analysis"
#define BLYNK_AUTH_TOKEN "2yROGCdzVTYDjyd-TH6Jdbb47f_MNIqK"

char auth[] = BLYNK_AUTH_TOKEN;


char ssid[] = "IOT";
char pass[] = "123456789";







unsigned int m=0,act=0,val,val1,val2,val3,val4;

String inputString = ""; 
unsigned char a[200];

int h,t;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  
}


void loop() {
Serial.print("val ; ");
Serial.println(val);
Serial.print("val1 ; ");
Serial.println(val1);
Serial.print("val2 ; ");
Serial.println(val2);
Serial.print("val3 ; ");
Serial.println(val3);
Serial.print("val4 ; ");
Serial.println(val4);

    delay(3000);
  
  if( val==0)
  {
    Serial.print("R PHASE DOWN");
     Blynk.virtualWrite(V4,"R PHASE DISCONNECTED!");
   }
   else if (val1==0)
   {
   Serial.print("Y PHASE OK");
    Blynk.virtualWrite(V4,"Y PHASE DISCONNECTED!");
   }
    else if (val2==0)
   {
   Serial.print("B PHASE OK");
    Blynk.virtualWrite(V4,"B PHASE DISCONNECTED!");
   }
    else if (val4==0)
   {
   Serial.print(" OK ");
    Blynk.virtualWrite(V4,"EARTH FAULT");
   }
   else 
   {
     Blynk.virtualWrite(V4,"                       ");
   }
   

  while(Serial.available())
    {
        char data;
        data=Serial.read();
  
        a[m]=data;
          if(a[0] == '*')
          {
            if(m<=15)
            {m++;}
          }
      }
      if(m > 1)
      {
        val = (a[1]-0x30)*100 + (a[2]-0x30)*10  + (a[3] - 0x30);//CUURENT
        val1 = (a[4]-0x30)*100 + (a[5]-0x30)*10  + (a[6] - 0x30);//CUURENT
         val2 = (a[7]-0x30)*100 + (a[8]-0x30)*10  + (a[9] - 0x30);//CUURENT
        val3 = (a[10]-0x30)*100 + (a[11]-0x30)*10  + (a[12] - 0x30);//CUURENT
         val4 = (a[13]-0x30)*100 + (a[14]-0x30)*10  + (a[15] - 0x30);//CUURENT
    
        m=0;
      }


      Blynk.virtualWrite(V0,val);

      Blynk.virtualWrite(V1,val1);

       Blynk.virtualWrite(V2,val2);

      Blynk.virtualWrite(V3,val3);



}
