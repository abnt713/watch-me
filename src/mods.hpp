#include <vector>

#include "config.h"

#include "base/Loadable.hpp"
#include "pkg/Power.hpp"
#include "pkg/Battery.hpp"
#include "ui/SimpleUI.hpp"

namespace mods {
	std::vector <Setup*> setups;
	std::vector <Looper*> loops;

	Power *power;
	Battery *batt;
	SimpleUI *ui;

	static void uiWrapper(lv_obj_t *obj, lv_event_t event) {
		ui->onBtnClick(obj, event);
	}

	static void addSetup(Setup *s) {
		setups.push_back(s);
	}

	static void addLooper(Looper *l) {
		loops.push_back(l);
	}

	static void addLoadable(Loadable *l) {
		addSetup(l);
		addLooper(l);
	}

	static void init(TTGOClass *ttgo) {
		power = new Power(ttgo);
		addLoadable(power);
		pinMode(AXP202_INT, INPUT);
		attachInterrupt(AXP202_INT, [] {
				power->activateLowPower();
		}, FALLING);

		batt = new Battery(ttgo->power);
		addSetup(batt);

		ui = new SimpleUI(ttgo, batt, uiWrapper);
		addLoadable(ui);
	}

	static void setup() {
		for (Setup *v : setups) {
			v->setup();
		}
	}

	static void loop() {
		for (Looper *v : loops) {
			v->loop();
		}
	}
}
