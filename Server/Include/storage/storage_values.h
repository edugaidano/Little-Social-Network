#ifndef STORAGE_VALUES_H
#define STORAGE_VALUES_H

#include <cstdint>

// Directories

constexpr auto PROFILES_DIR = "Profiles";
constexpr auto MESSAGES_DIR = "Messages";

// Files

constexpr auto USERS_INDEX = "Users_Index";
constexpr auto NEXT_ID = "Next_ID.txt";
constexpr auto MESSAGES_INDEX = "Messages_Index";

// Defines

#define DATE_SIZE 15
#define SENDER_SIZE 31
#define SUBJECT_SIZE 61

// Typedefs

typedef uint32_t ID_T;

typedef struct MESSAGE_ITEM {
    ID_T id;
    uint8_t seen;
    char date[DATE_SIZE];
    char sender[SENDER_SIZE];
    char subject[SUBJECT_SIZE];
} MESSAGE_ITEM;

#endif