#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
  _QWERTY = 0,
  _SUB,
  _MISC,
  _ADVANCE
};


enum custom_keycodes {
  QWERTY = SAFE_RANGE, // 使用可能なキーコード
  COLEMAK,
  DVORAK,
  SUB,
  MISC,
  ADVANCE,

  BACKLIT,
  EISU,
  KANA,
  RGBRST,

  DYNAMIC_MACRO_RANGE, // このコード以降にダイナミックマクロのキーが割り当てられる
};

#undef C
#undef A
#undef G

#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define __XXX__ KC_TRNS // 明示的透過

#define O(key) OSM(MOD_##key)
#define C(key) RCTL(KC_##key)
#define A(key) RALT(KC_##key)
#define G(key) RGUI(KC_##key)
#define C_T(key) RCTL_T(KC_##key)
#define A_T(key) RALT_T(KC_##key)
#define G_T(key) RGUI_T(KC_##key)

#define LO_S OSL(_SUB)
#define LO_M OSL(_MISC)
#define LO_A OSL(_ADVANCE)
#define L_S(key) LT(_SUB, KC_##key)
#define L_M(key) LT(_MISC, KC_##key)
#define L_A(key) LT(_ADVANCE, KC_##key)

// QK_LCTL | QK_LSFT | QK_LALT | QK_LGUI
#define H(key)  HYPR(KC_##key)
#define CA(key) RCTL(RALT(KC_##key))
#define GA(key) RGUI(RALT(KC_##key))
#define GC(key) RGUI(RCTL(KC_##key))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Main layer
  [_QWERTY] = LAYOUT( \
    KC_APP,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    DM_RSTP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINUS,
    C_T(ENT),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, L_M(QUOT),
    L_M(TAB),KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, L_A(BSLS),
    KC_MPLY, KC_LGUI, KC_LALT, KC_GRV,  KC_ESC,  O(LSFT), KC_LCTL, LO_S,    KC_SPC,  KC_MINUS,KC_EQL,  KC_LALT, KC_RGUI, KC_ENT
    // tty切替に使うためにRALT -> LALT
    ),

    // F1~F12, Backspace, Delete, Cursor keys, Lang keys, Symbols
  [_SUB] = LAYOUT( \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12,
    _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LANG5,KC_F11,
    __XXX__, KC_BSPC, KC_DEL,  XXXXXXX, XXXXXXX, KC_TILD,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LANG2,XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV,  KC_LPRN, KC_RPRN, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_LANG1,XXXXXXX,
    _______, __XXX__, __XXX__, _______, __XXX__, __XXX__, _______, _______, __XXX__, __XXX__, _______, __XXX__, __XXX__, _______
    ),

    // Mouse keys, Window control shortcuts
  [_MISC] = LAYOUT( \
    XXXXXXX, KC_FN1,  KC_FN2,  KC_FN3,  KC_FN4,  KC_FN5,                    KC_FN6,  KC_FN7,  KC_FN8,  KC_FN9,  KC_FN10, KC_FN12,
    _______, KC_BTN3, KC_WBAK, KC_MS_U, KC_WFWD, G(R),                      GC(Y),   GC(U),   GC(I),   GC(O),   XXXXXXX, KC_FN11,
    __XXX__, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,                   GA(LEFT),GA(DOWN),GA(UP),  GA(RGHT),XXXXXXX, __XXX__,
    __XXX__, KC_BTN2, KC_WH_L, G(M),    KC_WH_R, KC_WH_D, _______, _______, G(LEFT), G(DOWN), G(UP),   G(RGHT), XXXXXXX, __XXX__,
    _______, __XXX__, __XXX__, _______, __XXX__, __XXX__, _______, KC_ACL0, KC_ACL2, KC_ACL1, _______, __XXX__, __XXX__, _______
    ),

    // Media keys, Media control shortcuts, Dynamic macro keys, Sleep, etc...
    // RGB ON| HUE+ | SAT+ | VAL+ |
    // ------+------+------+------|
    //  MODE | HUE- | SAT- | VAL- |
    // ---------------------------'
    // RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI
    // RGB_SMOD,RGB_HUD, RGB_SAD, RGB_VAD
  [_ADVANCE] =  LAYOUT( \
    RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SLEP,
    DEBUG,   DM_RSTP, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX,                   XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
    __XXX__, DM_REC1, DM_PLY1, XXXXXXX, CA(T),   XXXXXXX,                   H(A),    H(B),    H(C),    H(D),    H(G),    __XXX__,
    TERM_ON, DM_REC2, DM_PLY1, CA(D),   CA(Y),   CA(B),   _______, _______, H(E),    KC_MPRV, KC_MPLY, KC_MNXT, H(F),    __XXX__,
    TERM_OFF,__XXX__, __XXX__, _______, __XXX__, __XXX__, _______, _______, __XXX__, __XXX__, _______, __XXX__, __XXX__, _______
    )
};


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADVANCE layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        // persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        // persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case SUB:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_SUB);
        update_tri_layer_RGB(_SUB, _MISC, _ADVANCE);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_SUB);
        update_tri_layer_RGB(_SUB, _MISC, _ADVANCE);
      }
      return false;
      break;
    case MISC:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_MISC);
        update_tri_layer_RGB(_SUB, _MISC, _ADVANCE);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_MISC);
        TOG_STATUS = false;
        update_tri_layer_RGB(_SUB, _MISC, _ADVANCE);
      }
      return false;
      break;
    case ADVANCE:
        if (record->event.pressed) {
          layer_on(_ADVANCE);
        } else {
          layer_off(_ADVANCE);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_SUB (1<<_SUB)
#define L_MISC (1<<_MISC)
#define L_ADVANCE (1<<_ADVANCE)
#define L_ADJUST_TRI (L_ADVANCE|L_MISC|L_SUB)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      matrix_write(matrix, buf);
  }
#endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_MISC:
           matrix_write_P(matrix, PSTR("Misc"));
           break;
        case L_SUB:
           matrix_write_P(matrix, PSTR("Sub"));
           break;
        case L_ADVANCE:
        // case L_ADVANCE_TRI:
           matrix_write_P(matrix, PSTR("Advance"));
           break;
        default:
           matrix_write_P(matrix, PSTR("Undef-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static const char os_logo[][3][3] PROGMEM = {{{0x95,0x96,0},{0xb5,0xb6,0}}, {{0x97,0x98,0},{0xb7,0xb8,0}}, {{0x99,0x9a,0},{0xb9,0xba,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write_P(matrix, os_logo[2][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[2][1]);
  }else{
    matrix_write_P(matrix, os_logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[1][1]);
  }

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboard LED Status
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
  render_rgbled_status(true, matrix);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_rgbled_status(false, &matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
