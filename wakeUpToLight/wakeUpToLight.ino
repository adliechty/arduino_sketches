int lightsPin = 3;      // LED connected to digital pin 9
int curTime = 0;
int incomingByte = -1;
unsigned long StartTime = millis();
unsigned long alarmTime = 30600000;//28800000;   8.5 hours
unsigned long fadeInTime = 300000;  //5 min fade in time
string readString;

;void setup() {
  // put your setup code here, to run once:
  pinMode(lightsPin, OUTPUT);
  Serial.begin(9600); 
  Serial.print("START OF PROGRAM");
  analogWrite(lightsPin, 255);
  delay(1000);
  analogWrite(lightsPin, 0);
  delay(1000);
  analogWrite(lightsPin, 255);
  delay(1000);
  analogWrite(lightsPin, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

  curTime = curTime + 1;

  if (Serial.available())  {
    char c = Serial.read();  //gets one byte from serial buffer
    if (c == '\n') {
      //do stuff
      Serial.println(readString); //prints string to serial port out
      readString=""; //clears variable for new input      
     }  
    else {     
      readString += c; //makes the string readString
    }
  }
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
      incomingByte = incomingByte - 48;
      analogWrite(lightsPin, incomingByte);
  }                
  if (millis() - StartTime >= alarmTime) {
      Serial.print("TIMER EXPIRED");
      int fade = 0;
      while (millis() - StartTime < alarmTime + fadeInTime) {
        fade = ((millis() - StartTime - alarmTime) /  (fadeInTime / 255));
        Serial.print(fade, DEC);
        Serial.print("\n");
        analogWrite(lightsPin, fade);  
        
      }
      analogWrite(lightsPin, 255);
      Serial.print("Done");
      while (1 == 1) {}

  }
}

