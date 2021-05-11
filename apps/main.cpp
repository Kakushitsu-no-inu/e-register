#include "application.h"

int main() {
  auto clg = application::get_instance();
  clg.run();
  return 0;
}
