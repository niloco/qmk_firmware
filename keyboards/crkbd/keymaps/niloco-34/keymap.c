/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
// Callum's one-shot modifiers
#include "oneshot.h"

// Layout for corne 3x6 based on Callum's userspace

// #defines for readability (lmao)
#define DFQ DF(DEF_Q)
#define DFC DF(DEF_C)
#define DFG DF(DEF_G)
#define TGS TG(STENO)
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)

// layers
enum layers { DEF_Q, DEF_C, SYM, NAV, NUM };

// one shot mods
enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};

// combos

//// naming:
//// {hand}_{finger(s): P, R, M, I}_{other info}_{resulting key}
enum combos {
    L_R_UPPER_GUI,
    L_M_UPPER_ALT,
    L_I_UPPER_CTRL,    

    R_I_UPPER_CTRL,
    R_M_UPPER_ALT,
    R_R_UPPER_GUI,
    
    COMBO_LENGTH,
};

//// number of combos:
uint16_t COMBO_LEN = COMBO_LENGTH;

//// based on qwerty fingerings for now
#define COMBO_ONLY_FROM_LAYER DEF_Q

////// left hand

//////// mods
const uint16_t PROGMEM l_r_upper_gui[] = {KC_W, KC_S, COMBO_END};
const uint16_t PROGMEM l_m_upper_alt[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM l_i_upper_ctrl[] = {KC_R, KC_F, COMBO_END};

////// right hand

//////// mods
const uint16_t PROGMEM r_i_upper_ctrl[] = {KC_U, KC_J, COMBO_END};
const uint16_t PROGMEM r_m_upper_alt[] = {KC_I, KC_K, COMBO_END};
const uint16_t PROGMEM r_r_upper_gui[] = {KC_O, KC_L, COMBO_END};

// combo mapping
combo_t key_combos[] = {
    [L_R_UPPER_GUI] = COMBO(l_r_upper_gui, OS_GUI),
    [L_M_UPPER_ALT] = COMBO(l_m_upper_alt, OS_ALT),
    [L_I_UPPER_CTRL] = COMBO(l_i_upper_ctrl, OS_CTRL),
    [R_I_UPPER_CTRL] = COMBO(r_i_upper_ctrl, OS_CTRL),
    [R_M_UPPER_ALT] = COMBO(r_m_upper_alt, OS_ALT),
    [R_R_UPPER_GUI] = COMBO(r_r_upper_gui, OS_GUI),
};

// layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Normal base layout
  [DEF_Q] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,   KC_QUOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, OS_SHFT, LA_NAV,     LA_SYM, KC_SPC,  XXXXXXX
                                      //`--------------------------'  `--------------------------'
 ),

    // Colemak dh(m?) alpha layout
  [DEF_C] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y,   KC_QUOT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H,   KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, OS_SHFT, LA_NAV,     LA_SYM, KC_SPC,  XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  // Symbols
  [SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_PERC, KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                     KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,                      KC_HASH, OS_SHFT,  OS_CTRL, OS_ALT,  OS_GUI, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_PLUS, KC_PIPE, KC_AT,   KC_TAB, KC_BSLS,                     XXXXXXX, KC_AMPR, KC_SCLN, KC_COLN, KC_EXLM, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // Nav and switch default layer
  [NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,  DFC,   XXXXXXX, XXXXXXX,  DFQ,    KC_VOLU,                      RESET,   KC_CAPS,  KC_UP,  XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, OS_GUI, OS_ALT,  OS_CTRL, OS_SHFT,  KC_VOLD,                     KC_BSPC, KC_LEFT, KC_DOWN,  KC_RGHT, KC_DEL,  _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, CL_SWAP, CL_NORM, XXXXXXX, KC_ESC, KC_MPLY,                      XXXXXXX, KC_PGDN, KC_PGUP, XXXXXXX, KC_ENT,  _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  // Numbers and f-keys
  [NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,   KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, OS_GUI, OS_ALT,  OS_CTRL, OS_SHFT,  KC_F11,                      KC_F12,  OS_SHFT, OS_CTRL, OS_ALT,  OS_GUI,   _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );

    // mod is dependent on whether or not caps is swapped
    uint16_t mod = keymap_config.swap_control_capslock ? KC_CAPS : KC_LCTL;
    update_oneshot(
        &os_ctrl_state, mod, OS_CTRL,
        keycode, record
    );

    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );

    update_oneshot(
        &os_gui_state, KC_LGUI, OS_GUI,
        keycode, record
    );

    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE
