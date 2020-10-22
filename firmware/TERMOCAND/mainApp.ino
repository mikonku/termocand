void mainApp(){
  
  while(digitalRead(pushButton)) {
    delay(5);
    int suhu;
    int n = 0;
    int i=0;    
    if(handDetected()){
      myDFPlayer.playMp3Folder(1);
      delayVoice();     
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dekatkan kening");
      lcd.setCursor(4,1);
      lcd.print("Anda");
  
      
      myservo.write(180); delay(1000);
      myservo.write(0);
      Serial.println(F("Memberikan hand sanitizer"));

      
      int i=0;
      while(statSuhu){
        
        if(faceDetected()){
          delay(500);
          float suhu = mlx.readObjectTempC()+CORRECT;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Suhu Tubuh Anda:");
          lcd.setCursor(1,1);
          lcd.print(suhu); lcd.write(DEG); lcd.print("C");
          Serial.println(suhu);
          Serial.println(F("Membaca suhu"));
          if(suhu>THSuhu || suhu < 33){
            Serial.println(F("Suhu tinggi"));  
            statSuhu = false;
            goto ALERT;
          } 
          else if(suhu<THSuhu){
            Serial.println(F("Suhu Normal"));
            myDFPlayer.playMp3Folder(8);
            delayVoice();
            delay(3000);
            statSuhu = false;
          } else {
            normal = true;
            statSuhu = false;
          }
        }
        if(i>counter) {statSuhu = false;}
        i++;
        Serial.println(i);
        delay(1000);
      
      } statSuhu = true;
  
      myDFPlayer.playMp3Folder(2);
      delayVoice();
      myDFPlayer.playMp3Folder(3);
      delayVoice();
      myDFPlayer.playMp3Folder(4);
      delayVoice();
      
      i=0;
      while(i<3){
       i++;
       delay(1000); 
      }
      
      i=0;
      while(member) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tempelkan kartu anda");
        lcd.setCursor(0,1);
        lcd.print("Pada RFID READER");
       
        i=0;
        while(Serial1.available()){
          i++;
          if(i>5){
            goto runNext;
          }
          Serial.println(i);
          delay(1000);  
        } 
      member = true;
    }
    
  runNext:
    if(normal){
      myDFPlayer.playMp3Folder(1);
      delayVoice();
      givePermen();
      myDFPlayer.playMp3Folder(5);
      delayVoice();
      Serial.println(F("Ambil permennya"));
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Silahkan Ambil");
      lcd.setCursor(1,1);
      lcd.print("Permennya");
      del=false;
    }
    
    }

    //Serial.println(del); delay(100);
    while(del==false){
      Serial.println("DEL");
      lcd.clear(); delay(2);
      del=true;
    }
    
    lcd.setCursor(1,0);
    lcd.print(" MAN 2 Bogor");
  }

  SENS:
    if(faceDetected()){
      delay(500);
      float suhu = mlx.readObjectTempC()+CORRECT;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Suhu Tubuh Anda:");
      lcd.setCursor(1,1);
      lcd.print(suhu); lcd.write(DEG); lcd.print("C");
      Serial.println(suhu);
      Serial.println(F("Membaca suhu"));
      if(suhu>THSuhu || suhu < 33){
        Serial.println(F("Suhu tinggi"));           
        goto ALERT;
      } 
      else if(suhu<THSuhu){
        Serial.println(F("Suhu Normal"));
        myDFPlayer.playMp3Folder(8);
        delayVoice();
        delay(3000);
      }
    }
    delay(10);
    goto SENS;

  ALERT:
    myDFPlayer.playMp3Folder(9);
    delayVoice();
    n++;
    if(n>5){ return; }
    goto ALERT;

}
