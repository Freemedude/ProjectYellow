/**
 * @file: timers.h
 * @author: Daniel Gaard Hansen
 * @date: 2020/06/14
 * 
 * @brief Contains functions for timing
 */
#ifndef TIMERS_H_202006141049
#define TIMERS_H_202006141049

#include <chrono>
#include <string>

#include "integers.h"

using Time = std::chrono::steady_clock;

using Seconds = std::chrono::seconds;
using Millis = std::chrono::milliseconds;
using Micros = std::chrono::microseconds;

using TimePoint = Time::time_point;
using Duration =  std::chrono::duration<double>;

template<typename TUnit>
constexpr auto DurationCast = std::chrono::duration_cast<TUnit>;

enum class TimeUnit
{
    Seconds,
    MilliSeconds,
    MicroSeconds
};

void print_timer_duration(
        const std::string &label,
        Duration duration);

class ScopedTimer
{
public:
    ScopedTimer(const std::string &label);

    ~ScopedTimer();

    const std::string &label;
    TimePoint start;
};

struct Timer
{
    const char *label;
    TimePoint start;
    TimePoint end;
    bool running;

};

Timer CreateTimer(const char* label);

void TimerPrint(Timer *timer);
Duration TimerGetDuration(Timer *timer);

u64 TimerGetTicks(Timer* timer, TimeUnit unit);
void TimerStart(Timer *timer);
void TimerEnd(Timer *timer);
void TimerResult(Timer *timer);

#endif // TIMERS_H_202006141049