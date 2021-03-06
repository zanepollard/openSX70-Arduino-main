// --------------------------------------------------------------------------------------------------------------------------------------

//                                CAMERA CONTROL

// --------------------------------------------------------------------------------------------------------------------------------------
//***************************************************************************************************************************************

int REDbutton(int button) {

               #if ISDEBUG 
              //Serial.println("REDbutton");      
              #endif

    
    // REDbutton (button pin)
    // REDbutton is a standalone function
    // by Joaquín de Prada
  
// REDbutton variables  
static boolean buttonActive = false;
static unsigned long buttonTimer = 0;
static unsigned long STARTbuttonTimer = 0 ;
// END of REDbutton variables
    
    pinMode(button, INPUT_PULLUP);
 
    
int result= 0 ;

                 #if ISDEBUG 
                 //Serial.print ("SHUTTERSPEED:  ");    
                 //Serial.println (ShutterSpeed[Read_DS2408_PIO(0)]);
                 #endif

if (digitalRead(button) == LOW) {
            if (buttonActive == false) {
               #if ISDEBUG 
              Serial.println("button pressed");      
              #endif
            STARTbuttonTimer = millis(); 
            buttonActive = true ;
                                        }
     
     } else  {


      if (buttonActive == true) {
            buttonTimer = millis();
               #if ISDEBUG 
            Serial.println("button just released");
            Serial.print("pressed time inside function:  ");
              #endif
            result = (buttonTimer - STARTbuttonTimer);
               #if ISDEBUG 
            Serial.println(result);
              #endif
            buttonActive = false ;
     }
     }
                      return result;

     } // END OF REDbutton function
//***************************************************************************************************************************************
void ShutterT()
{
                 #if ISDEBUG 
                 Serial.println ("SHUTTER T");    
                 #endif

                  #if SHUTTER
                  shutterCLOSE (); 
                  #endif
                  
                  #if MOTOR 
                  mirrorUP();   //Motor Starts: MIRROR COMES UP!!!
                  while (digitalRead(S3) != HIGH)            //waiting for S3 to OPEN˚
                   ;
                  delay (40);                               //S3 is now open start Y-delay (40ms)
                  #endif
 
                  #if !MOTOR
                  delay (500);
                  #endif

                  #if SHUTTER
                  shutterOPEN ();
                   
                        while (digitalRead(S1) == HIGH)
                        ;

                        if (digitalRead(S1) == LOW)
                        {
                        shutterCLOSE ();
                        }
                  #endif
                  
                  #if !MOTOR
                  delay (1000);
                  #endif

                  #if MOTOR
                  delay (200);                             //AGAIN is this delay necessary?
                  mirrorDOWN ();                          //Motor starts, let bring the mirror DOWN
                  delay (200);                             //AGAIN is this delay necessary?
                  #endif

                 #if SHUTTER
                 shutterOPEN();
                 #endif   
                 //shots = 0;  
       
                 return;       


}

void ShutterB()
{
               #if ISDEBUG 
               Serial.println ("SHUTTER B");    
               #endif

                  #if SHUTTER
                  shutterCLOSE (); 
                  #endif
                  
                  #if MOTOR 
                  mirrorUP();   //Motor Starts: MIRROR COMES UP!!!
                  while (digitalRead(S3) != HIGH)            //waiting for S3 to OPEN˚
                   ;
                  delay (40);                               //S3 is now open start Y-delay (40ms)
                  #endif
 
                  #if !MOTOR
                  delay (500);
                  #endif

                  #if SHUTTER
                  if (Read_DS2408_PIO(2) ==  1) //CASE DONGLE FLASH AT THE END OF B
                  {
                  analogWrite(Solenoid2, 255);
                  }
                  shutterOPEN ();
                   if (Read_DS2408_PIO(2) ==  1) //CASE DONGLE FLASH AT THE END OF B
                  {
                  analogWrite(Solenoid2, 130);
                  }
                        while (digitalRead(S1) == LOW)
                        ;
                   if (Read_DS2408_PIO(2) ==  1) //CASE DONGLE FLASH AT THE END OF B
                  {
                  Write_DS2408_PIO (7,1);
                  delay (1);
                  analogWrite (Solenoid2,0);
                  Write_DS2408_PIO (7,0);                  
                  }
                        shutterCLOSE ();
                  #endif
                  
                  #if !MOTOR
                  delay (1000);
                  #endif

                  #if MOTOR
                  delay (200);                             //AGAIN is this delay necessary?
                  mirrorDOWN ();                          //Motor starts, let bring the mirror DOWN
                  delay (200);                             //AGAIN is this delay necessary?
                  #endif

                 #if SHUTTER
                 shutterOPEN();
                 #endif   
                 //shots = 0;  

              return;    

}
//***************************************************************************************************************************************
void motorON()
{
                                        #if ISDEBUG 
                                      Serial.println ("motorON");
                                      #endif
  digitalWrite(Motor, HIGH);
}

//***************************************************************************************************************************************
void motorOFF()
{
                                      #if ISDEBUG 
                                    Serial.println ("motorOFF");
                                    #endif
  digitalWrite(Motor, LOW);
}

//***************************************************************************************************************************************
void shutterCLOSE()
{
                                      #if ISDEBUG 
                                    Serial.println ("shutterCLOSE");
                                    #endif
                                    HighSpeedPWM ();
                                    analogWrite(Solenoid1, 255);
                                    #if ALPHA
  //                                  Serial.println ("ALPHA");
                                    delay (15);                                        //Wait for the SOL#1 in BC position, more tests perhaps need changed to 25
                                    analogWrite (Solenoid1, 125);
                                    return;
                                    #endif
                                    #if MODEL2
//                                    Serial.println ("MODEL2");
                                    delay (20);                                        //Wait for the SOL#1 in BC position, more tests perhaps need changed to 25
                                    analogWrite (Solenoid1, 155);
                                    return;
                                    #endif
  //return;
  }   //end of void motorON()

//***************************************************************************************************************************************
void shutterOPEN()
{
                            #if ISDEBUG 
                          Serial.println ("shutterOPEN");
                          #endif
analogWrite (Solenoid1,0);
return;

}     //end of void shutterOPEN()
//***************************************************************************************************************************************

void mirrorDOWN()
{
                            #if ISDEBUG 
                          Serial.println ("mirrorDOWN");
                          #endif
  motorON ();

  while (digitalRead(S5) != LOW)  //While S5 open keep the motor running and lower the mirror
    ;
  motorOFF ();
  return;
}    //end of void mirrorDOWN()
//***************************************************************************************************************************************

void mirrorUP()
{
                            #if ISDEBUG 
                          Serial.println ("mirrorUP");
                          #endif
  motorON ();

  while (digitalRead(S5) != HIGH)            //waiting for S5 to OPEN do NOTHING
    ;
  //S5 OPENS
  //S1 MAY BE OPEN NOW (DON'T KNOW HOW TO DO THIS YET)
  // Motor Brake
  motorOFF ();
  return;

}   //end of mirrorUP();
//***************************************************************************************************************************************

void darkslideEJECT()
{
                              #if ISDEBUG 
                            Serial.println ("darkslideEJECT");
                            #endif
  shutterCLOSE();
  mirrorUP();
  mirrorDOWN();
  shutterOPEN();
  return;
}   // end of void darkslideEJECT()

//***************************************************************************************************************************************

void Click(int ExpDelay)
{
 
  if (ExpDelay > 0)
  {
    //AUTO mode ExDelay is the shutter speed from built in light meter
          Serial.print ("(AUTO) ExpDelay = ");
      Serial.println (ExpDelay);

  } else  
    //MANUAL this is where we set the manual aperture
    {
      Serial.print ("(MANUAL) ExpDelay = ");
      Serial.println (ExpDelay);
      
       //added to know the value of photodiode
      //  R11();
      //  sensorValueLOW = analogRead(lightMeter);
        //sensorValueLOW = LightValueLOW();
       // sensorValueHIGH = LightValueHIGH();
       
       int ShutterDelay = (ShutterSpeed[Read_DS2408_PIO(0)]);
       int ShutterDelay1;
       int ShutterDelay2;
       int ShutterDelay3;
       int ShutterConstantFlash = ShutterConstant - FlashDelay;
       int HalfShutterDelay = ShutterDelay / 2 ;
      if ((ShutterDelay) <= (ShutterF8))
        {
         
          ShutterDelay1 = ShutterConstantFlash + HalfShutterDelay;
          ShutterDelay2 = HalfShutterDelay; 
          
        } else 
        {
          ShutterDelay1 = ShutterConstantFlash + ShutterF8;
          ShutterDelay2 = ShutterDelay - ShutterDelay1;
        }
          ShutterDelay3 = ShutterConstantFlash + ShutterDelay;

         //    #if SIMPLEDEBUG 
          
                    Serial.begin (9600);
                    Serial.print ("ShutterConstant: ");
                    Serial.print (ShutterConstant);
                    Serial.println (" ms ");
                    Serial.print ("ShutterConstantFlash: ");
                    Serial.print (ShutterConstantFlash);
                    Serial.println (" ms ");

                    Serial.print ("ShutterDelay: ");
                    Serial.print (ShutterDelay);
                    Serial.println (" ms ");
                    Serial.print ("HalfShutterDelay: ");
                    Serial.print (HalfShutterDelay);
                    Serial.println (" ms ");

                    Serial.print ("Total exposure time including flash: ");
                    Serial.print (ShutterConstant+ShutterDelay);
                    Serial.println (" ms ");
                    
                    Serial.print ("ShutterDelay1: ");
                    Serial.print (ShutterDelay1);
                    Serial.println (" ms ");
                    Serial.print ("ShutterDelay2: ");
                    Serial.print (ShutterDelay2);
                    Serial.println (" ms ");
                    Serial.print ("ShutterDelay3: ");
                    Serial.print (ShutterDelay3);
                    Serial.println (" ms ");
                    Serial.print ("S2 OFF: open----");
                    Serial.print (ShutterDelay1);
                    Serial.print ( "ms----(*Flash)----"); 
                    Serial.print (ShutterDelay2);
                    Serial.println ("ms----close");
                    Serial.print ("S2 ON:  open----");
                    Serial.print (ShutterDelay3);
                    Serial.println ( "ms----(Flash*)----close"); 
                    Serial.println ("-------------------------------");
                //    Serial.print ( "Light Value LOW (direct): ");

               //     Serial.print ( "Light Value HIGH: "); 
               //     Serial.println (LightValueHIGH());
 
                  
           //   #endif
                      Serial.print ( "Light Value LOW: ");
                      Serial.println (sensorValueLOW);
                      Serial.print ( "Light Value HIGH: ");
                      Serial.println (sensorValueHIGH);
                      
          
  if (Read_DS2408_PIO(2) ==  0) 
      {  //S2 OFF FLASH AT THE BEGGINING
      shutterOPEN ();   ////////CLICK! SOLENOID OFF MAKES THE SHUTTER TO OPEN!
      delay (ShutterDelay1);
      //Serial.println ("FastFlash");
      FastFlash();       ////////TRIGGER FLASH
      delay (ShutterDelay2);  
      shutterCLOSE (); ///////PICTURE TAKEN!
      return;
      }
 if (Read_DS2408_PIO(2) ==  1)
      { //S2 ENGAGED FLASH AT THE END
      shutterOPEN ();   ////////CLICK! SOLENOID OFF MAKES THE SHUTTER TO OPEN!
      delay (ShutterDelay3);
      //Serial.println ("FastFlash");
      FastFlash();       ////////TRIGGER FLASH
      shutterCLOSE (); ///////PICTURE TAKEN!
      return;         
      }
    }


}//end of void Click()

/*
float PhotoDelay1 = (ShutterSpeed[Read_DS2408_PIO(0)])  ; ;

PhotoDelay1 = (PhotoDelay1 / 2);

//unsigned long PhotoDelay2 = ((ShutterSpeed[Read_DS2408_PIO(0)]) / 2) ;

PhotoDelay1 =  PhotoDelay1 + (ShutterConstant - 1);

float PhotoDelay2 = (ShutterSpeed[Read_DS2408_PIO(0)])  ;

PhotoDelay2 = (PhotoDelay2 / 2) ;

float PhotoDelay3 = (ShutterConstant + (ShutterSpeed[Read_DS2408_PIO(0)]))-1;


 if ((ShutterSpeed[Read_DS2408_PIO(0)]) > 0)

        if (ExpDelay == 0){

          {
            if (Read_DS2408_PIO(2) ==  0) {  //S2 OFF
  
                                Serial.begin (9600);
                                Serial.println ("--------------------------------------------------TOTAL EXPOSURE CLICK S2 OFF:  ");
                                Serial.print ("---------------------CLICK:");
                                Serial.println (PhotoDelay1 + PhotoDelay2 +1 );

                                Serial.print (PhotoDelay1 );
                                Serial.print ( " ms + FLASH (1ms) + ");
                                Serial.print (PhotoDelay2);
                                Serial.println (" ms");
                                Serial.print ("PhotoDelay1:  ");
                                Serial.println (PhotoDelay1 );

                                Serial.print ("PhotoDelay2:  ");
                                Serial.println (PhotoDelay2 );

                                Serial.print ("ShutterConstant: ");
                                Serial.println (ShutterConstant);

                                Serial.print ("ShutterConstant - 1: ");
                                Serial.println (ShutterConstant - 1);
  
                                Serial.print ("ShutterSpeed: ");
                                Serial.println (ShutterSpeed[Read_DS2408_PIO(0)]);
                                Serial.print ("ShutterSpeed / 2: ");
                                Serial.println (ShutterSpeed[Read_DS2408_PIO(0)] / 2);
                                Serial.println ("--------------------------------------------------------");
    
                                shutterOPEN ();  //SOLENOID OFF MAKES THE SHUTTER TO OPEN!
        if (ExpDelay == 0){
          delay (PhotoDelay1); //ShutterSpeed-1 /2 part 1
          FastFlash();
          delay (PhotoDelay2); //ShutterSpeed-1 /2 part 1
          
//        delay (ShutterSpeed[Read_DS2408_PIO(0)]);                        // NOW COMES THE DELAY THAT IS THE PHOTO!
        }
        } else  if (Read_DS2408_PIO(2) ==  1) {
    Serial.begin (9600);
    Serial.println ("--------------------------------------------------TOTAL EXPOSURE CLICK S2 ON:  ");
    Serial.print ("---------------------CLICK:");
    Serial.println (PhotoDelay3 +1 );

    Serial.print (PhotoDelay3 );
    Serial.print ( "ms + FLASH + CLOSE");
    
    Serial.print ("PhotoDelay3:  ");
    Serial.println (PhotoDelay3 );

    Serial.print ("ShutterConstant: ");
    Serial.println (ShutterConstant);

    Serial.print ("ShutterConstant - 1: ");
    Serial.println (ShutterConstant - 1);

    
   // Serial.print ("ShutterSpeed: ");
   // Serial.println (ShutterSpeed[Read_DS2408_PIO(0)]);
    
   // Serial.print ("ShutterSpeed / 2: ");
   // Serial.println (ShutterSpeed[Read_DS2408_PIO(0)] / 2);

    
    Serial.println ("--------------------------------------------------------");
    
    shutterOPEN ();  //SOLENOID OFF MAKES THE SHUTTER TO OPEN!
        if (ExpDelay == 0){
          delay (PhotoDelay1); //ShutterSpeed-1 /2 part 1
          FastFlash();
          delay (PhotoDelay2); //ShutterSpeed-1 /2 part 1
          
//        delay (ShutterSpeed[Read_DS2408_PIO(0)]);                        // NOW COMES THE DELAY THAT IS THE PHOTO!


        }
        } else {

        delay (ExpDelay);                        // I THINK ExpDelay IS FOR AUTO MODE
        Serial.print("        actual delay: ");
        Serial.println (ExpDelay);
          
        }
        
        ////////CLICK!
    shutterCLOSE ();                                         //close the shutter
    return;
            }
            }
} //end of void Click()


*/



void Ydelay ()
{
  delay (80);
  //OPTION: SET ONLY 1 "MIDDLE GROUND" DELAY AT 80ms
  
/*                    if (Read_DS2408_PIO(2) ==  0) {
                    //NORMAL DELAY
                    delay (40);                                 //S3 is now open start Y-delay (40ms)
                   
                        } 
                        else 
                        {
                    delay (200);                              //LONG DELAY SELECTED 
                    //Serial.println ("LONG DELAY**************************************************************************************************************************************");     
                        }
*/                        
return;
}
//***************************************************************************************************************************************
void HighSpeedPWM ()
{

  

  //PWM high speed
  //one N_Mosfet powerdown
  //taken from: https://www.gammon.com.au/forum/?id=11504
/* 
  Timer 0
  input     T0     pin  6  (D4)
  output    OC0A   pin 12  (D6)
  output    OC0B   pin 11  (D5)

  Timer 1
  input     T1     pin 11  (D5)
  output    OC1A   pin 15  (D9)
  output    OC1B   pin 16  (D10)

  Timer 2
  output    OC2A   pin 17  (D11)
  output    OC2B   pin  5  (D3)
 
*/

  TCCR2A = bit (WGM20) | bit (WGM21) | bit (COM2B1); // fast PWM, clear OC2A on compare
  TCCR2B = bit (WGM22) | bit (CS20);         // fast PWM, no prescaler
  OCR2A =  n;                                // from table  
  OCR2B = ((n + 1) / 2) - 1;                 // 50% duty cycle
  
  //THIS AFFECTS OUTPUT 3 AND OUTPUT 11 (Solenoid1 and Solenoid2)

 }
//***************************************************************************************************************************************
