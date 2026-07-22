#include "logs.h"

const std::string c_log_level[] = {
    "[  DEBUG   ] ",
    "[   INFO   ] ",
    "[ WARNING  ] ",
    "[  ERROR   ] "
};

// Public Functions //

LOG_T log_init(LOG_LEVEL level, const std::string& file_name) {
    LOG_T logger;
    logger.file.open(file_name, std::ios::app);
    if (!logger.file.is_open()) {
        std::cerr<<"The logger file "<<file_name<<" could not be open\n";
        exit(EXIT_FAILURE);
    }
    logger.level=level;
    return logger;
}

LOG_LEVEL level_from_string(const std::string& str_level) {
    if (str_level == "LEVEL_DEBUG")      return LEVEL_DEBUG;
    if (str_level == "LEVEL_INFO")       return LEVEL_INFO;
    if (str_level == "LEVEL_WARNING")    return LEVEL_WARNING;
    if (str_level == "LEVEL_ERROR")      return LEVEL_ERROR;
    if (str_level == "LEVEL_OFF")        return LEVEL_OFF;

    std::cerr<<"The log level is not written correctly ("<<str_level<<")\n";
    exit(EXIT_FAILURE);
}

void doLog(LOG_T& logger, LOG_LEVEL log_level, const std::string& information_to_log) {
    if (logger.level > log_level) 
        return;

    std::time_t t = std::time(nullptr);
    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d %m %Y - %H:%M:%S ");
    std::string new_log = oss.str() + c_log_level[log_level] + information_to_log + '\n';

    logger.file<<new_log<<std::flush;
}