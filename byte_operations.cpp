namespace byte_operations
{
	enum Endianity { LE, BE };

	//_index = 0..1 ->
	unsigned char ByteOf(unsigned short _value, int _index)
	{
		if (_index == 0)
		{
			_value = _value << 8;
			_value = _value >> 8;
		}
		else
		{
			_value = _value >> 8;
		}

		return static_cast<unsigned char>(_value);
	}

	//_index = 0..3 ->
	unsigned char ByteOf(unsigned int _value, int _index)
	{
		if (_index == 0)
		{
			_value = _value << 24;
			_value = _value >> 24;
		}
		else if (_index == 1)
		{
			_value = _value << 16;
			_value = _value >> 24;
		}
		else if (_index == 2)
		{
			_value = _value << 8;
			_value = _value >> 24;
		}
		else
		{
			_value = _value >> 24;
		}

		return _value;
	}

	//_index = 0..7 ->
	unsigned char ByteOf(unsigned long long _value, int _index)
	{
		if (_index == 0)
		{
			_value = _value << 56;
			_value = _value >> 56;
		}
		else if (_index == 1)
		{
			_value = _value << 48;
			_value = _value >> 56;
		}
		else if (_index == 2)
		{
			_value = _value << 40;
			_value = _value >> 56;
		}
		else if (_index == 3)
		{
			_value = _value << 32;
			_value = _value >> 56;
		}
		else if (_index == 4)
		{
			_value = _value << 24;
			_value = _value >> 56;
		}
		else if (_index == 5)
		{
			_value = _value << 16;
			_value = _value >> 56;
		}
		else if (_index == 6)
		{
			_value = _value << 8;
			_value = _value >> 56;
		}
		else
		{
			_value = _value >> 56;
		}

		return static_cast<unsigned char>(_value);
	}

	//(!) always returns 2 bytes (not just the significant bytes)
	//(!) the first byte in the list is LSB
	list<unsigned char> BytesOf(unsigned short _value)
	{
		return { ByteOf(_value, 0), ByteOf(_value, 1) };
	}

	//(!) always returns 4 bytes (not just the significant bytes)
	//(!) the first byte in the list is LSB
	list<unsigned char> BytesOf(unsigned int _value)
	{
		return { ByteOf(_value, 0), ByteOf(_value, 1), ByteOf(_value, 2), ByteOf(_value, 3) };
	}

    //(!) always returns 8 bytes (not just the significant bytes)
	//(!) the first byte in the list is LSB
	list<unsigned char> BytesOf(unsigned long long _value)
	{
		return { ByteOf(_value, 0), ByteOf(_value, 1), ByteOf(_value, 2), ByteOf(_value, 3), ByteOf(_value, 4),
		ByteOf(_value, 5), ByteOf(_value, 6), ByteOf(_value, 7) };
	}

    //if _endianity has value 'LE' then 'a' is the least significant byte, respectively if _endianity has value 'BE' then 'a' is the most significant byte
	unsigned short _16(unsigned char a, unsigned char b, Endianity _endianity)
	{
		if (_endianity == LE)
		{
			return a | (b << 8);
		}
		else
		{
			return b | (a << 8);
		}
	}

    /* if _endianity has value 'LE' then 'a' is the least significant byte and 'd' is the most significant byte,
       respectively if _endianity has value 'BE' then 'a' is the most significant byte and 'd' is the least significant byte */
	unsigned int _32(unsigned char a, unsigned char b, unsigned char c, unsigned char d, Endianity _endianity)
	{
		if (_endianity == LE)
		{
			return (d << 24) | (c << 16) | (b << 8) | a;
		}
		else
		{
			return (a << 24) | (b << 16) | (c << 8) | d;
		}
	}

    //=> unsigned int { _a[0], _a[1], _b[0], _b1 } where the first byte in the list is the least significant byte
	unsigned int _32(unsigned short _a, unsigned short _b)
	{
		unsigned char low1 = ByteOf(_a, 0);
		unsigned char high1 = ByteOf(_b, 1);
		unsigned char low2 = ByteOf(_a, 0);
		unsigned char high2 = ByteOf(_b, 1);
		return (high2 << 24) | (low2 << 16) | (high1 << 8) | low1;
	}

    /* if _endianity has value 'LE' then 'a' is the least significant byte and 'h' is the most significant byte,
          respectively if _endianity has value 'BE' then 'a' is the most significant byte and 'h' is the least significant byte */
	unsigned long long _64(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f,
		unsigned char g, unsigned char h, Endianity _endianity)
	{
		if (_endianity == LE)
		{
			return (static_cast<unsigned long long>(h) << 56) |
				(static_cast<unsigned long long>(g) << 48) |
				(static_cast<unsigned long long>(f) << 40) |
				(static_cast<unsigned long long>(e) << 32) |
				(static_cast<unsigned long long>(d) << 24) |
				(static_cast<unsigned long long>(c) << 16) |
				(static_cast<unsigned long long>(b) << 8) |
                static_cast<unsigned long long>(a);
		}
		else
		{
			return (static_cast<unsigned long long>(a) << 56) |
				(static_cast<unsigned long long>(b) << 48) |
				(static_cast<unsigned long long>(c) << 40) |
				(static_cast<unsigned long long>(d) << 32) |
				(static_cast<unsigned long long>(e) << 24) |
				(static_cast<unsigned long long>(f) << 16) |
				(static_cast<unsigned long long>(g) << 8) |
                static_cast<unsigned long long>(h);
		}
	}

    //=> unsigned long long { _a[0], _a[1], _b[0], _b[1], _c[0], _c[1], _d[0], _d[1] } where the first byte in the list is the least significant byte
    unsigned long long _64(unsigned short _a, unsigned short _b, unsigned short _c, unsigned short _d)
    {
        unsigned char a0 = ByteOf(_a, 0);
        unsigned char a1 = ByteOf(_a, 1);
        unsigned char b0 = ByteOf(_b, 0);
        unsigned char b1 = ByteOf(_b, 1);
        unsigned char c0 = ByteOf(_c, 0);
        unsigned char c1 = ByteOf(_c, 1);
        unsigned char d0 = ByteOf(_d, 0);
        unsigned char d1 = ByteOf(_d, 1);

        return (static_cast<unsigned long long>(d1) << 56) |
               (static_cast<unsigned long long>(d0) << 48) |
               (static_cast<unsigned long long>(c1) << 40) |
               (static_cast<unsigned long long>(c0) << 32) |
               (static_cast<unsigned long long>(b1) << 24) |
               (static_cast<unsigned long long>(b0) << 16) |
               (static_cast<unsigned long long>(a1) << 8) |
               static_cast<unsigned long long>(a0);
    }

    //=> unsigned long long { _a[0], _a[1], _a[2], _a[3], _b[0], _b[1], _b[2], _b[3] } where the first byte in the list is the least significant byte
	unsigned long long _64(unsigned int _a, unsigned int _b)
	{
		unsigned char low0 = ByteOf(_a, 0);
		unsigned char low1 = ByteOf(_a, 1);
		unsigned char low2 = ByteOf(_a, 2);
		unsigned char low3 = ByteOf(_a, 3);
		unsigned char high0 = ByteOf(_b, 0);
		unsigned char high1 = ByteOf(_b, 1);
		unsigned char high2 = ByteOf(_b, 2);
		unsigned char high3 = ByteOf(_b, 3);

		return (static_cast<unsigned long long>(high3) << 56) |
			(static_cast<unsigned long long>(high2) << 48) |
			(static_cast<unsigned long long>(high1) << 40) |
			(static_cast<unsigned long long>(high0) << 32) |
			(static_cast<unsigned long long>(low3) << 24) |
			(static_cast<unsigned long long>(low2) << 16) |
			(static_cast<unsigned long long>(low1) << 8) |
            static_cast<unsigned long long>(low0);
	}
}
