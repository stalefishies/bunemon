#ifndef FIELDS_HPPGUARD
#define FIELDS_HPPGUARD

#include "common.hpp"

enum { FIELD_MAX_ZONE = 26, FIELD_MAX_ROOM = 23, FIELD_MAX_SCREEN = 6 };

// Name of each field
extern const String field_name[FIELD_MAX_ZONE];

// Width and height of each field's map
extern const uint8_t field_width [FIELD_MAX_ZONE];
extern const uint8_t field_height[FIELD_MAX_ZONE];

// Number of rooms in each field (at most FIELD_MAX_ROOM)
extern const uint8_t field_rooms[FIELD_MAX_ZONE];

// Convert a zone / room / screen into map x, y coordinates
// Returns false if the screen is invalid
bool fieldCoord(int zone, int room, int screen, int *x, int *y);

// Used for locating rooms within a field's map
// Exceptions to array:
//  zone  6   room 5   screen 1  =>  map x is 8 (I5)
//  zone  8   room 5   screen 2  =>  map x is 0 (A5)
//  zone  8   room 5   screen 3  =>  map x is 1 (B5)
//  zone  9   room 9   screen 1  =>  map x is 0 (A3)
//  zone 18   room 9   screen 1  =>  map x is 0 (A3)
typedef union FieldPosition {
    struct { uint8_t x, y, w, h; };
    uint32_t exists;
} LMRoomPosition;
extern const FieldPosition field_pos[FIELD_MAX_ZONE][FIELD_MAX_ROOM];

// Get room name, returns { 0, NULL } if screen is invalid
const String fieldRoom(int zone, int room, int screen);

#endif /* FIELDS_HPPGUARD */
