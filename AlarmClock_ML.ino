#include<DS3231.h>
#include<LiquidCrystal.h>
DS3231 rtc(A4,A5);
const int rs=9, en = 8, d4 = 7, d5=6, d6=5, d7=4;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
Time t;
Time bedtime;

int parse_hours[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23};
int nightLightRange[10];
int th,tm,bh,bm;
int sensorValue = 0;
int flag = 0;
int bedtimeIndex;


const int setButton = 2, changeButton = 3, sensorPin = A3;
boolean setButtonState, changeButtonState;



void setup(){
  Serial.begin(115200);
  rtc.begin();
  lcd.begin(16,2);
  pinMode(setButton,INPUT);
  pinMode(changeButton,INPUT);
  bedtime.hour = 21;
  bedtime.min = 0;
  rtc.setTime(18,59,30);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
}

void loop(){

  //------------------------------SHOW TIME----------------------------------
  t = rtc.getTime();  
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.setCursor(6,0);
  lcd.print(t.hour);
  if (t.hour<10)
  lcd.print(' ');
  lcd.setCursor(8,0);
  lcd.print(" :");
  lcd.setCursor(10,0);
  lcd.print(t.min);
  if (t.min<10)
  lcd.print(' ');
  lcd.setCursor(12,0);
  lcd.print(" :");
  lcd.setCursor(14,0);
  lcd.print(t.sec);
  if (t.sec<10)
  lcd.print(' ');
  
  delay(1000);
  
  //Show bedtime
  lcd.setCursor(0,1);
  lcd.print("Bedtime: ");
  lcd.setCursor(9,1);
  lcd.print(bedtime.hour);
  lcd.setCursor(12,1);
  lcd.print(":");
  lcd.setCursor(13,1);
  lcd.print(bedtime.min);
  if (bedtime.min<10)
  lcd.print(' ');

  setBedtime();
  
  //-------------------------------MANUALLY CHANGING TIME/BEDTIME------------------------------------------

  setButtonState = digitalRead(setButton);
  if (setButtonState==1)
    setDigitalClock();

  setButtonState = 0;

  flag = 1;
  for (int i = 0;i<10;i++){
    if (t.hour == nightLightRange[i]){
      flag = 0;
      break;
    }
  }
  if (flag == 0)
    lightingNight();
  else
    checkSensor();

  
}


void checkSensor(){
  sensorValue = analogRead(sensorPin);
 if (sensorValue<100)     //when sufficient light in environment, sensor reads >800
  lightingEvening();
 else
  lightingMorning();
}



void setDigitalClock(){

  

  th = t.hour;
  tm = t.min;
  bh = bedtime.hour;
  bm = bedtime.min;

  //-----------------TIME: HOURS----------------------------------
  setButtonState = 0;
  delay(1000);
  while(1){
      //lcd.print("X");
      lcd.setCursor(8,0);
      lcd.blink();
      changeButtonState = digitalRead(changeButton);
      if (changeButtonState == 1){
        changeButtonState =0;
        delay(400);  
        th++;
        if (th==24){
          th = 0;
          lcd.setCursor(6,0);
          lcd.print(" ");
        }
        lcd.setCursor(6,0);
        lcd.print(th);
        if (th<10){
          lcd.setCursor(7,0);
          lcd.print(" ");
        }
        
      }
      changeButtonState = 0;
      setButtonState = 0;
      setButtonState = digitalRead(setButton);
      if ( setButtonState ==1){
        break;
      }
               
  }
  lcd.noBlink();

  
  lcd.setCursor(13,1);


  //------------------TIME: MINUTES----------------------------
  setButtonState = 0;
  delay(1000);
  while(1){
      //lcd.print("X");
      lcd.setCursor(12,0);
      lcd.blink();
      changeButtonState = digitalRead(changeButton);
      if (changeButtonState == 1){
        lcd.blink();
        changeButtonState =0;
        delay(400);  
        tm++;
        if (tm==60){
          tm = 0;
          lcd.setCursor(10,0);
          lcd.print(" ");
        }
        lcd.setCursor(10,0);
        lcd.print(tm);
        if (tm<10){
          lcd.setCursor(11,0);
          lcd.print(" ");
        }
        
        
      }
      changeButtonState = 0;
      setButtonState = 0;
      setButtonState = digitalRead(setButton);
      if ( setButtonState ==1){
        break;
      }
               
  }
  lcd.noBlink();

  
  lcd.setCursor(13,1);
  setButtonState = 0;


//----------------BEDTIME: HOURS------------------------
  
setButtonState = 0;
  delay(1000);
  while(1){
      //lcd.print("X");
      lcd.setCursor(11,1);
      lcd.blink();
      changeButtonState = digitalRead(changeButton);
      if (changeButtonState == 1){
        lcd.blink();
        changeButtonState =0;
        delay(400);  
        bh++;
        if (bh==24){
          bh = 0;
          lcd.setCursor(9,1);
          lcd.print(" ");
        }
        
//        if (bedtime.hour<10)
//          lcd.print(' ');
        lcd.setCursor(9,1);
        lcd.print(bh);
        
        if (bh<10){
          lcd.setCursor(10,1);
          lcd.print(" ");
        }
      }
      changeButtonState = 0;
      setButtonState = 0;
      setButtonState = digitalRead(setButton);
      if ( setButtonState ==1){
        break;
      }
               
  }
  lcd.noBlink();

  
  bedtime.hour = bh;


 //--------------BEDTIME: MINUTES----------------------
setButtonState = 0;
  delay(1000);
  while(1){
      //lcd.print("X");
      lcd.setCursor(15,1);
      lcd.blink();
      changeButtonState = digitalRead(changeButton);
      if (changeButtonState == 1){
        lcd.blink();
        changeButtonState =0;
        delay(400);  
        bm++;
        if (bm==60){
          bm = 0;
          lcd.setCursor(13,1);
          lcd.print("  ");
        }
        lcd.setCursor(13,1);
        lcd.print(bm);
        if (bm<10)
        lcd.print("  ");

        if (bm<10){
          lcd.setCursor(14,1);
          lcd.print(" ");
        }
        
      }
      changeButtonState = 0;
      setButtonState = 0;
      setButtonState = digitalRead(setButton);
      if ( setButtonState ==1){
        break;
      }
               
  }
  lcd.noBlink();

  bedtime.min = bm;


  //-------------SET ALL---------------------------

  rtc.setTime(th,tm,0);
  setBedtime();

}

void setBedtime(){
  
    bedtimeIndex=0;
    while(1){
    if (bedtime.hour == parse_hours[bedtimeIndex])
      break;
    bedtimeIndex++;
    }
    int j =0;
    for(int i= bedtimeIndex-2; i<bedtimeIndex+8;i++){
      nightLightRange[j] = parse_hours[i];
      j++;
    }
    
        
}

void lightingNight(){
  
      
      //LED2
      digitalWrite(10,LOW);    //red pin of rgb led
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);

      //LED1
      digitalWrite(A2,LOW);    //red pin of rgb led
      digitalWrite(A1,HIGH);
      digitalWrite(A0,HIGH);

      
    
 }


void lightingMorning(){

        //LED2
      digitalWrite(10,HIGH);    //red pin of rgb led
      digitalWrite(11,HIGH);
      digitalWrite(12,HIGH);

      //LED1
      digitalWrite(A2,HIGH);    //red pin of rgb led
      digitalWrite(A1,HIGH);
      digitalWrite(A0,HIGH);
  
}

void lightingEvening(){

  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  
}
