#include <stdbool.h>

enum CuteLogLevel {
    NONE,
    LOG,
    INFO,
    WARN,
    ERR, 
    DEBUG
};

typedef struct {
    unsigned int color1, color2, color3, color4, color5, color6;
} CuteColorScheme;

typedef struct {
    char *name;
    CuteColorScheme color_scheme;
    bool show_time;
    bool is_dynamic; // For internal use only, do not change the value
} CuteProfile;

extern CuteProfile cute_new_profile(char *name, bool show_time);

extern CuteProfile *cute_new_dynamic_profile(char *name, bool show_time);

extern void cute_destroy_dynamic_profile(CuteProfile *profile);

extern char *cute_log_level_str(enum CuteLogLevel level);

extern void cute_log(CuteProfile *profile, enum CuteLogLevel level, const char *message_fmt, ...);
