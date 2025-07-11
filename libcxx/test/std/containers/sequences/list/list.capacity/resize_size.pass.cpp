//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <list>

// void resize(size_type sz); // constexpr since C++26

#include <list>
#include <cassert>

#include "test_macros.h"
#include "DefaultOnly.h"
#include "min_allocator.h"

TEST_CONSTEXPR_CXX26 bool test() {
  {
    std::list<int> l(5, 2);
    l.resize(2);
    assert(l.size() == 2);
    assert(std::distance(l.begin(), l.end()) == 2);
    assert(l == std::list<int>(2, 2));
  }
  {
    std::list<int> l(5, 2);
    l.resize(10);
    assert(l.size() == 10);
    assert(std::distance(l.begin(), l.end()) == 10);
    assert(l.front() == 2);
    assert(l.back() == 0);
  }
#if TEST_STD_VER >= 11
  if (!TEST_IS_CONSTANT_EVALUATED) {
    {
      std::list<DefaultOnly> l(10);
      l.resize(5);
      assert(l.size() == 5);
      assert(std::distance(l.begin(), l.end()) == 5);
    }
    {
      std::list<DefaultOnly> l(10);
      l.resize(20);
      assert(l.size() == 20);
      assert(std::distance(l.begin(), l.end()) == 20);
    }
    {
      std::list<DefaultOnly, min_allocator<DefaultOnly>> l(10);
      l.resize(5);
      assert(l.size() == 5);
      assert(std::distance(l.begin(), l.end()) == 5);
    }
    {
      std::list<DefaultOnly, min_allocator<DefaultOnly>> l(10);
      l.resize(20);
      assert(l.size() == 20);
      assert(std::distance(l.begin(), l.end()) == 20);
    }
  }
  {
    std::list<int, min_allocator<int>> l(5, 2);
    l.resize(2);
    assert(l.size() == 2);
    assert(std::distance(l.begin(), l.end()) == 2);
    assert((l == std::list<int, min_allocator<int>>(2, 2)));
  }
  {
    std::list<int, min_allocator<int>> l(5, 2);
    l.resize(10);
    assert(l.size() == 10);
    assert(std::distance(l.begin(), l.end()) == 10);
    assert(l.front() == 2);
    assert(l.back() == 0);
  }
#endif

  return true;
}

int main(int, char**) {
  assert(test());
#if TEST_STD_VER >= 26
  static_assert(test());
#endif

  return 0;
}
