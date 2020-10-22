#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include "DFRobotDFPlayerMini.h"
int n = 0;
const float CORRECT = 4.5;

DFRobotDFPlayerMini myDFPlayer;

LiquidCrystal_I2C lcd(0x27,16,2);

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

NewPing sonar1(48, 50, 100);
NewPing sonar2(3, 2, 200);

#include <Servo.h>

Servo myservo;
Servo permen;

byte bar[] = {
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F,
  0x1F
};
byte degree[] = {
  0x04,
  0x0A,
  0x04,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

#define BAR              0
#define DEG              1
#define buusyPin         A0   //pin busy DFPLAYER
int bsy = 0;

int pos = 0;

bool statSuhu = true; 
bool member = true; 
bool normal = true;
bool del=true;

int counter = 5;
int THSuhu = 38;
String data;
int pushButton = 12;


void SendData(String data = "#1,24739216181,12#");
bool handDetected(long tH = 15);
bool faceDetected(long tH = 15);
