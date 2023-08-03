/*
 * pwm acoplado a la red 60/50 Hz 110/220 VAC
 * de un solo canal
 * con potenciometro
 * Este codigo varia la señal de salida hacia la etapa de potencia
 * en relacion con el voltaje de entrada en el pin A0
 */
//-----------------------------------------------------------------------
//!5V va conectado a 5V
//!GND va conectado a GND
//!pin 5 va conectado canal 1 
//!pin 2 va conectado a sync
//!pin central del potenciometro a pin A0 de el arduino
const byte ch1 = 5;  
int sensorPin = A0;
int c = 0;                                             
int p = 0;
int tope = 0;
int a = 0;
int g = 0;
//-----------------------------------------------------------------------
//!pin_2  interrupcion por cambio de estato
//!de un estado bajo a un estado alto
const byte interruptPin = 2;
volatile byte state = LOW;
//----------------------------------------------------------------------
//!
//!configuracion de interupcion por cambio de estado 
//!configuracion para habilitar la  escritura  en el ch1
void setup()
   {  
    Serial.begin(9600);
    pinMode(interruptPin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING);

      pinMode(ch1,OUTPUT);  
   }
//----------------------------------------------------------------------
//!cuando p = tope el pwm esta en 0%
//!cuando p = 0 pwm es 100%
void loop()
   { 
   digitalWrite(ch1,LOW);     
   }
 //---------------------------------------------------------------------
 //!funcion de interrupcion por cambio de estado de un pin
 //!while(pin2) sirve para mantener un contador
 //!siempre y cuando el estado del pin2 sea 1
 //!si c = p se envia un alto en ch1  prendiendo el bombillo
 //!al salir del while ch1 se le escribe un bajo apagando el bombillo
 void blink() {

   p = analogRead(sensorPin);             //!Tomar valor analogo
   p = map(p, 0, 1023, 0, tope);          //!Ecuacion de la recta
   c = 0;
  
  while(bitRead(PIND,2)){
    
    if (p < g){
    if(c >= p)digitalWrite(ch1,HIGH);
    }
    c++;  
    
    }
  
    tope = c;
    a = (tope * 2)/100;
    g = tope - a;                         //! 98% del ciclo util 
    digitalWrite(ch1,LOW); 

 }
  
 //---------------------------------------------------------------------
 // Compilado en Arduino 1.8.5
 // Elaborado por:
 // SUTAGAO
