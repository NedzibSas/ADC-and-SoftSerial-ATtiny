#include <SoftSerial.h>     
#include <TinyPinChange.h>  

SoftSerial ASerial(2, 3); // RX, TX

uint8_t adc_lobyte; // to hold the low byte of the ADC register (ADCL)
uint16_t raw_adc;
void setup()  
{
  ASerial.begin(9600);
  ADMUX =
            (0 << ADLAR) |     // do not left shift result (for 10-bit values)
            (0 << REFS2) |     // Sets ref. voltage to internal 1.1V, bit 2
            (1 << REFS1) |     // Sets ref. voltage to internal 1.1V, bit 1   
            (0 << REFS0) |     // Sets ref. voltage to internal 1.1V, bit 0
            (0 << MUX3)  |     // use ADC1 for input (PB2), MUX bit 3
            (0 << MUX2)  |     // use ADC1 for input (PB2), MUX bit 2
            (1 << MUX1)  |     // use ADC1 for input (PB2), MUX bit 1
            (0 << MUX0);       // use ADC1 for input (PB2), MUX bit 0

  ADCSRA = 
            (1 << ADEN)  |     // Enable ADC 
            (1 << ADPS2) |     // set prescaler to 64, bit 2 
            (1 << ADPS1) |     // set prescaler to 64, bit 1 
            (1 << ADPS0);      // set prescaler to 64, bit 0  
}
int var=0;
void loop()
{
  ADCSRA |= (1 << ADSC);
  adc_lobyte = ADCL;
  raw_adc = ADCH<<8 | adc_lobyte;
  ASerial.println(raw_adc);
  delay(10);
}
