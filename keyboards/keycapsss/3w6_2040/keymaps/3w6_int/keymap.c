// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later


#include QMK_KEYBOARD_H

enum layers {
    _ALPHA_COLEMAK = 0,
    _ALPHA_QWERTY,
    _SYM,
    _NAV,
    _NUM,
    _CFG,
};

// start SM Tap Dance (sm_td or smtd for short) user library for QMK

enum custom_keycodes {
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    CKC_A, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_R,
    CKC_S,
    CKC_T,
    CKC_N,
    CKC_E,
    CKC_I,
    CKC_O,
    CKC_NA,
    CKC_NR,
    CKC_NS,
    CKC_NT,
    CKC_ESC,
    CKC_SPC,
    CKC_TAB,
    CKC_ENT,
    // Add custom keycodes for umlauts
    UM_A,
    UM_O,
    UM_U,
    UM_SS,
    SMTD_KEYCODES_END,
};

#include "sm_td.h"

// Process tap dance records
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }
    return true;
}

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_A, KC_A, KC_LEFT_CTRL)
        SMTD_MT(CKC_R, KC_R, KC_LEFT_ALT)
        SMTD_MT(CKC_S, KC_S, KC_LEFT_GUI)
        SMTD_MT(CKC_T, KC_T, KC_LSFT)
        SMTD_MT(CKC_N, KC_N, KC_RSFT)
        SMTD_MT(CKC_E, KC_E, KC_RIGHT_GUI)
        SMTD_MT(CKC_I, KC_I, KC_RIGHT_ALT)
        SMTD_MT(CKC_O, KC_O, KC_RIGHT_CTRL)
        // copy and paste in num layout
        SMTD_MT(CKC_NA, RGUI(KC_A), KC_LEFT_CTRL)
        SMTD_MT(CKC_NR, RGUI(KC_X), KC_LEFT_ALT)
        SMTD_MT(CKC_NS, RGUI(KC_C), KC_LEFT_GUI)
        SMTD_MT(CKC_NT, RGUI(KC_V), KC_LSFT)
        // layout switch
        SMTD_LT(CKC_ESC, KC_ESC, _CFG)
        SMTD_LT(CKC_SPC, KC_SPC, _NUM)
        SMTD_LT(CKC_TAB, KC_TAB, _NAV)
        SMTD_LT(CKC_ENT, KC_ENT, _SYM)
        case UM_A:
            if (action == SMTD_ACTION_TAP) {
                tap_code16(LALT(KC_U));
                wait_ms(10);
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(LSFT(KC_A));  // Ä
                } else {
                    tap_code(KC_A);          // ä
                }
            }
            break;
        case UM_O:
            if (action == SMTD_ACTION_TAP) {
                tap_code16(LALT(KC_U));
                wait_ms(10);
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(LSFT(KC_O));  // Ö
                } else {
                    tap_code(KC_O);          // ö
                }
            }
            break;
        case UM_U:
            if (action == SMTD_ACTION_TAP) {
                tap_code16(LALT(KC_U));
                wait_ms(10);
                if (get_mods() & MOD_MASK_SHIFT) {
                    tap_code16(LSFT(KC_U));  // Ü
                } else {
                    tap_code(KC_U);          // ü
                }
            }
            break;
        case UM_SS:
            if (action == SMTD_ACTION_TAP) {
                tap_code16(LALT(KC_S));
            }
            break;
    }
}

// end SM Tap Dance (sm_td or smtd for short) user library for QMK

// start Combos

const uint16_t PROGMEM lock_device[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM close_app[]   = {KC_Q, KC_P, COMBO_END};
const uint16_t PROGMEM caps_lock[]   = {KC_P, KC_L, COMBO_END};
const uint16_t PROGMEM caps_word[]   = {CKC_T, CKC_N, COMBO_END};
const uint16_t PROGMEM TD_AE[] = {CKC_A, CKC_R, COMBO_END};
const uint16_t PROGMEM TD_OE[] = {CKC_I, CKC_O, COMBO_END};
const uint16_t PROGMEM TD_UE[] = {KC_U, KC_Z, COMBO_END};
const uint16_t PROGMEM TD_SS[] = {KC_S, KC_S, COMBO_END};
const uint16_t PROGMEM TD_ENT[] = {CKC_S, CKC_T, COMBO_END};
const uint16_t PROGMEM TD_BSPC[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM TD_SCREENSHOT[] = {KC_C, KC_D, COMBO_END};
combo_t key_combos[]  = {
    COMBO(lock_device, LCTL(RGUI(KC_Q))),
    COMBO(close_app, RGUI(KC_Q)),
    COMBO(caps_lock, KC_CAPS),
    COMBO(caps_word, QK_CAPS_WORD_TOGGLE),
    COMBO(TD_AE, UM_A),        // ä/Ä
    COMBO(TD_OE, UM_O),        // ö/Ö
    COMBO(TD_UE, UM_U),        // ü/Ü
    COMBO(TD_SS, UM_SS),       // ß
    COMBO(TD_ENT, KC_ENT),
    COMBO(TD_BSPC, KC_BSPC),
    COMBO(TD_SCREENSHOT, LGUI(LSFT(KC_4))),
};

// end Combos

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

    [_ALPHA_COLEMAK] = LAYOUT_split_3x5_3(
        KC_Q,     KC_W,    KC_F,    KC_P,    KC_B,                                                             KC_J,    KC_L,    KC_U,    KC_Z,    KC_MINS,
        CKC_A, CKC_R, CKC_S, CKC_T, KC_G,                                                                     KC_M, CKC_N, CKC_E, CKC_I, CKC_O,
        KC_Y, KC_X, KC_C, KC_D, KC_V,                                                              KC_K,    KC_H,    KC_COMMA, KC_DOT,  KC_SLASH,
                CKC_ESC, CKC_SPC, CKC_TAB,                                                                         KC_BSPC, CKC_ENT, KC_DEL
    ),
    [_ALPHA_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        LCTL_T(KC_A), LALT_T(KC_S), LGUI_T(KC_D), LSFT_T(KC_F), KC_G,                                KC_H, RSFT_T(KC_J), RGUI_T(KC_K), RALT_T(KC_L), RCTL_T(KC_SCLN),
        KC_Z, KC_X,    KC_C,    KC_V,    KC_B,                                                                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
             LT(_CFG,KC_ESCAPE), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),                                      KC_BSPC, LT(_SYM, KC_ENT), KC_DEL
    ),
    [_SYM] = LAYOUT_split_3x5_3(
        RALT(KC_8) , LSFT(KC_6),   LSFT(KC_RBRC),  LSFT(KC_2), XXXXXXX,                          RSFT(KC_EQUAL), KC_NONUS_BACKSLASH, KC_GRAVE, RSFT(KC_GRAVE), XXXXXXX,
        RALT(KC_5), LSFT(KC_4), RALT(KC_L), LSFT(KC_7), KC_RBRC,                                   RSFT(KC_NONUS_HASH), LALT(KC_N), XXXXXXX, XXXXXXX, XXXXXXX,
        LSFT(KC_MINUS), LSFT(KC_1), RSFT(KC_5), KC_NONUS_HASH, RALT(KC_7),                      KC_EQUAL, XXXXXXX, KC_MINS, XXXXXXX, XXXXXXX,
                LSFT(KC_8), LSFT(KC_9), LSFT(KC_SLASH),                                                       XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_NAV] = LAYOUT_split_3x5_3(
        XXXXXXX,  KC_F7, KC_F8, KC_F9, KC_F10,                                                                 XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
        LCTL_T(XXXXXXX), LALT_T(KC_F4),  LGUI_T(KC_F5),  LSFT_T(KC_F6),  KC_F11,                     KC_HOME, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,
        XXXXXXX,  KC_F1,  KC_F2,  KC_F3,  KC_F12,                                                              XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                  XXXXXXX, XXXXXXX, XXXXXXX,                                                                         XXXXXXX, MO(_CFG), XXXXXXX
    ),
     [_NUM] = LAYOUT_split_3x5_3(
        KC_MUTE, KC_VOLD, LGUI(KC_F), KC_VOLU, XXXXXXX,                                                     KC_RBRC,  KC_7,  KC_8,  KC_9,  RALT(KC_9),
        CKC_NA, CKC_NR, CKC_NS, CKC_NT, RGUI(KC_Y),                                                               RSFT(KC_0),  KC_4,  KC_5,  KC_6, RALT(KC_6),
        XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                                                         RSFT(RALT(KC_7)),  KC_1,  KC_2,  KC_3, KC_DOT,
                  XXXXXXX, XXXXXXX, XXXXXXX,                                                                           KC_BSPC, KC_0, KC_PENT
    ),
        [_CFG] = LAYOUT_split_3x5_3(
        LALT(KC_Q), XXXXXXX, XXXXXXX, LALT(KC_P), LALT(KC_B),                                             XXXXXXX, XXXXXXX, KC_LBRC,DF(_ALPHA_COLEMAK), DF(_ALPHA_QWERTY),
        LALT(KC_A), XXXXXXX, LALT(KC_S), RSFT_T(LALT(KC_T)), LALT(KC_G),                              XXXXXXX, RSFT_T(XXXXXXX), XXXXXXX, XXXXXXX, KC_SCLN,
        LALT(KC_Y), XXXXXXX, LALT(KC_C), LALT(KC_D), LALT(KC_V),                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                XXXXXXX, XXXXXXX, XXXXXXX,                                                                          XXXXXXX, XXXXXXX, QK_BOOT
    )
    // clang-format on
};