//the timer has relatively high precision - the error is less than 1 second per 1 hour period
struct Timer
{
private:

    bool Running = false;
    int Interval; //in microseconds

public:

    bool Repeat = false;
    event<Timer*> OnTick;

    Timer() = default;

    //the interval is set in microseconds
    //_repeat specifies whether the period is repeated after the previous one ends
    Timer(int _interval, bool _repeat = true)
    {
        Interval = _interval;
        Repeat = _repeat;
    }

    Timer(const Timer&) = delete;

    Timer& operator=(const Timer&) = delete;

    bool IsRunning()
    {
        return Running;
    }

    int interval()
    {
        return Interval;
    }

    void Start()
    {
        Running = true;

        std::thread timerThread = std::thread([this]()
              {
                  using namespace std::chrono;

                  long long initialTime = duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();

                  while (true)
                  {
                      long long currentTime = duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();

                      //if the period is reached
                      if (currentTime - initialTime > Interval)
                      {
                          Running = Repeat; //->
                          OnTick(this); //->
                          if (Repeat) initialTime = duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();
                      }

                      if (!Running)
                      {
                          return;
                      }
                  }
              });

        timerThread.detach();
    }

    void Stop()
    {
        Running = false;
    }
};
