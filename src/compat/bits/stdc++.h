/*
============================================================
 <bits/stdc++.h> compatibility header
============================================================

A few example files include the GNU-only header <bits/stdc++.h>.
GCC ships it, but MSVC and Apple Clang do not. When CMake detects
MSVC it adds src/compat to the include path, and this file is used
instead so the same examples compile unchanged.

This header intentionally includes the standard headers that the
examples in this repository use. Add more only when a file needs
them; keeping the list short makes build errors easier to read.
*/

#ifndef DSA_COMPAT_BITS_STDCXX_H
#define DSA_COMPAT_BITS_STDCXX_H

#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#endif // DSA_COMPAT_BITS_STDCXX_H
