
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#

BOOTMAGIC_ENABLE  = no  # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE   = yes # Mouse keys(+4700)
EXTRAKEY_ENABLE   = yes # Audio control and System control(+450)
CONSOLE_ENABLE    = no  # Console for debug(+400)
COMMAND_ENABLE    = no  # Commands for debug and configuration
NKRO_ENABLE       = yes # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE  = no  # Enable keyboard backlight functionality
MIDI_ENABLE       = no  # MIDI controls
AUDIO_ENABLE      = no  # Audio output on port C6
UNICODE_ENABLE    = yes # Unicode
BLUETOOTH_ENABLE  = no  # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE   = no  # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no  # Enable one-hand typing

# HELIX_ROWS = 5              # Helix Rows is 4 or 5
OLED_ENABLE = yes           # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = no         # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
Link_Time_Optimization = no # if firmware size over limit, try this option

# convert Helix-specific options (that represent combinations of standard options)
#   into QMK standard options.
include $(strip $(KEYBOARD_LOCAL_FEATURES_MK))
