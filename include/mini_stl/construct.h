#pragma once

#include "utility.h"

namespace mini_stl {

template <typename T, typename... Args> void construct(T *ptr, Args &&...args) {
  ::new (static_cast<void *>(ptr)) T(mini_stl::forward<Args>(args)...);
}

template <typename T> void destroy(T *ptr) { ptr->~T(); }

template <typename ForwardIt> void destroy(ForwardIt first, ForwardIt last) {
  for (; first != last; ++first) {
    mini_stl::destroy(&*first);
  }
}

} // namespace mini_stl
