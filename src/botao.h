
#ifndef _BOTAO_H
#define _BOTAO_H

#if defined(ARDUINO) && ARDUINO >= 100
   #include "Arduino.h"
#else
   #include "WProgram.h"
#endif   
#include "util.h"

#define DEBOUNCE_DELAY 70

class Botao {
private:
  int pin;
  
  int buttonState;             // the current reading from the input pin
  int lastButtonState;
  unsigned long lastDebounceTime;  // the last time the output pin was toggled

  Callback<Botao> *callbackOnHigh;  // primeiro callback acionado quando o botão ficar HIGH (key up) durante a atualizacao no loop
  Callback<Botao> *callbackOnLow;   // primeiro callback acionado quando o botão ficar LOW (key down) durante a atualizacao no loop

public:  

   /**
    * Cria e configura o pino do botáo para INPUT com PULL_UP.
    */
   Botao(int pinButton);
   
   /**
    * Durante o setup, vocë pode definir uma função de callback para ser chamada quando o botão mudar para o estado HIGH.
   */
   void addCallbackOnHIGH( Callback<Botao> *callbackOnHigh );

   /**
    * Durante o setup, vocë pode definir uma função de callback para ser chamada quando o botão mudar para o estado LOW.
   */
   void addCallbackOnLOW( Callback<Botao> *callbackOnLow );

   /** 
    * get() retorna o status do botao. Pode ser LOW ou HIGH
    **/
   int get();
   
   /**
    * atualiza() deve ser chamado no loop para chamar o callback caso mude de estado.
    */
  void atualiza();

  /** down() - executa o comportamento do botao quando ele eh pressionado */ 
  void down();

  /** up() - executa o comportamento do botao quando ele eh levantado */
  void up();
  
};


#endif


