
  void Dongle(int Exposure) 
    {
                                        #if SIMPLEDEBUG 
                                        Serial.print ("                                                 Dongle:");
                //                        Serial.println (DongleSlot);
                                        #endif


//=========================================================================================================================================================                   
     // CASE 0 FORCED EJECTION TO SAFEGUARD SOLENOID#1 IN MULTIPLE EXPOSURES AFTER 1 MINUTE (60000ms)       
//=========================================================================================================================================================

unsigned long currentMillisTimer = millis();
           
           if ((currentMillisTimer-DoubleExposureTimer) >= 300000 && shots >= 1)
         //F***K it, if I break my camera, I need longer for double exposures!! Changed forced expulsion to 5 minutes
         
         {
           eepromUpdate ();

            shots = 0;
 
             
            mirrorDOWN ();

            delay (50);                             //100-->50 AGAIN is this delay necessary?
            
            
            
            shutterOPEN();    
           
           Write_DS2408_PIO (6, 0); 
         }  else if ((currentMillisTimer-DoubleExposureTimer) >= 60000 && shots >= 1)

         //F***K it, if I break my camera, I need longer for double exposures!! Changed light up to 1 minute

         {
          Write_DS2408_PIO (6, 1); 
          
         } 


//=========================================================================================================================================================                   
     // CASE 1 NORMAL OPERATION NORMAL OPERATION NORMAL OPERATION NORMAL OPERATION NORMAL OPERATION NORMAL OPERATION NORMAL OPERATION NORMAL OPERATION            
//=========================================================================================================================================================

    
    if (takePicture == true  && switch1 ==  0 && shots == 0)    //NORMAL OPERATION
    {
      

         if ((ShutterSpeed[selector] == (AUTO100)))
                            {
                              output_compare = 490; //OPTION magic number for ISO 125 or 160 or whatever it is
                              Serial.println ("A1");
                                AutoExposure();
                                      byte PictureType = 1;                    
                                      eepromUpdate ();
                                      shots = shots++;  
                              return;
                            }
                            if ((ShutterSpeed[selector] == (AUTO600)))
                            {
                              output_compare = 200; //OPTION magic number for ISO 600
                               Serial.println ("A6");
                              AutoExposure();
                                      byte PictureType = 6;                    
                                      eepromUpdate ();
                                      shots = shots++;  
                              return;
                            }                  
                          
                          
/*                          #if SIMPLEDEBUG
                          Serial.println ("take Manual picture");
                          #endif
                    byte PictureType = 0;                    
//                    eepromUpdate ();
    
                  shutterCLOSE (); 

//                  delay (200); //added to fix bad photos
                  delay (100); //added to fix bad photos WITH LESS delay
                                    
                  mirrorUP();   //Motor Starts: MIRROR COMES UP!!!
                  while (digitalRead(S3) != HIGH)            //waiting for S3 to OPEN
                   ;
                  Ydelay();
                  

                  Click (0);  
                  
//                  delay (200);                             //AGAIN is this delay necessary?
                  mirrorDOWN ();                          //Motor starts, let bring the mirror DOWN
                  delay (50);                             //AGAIN is this delay necessary?
                  //CHANGED 200->50

                 shutterOPEN();
                 eepromUpdate ();
                 shots = 0;  

                 return;  
 */   
     } // END of  if (takePicture == true  && Read_DS2408_PIO(1) ==  0 && shots == 0)    //NORMAL OPERATION
    
//=========================================================================================================================================================                   
     // CASE 2 DOUBLE EXPOSURE FIRST SHOT: MIRROR DOWN AND FIRST PICTURE (CLICK: SHUTTER OPERATION REMAINING CLOSED)           
//=========================================================================================================================================================

    
     if (takePicture == true && switch1 ==  1 && shots == 0)    //DOUBLE EXPOSURE and RED BUTTON PRESSED (S1) FIRST SHOT!!!!
      {   
/*
     EEPROM.get (13,ActualPicture);
          //CurrentPicture = (CurrentPicture+1);
*/    
          byte PictureType = 0;
         
          DoubleExposureTimer = millis();
    
          shutterCLOSE ();  // I CLOSE THE SHUTTER
          
          mirrorUP();                                 //Motor Starts: MIRROR COMES UP!!!

          while (digitalRead(S3) != HIGH)            //waiting for S3 to OPEN
            ;
          Ydelay();                         //S3 is now open start Y-delay (40ms)
          delay (500);
                  
          Click (0);                 // NOW I am going to take the picture: SMILE!

          delay (500);            //debounce will go here
          shots++;
          return;

          } // end of  if (takePicture == true && Read_DS2408_PIO(1) ==  1 && shots == 0)    //DOUBLE EXPOSURE and RED BUTTON PRESSED (S1) FIRST SHOT!!!!

//=========================================================================================================================================================        
         // CASE 3 DOUBLE EXPOSURE ULTERIOR SHOTS: NO MOTOR OPERATION JUST PICTURE (CLICK: SHUTTER OPERATION REMAINING CLOSED) 
//=========================================================================================================================================================


         
         if (takePicture == true && switch1 ==  1 && shots >= 1)    //DOUBLE EXPOSURE and RED BUTTON PRESSED (S1) ULTERIOR SHOTS!!!!
          {
 
                 Click(0);

          delay (500); //debounce will go here
          
          shots++;
                    return;
          
          } // end of  if (digitalRead(S1) == LOW && Read_DS2408_PIO(1) ==  1 && shots >= 1)    //DOUBLE EXPOSURE and RED BUTTON PRESSED (S1) ULTERIOR SHOTS!!!!

          
//=========================================================================================================================================================          
          // CASE 4 PICTURE EXPULSION AFTER DOUBLE EXPOSURE: MIRROR DOWN AND SHUTTER OPENING (NO PICTURE TAKEN)
//=========================================================================================================================================================
          
         if (takePicture == true && switch1 ==  0 && shots >= 1)  //Was in DOUBLE EXPOSURE MODE but NOW is back to NORMAL
          {
            
            eepromUpdate ();

            shots = 0;

            Write_DS2408_PIO (6, 0);
             
            mirrorDOWN ();

            delay (50);                             //AGAIN is this delay necessary? 100-->50
                  delay (500);

            shutterOPEN();    
 
            return;
            
           }// end of if (takePicture == true && Read_DS2408_PIO(1) ==  0 && shots >= 1)  //Was in DOUBLE EXPOSURE MODE but NOW is back to NORMAL

    }
     
    
 
