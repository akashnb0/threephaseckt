#include <EveryTimer.h>
#define PERIOD_MS 1000

EveryTimer timer;
bool active = true;

#include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



#define rphase A0
#define yphase A1
#define bphase A2
#define current A3

#define relay1 2
#define alert 3
const int numMeasurements = 100;  // Number of measurements for averaging
  
int sec;
int rvalue,yvalue,bvalue,currentvalue,act=0,alert1;

int phasestate;
void setup()
{
  // Debug console
  Serial.begin(9600);
   timer.Every(PERIOD_MS, action);

pinMode(current,INPUT);
pinMode(alert,INPUT_PULLUP);
pinMode(rphase,INPUT);
pinMode(yphase,INPUT);
pinMode(bphase,INPUT);
pinMode(relay1,OUTPUT);
digitalWrite(relay1,LOW);

  lcd.begin(16, 2);              //Init the LCD           //Activate backlight     
  lcd.home();  
  lcd.setCursor(0,0);
  lcd.print("THREE PHASE ");
  lcd.setCursor(0,1);
  lcd.print("POWER FAILURE");
  lcd.clear();
  

 
}

void loop()
{

  timer.Update();
  Serial.print("SEc :");
  Serial.println(sec);
  
  rvalue=analogRead(rphase);
  Serial.print("R:");
  Serial.println(rvalue);
  
  lcd.setCursor(0,0);
  lcd.print("R:");
  lcd.print(rvalue);
  
  yvalue=analogRead(yphase);
  Serial.print("Y:");
  Serial.println(yvalue);
  lcd.setCursor(6,0);
  lcd.print("Y:");
  lcd.print(yvalue);
  
  bvalue=analogRead(bphase);
  Serial.print("B:");
  Serial.println(bvalue);
  lcd.setCursor(0,1);
  lcd.print("B:");
  lcd.print(bvalue);
  
  currentvalue=analogRead(current);
  Serial.print("C:");
  Serial.print(currentvalue);
  lcd.setCursor(6,1);
  lcd.print("C:");
  lcd.print(currentvalue);

 alert1=digitalRead(alert);
 Serial.print("G:");
 Serial.println(alert1);
 if (alert1==0)
{
  Serial.print("Earth falut");
  lcd.setCursor(0,0);
  lcd.print("EARTH FAULT");
   lcd.setCursor(0,1);
  lcd.print("                 ");
  delay(3000);

}
 
  if((rvalue<100 || yvalue<100|| bvalue<100))
    {
      phasestate=0;
      digitalWrite(relay1,HIGH);
      
    }
  else{phasestate=1;}

//float measurements[numMeasurements];
//  
//  // Collect 100 measurements
//  for (int i = 0; i < numMeasurements; i++) {
//    measurements[i] = analogRead(current); // Convert ADC value to voltage (assuming 5V Arduino)
//    delay(10);  // Add a small delay to stabilize readings
//  }
//
//  // Calculate the average
//
//  for (int i = 0; i < numMeasurements; i++) {
//    rvalue += measurements[i];
//  }
//  rvalue /= numMeasurements;
//rvalue=rvalue*3;
//  // Print the average value
//  Serial.print("The average current value over ");
//  Serial.print(numMeasurements);
//  Serial.print(" measurements is: ");
//  Serial.println(rvalue);


      
if( yvalue>200 && bvalue>200 && rvalue>200 )
  {
  Serial.println("All phase on and iot on");
  digitalWrite(relay1,LOW);
  }
  else
  {
  digitalWrite(relay1,HIGH);
  }
if( yvalue<200)
{
   Serial.println("Y PHASE OFF ");
  digitalWrite(relay1,HIGH);
 
}
else if(bvalue<200)
{
   Serial.println("B PHASE OFF ");
  digitalWrite(relay1,HIGH);
}

else if(rvalue<200)
{
   Serial.println("R PHASE OFF ");
  digitalWrite(relay1,HIGH);
}
  
else if(yvalue<200 && bvalue<200 && rvalue<200)
  {
   Serial.println("ALL LOAD DOWN");
  digitalWrite(relay1,HIGH);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("ALL LOAD DOWN");


  }

senddata();
  delay(1000);

}

void senddata()
  {
    Serial.print('*');

    if(rvalue<=9){Serial.print("00"); Serial.print(rvalue);}
    else if(rvalue<=99){Serial.print("0"); Serial.print(rvalue);}
    else if(rvalue<=999){ Serial.print(rvalue);}

    if(yvalue<=9){Serial.print("00"); Serial.print(yvalue);}
    else if(yvalue<=99){Serial.print("0"); Serial.print(yvalue);}
    else if(yvalue<=999){Serial.print(yvalue);}

    
    if(bvalue<=9){Serial.print("00"); Serial.print(bvalue);}
    else if(bvalue<=99){Serial.print("0"); Serial.print(bvalue);}
    else if(bvalue<=999){Serial.print(bvalue);}

    if(currentvalue<=9){Serial.print("00"); Serial.print(currentvalue);}
    else if(currentvalue<=99){Serial.print("0"); Serial.print(currentvalue);}
    else if(currentvalue<=999){Serial.print(currentvalue);}

        if(alert1<=9){Serial.print("00"); Serial.print(alert1);}
    else if(alert1<=99){Serial.print("0"); Serial.print(alert1);}
    else if(alert1<=999){Serial.print(alert1);}
  }


  void action()
{
  sec++;
}
