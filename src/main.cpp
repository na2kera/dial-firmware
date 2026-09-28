#include <M5Dial.h>

#include "apps/qr_manager/qr_manager.h"
#include "home/home.h"

namespace {

enum class Screen {
    Home,
    QrManager,
};

Screen screen = Screen::Home;
long last_encoder_step = 0;

}  // namespace

void setup() {
    auto cfg = M5.config();
    cfg.serial_baudrate = 115200;
    M5Dial.begin(cfg, true, false);
    last_encoder_step = M5Dial.Encoder.read() / 4;
    Home::show();
    Serial.println("Dial launcher started");
}

void loop() {
    M5Dial.update();

    // The encoder reports four counts per detent.
    long encoder_step = M5Dial.Encoder.read() / 4;
    if (encoder_step != last_encoder_step) {
        long delta = encoder_step - last_encoder_step;
        last_encoder_step = encoder_step;
        if (screen == Screen::Home) {
            Home::move(delta);
        } else {
            QrManager::move(delta);
        }
    }

    if (!M5Dial.BtnA.wasReleased()) return;

    if (screen == Screen::Home) {
        if (Home::selectedApp() == Home::App::QrManager) {
            screen = Screen::QrManager;
            QrManager::show();
            Serial.println("opened: QR Manager");
        }
    } else if (M5Dial.BtnA.wasReleaseFor(900)) {
        screen = Screen::Home;
        Home::show();
        Serial.println("returned: Home");
    } else {
        QrManager::toggleQrOnly();
    }

    M5Dial.Speaker.tone(2000, 40);
}
