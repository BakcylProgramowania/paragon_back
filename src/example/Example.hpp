#pragma once

namespace paragon {

class Example {
 public:
  explicit Example(const int sth);
  int get() const;

 private:
  int sth{};
};

}  // namespace paragon