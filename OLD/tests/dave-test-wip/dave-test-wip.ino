/*
  Polaroid Light Meter
  Dave Walker
  16th February 2019
  For use with the TSL235R sensor, connected to digital pins 3,4,5
*/
const int output_compare = 8192;    // How many pulses before triggering 
                  // interrupt
unsigned int old_millis;            // Temporary variable for disp. 
                  // time between interrupts

void setup()
{
  Serial.begin(9600);                    // Start serial monitor

  cli();                       // Stop interrupts
  TCCR1A=0;                    // Reset timer/counter control register A
  bitSet(TCCR1B ,CS12);        // Counter Clock source is external pin
  bitSet(TCCR1B ,CS11);        // Clock on rising edge
  OCR1A = output_compare;      // Set output compare value
  TIMSK1 |= (1 << TOIE1);      // Enable compare A Match Interrupt
  TIMSK1 |= (1 << OCIE1A);     // enable compare B Match Interrupt
  sei();                       // Restart interrupts
 }

void loop()
{                                       // Nothing to see here
}

ISR(TIMER1_COMPA_vect)         // Output Compare interrupt service routine 
{
  Serial.print("Time since last event = ");
  Serial.print(millis()-old_millis);
  Serial.println(" ms");
  TCNT1 = 0;                   // Reset the hardware counter
  old_millis = millis();
}

ISR(TIMER1_OVF_vect)           // Overflow Flag interrupt service routine 
{
  Serial.print("Overflow Occured!");
  TCNT1 = 0;                   // Reset the hardware counter
}
