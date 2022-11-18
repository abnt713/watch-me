#include "Battery.hpp"

Battery::Battery(AXP20X_Class *power) {
	this->power = power;
}

void Battery::setup() {
	this->power->adc1Enable(AXP202_VBUS_VOL_ADC1
			| AXP202_VBUS_CUR_ADC1
			| AXP202_BATT_CUR_ADC1
			| AXP202_BATT_VOL_ADC1,
			true);

	this->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ
			| AXP202_VBUS_REMOVED_IRQ
			| AXP202_VBUS_CONNECT_IRQ
			| AXP202_CHARGING_IRQ,
			true);
}

void Battery::battPercentage(char *buf, int size) {
	snprintf(buf, size, "%% %d", this->power->getBattPercentage());
}
