#define BLYNK_TEMPLATE_ID "TMPL6g-ebZ-CU"
#define BLYNK_TEMPLATE_NAME "VehicleSafety"
#define BLYNK_AUTH_TOKEN "Your Auth Token" // 👈 এখানে আপনার আসল ব্লিংক টোকেন বসান

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <MPU6050.h>
#include <LiquidCrystal_I2C.h>

// 📶 ওয়াইফাই সেটিংস (হ্যান্ডওভারের সুবিধার্থে এটি সেট করা)
char ssid[] = "Sohag mahmud";       
char pass[] = "PASSsohag99";        

BlynkTimer timer;
MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define TRIG D5
#define ECHO D6
#define LED  D7
#define BUZZ D8
#define MQ   A0

// 🚧 আল্ট্রাসনিক সেন্সর রিডিং ফাংশন
long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 25000); // ২৫ms নিরাপদ টাইমআউট
  if (duration == 0) return 400; 
  return duration * 0.034 / 2;
}

// ☁️ ডাটা প্রসেসিং ও অ্যালার্ট লজিক
void sendData() {
  long dist = getDistance();
  int gas = analogRead(MQ);

  // ⚠️ টিল্ট রিডিং
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  float tilt = abs(ax / 16384.0 * 90);

  String alert = "SAFE";
  bool hazard = false; 

  // অ্যালার্ট কন্ডিশন চেক
  if (dist < 15) {
    alert = "OBSTACLE";
    hazard = true;
  }
  else if (gas > 920) { // আপনার পরিবেশ অনুযায়ী এই মান (যেমন ৪০০ বা ৬০০) টিউন করতে পারেন
    alert = "GAS LEAK";
    hazard = true;
  }
  else if (tilt > 45) {
    alert = "ACCIDENT";
    hazard = true;
  }

  // বিপদ থাকলে হার্ডওয়্যার আউটপুট অন হবে, কেটে গেলে অটো অফ হবে
  if (hazard) {
    digitalWrite(LED, HIGH);
    digitalWrite(BUZZ, HIGH);
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(BUZZ, LOW);
  }

  // 💻 এলসিডি স্ক্রিন আপডেট (সবচেয়ে নিরাপদ ফরম্যাট)
  lcd.clear();
  if (hazard) {
    lcd.setCursor(0, 0);
    lcd.print("⚠️ HAZARD DETECT!");
    lcd.setCursor(0, 1);
    lcd.print("STATUS: " + alert);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("D:" + String(dist) + "cm G:" + String(gas));
    lcd.setCursor(0, 1);
    lcd.print("T:" + String((int)tilt) + "deg  S:SAFE");
  }

  // ☁️ ব্লিংক মোবাইল অ্যাপে ডাটা পুশ
  Blynk.virtualWrite(V0, dist);
  Blynk.virtualWrite(V1, gas);
  Blynk.virtualWrite(V2, tilt);
  Blynk.virtualWrite(V3, alert);
}

void setup() {
  Serial.begin(115200); 

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  digitalWrite(LED, LOW);
  digitalWrite(BUZZ, LOW);

  Wire.begin(D2, D1); 
  mpu.initialize();

  // এলসিডি ডিসপ্লে ইনিশিয়াল স্টার্ট
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Vehicle Safety");
  lcd.setCursor(0, 1);
  lcd.print("System Starting");

  // 🛑 ক্র্যাশ প্রতিরোধের বিশেষ ওয়াইফাই কনফিগারেশন
  WiFi.begin(ssid, pass);
  Blynk.config(BLYNK_AUTH_TOKEN);
  
  timer.setInterval(1000L, sendData); // প্রতি ১ সেকেন্ড পর পর ডাটা আপডেট হবে
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.run(); // ওয়াইফাই কানেক্ট থাকলেই কেবল ব্লিংক ক্লাউড রান করবে
  }
  timer.run();
}
