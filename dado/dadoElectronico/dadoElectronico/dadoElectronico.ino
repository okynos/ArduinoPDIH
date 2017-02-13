/*
  Practica 2 - Periféricos y dispositivos de interfaz humana
              Ejercicio 2 - Dado Electrónico
              José Luis Fernández Aguilera - 17/04/2016

  led - Vector de enteros que almacena los leds verticales, pines 2, 3, 4, 6, 7 y 8 para los leds de las filas.
  ledSize - Variable entera que almacena el tamaño del vector.
  centerLed - Variable que almacena el pin del led central, pin utilizado el 5.
  boton - Variable que almacena el pin del boton, pin utilizado el 9.
  rodar - Variable booleana que define si el dado está rodando.
*/
int led[] = {2, 3, 4, 6, 7, 8};
int ledSize = 6, centerLed = 5, boton = 9;
bool rodar = false;

// Se establecen todos los pines a su modo correspondiente y se encienden los 7 leds a modo indicativo.
void setup() {
  pinMode(boton, INPUT);
  pinMode(centerLed, OUTPUT);
  for(int i=0; i<ledSize; ++i){
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }
  digitalWrite(centerLed, HIGH);
  randomSeed(analogRead(0));
  Serial.begin(9600);
}

// Funcionamiento
// Si el boton es pulsado se procede a rodar el dado, si el botón no se pulsa no ocurre nada.
void loop() {
  if(digitalRead(boton) == HIGH)
    rodar = true;
  
  if(rodar){
    rodarDado();
    rodar = false;
  }
}

// Enciende los leds dependiendo del número que se le pase como argumento.
void encenderDado(int numero){
  switch(numero){
    case 1:
      digitalWrite(centerLed, HIGH);
    break;
    case 2:
      digitalWrite(led[5], HIGH);
      digitalWrite(led[0], HIGH);
    break;
    case 3:
      digitalWrite(led[5], HIGH);
      digitalWrite(led[0], HIGH);
      digitalWrite(centerLed, HIGH);
    break;
    case 4:
      digitalWrite(led[0], HIGH);
      digitalWrite(led[5], HIGH);
      digitalWrite(led[2], HIGH);
      digitalWrite(led[3], HIGH);      
    break;
    case 5:
      digitalWrite(led[0], HIGH);
      digitalWrite(led[5], HIGH);
      digitalWrite(led[2], HIGH);
      digitalWrite(led[3], HIGH); 
      digitalWrite(centerLed, HIGH);
    break;
    case 6:
      for(int i=0; i<ledSize; ++i)
          digitalWrite(led[i], HIGH);
    break;
      }
}

// Función que rueda el dado 5 veces siendo la quinta vez el número definitivo
// Primero apaga todos los leds y los enciende en función del número rodado.
// El número seleccionado se muestra por el serial.
void rodarDado(){  
  for(int i=0; i<5; ++i){
    for(int i=0; i<ledSize; ++i){
      digitalWrite(led[i], LOW);
    }
    digitalWrite(centerLed, LOW);
    int randNumber = random(1, 7);
    if(i == 4)
      Serial.println(randNumber);
    encenderDado(randNumber);
    delay(300);
  }
}

