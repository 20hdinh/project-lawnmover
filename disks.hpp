///////////////////////////////////////////////////////////////////////////////
// disks.hpp
//
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once



#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <iostream>

enum disk_color { DISK_LIGHT, DISK_DARK};

class disk_state {
private:
  std::vector<disk_color> _colors;

public:
  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_LIGHT) {

    assert(light_count > 0);

    for (size_t i = 1; i < _colors.size(); i += 2) {
      _colors[i] = DISK_DARK;
    }
  }

  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // TODO? Return true when this disk_state is in alternating format. That means
  // that the first disk at index 0 is light, the second disk at index 1
  // is dark, and so on for the entire row of disks.
  bool is_initialized() const {
      for (size_t i = 0; i < total_count(); i++){     //check each position before function
        if (i % 2 == 0){                              //check even position --> should be light
            if (_colors[i] == DISK_DARK) {
              return false;
            }
        } else {                                      //check odd position --> should be dark
            if (_colors[i] == DISK_LIGHT) {
              return false;
            }
        }
      }

      return true;
  }

  // TODO: Return true when this disk_state is fully sorted, with all light disks on
  // the left (low indices) and all dark disks on the right (high indices).
  bool is_sorted() const {
    // is located within disk_state class, can access _colors directly
    for (size_t i = 0; i < total_count() / 2; i++) {
      if (_colors[i] == DISK_DARK) {
        return false;
      }
    }
    for (size_t i = total_count() / 2; i < total_count(); i++) {
      if (_colors[i] == DISK_LIGHT) {
        return false;
      }
    }
    
    return true;
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;

public:

  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }

  const disk_state& after() const {
    return _after;
  }

  unsigned swap_count() const {
    return _swap_count;
  }
};

// DONE TODO: Algorithm that sorts disks using the alternate algorithm.
sorted_disks sort_alternate(const disk_state& before) {
	int numOfSwap = 0;                                                                      //record # of step swap
  auto after = before;  // make copy of the disks to return
    size_t begin = 1;
    size_t end = after.total_count();
    while (begin > end) {
      for (auto i = begin; after.is_index(i); i += 2) {
        if ((after.get(i - 1) == DISK_DARK) && (after.get(i) == DISK_LIGHT)) {
          after.swap(i - 1);
          numOfSwap++;
        }
      }
      begin++;
      end--;
    }
  
  return sorted_disks(after, numOfSwap);
}


// DONE TODO: Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
  int numOfSwap = 0;
  auto after = before;  // make copy of the disks to return
  // would prefer to start with index = 0, but disk_state uses initial position of 1
  // only needs n (i / 2) runs to sort, using i+=2 equivalent b/c always even disks
    for (size_t i = 1; after.is_index(i); i += 2) {
      if (i % 2 == 1) {
        // left to right
        // keeping the index = 1 consistent
        // use j - 1 because last position is already checked
        for (size_t j = 1; after.is_index(j - 1); j++) {
          if ((after.get(j - 1) == DISK_DARK) && (after.get(j) == DISK_LIGHT)) {
            after.swap(j - 1);
            numOfSwap++;
          }
        }
      } else {
        // right to left
        // making sure to keep index consistent
        for (size_t j = after.total_count(); j > 1; j--) {
          if ((after.get(j - 1) == DISK_LIGHT) && (after.get(j - 2) == DISK_DARK)) {
            after.swap(j - 2);
            numOfSwap++;
          }
        }
      }
    }

  return sorted_disks(after, numOfSwap);
}
