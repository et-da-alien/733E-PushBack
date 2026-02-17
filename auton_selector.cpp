#include "iostream"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_style.h"
#include "liblvgl/display/lv_display.h"
#include "liblvgl/font/lv_symbol_def.h" // IWYU pragma: keep
#include "liblvgl/misc/lv_color.h"      // IWYU pragma: keep
#include "liblvgl/misc/lv_event.h"
#include "liblvgl/misc/lv_palette.h"
#include "liblvgl/misc/lv_style.h"
#include "liblvgl/misc/lv_types.h"
#include "liblvgl/widgets/button/lv_button.h"
#include "liblvgl\lvgl.h" // IWYU pragma: keep
#include <cstddef>
#include <ostream>

// My .h files
#include "auton_selector.h"
#include "global_var.h"

// Screens
lv_obj_t *homeScreen = lv_obj_create(NULL);
lv_obj_t *redScreen = lv_obj_create(NULL);
lv_obj_t *blueScreen = lv_obj_create(NULL);

// Styles
lv_style_t styleGrey;
lv_style_t styleGreyChecked;
lv_style_t styleRed;
lv_style_t styleRedChecked;
lv_style_t styleBlue;
lv_style_t styleBlueChecked;

lv_style_t styleButton;

// Home Buttons
lv_obj_t *skillButton = lv_button_create(homeScreen);
lv_obj_t *redButton = lv_button_create(homeScreen);
lv_obj_t *blueButton = lv_button_create(homeScreen);
// RedSideButtons
lv_obj_t *redPosButton = lv_button_create(redScreen);
lv_obj_t *redNegButton = lv_button_create(redScreen);
lv_obj_t *redSoloAWPButton = lv_button_create(redScreen);
// BlueSideButtons
lv_obj_t *bluePosButton = lv_button_create(blueScreen);
lv_obj_t *blueNegButton = lv_button_create(blueScreen);
lv_obj_t *blueSoloAWPButton = lv_button_create(blueScreen);

void basicStyleInitialization(lv_style_t *style, lv_palette_t color) {
  lv_style_init(style); // Initializes the style
  lv_style_set_bg_color(
      style,
      lv_palette_main(
          color)); // Simply setting the background color to associated color
}

void checkedStyleInit(lv_style_t *style, lv_palette_t color) {
  lv_style_init(style);
  lv_style_set_border_width(style, 10);
  lv_style_set_border_opa(style, 255);
  lv_style_set_border_color(style, lv_color_white());
  lv_style_set_bg_color(style, lv_palette_darken(color, 3));
}

void styleInit() {
  lv_style_set_radius(&styleButton, 10);
  lv_style_set_bg_opa(&styleButton, LV_OPA_COVER);
  lv_style_set_text_color(&styleButton, lv_color_black());
  lv_style_set_text_font(&styleButton, &lv_font_montserrat_24);

  basicStyleInitialization(&styleGrey, LV_PALETTE_GREY);
  checkedStyleInit(&styleGreyChecked, LV_PALETTE_GREY);

  basicStyleInitialization(&styleRed, LV_PALETTE_RED);
  checkedStyleInit(&styleRedChecked, LV_PALETTE_RED);

  basicStyleInitialization(&styleBlue, LV_PALETTE_BLUE);
  checkedStyleInit(&styleBlueChecked, LV_PALETTE_BLUE);
}

void styleButtons() {
  lv_obj_add_style(skillButton, &styleGrey, LV_STATE_DEFAULT);
  lv_obj_add_style(skillButton, &styleGreyChecked, LV_STATE_CHECKED);
  // Red Button Styles
  lv_obj_add_style(redButton, &styleRed, LV_STATE_DEFAULT);
  lv_obj_add_style(redButton, &styleRedChecked, LV_STATE_CHECKED);
  // Red Child Buttons
  lv_obj_add_style(redPosButton, &styleRed, LV_STATE_DEFAULT);
  lv_obj_add_style(redPosButton, &styleRedChecked, LV_STATE_CHECKED);
  lv_obj_add_style(redNegButton, &styleRed, LV_STATE_DEFAULT);
  lv_obj_add_style(redNegButton, &styleRedChecked, LV_STATE_CHECKED);
  lv_obj_add_style(redSoloAWPButton, &styleRed, LV_STATE_DEFAULT);
  lv_obj_add_style(redSoloAWPButton, &styleRedChecked, LV_STATE_CHECKED);
  // Blue Button Styles
  lv_obj_add_style(blueButton, &styleBlue, LV_STATE_DEFAULT);
  lv_obj_add_style(blueButton, &styleBlueChecked, LV_STATE_CHECKED);
  // Blue Child Buttons
  lv_obj_add_style(bluePosButton, &styleBlue, LV_STATE_DEFAULT);
  lv_obj_add_style(bluePosButton, &styleBlueChecked, LV_STATE_CHECKED);
  lv_obj_add_style(blueNegButton, &styleBlue, LV_STATE_DEFAULT);
  lv_obj_add_style(blueNegButton, &styleBlueChecked, LV_STATE_CHECKED);
  lv_obj_add_style(blueSoloAWPButton,& styleBlue, LV_STATE_DEFAULT);
  lv_obj_add_style(blueSoloAWPButton,& styleBlueChecked, LV_STATE_CHECKED);
}

void updateStates() {
  lv_obj_remove_state(skillButton, LV_STATE_CHECKED);
  lv_obj_remove_state(redButton, LV_STATE_CHECKED);
  lv_obj_remove_state(blueButton, LV_STATE_CHECKED);
  lv_obj_remove_state(redPosButton, LV_STATE_CHECKED);
  lv_obj_remove_state(redNegButton, LV_STATE_CHECKED);
  lv_obj_remove_state(redSoloAWPButton, LV_STATE_CHECKED);
  lv_obj_remove_state(bluePosButton, LV_STATE_CHECKED);
  lv_obj_remove_state(blueNegButton, LV_STATE_CHECKED);
  lv_obj_remove_state(blueSoloAWPButton, LV_STATE_CHECKED);

  if (global::selectedAuton == states::autonStates::skills)
    lv_obj_add_state(skillButton, LV_STATE_CHECKED);
  else if (global::selectedAuton == states::autonStates::redSide)
    lv_obj_add_state(redButton, LV_STATE_CHECKED);
  else if (global::selectedAuton == states::autonStates::blueSide)
    lv_obj_add_state(blueButton, LV_STATE_CHECKED);
  else if (global::selectedAuton == states::autonStates::redSidePos)
    lv_obj_add_state(redPosButton, LV_STATE_CHECKED);
  else if (global::selectedAuton == states::autonStates::redSideNeg)
    lv_obj_add_state(redNegButton, LV_STATE_CHECKED);
  else if (global::selectedAuton == states::autonStates::soloAWPRed)
    lv_obj_add_state(redSoloAWPButton, LV_STATE_CHECKED);
  else if (global::selectedAuton == states::autonStates::blueSidePos)
    lv_obj_add_state(bluePosButton, LV_STATE_CHECKED);
  else if (global::selectedAuton == states::autonStates::blueSideNeg)
    lv_obj_add_state(blueNegButton, LV_STATE_CHECKED);
  else if (global::selectedAuton == states::autonStates::soloAWPBlue)
    lv_obj_add_state(blueSoloAWPButton, LV_STATE_CHECKED);
}

void btnEventCB(lv_event_t *btnPressed) {
  lv_obj_t *btn = static_cast<lv_obj_t *>(lv_event_get_target(btnPressed));

  if (btn == skillButton) {
    if (global::selectedAuton != states::autonStates::skills)
      global::selectedAuton = states::autonStates::skills;
    else
      global::selectedAuton = states::autonStates::noAuto;
  }
  // Load New Screens
  else if (btn == redButton &&
           global::selectedAuton != states::autonStates::skills) {
    lv_screen_load(redScreen);
  } else if (btn == blueButton &&
             global::selectedAuton != states::autonStates::skills) {
    lv_screen_load(blueScreen);
  }
  // Buttons per Screen
  // All Red Buttons
  else if (btn == redPosButton) {
    if (global::selectedAuton != states::autonStates::redSidePos)
      global::selectedAuton = states::autonStates::redSidePos;
    else
      global::selectedAuton = states::autonStates::noAuto;
  } else if (btn == redNegButton) {
    if (global::selectedAuton != states::autonStates::redSideNeg)
      global::selectedAuton = states::autonStates::redSideNeg;
    else
      global::selectedAuton = states::autonStates::noAuto;
  } else if (btn == redSoloAWPButton) {
    if (global::selectedAuton != states::autonStates::soloAWPRed)
      global::selectedAuton = states::autonStates::soloAWPRed;
    else
      global::selectedAuton = states::autonStates::noAuto;
  }
  // All Blue Buttons
  else if (btn == bluePosButton) {
    if (global::selectedAuton != states::autonStates::blueSidePos)
      global::selectedAuton = states::autonStates::blueSidePos;
    else
      global::selectedAuton = states::autonStates::noAuto;
  } else if (btn == blueNegButton) {
    if (global::selectedAuton != states::autonStates::blueSideNeg)
      global::selectedAuton = states::autonStates::blueSideNeg;
    else
      global::selectedAuton = states::autonStates::noAuto;
  } else if (btn == blueSoloAWPButton) {
    if (global::selectedAuton != states::autonStates::soloAWPBlue)
      global::selectedAuton = states::autonStates::soloAWPBlue;
    else
      global::selectedAuton = states::autonStates::noAuto;
  }

  updateStates();
}

void buttonInitialization(lv_obj_t *btn, int x, int y, int width, int height,
                          const char *name) {
  // Determining the position, dimension, and fuction of the button
  lv_obj_set_pos(btn, x, y);
  lv_obj_set_size(btn, width, height); // Note to self screen is 480 x 240
  lv_obj_add_event_cb(btn, btnEventCB, LV_EVENT_CLICKED, NULL);

  // Determing the appearance of the buttons
  lv_obj_add_style(btn, &styleButton, 0);

  // For labelling/naming the button
  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, name);
  lv_obj_center(label);
}

void selectorInit() {
  lv_screen_load(homeScreen);
  styleInit();
  styleButtons();

  buttonInitialization(skillButton, 12, 12, 144, 192, "Skills");
  buttonInitialization(redButton, 168, 12, 144, 192, "Red Side");
  buttonInitialization(blueButton, 330, 400, 144, 192, "Blue Side");

  buttonInitialization(redPosButton, 12, 12, 144, 152, LV_SYMBOL_PLUS);
  buttonInitialization(redNegButton, 168, 12, 144, 152, LV_SYMBOL_MINUS);
  buttonInitialization(redSoloAWPButton, 324, 12, 144, 152, "Solo AWP");

  buttonInitialization(bluePosButton, 12, 12, 144, 152, LV_SYMBOL_PLUS);
  buttonInitialization(blueNegButton, 168, 12, 144, 152, LV_SYMBOL_MINUS);
  buttonInitialization(blueSoloAWPButton, 324, 12, 144, 152, "Solo AWP");

}