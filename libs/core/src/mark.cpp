#include "mark.h"

size_t mark::count{};

mark::mark(std::string_view value, std::string_view subject, const std::tm &date)
  : value{value}, subject{subject}, date{date} {
  id = count++;
}

std::string mark::time_to_string() const {
  char c[12];
  std::strftime(c, 12, "%d.%m.%Y", &date);
  return std::string{c};
}
