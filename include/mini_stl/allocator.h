#pragma once

#include "construct.h"
#include <cstddef>
#include <limits>
#include <new>

namespace mini_stl {

template <typename T> class allocator {
public:
  using value_type = T;
  using pointer = T *;
  using size_type = std::size_t;

  pointer allocate(size_type n) {
    if (n == 0)
      return nullptr;

    if (n > std::numeric_limits<size_type>::max() / sizeof(T)) {
      throw std::bad_array_new_length();
    }

    return static_cast<pointer>(::operator new(n * sizeof(T)));
  }

  void deallocate(pointer p, size_type /*n*/) noexcept {
    ::operator delete(static_cast<void *>(p));
  }

  template <typename... Args> void construct(pointer p, Args &&...args) {
    mini_stl::construct(p, static_cast<Args &&>(args)...);
  }

  void destroy(pointer p) { mini_stl::destroy(p); }
};
} // namespace mini_stl
