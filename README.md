# Mini Keyboard

## AVRDUDE e USBASP-CLONE

Os comandos abaixo (avrdude) necessitam do **usbasp-clone** conectado na plaquinha 
com o ATmega32u4.

Comando para testar se o AVRDUDE está reconhecendo o chip:

    C:\Users\smarc\.platformio\packages\tool-avrdude>avrdude -p m32u4 -c usbasp-clone -P usb

Comando para fazer upload do HEX file para o chip:

    C:\Users\smarc\.platformio\packages\tool-avrdude>avrdude -p m32u4 -c usbasp-clone -P usb -U flash:w:C:\Users\smarc\CLionProjects\MiniKeyboard\.pio\build\atmega32u4_usbasp\firmware.hex:i

Comando para regravar o bootloader:

Quando o Windows não reconhece o chip, pode ser que bootloader precise ser regravado:

- LilyPad-USB :
  
      avrdude -p m32u4 -c usbasp-clone -P usb -U flash:w:C:\Users\smarc\.platformio\packages\framework-arduino-avr\bootloaders\caterina-LilyPadUSB\Caterina-LilyPadUSB.hex:i

## USB Descriptor Dumper

Baixe o TDD (Thesycon USB Descriptor Dumper) do site https://www.thesycon.de/eng/usb_descriptordumper.shtml e salve na pasta `tools/`.

Ele serve para consultar o descritor do dispositivo USB.