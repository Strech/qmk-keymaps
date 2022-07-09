#include QMK_KEYBOARD_H

enum layers {
  _BASE,
  _RISE,
  _LOWER
};

#define CC_RISE MO(_RISE)
#define CC_LOWR MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSPC,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_GRV,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, A(KC_SPC),
    KC_LCTL, KC_LALT,                   KC_LGUI, KC_SPC,     KC_ENT,  CC_RISE,                            CC_LOWR, G(KC_SPC)
  ),

  [_RISE] = LAYOUT(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    S(KC_9), S(KC_0),
    _______, _______, _______, _______, _______, _______,             KC_MINS, KC_EQL,  _______, _______, KC_QUOT, KC_DEL,
    _______, _______, _______, _______, _______, _______,    _______, KC_UNDS, KC_PLUS, _______, _______, KC_BSLS, _______,
    _______, _______,                   _______, _______,    _______, _______,                            _______, _______
  ),

  [_LOWER] = LAYOUT(
    KC_SLEP, KC_HOME, KC_UP,   KC_END,  _______, _______,             _______, _______, _______, KC_BRIU, KC_VOLU, KC_PGUP, KC_PGDN,
    KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,             _______, _______, _______, KC_BRID, KC_VOLD, KC_MPLY,
    _______, _______, _______, _______, _______, _______,    _______, _______, _______, KC_MPRV, KC_MNXT, _______, _______,
    _______, _______,                   _______, _______,    _______, _______,                            _______, _______
  ),
};

void matrix_init_user(void) {
  // set CapsLock LED to output and low
  setPinOutput(B1);
  writePinLow(B1);
  // set NumLock LED to output and low
  setPinOutput(B2);
  writePinLow(B2);
  // set ScrollLock LED to output and low
  setPinOutput(B3);
  writePinLow(B3);
}

void matrix_scan_user(void) {
  // no-op
}


void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(B2);
  } else {
    writePinLow(B2);
  }
}

//function for layer indicator LED
layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
  case _RISE:
    writePinLow(B3);
    writePinHigh(B1);
    break;
  case _LOWER:
    writePinLow(B1);
    writePinHigh(B3);
    break;
  default:
    // no-op
    writePinLow(B1);
    writePinLow(B3);
    break;
  };

  return state;
}
