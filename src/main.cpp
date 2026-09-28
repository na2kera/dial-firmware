#include <M5Dial.h>

#include "apps/device_info/device_info.h"
#include "apps/qr_manager/qr_manager.h"
#include "home/home.h"

namespace {

enum class Screen {
    Home,
    QrManager,
    DeviceInfo,
};

Screen screen = Screen::Home;
long last_encoder_step = 0;
bool ignore_next_release = false;

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
        } else if (screen == Screen::QrManager) {
            QrManager::move(delta);
        }
    }

    if (screen != Screen::Home && M5Dial.BtnA.pressedFor(900)) {
        screen = Screen::Home;
        ignore_next_release = true;
        Home::show();
        M5Dial.Speaker.tone(2000, 40);
        Serial.println("returned: Home");
        return;
    }

    if (!M5Dial.BtnA.wasReleased()) return;
    if (ignore_next_release) {
        ignore_next_release = false;
        return;
    }

    if (screen == Screen::Home) {
        switch (Home::selectedApp()) {
            case Home::App::QrManager:
                screen = Screen::QrManager;
                QrManager::show();
                Serial.println("opened: QR Manager");
                break;
            case Home::App::DeviceInfo:
                screen = Screen::DeviceInfo;
                DeviceInfo::show();
                Serial.println("opened: Device Info");
                break;
        }
    } else if (screen == Screen::QrManager) {
        QrManager::toggleQrOnly();
    }

    M5Dial.Speaker.tone(2000, 40);
}
