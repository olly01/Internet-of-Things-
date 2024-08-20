
#define BLYNK_TEMPLATE_ID           "TMPL5duwe5DmS"
#define BLYNK_TEMPLATE_NAME         "dryer sensor"
#define BLYNK_AUTH_TOKEN            "2-b45XqL7igRTiWftebBOPRh7XDeviDG"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
// Set password to "" for open networks.
#include <DHT.h>

DHT dht(26, DHT11);
char ssid[] = "NOWEILDV_EXT";
char pass[] = "bHVJZFQjxx1t";

BlynkTimer timer;

int remainingTime = 0;

void myTempEvent(){
double temp = dht.readTemperature();
Blynk.virtualWrite(V0, temp);
//if(temp>23){
  //Blynk.logEvent("notify");
//}
}
void myHumidEvent(){
double humid = dht.readHumidity();
Blynk.virtualWrite(V4, humid);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void updateTimer(){
  if (remainingTime > 0) {
    remainingTime --;

    int hours = remainingTime / 3600;
    int minutes = (remainingTime % 3600) / 60;
    int seconds = remainingTime % 60;

    // Format the time and update the Blynk widget
    Blynk.virtualWrite(V2, String(hours) + ":" + String(minutes) + ":" + String(seconds));
  } else {
    // Timer expired, you can perform actions here
    Serial.println("Timer expired!");
    Blynk.logEvent("notify");
    // Optionally, you can reset the timer or perform any other actions
    // remainingTime = timerDuration;
  }
}

BLYNK_WRITE(V3) {  // Assuming V2 is the virtual button pin on your Blynk app
  int buttonState = param.asInt();
  if (buttonState == 1) {  // Check if the button is pressed
    double temp = dht.readTemperature();
    double humid = dht.readHumidity();
    
    // Check if readings are valid
    if (!isnan(temp) && !isnan(humid)) {
      double newTime = 50 / (temp * (1 - (humid / 100)));
      
      if (!isnan(newTime) && newTime > 0) {
        remainingTime = newTime * 3600;
        Blynk.virtualWrite(V1, remainingTime);
        Serial.println("Timer updated based on button press.");
      } else {
        Serial.println("Invalid timer value");
      }
    } else {
      Serial.println("Invalid temperature or humidity reading");
    }
     Blynk.virtualWrite(V3, 0);
  }
}

void setup()
{
Serial.begin(115200);
pinMode(LED_BUILTIN, OUTPUT);
Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
timer.setInterval(1000L, updateTimer);
timer.setInterval(1000L, myTempEvent);
timer.setInterval(1000L, myHumidEvent);
dht.begin();
delay(2000);
}

void loop()
{
    
Blynk.run();
timer.run();
double temp = dht.readTemperature();
double humid = dht.readHumidity();



// Call the updateTimer function every second
timer.setInterval(1000L, updateTimer);
Serial.print("Temp: ");
Serial.print(temp);
Serial.print("c");
Serial.print("Humidity: ");
Serial.print(humid);
Serial.println(" % ");
delay(2000);
}