#include QMK_KEYBOARD_H

enum layers{
  _BASE,
  _NUM,
  _NAV,
};

enum combo_events {
  COMBO_BSPC,
};

#define LALT_Q LALT_T(KC_Q)
#define LCTL_A LCTL_T(KC_A)
#define LSFT_Z LSFT_T(KC_Z)

#define RCTL_SC RCTL_T(KC_SCLN)
#define RSFT_SL RSFT_T(KC_SLSH)

#define GUI_ESC LGUI_T(KC_ESC)
#define NAV_ENT LT(_NAV, KC_ENT)
#define NUM_TAB LT(_NUM, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
     LALT_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_MPLY, KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
     LCTL_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,   RCTL_SC,
     LSFT_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT, RSFT_SL,
                               GUI_ESC,  KC_SPC,          NAV_ENT, NUM_TAB
  ),

  [_NUM] = LAYOUT(
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    _______, _______, _______, _______,  KC_GRV,          KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_QUOT,
    _______, _______, _______, _______, _______,          KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS,
                               _______, _______,          _______, _______
  ),

  [_NAV] = LAYOUT(
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, KC_HOME, _______, KC_UP,   _______, KC_PGUP,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,          KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
    _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
                               _______, _______,          _______, _______
  ),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case LT(_NUM, KC_TAB):
    return 100;
  case LGUI_T(KC_ESC):
    return 100;
  default:
    return TAPPING_TERM;
  }
}

uint8_t mod_state;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    mod_state = get_mods();

    if (clockwise) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code(KC_BRMD);
        set_mods(mod_state);
      } else {
        tap_code(KC_VOLD);
      }
    } else {
      if (get_mods() & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code(KC_BRMU);
        set_mods(mod_state);
      } else {
        tap_code(KC_VOLU);
      }
    }
  }
}

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_bspc[] = {KC_O, KC_P, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_BSPC] = COMBO_ACTION(combo_bspc),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  mod_state = get_mods();

  switch(combo_index) {
  case COMBO_BSPC:
    if (pressed) {
      if (mod_state & MOD_MASK_SHIFT) {
        del_mods(MOD_MASK_SHIFT);
        tap_code(KC_DEL);
        set_mods(mod_state);
      } else {
        // use tap_code16 for mods
        tap_code(KC_BSPC);
      }
    }
    break;
  }
}
#endif

#ifdef OLED_DRIVER_ENABLE  //Special thanks to Sickbabies for this great OLED widget!
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_90;  // rotates for proper orientation
}

void render_lechiffre_logo(void) {
  static const char PROGMEM lechiffre_logo[] = {
    // 'lechiffre_logo', 32x20px
    0x00, 0x3e, 0x20, 0x20, 0x00, 0x18, 0x2c, 0xa8, 0x80, 0x00, 0x1c, 0x22, 0x22, 0x00, 0x3e, 0x08,
    0x30, 0x00, 0x34, 0x00, 0x3c, 0x0a, 0x00, 0xbc, 0x8a, 0x00, 0x38, 0x08, 0x00, 0x18, 0x2c, 0x28,
    0x00, 0xb6, 0xb6, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00,
    0x00, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0x00, 0x6d, 0x6d, 0x00, 0xdb, 0xdb, 0x00, 0xb6, 0xb6, 0x00,
    0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00,
    0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00
  };

  oled_write_raw_P(lechiffre_logo, sizeof(lechiffre_logo));
}

static void render_layer_status(void) {
  oled_write_P(PSTR("-----"), false);
  switch (get_highest_layer(layer_state)) {
  case _BASE:
    oled_write_ln_P(PSTR("BASE"), false);
    break;
  case _NUM_SYM:
    oled_write_ln_P(PSTR(" SYM"), false);
    break;
  case _NAV:
    oled_write_ln_P(PSTR(" NAV"), false);
    break;
  default:
    oled_write_ln_P(PSTR("?????"), false);
  }
}

#define KEYLOG_LEN 11
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
  ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
  '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
    keycode = keycode & 0xFF;
  }

  for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
    keylog_str[i] = keylog_str[i - 1];
  }

  if (keycode < 60) {
    keylog_str[0] = code_to_name[keycode];
  }

  keylog_str[KEYLOG_LEN - 1] = 0;

  log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

//Text only renders
void render_keylogger_status(void) {
    oled_write_P(PSTR("-----"), false);
    oled_write(keylog_str, false);
}

void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("-----"), false);
    oled_write_P(PSTR("C"), led_state.caps_lock);
	oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
	oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), led_state.scroll_lock);
    //oled_write_ln_P(PSTR(" "), false);
}

void render_mod_status(uint8_t modifiers) {
       oled_write_P(PSTR("-----"), false);
    oled_write_ln_P(PSTR("SHFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_ln_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    oled_write_ln_P(PSTR("CTRL"), (modifiers & MOD_MASK_CTRL));
    oled_write_ln_P(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
}

void oled_task_user(void) {
    render_lechiffre_logo();
    oled_set_cursor(0,3);
    render_layer_status();	// Renders the current keyboard state (layer, lock, caps, scroll, etc)
	render_mod_status(get_mods()|get_oneshot_mods());
	render_keylock_status(host_keyboard_led_state());
	render_keylogger_status();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
      add_keylog(keycode);
    }
    return true;
  }
#endif
