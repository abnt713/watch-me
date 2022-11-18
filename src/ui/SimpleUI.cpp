#include "SimpleUI.hpp"
#include "config.hpp"

SimpleUI::SimpleUI(TTGOClass *ttgo, Battery *batt, lv_event_cb_t cb) {
	this->ttgo = ttgo;
	this->batt = batt;
	this->cb = cb;

	this->isTxtVisible = false;
}

void SimpleUI::setup() {
	ttgo->setBrightness(48);
	ttgo->openBL();
	ttgo->lvgl_begin();

	lv_obj_set_style_local_bg_color(
		lv_scr_act(),
		LV_OBJ_PART_MAIN,
		LV_STATE_DEFAULT,
		LV_COLOR_BLACK
	);

	this->btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_event_cb(btn, this->cb);
	lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, 0);

	this->currTime = lv_label_create(this->btn, NULL);
	this->battLabel = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style_local_text_color(
		this->battLabel,
		LV_LABEL_PART_MAIN,
		LV_STATE_DEFAULT,
		LV_COLOR_WHITE
	);
	lv_obj_align(this->battLabel, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

	this->txtFlash = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(this->txtFlash, "---");
	lv_obj_set_style_local_text_color(
		this->txtFlash,
		LV_LABEL_PART_MAIN,
		LV_STATE_DEFAULT,
		LV_COLOR_WHITE
	);
}

void SimpleUI::loop() {
	lv_task_handler();

	time_t now;
	struct tm info;
	char buf[64];

	time(&now);
	localtime_r(&now, &info);
	strftime(buf, sizeof(buf), "%H:%M:%S", &info);
	lv_label_set_text(this->currTime, buf);

	batt->battPercentage(buf, 64);
	lv_label_set_text(this->battLabel, buf);
	lv_obj_align(this->battLabel, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
}

void SimpleUI::onBtnClick(lv_obj_t *obj, lv_event_t event) {
	if (event != LV_EVENT_CLICKED) {
		return;
	}
	if (!this->isTxtVisible) {
		this->isTxtVisible = true;
		lv_label_set_text(this->txtFlash, "TXT");
	} else {
		this->isTxtVisible = false;
		lv_label_set_text(this->txtFlash, "---");
	}
}
