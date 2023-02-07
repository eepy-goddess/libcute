#include <errno.h>
#include "libcute.h"
#include <stdarg.h>
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

int cute_exit_if_null(void *pointer, char *message) {
    if(pointer == 0) {
        fprintf(stderr, "%s\n", message);
        abort();
    }
    return 0;
}

CuteProfile *cute_new_dynamic_profile(char *name, bool show_time) {
    CuteProfile *profile = (CuteProfile *) malloc(sizeof(CuteProfile));
    
    cute_exit_if_null(profile, "Error: Unable to make heap-allocated libcute profile! Possibly not enough memory?\nExiting to prevent further damage to the program");
    
    profile->name = name;
    profile->show_time = show_time;
    profile->is_dynamic = true;

    return profile;
}

void cute_destroy_dynamic_profile(CuteProfile *profile) {
    cute_exit_if_null(profile, "Attempted to free a null heap-allocated libcute profile pointer, please fix.");
    if (!profile->is_dynamic) {
        cute_log(profile, ERR, "Attempted to free a libcute profile stored on the stack. Please fix.");
        return;
    }
    
    free(profile);
}

char *cute_log_level_str(CuteLogLevel level) {
    
    switch (level) {
        case NONE:
            return "[NONE]";
        case LOG:
            return "[LOG]";
        case INFO:
            return "[INFO]";
        case WARN:
            return "[WARN]";
        case ERR:
            return "[ERROR]";
        case DEBUG:
            return "[DEBUG]";
        default:
            fprintf(stderr, "No logging level selected, exiting");
            abort();
    }
 
    return "open an issue at https://github.com/a-weeb-programmer/libcute, this message shouldn't show up unless something is wrong";
}

void cute_log(CuteProfile *profile, CuteLogLevel level, const char *message_fmt, ...) {
    struct tm *timeinfo;
    char *time_str;
    char *name = profile->name;
    char *level_str = cute_log_level_str(level);
    char *log_str_head, *log_str_tail, *log_str;
    size_t head_size, tail_size;

    va_list args;
    va_start(args, message_fmt);

    if (profile->show_time){
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        time_str = asctime(timeinfo);
        head_size = (sizeof(char) * (strlen(time_str) + strlen(level_str) + strlen(name) + strlen("[]  []: ")));
        log_str_head = (char *) malloc(head_size);
        cute_exit_if_null(log_str_head, "Unable to allocate enough memory to make the log string head, exiting");
        
        sprintf(log_str_head, "[%.*s] %s [%s]: ", (int) strlen(time_str) - 1, time_str, level_str, name);
    } else {
        head_size = (sizeof(char) * (strlen(level_str) + strlen(name) + strlen(" []: ")));
        log_str_head = (char *) malloc(head_size);
        cute_exit_if_null(log_str_head, "Unable to allocate enough memory to make the log string head, exiting");

        sprintf(log_str_head, "%s [%s]: ", level_str, name);
    }
    
    tail_size = (sizeof(char) * (strlen(message_fmt) + sizeof(args)));
    log_str_tail = (char *) malloc(tail_size);
    cute_exit_if_null(log_str_tail, "Unable to allocate enough memory to make the log string tail, exiting");
    
    vsprintf(log_str_tail, message_fmt, args);

    log_str = (char *) malloc((sizeof(char) * (strlen(log_str_head) + strlen(log_str_tail))) + 1);
    cute_exit_if_null(log_str, "Unable to allocate enough memory to make the log string, exiting");

    memset(log_str, '\0', (sizeof(char) * (strlen(log_str_head) + strlen(log_str_tail))) + 1);
    strcat(log_str, log_str_head);
    strcat(log_str, log_str_tail);

    printf("%s\n", log_str);

    va_end(args);
    free(log_str);
    free(log_str_head);
    free(log_str_tail);
}
