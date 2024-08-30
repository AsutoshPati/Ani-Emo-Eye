/*
  Robot Eye Animation (Wi-Fi)

  This project features a robotic eye display that dynamically 
  shows different emotions through various eye expressions. Emotions 
  can be updated in real-time by sending parameters via Wi-Fi, 
  making it an interactive and responsive system ideal for robotics 
  applications.

  created 21 Aug 2024
  by Asutosh Pati (https://www.linkedin.com/in/asutoshpati/)

  Dependencies:
  - Adafruit GFX Library by Adafruit
  - Adafruit SSD1306 by Adafruit
  - ESP32 Dev Module Board (Written for CAP10 Pratham)
*/

#include <WiFi.h>
#include <WebServer.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "eyes.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Put your SSID & Password */
const char* ssid = "CAP10 Eye";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP address details */
IPAddress local_ip(192,168,1,1); 
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80); // Give the port ID

// 0 - Happy; 1 - Neutral; 2 - Sleep; 3 - Angry; 4 - Upset; 5 - Sad; 6 - Love
int mood = 2;                   // Emotion to display
int l_X = 20, r_X = 74;         // Left & right eye position
const int blink_time = 50;      // Duration of eye remain close during blink
const int sleep_after = 2000;   // Blink period
long int last_sleep = 0;        // Last blink time

void setup() {
  Serial.begin(115200);
  delay(100);

  // Create hotSpot/access point
  Serial.println("Starting Hotspot");
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  // Start OLED display
  Serial.println("Starting Display");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setRotation(2);

  show_mood(2); // Initially bot will display Sleep mood/emotion

  // Define resources (URL endpoints)
  server.on("/", show);
  server.onNotFound(handle_NotFound);   // Handle 404 error

  // Start the server now
  server.begin();
  Serial.println("HTTP server started");

}

void loop() {
  server.handleClient(); // Handle clients
  delay(10);

  // Blink after 2 seconds
  if(millis() - last_sleep >= sleep_after){
    blink();
    last_sleep = millis();
  }
}

void handle_NotFound(){
  // Handle the page not found error
  server.send(404, "text/plain", "Not found");
}

void show() {
  /*
  Handle the incoming request to server;
  Check for the emotion received in argument and show mood accordingly.
   */
  String message = "s";
  for (int i = 0; i < server.args(); i++) {
    if(server.argName(i) == "mood"){
      message = server.arg(i);
    }
  }

  if(message == "N") { show_mood(1); }
  else if(message == "F") { show_mood(4); }
  else if(message == "A") { show_mood(3); }
  else if(message == "S") { show_mood(5); }
  else if(message == "H") { show_mood(0); }
  else if(message == "L") { show_mood(6); }
  
  server.send(200, "text/html", sendHTML());
}

// Web-based interface
String sendHTML() {
  String html_text = "<!DOCTYPE html>"
  "<html>"
    "<head><meta name=viewport content=\"width=device-width, initial-scale=1.0, user-scalable=no\">"
    "<title>WiFi RC Car Control</title>"
    "<style>"
      "html { "
        "font-family: Helvetica;"
        "display: inline-block;"
        "margin: 0px auto;"
        "text-align: center;"
        "height: 100%;"
      "}"
      "body{"
        "margin-top: 50px;"
        "height: 100%;"
      "}"
      "h1 {"
        "color: #444444;"
        "margin: 50px auto 30px;"
      "}"
      "h3 {"
        "color: #444444;"
        "margin-bottom: 50px;"
      "}"
      "p {"
        "font-size: 14px;"
        "color: #888;"
        "margin-bottom: 10px;"
      "}"
    "</style>"
  "</head>"
  "<body>"
    "<h1>WiFi Mood Display</h1>"
    "<h3>Made by Protionix</h3>"
    "<hr>"
    "<p id='mood_place' onload='showMood()'></p>"
    "<script>"
      "function GetURLParameter(sParam){"
        "var sPageURL = window.location.search.substring(1);"
        "var sURLVariables = sPageURL.split('&');"
        "for (var i = 0; i < sURLVariables.length; i++){"
          "var sParameterName = sURLVariables[i].split('=');"
          "if (sParameterName[0] == sParam){"
            "return sParameterName[1];"
          "}"
        "}"
      "}"
      ""
      "function showMood() {"
        "document.getElementById('mood_place').innerHTML = GetURLParameter('mood');"
      "}"
    "</script>"
  "</body>"
"</html>";
return html_text;
}

void show_mood(int mood_id){
  // Show the desired emotion / mood
  mood = mood_id;
  display.clearDisplay();
  display.drawBitmap(l_X, 8, peyes[mood_id][0][0], 32, 32, WHITE);
  display.drawBitmap(r_X, 8, peyes[mood_id][0][1], 32, 32, WHITE);
  display.display();
}

void blink(){
  // Blink Eye
  display.clearDisplay();
  display.drawBitmap(l_X, 8, eye0, 32, 32, WHITE);
  display.drawBitmap(r_X, 8, eye0, 32, 32, WHITE);
  display.display();
  delay(blink_time);
  show_mood(mood);
}
