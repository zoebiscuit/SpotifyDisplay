#include <Arduino.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <WiFi.h>
#include <SpotifyEsp32.h>
#include <SPI.h>

char* SSID = "";
char* PASSWORD = "";

const char* CLIENT_ID = "CLIENT_ID";
const char* CLIENT_SECRET = "CLIENT_SECRET";

Spotify sp(CLIENT_ID, CLIENT_SECRET);

#define TFT_CS 1
#define TFT_RST 2
#define TFT_DC 3
#define TFT_SCLK 4
#define TFT_MOSI 5

String lastArtist;
String lasTrackname;

Adafruit_ST77 screen = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(115200);

  screen.initR(INITR_BLACKTAB); /type of screen
  screen.setRotation(1); //landscpae
  Serial.println("TFT Initialized!");
  tft.fillScreen(ST77XX_BLACK); //nothing in buffer?? black screen


  WiFi.begin(SSID, PASSWORD);
  Serial.print("Connecting to WiFi...");
  while(WiFi.status() != WL_CONNECTED) { //Shows a loading dot
    delay(1000);
    Serial.print(".");
  }
  Serial.printf("\nConnected!\n");


  screen.setCursor(0,0);
  screen.write(WiFi.localIP().toString().c_str()); //prints IP on screen



  sp.begin();
  while(!sp.is_auth()) {
    sp.handle_client();
    delay(1000);
  }
  Serial.println("Connected to Spotify!");


}



void loop() {
  // put your main code here, to run repeatedly:
  String currentArtist = sp.currentartist_names();
  String currentTrackname = sp.current_track_name():

  if(lastArtist != currentArtist && currentArtist != "Something went wrong" && !currentArtist.isEmpty()) {
    screen.fillScreen(ST77XX_BLACK);
    lastArtist = currentArtist;
    Serial.println("Artist: " + lastArtist);
    screen.setCursor(10,10);
    screen.write(lastArtist.c_str());
  }

  if (lastTrackname != currentTrackname && currentTrackname != "Something went wrong" && currentTrackname != "null") {
    lastTrackname = currentTrackname;
    Serial.println("Track: " + lastTrackname);
    screen.setCursor(10,40);
    screen.write(lastTrackname.c_str());
  }

  delay(2000);

}
