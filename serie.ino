int incomingByte = 0;   // for incoming serial data
int led = 9;
int automatic = 1;
String input = "";
int sensibility = 15;

void setup() {
  Serial.begin(9600);
  pinMode (led,OUTPUT);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    
    if(incomingByte == 126){
      input="";
    }
    else if(incomingByte == 65){
      input="A";
    }
    else if(incomingByte == 84){
      input="T";
    }
    else if(incomingByte == 83){
      input="S";
      sensibility = 0;
    }
    else if(incomingByte == 45){
      Serial.print("Commande: ");
      Serial.println(input);
    }else{
      if(input == "A"){
        automatic = incomingByte - '0';
      }
      if(input == "T" && automatic == 0){
        if(incomingByte -'0' == 1){
          digitalWrite (led,HIGH);
        }else{

          digitalWrite (led,LOW);
        }
      }
      if(input.startsWith("S")){
        sensibility = sensibility * 10 + incomingByte - '0';
      }
      input+=incomingByte- '0';
    }
  }


  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(100);
  if(automatic != 0){
    if (sensorValue > sensibility){
      Serial.println ("target0");
      analogWrite (led,LOW);
    }

    if (sensorValue < sensibility){
      Serial.println ("target1");
      sensorValue = map(sensorValue, sensibility, 1, 0, 254);
      analogWrite (led,sensorValue);
    }
  }
}

