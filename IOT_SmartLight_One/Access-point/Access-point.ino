
/*
   NodeMCU/ESP8266 act as AP (Access Point) and simplest Web Server
   to control GPIO (on-board LED)
   Connect to AP "arduino-er", password = "password"
   Open browser, visit 192.168.4.1
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "ESP8266";
const char *password = "12345678";
int stateLED = LOW;

ESP8266WebServer server(80);

void handleRoot() {
  response();
}

void handleLedOn() {
  stateLED = HIGH;
  digitalWrite(0, stateLED);
  digitalWrite(2, stateLED);
  response();
}

void handleLedOff() {
  stateLED = LOW;
  digitalWrite(0, stateLED);
  digitalWrite(2, stateLED);
  response();
}
const String HtmlHtml = "<html><head>"
                        "<BODY align=\"center\">"
                        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" /></head>";
const String HtmlHtmlClose = "</html>";
const String HtmlTitle = "<h1>ESP8266 AP By MinhHaGroup</h1><br/>\n";
const String HtmlLedStateLow = "<big>LED is now <b>OFF</b></big><br/>\n";
const String HtmlLedStateHigh = "<big>LED is now <b>ON</b></big><br/>\n";
const String HtmlButtons =
  "<a href=\"LEDOn\"><button style=\"display: block; width: 100%;\">ON</button></a><br/>"
  "<a href=\"LEDOff\"><button style=\"display: block; width: 100%;\">OFF</button></a><br/>";

void response() {
  String htmlRes = HtmlHtml + HtmlTitle;
  if (stateLED == LOW) {
    htmlRes += HtmlLedStateLow;
  } else {
    htmlRes += HtmlLedStateHigh;
  }

  htmlRes += HtmlButtons;
  htmlRes += HtmlHtmlClose;

  server.send(200, "text/html", htmlRes);
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println();

  WiFi.softAP(ssid, password);

  IPAddress apip = WiFi.softAPIP();
  Serial.print("visit: \n");
  Serial.println(apip);
  server.on("/", handleRoot);
  server.on("/LEDOn", handleLedOn);
  server.on("/LEDOff", handleLedOff);
  server.begin();
  Serial.println("HTTP server beginned");
  pinMode(0, OUTPUT);
  digitalWrite(0, stateLED);
  pinMode(2, OUTPUT);
  digitalWrite(2, stateLED);
}

void loop() {
  server.handleClient();
}
