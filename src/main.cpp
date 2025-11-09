#include <Arduino.h>
#include <Keyboard.h>
#include <Remote.h>
#include <Botao.h>

constexpr uint8_t LED_PIN = LED_BUILTIN;
constexpr unsigned long BLINK_INTERVAL_MS = 500;

// Estado e temporização não bloqueante
static bool ledState = false;
static unsigned long ledLastToggle = 0;
// static unsigned long lastPrint = 0;
// static unsigned long lastDigitalRead = HIGH;

Botao bVolumeDecrease(2);
Botao bVolumeIncrease(3);
Botao bPreviousTrack(4);
Botao bPlayPause(5);
Botao bNextTrack(6);
Botao bLeft(8);
Botao bDown(9);
Botao bUp(10);
Botao bRight(11);
Botao bMute(12);

Botao *botoes[] = {&bVolumeDecrease, &bVolumeIncrease, &bPreviousTrack, &bPlayPause, &bNextTrack,
    &bLeft, &bDown, &bUp, &bRight, &bMute};


void volume_increase_onkeydown(Botao* botao) {
    Remote.increase();
}

void volume_decrease_onkeydown(Botao* botao) {
    Remote.decrease();
}

void previous_track_onkeydown(Botao* botao) {
    Remote.previous();
}

void play_pause_onkeydown(Botao* botao) {
    Remote.play_pause();
}

void next_track_onkeydown(Botao* botao) {
    Remote.next();
}

void mute_onkeydown(Botao* botao) {
    Remote.mute();
}

void remote_button_onkeyup(Botao* botao) {
    Remote.clear();
}

void left_onkeydown(Botao* botao) {
    Keyboard.press(KEY_LEFT_ARROW);
}

void left_onkeyup(Botao* botao) {
    Keyboard.release(KEY_LEFT_ARROW);
}

void down_onkeydown(Botao* botao) {
    Keyboard.press(KEY_DOWN_ARROW);
}

void down_onkeyup(Botao* botao) {
    Keyboard.release(KEY_DOWN_ARROW);
}

void up_onkeydown(Botao* botao) {
    Keyboard.press(KEY_UP_ARROW);
}

void up_onkeyup(Botao* botao) {
    Keyboard.release(KEY_UP_ARROW);
}

void right_onkeydown(Botao* botao) {
    Keyboard.press(KEY_RIGHT_ARROW);
}

void right_onkeyup(Botao* botao) {
    Keyboard.release(KEY_RIGHT_ARROW);
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // garante estado inicial

    // configura a acao de cada botao:
    auto * remote_clear_onkeyup = new FuncaoCallback<Botao>(remote_button_onkeyup);

    //bVolumeIncrease.addCallbackOnLOW(new MetodoCallback<Botao, Remote_>(&Remote, Remote_::increase));
    bVolumeIncrease.addCallbackOnLOW(new FuncaoCallback<Botao>(volume_increase_onkeydown));
    bVolumeIncrease.addCallbackOnHIGH(remote_clear_onkeyup);

    bVolumeDecrease.addCallbackOnLOW(new FuncaoCallback<Botao>(volume_decrease_onkeydown));
    bVolumeDecrease.addCallbackOnHIGH(remote_clear_onkeyup);

    bPreviousTrack.addCallbackOnLOW(new FuncaoCallback<Botao>(previous_track_onkeydown));
    bPreviousTrack.addCallbackOnHIGH(remote_clear_onkeyup);

    bPlayPause.addCallbackOnLOW(new FuncaoCallback<Botao>(play_pause_onkeydown));
    bPlayPause.addCallbackOnHIGH(remote_clear_onkeyup);

    bNextTrack.addCallbackOnLOW(new FuncaoCallback<Botao>(next_track_onkeydown));
    bNextTrack.addCallbackOnHIGH(remote_clear_onkeyup);

    bMute.addCallbackOnLOW(new FuncaoCallback<Botao>(mute_onkeydown));
    bMute.addCallbackOnHIGH(remote_clear_onkeyup);

    bLeft.addCallbackOnLOW(new FuncaoCallback<Botao>(left_onkeydown));
    bLeft.addCallbackOnHIGH(new FuncaoCallback<Botao>(left_onkeyup));

    bDown.addCallbackOnLOW(new FuncaoCallback<Botao>(down_onkeydown));
    bDown.addCallbackOnHIGH(new FuncaoCallback<Botao>(down_onkeyup));

    bUp.addCallbackOnLOW(new FuncaoCallback<Botao>(up_onkeydown));
    bUp.addCallbackOnHIGH(new FuncaoCallback<Botao>(up_onkeyup));

    bRight.addCallbackOnLOW(new FuncaoCallback<Botao>(right_onkeydown));
    bRight.addCallbackOnHIGH(new FuncaoCallback<Botao>(right_onkeyup));

    //Serial.begin(115200);

    // inicia a biblioteca keyboard
    Keyboard.begin();
    Remote.begin();
}


void loop() {
    unsigned long now = millis();

    if (now - ledLastToggle >= BLINK_INTERVAL_MS) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? HIGH : LOW);
        ledLastToggle = now;
    }

    // loop para atualizacao de todos os botoes
    for (Botao* botao : botoes) {
        botao->atualiza();
    }

    // for (int i = 2; i <= 12; i++) {
    //     if (lastDigitalRead == HIGH
    //         && digitalRead(i) == LOW) {
    //         lastDigitalRead = LOW;
    //
    //         if (now < lastPrint || now - lastPrint >= 100) {
    //             switch (i) {
    //                 case 2:
    //                     Remote.decrease();
    //                     break;
    //                 case 3:
    //                     Remote.increase();
    //                     break;
    //                 case 4:
    //                     Remote.rewind();
    //                     break;
    //                 case 5:
    //                     Remote.pause();
    //                     break;
    //                 case 6:
    //                     Remote.forward();
    //                     break;
    //                 case 12:
    //                     Remote.mute();
    //                     break;
    //                 default:
    //                     Keyboard.print(i);
    //                     Keyboard.print('-');
    //             }
    //             lastPrint = now;
    //         }
    //     }
    //
    //     if (lastDigitalRead == LOW
    //         && digitalRead(i) == HIGH) {
    //         lastDigitalRead = HIGH;
    //         if ((i >= 2 && i <= 6) || i == 12) {
    //             Remote.clear();
    //         }
    //     }
    // }
}


/*
 Information for device LilyPad USB (VID=0x1B4F PID=0x9208):

------------------------------
Connection Information:
------------------------------
Device current bus speed: FullSpeed
Device supports USB 1.1 specification
Device supports USB 2.0 specification
Device address: 0x001E
Current configuration value: 0x01
Number of open pipes: 4


------------------------------
Device Descriptor:
------------------------------
0x12	bLength
0x01	bDescriptorType
0x0200	bcdUSB
0xEF	bDeviceClass      (Miscellaneous device)
0x02	bDeviceSubClass
0x01	bDeviceProtocol
0x40	bMaxPacketSize0   (64 bytes)
0x1B4F	idVendor
0x9208	idProduct
0x0100	bcdDevice
0x01	iManufacturer   "SparkFun"
0x02	iProduct        "LilyPad USB"
0x03	iSerialNumber   "HIDKH"
0x01	bNumConfigurations


-------------------------
Configuration Descriptor:
-------------------------
0x09	bLength
0x02	bDescriptorType
0x0064	wTotalLength   (100 bytes)
0x03	bNumInterfaces
0x01	bConfigurationValue
0x00	iConfiguration
0xA0	bmAttributes   (Bus-powered Device, Remote-Wakeup)
0xFA	bMaxPower      (500 mA)

Interface Association Descriptor:
------------------------------
0x08	bLength
0x0B	bDescriptorType
0x00	bFirstInterface
0x02	bInterfaceCount
0x02	bFunctionClass      (Communication Device Class)
0x02	bFunctionSubClass   (Abstract Control Model - ACM)
0x00	bFunctionProtocol
0x00	iFunction

Interface Descriptor:
------------------------------
0x09	bLength
0x04	bDescriptorType
0x00	bInterfaceNumber
0x00	bAlternateSetting
0x01	bNumEndPoints
0x02	bInterfaceClass      (Communication Device Class)
0x02	bInterfaceSubClass   (Abstract Control Model - ACM)
0x00	bInterfaceProtocol
0x00	iInterface

CDC Header Functional Descriptor:
------------------------------
0x05	bFunctionalLength
0x24	bDescriptorType
0x00	bDescriptorSubtype
0x0110	bcdCDC

CDC Call Management Functional Descriptor:
------------------------------
0x05	bFunctionalLength
0x24	bDescriptorType
0x01	bDescriptorSubtype
0x01	bmCapabilities
0x01	bDataInterface

CDC Abstract Control Management Functional Descriptor:
------------------------------
0x04	bFunctionalLength
0x24	bDescriptorType
0x02	bDescriptorSubtype
0x06	bmCapabilities

CDC Union Functional Descriptor:
------------------------------
0x05	bFunctionalLength
0x24	bDescriptorType
0x06	bDescriptorSubtype
0x00	bControlInterface
0x01	bSubordinateInterface(0)

Endpoint Descriptor:
------------------------------
0x07	bLength
0x05	bDescriptorType
0x81	bEndpointAddress  (IN endpoint 1)
0x03	bmAttributes      (Transfer: Interrupt / Synch: None / Usage: Data)
0x0010	wMaxPacketSize    (1 x 16 bytes)
0x40	bInterval         (64 frames)

Interface Descriptor:
------------------------------
0x09	bLength
0x04	bDescriptorType
0x01	bInterfaceNumber
0x00	bAlternateSetting
0x02	bNumEndPoints
0x0A	bInterfaceClass      (CDC Data)
0x00	bInterfaceSubClass
0x00	bInterfaceProtocol
0x00	iInterface

Endpoint Descriptor:
------------------------------
0x07	bLength
0x05	bDescriptorType
0x02	bEndpointAddress  (OUT endpoint 2)
0x02	bmAttributes      (Transfer: Bulk / Synch: None / Usage: Data)
0x0040	wMaxPacketSize    (64 bytes)
0x00	bInterval

Endpoint Descriptor:
------------------------------
0x07	bLength
0x05	bDescriptorType
0x83	bEndpointAddress  (IN endpoint 3)
0x02	bmAttributes      (Transfer: Bulk / Synch: None / Usage: Data)
0x0040	wMaxPacketSize    (64 bytes)
0x00	bInterval

Interface Descriptor:
------------------------------
0x09	bLength
0x04	bDescriptorType
0x02	bInterfaceNumber
0x00	bAlternateSetting
0x01	bNumEndPoints
0x03	bInterfaceClass      (Human Interface Device Class)
0x00	bInterfaceSubClass
0x00	bInterfaceProtocol
0x00	iInterface

HID Descriptor:
------------------------------
0x09	bLength
0x21	bDescriptorType
0x0101	bcdHID
0x00	bCountryCode
0x01	bNumDescriptors
0x22	bDescriptorType   (Report descriptor)
0x007A	bDescriptorLength

Endpoint Descriptor:
------------------------------
0x07	bLength
0x05	bDescriptorType
0x84	bEndpointAddress  (IN endpoint 4)
0x03	bmAttributes      (Transfer: Interrupt / Synch: None / Usage: Data)
0x0040	wMaxPacketSize    (1 x 64 bytes)
0x01	bInterval         (1 frames)

Microsoft OS Descriptor is not available. Error code: 0x0000001F


--------------------------------
String Descriptor Table
--------------------------------
Index  LANGID  String
0x00   0x0000  0x0409
0x01   0x0409  "SparkFun"
0x02   0x0409  "LilyPad USB"
0x03   0x0409  "HIDKH"

------------------------------

Connection path for device:
Controlador Host Compatível com USB xHCI
Root Hub
LilyPad USB (VID=0x1B4F PID=0x9208) Port: 4

Running on: Windows 10 or greater (Build Version 19045)

Brought to you by TDD v2.19.0, Dec  5 2023, 12:08:38

 */
