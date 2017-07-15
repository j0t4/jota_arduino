volatile unsigned long pps_cuenta = 0;
volatile unsigned long multiplicador = 0;
volatile unsigned long frecuencia = 0;

void gpsPPS()
{
  pps_cuenta++;
  if (pps_cuenta == 1)                           // Start counting the 2.5 MHz signal from Si5351A CLK0
  {
    TCCR1B = 7;                                  //Clock on rising edge of pin 5
  }
  else if (pps_cuenta == 65)                     //The 40 second gate time elapsed - stop counting
  {     
    frecuencia = TCNT1 + ( multiplicador << 16);//Calculate correction factor
    TCCR1A = 0;                                  //Turn off counter
    TCCR1B = 0; 
    TCNT1 = 0;                                   //Reset count to zero
    TIFR1  = 1;                                    //Reset overflow
    TIMSK1 = 1;                                    //Turn on overflow flag
    multiplicador = 0;
    pps_cuenta = 0;                                  //Reset the seconds counter
  }
}

ISR(TIMER1_OVF_vect)
{
  multiplicador++;
  //TIFR1 = (1<<TOV1); 
}

void setup() 
{
  
  Serial.begin(115200);
  Serial.println("\nHello.\n");
  
  //Set up Timer1 as a frequency counter - input at pin 5
  TCCR1B = 0;                                    //Disable Timer5 during setup
  TCCR1A = 0;                                    //Reset
  TCNT1  = 0;                                    //Reset counter to zero
  TIFR1  = 1;                                    //Reset overflow
  TIMSK1 = 1;                                    //Turn on overflow flag
  pinMode(5, INPUT);  // Este es el pin para contar el Timer1 de 16 bits
  pinMode(2, INPUT);  // Este es el pin para interrupir con el pps en INT0
  attachInterrupt(INT0, gpsPPS, RISING);

}

void loop()                     // run over and over again
{
    delay(60000);
    Serial.print(multiplicador);
    Serial.print("  -->  ");
    unsigned long frecuencia2 = (frecuencia >> 6);
    Serial.println(frecuencia2);

}
