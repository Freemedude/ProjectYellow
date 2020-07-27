//
// @author freemedude
// @date 2020-07-26
// @brief 
//

#ifndef PROJECT_YELLOW_LOGGER_H
#define PROJECT_YELLOW_LOGGER_H

#include <string>
#include <vector>

enum class Priority
{
    Info,
    Count
};

enum class LogType
{
    Destructor,
    Misc,
    Count
};

struct Log
{
    Priority priority;
    LogType type;
    std::string info;
};

class Logger
{
private:
    static Logger *m_instance;
public:
    std::vector<Log> m_logs;

    static void Info(LogType type, const std::string &message);
};


#endif //PROJECT_YELLOW_LOGGER_H
