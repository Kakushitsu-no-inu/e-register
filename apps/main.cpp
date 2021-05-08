#include "application.h"

int main() {
  auto clg = application::get_instance();
  try {
    clg.run();
  } catch (std::exception &err) {
    std::cout << err.what() << std::endl;
  }
  return 0;
}
