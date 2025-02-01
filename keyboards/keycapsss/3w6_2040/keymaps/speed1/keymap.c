// Copyright 2021 weteor | 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_german_mac_iso.h"
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
    CKC_ESC,
    CKC_SPC,
    CKC_TAB,
    CKC_ENT,
    CKC_U,
    SMTD_KEYCODES_END,
};

#include "sm_td.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }
    return true;
}

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_A, KC_A, KC_LEFT_GUI)
        SMTD_MT(CKC_R, KC_R, KC_LEFT_ALT)
        SMTD_MT(CKC_S, KC_S, KC_LEFT_CTRL)
        SMTD_MT(CKC_T, KC_T, KC_LSFT)
        SMTD_MT(CKC_N, KC_N, KC_RSFT)
        SMTD_MT(CKC_E, KC_E, KC_RIGHT_CTRL)
        SMTD_MT(CKC_I, KC_I, KC_RIGHT_ALT)
        SMTD_MT(CKC_O, KC_O, KC_RIGHT_GUI)
        SMTD_LT(CKC_ESC, KC_ESC, _CFG)
        SMTD_LT(CKC_SPC, KC_SPC, _NUM)
        SMTD_LT(CKC_TAB, KC_TAB, _NAV)
        SMTD_LT(CKC_ENT, KC_ENT, _SYM)
        }
    }


// end SM Tap Dance (sm_td or smtd for short) user library for QMK

// start Combos

const uint16_t PROGMEM lock_device[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM close_app[]   = {KC_Q, KC_P, COMBO_END};
const uint16_t PROGMEM caps_lock[]   = {CKC_T, CKC_N, COMBO_END};
const uint16_t PROGMEM TD_AE[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM TD_OE[] = {KC_U, KC_Z, COMBO_END};
const uint16_t PROGMEM TD_UE[] = {KC_L, KC_U, COMBO_END};
combo_t key_combos[]  = {
    COMBO(lock_device, LCTL(RGUI(KC_Q))),
    COMBO(close_app, RGUI(KC_Q)),
    COMBO(caps_lock, KC_CAPS),
    COMBO(TD_AE, KC_QUOT),
    COMBO(TD_OE, KC_SCLN),
    COMBO(TD_UE, KC_LBRC),
};

// end Combos

// start Tap Dance declarations

enum {
    TD_Y_undo,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_Y_undo]  = ACTION_TAP_DANCE_DOUBLE(KC_Y, RGUI(KC_Y)),
};

// end Tap Dance declarations

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

    [_ALPHA_COLEMAK] = LAYOUT_split_3x5_3(
        KC_Q,     KC_W,    KC_F,    KC_P,    KC_B,                                          KC_J,    KC_L,    KC_U,    KC_Z,    KC_MINS,
        CKC_A, CKC_R, CKC_S, CKC_T, KC_G,                                                  KC_M, CKC_N, CKC_E, CKC_I, CKC_O,
        TD(TD_Y_undo), KC_X, KC_C, KC_D, KC_V,                                           KC_K,    KC_H,    KC_COMMA, KC_DOT,  KC_SLASH,
                CKC_ESC, CKC_SPC, CKC_TAB,                                                      KC_BSPC, CKC_ENT, KC_DEL
    ),
    [_ALPHA_QWERTY] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                                  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,         KC_H, RSFT_T(KC_J), RCTL_T(KC_K), RALT_T(KC_L), RGUI_T(KC_SCLN),
        KC_Z, KC_X,    KC_C,    KC_V,    KC_B,                                          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
             LT(_CFG,KC_ESCAPE), LT(_NUM,KC_SPC), LT(_NAV, KC_TAB),                     KC_BSPC, LT(_SYM, KC_ENT), KC_DEL
    ),
    [_SYM] = LAYOUT_split_3x5_3(
        RALT(KC_8) , LSFT(KC_6),   LSFT(KC_RBRC),  LSFT(KC_2), RALT(KC_9),            RSFT(KC_EQUAL), KC_NONUS_BACKSLASH, KC_GRAVE, RSFT(KC_GRAVE), XXXXXXX,
        LSFT(KC_DOT), LSFT(KC_4), RSFT(KC_5), LSFT(KC_7),  KC_RBRC,                    RSFT(KC_NONUS_HASH), LALT(DE_N), XXXXXXX, XXXXXXX, XXXXXXX,
        LSFT(KC_MINUS), LSFT(KC_1), RALT(KC_L), KC_NONUS_HASH, RALT(KC_7),          KC_EQUAL, XXXXXXX, KC_MINS, XXXXXXX, XXXXXXX,
                LSFT(KC_8), LSFT(KC_9), LSFT(KC_SLASH),                                           XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_NAV] = LAYOUT_split_3x5_3(
        XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,          XXXXXXX, RGUI(KC_V),  RGUI(KC_C), RGUI(KC_X), RGUI(KC_Y),
        KC_MPRV, KC_MPLY, KC_MPLY, KC_MNXT, XXXXXXX,          KC_HOME, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                  XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, MO(_CFG), XXXXXXX
    ),
     [_NUM] = LAYOUT_split_3x5_3(
        XXXXXXX,  KC_F7, KC_F8, KC_F9, KC_F10,                    RALT(KC_5),  KC_7,  KC_8,  KC_9,  RALT(KC_6),
        RGUI(KC_A),  KC_F4,  KC_F5,  KC_F6,  KC_F11,             RSFT(KC_0),  KC_4,  KC_5,  KC_6, RSFT(KC_COMMA),
        XXXXXXX,  KC_F1,  KC_F2,  KC_F3,  KC_F12,                 RSFT(RALT(DE_7)),  KC_1,  KC_2,  KC_3, KC_DOT,
                  XXXXXXX, XXXXXXX, XXXXXXX,                        RSFT(KC_0), KC_0, KC_PENT
    ),
        [_CFG] = LAYOUT_split_3x5_3(
        RGUI(KC_Y), RGUI(KC_X), RGUI(KC_C), RGUI(KC_V), XXXXXXX,          XXXXXXX, XXXXXXX, KC_LBRC,DF(_ALPHA_COLEMAK), DF(_ALPHA_QWERTY),
        KC_QUOT, XXXXXXX, XXXXXXX, LSFT_T(XXXXXXX), XXXXXXX,              XXXXXXX, RSFT_T(XXXXXXX), XXXXXXX, XXXXXXX, KC_SCLN,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                XXXXXXX, XXXXXXX, XXXXXXX,                                            XXXXXXX, XXXXXXX, QK_BOOT
    )
    // clang-format on
};
