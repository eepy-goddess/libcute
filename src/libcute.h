#include <stdbool.h>

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

extern void cute_log(CuteProfile *profile, const char *message);

extern void cute_err_log(CuteProfile *profile, const char *message, int err_code);
