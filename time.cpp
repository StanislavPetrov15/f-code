namespace time_
{
	const int SECONDS_IN_AN_HOUR = 3600;

	const int SECONDS_IN_A_DAY = 86400;

	const int MINUTES_IN_A_DAY = 1440;

	//the length of months in a non-leap year
	const list<int> MONTH_LENGTHS { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	enum TimeUnit { MILLISECOND, SECOND };

	struct DateTime;
	bool IsLeap(int);
	bool IsValidDate(const DateTime&);

	struct DateTime
	{
	    private:

		int Year = 0;
		int Month = 0;
		int Day = 0;
		int Hour = 0;
		int Minute = 0;
		int Second = 0;
		int Timezone = 0;

	    public:

	    ///CONSTRUCTORS

		DateTime() = default;

		DateTime(int _year, int _month, int _day, int _hour, int _minute, int _second, int _timezone_ = 0) :
			Year(_year),
			Month(_month),
			Day(_day),
			Hour(_hour),
			Minute(_minute),
			Second(_second),
			Timezone(_timezone_) {}

		DateTime(const DateTime&) = default;

		///OPERATORS

		DateTime& operator=(const DateTime&) = default;

		bool operator==(const DateTime& _datetime) const
		{
			DateTime datetime = (*this);
			DateTime datetime_ = _datetime;

			datetime.ToTimezone(0);
			datetime_.ToTimezone(0);

			return datetime.year() == datetime_.year() &&
				datetime.month() == datetime_.month() &&
				datetime.day() == datetime_.day() &&
				datetime.hour() == datetime_.hour() &&
				datetime.minute() == datetime_.minute() &&
				datetime.second() == datetime_.second();
		}

		bool operator!=(const DateTime& _datetime) const
		{
			DateTime datetime = (*this);
			DateTime datetime_ = _datetime;

			datetime.ToTimezone(0);
			datetime_.ToTimezone(0);

			return datetime.year() != datetime_.year() ||
				datetime.month() != datetime_.month() ||
				datetime.day() != datetime_.day() ||
				datetime.hour() != datetime_.hour() ||
				datetime.minute() != datetime_.minute() ||
				datetime.second() != datetime_.second();
		}

		///FIELDS

		int year() const
        {
		    return Year;
        }

		int month() const
        {
		    return Month;
        }

		int day() const
        {
		    return Day;
        }

		int hour() const
        {
		    return Hour;
        }

		int minute() const
        {
		    return Minute;
        }

		int second() const
        {
		    return Second;
        }

		int timezone() const
        {
		    return Timezone;
        }

		///FUNCTIONS

		//23-5-2009 09:51:07 +3 -> ToTimezone(7) => 23-5-2009 13:51:07 7
        //23-5-2009 09:51:07 +3 -> ToTimezone(-8) => 22-5-2009 22:51:07 -8
		//_timezone_ >= -11 & _timezone_ <= 14 ->
		void ToTimezone(int _timezone_)
		{
			if (_timezone_ < -11 || _timezone_ > 14) return;

			if (Timezone < _timezone_)
			{
				Hour += _timezone_ - Timezone;
			}
			else if (Timezone > _timezone_)
			{
				Hour -= Timezone - _timezone_;
			}

			//

			if (Hour < 0)
			{
				Hour += 24;
				Day--;
			}
			else if (Hour > 23)
			{
				Hour -= 24;
				Day++;
			}

			//

			int month = Month - 1;
			int monthLength = IsLeap(Year) && Month == 1 ? MONTH_LENGTHS[month] + 1 : MONTH_LENGTHS[month];
			if (Day < 1)
			{
				Month--;
			}
			else if (Day > monthLength)
			{
				Month++;
				Day = 1;
			}

			//

			if (Month < 1)
			{
				Month = 12;
				Year--;
				Day = IsLeap(Year) && Month == 1 ? MONTH_LENGTHS[11] + 1 : MONTH_LENGTHS[11];
			}
			else if (Month > 12)
			{
				Month = 1;
				Year++;
			}

			//

			Timezone = _timezone_;
		}

		bool IsAfter(const DateTime& _datetime) const
		{
			DateTime datetime = (*this);
			DateTime datetime_ = _datetime;

			datetime.ToTimezone(0);
			datetime_.ToTimezone(0);

			if (datetime.year() > datetime_.year()) return true;
			if (datetime.year() < datetime_.year()) return false;

			//-> datetime.year() == _datetime.year() ->

			if (datetime.month() > datetime_.month()) return true;
			if (datetime.month() < datetime_.month()) return false;

			//-> datetime.month() == _datetime.month() ->

			if (datetime.day() > datetime_.day()) return true;
			if (datetime.day() < datetime_.day()) return false;

			//-> datetime.day() == _datetime.day() ->

			if (datetime.hour() > datetime_.hour()) return true;
			if (datetime.hour() < datetime_.hour()) return false;

			//-> datetime.hour() == _datetime.hour() ->

			if (datetime.minute() > datetime_.minute()) return true;
			if (datetime.minute() < datetime_.minute()) return false;

			//-> datetime.minute() == _datetime.minute() ->

			if (datetime.second() > datetime_.second()) return true;
			if (datetime.second() < datetime_.second()) return false;
		}

		bool IsBefore(const DateTime& _datetime) const
		{
			DateTime datetime = (*this);
			DateTime datetime_ = _datetime;

			datetime.ToTimezone(0);
			datetime_.ToTimezone(0);

			if (datetime.year() < datetime_.year()) return true;
			if (datetime.year() > datetime_.year()) return false;

			//-> datetime.year() == _datetime.year() ->

			if (datetime.month() < datetime_.month()) return true;
			if (datetime.month() > datetime_.month()) return false;

			//-> datetime.month() == _datetime.month() ->

			if (datetime.day() < datetime_.day()) return true;
			if (datetime.day() > datetime_.day()) return false;

			//-> datetime.day() == _datetime.day() ->

			if (datetime.hour() < datetime_.hour()) return true;
			if (datetime.hour() > datetime_.hour()) return false;

			//-> datetime.hour() == _datetime.hour() ->

			if (datetime.minute() < datetime_.minute()) return true;
			if (datetime.minute() > datetime_.minute()) return false;

			//-> datetime.minute() == _datetime.minute() ->

			if (datetime.second() < datetime_.second()) return true;
			if (datetime.second() > datetime_.second()) return false;
		}
	};

    int Year = 0;
    int Month = 0;
    int Day = 0;
    int Hour = 0;
    int Minute = 0;
    int Second = 0;
    int Timezone = 0;

	bool IsValidDateTime(const DateTime&);
	//DayOfYear({ 2024, 2, 5, 0, 0, 0, 0 }) => 36
	int DayOfYear(const DateTime& _datetime)
	{
	    if (!IsValidDateTime(_datetime)) return -1;

		int day = 0;

		bool isLeap = IsLeap(_datetime.year());
		for (int i = 0; i < _datetime.month() - 1; i++)
		{
			day += isLeap && i == 1 ? MONTH_LENGTHS[i] + 1 : MONTH_LENGTHS[i];
		}

		return day + _datetime.day();
	}

	//number of seconds since UNIX Epoch
	long long Elapsed()
    {
	    return time(nullptr);
    }

    //returns the number of seconds between _datetime and _datetime_
	//_datetime1 and/or _datetime2 is not valid => -1
	unsigned long long IntervalOf(const DateTime& _datetime1, const DateTime& _datetime2)
	{
		if (!IsValidDateTime(_datetime1) || !IsValidDateTime(_datetime2)) return -1;

		DateTime datetime = _datetime1;
		DateTime datetime_ = _datetime2;

		datetime.ToTimezone(0);
		datetime_.ToTimezone(0);

		DateTime& earlierDate = datetime.IsBefore(datetime_) ? datetime : datetime_;
		DateTime& laterDate = datetime_.IsAfter(datetime_) ? datetime : datetime_;

		int earlierDateSOY = (earlierDate.hour() * SECONDS_IN_AN_HOUR) + (earlierDate.minute() * 60) + earlierDate.second();
		int laterDateSOY = (laterDate.hour() * SECONDS_IN_AN_HOUR) + (laterDate.minute() * 60) + laterDate.second();
		int earlierDateDOY = DayOfYear(earlierDate);
		int laterDateDOY = DayOfYear(laterDate);

		if (earlierDate.year() == laterDate.year() && earlierDateDOY == laterDateDOY)
		{
			return laterDateSOY - earlierDateSOY;
		}

		int seconds = 0;

		//remaining seconds until the end of the earlier day
		seconds += SECONDS_IN_A_DAY - earlierDateSOY;

		//full days between earlier and the later day
		int days = 0;

		if (earlierDate.year() == laterDate.year())
		{
			days = (laterDateDOY - earlierDateDOY);
		}
		else
		{
			//remaining days until the end of (the year of the earlier date)
			days += IsLeap(earlierDate.year()) ? 366 - earlierDateDOY : 365 - earlierDateDOY;

			//the days in (the years between the earlier and the later date)
			for (int year = earlierDate.year() + 1; year < laterDate.year(); year++)
			{
				days += IsLeap(year) ? 366 : 365;
			}

			//number of days in (the year of the later date)
			days += laterDateDOY;
		}

		seconds += (days - 1) * SECONDS_IN_A_DAY;

		//number of seconds since the beginning of the later date
		seconds += laterDateSOY;

		return seconds;
	}

	//_year >= 1600 ->
	bool IsLeap(int _year)
	{
	    //if the year is not divisible by 4 without remainder
	    if (numeric::Mod(_year, 4) != 0)
        {
            return false;
        }
	    //if the year is 'centurial'
	    if (numeric::Mod(_year, 100) == 0 && numeric::Mod(_year, 400) != 0)
        {
            return false;
        }
	    else
        {
            return true;
        }
	}

	//_datetime.year() > 4000 => false
	bool IsValidDateTime(const DateTime& _datetime)
	{
		if (_datetime.year() < 1 || _datetime.year() > 4000) return false;

		if (_datetime.month() < 1 || _datetime.month() > 12) return false;

		int month = _datetime.month() - 1;
		int monthLength = IsLeap(_datetime.year()) && _datetime.month() == 1 ? MONTH_LENGTHS[month] + 1 : MONTH_LENGTHS[month];
		if (_datetime.day() < 1 || _datetime.day() > monthLength) return false;

		if (_datetime.hour() < 0 || _datetime.hour() > 23) return false;

		if (_datetime.minute() < 0 || _datetime.minute() > 59) return false;

		if (_datetime.second() < 0 || _datetime.second() > 59) return false;

		if (_datetime.timezone() < -12 || _datetime.timezone() > 14) return false;

		return true;
	}

	//=> UTC
	DateTime Now()
	{
		long long seconds = time(nullptr); //seconds since UNIX Epoch

		int year = 1970;
        int month = 1;

        //determine the current year
    while (true)
    {
        int daysInYear = IsLeap(year) ? 366 : 365;

        if (seconds < (daysInYear * SECONDS_IN_A_DAY)) break;

        int secondsInYear = daysInYear * SECONDS_IN_A_DAY;

        seconds -= secondsInYear;

        year++;
    }

    //determine the current month
    while (true)
    {
        int daysInMonth = IsLeap(year) && month == 2 ? 29 : MONTH_LENGTHS[month];

        if (seconds < (daysInMonth * SECONDS_IN_A_DAY)) break;

        int secondsInMonth = daysInMonth * SECONDS_IN_A_DAY;

        seconds -= secondsInMonth;

        month++;
    }

		int dayOfMonth = (seconds / SECONDS_IN_A_DAY) + 1;

		int secondOfDay = numeric::Mod(seconds, SECONDS_IN_A_DAY);

		int hour = secondOfDay / SECONDS_IN_AN_HOUR;

		int secondOfHour = numeric::Mod(secondOfDay, SECONDS_IN_AN_HOUR);

		int minutes = secondOfHour / 60;

		int secondOfMinute = numeric::Mod(secondOfHour, 60);

		return { year, month, dayOfMonth, hour, minutes, secondOfMinute };
	}
}
