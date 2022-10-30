
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WebServer.h>

#include <WiFi.h>

#include "page.h" //Pagina HTML con javascript
#include "logo_bitmap.h"//Logo del proyecto
// convertir imagen en bitmap http://javl.github.io/image2cpp/

#define A  16   //Puerto de salida conectado al pin A del CD4052
#define B  17   //Puerto de salida conectado al pin B del CD4052
#define Ampli 18 // - Puerto de salida que enciende y apaga el amplificador
#define Bt    19 //TX - Puerto de salida que enciende y apaga el modulo Bluetooth

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,-1);

const char* ssid = "vodafoneFD30";
const char* password = "R2MHRTMGTNJZGK";
WebServer server(80); //Server on port 80


//Configuración por defecto; variables globales
boolean change = false;
String device = "PC"; 
String ampli = "OFF";
String bt = "OFF";


// ENVIAR PÁGINA HTML CON CÓDIGO JAVASCRIPT INCRUSTADO
void handlePage() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


// MONITORIZACIÓN DE LAS VARIABLES
void handleVariables(){
  server.send(200, "application/json", "{\"Ampli\":"+ampli+", \"Bt\":"+bt+"}"); 
  
}

void handleOptionStatus() {
    server.send(200, "text/plane", device); //
}

//MANEJADORES DE BOTONES

void handleAmpli() {
 String option = server.arg("Ampli"); 
 if (option == "OFF") {
  digitalWrite(Ampli, HIGH);
  ampli = "ON";
 }else{ 
  digitalWrite(Ampli, LOW);
  ampli = "OFF";
 }
 change = true;
 server.send(200, "text/plane", ampli); //Send web page
}

void handleBt() {
 String option = server.arg("Bt"); 
 if (option == "OFF") {
  digitalWrite(Bt, HIGH);
  bt = "ON";
 }else{ 
  digitalWrite(Bt, LOW);
  bt = "OFF";
 }
 change = true;
 server.send(200, "text/plane", bt); //Send web page
}
void handleOption() {
 String option = server.arg("Option"); 
 if (option == "PC") {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
 }else if(option == "Bluetooth"){
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
 }else if(option == "Aux input I"){
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
 }else if(option == "Aux input II"){
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
 }
 device = option;
 change = true;
 server.send(200, "text/plane", device); //Send web page

}
// physical buttons



void updateDisplay(){
  display.clearDisplay();
  // Scroll part of the screen
  display.setCursor(6,3);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.println("Configuracion actual");
  display.setCursor(6,0);
  display.drawRect(0, 0, 128, 13, WHITE);
  display.setTextColor(WHITE);
  display.setCursor(6,15);
  display.print("Amplificador:");
  display.setTextColor(BLACK, WHITE);
  display.print(ampli);
  display.setCursor(6,25);
  display.setTextColor(WHITE);
  display.print("Bluetooth:");
  display.setTextColor(BLACK, WHITE);
  display.print(bt);
  display.setCursor(6,35);
  display.setTextColor(WHITE);
  display.print("Entrada:");
  display.setTextColor(BLACK, WHITE);
  display.print(device);
  display.setTextColor(WHITE);
  display.setCursor(6,45);
  display.print("Red wifi: ");
  display.print(ssid);
  display.setCursor(6,55);
  display.print("IP: ");
  display.println(WiFi.localIP()); 
  display.display();
  }

void setup(void){
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  display.drawBitmap(0, 0,  CrayfeLogo, 128, 64, WHITE);
  display.display();
  pinMode(Ampli, OUTPUT);
  pinMode(Bt,OUTPUT);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);


  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(Ampli, LOW);
  digitalWrite(Bt, LOW);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.print(WiFi.localIP());
  server.on("/", handlePage);      
  server.on("/setOption", handleOption);
  server.on("/swapAmpli", handleAmpli);
  server.on("/swapBt", handleBt);
  server.on("/variables", handleVariables);
  //server.on("/readOption", handleOptionStatus);
  server.begin();                  //Start server
  delay(2000);
  updateDisplay();
}


void loop(void){

  if(change){
    updateDisplay();
    change = false;
  }  
    
  server.handleClient();          //Handle client requests
}
