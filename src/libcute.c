#include <errno.h>
#include "libcute.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static time_t rawtime;

CuteProfile cute_new_profile(char *name, bool show_time) {
    CuteProfile profile;
    profile.name = name;
    profile.show_time = show_time;
    profile.is_dynamic = false;
    return profile;
}

CuteProfile *cute_new_dynamic_profile(char *name, bool show_time) {
    CuteProfile *profile = (CuteProfile *) malloc(sizeof(CuteProfile));
    if (profile == 0) {
        fprintf(stderr, "Error: %d\nUnable to make heap-allocated libcute profile! Possibly not enough memory?\nExiting to prevent further damage to the program\n", ENOMEM);
        abort();
    }
    profile->name = name;
    profile->show_time = show_time;
    profile->is_dynamic = true;
    return profile;
}

void cute_destroy_dynamic_profile(CuteProfile *profile) {
    if (profile == 0) {
        fprintf(stderr, "Attempted to free a null libcute profile pointer. Please fix.");
        abort();
    }
    if (!profile->is_dynamic) {
        cute_err_log(profile, "Attempted to free a libcute profile stored on the stack. Please fix.", 0);
        return;
    }
    free(profile);
}

void cute_log(CuteProfile *profile, const char *message) {
    struct tm *timeinfo;
    char *time_str;
    char *name = profile->name;
    
    if (profile->show_time){
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        time_str = asctime(timeinfo);

        printf("%.*s %s: %s\n", (int) strlen(time_str) - 1, time_str, name, message);
    } else {
        printf("%s: %s\n", name, message);
    }
}

/* I'll do error code parsing soon, leave me alone TwT */
void cute_err_log(CuteProfile *profile, const char *message, unsigned int err_code) {
    struct tm *timeinfo;
    char *time_str;
    char *name = profile->name;

    if (profile->show_time){
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        time_str = asctime(timeinfo);
        
        fprintf(stderr, "%.*s Error code: %d, %s: %s\n", (int) strlen(time_str) - 1, time_str, err_code, name, message);
    } else {
        fprintf(stderr, "Error code: %d, %s: %s\n", err_code, name, message);
    }
}
