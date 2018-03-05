#include "jc65.h"
#include "version.h"

enum layers {
    _BL = 0,    // Base Layer
    _FL,        // Function Layer
    _KL,        // 2nd function layer,
    _NL,        // numpad layer
    _AL,        // Adjust Layer
};

enum jc65_keycodes {
    DYNAMIC_MACRO_RANGE = SAFE_RANGE,
};

#include "dynamic_macro.h"
#define _______ KC_TRNS
#define XXXXXXX KC_NO

static uint8_t current_layer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* _BL: Base Layer, mostly standard 65% QWERTY layout.-------------7-[ ]
    *  .---------------------------------------------------------------.
    *  |GrE|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Ins|
    *  |---------------------------------------------------------------|
    *  |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|Del|
    *  |---------------------------------------------------------------|
    *  |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |PgU|
    *  |---------------------------------------------------------------|
    *  |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |PgD|
    *  |---------------------------------------------------------------|
    *  |Ctrl|Gui |Alt |      Space             |RAlt |Ctrl |Lft|Dwn|Rgt|
    *  *---------------------------------------------------------------*
    */
    [_BL] = KEYMAP(
        KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  XXXXXXX, KC_BSPC, KC_INS,
        KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        KC_LCTL,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,           KC_HOME,
        KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI,          KC_LALT, KC_SPC,           MO(_KL),           KC_SPC,           KC_RALT, MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* _FL: Function Layer.
    *  .---------------------------------------------------------------.
    *  |M0 | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|SLock  |PSc|
    *  |---------------------------------------------------------------|
    *  |Fn_AL|   |   |   |   |   |   |   |   |   |   |   |   |     |Pau|
    *  |---------------------------------------------------------------|
    *  |FnCaps|   |   |   |   |   |Lft|Dwn|Up |Rgt|   |   |        |Hme|
    *  |---------------------------------------------------------------|
    *  |        |   |   |   |   |   |   |   |   |   |   |VlMute|VlU|End|
    *  |---------------------------------------------------------------|
    *  |    |    |Menu|                        |     |     |WBk|VlD|WFw|
    *  *---------------------------------------------------------------*
    */
    [_FL] = KEYMAP(
        KC_GRV,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, _______, KC_VOLU,
        KC_CAPS,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
        _______,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX, _______,          KC_PGUP,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(_AL), XXXXXXX, XXXXXXX, MO(_NL),          _______, KC_MUTE, KC_PGDN,
        _______, _______,          _______, KC_SPC,             XXXXXXX,             KC_SPC,             _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT
    ),

    /* _KL: Function Layer.
    *  .---------------------------------------------------------------.
    *  |M0 | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|SLock  |PSc|
    *  |---------------------------------------------------------------|
    *  |Fn_AL|   |   |   |   |   |   |   |   |   |   |   |   |     |Pau|
    *  |---------------------------------------------------------------|
    *  |FnCaps|   |   |   |   |   |Lft|Dwn|Up |Rgt|   |   |        |Hme|
    *  |---------------------------------------------------------------|
    *  |        |   |   |   |   |   |   |   |   |   |   |VlMute|VlU|End|
    *  |---------------------------------------------------------------|
    *  |    |    |Menu|                        |     |     |WBk|VlD|WFw|
    *  *---------------------------------------------------------------*
    */
    [_KL] = KEYMAP(
        XXXXXXX,        XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, _______, XXXXXXX,
        XXXXXXX,          KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX, XXXXXXX, KC_F9, KC_F10, KC_F11, KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______,          KC_F5, KC_F6, KC_F7, KC_F8, XXXXXXX, XXXXXXX, KC_F5, KC_F6,   KC_F7, KC_F8, XXXXXXX, _______,          XXXXXXX,
        _______, XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4, XXXXXXX, XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F4,          _______, XXXXXXX, XXXXXXX,
        _______, _______,          _______, KC_SPC,             _______,             KC_SPC,             _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* _NL: Function Layer.
    *  .---------------------------------------------------------------.
    *  |M0 | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|SLock  |PSc|
    *  |---------------------------------------------------------------|
    *  |Fn_AL|   |   |   |   |   |   |   |   |   |   |   |   |     |Pau|
    *  |---------------------------------------------------------------|
    *  |FnCaps|   |   |   |   |   |Lft|Dwn|Up |Rgt|   |   |        |Hme|
    *  |---------------------------------------------------------------|
    *  |        |   |   |   |   |   |   |   |   |   |   |VlMute|VlU|End|
    *  |---------------------------------------------------------------|
    *  |    |    |Menu|                        |     |     |WBk|VlD|WFw|
    *  *---------------------------------------------------------------*
    */
    [_NL] = KEYMAP(
        XXXXXXX,                KC_P7,      KC_P8,  KC_P9,  XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,                KC_P4,      KC_P5,  KC_P6,  KC_PAST,    KC_PSLS,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,                KC_P1,      KC_P2,  KC_P3,  KC_PPLS,    KC_PMNS,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX,    XXXXXXX,    KC_P0,      KC_PDOT,XXXXXXX,KC_PENT, XXXXXXX,  XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_NLCK,    _______,          XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,                XXXXXXX,    XXXXXXX, KC_SPC,             XXXXXXX,             KC_SPC,             XXXXXXX,   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* _AL: Adjust Layer.
    *  Default keymap, RGB Underglow, LED backlight, and Dynamic Macro settings.
    *  .---------------------------------------------------------------.
    *  |Ver|Tog|Mod|H- |H+ |S- |S+ |V- |V+ |   |BLT|BL-|BL+|       |MP1|
    *  |---------------------------------------------------------------|
    *  |Fn_AL|_BL|_WL|   |   |   |   |   |   |   |   |   |   |     |MR1|
    *  |---------------------------------------------------------------|
    *  |FnCaps|   |   |_DL|   |   |   |   |   |   |   |   |        |MS |
    *  |---------------------------------------------------------------|
    *  |        |   |   |_CL|   |_BL|_NL|   |   |   |   |      |   |MR2|
    *  |---------------------------------------------------------------|
    *  |Rst |    |    |                        |     |     |   |   |MP2|
    *  *---------------------------------------------------------------*
    */
    [_AL] = KEYMAP(
        XXXXXXX,    RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, XXXXXXX, BL_TOGG, BL_DEC,  BL_INC,  XXXXXXX, XXXXXXX, RGB_VAI,
        XXXXXXX,          XXXXXXX,XXXXXXX, XXXXXXX, RESET, XXXXXXX, MAGIC_SWAP_CONTROL_CAPSLOCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD,
        XXXXXXX,          MAGIC_HOST_NKRO, MAGIC_TOGGLE_NKRO, MAGIC_UNHOST_NKRO, XXXXXXX, XXXXXXX, MAGIC_UNSWAP_CONTROL_CAPSLOCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          RGB_TOG,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, RGB_SAI, XXXXXXX,
        XXXXXXX,   XXXXXXX,          XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, RGB_HUD, RGB_SAD, RGB_HUI
    ),
};

void matrix_init_user(void) {
    #ifdef BACKLIGHT_ENABLE
        backlight_level(0);
    #endif
    #ifdef RGBLIGHT_ENABLE
        rgblight_mode(1);
        rgblight_sethsv(180,100,100);
    #endif
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    if (current_layer == layer) {
    }
    else {
        current_layer = layer;
        switch (layer) {
            case 0:
                backlight_level(0);
                rgblight_sethsv(180,100,255);
                break;
            case 1:
                backlight_level(1);
                rgblight_sethsv(180,95,240);
                break;
            case 2:
                backlight_level(1);
                rgblight_sethsv(180,90,225);
                break;
            case 3:
                backlight_level(1);
                rgblight_sethsv(180,85,210);
                break;
            case 4:
                backlight_level(1);
                rgblight_sethsv(180,80,195);
                break;
            case 5:
                backlight_level(2);
                rgblight_sethsv(230,255,255);
                break;
            case 6:
                backlight_level(3);
                rgblight_sethsv(350,255,255);
                break;
            default:
                backlight_level(0);
                rgblight_sethsv(180,100,100);
                break;
        }
    }
}