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

}
