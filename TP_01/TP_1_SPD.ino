/*

Arduino - Trabajo Práctico 01

Antes de empezar lea lo siguiente:
Respetar las reglas de estilo en cuanto a la documentación del código, se prolij@. Recuerda que cuando
programamos, solo dios y vos saben que quisiste escribir, en cambio si no sos prolij@, cuando quieras ver el
código dentro de varios años solo dios sabrá que codeaste (Con suerte).

1. Trabajo Práctico 01: Cronómetro Binario

Crear un circuito con los conocimientos y buenas prácticas aprendidas el cual siga las
siguientes directivas:
1.1. Al iniciar la simulación, todos los led deben comenzar apagados.
1.2. Cada 1 segundo que transcurra, se deben encender los led de acuerdo al número que
representan.
1.3. El numero 15 (0000001111) se representaria encendiendo los leds AMARILLO y NARANJA.
1.4. Al pasar al número 16 (0000010000), se deben apagar todos los led anteriores y
encenderse uno de los leds VERDES. (Nótese, en el ejemplo los 0 representan los led
apagados y los 1 los led encendidos).
1.5. Al presionar el botón START, debe iniciar el cronómetro, al volver a presionarlo hará que la
secuencia se detenga. (Como si se hubiese presionado pausa).
1.6. Al presionar el botón RESET, el cronómetro debe reiniciarse y arrancar de 0.
1.7. El número máximo a mostrar (tanto con leds como por consola) será el 1023 (Todos los leds
prendidos) al pasarlo se deberán apagar los leds y no mostrar nada por consola.
1.8. Tip: Modularizar la función que controla el encendido de los LEDS y de ser posible, todo el
código para evitar repetir líneas. Usar millis para controlar el tiempo del contador para que el
cambio de los leds encendidos sea perceptible para el ojo humano y documentar cada
función creada en el código. (Un breve comentario que diga que es lo que hace esa
función).
*/


void dibujar(unsigned long);
void apagarLeds();

void setup()
{
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  
  Serial.begin(9600);
}


unsigned long millisAntes=0;
unsigned long millisAhora=0;
unsigned long tiempoTotal = 0;


unsigned long termino;
int millisPausa;
int botonAntes=LOW;
int botonResetAntes= LOW;
int estadoBoton=LOW;
int flagStart=LOW;

unsigned long contador = 0;
unsigned long comienzo = 0;






void loop()
{
  
  int botonAhora = digitalRead(2);
  int botonReset = digitalRead(3);
  
  
  //Serial.println(botonReset);
  //Serial.println(botonResetAntes);
                 
  if(botonReset == HIGH && botonResetAntes == LOW)
  {
    Serial.println("Boton Reset presionado.");
    tiempoTotal = 0;
    apagarLeds();
    
	
    
  }
 	 
  
  if(botonAhora == HIGH && botonAntes == LOW)
  {
    	flagStart= !flagStart;

    	if(flagStart == HIGH)
        {
		   
           Serial.println("Prende la luz");
           comienzo = millis();
           //contador = tiempoTotal;
           millisAhora = millis();
        }
    	if(flagStart == LOW)
        {
            Serial.println("Pausa la secuencia.");
          	//termino = millis();
          	//tiempoTotal = contador;
        }
    
   		
    
    	if(tiempoTotal >= 1023)
        {
         	tiempoTotal = 0;
          	flagStart = !flagStart;
        }
   }
  
  if(flagStart==HIGH)
  {
    //Serial.println(contador);
    if(millis()- millisAhora >= 1000)
    {
      
      
      if(tiempoTotal < 1024)
      {
       	dibujar(tiempoTotal);
        millisAhora = millis();
      	Serial.print ("Seconds: ");
      	Serial.print (tiempoTotal);
      	Serial.print (" | ");
      	Serial.print ("Binary: ");
      	Serial.println(tiempoTotal,BIN);
      }else
      {
        apagarLeds();
      }
      tiempoTotal++;
    }

    


  }
  
  botonResetAntes = botonReset;
  botonAntes=botonAhora;  
  delay(20);
}




void dibujar(unsigned long tiempoTotal)
{
  int led;
  
  
  for(led = 4; led <=13; led++)
  {
      if(tiempoTotal%2 == 0)
  	  {
        //Serial.println("Dibuja 0");
    	digitalWrite(led, LOW);
        tiempoTotal = tiempoTotal/2;
    
  	   	}else
  			{
        	//Serial.println("Dibuja 1");
    		digitalWrite(led,HIGH);
        	tiempoTotal = (tiempoTotal/2);
        	
  	    	}
      //Serial.println(tiempoTotal);
      if(tiempoTotal == 0)
      {
        break;
      }

  	  }
  
}

void apagarLeds()
{
  	int led;
  	for(led = 4; led <=13; led++)
    {
      digitalWrite(led, LOW);
    }
}
