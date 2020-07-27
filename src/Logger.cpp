//
// @author freemedude
// @date 2020-07-26
// @brief 
//

#include "Logger.h"

Logger* Logger::m_instance = nullptr;

void Logger::Info(LogType type, const std::string &message)
{
    Log l;
    l.info = message;
    l.type = type;
    l.priority = Priority::Info;
    m_instance->m_logs.push_back(l);
}
