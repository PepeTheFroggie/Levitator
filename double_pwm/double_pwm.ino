#define PWM_CT1A  9 //OC1A PB1
#define PWM_CT1B 10 //OC1B PB2
#define PWM_CT3A  1 //OC3A PD1 PF1 TX1
#define PWM_CT3B  2 //OC3B PD2 PF2

// Reg PMX0; bit TXD6 0=PD1 1=PD6; RXD5 0=PD0 1=PD5
// Reg PMX1; bit C3AC 0=PF1 1=AC0P -> D6 ?

int freq = 400;
int oldpwm = 0; 
int pwm = 60;

void ct_init()
{
  pinMode(PWM_CT1A,OUTPUT);
  pinMode(PWM_CT1B,OUTPUT);
  TCCR1A = (1<<COM1A1)+(1<<COM1B1)+(1<<COM1B0)+(1<<WGM11); 
  TCCR1B = (1<<WGM13)+(1<<CS10); // prescaler = 1; 
  ICR1  = freq;
  OCR1A = 100;
  OCR1B = 300;

  // LGT8F328
  //PMX1 |= (1<<C3AC);
  //DDRD |= (1<<PD6);
  DDRF |= (1<<PF1); // timer3 only
  DDRF |= (1<<PF2); // timer3 only
  TCCR3A = (1<<COM3A1)+(1<<COM3B1)+(1<<COM3B0)+(1<<WGM31); 
  TCCR3B = (1<<WGM33)+(1<<CS30); // prescaler = 1; 
  ICR3  = freq;
  OCR3A = 100;
  OCR3B = 300;
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200);
  UCSR0B &= ~(1<<TXEN0); // disable serial tx

  delay(100);
  ct_init();
}

bool up,down;

void goup()
{
      asm("push r16");
      asm("cli");
      asm("ldi  r16,0x10");
      asm("sts  0x81,r16");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("ldi  r16,0x11");
      asm("sts  0x81,r16");
      asm("sei");
      asm("pop r16");  
}

void godown()
{
      asm("push r16");
      asm("cli");
      asm("ldi  r16,0x10");
      asm("sts  0x91,r16");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("nop");
      asm("ldi  r16,0x11");
      asm("sts  0x91,r16");
      asm("sei");
      asm("pop r16");  
}

void loop()
{
  delay(20);
  if (oldpwm != pwm)
  {
    OCR1A = OCR3A = 100 + pwm;
    OCR1B = OCR3B = 300 - pwm;
  }

  if (Serial.available())
  {
    char ch = Serial.read();
    if      (ch == 'P') pwm++;
    else if (ch == 'p') pwm--;
    else if (ch == 'F') { freq++; ICR1  = freq; }
    else if (ch == 'f') { freq--; ICR1  = freq; }
    else if (ch == 'r') { up   = true; down = false; }
    else if (ch == 'z') { down = true; up   = false; }
    else if (ch == 't') { up = false; down = false; }
  }
  if (up) goup();
  if (down) godown();
}
