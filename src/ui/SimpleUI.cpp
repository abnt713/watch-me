#include "SimpleUI.hpp"
#include "config.hpp"
#include "assets/img/watch_bg.c"
#include "assets/fonts/watch_display.c"

LV_IMG_DECLARE(watch_bg);

extern const lv_font_t watch_display;

SimpleUI::SimpleUI(TTGOClass *ttgo, Battery *batt, lv_event_cb_t cb) {
	this->ttgo = ttgo;
	this->batt = batt;
	this->cb = cb;
	this->is_on = false;
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

	this->bg = lv_img_create(lv_scr_act(), NULL);
	lv_obj_align(this->bg, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	lv_obj_set_size(this->bg, 240, 240);
	lv_img_set_src(this->bg, &watch_bg);

	static lv_style_t style_hidden_btn;
	lv_style_init(&style_hidden_btn);
	lv_style_set_bg_opa(&style_hidden_btn, LV_STATE_DEFAULT, 0);
	lv_style_set_outline_width(&style_hidden_btn, LV_STATE_DEFAULT, 0);
	lv_style_set_border_opa(&style_hidden_btn, LV_STATE_DEFAULT, 0);

	this->btn = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_add_style(this->btn, LV_BTN_PART_MAIN, &style_hidden_btn);
	lv_obj_set_event_cb(btn, this->cb);
	lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, 0);

	this->currTime = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(this->currTime, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_local_text_color(
		this->currTime,
		LV_LABEL_PART_MAIN,
		LV_STATE_DEFAULT,
		LV_COLOR_BLACK
	);
	lv_obj_set_style_local_text_font(this->currTime, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &watch_display);

	this->battLabel = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style_local_text_color(
		this->battLabel,
		LV_LABEL_PART_MAIN,
		LV_STATE_DEFAULT,
		LV_COLOR_BLACK
	);
	lv_obj_align(this->battLabel, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

	this->txtFlash = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(this->txtFlash, "---");
	lv_obj_set_style_local_text_color(
		this->txtFlash,
		LV_LABEL_PART_MAIN,
		LV_STATE_DEFAULT,
		LV_COLOR_BLACK
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
	lv_obj_align(this->currTime, NULL, LV_ALIGN_CENTER, 0, 0);

	batt->battPercentage(buf, 64);
	lv_label_set_text(this->battLabel, buf);
	lv_obj_align(this->battLabel, NULL, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
}

void SimpleUI::onBtnClick(lv_obj_t *obj, lv_event_t event) {
	if (event != LV_EVENT_CLICKED) {
		return;
	}

	if (this->is_on) {
		lv_label_set_text(this->txtFlash, "OFF");
		this->is_on = false;
	} else {
		lv_label_set_text(this->txtFlash, "ON");
		this->is_on = true;
	}
}
