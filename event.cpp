template<typename... args> struct event
{
private:

    list<void(*)(args...)> Subscribers;

public:

    event() = default;

    event& operator=(const event&) = default;

    //adds a subscriber to the list of subscribers
    void operator+= (void(*_subscriber)(args...))
    {
        Subscribers.Append(_subscriber);
    }

    //notifies each subscriber when the event occurs
    void operator()(args... _parameters) const
    {
        for (void(*__subscriber)(args...) : Subscribers)
        {
            __subscriber(_parameters...);
        }
    }

    const list<void(*)(args...)>& subscribers() const
    {
        return Subscribers;
    }
};
