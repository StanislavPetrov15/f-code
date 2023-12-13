//<T> is built-in integral type
    template<typename T> struct Range
    {
        private:

        T Begin = 0;
        T End = 0;
        T Length = 0;

        public:

		//CONSTRUCTORS:

        Range() = default;

        //_end >= _begin ->
        Range(T _begin, T _end): Begin(_begin), End(_end)
        {
            if (Begin > End)
            {
                return;
            }

            T n = End - Begin;

            Length = ++ n;
        }

        Range(const Range&) = default;

		//OPERATORS:

        Range& operator=(const Range&) = default;

        bool operator==(const Range& _range) const
        {
            return Begin == _range.Begin && End == _range.End;
        }

        bool operator!=(const Range& _range) const
        {
            return Begin != _range.Begin || End != _range.End;
        }

        //determines if the beginning of &this is before the beginning of _range
        //Range(29, 38) < Range(27, 35) => false
        //Range(29, 38) < Range(29, 35) => false
        //Range(29, 38) < Range(30, 35) => true
        bool operator<(const Range& _range) const
        {
            return Begin < _range.Begin;
        }

        //determines if the beginning of &this is after the beginning of _range
        //Range(29, 38) > Range(29, 35) => false
        //Range(29, 38) > Range(30, 35) => false
        //Range(29, 38) > Range(27, 35) => true
        bool operator>(const Range& _range) const
        {
            return Begin > _range.Begin;
        }

        //generates new range with beginning (the beginning of &this) and end (the end of _range)
        //the two ranges must be neighboring
        //if the two ranges are not neighboring the function returns {}
        //Range(22, 40) & Range(41, 53) => (22, 53)
        //Range(41, 53) & Range(22, 40) => (22, 53)
        Range operator&(Range& _range)
        {
            if (! IsAdjacentTo(_range)) return {};

            Range& r1 = *this < _range ? *this : _range;
            Range& r2 = *this < _range ? _range : *this;
            Range range(r1.Begin, r2.End);

            return range;
        }

		//FIELDS:

        int begin() const
        {
            return Begin;
        }

        int end() const
        {
            return End;
        }

        int length() const
        {
            return Length;
        }

        bool IsSet() const
        {
            return End >= Begin;
        }

		//FUNCTIONS:

        //Range(21, 30).IsAdjacentTo(Range(32, 37)) => false
        //Range(21, 30).IsAdjacentTo(Range(31, 37)) => true
        //Range(31, 37).IsAdjacentTo(Range(21, 30)) => true
        bool IsAdjacentTo(const Range& _range) const
        {
            if (! IsSet() || ! _range.IsSet())
            {
                return false;
            }
            else
            {
                return IsRightBefore(_range) || IsRightAfter(_range);
            }
        }

        //Range(21, 30).IsBefore(Range(30, 35)) => false
        //Range(21, 30).IsBefore(Range(31, 37)) => true
        //Range(21, 30).IsBefore(Range(35, 37)) => true
        bool IsBefore(const Range& _range) const
        {
            if (! IsSet() || ! _range.IsSet())
            {
                return false;
            }
            else
            {
                return End < _range.Begin;
            }
        }

        //Range(30, 35).IsAfter(Range(21, 30)) => false
        //Range(33, 37).IsAfter(Range(21, 30)) => true
        bool IsAfter(const Range& _range) const
        {
            if (! IsSet() || ! _range.IsSet())
            {
                return false;
            }
            else
            {
                return Begin > _range.End;
            }
        }

        //Range(21, 30).IsRightBefore(Range(32, 35)) => false
        //Range(21, 30).IsRightBefore(Range(31, 35)) => true
        bool IsRightBefore(const Range& _range) const
        {
            if (! IsSet() || ! _range.IsSet())
            {
                return false;
            }
            else
            {
                return End + 1 == _range.Begin;
            }
        }

        //Range(32, 35).IsRightAfter(Range(21, 30)) => false
        //Range(31, 35).IsRightAfter(Range(21, 30)) => true
        bool IsRightAfter(const Range& _range) const
        {
            if (! IsSet() || ! _range.IsSet())
            {
                return false;
            }
            else
            {
                return Begin == _range.End + 1;
            }
        }

        //Range(21, 30).AlignWith(Range(21, 50)) => true
        //Range(21, 30).AlignWith(Range(22, 50)) => false
        bool AlignWith(const Range& _range) const
        {
            if (! IsSet() || ! _range.IsSet())
            {
                return false;
            }
            else
            {
                return Begin == _range.Begin;
            }
        }

        //Range(76, 81).Contains(82) => false
        //Range(76, 81).Contains(81) => true
        bool Contains(const T& _value) const
        {
            return _value >= Begin && _value <= End;
        }

        //Range(73, 90).Contains(Range(78, 91)) => false
        //Range(73, 90).Contains(Range(78, 90)) => true
        bool Contains(const Range& _range) const
        {
            if (! IsSet() || ! _range.IsSet())
            {
                return false;
            }
            else
            {
                return _range.Begin >= Begin && _range.End <= End;
            }
        }

        //Range(73, 90).Intersects(Range(78, 90)) => false
        //Range(73, 90).Intersects(Range(78, 92)) => true
        bool Intersects(const Range& _range) const
        {
            const Range& r1 = *this < _range ? *this : _range;
            const Range& r2 = *this < _range ? _range : *this;

            if (r1 == r2)
            {
                return false;
            }
            else if (! r1.IsSet() || ! r2.IsSet())
            {
                return false;
            }
            else if (r1.Contains(r2) || r2.Contains(r1))
            {
                return false;
            }
            else if (r1.AlignWith(r2))
            {
                return false;
            }
            else
            {
                return r1.Begin < r2.Begin && r1.End < r2.End;
            }
        }
    };

    //DisplacementOf(Range(23, 30), Range(35, 40)) => 12
    //DisplacementOf(Range(23, 30), Range(14, 40)) => 9
    //DisplacementOf(Range(-5, 8), Range(20, 23)) => 25
    //DisplacementOf(Range(-119, -108), Range(-105, 92)) => 14
    template<typename T> int DisplacementOf(const Range<T>& R1, const Range<T>& R2)
    {
        if (! R1.IsSet() || ! R2.IsSet()) return - 1;

        const Range<T>& earlier = R1.begin() < R2.begin() ? R1 : R2;
        const Range<T>& later = R1.begin() < R2.begin() ? R2 : R1;

        return later.begin() - earlier.begin();
    }

    //IntervalOf(Range(23, 30), Range(35, 40)) => 4
    //IntervalOf(Range(35, 40), Range(23, 30)) => 4
    //IntervalOf(Range(-5, 8), Range(20, 23)) => 11
    //IntervalOf(Range(-119, -108), Range(-105, 92)) => 2
    template<typename T> int IntervalOf(const Range<T>& R1, const Range<T>& R2)
    {
        if (! R1.IsSet() || ! R2.IsSet()) return - 1;

        const Range<T>& earlier = R1.begin() < R2.begin() ? R1 : R2;
        const Range<T>& later = R1.begin() < R2.begin() ? R2 : R1;

        return later.begin() - earlier.end() - 1;
    }
