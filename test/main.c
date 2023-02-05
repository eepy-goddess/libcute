#include "../src/libcute.h"
#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
#else // _WIN32
    #include <unistd.h>
#endif // _WIN32

int main() {
    CuteProfile *profile = cute_new_dynamic_profile("test", true);
    cute_log(profile, LOG, "running with libcute");
    cute_log(profile, ERR, "testing error logging");
    cute_log(profile, LOG, "testing time logging");
    sleep(3);
    cute_log(profile, LOG, "testing time logging");
    CuteProfile *dyn_profile = cute_new_dynamic_profile("dynamic-profile", true);
    cute_log(dyn_profile, LOG, "Testing dynamic profile");
    cute_log(dyn_profile, INFO, "Freeing dynamic profile");
    cute_destroy_dynamic_profile(dyn_profile);
    cute_log(profile, LOG, "The test is now over uwu");
    cute_destroy_dynamic_profile(profile);
    printf("size: %zu", sizeof(CuteProfile));
    return 0;
}
