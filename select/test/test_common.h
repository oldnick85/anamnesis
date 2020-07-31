#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <cstdio>
#include <chrono>
#include <memory>
#include <vector>
#include "ccombinecombination.h"
#include "ccombinepermutation.h"
#include "csetgensingle.h"
#include "csetgendouble.h"
#include "ccasket.h"

#define TEST_MAX_COUNT 100

using TimePoint_t = std::chrono::time_point<std::chrono::high_resolution_clock>;

#endif // TEST_COMMON_H
