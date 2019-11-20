#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>

ESP8266WebServer server(80);

String webPage = "";

boolean button_State;
const int button_pin = D3;
const int gpio2_pin = D0;
int lastButtonState = LOW; 

void setup(void){
  
  Serial.begin(9600);
  delay(1000);
  Serial.println("");
  WiFiManager wifiManager;

  pinMode(button_pin, INPUT);
  digitalWrite(button_pin, HIGH);

  pinMode(gpio2_pin, OUTPUT); 

  button_State = false;

  if (!wifiManager.autoConnect("BanLinhKien.Vn CS#")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected... :)");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

   server.on("/", [](){
   int val = digitalRead(gpio2_pin);
   if(val == HIGH)
     webPage += "Trạng thái thiết bị: OFF";
   if(val == LOW) 
     webPage += "Trạng thái thiết bị: ON";
     server.send(200, "text/html", webPage);
   });
    
  server.on("/relayon", [](){
    digitalWrite(gpio2_pin, LOW);
   int val = digitalRead(gpio2_pin);
  if(val == HIGH)
    webPage += "Trạng thái thiết bị: OFF";
  if(val == LOW) 
    webPage += "Trạng thái thiết bị: ON";
    server.send(200, "text/html", webPage);
    delay(1000);
  });
  
  server.on("/relayoff", [](){
    digitalWrite(gpio2_pin, HIGH);
   int val = digitalRead(gpio2_pin);
  if(val == HIGH)
    webPage += "Trạng thái thiết bị: OFF";
  if(val == LOW) 
    webPage += "Trạng thái thiết bị: ON";
    server.send(200, "text/html", webPage);
    delay(1000); 
  });
   
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  
  webPage = "<html> <header>";
  webPage += "<title>Điều khiển công tắc thông minh</title>"; 
  webPage += "<meta charset=\"utf-8\"> </header>";

  webPage += "<body>" ;
  webPage += "<center> <img src=\"https://upload.wikimedia.org/wikipedia/vi/5/50/LogoUCTnew.jpg\" width=\"100px\" height=\"auto\"/>";
  webPage += "<center> <h3> BANLINHKIEN.VN <br> SỐ 11 NGÕ 66 DAI CO VIET<br> </h3> ";
  webPage += "<center> <p> <h1 style=\"color: red\">CÔNG TẮC THÔNG MINH</h1></p>";
  webPage += "<p align =\"right\" style=\"color: blue\"> SVTH: Bui Khac Viet </p>";
  webPage += "<p align =\"right\" style=\"color: blue\"> GVHD: MINHHAGROUP <hr> </p>";

  webPage += "<p> <a href=\"relayon\"> <button style=\"width:200px;height:90px\"> <font size=\"5\">Device ON </font> </button> </a>&nbsp";
  webPage += "<a href=\"relayoff\"> <button style=\"width:200px;height:90px\"> <font size=\"5\">Device OFF </font> </button> </a> </p>";
  
  webPage += "</body></html>";
  
  
  int reading = digitalRead(button_pin);
  if (reading != lastButtonState) {
  if (reading == LOW)
    {
      button_State = !button_State; 
    }
   
   lastButtonState = reading;
   digitalWrite(gpio2_pin, button_State); 
   int val = digitalRead(gpio2_pin);
   
  }
      server.handleClient();

}

