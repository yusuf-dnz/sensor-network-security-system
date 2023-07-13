# Sensor Network - Security System
Arduino UNO &amp; NodeMCU  Sensor Network.
----
Bu sistemde bir sensör ağ kurularak, belirli bir alanda kızıl ötesi hareketlenmelerin algılanıp sistem sahibine Cloud üzerinden bilgilendirme yapılması sağlanıyor.
Mevcut iki adet düğüm ile bu sistem tamamen kablosuz olarak çalışabilir ve ağ ölçeklenebilir olup sensör düğüm sayısı artırılabilir.

Sistem sahibi tarafından RFID kart ile etkinleştirilen anahtar düğüm yayınladığı mesaj ile  sensor düğümü kablosuz olarak etkinleştirip BLYNK sunucusuna durum bilgisi göndermeye başlar ve bu bilgi hem mobil hem tarayıcı tarafında hesap sahibi tarafından anlık olarak okunabilir.

----
This security system, a sensor network is established to detect infrared movements in a specific area and provide notification to the system owner through the Cloud. This system can operate completely wirelessly with two existing nodes and is scalable, allowing for an increase in the number of sensor nodes.

The Key node, activated by an RFID card by the system owner, initiates the activation of the sensor node wirelessly through its broadcasted message. It starts sending status information to the BLYNK server, and this information can be instantly read by the account owner on both mobile and browser platforms.

![image](https://github.com/yusuf-sea/Arduino_SensorNetwork/assets/101550162/60efb880-6ad7-4f22-bafa-59a743bcd19b)

## Key Node [1.1]

- NRF24L01
- MFRC522
- Arduino Uno R3

Anahtar düğüm, RFID kart ile etkinleştirilip ortama 2.4Ghz bandında mesaj yayınlamak üzere programlandı. Yayınlanan mesaj etki alanı içerisinde olan bulut erişimli düğüme bir aktif/pasif mesajı gönderiyor.

RFID kart ilk okutulmada aktif etme mesajı olarak bool tipinde "1" mesajı yollar, kart tekrar okutulduğunda bool değeri "0" olarak değiştirilip radyo frekans ile yayınlanır. 

English description:
----
The Key node is programmed to be activated with an RFID card and broadcast messages in the 2.4GHz band within its range. The broadcasted message sends an active/passive signal to the cloud-enabled node within its coverage area.

Upon the initial card reading, the RFID card sends an activation message as a boolean value of "1". When the card is read again, the boolean value is changed to "0" and broadcasted via radio frequency.

## Cloud Gateway [1.2]

- NRF24L01
- NodeMCU V3
- PIR sensor

Bulut erişimli düğüm, Anahtar düğümden gelen radyo frekans dalgalarını dinler. Gelen herhangi bir veri var ise kontrol deyimleri ile 0 veya 1 olduğu tespit edilip, "1" mesajı alınırsa üzerinde bulunan kızılötesi sensörü okumaya başlar ve okunan veriyi düşük bir gecikme ile buluta gönderir. Eğer okunan veri "0" ise bulut sisteme "güvenlik kapalı" mesajı gönderir ve sesör okumayı durdurur.

English description:
----
Cloud Gateway node listens to radio frequency waves from the Key node. If there is any incoming data, it is determined whether it is a "0" or "1" using control statements. If a "1" message is received, it starts reading the infrared sensor on it and sends the read data to the cloud with low latency. If the read data is "0," the cloud sends  "security closed" message to the system and stops sensor reading.

--------
![image](https://github.com/yusuf-sea/Arduino_SensorNetwork/assets/101550162/8b0eb2c2-dded-4933-a521-badafee46e0c)

* Mobile App


