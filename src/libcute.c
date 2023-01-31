#include <errno.h>
#include "libcute.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static time_t rawtime;

extern CuteProfile cute_new_profile(char *name, bool show_time) {
    CuteProfile profile;
    profile.name = name;
    profile.show_time = show_time;
    profile.is_dynamic = false;
    return profile;
}

extern CuteProfile *cute_new_dynamic_profile(char *name, bool show_time) {
    CuteProfile *profile = (CuteProfile *) malloc(sizeof(CuteProfile));
    if (profile == 0) {
        fprintf(stderr, "Error: %d\nUnable to make heap-allocated libcute profile! Possibly not enough memory?\nExiting to prevent further damage to the program\n", ENOMEM);
        exit(ENOMEM);
    }
    profile->name = name;
    profile->show_time = show_time;
    profile->is_dynamic = true;
    return profile;
}

extern void cute_destroy_dynamic_profile(CuteProfile *profile) {
    if (profile == 0) {
        fprintf(stderr, "Attempted to free a null libcute profile pointer. Please fix.");
        return;
    }
    if (!profile->is_dynamic) {
        cute_err_log(profile, "Attempted to free a libcute profile stored on the stack. Please fix.", 0);
        return;
    }
    free(profile);
}

extern void cute_log(CuteProfile *profile, const char *message) {
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char *time_str = asctime(timeinfo);
    char *name = profile->name;
    
    for (int i = 0; i < (int) strlen(time_str); i++) {
        if (time_str[i] == '\n') {
            time_str[i] = '\0';
        }
    }

    profile->show_time ? printf("%s %s: %s\n", time_str, name, message) : printf("%s: %s\n", name, message);
}

/* I'll do error code parsing soon, leave me alone TwT */
extern void cute_err_log(CuteProfile *profile, const char *message, unsigned int err_code) {
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    char *time_str = asctime(timeinfo);
    char *name = profile->name;

    for (int i = 0; i < (int) strlen(time_str); i++) {
        if (time_str[i] == '\n') {
            time_str[i] = '\0';
        }
    }

    profile->show_time ? fprintf(stderr, "%s Error code: %d, %s: %s\n", time_str, err_code, name, message) : 
        fprintf(stderr, "Error code: %d, %s: %s\n", err_code, name, message);
}
