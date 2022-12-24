#include "mods.hpp"

TTGOClass *ttgo;

void setup() {
	ttgo = TTGOClass::getWatch();
	ttgo->begin();

	mods::init(ttgo);

	ttgo->rtc->check();
	ttgo->rtc->syncToSystem();

	mods::setup();
}

void loop() {
	mods::loop();
}
