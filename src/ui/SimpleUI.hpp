#ifndef SIMPLEUI_H
#define SIMPLEUI_H

#include "pkg/Battery.hpp"
#include "config.hpp"

class SimpleUI {
	public:
		SimpleUI(TTGOClass *ttgo, Battery *batt, lv_event_cb_t cb);
		void setup();
		void loop();
		void onBtnClick(lv_obj_t *obj, lv_event_t event);
	private:
		TTGOClass *ttgo;
		Battery *batt;

		lv_obj_t *btn;
		lv_obj_t *currTime;
		lv_obj_t *txtFlash;
		lv_obj_t *battLabel;
		lv_event_cb_t cb;

		bool isTxtVisible;
};

#endif
