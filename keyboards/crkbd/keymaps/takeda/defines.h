extern keymap_config_t keymap_config;

// Layers
#define _DH 0
#define _QW 1
#define _DV 2
#define _GMG 3
#define _LO 4
#define _RA 5
#define _AD 6

#define IDLE_TIMEOUT 5000
#define IDLE_SLEEP 60000

enum keycodes {
  MODDH = SAFE_RANGE,
  QWERTY,
  DVORAK,
  M_BSPC,
  M_WIPE,
  M_RGBRS,
  M_RAN64,
  UC_FLIP,
  UC_TABL,
  UC_SHRG,
  UC_DISA,
  UC_DANC,
  UC_SCRE,
  UC_WALL,
  UC_SOB,
  UC_DEAL,
  UC_RAGE,
  UC_NOOO,
  UC_SALU,
  UC_LENY,
  UC_WHAT,
  UC_CRY,
  UC_SHR2,
  UC_HAPY,
  UC_STRG,
  M_MAC_CHG,
  COPY,
  CUT,
  PASTE,
  GAMING
};

// Shortcuts
#define EMOJI TT(_EM)

// Mod-Taps
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_advanced_keycodes.md
#define LST(X) LSFT_T(X)
#define RST(X) RSFT_T(X)
#define LCT(X) LCTL_T(X)
#define RCT(X) RCTL_T(X)
#define LGT(X) LGUI_T(X)
#define RGT(X) RGUI_T(X)
#define TAT(X) LALT_T(X)
#define AGT(X) RALT_T(X)
#define MCPY(X) LT(COPY, X)
#define MCUT(X) LT(CUT, X)
#define MPST(X) LT(PASTE, X)
//GACS
//CAGS

// Modifiers
#define LT_ESC LT(_AD, KC_ESC)
#define LT_GUI LT(_AD, KC_RGUI)
#define LT_TAB LT(_LO, KC_TAB)
#define LT_DEL LT(_RA, KC_DEL)
#define LT_SPC LT(_LO, KC_SPC)
#define S_SPC LSFT_T(KC_SPC)
#define S_TAB LSFT_T(KC_TAB)
#define S_DEL RSFT_T(KC_DEL)
#define LT_BSPC LT(_RA, KC_BSPC)
