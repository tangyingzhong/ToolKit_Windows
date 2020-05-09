#pragma once

#include <SDKDDKVer.h>

// Close This function or variable may be unsafe Warning: C4996
#define _CRT_SECURE_NO_DEPRECATE

// Close the warning of not saving file as UNICODE encode. C4819
#define NO_WARN_MBCS_MFC_DEPRECATION

// Test frame work needing head file
#include "CppUnitTest.h"

// Filter some paramenters not use again
#define WIN32_LEAN_AND_MEAN       

#include "Tool/Toolkit.h"
