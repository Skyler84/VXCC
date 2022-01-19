/*
 * Licence: GNU GPL-3
 *
 * Copyright (c) 2022, Skyler Mansfield <skyler.mansfield.21@gmail.com>
 */

#pragma once

#include <cassert>

#define TODO(x) assert(false && "TODO: " #x)
#define VERIFY(x) assert(x)
#define UNIMPLEMENTED(x) assert(false && "Unimplemented: " #x)
#define UNREACHABLE(x) assert(false && "Unreachable: " #x)
