/*
  Practica 2 - Periféricos y dispositivos de interfaz humana
              Ejercicio 1 - Semáforos
              José Luis Fernández Aguilera - 18/04/2016

  Vector semaforo1 y semáforo2 que contienen un vector de 3 enteros.
  Los cuales definen los pines a los que se conectarán los leds del semaforo.
  0 -> Led Rojo.
  1 -> Led Ambar o Amarillo.
  2 -> Led Verde.
  Pines: 
   * Semáforo 1 
     - Pin 3 Rojo
     - Pin 4 Amarillo
     - Pin 5 Verde
   * Semáforo 2 
     - Pin 6 Rojo
     - Pin 7 Amarillo
     - Pin 8 Verde
   * Boton 1 pin 2
   * Boton 2 pin 9
*/
int semaforo1[3] = {3, 4, 5}; //Rojo, amarillo, verde
int semaforo2[3] = {6, 7, 8};

// Enteros que almacenan puerto de arduino que se usará para los interruptores.
int boton1 = 2, boton2 = 9;

// Variables booleanas de control del estado de la ejecución.
// La variable manual determina el modo de ejecución automático cada cierto tiempo o manual, volatile por el uso de interrupciones.
// La variable estado controla el estado de ambos semáforos. 
volatile bool manual = false;
int estado = true;

void setup() {
  for(int i=0; i<3; ++i){
    pinMode(semaforo1[i], OUTPUT);
    pinMode(semaforo2[i], OUTPUT);
  }
  pinMode(boton1, INPUT);
  pinMode(boton2, INPUT);
  // Establecemos un punto de interrupción en el arduino sobre el botón 1 (pin 2)
  // Así cada vez que pulsemos el botón 1 se llamará a la función cambiarModo()
  attachInterrupt(digitalPinToInterrupt(boton1), cambiarModo, RISING);
  Serial.begin(9600);
}

// Si estamos en modo automático los semáforos cambian de estado constantemente.
// Si estamos en modo manual los semáforos solo cambian de estado cuando se pulse el botón 2.
void loop() {
  if(!manual){
    Serial.println("modo manual");
    cambioSemaforo(estado);
    estado = !estado;
  }else{
    Serial.println("modo auto");
    if(digitalRead(boton2) == HIGH){
      Serial.println("pulsado b2");
      cambioSemaforo(estado);
      estado = !estado;
    }
  }
}

// Función que cambia el estado de las luces de los semáforos
// Si el modo es true el semáforo 1 quedará en verde y el semáforo 2 en rojo
// Si el modo es false el semáforo 1 quedará en rojo y el semáforo 2 en verde.
void cambioSemaforo(bool mode){
  if(mode){
    digitalWrite(semaforo1[1], HIGH);
    digitalWrite(semaforo1[2], LOW);
    delay(500);
    
    digitalWrite(semaforo1[0], HIGH);
    digitalWrite(semaforo1[1], LOW);
    digitalWrite(semaforo2[2], HIGH);
    digitalWrite(semaforo2[0], LOW);
    delay(3000);
  }else{    
    digitalWrite(semaforo2[1], HIGH);
    digitalWrite(semaforo2[2], LOW);
    delay(500);
    
    digitalWrite(semaforo1[2], HIGH);
    digitalWrite(semaforo1[0], LOW);
    digitalWrite(semaforo2[0], HIGH);
    digitalWrite(semaforo2[1], LOW);
    delay(3000);
  }
}

// Función que cambia el modo de ejecución del programa alterando la variable manual.
void cambiarModo(){
  manual = !manual;
  Serial.println("Changing mode");
  delay(1000);
}
