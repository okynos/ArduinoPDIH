/*
  Practica 2 - Periféricos y dispositivos de interfaz humana
              Ejercicio 3 - Altavoz
              José Luis Fernández Aguilera - 18/04/2016

  melody - Vector de enteros que representan las notas de la cancion de Mario Bross Underworld
  noteDurations - Vector de enteros del mismo tamaño que melody que representa las duraciones de las notas de melody.
  play - Variable booleana que indica el estado de la reproducción si se está reproduciendo o no, volatile por el uso de interrupciones.
  boton - Variable entera asociada al pin al que se conecta el botón para las interrupciones.
  Pines utilizados el 2 para el botón y el pin 8 para el Buzzer.
*/
#include "pitches.h"

//Underworld melody
int melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, 
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};

//Underwolrd tempo
int noteDurations[] = {
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18,18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

volatile bool play = true;
int boton = 2;
int buzzer = 8;

// Inicializamos el botón y su interrupción asociada, RISING cuando se incremente el voltaje del pin 2.
void setup() {
  pinMode(boton, INPUT);
  attachInterrupt(0, playPause, RISING);
  Serial.begin(9600);
}

void loop() {
    //Trozo de código extraido del ejemplo toneMelody y modificado.
    
    // Bucle que itera sobre las notas de la melodía:
    for (int thisNote = 0; thisNote < 56; thisNote++) {
      // Para calcular la duracion de la nota, toma un segundo
      // dividido por el tipo de nota.
      //p.e. un cuarto de nota = 1000 / 4, octavo de nota = 1000/8, etc.
      if(play){
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(buzzer, melody[thisNote], noteDuration);
    
        // Para distinguir las notas, se establece un minimo de tiempo entre notas.
        // La duración de la nota + 30% parece funcional bien:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // Paramos el tono que suena:
        noTone(buzzer);
      }
      else
        while(!play){}
    }
}

// Función que invierte la variable play para detener en un momento determinado la ejecución de la melodía.
void playPause(){
  play = !play;
  if(play)
    Serial.println("Play");
  else
    Serial.println("Pause");
  delay(1000);
}
