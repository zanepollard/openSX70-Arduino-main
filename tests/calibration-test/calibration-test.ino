const int S1 = 12;     //Red button SHUTTER RELEASE
const int FFA = 4;
int sensorValue;
int lightMeter = A3;
const int Solenoid1 = 3; 

int const samples = 100;
unsigned long timevalue [samples];
//unsigned long high [samples];
unsigned long low [samples];


void setup() {
  // put your setup code here, to run once:
pinMode(S1, INPUT_PULLUP);
pinMode(FFA, OUTPUT);
    
pinMode(Solenoid1, OUTPUT);
 Serial.begin(9600);
Serial.println ("openSX70 calibration");
R11();
analogWrite(Solenoid1, 0);
Serial.print ("Shutter open: ");
Serial.println (analogRead(lightMeter));

Serial.print ("closing shutter...");
analogWrite(Solenoid1, 255);
delay (100);
Serial.print ("Shutter closed: ");
Serial.println (analogRead(lightMeter));


//R15();

int samples = 100;
unsigned long timevalue [samples];
//unsigned long high [samples];
unsigned long low [samples];


}

void R11()
{
//Connect 1M5
//Disconnect rest
//R11 on the PCB
//pinMode (A7, INPUT);
pinMode (A4, INPUT);
pinMode (A5, OUTPUT);  // this is the one "connected"
digitalWrite (A5, LOW);
return ;
}

void R15()
{
//Connect 750K
//Disconnect rest
//R15 on the PCB
//pinMode (A7, INPUT);
pinMode (A5, INPUT);
pinMode (A4, OUTPUT);  // this is the one "connected"
digitalWrite (A4, LOW);
return ;
}





void loop() {

  R11();

if (digitalRead(S1) == LOW) {

unsigned long initialMillis = millis();


timevalue[0] = (millis() - initialMillis);
//  R11();

low[0] = analogRead(lightMeter);

analogWrite(Solenoid1, 0);

for (int i = 1 ; i < samples; i++)
{


timevalue[i] = {millis() - initialMillis};
//  R11();
low[i] = analogRead(lightMeter);
}

for (int i = 1 ; i < samples; i++)
{
Serial.print ("time: ");
Serial.print (timevalue[i]);
Serial.print (" ms  LOW: ");
Serial.println (low[i]);

}

analogWrite(Solenoid1, 0);
Serial.println ("Shutter closed, capture ended");
delay (5000);
}
return;
}
