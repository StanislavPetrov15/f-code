template<typename K, typename V> struct pair
    {
        private:

        K Key;
        V Value;

        public:

        pair() = default;

        pair(const K &_key, const V &_value) : Key(_key), Value(_value) {};

        pair(const pair<K, V> &) = default;

        pair &operator=(const pair<K, V> &) = default;

        bool operator==(const pair<K, V> &_pair) const
        {
            return Key == _pair.Key && Value == _pair.Value;
        };

        bool operator!=(const pair<K, V> &_pair) const
        {
            return Key != _pair.Key || Value != _pair.Value;
        };

        const K &key() const
        {
            return Key;
        }

        const V &value() const
        {
            return Value;
        }
    };
