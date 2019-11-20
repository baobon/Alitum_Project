#include <ESP8266WiFi.h>
#include <FirebaseArduino.h> 
#include <SHT1x.h>
#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x3F,16,2);
#define dataPin  D5 // Vàng
#define clockPin D6 // Xanh dương
SHT1x sht1x(dataPin, clockPin);
int temp,states;
float humidity;
int humset;
int menu = 0;
#define relay D0
#define firebaseURL "nhayen-17c7a.firebaseio.com"
#define authCode  "4LGQ9fmMhv1WGzj2wxSVEaz05rWth4BoH3Owp5i1"
#define Idwifi "P5 VIP"
#define passwifi "123466666a"

void setupFirebase()
{
  Firebase.begin(firebaseURL,authCode);
  Firebase.setFloat("Temp", 0);
  Firebase.setFloat("Humidity", 0);
  Firebase.set("relay", 0);
  Firebase.set("states", 0);
  Firebase.set("humset", "80");
  Firebase.set("menu",0);
}


void setupWifi()
{ 
  WiFi.begin(Idwifi,passwifi);
  lcd.print("Wait connect");
  while(WiFi.status() != WL_CONNECTED)
    {
    lcd.print(".");
    delay(500);
    }
  delay(2000);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("Connected");
  lcd.setCursor(2,1);
  lcd.print("IoT-Temp-Humi");
  delay(5000);
}



void lcdbegin()
{ lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.setCursor(4,0);
  lcd.print(char(223));
  lcd.print("C");
  lcd.setCursor(8,0);
  lcd.print("H:");
  lcd.print(1,0);
  lcd.setCursor(15,0);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Hs:");
  lcd.setCursor(5,1);
  lcd.print("%");
  lcd.setCursor(10,1);
  lcd.print("ST:");
}

void setup()
{  pinMode(D0,OUTPUT);
   digitalWrite(D0,HIGH);
   Serial.begin(115200);
   lcd.init();      
   lcd.backlight(); 
   setupWifi();
   setupFirebase();
   lcdbegin();
}

void getSHT()
{
  temp = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
}
void sendSHT()
{
  Firebase.setFloat("Temp",temp);
  Firebase.setFloat("Humidity",humidity);
}

void getLCD()
{
  lcd.setCursor(2,0);
  if(temp > 100 or temp < 0)
  {lcd.print("--");}
  else{lcd.print(temp);}
  lcd.setCursor(10,0);
  if(humidity > 100 or humidity < 0)
  {lcd.print("--.--");}
  else
  {lcd.print(humidity);}
  lcd.setCursor(3,1);
  lcd.print(humset);
  lcd.setCursor(13,1);
  int statusrl = digitalRead(relay);
  if(statusrl==1)
  {
    lcd.print("ON ");
  }
  if(statusrl==0)
  {
    lcd.print("OFF");
  }
}

void getData()
{ 
  String valhum = Firebase.getString("humset");
  String valsta = Firebase.getString("states");
  String valmenu = Firebase.getString("menu");

  humset = valhum.toInt();
  states = valsta.toInt();
  menu = valmenu.toInt();
  
} 

void Manu()
{
  if(states == 0)
  {
    digitalWrite(relay, 0);
    Firebase.setInt("relay", 0);
  }else if(states ==1)
  {
    digitalWrite(relay, 1);
    Firebase.setInt("relay",1);
  }
}

void Auto()
{
  if(humset > humidity)
  {
    digitalWrite(relay,1);
    Firebase.setInt("relay",1);
  }else{
    digitalWrite(relay,0);
    Firebase.setInt("relay",0);
  }
}

void loop()
{
  while(true)
  {
    while(menu==0)
    {   lcd.setCursor(7,1);
        lcd.print("AU");
        
          getLCD();
          getData();
          Auto();
          getSHT();
          
      sendSHT();
    }
   while(menu==1)
   {    lcd.setCursor(7,1);
        lcd.print("MA");

          getLCD();
          getData();
          Manu();
          getSHT();
        
      sendSHT();
   }
  }
}
