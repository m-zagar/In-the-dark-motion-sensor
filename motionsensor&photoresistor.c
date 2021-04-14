#define F_CPU 7372800UL
#define dayToNight 800

#include <avr/io.h>
#include <util/delay.h>

void sensorDetect() {
  //Check for movement
  if ((PINC & (1 << 0))) {
    //Turn on LED if there is movement
    PORTA = 0x01;
    _delay_ms(1);

  } else {
    //Reset LED if no movement
    PORTA = 0xfe;
  }

}

int main() {
  DDRA = 0xfe; //Set LEDS 1-7 for output
  PORTA = 0xfe;
  DDRC = 0x00; //Set PORTC for PIR
  PORTC = 0x00;
  uint16_t adc;

  ADMUX = _BV(REFS0);
  ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1); //ADC config

  while (1) {
    ADCSRA |= _BV(ADSC);

    while (!(ADCSRA & _BV(ADIF)));
    adc = ADC; //Variable for saving ADC output
    if (adc > dayToNight) {
      sensorDetect(); //Activate sensor if light is low enough

    } else {
      PORTA = 0xfe; //Turn off LEDS if light too high
    }
    _delay_ms(100); //Delay between ADC changes

  }

  return 0;
}
