#ifndef UTILS_LOGS_H
#define UTILS_LOGS_H

#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>

typedef enum LOG_LEVEL {
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_OFF
} LOG_LEVEL;

typedef struct LOG_T {
    std::ofstream file;
    LOG_LEVEL level;
} LOG_T;

LOG_T log_init(LOG_LEVEL level, const std::string& file_name);

LOG_LEVEL level_from_string(const std::string& str_level);

void doLog(LOG_T& logger, LOG_LEVEL log_level, const std::string& information_to_log);

#define LOG_DEBUG(logger, information_to_log) doLog(logger, LEVEL_DEBUG, information_to_log)
#define LOG_INFO(logger, information_to_log) doLog(logger, LEVEL_INFO, information_to_log)
#define LOG_WARNING(logger, information_to_log) doLog(logger, LEVEL_WARNING, information_to_log)
#define LOG_ERROR(logger, information_to_log) doLog(logger, LEVEL_ERROR, information_to_log)

#endif //UTILS_LOGS_H