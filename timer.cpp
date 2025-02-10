/* (USAGE-EXAMPLE)
   void timer_Tick(Timer* _timer, void* _data) { ... }
   Timer timer(2500, 30, true, nullptr);
   timer.OnTick += timer_Tick;
   timer.Restart(); //eventually (not a mandatory function to call); should be called only if the timer is running; it won't have an effect if the timer is not running
   timer.Stop(); //timer is stopped; Restart() should not be called after that point */
//(NOTE) this timer is not very precise and it should not be used for periods lower than 10ms
struct Timer
{
private:

    bool Running = false;
    int Interval; //in milliseconds
    long long InitialTime = -1; //(INTERNAL-VARIABLE)
    int Period = -1; //in milliseconds
    void* Data; //optional data

public:

    bool Repeat = false;
    event<Timer*, void*> OnTick;

    Timer() = default;

    //_interval speicifes the time between two occurences of the OnTick event; it is set in milliseconds
    /*_period specifies the period used by the timer to check if the OnTick event needs to be fired;
      (EXAMPLE) if the timer interval (_interval) is 15 second and _internalPeriod is 100ms then the timer will check (if
       the OnTick event must be generated) every 100ms; this value shouldn't be (lower than 2ms) and (higher than 200ms)
       higher _internalPeriod will give more CPU time to other active threads, but also will lower the precision for firing the OnTick event;
       this value also must be atleast 10 times lower than _interval - i.e. if interval is 1.5 seconds, then this value must be lower than 150ms;
       if _interval is lower than 10ms (the minimum possible value), then value of 1 must be used for _internalPeriod*/
    //_repeat specifies if the period is repeated after the previous one ends
    //_data is an optional data; if there is no data supplied then this parameter must be null
    //(!) this constructor does not validate the parameters
    Timer(int _interval, int _period, bool _repeat, void* _data)
    {
        Interval = _interval * 1000;
        Period = _period;
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
                      if (currentTime - InitialTime >= Interval)
                      {
                          if (Repeat)
                          {
                              InitialTime = currentTime;
                          }

                          OnTick(this, Data); //->
                      }

                      if (Period != -1)
                      {
                          Sleep(Period);
                      }
                  }
              });

        timerThread.detach(); //this allows the thread to continue after this function finishes
    }

    void Stop()
    {
        Running = false;
    }

    //the timer is running ->
    void Restart()
    {
       InitialTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }
};
