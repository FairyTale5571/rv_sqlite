// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

#include <boost/format.hpp>
#include <boost/filesystem.hpp>


// add headers that you want to pre-compile here
#include "framework.h"

#include <SQLiteCpp/Database.h>


#define CURRENT_VERSION "RV_SQLITE v0.1"
#define MACROS_STRNCPY(x) strncpy_s(output, outputSize, x, _TRUNCATE)
#define CBK(x,y) callbackPtr("rv_sqlite",x,y)

#endif //PCH_H
