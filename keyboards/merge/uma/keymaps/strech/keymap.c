#include QMK_KEYBOARD_H

enum layers {
  _BASE,
  _RISE,
  _LOWER
};

#define CC_MENU LALT(KC_SPC)
#define CC_LANG LGUI(KC_SPC)
#define CC_REST LGUI(KC_K)
#define CC_SCRN LALT(LGUI(KC_5))
#define CC_LOCK LCTL(LGUI(KC_Q))

#define CC_RISE MO(_RISE)
#define CC_LOWR MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_ansi_rspace_split_bksp(
          KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,       KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  CC_SCRN, KC_DEL,           KC_MUTE,
          KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
 CC_REST, KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_BSPC,                   KC_PGDN,
 CC_LANG, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_GRV,              KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,
 CC_MENU, XXXXXXX, CC_LOWR,                   KC_LGUI, KC_SPC,              KC_ENT,                    KC_RALT, CC_RISE,                   KC_LEFT, KC_DOWN, KC_RGHT
),

[_RISE] = LAYOUT_ansi_rspace_split_bksp(
          _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,          _______,
          _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
 _______, _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______,                   KC_END,
 _______, _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______,          _______,
 _______, _______, _______,                   _______, _______,             _______,                   _______, _______,                   _______, _______, _______
),

[_LOWER] = LAYOUT_ansi_rspace_split_bksp(
          _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,          _______,
          _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______, _______,          _______,
 CC_LOCK, _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______,                   _______,
 _______, _______, _______, _______, _______, _______, _______,             _______, _______, _______, _______, _______, _______, _______,          _______,
 _______, _______, _______,                   _______, _______,             _______,                   _______, _______,                   _______, _______, _______
),

};
