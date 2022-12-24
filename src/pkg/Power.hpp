#ifndef POWER_HPP
#define POWER_HPP

#include "config.hpp"
#include "base/Loadable.hpp"

class Power : public Loadable {
	public:
		Power(TTGOClass *ttgo);
		void activateLowPower();
		void setup();
		void loop();
	private:
		TTGOClass *ttgo;
		AXP20X_Class *power;
		bool isLowPower;
};

#endif
