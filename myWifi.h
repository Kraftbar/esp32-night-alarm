
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
// Replace with your network credentials
const char* ssid     = "Telenor2259nam";
const char* password = "RammetilskuddSkumlagt";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;


void mytoInt(String timeString , int &sek,int &min,int &hour){
    int firstColon = timeString.indexOf(":");
    int secondColon = timeString.lastIndexOf(":");
    
    String hourString = timeString.substring(0, firstColon);
    String minString = timeString.substring(firstColon + 1, secondColon);
    String secString = timeString.substring(secondColon + 1);

    int foo [3];
    hour=hourString.toInt();
    min=minString.toInt();
    sek=secString.toInt();

}



void mySetup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(3600*2);
}
int myLoop() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedTime();


  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);


  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);

  int sek;  int min;int hour;
  mytoInt(dayStamp,sek,min,hour);

  return hour;


 

}
