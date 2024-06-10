#include <Servo.h>

//ambil template, device dan token dari blynk
#define BLYNK_TEMPLATE_ID "TMPLXZWfjVmI"
#define BLYNK_DEVICE_NAME "Pakan Iwak Neo"
#define BLYNK_AUTH_TOKEN "0L9EwJo9FpkxiVlOtnla71lm8YR-nWmr"

//include library Blynk
#include <BlynkSimpleEsp8266.h>

Servo servo;

//buat sebuah variabel untuk menampung datastream StatusPakan
int StatusPakanNeo;

void setup() {
  // servo = D2 = 4 
  servo.attach(4);
  // posisi servo awal
  servo.write(0);

  Serial.begin(115200);

  //koneksi ke WiFi
  WiFi.begin("malmal", "ucilganteng");
  //uji berhasil atau tidak
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Wifi Terkoneksi");
  
  //apabila terkoneksi, koneksikan perangkat ke Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, "malmal", "ucilganteng");

  Serial.println("Blynk Terkoneksi");
}

void BeriPakan()
{
  //proses perputaran baling baling secara halus
  for(int posisi=0; posisi<=300; posisi++)
  {
    //set posisi servo berdasarkan variabel posisi
    servo.write(posisi);
    delay(10);  
  }
  for(int posisi=300; posisi>=0; posisi--)
  {
    //set posisi servo berdasarkan variabel posisi
    servo.write(posisi);
    delay(10);  
  }
}

void loop() {
  //jalankan aplikasi Blynk dari NodeMCU
  Blynk.run();

  //tampilkan StatusPakan Neo diserial monitor
  Serial.println("Status Pakan : " + String(StatusPakanNeo));

  //jika StatusPakanNeo = 1 maka beri pakan
  if(StatusPakanNeo == 1)
  {
    //panggil void BeriPakan
    BeriPakan();
    //kembalikan StatusPakanNeo menjadi 0 setetlah diberi pakan
    Blynk.virtualWrite(V0, 0);
    StatusPakanNeo = 0;
    delay(2000);
  }
}

//baca data stream StatusPakanNeo
BLYNK_WRITE(V0)
{
  //baca datastream kemudian tampung kedalam variabel StatusPakanNeo
  StatusPakanNeo = param.asInt();
}
