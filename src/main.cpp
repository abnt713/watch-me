#include "config.hpp"

#include "pkg/Power.hpp"
#include "pkg/Battery.hpp"
#include "ui/SimpleUI.hpp"

TTGOClass *ttgo;

Power *power;
Battery *batt;
SimpleUI *ui;

static void uiWrapper(lv_obj_t *obj, lv_event_t event) {
	ui->onBtnClick(obj, event);
}

void init() {
	ttgo = TTGOClass::getWatch();
	ttgo->begin();

	power = new Power(ttgo);
	batt = new Battery(ttgo->power);
	ui = new SimpleUI(ttgo, batt, uiWrapper);
}

void setup() {
	init();

	ttgo->rtc->check();
	ttgo->rtc->syncToSystem();

	pinMode(AXP202_INT, INPUT);
	attachInterrupt(AXP202_INT, [] {
			power->activateLowPower();
	}, FALLING);

	batt->setup();
	power->setup();
	ui->setup();
}

void loop() {
	ui->loop();
	power->loop();
}
