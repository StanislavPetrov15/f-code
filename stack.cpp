template<typename T> struct stack
{
    private:

    int Count = 0;
    int Size = 0;
    int ExtensionValue = 4.0; //(in percent of the current size)
    T* Elements = nullptr;

    public:

    ///CONSTRUCTORS 

    stack() = default;

    stack(int _size)
    {
        resize(_size);
    }

    stack(const stack<T>& _value)
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

    ~stack()
    {
        delete [] Elements;
    }

    ///OPERATORS

    bool operator==(const stack<T>& _value) const
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

    bool operator!=(const stack<T>& _value) const
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

    stack<T>& operator=(const stack<T>& _value)
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

    stack<T>& operator+=(const T& _value)
    {
        return push(_value);
    }

    stack<T>& operator+=(const stack<T>& _value)
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

    stack<T>& push(const T& _value)
    {
        if (Count + 1 > Size)
        {
            int value = (Size / 100.0) * ExtensionValue;
            resize(Size + (value > 0 ? value : 1));
        }

        Elements[Count++] = _value;

        return *this;
    }

    //&Count >= 0 ->
    T pop()
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
    T peek()
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
