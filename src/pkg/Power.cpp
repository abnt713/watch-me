#include "Power.hpp"
#include "config.hpp"

Power::Power(TTGOClass *ttgo) {
	this->ttgo = ttgo;
	this->power = ttgo->power;

	this->isLowPower = false;
}

void Power::activateLowPower() {
	this->isLowPower = true;
}

void Power::setup() {
	power->clearIRQ();
	this->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ, true);
	this->power->clearIRQ();
}

void Power::loop() {
	if (!this->isLowPower) {
		return;
	}

	this->isLowPower = false;
	this->power->readIRQ();
	if (!this->power->isPEKShortPressIRQ()) {
		this->power->clearIRQ();
		return;
	}
	// Clean power chip irq status
	this->power->clearIRQ();

	// Set  touchscreen sleep
	this->ttgo->displaySleep();

	/*
		 In TWatch2019/ Twatch2020V1, touch reset is not connected to ESP32,
		 so it cannot be used. Set the touch to sleep,
		 otherwise it will not be able to wake up.
		 Only by turning off the power and powering on the touch again will the touch be working mode
	// this->displayOff();
	*/

	this->ttgo->powerOff();

	//Set all channel power off
	this->power->setPowerOutPut(AXP202_LDO3, false);
	this->power->setPowerOutPut(AXP202_LDO4, false);
	this->power->setPowerOutPut(AXP202_LDO2, false);
	this->power->setPowerOutPut(AXP202_EXTEN, false);
	this->power->setPowerOutPut(AXP202_DCDC2, false);

	// TOUCH SCREEN  Wakeup source
	// esp_sleep_enable_ext1_wakeup(GPIO_SEL_38, ESP_EXT1_WAKEUP_ALL_LOW);
	// PEK KEY  Wakeup source
	esp_sleep_enable_ext1_wakeup(GPIO_SEL_35, ESP_EXT1_WAKEUP_ALL_LOW);
	esp_deep_sleep_start();
	this->power->clearIRQ();
}
