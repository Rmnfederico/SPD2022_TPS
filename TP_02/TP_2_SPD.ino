// C++ code
#include <LiquidCrystal.h>
#include <string.h>

//LiquidCrystal(rs, enable, d4, d5, d6, d7)

LiquidCrystal led(2, 3, 4, 5, 6, 7);

void setup()
{
  led.begin(16, 2);
  Serial.begin(9600);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
}



int boton11Antes=LOW;
int boton12Antes=LOW;
int boton13Antes=LOW;

unsigned long int millisAhora;
unsigned long int millisAntes=0;

char palabra[20]= "muchacha"; // palabra elegida para jugar (puede ser cualquiera) //
char auxPalabra[20];            
char letra='A';
int flag=1;
int vidas=3;
int i=0;
int gano=0;
int contadorLetras=0;

void loop()
{	
	int boton11Ahora=digitalRead(11);
  	int boton12Ahora=digitalRead(12);
  	int boton13Ahora=digitalRead(13);
  	millisAhora=millis();
  	int tam=strlen(palabra);
  
    if(i<tam)    
    {
      auxPalabra[i]='_';  // formateo con guiones, el auxiliar q va a mostrarse y modificarse
      i++;
    }
    else
    { 
      if(flag==1)
      {
        led.setCursor(9,0);
        led.print("LP: ");
        mostrarVidas(vidas);
        strupr(palabra);		
        led.setCursor(3,0);
        led.print(letra);
        mostrarPalabra(auxPalabra);
      }
      if(vidas!=0 && gano != tam)
      {
        millisAntes=millisAhora;     // guardo los milisegundos mientras NO se haya ganado o perdido
        if( (boton11Ahora==HIGH && boton11Antes==LOW) || (boton13Ahora==HIGH && boton13Antes==LOW)) //evaluo si se presiona un boton de navegacion u otro
        {
          mostrarYSeleccionarLetra(boton11Ahora,	// muestra la letra seleccionada, recibe dos botones para navegar dentro del abecedario y devuelve la letra por parametro
                                   boton13Ahora,
                                   &letra); 		
        }
        if(boton12Ahora==HIGH && boton12Antes==LOW)	// evaluo si se preciona el boton de seleccion de letra
        {
          contadorLetras=evaluarYreemplazarLetra(palabra,auxPalabra, letra); //evalua si la letra seleccionada esta dentro de la palabra, retorna la cantidad de letras encontradas
          if(contadorLetras>0)
          {
            gano=gano+contadorLetras; //guardo en la variable gano la cantidad de letras sin repetir y equivalentes al tamaño de la palabra
          }
          else
          {
            vidas--; // decremento una vida si la letra no se encontro
          }
        } 
        boton11Antes=boton11Ahora;  //antirrebotes
        boton12Antes=boton12Ahora;
        boton13Antes=boton13Ahora;
  		}
      else
      {
        if(gano==tam) // si la cantidad de letras encontradas coincide con el tamaño de la palabra, ha ganado.
        {
          led.setCursor(0,0);
          led.print("                "); 
          led.setCursor(3,1);
          led.print(" GANASTE! ");
          flag=0;
        }
        else         //  cuando se pierde todas las vidas
        {
            led.setCursor(0,0);
        	led.print("                ");
          	led.setCursor(3,1);
        	led.print(" PERDISTE! ");
          	flag=0;
        } 
        if(millisAhora-millisAntes>3000)
        {
          letra='A';
          flag=1;
          vidas=3;
          i=0;
          gano=0;
          contadorLetras=0;
          led.setCursor(4,1);
          led.print("                ");
        }
   	 }        
    }
  
  delay(100);	
}





              //////  funciones  ///////
                                     



void mostrarYSeleccionarLetra(int subir, int bajar, char* letra)
{	
    if(*letra<'Z' && subir==1 && bajar ==0)
    {
      (*letra)++;
    }
    else if(*letra >'A' && subir ==0 && bajar ==1)
    {
      (*letra)--;
    } 
}

int evaluarYreemplazarLetra(char palabra[],char auxPalabra[], char letra)
{  
  	int retorno=0;
  	int tam=strlen(palabra);
  	for(int i=0; i<tam; i++)
    {
      if(palabra[i]==letra && auxPalabra[i] != palabra[i]) //entra al if si la letra esta dentro de la palabra y si esta YA no esta dentro del auxiliar
      {														
        auxPalabra[i]=letra;
        retorno++;
      }      
    }  
  return retorno;   // retorna la cantidad de letras encontradas
}

void mostrarPalabra(char auxPalabra[])
{	
  	led.setCursor(3,1); 	//muestra el auxiliar de la palabra
	led.print(auxPalabra);
}

void mostrarVidas(int vidas)
{	
  	led.setCursor(12,0);
  	if(vidas ==3)
    {
      led.print("***");
    }else if(vidas == 2)		//muestra las vidas
    {
      led.print("** ");
    }else if(vidas==1)
    {
      led.print("*  ");
    }	
}