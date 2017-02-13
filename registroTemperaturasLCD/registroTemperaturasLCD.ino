/*
  Practica 2 - Periféricos y dispositivos de interfaz humana
              Ejercicio 5 - TemperaturaLCD
              José Luis Fernández Aguilera - 18/04/2016

  temp - Variable entera que almacena el puerto analógico por el que se lee el valor de temperatura.
  eeAddress - Variable entera que almacena la dirección de memoria en la que vamos a almacenar los datos de temperatura.
  eeSize - Variable que almacena el número de Bytes restantes de la memoria EEPROM.
  temperature - Variable de tipo flotante que almacena el valor real de la temperatura una vez analizada.
  Pines utilizados el pin analógico A0 para el sensor de temperatura y los pines 12, 11, 5, 4, 3 y 2 para los datos relativos a la pantalla LCD
*/
#include <EEPROM.h>
#include <LiquidCrystal.h>

// Constante que define el tiempo de medición de temperatura.
#define interval 1000

int temp = A0;
int eeAddress = 0;
int eeSize = 1024;
float temperature;


// Inicializar la librería de LCD con los números de la interface que hemos conectado al arduino.
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(temp, INPUT);
  Serial.begin(9600);
  
  // Establecemos el número de columnas y de filas que tiene nuestra pantalla.
  lcd.begin(16, 2);
  // Imprimimos el mensaje estático en el LCD.
  lcd.print("Temp.: ");
  lcd.setCursor(0, 1);
  lcd.print("Lecturas: ");
}

/*
 * Funcionamiento general
 * Si no hay nada en el buffer serie del arduino y si el tamaño de la EEPROM es mayor que 0
 * Leemos la temperatura del componente, la transformamos y la escribimos en la EEPROM y simultáneamente en la pantalla LCD junto con las lecturas.
 * Si alguna de estas condiciones no se cumpliese analizariamos el buffer de escritura del serial para leer un carácter
 * Si el carácter leído es una r/R se escribe por pantalla todas las temperaturas almacendas en la EEPROM hasta el momento.
 * Si el carácter leído es una w/W se escribe en la EEPROM del arduino el último valor registrado.
 * Si el carácter leído es b/B se reinicia la posición de escritura y el contador de tamaño (Se eliminan todos los valores de la EEPROM).
 * Si el carácter leído es s/S se imprime por el puerto serie toda la información asociada al tamaño y escrituras en la EEPROM.
 * Finalmente si no queda espacio en la EEPROM se informa por el puerto serie que la memoria EEPROM está completa.
 * 
 */
void loop() {
  if(Serial.available() <= 0 && eeSize > 0){
    float lecture = analogRead(temp);
    temperature = ( (((lecture*5)/1024)-0.5)/0.01 );  

    EEPROM.put(eeAddress, temperature);
    eeSize -= sizeof(float);
    eeAddress += sizeof(float);
    
    lcd.setCursor(7, 0);
    lcd.print(temperature);
    lcd.print(" C  ");
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(10, 1);
    // print the number of seconds since reset:
    lcd.print(eeAddress/sizeof(float));
  }else{
    char character = Serial.read();
    if(character == 'r' || character == 'R'){
      for(int i=0; i<eeAddress; i += sizeof(float)){
        float dataRead;
        Serial.print(EEPROM.get(i, dataRead));
        Serial.println();
      }
      Serial.println();
    }
    if(character == 'w' || character == 'W'){
      EEPROM.put(eeAddress, temperature);
      eeSize -= sizeof(float);

      eeAddress += sizeof(float);
      Serial.print("Temperature ");
      Serial.print(temperature);
      Serial.println(" stored in EEPROM");
    }
    if(character == 'b' || character == 'B'){
      eeAddress = 0;
      eeSize = 1024;
    }
    if(character == 's' || character == 'S'){
      Serial.print(eeSize);
      Serial.println(" Bytes left in EEPROM");
      Serial.print(eeAddress / sizeof(float));
      Serial.println(" Readings stored in EEPROM");
      Serial.print(eeSize / sizeof(float));
      Serial.println(" Writings left in EEPROM");
    }
  }
  if(eeSize == 0)
    Serial.println("EEPROMM size is full please erase data.");
  delay(interval);
}

