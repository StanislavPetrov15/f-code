namespace numeric
{
    enum class TraversalDirection { LEFT, RIGHT };

    enum class MagnitudeDirection { SMALLER, LARGER };

    const char HEX_DIGITS[16] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    ///FUNCTIONS

    template<typename T> T Absolute(T _number)
    {
        if (_number >= 0)
        {
            return _number;
        }
        else
        {
            return _number - _number - _number;
        }
    }

    //(8) => -8
    //(-6) => 6
    template<typename T> T Inverse(T _number)
    {
        if (_number < 0.0)
        {
            return Abs(_number);
        }
        else
        {
            return -_number;
        }
    }

    int RoundDown(double);
    long long RoundDown_L(double);

    //(6.02645) => 0.02645
    //(-18.823569) => 0.823569
    //(0) => 0.0
    double FractionOf(double N)
    {
        return Absolute(N - RoundDown_L(N));
    }

    int Mod(int, int);

    bool IsEven(int N)
    {
        return Mod(Absolute(N), 2) == 0;
    }

    bool IsOdd(int N)
    {
        return Mod(Absolute(N), 2) != 0;
    }

    //(52, 5) => 2
    //(7, 20) => 7
    //(20, 7) => 6
    //(0, 3) => 0
    //N1 > 0, N2 > 0 ->
    int Mod(int N1, int N2)
    {
        if (N1 < 0 || N2 < 0)
        {
            return 0;
        }
        else if (N1 == N2)
        {
            return 0;
        }
        else if (N1 < N2)
        {
            return N1;
        }
        else
        {
            return N1 - ((N1 / N2) * N2);
        }
    }

    //(52.6, 5.0) => 2.6
    //(5.0, 52.6) => 5.0
    //(218.0749, 39.4) => 21.0749
    //(0.0, 3.0) => 0.0
    //N1 > 0.0, N2 > 0.0 ->
    double Mod(double N1, double N2)
    {
        if (N1 < 0 || N2 < 0)
        {
            return -1;
        }
        else if (N1 == N2)
        {
            return 0;
        }
        else if (N1 < N2)
        {
            return N1;
        }
        else
        {
            return FractionOf(N1 / N2) * N2;
        }
    }

    //_exponent < 0 => 0
    //_exponent == 0 => 1
    //_exponent > 0 ->
    long long Pow(int _base, int _exponent)
    {
        if(_exponent < 0) return 0;
        else if (_exponent == 0) return 1;

        long long result = _base;

        for (int i = 0; i < _exponent - 1; i++)
        {
            result *= _base;
        }

        return result;
    }

    //_exponent < 0.0 => 0.0
    //_exponent == 0.0 => 1.0
    //_exponent > 0.0 ->
    double Pow(double _base, double _exponent)
    {
        if(_exponent < 0) return 0.0;
        else if (_exponent == 0) return 1.0;

        double result = _base;

        for (int i = 0; i < _exponent - 1.0; i++)
        {
            result *= _base;
        }

        return result;
    }

    //N1 == N2 => N2
    int LargerOf(int N1, int N2)
    {
        return N1 > N2 ? N1 : N2;
    }

    //N1 == N2 => N2
    long long LargerOf_L(long long N1, long long N2)
    {
        return N1 > N2 ? N1 : N2;
    }

    //N1 == N2 => N2
    double LargerOf(double N1, double N2)
    {
        return N1 > N2 ? N1 : N2;
    }

    //N1 == N2 => N2
    int SmallerOf(int N1, int N2)
    {
        return N1 < N2 ? N1 : N2;
    }

    //N1 == N2 => N2
    long long SmallerOf_L(long long N1, long long N2)
    {
        return N1 < N2 ? N1 : N2;
    }

    //N1 == N2 => N2
    double SmallerOf(double N1, double N2)
    {
        return N1 < N2 ? N1 : N2;
    }

    //(89.4, 9106.7) => 4598.05
    double AverageOf(double N1, double N2)
    {
        double larger = LargerOf(N1, N2);
        double smaller = SmallerOf(N1, N2);
        return smaller + ((larger - smaller) / 2.0);
    }

    //(54, 182) => 98
    //(182, 28) => 50
    //_percent >= 0.0, _value >= 0.0 ->
    double FromPercent(double _percent, double _value)
    {
        return (_value / 100.0) * _percent;
    }

    //(15, 782) => 1.9181585677749362
    //(782, 15) => 5213.3333333333330
    //N1 >= 0.0, N2 >= 0.0 ->
    double ToPercent(double N1, double N2)
    {
        return (N1 / N2) * 100.0;
    }

    //(385.91) => 385.0
    //(-2.36) => -3.0
    int RoundDown(float _value)
    {
        if (_value >= 0.0)
        {
            return _value;
        }
        else
        {
            return _value - 1.0;
        }
    }

    //(385.91) => 385.0
    //(-2.36) => -3.0
    int RoundDown(double _value)
    {
        if (_value >= 0.0)
        {
            return _value;
        }
        else
        {
            return _value - 1.0;
        }
    }

    //(385.91) => 385.0
    //(-2.36) => -3.0
    long long RoundDown_L(float _value)
    {
        if (_value >= 0.0)
        {
            return _value;
        }
        else
        {
            return _value - 1.0;
        }
    }

    //(385.91) => 385.0
    //(-2.36) => -3.0
    long long RoundDown_L(double _value)
    {
        if (_value >= 0.0)
        {
            return _value;
        }
        else
        {
            return _value - 1.0;
        }
    }

    //(385.91) => 386.0
    //(-2.36) => 2.0
    int RoundUp(float _value)
    {
        if (_value >= 0.0)
        {
            return _value + 1;
        }
        else
        {
            return _value;
        }
    }

    //(385.91) => 386.0
    //(-2.36) => 2.0
    int RoundUp(double _value)
    {
        if (_value >= 0.0)
        {
            return _value + 1;
        }
        else
        {
            return _value;
        }
    }

    //(385.91) => 386.0
    //(-2.36) => 2.0
    long long RoundUp_L(float _value)
    {
        if (_value >= 0.0)
        {
            return _value + 1;
        }
        else
        {
            return _value;
        }
    }

    //(385.91) => 386.0
    //(-2.36) => 2.0
    long long RoundUp_L(double _value)
    {
        if (_value >= 0.0)
        {
            return _value + 1;
        }
        else
        {
            return _value;
        }
    }

    //(385.45 => 385.0
    //(385.91) => 386.0
    //(385.50) => 385.0
    //(-2.36) => -2.0
    //(-2.79) -> -3.0
    //(-2.50) -> -3.0
    float RoundToNearest(float _value)
    {
        float roundedDown = RoundDown(_value);
        float roundedUp = RoundUp(_value);
        float f1 = _value - roundedDown;
        float f2 = roundedUp - _value;

        if (f1 < f2 || f1 == f2)
        {
            return roundedDown;
        }
        else
        {
            return roundedUp;
        }
    }

    //(385.45 => 385.0
    //(385.91) => 386.0
    //(385.50) => 385.0
    //(-2.36) => -2.0
    //(-2.79) -> -3.0
    //(-2.50) -> -3.0
    double RoundToNearest(double _value)
    {
        float roundedDown = RoundDown_L(_value);
        float roundedUp = RoundUp_L(_value);
        float f1 = _value - roundedDown;
        float f2 = roundedUp - _value;

        if (f1 < f2 || f1 == f2)
        {
            return roundedDown;
        }
        else
        {
            return roundedUp;
        }
}

    //(3, 5) => 2
    //(5, 3) => 2
    //(511, 96) => 415
    //(96, 511) => 415
    //(-4, 5) => 9
    //(5, -4) => 9
    //N == N => 0
    int DistanceOf(int N1, int N2)
    {
        return (LargerOf(N1, N2) - SmallerOf(N1, N2));
    }

    //"stl" :: smaller to larger
    //(252, 103, 35) => 155
    //(103, 252, 35) => 155
    //(-103, 252, 35) => 21
    //(252, -103, 35) => 21
    //(-117, -106, 35) => -113
    int LinearInterpolationSTL(int _a, int _b, int _percentage)
    {
        if (_a <= _b)
        {
            int difference = _b - _a;
            return _a + FromPercent(_percentage, difference);
        }
        else
        {
            int difference = _a - _b;
            return _b + FromPercent(_percentage, difference);
        }
    }

    //"stl" :: smaller to larger
    //(252, 103, 35) => 155.15
    //(103, 252, 35) => 155.15
    //(-103, 252, 35) => 21.25
    //(252, -103, 35) => 21.25
    //(-117, -106, 35) => -113.15
    double LinearInterpolationSTL(double _a, double _b, double _percentage)
    {
        if (_a <= _b)
        {
            double difference = _b - _a;
            return _a + FromPercent(_percentage, difference);
        }
        else
        {
            double difference = _a - _b;
            return _b + FromPercent(_percentage, difference);
        }
    }

    //"fts" :: first to second
    //(252, 103, 35) => 199
    //(103, 252, 35) => 155
    //(-103, 252, 35) => 21
    //(252, -103, 35) => 127
    //(-117, -106, 35) => -113
    int LinearInterpolationFTS(int _a, int _b, int _percentage)
    {
        int difference = _b - _a;
        return _a + FromPercent(_percentage, difference);
    }

    //"fts" :: first to second
    //(252, 103, 35) => 199.85
    //(103, 252, 35) => 155.15
    //(-103, 252, 35) => 21.25
    //(252, -103, 35) => 127.75
    //(-117, -106, 35) => -113.15
    double LinearInterpolationFTS(double _a, double _b, double _percentage)
    {
        double difference = _b - _a;
        return _a + FromPercent(_percentage, difference);
    }

    //(3, 5) => 2
    //(5, 3) => 2
    //(511, 96) => 415
    //(96, 511) => 415
    //(-4, 5) => 9
    //(5, -4) => 9
    //N == N => 0
    long long DistanceOf_L(long long N1, long long N2)
    {
        return (LargerOf_L(N1, N2) - SmallerOf_L(N1, N2));
    }

    //(3.2, 5.1) => 1.9
    //(5.1, 3.2) => 1.9
    //(511.0, 96.0) => 415
    //(96.0, 511.0) => 415
    //(-4.0, 5.2) => 9.2
    //(5.2, -4.0) => 9.2
    //N == N => 0.0
    double DistanceOf(double N1, double N2)
    {
        return (LargerOf(N1, N2) - SmallerOf(N1, N2));
    }

    //_rangeBegin >= _rangeEnd => -1
    //_currentValue < _rangeBegin || _value > _rangeEnd => -2
    //_addition < 1 => -3
    //(20, 35, 28, 9) => 21
    //(20, 35, 28, 61) => 25
    //(-8, 5, -3, 19) => 2
    int CircularAddition(int _rangeBegin, int _rangeEnd, int _currentValue, int _addition)
    {
        if (_rangeBegin >= _rangeEnd)
        {
            return -1;
        }
        else if (_currentValue < _rangeBegin || _currentValue > _rangeEnd)
        {
            return -2;
        }
        else if (_addition < 1)
        {
            return -3;
        }
        else if ((_currentValue + _addition) <= _rangeEnd)
        {
            return _currentValue + _addition;
        }

        _addition -= _rangeEnd - _currentValue;

        int spaceLength = DistanceOf(_rangeEnd, _rangeBegin) + 1;

        while (true)
        {
            if (_addition > spaceLength)
            {
                _addition -= spaceLength;
            }
            else
            {
                return (_rangeBegin + _addition) - 1;
            }
        }
    }

    //_rangeBegin >= _rangeEnd => -1
    //_currentValue < _rangeBegin || _value > _rangeEnd => -2
    //_subtraction < 1 => -3
    //(20, 35, 28, 9) => 35
    //(20, 35, 28, 61) => 31
    //(-8, 5, -3, 19) => -8
    int CircularSubtraction(int _rangeBegin, int _rangeEnd, int _currentValue, int _subtraction)
    {
        if (_rangeBegin >= _rangeEnd)
        {
            return -1;
        }
        else if (_currentValue < _rangeBegin || _currentValue > _rangeEnd)
        {
            return -2;
        }
        else if (_subtraction < 1)
        {
            return -3;
        }
        else if ((_currentValue - _subtraction) >= _rangeBegin)
        {
            return _currentValue - _subtraction;
        }

        _subtraction -= _currentValue - _rangeBegin;

        int spaceLength = DistanceOf(_rangeEnd, _rangeBegin) + 1;

        while (true)
        {
            if (_subtraction > spaceLength)
            {
                _subtraction -= spaceLength;
            }
            else
            {
                return (_rangeEnd - _subtraction) + 1;
            }
        }
    }

	//returns the number of bits needed for the binary representation of _number
	int BitLengthOf(unsigned int _number)
	{
		if (_number == 0 || _number == 1) return 1;

		int length = 0;

		while (_number > 0)
		{
			_number /= 2;
			length++;
		}

		return length;
	}

    //_size is the size of _hex
    unsigned long long ToDecimal(const char* _hex, int _size)
    {
        unsigned long long result = 0;

        for (int i = _size - 1, n = 0; i > -1; i--, n++)
        {
            char symbol = _hex[i];

            if (symbol == '1')
            {
                result += Pow(16, n);
            }
            else if (symbol == '2')
            {
                result += 2 * Pow(16, n);
            }
            else if (symbol == '3')
            {
                result += 3 * Pow(16, n);
            }
            else if (symbol == '4')
            {
                result += 4 * Pow(16, n);
            }
            else if (symbol == '5')
            {
                result += 5 * Pow(16, n);
            }
            else if (symbol == '6')
            {
                result += 6 * Pow(16, n);
            }
            else if (symbol == '7')
            {
                result += 7 * Pow(16, n);
            }
            else if (symbol == '8')
            {
                result += 8 * Pow(16, n);
            }
            else if (symbol == '9')
            {
                result += 9 * Pow(16, n);
            }
            else if (symbol == 'A')
            {
                result += 10 * Pow(16, n);
            }
            else if (symbol == 'B')
            {
                result += 11 * Pow(16, n);
            }
            else if (symbol == 'C')
            {
                result += 12 * Pow(16, n);
            }
            else if (symbol == 'D')
            {
                result += 13 * Pow(16, n);
            }
            else if (symbol == 'E')
            {
                result += 14 * Pow(16, n);
            }
            else if (symbol == 'F')
            {
                result += 15 * Pow(16, n);
            }
        }

        return result;
    }
}
