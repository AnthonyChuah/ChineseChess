#ifndef INCLUDES_H
#define INCLUDES_H

// Macros for unit types.
#define UNIT 0
#define SOLDIER 1
#define CANNON 2
#define CHARIOT 3
#define HORSEMAN 4
#define ELEPHANT 5
#define MANDARIN 6
#define GENERAL 7
// Macros for player colours.
#define BLACK true
#define RED false
// Macros for determining what is past the river for each side:
#define BLACK_PAST_RIVER 4
// Black unit is past river if row > 4.
#define RED_PAST_RIVER 5
// Red unit is past river if row < 5.
#define BLACK_PALACE_FRONT 2
// Black Palace grounds are from R0C3 to R2C5 inclusive.
#define RED_PALACE_FRONT 7
// Red Palace grounds are from R7C3 to R9C5 inclusive.
#define NUMROWS 10
#define NUMCOLS 9

// Libraries used.
#include <iostream>
#include <string>
#include <cstddef>
#include <utility>
#include <cstdlib>
#include <set>

// Header files included in the correct order.
#include "unit.h"
#include "board.h"
#include "soldier.h"
#include "cannon.h"
#include "chariot.h"
#include "horseman.h"
#include "elephant.h"
#include "mandarin.h"
#include "general.h"

#endif
