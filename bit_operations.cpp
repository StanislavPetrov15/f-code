namespace bit_operations
{
	//(!) bit index '0' specifies the least significant bit

	//LSB :: Least Significant Bit, MSB :: Most Significant Bit
	enum BitOrder { LSB0, MSB0 };

	list<bool> BitsOf(unsigned long long);
	void SetBit(unsigned char&, int, bool);
	bool GetBit(unsigned char, int);
	struct BitSet
	{
	private:

		int BitCount = 0;
		unsigned char* Bytes = nullptr;

	public:

		BitSet() = default;

		BitSet(unsigned short _bitCount)
		{
			BitCount = _bitCount;

            int byteSize;

            if (BitCount % 8 == 0)
            {
                byteSize = BitCount / 8;
            }
            else
            {
                byteSize = (BitCount / 8) + 1;
            }

			Bytes = new unsigned char[byteSize];

			for (int i = 0; i < byteSize; i++)
			{
				Bytes[i] = 0;
			}
		} //-> the value of each bit is 0

		BitSet(unsigned long long _value)
		{
			list<bool> bits = BitsOf(_value).TrimEnd(false);

			BitCount = bits.count();

            int byteSize;

            if (BitCount % 8 == 0)
            {
                byteSize = BitCount / 8;
            }
            else
            {
                byteSize = (BitCount / 8) + 1;
            }

			Bytes = new unsigned char[byteSize];

			for (int i = 0; i < BitCount; i++)
			{
				SetBit(i, bits[i]);
			}
		}

		BitSet(const BitSet& _bitset)
		{
			if (this != &_bitset)
			{
				BitCount = _bitset.BitCount;

				delete[] Bytes;

				Bytes = new unsigned char[_bitset.byteCount()];

				*Bytes = *_bitset.Bytes;

				for (int i = 0; i < _bitset.byteCount(); i++)
				{
					Bytes[i] = _bitset.Bytes[i];
				}
			}
		}

		BitSet& operator=(const BitSet& _bitset)
		{
			if (this != &_bitset)
			{
				BitCount = _bitset.BitCount;

				delete[] Bytes;

				Bytes = new unsigned char[_bitset.byteCount()];

				for (int i = 0; i < _bitset.byteCount(); i++)
				{
					Bytes[i] = _bitset.Bytes[i];
				}
			}

			return *this;
		}

		~BitSet()
		{
			delete [] Bytes;
		}

		int bitCount() const
		{
			return BitCount;
		}

		int byteCount() const
		{
			return BitCount / 8;
		}

		unsigned char* byteSequence() const
		{
			return Bytes;
		}

		void SetBit(int _index, bool _value)
		{
			div_t result = std::div(_index, 8);

			bit_operations::SetBit(Bytes[result.quot], result.rem, _value);
		}

        bool GetBit(int _index) const
		{
			div_t result = std::div(_index, 8);

			return bit_operations::GetBit(Bytes[result.quot], result.rem);
		}

        list<bool> GetBits(int _begin, int _end)
        {
            list<bool> result;

            for (int i = _begin; i <= _end; i++)
            {
                result.Append(GetBit(i));
            }

            return result;
        }

        //(0000000000).SetBits((111001), 3) => 0111001000
		void SetBits(const list<bool>& _bits, int _begin)
		{
            for (int i = 0; i < _bits.count(); i++)
            {
                SetBit(_begin + i, _bits[_bits.count() - (i + 1)]);
            }
		}

        //(0000000000).SetBits((111001), 3) => 0100111000
        void SetBitsReversed(const list<bool>& _bits, int _begin)
        {
            for (int i = 0; i < _bits.count(); i++)
            {
                SetBit(_begin + i, _bits[i]);
            }
        }
	};

	//Reverse<unsigned char>(01001010) => 01010010
	//Reverse<unsigned short>(0000000001001010) => 0101001000000000
	//Reverse<unsigned int>(00000100111001011110000000101010) => 01010100000001111010011100100000
	//<T> = unsigned char | unsigned short | unsigned int ->
	template<typename T> T Reverse(T _sequence)
	{
		T sequence = 0;

		int sequenceLength = sizeof(T) * 8;
		for (int i = 0; i < sequenceLength; i++)
		{
			sequence |= (static_cast<unsigned int>(_sequence) << (31 - i)) >> 31;

			if (i < sequenceLength - 1)
			{
				sequence <<= 1;
			}
		}

		return sequence;
	}

	//_index >= 0 || _index <= 7 ->
	bool GetBit(unsigned char _number, int _index)
	{
		_number = _number << (7 - _index);
		_number = _number >> 7;

		return _number;
	}

	//_index >= 0 || _index <= 15 ->
	bool GetBit(unsigned short _number, int _index)
	{
		_number = _number << (15 - _index);
		_number = _number >> 15;

		return _number;
	}

	//_index >= 0 || _index <= 31 ->
	bool GetBit(unsigned int _number, int _index)
	{
		_number = _number << (31 - _index);
		_number = _number >> 31;

		return _number;
	}

	//_index >= 0 || _index <= 63 ->
	bool GetBit(unsigned long long _number, int _index)
	{
		_number = _number << (63 - _index);
		_number = _number >> 63;

		return _number;
	}

	//GetBits(53, 1, 3) => [0, 1, 0] = Dx2
	// _begin >= 0 || _end <= 7, _begin < _end ->
	unsigned char GetBits(unsigned char _number, int _begin, int _end)
	{
		_number = _number << (7 - _end);
		_number = _number >> ((7 - _end) + _begin);

		return _number;
	}

	// _begin >= 0 || _end <= 15, _begin < _end ->
	unsigned short GetBits(unsigned short _number, int _begin, int _end)
	{
		_number = _number << (15 - _end);
		_number = _number >> ((15 - _end) + _begin);

		return _number;
	}

	// _begin >= 0 || _end <= 31, _begin < _end ->
	unsigned int GetBits(unsigned int _number, int _begin, int _end)
	{
		_number = _number << (31 - _end);
		_number = _number >> ((31 - _end) + _begin);

		return _number;
	}

	//_index >= 0 || _index <= 7 ->
	void SetBit(unsigned char& _number, int _index, bool _value)
	{
		if (_value)
		{
			_number |= (1 << _index);
		}
		else
		{
			_number &= ~(1 << _index);
		}
	}

	//_index >= 0 || _index <= 15 ->
	void SetBit(unsigned short& _number, int _index, bool _value)
	{
		if (_value)
		{
			_number |= (1 << _index);
		}
		else
		{
			_number &= ~(1 << _index);
		}
	}

	//_index >= 0 || _index <= 31 ->
	void SetBit(unsigned int& _number, int _index, bool _value)
	{
		if (_value)
		{
			_number |= (1 << _index);
		}
		else
		{
			_number &= ~(1 << _index);
		}
	}

	//_index >= 0 || _index <= 63 ->
	void SetBit(unsigned long long& _number, int _index, bool _value)
	{
		if (_value)
		{
			_number |= (1ull << _index);
		}
		else
		{
			_number &= ~(1ull << _index);
		}
	}

    /* (A) shifting by more positions than the bit length of the integer type may create problems (it certainly does on 32-bit integer) as it's
           probably undefined behaviour (there's no definite answer on the internet) so this segment is needed to ensure that things are working
           properly */

    //SetBits(x = 236, 4, 7, 0b1011) -> x = 188
    //_begin >= 0 || _end <= 7, _begin < _end ->
    void SetBits(unsigned char& _number, int _begin, int _end, unsigned char _value)
    {
            //extracting the (0.._begin) segment
            unsigned char n = _number << (8 - _begin);
            unsigned char rightSegment = n >> (8 - _begin);

            //clearing the (_begin.._end) segment so the bitwise OR operator can be used to 'insert' the _value into _number

            //(A)
            if (_end < 7)
            {
                _number >>= _end + 1;
                _number <<= _end + 1;
            }
            else
            {
                _number = 0;
            }

            _number |= rightSegment; //

            _value <<= _begin;
            _number |= _value;
    }

    //SetBits(x = 236, 4, 7, 0b1011) -> x = 188
    //_begin >= 0 || _end <= 15, _begin < _end ->
    void SetBits(unsigned short& _number, int _begin, int _end, unsigned short _value)
    {
        //extracting the (0.._begin) segment
        unsigned short n = _number << (16 - _begin);
        unsigned short rightSegment = n >> (16 - _begin);

        //clearing the (_begin.._end) segment so the bitwise OR operator can be used to 'insert' the _value into _number

        //(A)
        if (_end < 15)
        {
            _number >>= _end + 1;
            _number <<= _end + 1;
        }
        else
        {
            _number = 0;
        }

        _number |= rightSegment; //

        _value <<= _begin;
        _number |= _value;
    }

    //SetBits(x = 236, 4, 7, 0b1011) -> x = 188
    //_begin >= 0 || _end <= 31, _begin < _end ->
    void SetBits(unsigned int& _number, int _begin, int _end, unsigned int _value)
    {
        //extracting the (0.._begin) segment
        unsigned int n = _number << (32 - _begin);
        unsigned int rightSegment = n >> (32 - _begin);

        //clearing the (_begin.._end) segment so the bitwise OR operator can be used to 'insert' the _value into _number

        //(A)
        if (_end < 31)
        {
            _number >>= _end + 1;
            _number <<= _end + 1;
        }
        else
        {
            _number = 0;
        }

        _number |= rightSegment; //

        _value <<= _begin;
        _number |= _value;
    }

    //SetBits(x = 236, 4, 7, 0b1011) -> x = 188
    //_begin >= 0 || _end <= 63, _begin < _end ->
    void SetBits(unsigned long long& _number, int _begin, int _end, unsigned long long _value)
    {
        //extracting the (0.._begin) segment
        unsigned long long n = _number << (64 - _begin);
        unsigned long long rightSegment = n >> (64 - _begin);

        //clearing the (_begin.._end) segment so the bitwise OR operator can be used to 'insert' the _value into _number

        //(A)
        if (_end < 63)
        {
            _number >>= _end + 1;
            _number <<= _end + 1;
        }
        else
        {
            _number = 0;
        }

        _number |= rightSegment; //

        _value <<= _begin;
        _number |= _value;
    }

    //SetBits(x = 0, 3, { 1, 1, 0, 0, 1 }) -> x = 11001000
    //_bits.count() + _begin < 9 ->
    void SetBits(unsigned char& _number, int _begin, const list<bool>& _bits)
    {
        for (int i = 0; i < _bits.count(); i++)
        {
            SetBit(_number, _begin + i, _bits[_bits.count() - (i + 1)]);
        }
    }

    //SetBits(x = 0, 3, { 1, 1, 0, 0, 1 }) -> x = 00..11001000
    //_bits.count() + _begin < 17 ->
    void SetBits(unsigned short& _number, int _begin, const list<bool>& _bits)
    {
        for (int i = 0; i < _bits.count(); i++)
        {
            SetBit(_number, _begin + i, _bits[_bits.count() - (i + 1)]);
        }
    }

    //SetBits(x = 0, 3, { 1, 1, 0, 0, 1 }) -> x = 00..11001000
    //_bits.count() + _begin < 33 ->
    void SetBits(unsigned int& _number, int _begin, const list<bool>& _bits)
    {
        for (int i = 0; i < _bits.count(); i++)
        {
            SetBit(_number, _begin + i, _bits[_bits.count() - (i + 1)]);
        }
    }

    //SetBits(x = 0, 3, { 1, 1, 0, 0, 1 }) -> x = 00..11001000
    //_bits.count() + _begin < 65 ->
    void SetBits(unsigned long long& _number, int _begin, const list<bool>& _bits)
    {
        for (int i = 0; i < _bits.count(); i++)
        {
            SetBit(_number, _begin + i, _bits[_bits.count() - (i + 1)]);
        }
    }

	//returns all bits of _value; the first bit in the list is LSB
	//BitsOf(194) => [01000011]
	list<bool> BitsOf(unsigned char _value)
	{
		list<bool> bits;

		for (int i = 0; i < 8; i++)
		{
			bits.Append(GetBit(static_cast<unsigned char>(_value), i));
		}

		return bits;
	}

	//return all bits of _value; the first bit in the list is LSB
	//BitsOf(41092) => [0010000100000101]
	list<bool> BitsOf(unsigned short _value)
	{
		list<bool> bits;

		for (int i = 0; i < 16; i++)
		{
			bits.Append(GetBit(_value, i));
		}

		return bits;
	}

	//return all bits of _value; the first bit in the list is LSB
    //BitsOf(41092) => [00100001000001010000000000000000]
	list<bool> BitsOf(unsigned int _value)
	{
		list<bool> bits;

		for (int i = 0; i < 32; i++)
		{
			bits.Append(GetBit(_value, i));
		}

		return bits;
	}

	//return all bits of _value; the first bit in the list is LSB
    //BitsOf(41092) => [0010000100000101000000000000000000000000000000000000000000000000]
	list<bool> BitsOf(unsigned long long _value)
	{
		list<bool> bits;

		for (int i = 0; i < 64; i++)
		{
			bits.Append(GetBit(_value, i));
		}

		return bits;
	}

    //returns all bits of _value; the first bit in the list is MSB
    //BitsOfR(194) => [11000010]
    list<bool> BitsOfR(unsigned char _value)
    {
        list<bool> bits;

        for (int i = 7; i > -1; i--)
        {
            bits.Append(GetBit(static_cast<unsigned char>(_value), i));
        }

        return bits;
    }

    //return all bits of _value; the first bit in the list is MSB
    //BitsOfR(41092) => [1010000010000100]
    list<bool> BitsOfR(unsigned short _value)
    {
        list<bool> bits;

        for (int i = 15; i > -1; i--)
        {
            bits.Append(GetBit(_value, i));
        }

        return bits;
    }

    //return all bits of _value; the first bit in the list is МSB
    //BitsOfR(41092) => [00000000000000001010000010000100]
    list<bool> BitsOfR(unsigned int _value)
    {
        list<bool> bits;

        for (int i = 31; i > -1; i--)
        {
            bits.Append(GetBit(_value, i));
        }

        return bits;
    }

    //return all bits of _value; the first bit in the list is MSB
    //BitsOfR(41092) => [0000000000000000000000000000000000000000000000001010000010000100]
    list<bool> BitsOfR(unsigned long long _value)
    {
        list<bool> bits;

        for (int i = 63; i > -1; i--)
        {
            bits.Append(GetBit(_value, i));
        }

        return bits;
    }

    //the first bit in the list is LSB
    list<bool> SignificantBitsOf(unsigned char _value)
    {
        return BitsOf(_value).TrimBegin(0);
    }

    //the first bit in the list is LSB
    list<bool> SignificantBitsOf(unsigned short _value)
    {
        return BitsOf(_value).TrimBegin(0);
    }

    //the first bit in the list is LSB
    list<bool> SignificantBitsOf(unsigned int _value)
    {
        return BitsOf(_value).TrimBegin(0);
    }

    //the first bit in the list is LSB
    list<bool> SignificantBitsOf(unsigned long long _value)
    {
        return BitsOf(_value).TrimBegin(0);
    }

    //the first bit in the list is MSB
    list<bool> SignificantBitsOfR(unsigned char _value)
    {
        return BitsOfR(_value).TrimBegin(0);
    }

    //the first bit in the list is MSB
    list<bool> SignificantBitsOfR(unsigned short _value)
    {
        return BitsOfR(_value).TrimBegin(0);
    }

    //the first bit in the list is MSB
    list<bool> SignificantBitsOfR(unsigned int _value)
    {
        return BitsOfR(_value).TrimBegin(0);
    }

    //the first bit in the list is MSB
    list<bool> SignificantBitsOfR(unsigned long long _value)
    {
        return BitsOfR(_value).TrimBegin(0);
    }

	//returns the number of bits needed for the binary representation of _number
	int BitLengthOf(unsigned int _number)
	{
		int length = 0;

		while (_number > 0)
		{
			_number /= 2;
			length++;
		}

		return length;
	}
}
