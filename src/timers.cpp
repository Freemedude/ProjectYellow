void print_timer_duration(const std::string &label, Duration duration)
{
    Millis time = std::chrono::duration_cast<Millis>(duration);
    printf("%s: %lldms\n", label.c_str(), time.count());
}


ScopedTimer::ScopedTimer(const std::string &label)
        : label(label), start(Time::now())
{
}

ScopedTimer::~ScopedTimer()
{
    TimePoint now = Time::now();

    Duration duration = now - start;

    print_timer_duration(label, duration);
}


Timer CreateTimer(const char* label)
{
    Timer result {};

    result.label = label;
    result.start = Time::now();
    return result;
}

void TimerPrint(Timer *timer)
{
    print_timer_duration(timer->label, TimerGetDuration(timer));
}

Duration TimerGetDuration(Timer *timer)
{
    Duration result {};

    if (timer->running)
    {
        result = Time::now() - timer->start;
    } else
    {
        result = timer->end - timer->start;
    }
    return result;
}


void TimerStart(Timer *timer)
{
    timer->running = true;
}
void TimerEnd(Timer *timer)
{
    timer->end = Time::now();
    timer->running = false;
}

void TimerResume(Timer *timer)
{
    timer->running = true;
}


u64 TimerGetTicks(Timer *timer, TimeUnit unit)
{
    u64 result = 0;

    Duration duration = TimerGetDuration(timer);

    switch (unit)
    {

        case TimeUnit::Seconds:
        {
            auto time = std::chrono::duration_cast<Seconds>(duration);
            result = time.count();
        }
        case TimeUnit::MilliSeconds:
        {

            auto time = std::chrono::duration_cast<Millis>(duration);
            result = time.count();
        }
        case TimeUnit::MicroSeconds:
        {
            auto time = std::chrono::duration_cast<Micros>(duration);
            result = time.count();
        }
    }
    std::cout << "Unknown TimeUnit:" << (int)unit <<std::endl;
    return result;
}
