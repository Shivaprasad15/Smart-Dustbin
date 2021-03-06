 #include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  //RX,TX

int count=0;
const int trigPin = 6;
const int echoPin = 5;
int led=4;

long duration;
int distance;


void sms(){
     count=2;
     mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     mySerial.println("AT+CMGS=\"+9197******06\"\r"); //Phone number
     delay(1000);
     mySerial.println("Smart Bin...Vijayanagar Trash Container has been filled please clear it. https://goo.gl/XH4DTR");      //Message with the location url
     delay(100);
     mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
      delay(1000);
      Serial.println("SMS sent");
      return;
  }


  
void setup() {
mySerial.begin(9600);   // Setting the baud rate of GSM Module  
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(led,OUTPUT);
Serial.begin(9600); // Starts the serial communication
delay(1000);
}


void loop() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW); // Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;
Serial.print("Distance: ");
Serial.println(distance);
if(count==0)
{
if(distance<12) {
  digitalWrite(led,HIGH);
  sms();
} 
}
if(distance>=19) {
digitalWrite(led,LOW);
count=0;
}

delay(5000);
}


