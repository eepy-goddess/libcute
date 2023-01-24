#include "../src/libcute.h"

int main() {
  CuteProfile profile = cute_new_profile("test", true);
  cute_log(&profile, "Test with libcute is running uwu");
  return 0;
}
