#ifndef CONFIG_UPLUS
#define CONFIG_UPLUS

#define ONESHOT_TAP_TOGGLE 5 // 固定キーロック
#define ONESHOT_TIMEOUT 3000 // Time (in ms) before the one shot key is released

#define PERMISSIVE_HOLD

#undef LED_BRIGHTNESS_LO
#undef LED_BRIGHTNESS_HI
#define LED_BRIGHTNESS_LO       1
#define LED_BRIGHTNESS_HI       1

#undef MOUSEKEY_INTERVAL
#undef MOUSEKEY_DELAY
#undef MOUSEKEY_TIME_TO_MAX
#undef MOUSEKEY_MAX_SPEED
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY    0

#endif
