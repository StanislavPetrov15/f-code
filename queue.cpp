template<typename T> struct queue
{
private:

    int Count = 0;
    int Size = 0;
    int ExtensionValue = 4.0; //(in percent of the current size)
    T* Elements = nullptr;

public:

    ///CONSTRUCTORS

    queue() = default;

    queue(int _size)
    {
        resize(_size);
    }

    queue(const queue<T>& _value)
    {
        if (this == &_value) return;

        Size = _value.Size;
        Count = _value.Count;

        if (Elements != nullptr)
        {
            delete [] Elements;
        }

        Elements = new T[Size];

        for (int i = 0; i < Count; i++)
        {
            Elements[i] = _value.Elements[i];
        }
    }

    ///DESTRUCTOR 

    ~queue()
    {
        delete [] Elements;
    }

    ///OPERATORS

    bool operator==(const queue<T>& _value) const
    {
        if (Count != _value.Count)
        {
            return false;
        }

        for (int i = 0; i < Count; i++)
        {
            if (Elements[i] != _value[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const queue<T>& _value) const
    {
        if (Count != _value.Count)
        {
            return true;
        }

        for (int i = 0; i < Count; i++)
        {
            if (Elements[i] != _value[i])
            {
                return true;
            }
        }

        return false;
    }

    queue<T>& operator=(const queue<T>& _value)
    {
        if (this == &_value) return *this;

        Count = 0;
        Size = _value.Size;
        delete [] Elements;
        Elements = new T[Size];

        for (int i = 0; i < Count; i++)
        {
            _value.push(_value.Elements[i]);
        }

        return *this;
    }

    queue<T>& operator+=(const T& _value)
    {
        return push(_value);
    }

    queue<T>& operator+=(const queue<T>& _value)
    {
        return push(_value);
    }

    ///FIELDS

    int count() const
    {
        return Count;
    }

    int size() const
    {
        return Size;
    }

    T* elements()
    {
        return Elements;
    }

    T* elements() const
    {
        return Elements;
    }

    ///FUNCTIONS

    queue<T>& enqueue(const T& _value)
    {
        if (Count + 1 > Size)
        {
            int value = (Size / 100.0) * ExtensionValue;
            resize(Size + (value > 0 ? value : 1));
        }

        Count++;

        Elements[0] = _value;

        //move all elements 1 position to the right
        for (int i = Count - 1; i > 0; i--)
        {
            Elements[i] = Elements[i - 1];
        }

        return *this;
    }

    //&Count >= 0 ->
    T dequeue()
    {
        if (Count > 0)
        {
            //shrink &Elements if needed
            if (numeric::ToPercent(Count, Size) < 50)
            {
                resize(Count);
            }

            return Elements[Count-- - 1];
        }
    }

    //&Count >= 0 ->
    T peekRear()
    {
        if (Count > 0)
        {
            return Elements[0];
        }
    }

    //&Count >= 0 ->
    T peekFront()
    {
        if (Count > 0)
        {
            return Elements[Count - 1];
        }
    }

    void resize(int _size)
    {
        T* oldElements = Elements;

        Elements = new T[_size];

        //if the list is being extended
        if (_size > Size)
        {
            for (int i = 0; i < Count; i ++)
            {
                Elements[i] = oldElements[i];
            }
        }
        //if the list is being shrinked
        else if (_size < Size)
        {
            for (int i = 0; i < _size; i ++)
            {
                Elements[i] = oldElements[i];
            }

            Count = _size;
        }

        Size = _size;

        delete[] oldElements;
    }
};
