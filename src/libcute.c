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
        cute_log(profile, ERR, "Attempted to free a libcute profile stored on the stack. Please fix.");
        return;
    }
    
    free(profile);
}

char *cute_log_level_str(enum CuteLogLevel level) {
    char *log_level;
    
    switch (level) {
        default:
            log_level = "";
            break;
        case LOG:
            log_level = "[LOG]";
            break;
        case INFO:
            log_level = "[INFO]";
            break;
        case WARN:
            log_level = "[WARNING]";
            break;
        case ERR:
            log_level = "[ERROR]";
            break;
        case DEBUG:
            log_level = "[DEBUG]";
            break;
    }
 
    return log_level;
}

void cute_log(CuteProfile *profile, enum CuteLogLevel level, const char *message) {
    struct tm *timeinfo;
    char *time_str;
    char *name = profile->name;
    char *level_str = cute_log_level_str(level);

    if (profile->show_time){
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        time_str = asctime(timeinfo);

        printf("[%.*s] %s [%s]: %s\n", (int) strlen(time_str) - 1, time_str, level_str, name, message);
    } else {
        printf("%s [%s]: %s\n", level_str, name, message);
    }
}
