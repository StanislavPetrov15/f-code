/* (USAGE-EXAMPLE)
   void timer_Tick(Timer* _timer, void* _data) { ... }
   Timer timer(2500, true, nullptr);
   timer.OnTick += timer_Tick;
   timer.Restart(); //eventually
   timer.Stop(); //timer is stopped; Restart() should not be called after that point */
struct Timer
{
private:

    bool Running = false;
    int Interval; //in microseconds
    long long InitialTime = -1; //(INTERNAL-VARIABLE)
    void* Data; //optional data

public:

    bool Repeat = false;
    event<Timer*, void*> OnTick;

    Timer() = default;

    //the interval is set in microseconds
    //_repeat specifies whether the period is repeated after the previous one ends
    //_data is an optional data
    Timer(int _interval, bool _repeat, void* _data = nullptr)
    {
        Interval = _interval;
        Repeat = _repeat;
        Data = _data;
    }

    Timer(const Timer&) = delete;

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

                  InitialTime = duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();

                  while (true)
                  {
                      if (!Running)
                      {
                          break;
                      }

                      long long currentTime = duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();

                      //if the period is reached
                      if (currentTime - InitialTime > Interval)
                      {
                          Running = Repeat; //->

                          OnTick(this, Data); //->

                          if (Repeat)
                          {
                              InitialTime = duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();
                          }
                      }
                  }
              });

        timerThread.detach();
    }

    void Stop()
    {
        Running = false;
    }

    void Restart()
    {
        InitialTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }
};
