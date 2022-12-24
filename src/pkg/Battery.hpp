#ifndef BATTERY_H
#define BATTERY_H

#include "config.hpp"
#include "base/Loadable.hpp"

class Battery : public Setup {
	public:
		Battery(AXP20X_Class *power);
		void battPercentage(char *buf, int size);
		void setup();
	private:
		AXP20X_Class *power;
};

#endif
