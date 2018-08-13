#include "keycode_config.h"
#include "action.h"

#if (__has_include("secrets.h"))
#include "secrets.h"
#else
#define SENDSTRING_MM1 ""
#define SENDSTRING_MM2 ""
#define SENDSTRING_MM3 ""
#define SENDSTRING_MM4 ""
#define SENDSTRING_MM5 ""
#define SENDSTRING_MM6 ""
#endif

// easier to read
#define KBD_HALT     false
#define KBD_CONTINUE true

// custom keys:

// "MMENU" is a macro for "CMD+SPC" (aka Spotlight/Alfred)
#define ________ KC_TRNS
#define __ KC_NO

// sticky settings
#define STICKY_LOCK_DELAY 200
#define STICKY_AUTO_OFF 250

// tap-hold settings
#define LONGPRESS_DELAY 250

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

void scan_tap_hold(taphold_state state);
void scan_sticky_auto_off(void);

bool process_record_user_sleep(uint16_t keycode, keyrecord_t *record);
bool process_record_user_reset(uint16_t keycode, keyrecord_t *record);
bool process_record_user_goto_colemak(uint16_t keycode, keyrecord_t *record);
bool process_record_user_goto_bracket(uint16_t keycode, keyrecord_t *record);
bool process_record_user_goto_fn(uint16_t keycode, keyrecord_t *record);
bool process_record_user_goto_lock(uint16_t keycode, keyrecord_t *record);
bool process_record_user_taphold(uint16_t keycode, keyrecord_t *record);
bool process_record_user_sticky(uint16_t keycode, keyrecord_t *record);
bool process_record_user_dyn_macro(uint16_t keycode, keyrecord_t *record);
bool process_record_user_macro(uint16_t keycode, keyrecord_t *record);
bool process_record_user_babyproof(uint16_t keycode, keyrecord_t *record);
bool process_record_user_keycap_leds(uint16_t keycode, keyrecord_t *record);

void process_record_after_sticky_clear(void);

uint8_t current_mods(void);
void set_current_mods(uint8_t prev_mods, uint8_t current_mods);
void clear_sticky_mods(void);
void update_mods(uint8_t prev_mods);
void taphold_tapped(uint8_t index, bool pressed);
