
void cli(void) { }
void sei(void) { }

#define ISR(name) void name()

#define PB7 7
#define F_CPU 16000000L
#define TXEN0 3
#define RXEN0 4
#define RXCIE0 7

#define DDA6 6
#define DDA4 4
#define DDC7 7
#define DDC1 1
#define PG1 1

#define PD7 7

#define TXEN1 3
#define RXEN1 4
#define RXCIE1 7

#define TXEN2 3
#define RXEN2 4

#define RXCIE2 7

#define TXEN3 3
#define RXEN3 4
#define RXCIE3 7

#define UCSZ00 1
#define UCSZ01 2
uint8_t UCSR0C;

#define UCSZ10 1
#define UCSZ11 2
uint8_t UCSR1C;

#define UCSZ20 1
#define UCSZ21 2
uint8_t UCSR2C;

#define UCSZ30 1
#define UCSZ31 2
#define PD1 1

uint8_t UCSR3C;

uint8_t UCSR1B; 
#define UDRIE1 5
uint8_t UCSR2B; 
#define UDRIE2 5
uint8_t UCSR3B; 
#define UDRIE3 5
uint8_t UCSR0B; 
#define UDRIE0 5
uint8_t UCSR0A;
uint8_t UCSR1A;
uint8_t UCSR2A;
uint8_t UCSR3A;

#define UDRE0 5
#define UDRE1 5
#define UDRE2 5
#define UDRE3 5
void _delay_ms(int a) { UNUSED(a); }
void _delay_us(int a) { UNUSED(a); }
uint8_t DDRB;
uint8_t PORTB;

uint8_t UDR0;
uint8_t UCSR0B;
uint8_t UBRR0H;
uint8_t UBRR0L;

uint8_t UDR1;
uint8_t UCSR1B;
uint8_t UBRR1H;
uint8_t UBRR1L;

uint8_t UDR2;
uint8_t UCSR2B;
uint8_t UBRR2H;
uint8_t UBRR2L;

uint8_t UDR3;
uint8_t UCSR3B;
uint8_t UBRR3H;
uint8_t UBRR3L;

uint8_t DDRA;
uint8_t DDRC;

uint8_t PORTC;
uint8_t PORTA;

uint8_t DDRG;
uint8_t PORTG;


uint8_t DDRD;
uint8_t PORTD;
uint8_t PIND;
uint8_t PINC;

uint8_t DDRF;
uint8_t PORTF;
uint8_t PINF;
#define ISC21 5
#define ISC20 4
#define PA7 7
#define PL1 1
#define ADC15D 7
uint8_t PINL;
uint8_t DDRL;
uint8_t PORTL;
#define MUX0 0
#define MUX2 2
#define INT2 2
uint8_t PINB;
uint8_t EIMSK;
uint8_t EICRA;
#define PB1 1
#define PB2 2
#define PB3 3 
#define PB0 0 

#define  PL6 6
#define  PL7 7


#define PF1 1
#define PF2 2
#define PF3 3
#define PD0 0
#define PD1 1
#define PD2 2

uint8_t DDRE;
uint8_t PORTE;

#define PE5 5
#define PG5 5
#define PH5 5
#define PH4 4

uint8_t DDRH;
uint8_t TCCR1B;
uint16_t OCR1A;
uint8_t TIMSK1;
uint8_t PORTH;

#define WGM12 3
#define CS11 1
#define OCIE1A 1

uint8_t DDRK;
uint8_t PORTK;
uint8_t TCNT1;
uint8_t PINK;

#define PK6 6
#define PK5 5
#define PK7 7
#define PK4 4

#define CS12 2

#define PB6 6
#define PB5 5
#define PB4 4

 uint8_t ADMUX;
  uint8_t ADCSRA;
  uint8_t ADCSRB;
 uint8_t ADCL;
  uint8_t ADCH;
uint8_t DIDR2;
#define REFS0 6
#define ADEN 7
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0
#define MUX5 3
#define ADC9D 1
#define ADC8D 0
#define PK1 1
#define PK2 2
#define ADSC 6


uint8_t TCCR3A;
uint8_t TCCR3B;
uint8_t OCR3A;
uint8_t TIMSK3;
uint8_t OCR3B;
uint8_t OCR3C;

#define CS32 2
#define CS30 0
#define OCIE3A 1
#define OCIE3B 2
#define OCIE3C 3


uint8_t ADCSRA;
uint8_t ADCL;
uint8_t ADCH;
#define ADC10D 2
#define MUX1 1
#define REFS0 6
#define PK1 1
#define PK0 0

//hc-sr04
//Vcc
uint8_t DDRC;
uint8_t  PORTC;
#define  PC0 0

//GND
uint8_t  DDRC; 
#define  PC6 6

//Trigger
uint8_t  DDRC;
#define  PC2 2
uint8_t  PORTC;

//Echo
uint8_t  PINC;
#define PC4 4


//pir
//Vcc

uint8_t  PORTK;
#define   PK5 5

//GND
uint8_t  DDRK; //DDRK
#define  PK3 3 //PK7

//signal

#define  PK4 4

uint8_t PINK;

#define PCIE2 2
#define PCINT20 4
uint8_t PCICR;
uint8_t PCMSK2;


//tone 
#define PA1 1
uint8_t TCCR2A;
uint8_t TCCR2B;
uint8_t TCNT2;

        // Busy-wait
#define CS22 2
#define CS21 1
#define CS20 0


#define PE3 3
#define PC7 7
#define PA6 6
#define PA4 4