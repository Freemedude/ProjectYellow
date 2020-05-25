namespace Yellow
{

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


Timer::Timer(const std::string &label, bool startRunning)
        : label(label), running(startRunning), start(Time::now())
{}

Timer::~Timer() = default;

void Timer::Report()
{
    print_timer_duration(label, GetDuration());
}

Duration Timer::GetDuration() const
{
    Duration duration;
    if (running)
    {
        duration = Time::now() - start;
    } else
    {
        duration = end - start;
    }
    return duration;
}

void Timer::Start()
{
    start = Time::now();
    running = true;
}

void Timer::Resume()
{
    running = true;
}

void Timer::Stop()
{
    end = Time::now();
    running = false;
}

u64 Timer::GetTicksInUnit(TimeUnit unit) const
{
    Duration duration = GetDuration();

    switch (unit)
    {

        case TimeUnit::Seconds:
        {
            auto time = std::chrono::duration_cast<Seconds>(duration);
            return time.count();
        }
        case TimeUnit::MilliSeconds:
        {

            auto time = std::chrono::duration_cast<Millis>(duration);
            return time.count();
        }
        case TimeUnit::MicroSeconds:
        {
            auto time = std::chrono::duration_cast<Micros>(duration);
            return time.count();
        }
    }
    std::cout << "Unknown TimeUnit:" << (int)unit <<std::endl;
    return 0;
}

} // namespace Yellow