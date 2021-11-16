namespace byte_operations
{
	//(!) byte index '0' specifies the least significant byte

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

	//(!) the first byte in the list is LSB
	list<unsigned char> BytesOf(unsigned short _value)
	{
		return { ByteOf(_value, 0), ByteOf(_value, 1) };
	}

	//(!) the first byte in the list is LSB
	list<unsigned char> BytesOf(unsigned int _value)
	{
		return { ByteOf(_value, 0), ByteOf(_value, 1), ByteOf(_value, 2), ByteOf(_value, 3) };
	}

	//(!) the first byte in the list is LSB
	list<unsigned char> BytesOf(unsigned long long _value)
	{
		return { ByteOf(_value, 0), ByteOf(_value, 1), ByteOf(_value, 2), ByteOf(_value, 3), ByteOf(_value, 4),
		ByteOf(_value, 5), ByteOf(_value, 6), ByteOf(_value, 7) };
	}

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

	//_low (low1, high1) + _high (low2, high2) => unsigned int { high2, low2, high1, low1 }, where 'high1' is the high byte of the result
	unsigned int _32(unsigned short _low, unsigned short _high)
	{
		unsigned char low1 = ByteOf(_low, 0);
		unsigned char high1 = ByteOf(_low, 1);
		unsigned char low2 = ByteOf(_high, 0);
		unsigned char high2 = ByteOf(_high, 1);
		return (high2 << 24) | (low2 << 16) | (high1 << 8) | low1;
	}

	unsigned long long _64(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f,
		unsigned char g, unsigned char h, Endianity _endianity)
	{
		if (_endianity == LE)
		{
			return (static_cast<unsigned long long>(h) << 56) |
				(static_cast<unsigned long long>(g) << 48) |
				(static_cast<unsigned long long>(f) << 40) |
				(static_cast<unsigned long long>(e) << 32) |
				(d << 24) |
				(c << 16) |
				(b << 8) |
				a;
		}
		else
		{
			return (static_cast<unsigned long long>(a) << 56) |
				(static_cast<unsigned long long>(b) << 48) |
				(static_cast<unsigned long long>(c) << 40) |
				(static_cast<unsigned long long>(d) << 32) |
				(e << 24) |
				(f << 16) |
				(g << 8) |
				h;
		}
	}

	//_low (low1...high2) + _high (low2...high2) => unsigned long long { high2...low2, high1...low1 }, where 'high2' is the high byte of the result
	unsigned long long _64(unsigned int _low, unsigned int _high)
	{
		unsigned char low0 = ByteOf(_low, 0);
		unsigned char low1 = ByteOf(_low, 1);
		unsigned char low2 = ByteOf(_low, 2);
		unsigned char low3 = ByteOf(_low, 3);
		unsigned char high0 = ByteOf(_high, 0);
		unsigned char high1 = ByteOf(_high, 1);
		unsigned char high2 = ByteOf(_high, 2);
		unsigned char high3 = ByteOf(_high, 3);

		return (static_cast<unsigned long long>(high3) << 56) |
			(static_cast<unsigned long long>(high2) << 48) |
			(static_cast<unsigned long long>(high1) << 40) |
			(static_cast<unsigned long long>(high0) << 32) |
			(low3 << 24) |
			(low2 << 16) |
			(low1 << 8) |
			low0;
	}
}
