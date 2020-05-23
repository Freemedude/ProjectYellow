#pragma once

#include <chrono>
#include <string>
#include "Integers.h"

namespace Yellow
{
using Time = std::chrono::steady_clock;

using Seconds = std::chrono::seconds;
using Millis = std::chrono::milliseconds;
using Micros = std::chrono::microseconds;

using TimePoint = Time::time_point;
using Duration =  std::chrono::duration<double>;

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

class Timer
{
public:
    const std::string &label;
    TimePoint start;
    TimePoint end;

    bool running;

    Timer(const std::string &label, bool startRunning = true);

    ~Timer();

    void Report();

    Duration GetDuration() const;

    u64 GetTicksInUnit(TimeUnit unit) const;

    void Stop();

    void Start();

    void Resume();
};
} // namespace Yellow
