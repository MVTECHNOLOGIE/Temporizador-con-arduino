/*Temporizador V1.0 M&V Technologie

//-----------Pines-----------//
LCD 16X2 "I2C" 
A4 = SDA
A5 = SCL
2 o D2 = Hora
3 o D3 = Minutos
4 o D4 = Segundos
6 O D6 = Inicio o Start

*/

//-------Incluimos Librerías-------//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  //https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library.git

LiquidCrystal_I2C lcd(0x27,16,2); //Seleccionamos el tipo de LCD a utilizar
//Si no te funciona "0x27" intenta con "0x3F" o "0x20"
//-------Definimos los pines a utilizar-------//

#define Buzzer 13
#define Relay 12
#define BotonI 6
#define BotonS 4
#define BotonM 3
#define BotonH 2

//-------Definimos Variables-------//

int Horas = 0;
int Minutos = 0;
int Segundos = 0;
int SegundosFINAL = 0;
int ValorH = 0; //Declaramos una variable en la cual guardaremos los valores leidos del pulsador
int ValorM = 0; //Declaramos una variable en la cual guardaremos los valores leidos del pulsador
int ValorS = 0; //Declaramos una variable en la cual guardaremos los valores leidos del pulsador


void setup(){ // aquí ponemos los comandos de la subrutina

pinMode(BotonH,INPUT_PULLUP); //Declaramos como entrada y activamos una resistencia interna
pinMode(BotonM,INPUT_PULLUP); //Declaramos como entrada y activamos una resistencia interna
pinMode(BotonS,INPUT_PULLUP); //Declaramos como entrada y activamos una resistencia interna
pinMode(BotonI,INPUT_PULLUP); //Declaramos como entrada y activamos una resistencia interna
pinMode(Buzzer,OUTPUT); //Declaramos como salida
pinMode(Relay ,OUTPUT); //Declaramos como salida

lcd.begin(16,2);//Iniciamos comunicación con el I2C
lcd.init(); //Inicializa el modulo adaptador LCD a I2C, esta función internamente configura e inicializa el I2C y el LCD.
lcd.backlight(); //Enciende la Luz del Fondo del LCD
lcd.clear(); //Borra la pantalla LCD y posiciona el cursor en la esquina superior izquierda (posición (0,0))

lcd.setCursor(0,0); //Posiciona el cursor al principio de la primera fila (posición (0,0))
lcd.print("  TEMPORIZADOR");  //Imprimimos en el LCD 
lcd.setCursor(0,1); //Posiciona el cursor al principio de la segunda fila (posición (0,0))
lcd.print("M&V TECHNOLOGIE"); //Imprimimos en el LCD 
delay(3000); //Espera de 3 Segundos "s"
lcd.clear(); //Borra la pantalla LCD y posiciona el cursor en la esquina superior izquierda (posición (0,0))
}


void loop(){//Bucle Infinito

while(digitalRead(BotonI)== HIGH){ //Mientras el botón este en 1 "Alto o HIGH"
                                   //Se ejecutara todo lo que se encuentre en el bucle While
                                   
ValorH  = digitalRead(BotonH); //Almacenamos los valores leidos del Pulsador
ValorM  = digitalRead(BotonM); //Almacenamos los valores leidos del Pulsador
ValorS  = digitalRead(BotonS); //Almacenamos los valores leidos del Pulsador

if(ValorH == LOW){ //Mientras el botón este en 0 "Bajo o LOW"
Horas = Horas +1;  //Horas aumentará un numero 01
if(Horas == 24)    //y si llega a 24
Horas=0;           //volvera a 0
delay(200);        //Espera de 0.2 Segundos "s" = 200 Milisegundos "ms"
}
if(ValorM == LOW){    //Mientras el botón este en 0 "Bajo o LOW"
Minutos = Minutos +1; //Minutos aumentará un numero 01
if(Minutos == 60)     //y si llega a 60
Minutos=0;            //volvera a 0
delay(200);           //Espera de 0.2 Segundos "s" = 200 Milisegundos "ms"
}
if(ValorS == LOW){      //Mientras el botón este en 0 "Bajo o LOW"
Segundos = Segundos +1;//Segundos aumentará un numero 01
if(Segundos == 60)      //y si llega a 60
Segundos=0;             //volvera a 0
delay(200);             //Espera de 0.2 Segundos "s" = 200 Milisegundos "ms"
}

lcd.setCursor(0,0);  //Posiciona el cursor al principio de la primera fila (posición (0,0))
lcd.print(" ESCOGER TIEMPO "); //Imprimimos en el LCD 
lcd.setCursor(4,1); //Posiciona el cursor en la cuarta columna de la segunda fila (posición (4,1))

if (Horas<10)     //Si Hora es menor a 10 
lcd.print("0");   //Imprimimos en el LCD
lcd.print(Horas); //Imprimimos la Variable Hora
lcd.print(":");   //Imprimimos en el LCD
                  //Quedaria = 00:
if (Minutos<10)      //Si Minutos es menor a 10
lcd.print("0");      //Imprimimos en el LCD
lcd.print(Minutos);  //Imprimimos la Variable Minutos
lcd.print(":");      //Imprimimos en el LCD
                  //Quedaria = 00:00
if (Segundos<10)     //Si Minutos es menor a 10
lcd.print("0");      //Imprimimos en el LCD
lcd.print(Segundos); //Imprimimos la Variable Segundos
}                 //Quedaria = 00:00:00

lcd.clear(); //Borra la pantalla LCD y posiciona el cursor en la esquina superior izquierda (posición (0,0))
delay(100);  //Espera de 0.1 Segundos "s" = 100 Milisegundos "ms"
SegundosFINAL = Segundos +(Minutos*60)+ (Horas*60*60);


while(SegundosFINAL>0){ //Si "SegundosFINAL" es mayor a 0
                        //Se ejecutara todo lo que se encuentre en el bucle While
SegundosFINAL--;  //Se quitaran segundos
Horas = (SegundosFINAL / 3600); // "Horas" es igual a "SegundosFINAL" dividido para 3600 
Minutos = (SegundosFINAL /60) % 60; // "Minutos" es igual a "SegundosFINAL" dividido para 60 por el % de 60
Segundos = SegundosFINAL % 60; //"Segundos" es igual a "SegundosFINAL" %60

lcd.setCursor(0,0);             //Posiciona el cursor al principio de la primera fila (posición (0,0))
lcd.print("TIEMPO  ESTIMADO"); //Imprimimos en el LCD
digitalWrite(Relay,HIGH);       //Enciende Relay
delay(1000);                    //Espera de 1 Segundos "s"
lcd.setCursor(4,1); //Posiciona el cursor en la cuarta columna de la segunda fila (posición (4,1))

if (Horas<10)     //Si Hora es menor a 10 
lcd.print("0");   //Imprimimos en el LCD
lcd.print(Horas); //Imprimimos la Variable Hora
lcd.print(":");   //Imprimimos en el LCD
                  //Quedaria = 00:
if (Minutos<10)      //Si Minutos es menor a 10
lcd.print("0");      //Imprimimos en el LCD
lcd.print(Minutos);  //Imprimimos la Variable Minutos
lcd.print(":");      //Imprimimos en el LCD
                  //Quedaria = 00:00
if (Segundos<10)     //Si Minutos es menor a 10
lcd.print("0");      //Imprimimos en el LCD
lcd.print(Segundos); //Imprimimos la Variable Segundos
                  //Quedaria = 00:00:00
                  
if (SegundosFINAL == 0){ //Si "SegundosFINAL" llega a 0 entonces se
lcd.clear(); //Borra la pantalla LCD y posiciona el cursor en la esquina superior izquierda (posición (0,0))
lcd.setCursor(3,0);  //Posiciona el cursor en la quinta columna de la primera fila (posición (5,0))
lcd.print(" SU TIEMPO"); //Imprimimos en el LCD
lcd.setCursor(1,1);  //Posiciona el cursor en la tercera columna de la primera fila (posición (3,1))
lcd.print(" A FINALIZADO"); //Imprimimos en el LCD
digitalWrite(Relay,LOW);   //Apaga Relay
digitalWrite(Buzzer,HIGH); //Enciende Buzzer
delay(2000); //Espera de 2 Segundos "s"
digitalWrite(Buzzer,LOW); //Apaga Buzzer
lcd.clear(); //Borra la pantalla LCD y posiciona el cursor en la esquina superior izquierda (posición (0,0))
delay(200); //Espera de 0.2 Segundos "s" = 200 Milisegundos "ms"
}
}
}
