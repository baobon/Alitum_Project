#include <SHT1x.h>
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x3F,16,2);
#define dataPin  3 // Vàng
#define clockPin 4 // Xanh duong
SHT1x sht1x(dataPin, clockPin);
int temp;
float humidity;
#define tang 9
#define giam 8
#define menu 7
#define relay 10
int humset = 70;
int chedo;
int states;
void setup()
{
  Serial.begin(9600);
  pinMode(9, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(10,OUTPUT);
  lcd.init();       //Kh?i d?ng màn hình. B?t d?u cho phép Arduino s? d?ng màn hình
  lcd.backlight();   //B?t dèn n?n
  chedo = 0;
  
}

void getSHT()
{
  temp = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
  lcd.setCursor(0,0);
  lcd.print("T:");
  if(temp > 100 or temp < 0)
  {lcd.print("--");}
  else{lcd.print(temp);}
  lcd.print(char(223));
  lcd.print("C");
  lcd.setCursor(8,0);
  lcd.print("H:");
  if(humidity > 100 or humidity <0)
  {lcd.print("--.--");}
  else{lcd.print(humidity);}
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("HSET:");
  lcd.print(humset);
  lcd.print("%");
  lcd.setCursor(13,1);
  if(digitalRead(relay) == 1)
  {
    lcd.print("ON ");
  }
  if(digitalRead(relay) ==0)
  {
    lcd.print("OFF");
  }
}

void loop()
{ 
  while(true)
  {
    while(chedo == 0) // CHe do auto
    { lcd.setCursor(9,1);
      lcd.print("AU");
      getSHT();
      states =0;
      if(humidity < humset)
      {
         digitalWrite(relay,HIGH);
      }else{
         digitalWrite(relay,LOW);
      }
      // trang thai an nut
      if(digitalRead(tang)==0)//neu nhan nut nhan
      {
        humset = humset+1;
        if(humset > 99)
        {
          humset = 0;
        }
      }
      if(digitalRead(giam)==0)//neu nhan nut nhan
      { 
        humset = humset -1;
        if(humset <0)
        {
          humset = 99;
        }
      }
     if(digitalRead(menu)==0)
     {
      chedo = chedo+1;
      if(chedo >1)
      {
        chedo =0;
      }
     }
    }

  // CHe do manu

    while ( chedo == 1)
    {
      lcd.setCursor(9,1);
     lcd.print("MA");
     getSHT();
     if(digitalRead(tang)==0)//neu nhan nut nhan
        {
          states = 1;
        }
     if(digitalRead(giam)==0)//neu nhan nut nhan
       {
         states = 0;
       }
     if(digitalRead(menu)==0)
       {
       chedo = chedo+1;
       if(chedo >1)
        {
        chedo =0;
       }
      }
      if(states == 1)
      {
        digitalWrite(relay,HIGH);
      }
      else
      {
        digitalWrite(relay,LOW);
      }
    }
  }
}
