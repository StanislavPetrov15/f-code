//Chronometer c -> [computations -> c.Elapsed() | c.Reset()]
//c.Running -> Elapsed() => > -1
//!c.Running -> Elapsed() => -1
struct Chronometer
{
private:

    bool Running = false;
    long long InitialTime;

public:

    Chronometer() = default;

    Chronometer(const Chronometer&) = delete;

    Chronometer& operator=(const Chronometer&) = delete;

    bool IsRunning() const
    {
        return Running;
    }

    void Start()
    {
        Running = true;
        using namespace std::chrono;
        InitialTime = duration_cast<microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }

    //in microseconds
    int Elapsed() const
    {
        if (Running)
        {
            using namespace std::chrono;
            clock_t currentClock = duration_cast<microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
            return currentClock - InitialTime;
        }

        return -1;
    }

    void Reset()
    {
        Running = false;
        InitialTime = 0;
    }
};
