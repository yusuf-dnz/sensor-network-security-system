//Kütüphaneler
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
                                       //BLYNK bulut servisi için gerekli token.
#define BLYNK_TEMPLATE_ID "ID"
#define BLYNK_DEVICE_NAME "ESP"
#define BLYNK_AUTH_TOKEN "Your Token"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;        //Wi-Fi adı ve adresi.
char ssid[] = "xoshimit";
char pass[] = "23275527";
bool msg = 0;                          //Varsayılan olarak 0 mesajı.

BlynkTimer timer;

int s_vcc=16; //sensor pinleri tanımlandı.
int sensor=5;

RF24 radio(0, 2);                      // CE, CSN - RF24 pin seçimi
const byte address[6] = "00001";       //iletişim adresi seçme

void setup()
{
  pinMode(s_vcc,OUTPUT);
  digitalWrite(s_vcc,HIGH);
  
  while (!Serial);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  radio.begin();   
  radio.openReadingPipe(0, address);   //adres(kanal) ayarlama
  radio.startListening();              //modülü alıcı olarak ayarlama
  timer.setInterval(1000L, pirState);
}

void loop()
{
  Blynk.run();
  timer.run();
}


void pirState()
{
   if (radio.available()) 
  {
    
    radio.read(&msg, sizeof(msg));
    }
    
    if(msg==1){

    Serial.println("Güvenlik aktif.");

    long state = digitalRead(sensor);
          if(state == HIGH) {
            
            Blynk.virtualWrite(V5, "Hareket Var!!!");
            Serial.println("Hareket Var!!!");
          
          }
          else {      
            Blynk.virtualWrite(V5, "Hareket Yok...");
            Serial.println("Hareket Yok...");      
           }
    }
    else if(msg==0){
    Serial.println("Güvenlik devre dışı.");
    Blynk.virtualWrite(V5, "Güvenlik kapalı!!!");
    }
    else{
    Serial.println(msg);} //2 değer dışında gelecek veriler.
  }
