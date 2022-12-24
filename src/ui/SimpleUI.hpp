#ifndef SIMPLEUI_H
#define SIMPLEUI_H

#include "config.hpp"
#include "base/Loadable.hpp"
#include "pkg/Battery.hpp"

class SimpleUI : public Loadable {
	public:
		SimpleUI(TTGOClass *ttgo, Battery *batt, lv_event_cb_t cb);
		void setup();
		void loop();
		void onBtnClick(lv_obj_t *obj, lv_event_t event);
	private:
		bool is_on;

		TTGOClass *ttgo;
		Battery *batt;

		lv_obj_t *bg;
		lv_obj_t *btn;
		lv_obj_t *currTime;
		lv_obj_t *currDate;
		lv_obj_t *txtFlash;
		lv_obj_t *battLabel;
		lv_event_cb_t cb;
};

#endif
