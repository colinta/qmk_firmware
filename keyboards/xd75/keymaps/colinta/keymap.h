/* Copyright 2017 Colin T.A. Gray
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keycode_config.h"
#include "action.h"

#if (__has_include("secrets.h"))
#include "secrets.h"
#else
#define SENDSTRING_MM1 ""
#define SENDSTRING_MM2 ""
#define SENDSTRING_MM3 ""
#define SENDSTRING_MM4 ""
#endif

// easier to read
#define KBD_HALT     false
#define KBD_CONTINUE true

// layers:
// - colemak
// - record-mode (adds stop buttons)
// - qwerty
// - record-mode (adds stop buttons)
// - fn (start recording, change to colemak/qwerty)
// - lock
#define LAYER_COLEMAK 0
#define LAYER_RECORD_CM 1
#define LAYER_QWERTY 2
#define LAYER_RECORD_QW 3
#define LAYER_FN 4
#define LAYER_LOCK 5

// custom keys:

// "MMENU" is a macro for "CMD+SPC" (aka Spotlight/Alfred)
#define MMENU LGUI(KC_SPC)
#define ________ KC_TRNS
#define __ KC_NO
#define DM_1 DYN_MACRO_PLAY1
#define DM_2 DYN_MACRO_PLAY2
#define REC1 DYN_REC_START1
#define REC2 DYN_REC_START2
#define STOP DYN_REC_STOP

// sticky settings
#define STICKY_LOCK_DELAY 200
#define STICKY_AUTO_OFF 250

// tap-hold settings
#define LONGPRESS_DELAY 250

// recording settings
#define RECORDING_BLINK 500

typedef struct {
    bool is_pressed;
    uint16_t timer;
    uint16_t kc_tap;
    uint16_t kc_hold;
    uint8_t mods;
} taphold_t;

typedef enum {
    TAPPED,
    HELD,
} taphold_state;

typedef struct {
    bool enabled;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint16_t timer;
    uint8_t life;
} rgblight_fadeout;

void rgb_init(void);
void scan_tap_hold(taphold_state state);
void scan_rgblight_fadeout(void);
void scan_sticky_auto_off(void);

bool process_record_user_sleep(uint16_t keycode, keyrecord_t *record);
bool process_record_user_reset(uint16_t keycode, keyrecord_t *record);
bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record);
bool process_record_user_goto_layer(uint16_t keycode, keyrecord_t *record);
bool process_record_user_fnlayer(uint16_t keycode, keyrecord_t *record);
bool process_record_user_taphold(uint16_t keycode, keyrecord_t *record);
bool process_record_user_sticky(uint16_t keycode, keyrecord_t *record);
bool process_record_user_dyn_macro(uint16_t keycode, keyrecord_t *record);
bool process_record_user_macro(uint16_t keycode, keyrecord_t *record);
bool process_record_user_babyproof(uint16_t keycode, keyrecord_t *record);
bool process_record_user_keycap_leds(uint16_t keycode, keyrecord_t *record);

void process_record_after_sticky_clear(void);
void process_record_after_rgb(void);

uint8_t current_mods(void);
void set_current_mods(uint8_t prev_mods, uint8_t current_mods);
void clear_sticky_mods(void);
void update_mods(uint8_t prev_mods);
void start_rgb_light(void);
void taphold_tapped(uint8_t index, bool pressed);
