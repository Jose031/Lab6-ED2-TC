//********************************************************************************
// Universidad del Valle de Guatemala
// BE3015: Electrnónica Digital 2
// José David Méndez 19380
// Laboratorio 6
//********************************************************************************

//**********************************************************************************************************************
// Librerías
//**********************************************************************************************************************
#include <Arduino.h>
//**********************************************************************************************************************
// Defincion de Pines
//**********************************************************************************************************************
#define pot2 PE_5
#define btn1 PF_0
#define btn2 PF_4

// Definición de las varaibles de salida de los leds con sus respectivo numero de pin
#define ledR PF_1
#define ledV PF_3
#define ledA PF_2

//**********************************************************************************************************************
// Prototipo de Funciones
//**********************************************************************************************************************
void voltaje1(void); // Función para la impresión del voltaje del potenciometro 1
void voltaje2(void); // Función para la impresión del voltaje del potenciometro 2
void UPC(void);
void USART(void);    //Función de comunicación USART
void funcionamientoLEDS(void);
//**********************************************************************************************************************
// Variables Globales
//**********************************************************************************************************************
String voltaje = "";
int voltajeB = 0;
int contador = 0;
//**********************************************************************************************************************
// Configuracion
//**********************************************************************************************************************
void setup()
{
  // Velocidad a la que trabaja la comunicación serial
  Serial.begin(115200);
  Serial3.begin(115200);
  //Definicion de entradas
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(ledR, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(ledA, OUTPUT);

}
//**********************************************************************************************************************
// LOOP
//**********************************************************************************************************************
//**********************************************************************************************************************
// Fuinciones
//**********************************************************************************************************************
void voltaje1(void) // Voltaje potenciometro 2
{
  if (Serial3.available() > 0) // Condición que permite verficar si hay bytes disponibles en el buffer de registro
  {
    voltaje = Serial3.readStringUntil('\n'); //Lectura de valor ADC enviado por el ESP32
  }

}
void voltaje2(void) // Voltaje potenciometro 2
{
  voltajeB = analogRead(pot2);
  Serial3.println(analogRead(pot2));//Forma de enviar el valor ADC de la tiva c al ESP32
  delay(100);
}
void UPC(void) {
  if (digitalRead(btn1) == 0) { //Condicion que permite aumentar el valor DEL contador
    contador++;
    if (contador > 255)
    { // Condición que establece que el contador no se mayor al numero de condiciones que se tiene.
      contador = 0;
    }
  }
  if (digitalRead(btn2) == 0) { //Condicion que permite decrementar el valor del contador 
    contador--;
    if (contador < 0)
    { // Condición que establece que el contador no se mayor al numero de condiciones que se tiene.
      contador = 0;
    }
  }
  Serial3.println(contador); //Forma de enviar el valor del contador al ESP32
}
void funcionamientoLEDS(void) {

  analogWrite(ledR, voltaje.toInt());
  analogWrite(ledV, voltajeB);
  analogWrite(ledA, contador);

}
