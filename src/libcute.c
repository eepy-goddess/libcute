#include "libcute.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern CuteProfile cute_new_profile(char *name, bool show_time) {
    CuteProfile profile;
    profile.name = name;
    profile.show_time = show_time;
    profile.is_dynamic = false;
    return profile;
}

extern CuteProfile *cute_new_dynamic_profile(char *name, bool show_time) {
    CuteProfile *profile = (CuteProfile *) malloc(sizeof(CuteProfile));
    if(profile == NULL) {
        fprintf(stderr, "Unable to make heap-allocated libcute profile! Possibly not enough memory?\n");
        return NULL;
    }
    profile->name = name;
    profile->show_time = show_time;
    profile->is_dynamic = true;
    return profile;
}

extern void cute_destroy_dynamic_profile(CuteProfile *profile) {
    if (profile->is_dynamic) {
        cute_err_log(profile, "Attempted to free a libcute profile stored on the stack. Please fix.", 0);
        return;
    }
    free(profile);
}

extern void cute_log(CuteProfile *profile, const char *message) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *name = profile->name;
    profile->show_time ? printf("%s %s: %s\n", asctime(timeinfo), name, message) : printf("%s: %s\n", name, message);
}

/* I'll do error code parsing soon, leave me alone TwT */
extern void cute_err_log(CuteProfile *profile, const char *message, int err_code) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char* name = profile->name;
    profile->show_time ? fprintf(stderr, "%s %s: %s\n", asctime(timeinfo), name, message) : fprintf(stderr, "%s: %s\n", name, message);
}
