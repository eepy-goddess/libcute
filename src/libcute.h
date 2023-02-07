#include <stdbool.h>

typedef enum {
    NONE,
    LOG,
    INFO,
    WARN,
    ERR, 
    DEBUG
} CuteLogLevel;

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

extern int cute_exit_if_null(void *pointer, char *message);

extern CuteProfile *cute_new_dynamic_profile(char *name, bool show_time);

extern void cute_destroy_dynamic_profile(CuteProfile *profile);

extern char *cute_log_level_str(CuteLogLevel level);

extern void cute_log(CuteProfile *profile, CuteLogLevel level, const char *message_fmt, ...);
