#include <SPI.h>                          //SPI kütüphanemizi tanımlıyoruz.
#include <MFRC522.h>                      //MFRC522 kütüphanemizi tanımlıyoruz.
#include <nRF24L01.h>
#include <RF24.h>

bool guvenlikDurum = false;
int RST_PIN = 10;                          //RC522 modülü reset pinini tanımlıyoruz.
int SS_PIN = 9;                          //RC522 modülü chip select pinini tanımlıyoruz.
                                          
RF24 radio(7, 8);  // CE, CSN 
const byte address[6] = "00001";

MFRC522 rfid(SS_PIN, RST_PIN);            //RC522 modülü ayarlarını yapıyoruz.
byte ID[4] = {241, 153, 71, 67};          //Yetkili kart ID'sini tanımlıyoruz. 

void setup() { 
  Serial.begin(9600);                     //Seri haberleşmeyi başlatıyoruz.
  SPI.begin();                            //SPI iletişimini başlatıyoruz.
  rfid.PCD_Init();                        //RC522 modülünü başlatıyoruz.
  
  radio.begin();
  radio.openWritingPipe(address);         //İletişim kanalını seçiyoruz.
  radio.stopListening();                  //Receiver özelliğini se.iyoruz.      
}
 
void loop() {
  
    if ( ! rfid.PICC_IsNewCardPresent()){    //Yeni kartın okunmasını bekliyoruz.
    delay(500);
    return;
  } 
  if ( ! rfid.PICC_ReadCardSerial())      //Kart okunmadığı zaman bekliyoruz.
    return;

  if (rfid.uid.uidByte[0] == ID[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
      rfid.uid.uidByte[1] == ID[1] && 
      rfid.uid.uidByte[2] == ID[2] && 
      rfid.uid.uidByte[3] == ID[3] ) 
      {
        Serial.println("Geçerli Kart");
        ekranaYazdir();

        guvenlikDurum = !guvenlikDurum; //Kart ilk okumada güvenliği açar,sonraki okutmada güvenliği kapatır.
                
        //alıcı devreye RF veri gönderme
        
        if(guvenlikDurum==true){
          
          bool durum = 1;
          radio.write(&durum, sizeof(durum));
          Serial.println("Güvenlik aktif");
          
          }
          
        else{
          bool durum = 0;
          radio.write(&durum, sizeof(durum));
          Serial.println("Güvenlik devre dışı");
          }
        
      }
  else  //Yetkisiz girişte içerideki komutlar çalışır.
      {                                
        Serial.println("Yetkisiz Kart");
        ekranaYazdir();                
        delay(1000);
      }
  rfid.PICC_HaltA();
}
void ekranaYazdir(){
  Serial.print("ID Numarasi: ");
  for(int sayac = 0; sayac < 4; sayac++)
  {
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
    Serial.println("");
}
