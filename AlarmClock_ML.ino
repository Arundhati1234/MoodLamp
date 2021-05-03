#include<DS3231.h>
#include<LiquidCrystal.h>
DS3231 rtc(A4,A5);
const int rs=9, en = 8, d4 = 7, d5=6, d6=5, d7=4;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
Time t;
Time bedtime;

int th,tm,bh,bm;
int sensorValue = 0;
int flag = 0;
int oldTime;

const int setButton = 2, changeButton = 3, sensorPin = A3;
boolean setButtonState, changeButtonState;

void setup(){
  Serial.begin(115200);
  rtc.begin();
  lcd.begin(16,2);
  pinMode(setButton,INPUT);
  pinMode(changeButton,INPUT);
}

void loop(){

  //------------------------------SHOW TIME----------------------------------
  t = rtc.getTime();  
  lcd.setCursor(0,0);
  lcd.print(t.hour);
  lcd.setCursor(2,0);
  lcd.print(":");
  lcd.setCursor(3,0);
  lcd.print(t.min);
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(t.sec);
  delay(1000);
  
  //Show bedtime
  lcd.setCursor(0,1);
  lcd.print("BT: ");
  bedtime.hour = 12;
  bedtime.min = 00;
  lcd.setCursor(5,1);
  lcd.print(t.hour);
  lcd.setCursor(7,1);
  lcd.print(":");
  lcd.setCursor(8,1);
  lcd.print(t.min);

  //-------------------------------MANUALLY CHANGING TIME/BEDTIME------------------------------------------

  setButtonState = digitalRead(setButton);
  if (setButtonState==1)
    setDigitalClock();

  setButtonState = 0;

  //-------------------------------CONTROL LIGHTS----------------------------------------------------------

 if (((bedtime.hour == 1)&& (t.hour == 23))||((bedtime.hour == 0)&&(t.hour == 22))||((t.hour + 2 == bedtime.hour))){
        lightingNight();        
  }

  if ((oldTime+1) == t.hour){
    flag++;
    oldTime++;
  }

  if (flag>8){
    flag = 0;
    checkSensor();
  }
  
  
}


void checkSensor(){
  sensorValue = analogRead(sensorPin);
 if (sensorValue<800)     //when sufficient light in environment, sensor reads >800
  lightingEvening();
 else
  lightingMorning();
}



void setDigitalClock(){

  //-----------------TIME: HOURS----------------------------------
  setButtonState = 0;
  delay(1000);
  while(1){
      //lcd.print("X");
      changeButtonState = digitalRead(changeButton);
      if (changeButtonState == 1){
        changeButtonState =0;
        delay(500);  
        th++;
        if (th==24){
          th = 0;
          lcd.setCursor(0,0);
          lcd.print("0 ");
        }
        lcd.setCursor(0,0);
        lcd.print(th);
        
      }
      changeButtonState = 0;
      setButtonState = 0;
      setButtonState = digitalRead(setButton);
      if ( setButtonState ==1){
        break;
      }
               
  }

  
  lcd.setCursor(13,1);


  //------------------TIME: MINUTES----------------------------
  setButtonState = 0;
  delay(1000);
  while(1){
      //lcd.print("X");
      changeButtonState = digitalRead(changeButton);
      if (changeButtonState == 1){
        changeButtonState =0;
        delay(500);  
        tm++;
        if (tm==60){
          tm = 0;
          lcd.setCursor(3,0);
          lcd.print("0 ");
        }
        lcd.setCursor(3,0);
        lcd.print(tm);
        
      }
      changeButtonState = 0;
      setButtonState = 0;
      setButtonState = digitalRead(setButton);
      if ( setButtonState ==1){
        break;
      }
               
  }

  
  lcd.setCursor(13,1);
  setButtonState = 0;


//----------------BEDTIME: HOURS------------------------
  
setButtonState = 0;
  delay(1000);
  while(1){
      //lcd.print("X");
      changeButtonState = digitalRead(changeButton);
      if (changeButtonState == 1){
        changeButtonState =0;
        delay(500);  
        bh++;
        if (bh==24){
          bh = 0;
          lcd.setCursor(5,1);
          lcd.print("0 ");
        }
        lcd.setCursor(5,1);
        lcd.print(bh);
        
      }
      changeButtonState = 0;
      setButtonState = 0;
      setButtonState = digitalRead(setButton);
      if ( setButtonState ==1){
        break;
      }
               
  }

  
  lcd.setCursor(13,1);
  setButtonState = 0;


 //--------------BEDTIME: MINUTES----------------------
setButtonState = 0;
  delay(1000);
  while(1){
      //lcd.print("X");
      changeButtonState = digitalRead(changeButton);
      if (changeButtonState == 1){
        changeButtonState =0;
        delay(500);  
        bm++;
        if (bm==60){
          bm = 0;
          lcd.setCursor(8,1);
          lcd.print("0 ");
        }
        lcd.setCursor(8,1);
        lcd.print(bm);
        
      }
      changeButtonState = 0;
      setButtonState = 0;
      setButtonState = digitalRead(setButton);
      if ( setButtonState ==1){
        break;
      }
               
  }

  
  lcd.setCursor(13,1);
  setButtonState = 0;


  //-------------SET ALL---------------------------

  rtc.setTime(th,tm,0);
  bedtime.hour = bh;
  bedtime.min = bm;
  
        
}

void lightingNight(){
  
      
      //LED2
      digitalWrite(10,HIGH);    //red pin of rgb led
      digitalWrite(11,LOW);
      digitalWrite(12,LOW);

      //LED1
      digitalWrite(A2,HIGH);    //red pin of rgb led
      digitalWrite(A1,LOW);
      digitalWrite(A0,LOW);

      oldTime = t.hour;
    
 }


void lightingMorning(){

        //LED2
      digitalWrite(10,LOW);    //red pin of rgb led
      digitalWrite(11,LOW);
      digitalWrite(12,LOW);

      //LED1
      digitalWrite(A2,LOW);    //red pin of rgb led
      digitalWrite(A1,LOW);
      digitalWrite(A0,LOW);
  
}

void lightingEvening(){

  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  
}
