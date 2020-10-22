void initialize() {
   
  myservo.attach(7);
  permen.attach(A10);
  pinMode(buusyPin, INPUT);
  pinMode(pushButton, INPUT_PULLUP);
  
  Serial.println(F("Running Device."));
  
  lcd.init();
  lcd.backlight();
  lcd.createChar(BAR, bar);
  lcd.createChar(DEG, degree);
  lcd.home();
  
  loadSetting();
  lcd.print("OKE");
  
  Serial.begin(115200);
  Serial1.begin(9600);
  mlx.begin(); 


  Serial.println(F("MENYALAKAN PERANGKAT"));
  
  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("SUARA AKTIF"));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
  myDFPlayer.play(1);
  delayVoice();

  
  statSuhu =true;
  member=true;
  normal=true;
  myservo.write(0);
  permen.write(0);
  lcd.clear();
  
}

void loadSetting(){
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("LOADING");
  
  lcd.setCursor(0,1);
  for(int i=0;i<32;i++) {
    lcd.write(BAR);
    delay(20);
    i++;  
  }
  lcd.clear();
}

void delayVoice() { 
  if (myDFPlayer.available()) {
        printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }
  int z=0;
  int bsyflag=0;
  for(z=0; z<=300; z++){
    bsy = digitalRead(buusyPin);
    delay(20); 
    if (bsyflag==1 && bsy==1){
      break;
    }
    if(bsy==0){
      bsyflag=1;
    }
  }  
}


void printDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

bool handDetected(long tH){
  if(sonar1.ping_cm()<tH && sonar1.ping_cm()!=0) {
    Serial.println(F("HAND DETECTED!"));
    return true;
  } else {
    //Serial.println(F("HAND NOT DETECTED!"));
    return false;
  }
}

bool faceDetected(long tH){
  if(sonar2.ping_cm()<tH && sonar2.ping_cm()>4) {
    Serial.println(F("FACE DETECTED!"));
    return true;
  } else {
    //Serial.println(F("FACE NOT DETECTED!"));
    return false;
  }
}

void ShowSerialData() {
//  while(Serial1.available()!=0){
//    Serial.write(Serial1.read());
//  }
}

void SendData(String data) {
  Serial1.println(data); delay(50);
  //ShowSerialData();
}

void alert() {
    myDFPlayer.playMp3Folder(9);
    delayVoice();
    myDFPlayer.playMp3Folder(10);
    delayVoice();
    Serial.println("Menutup hand sanitizer");
//    goto runDevice;
}

void givePermen(){
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    permen.write(pos);              // tell servo to go to position in variable 'pos'
    delay(2);                       // waits 15ms for the servo to reach the position
  }
  delay(1000);
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    permen.write(pos);              // tell servo to go to p osition in variable 'pos'
    delay(2);                       // waits 15ms for the servo to reach the position
  }
}
