#ifndef BATTERY_H
#define BATTERY_H

#include "config.hpp"

class Battery {
	public:
		Battery(AXP20X_Class *power);
		void battPercentage(char *buf, int size);
		void setup();
	private:
		AXP20X_Class *power;
};

#endif
