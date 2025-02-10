namespace time_
{
    //(!) ALL FUNCTIONALITY USES THE GREGORIAN CALENDAR
    //(!) YEARS GIVEN AS ARGUMENTS MUST FALL IN THE RANGE (1600..9999)

	const int SECONDS_IN_AN_HOUR = 3600;

	const int SECONDS_IN_A_DAY = 86400;

	const int MINUTES_IN_A_DAY = 1440;

	//the length of months in a non-leap year
	const list<int> MONTH_LENGTHS { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	enum TimeUnit { MILLISECOND, SECOND };

	struct DateTime;
	bool IsLeap(int);
	bool IsValidDate(const DateTime&);
    void ToTimezone(int&, int&, int&, int&, int&, int&, int&, int);

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

		//{ 23-5-2009 09:51:07 +3 }.ToTimezone(7) => { 23-5-2009 13:51:07 7 }
        //{ 23-5-2009 09:51:07 +3 }.ToTimezone(-8) => { 22-5-2009 22:51:07 -8 }
		//_timezone_ >= -11 & _timezone_ <= 14 ->
		void ToTimezone(int _timezone_)
		{
            time_::ToTimezone(Year, Month, Day, Hour, Minute, Second, Timezone, _timezone_);
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

    //ToTimezone(2009, 5, 23, 9, 51, 07, +3, 7) -> 2009, 5, 23, 13, 51, 07, 7
    //ToTimezone(2009, 5, 23, 9, 51, 07, +3, -8) -> 2009, 5, 22, 22, 51, 07, -8
    //_newTimeZone >= -11 & _newTimeZone <= 14 ->
    void ToTimezone(int& _year, int& _month, int& _day, int& _hour, int& _minute, int& _second, int& _timezone_, int _newTimeZone)
    {
        if (_newTimeZone < -11 || _newTimeZone > 14) return;

        if (_timezone_ < _newTimeZone)
        {
            _hour += _newTimeZone - _timezone_;
        }
        else if (_timezone_ > _newTimeZone)
        {
            _hour -= _timezone_ - _newTimeZone;
        }

        //

        if (_hour < 0)
        {
            _hour += 24;
            _day--;
        }
        else if (_hour > 23)
        {
            _hour -= 24;
            _day++;
        }

        //

        int month = _month - 1;
        int monthLength = IsLeap(_year) && _month == 1 ? MONTH_LENGTHS[month] + 1 : MONTH_LENGTHS[month];
        if (_day < 1)
        {
            _month--;
        }
        else if (_day > monthLength)
        {
            _month++;
            _day = 1;
        }

        //

        if (_month < 1)
        {
            _month = 12;
            _year--;
            _day = IsLeap(_year) && _month == 1 ? MONTH_LENGTHS[11] + 1 : MONTH_LENGTHS[11];
        }
        else if (_month > 12)
        {
            _month = 1;
            _year++;
        }

        //

        _timezone_ = _newTimeZone;
    }

    //this function is not validating; the string must be in a valid format and also the parameter _inputFormat must correspond to the given string
    //D :: day; M :: month; Y :: year; H :: hour; M :: minute; S :: second; T :: Timezone (UTC)
    /* possible formats for the parameter _string:
       format 1 = D.M.Y
       format 2 = M.D.Y
       format 3 = D.M.Y H:M:S T
       format 4 = M.D.Y H:M:S T
       format 5 = D-M-Y
       format 6 = M-D-Y
       format 7 = D-M-Y H:M:S T
       format 8 = M-D-Y H:M:S T
       format 9 = D/M/Y
       format 10 = M/D/Y
       format 11 = D/M/Y H:M:S T
       format 12 = M/D/Y H:M:S T
       (EXAMPLE) "18-10-2029 3:15:41 +2"
       (EXAMPLE) "5.7.1982" */
    DateTime ToDateTime(const string& _string, int _inputFormat)
    {
        if (_inputFormat == 1)
        {
            list<string> elements = _string.Split('.');
            int day = elements[0].ToInteger(DECIMAL_A);
            int month = elements[1].ToInteger(DECIMAL_A);
            int year = elements[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, 0, 0, 0);
        }
        else if (_inputFormat == 2)
        {
            list<string> elements = _string.Split('.');
            int day = elements[1].ToInteger(DECIMAL_A);
            int month = elements[0].ToInteger(DECIMAL_A);
            int year = elements[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, 0, 0, 0);
        }
        else if (_inputFormat == 3)
        {
            list<string> parts = _string.Split(' ');
            list<string> firstPart = parts[0].Split('.');
            list<string> secondPart = parts[1].Split(':');
            int day = firstPart[0].ToInteger(DECIMAL_A);
            int month = firstPart[1].ToInteger(DECIMAL_A);
            int year = firstPart[2].ToInteger(DECIMAL_A);
            int hour = secondPart[0].ToInteger(DECIMAL_A);
            int minute = secondPart[1].ToInteger(DECIMAL_A);
            int second = secondPart[2].ToInteger(DECIMAL_A);
            int timezone = parts[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, hour, minute, second, timezone);
        }
        else if (_inputFormat == 4)
        {
            list<string> parts = _string.Split(' ');
            list<string> firstPart = parts[0].Split('.');
            list<string> secondPart = parts[1].Split(':');
            int day = firstPart[1].ToInteger(DECIMAL_A);
            int month = firstPart[0].ToInteger(DECIMAL_A);
            int year = firstPart[2].ToInteger(DECIMAL_A);
            int hour = secondPart[0].ToInteger(DECIMAL_A);
            int minute = secondPart[1].ToInteger(DECIMAL_A);
            int second = secondPart[2].ToInteger(DECIMAL_A);
            int timezone = parts[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, hour, minute, second, timezone);
        }
        else if (_inputFormat == 5)
        {
            list<string> elements = _string.Split('-');
            int day = elements[0].ToInteger(DECIMAL_A);
            int month = elements[1].ToInteger(DECIMAL_A);
            int year = elements[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, 0, 0, 0);
        }
        else if (_inputFormat == 6)
        {
            list<string> elements = _string.Split('-');
            int day = elements[1].ToInteger(DECIMAL_A);
            int month = elements[0].ToInteger(DECIMAL_A);
            int year = elements[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, 0, 0, 0);
        }
        else if (_inputFormat == 7)
        {
            list<string> parts = _string.Split(' ');
            list<string> firstPart = parts[0].Split('-');
            list<string> secondPart = parts[1].Split(':');
            int day = firstPart[0].ToInteger(DECIMAL_A);
            int month = firstPart[1].ToInteger(DECIMAL_A);
            int year = firstPart[2].ToInteger(DECIMAL_A);
            int hour = secondPart[0].ToInteger(DECIMAL_A);
            int minute = secondPart[1].ToInteger(DECIMAL_A);
            int second = secondPart[2].ToInteger(DECIMAL_A);
            int timezone = parts[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, hour, minute, second, timezone);
        }
        else if (_inputFormat == 8)
        {
            list<string> parts = _string.Split(' ');
            list<string> firstPart = parts[0].Split('-');
            list<string> secondPart = parts[1].Split(':');
            int day = firstPart[1].ToInteger(DECIMAL_A);
            int month = firstPart[0].ToInteger(DECIMAL_A);
            int year = firstPart[2].ToInteger(DECIMAL_A);
            int hour = secondPart[0].ToInteger(DECIMAL_A);
            int minute = secondPart[1].ToInteger(DECIMAL_A);
            int second = secondPart[2].ToInteger(DECIMAL_A);
            int timezone = parts[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, hour, minute, second, timezone);
        }
        else if (_inputFormat == 9)
        {
            list<string> elements = _string.Split('/');
            int day = elements[0].ToInteger(DECIMAL_A);
            int month = elements[1].ToInteger(DECIMAL_A);
            int year = elements[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, 0, 0, 0);
        }
        else if (_inputFormat == 10)
        {
            list<string> elements = _string.Split('/');
            int day = elements[1].ToInteger(DECIMAL_A);
            int month = elements[0].ToInteger(DECIMAL_A);
            int year = elements[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, 0, 0, 0);
        }
        else if (_inputFormat == 11)
        {
            list<string> parts = _string.Split(' ');
            list<string> firstPart = parts[0].Split('/');
            list<string> secondPart = parts[1].Split(':');
            int day = firstPart[0].ToInteger(DECIMAL_A);
            int month = firstPart[1].ToInteger(DECIMAL_A);
            int year = firstPart[2].ToInteger(DECIMAL_A);
            int hour = secondPart[0].ToInteger(DECIMAL_A);
            int minute = secondPart[1].ToInteger(DECIMAL_A);
            int second = secondPart[2].ToInteger(DECIMAL_A);
            int timezone = parts[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, hour, minute, second, timezone);
        }
        else if (_inputFormat == 12)
        {
            list<string> parts = _string.Split(' ');
            list<string> firstPart = parts[0].Split('/');
            list<string> secondPart = parts[1].Split(':');
            int day = firstPart[1].ToInteger(DECIMAL_A);
            int month = firstPart[0].ToInteger(DECIMAL_A);
            int year = firstPart[2].ToInteger(DECIMAL_A);
            int hour = secondPart[0].ToInteger(DECIMAL_A);
            int minute = secondPart[1].ToInteger(DECIMAL_A);
            int second = secondPart[2].ToInteger(DECIMAL_A);
            int timezone = parts[2].ToInteger(DECIMAL_A);
            return DateTime(year, month, day, hour, minute, second, timezone);
        }
    }

    //D :: day; M :: month; Y :: year; H :: hour; M :: minute; S :: second; T :: Timezone (UTC)
    /* possible formats for the output string:
       format 1 = D.M.Y
       format 2 = M.D.Y
       format 3 = D.M.Y H:M:S T
       format 4 = M.D.Y H:M:S T
       format 5 = D-M-Y
       format 6 = M-D-Y
       format 7 = D-M-Y H:M:S T
       format 8 = M-D-Y H:M:S T
       format 9 = D/M/Y
       format 10 = M/D/Y
       format 11 = D/M/Y H:M:S T
       format 12 = M/D/Y H:M:S T */
    string ToStringTime(const DateTime& _dateTime, int _outputFormat)
    {
        if (_outputFormat == 1)
        {
            return string::FromInteger(_dateTime.day()) + "." +
                   string::FromInteger(_dateTime.month()) + "." +
                   string::FromInteger(_dateTime.year());
        }
        else if (_outputFormat == 2)
        {
            return string::FromInteger(_dateTime.month()) + "." +
                   string::FromInteger(_dateTime.day()) + "." +
                   string::FromInteger(_dateTime.year());
        }
        else if (_outputFormat == 3)
        {
            return string::FromInteger(_dateTime.day()) + "." +
                   string::FromInteger(_dateTime.month()) + "." +
                   string::FromInteger(_dateTime.year()) + " " +
                   string::FromInteger(_dateTime.hour()) + ":" +
                   string::FromInteger(_dateTime.minute()) + ":" +
                   string::FromInteger(_dateTime.second()) + " " +
                   string::FromInteger(_dateTime.timezone());
        }
        else if (_outputFormat == 4)
        {
            return string::FromInteger(_dateTime.month()) + "." +
                   string::FromInteger(_dateTime.day()) + "." +
                   string::FromInteger(_dateTime.year()) + " " +
                   string::FromInteger(_dateTime.hour()) + ":" +
                   string::FromInteger(_dateTime.minute()) + ":" +
                   string::FromInteger(_dateTime.second()) + " " +
                   string::FromInteger(_dateTime.timezone());
        }
        else if (_outputFormat == 5)
        {
            return string::FromInteger(_dateTime.day()) + "-" +
                   string::FromInteger(_dateTime.month()) + "-" +
                   string::FromInteger(_dateTime.year());
        }
        else if (_outputFormat == 6)
        {
            return string::FromInteger(_dateTime.month()) + "-" +
                   string::FromInteger(_dateTime.day()) + "-" +
                   string::FromInteger(_dateTime.year());
        }
        else if (_outputFormat == 7)
        {
            return string::FromInteger(_dateTime.day()) + "-" +
                   string::FromInteger(_dateTime.month()) + "-" +
                   string::FromInteger(_dateTime.year()) + " " +
                   string::FromInteger(_dateTime.hour()) + ":" +
                   string::FromInteger(_dateTime.minute()) + ":" +
                   string::FromInteger(_dateTime.second()) + " " +
                   string::FromInteger(_dateTime.timezone());
        }
        else if (_outputFormat == 8)
        {
            return string::FromInteger(_dateTime.month()) + "-" +
                   string::FromInteger(_dateTime.day()) + "-" +
                   string::FromInteger(_dateTime.year()) + " " +
                   string::FromInteger(_dateTime.hour()) + ":" +
                   string::FromInteger(_dateTime.minute()) + ":" +
                   string::FromInteger(_dateTime.second()) + " " +
                   string::FromInteger(_dateTime.timezone());
        }
        else if (_outputFormat == 9)
        {
            return string::FromInteger(_dateTime.day()) + "/" +
                   string::FromInteger(_dateTime.month()) + "/" +
                   string::FromInteger(_dateTime.year());
        }
        else if (_outputFormat == 10)
        {
            return string::FromInteger(_dateTime.month()) + "/" +
                   string::FromInteger(_dateTime.day()) + "/" +
                   string::FromInteger(_dateTime.year());
        }
        else if (_outputFormat == 11)
        {
            return string::FromInteger(_dateTime.day()) + "/" +
                   string::FromInteger(_dateTime.month()) + "/" +
                   string::FromInteger(_dateTime.year()) + " " +
                   string::FromInteger(_dateTime.hour()) + ":" +
                   string::FromInteger(_dateTime.minute()) + ":" +
                   string::FromInteger(_dateTime.second()) + " " +
                   string::FromInteger(_dateTime.timezone());
        }
        else if (_outputFormat == 12)
        {
            return string::FromInteger(_dateTime.month()) + "/" +
                   string::FromInteger(_dateTime.day()) + "/" +
                   string::FromInteger(_dateTime.year()) + " " +
                   string::FromInteger(_dateTime.hour()) + ":" +
                   string::FromInteger(_dateTime.minute()) + ":" +
                   string::FromInteger(_dateTime.second()) + " " +
                   string::FromInteger(_dateTime.timezone());
        }
    }

    //DayOfYear(2024, 2, 5) => 36
    int DayOfYear(int _year, int _month, int _day)
    {
        int day = 0;

        bool isLeap = IsLeap(_year);
        for (int i = 0; i < _month - 1; i++)
        {
            day += isLeap && i == 1 ? MONTH_LENGTHS[i] + 1 : MONTH_LENGTHS[i];
        }

        return day + _day;
    }

	bool IsValidDateTime(const DateTime&);
    //_datetime is not valid => -1
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

    //_datetime.Year >= 1600 ->
    int DayOfWeek(int _year, int _month, int _day)
    {
        //determine the first day of week for _datetime.year()

        int weekdayOfYear = 6; //1 January 1600 is Saturday ->
        int datetimeYear = _year;

        for (int year = 1600; year < datetimeYear; year++)
        {
            if (IsLeap(year))
            {
                if (weekdayOfYear == 6)
                {
                    weekdayOfYear = 1;
                }
                else if (weekdayOfYear == 7)
                {
                    weekdayOfYear = 2;
                }
                else
                {
                    weekdayOfYear += 2;
                }
            }
            else
            {
                if (weekdayOfYear == 7)
                {
                    weekdayOfYear = 1;
                }
                else
                {
                    weekdayOfYear++;
                }
            }
        }

        //

        int dayOfWeek = weekdayOfYear;

        dayOfWeek += (DayOfYear(_year, _month, _day) - 1) % 7;

        if (dayOfWeek > 7)
        {
            dayOfWeek -= 7;
        }

        return dayOfWeek;
    }

    //_datetime1 and/or _datetime2 is not valid => -1
    //_datetime.Year >= 1600 ->
    int DayOfWeek(const DateTime& _datetime)
    {
        if (!IsValidDateTime(_datetime)) return -1;

        return DayOfWeek(_datetime.day(), _datetime.month(), _datetime.year());
    }

	//number of seconds since UNIX Epoch
	long long Elapsed()
    {
	    return time(nullptr);
    }

    //returns the number of seconds between the two intervals
    //_year1 >= 1600 && _year2 >= 1600 ->
    unsigned long long IntervalOf(
        int _year1, int _month1, int _day1, int _hour1, int _minute1, int _second1, int _timezone1,
        int _year2, int _month2, int _day2, int _hour2, int _minute2, int _second2, int _timezone2)
    {
        ToTimezone(_year1, _month1, _day1, _hour1, _minute1, _second1, _timezone1, 0);
        ToTimezone(_year2, _month2, _day2, _hour2, _minute2, _second2, _timezone2, 0);

        int earlierYear = _year1 < _year2 ? _year1 : _year2;
        int earlierMonth = _month1 < _month2 ? _month1 : _month2;
        int earlierDay = _day1 < _day2 ? _day1 : _day2;
        int earlierHour = _hour1 < _hour2 ? _hour1 : _hour2;
        int earlierMinute = _minute1 < _minute2 ? _minute1 : _minute2;
        int earlierSecond = _second1 < _second2 ? _second1 : _second2;
        int laterYear = _year1 > _year2 ? _year1 : _year2;
        int laterMonth = _month1 > _month2 ? _month1 : _month2;
        int laterDay = _day1 > _day2 ? _day1 : _day2;
        int laterHour = _hour1 > _hour2 ? _hour1 : _hour2;
        int laterMinute = _minute1 > _minute2 ? _minute1 : _minute2;
        int laterSecond = _second1 > _second2 ? _second1 : _second2;

        int earlierDateSOY = (earlierHour * SECONDS_IN_AN_HOUR) + (earlierMinute * 60) + earlierSecond;
        int laterDateSOY = (laterHour * SECONDS_IN_AN_HOUR) + (laterMinute * 60) + laterSecond;
        int earlierDateDOY = DayOfYear(earlierYear, earlierMonth, earlierDay);
        int laterDateDOY = DayOfYear(laterYear, laterMonth, laterDay);

        if (earlierYear == laterYear && earlierDateDOY == laterDateDOY)
        {
            return laterDateSOY - earlierDateSOY;
        }

        int seconds = 0;

        //remaining seconds until the end of the earlier day
        seconds += SECONDS_IN_A_DAY - earlierDateSOY;

        //full days between earlier and the later day
        int days = 0;

        if (earlierYear == laterYear)
        {
            days = (laterDateDOY - earlierDateDOY);
        }
        else
        {
            //remaining days until the end of (the year of the earlier date)
            days += IsLeap(earlierYear) ? 366 - earlierDateDOY : 365 - earlierDateDOY;

            //the days in (the years between the earlier and the later date)
            for (int year = earlierYear + 1; year < laterYear; year++)
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

    //returns the number of seconds between _datetime and _datetime_
	//_datetime1 and/or _datetime2 is not valid => -1
    //__datetime1.year() >= 1600 && _datetime2.year() >= 1600 ->
	unsigned long long IntervalOf(const DateTime& _datetime1, const DateTime& _datetime2)
	{
        if (!IsValidDateTime(_datetime1) || !IsValidDateTime(_datetime2)) return -1;

        return IntervalOf(
            _datetime1.year(),
            _datetime1.month(),
            _datetime1.day(),
            _datetime1.hour(),
            _datetime1.minute(),
            _datetime1.second(),
            _datetime1.timezone(),
            _datetime2.year(),
            _datetime2.month(),
            _datetime2.day(),
            _datetime2.hour(),
            _datetime2.minute(),
            _datetime2.second(),
            _datetime2.timezone());
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

	//_datetime.year() > 9999 => false
	bool IsValidDateTime(const DateTime& _datetime)
	{
		if (_datetime.year() < 1 || _datetime.year() > 9999) return false;

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
