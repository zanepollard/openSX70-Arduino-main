const int S1 = 12;     //Red button SHUTTER RELEASE
const int FFA = 4;
int sensorValue;
int lightMeter = A3;
const int Solenoid1 = 3; 

int const samples = 100;
unsigned long timevalue [samples];
//unsigned long high [samples];
unsigned long low [samples];

const int numberOfSamples = 200;

struct samples {

unsigned long timeValue;
int lightValue;
  
};

struct samples mySamples[numberOfSamples];



void setup() {


  // put your setup code here, to run once:
pinMode(S1, INPUT_PULLUP);
//pinMode(FFA, OUTPUT);


pinMode(Solenoid1, OUTPUT);
 Serial.begin(9600);

Serial.println ("openSX70 calibration");

//unsigned long timevalue [samples];
//unsigned long high [samples];
//unsigned long low [samples];

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
