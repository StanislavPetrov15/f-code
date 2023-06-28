namespace unicode
{
    using bit_operations::GetBits;
    using bit_operations::SetBits;

    //code unit of UTF-8
    using utf8 = unsigned char;

    //code unit of UTF-16
    using utf16 = unsigned short;

    //code unit of UTF-32
    using utf32 = unsigned int;

    //Unicode code point
    using CodePoint = unsigned int;

    const list<unsigned char> UTF8_BOM { 0b11101111, 0b10111011, 0b10111111 };

    const list<unsigned char> UTF16LE_BOM { 0b11111111, 0b11111110 };

    const list<unsigned char> UTF16BE_BOM { 0b11111110, 0b11111111 };

    const list<unsigned char> UTF32LE_BOM { 0b11111111, 0b11111110, 0b00000000, 0b00000000 };

    const list<unsigned char> UTF32BE_BOM { 0b00000000, 0b00000000, 0b11111110, 0b11111111 };

    const int UTF8_CODE_UNIT_LENGTH = 1; //in bytes

    const int UTF16_CODE_UNIT_LENGTH = 2; //in bytes

    const int UTF32_CODE_UNIT_LENGTH = 4; //in bytes

    const Range<unsigned short> HIGH_SURROGATES(55296, 56319);

    const Range<unsigned short> LOW_SURROGATES(56320, 57343);

    const int BMP_BEGIN = 0;

    const int BMP_END = 65535;

    const int SMP_BEGIN = 65536;

    const int SMP_END = 131071;

    const int SIP_BEGIN = 131072;

    const int SIP_END = 196607;

    const int SSP_BEGIN = 917504;

    const int SSP_END = 983039;

    //(Private Use Area) begin
    const int PUA1_BEGIN = 57344;

    //(Private Use Area) end
    const int PUA1_END = 63743;

    //(Supplementary Private Use Area-A) begin
    const int PUA2_BEGIN = 983040;

    //(Supplementary Private Use Area-A) end
    const int PUA2_END = 1048573;

    //(Supplementary Private Use Area-B) begin
    const int PUA3_BEGIN = 1048576;

    //(Supplementary Private Use Area-B) end
    const int PUA3_END = 1114109;

    const Range<int> ARABIC_DIGITS(48, 57);

    //determines if the code point is an arabic digit
    bool IsDigit(CodePoint _character)
    {
        return ARABIC_DIGITS.Contains(_character);
    }

    //determines if the code point is whitepsace character (characters with property WS/WSpace/White_Space = Yes)
    bool IsWhitespace(CodePoint _character)
    {
         return _character == 9 || _character == 10 || _character == 11 || _character == 12 || _character == 13 || _character == 32 ||
                _character == 133 || _character == 160 || _character == 5760 || (_character >= 8192 && _character <= 8202) ||
                _character == 8232 || _character == 8233 || _character == 8239 || _character == 8287 || _character == 12288;
    }

    bool IsHighSurrogate(utf16 _codeUnit)
    {
        return HIGH_SURROGATES.Contains(_codeUnit);
    }

    bool IsLowSurrogate(utf16 _codeUnit)
    {
        return LOW_SURROGATES.Contains(_codeUnit);
    }

    //determines if the code point is part of Basic Multilingual Plane (it doesn't include the surrogate range)
    bool IsBMP(CodePoint _codePoint)
    {
        return _codePoint < HIGH_SURROGATES.begin() || (_codePoint > LOW_SURROGATES.end() && _codePoint <= BMP_END);
    }

    //determines if the code point is part of Supplementary Multilingual Plane
    bool IsSMP(CodePoint _codePoint)
    {
        return _codePoint >= SMP_BEGIN && _codePoint <= SMP_END;
    }

    //determines if the code point is part of Supplementary Ideographic Plane
    bool IsSIP(CodePoint _codePoint)
    {
        return _codePoint >= SIP_BEGIN && _codePoint <= SIP_END;
    }

    //determines if the code point is part of Supplementary Special-purpose Plane
    bool IsSSP(CodePoint _codePoint)
    {
        return _codePoint >= SSP_BEGIN && _codePoint <= SSP_END;
    }

    //determines if the code point is part of Private Use Area
    bool IsPUA(CodePoint _codePoint)
    {
        return _codePoint >= PUA1_BEGIN && _codePoint <= PUA1_END;
    }

    //determines if the code point is part of (Supplementary Private Use Area-A)
    bool IsPUA2(CodePoint _codePoint)
    {
        return _codePoint >= PUA2_BEGIN && _codePoint <= PUA2_END;
    }

    //determines if the code point is part of (Supplementary Private Use Area-B)
    bool IsPUA3(CodePoint _codePoint)
    {
        return _codePoint >= PUA3_BEGIN && _codePoint <= PUA3_END;
    }

    //returns (high surrogate, low surrogate)
    //_codePoint is not a code point from BMP ->
    t2<utf16, utf16> GetSurrogatePair(CodePoint _codePoint)
    {
        unsigned int number = (_codePoint - 65536);
        utf16 highSurrogate = (number >> 10) + HIGH_SURROGATES.begin();
        utf16 lowSurrogate = ((number << 22) >> 22) + LOW_SURROGATES.begin();
        return t2<utf16, utf16>(highSurrogate, lowSurrogate);
    }

    //the parameters rerpesents UTF-8 character that is part of BMP ->
    utf16 ToUTF16(unsigned char _high, unsigned char _low)
    {
        SetBits(_high, 5, 7, false);
        SetBits(_low, 6, 7, false);
        return (_high << 6) | _low;
    }

    //the parameters represent UTF-8 character that is part of BMP ->
    utf16 ToUTF16(unsigned char _high, unsigned char _lowa, unsigned char _lowb)
    {
        SetBits(_high, 4, 7, false);
        SetBits(_lowa, 6, 7, false);
        SetBits(_lowb, 6, 7, false);
        return (_high << 12) | (_lowa << 6) | _lowb;
    }

    list<utf8> ToUTF8(CodePoint);

    //returns a single UTF-8 character
    //_codeUnit represent a BMP code point ->
    list<utf8> ToUTF8(utf16 _codeUnit)
    {
        return ToUTF8(static_cast<CodePoint>(_codeUnit));
    }

    CodePoint ToCodePoint(utf16, utf16);
    //returns a single UTF-8 character
    //the parameters represent a valid surrogate pair ->
    list<utf8> ToUTF8(utf16 _highSurrogate, utf16 _lowSurrogate)
    {
        return ToUTF8(ToCodePoint(_highSurrogate, _lowSurrogate));
    }

    //returns a single UTF-8 character
    //_codePoint represent a valid Unicode code point ->
    list<utf8> ToUTF8(CodePoint _codePoint)
    {
        //if the code point must be encoded by one byte
        if (_codePoint < 128)
        {
            return { static_cast<unsigned char>(_codePoint) };
        }
            //if the code point must be encoded by two bytes
        else if (_codePoint >= 128 && _codePoint <= 2047)
        {
            unsigned char high = 0b11000000 | GetBits(_codePoint, 6, 10);
            unsigned char low = 0b10000000 | GetBits(_codePoint, 0, 5);
            return { high, low };
        }
            //if the code point must be encoded by three byte
        else if (_codePoint >= 2048 && _codePoint <= 65535)
        {
            unsigned char high = 0b11100000 | GetBits(_codePoint, 12, 15);
            unsigned char lowa = 0b10000000 | GetBits(_codePoint, 6, 11);
            unsigned char lowb = 0b10000000 | GetBits(_codePoint, 0, 5);
            return { high, lowa, lowb };
        }
            //if the code point must be encoded by four byte
        else if (_codePoint >= 65536)
        {
            unsigned char high = 0b11110000 | GetBits(_codePoint, 18, 20);
            unsigned char lowa = 0b10000000 | GetBits(_codePoint, 12, 17);
            unsigned char lowb = 0b10000000 | GetBits(_codePoint, 6, 11);
            unsigned char lowc = 0b10000000 | GetBits(_codePoint, 0, 5);
            return { high, lowa, lowb, lowc };
        }
    }

    //the parameters represent UTF-8 character that is part of BMP ->
    utf32 ToUTF32(unsigned char _high, unsigned char _lowa)
    {
        SetBits(_high, 5, 7, false);
        SetBits(_lowa, 6, 7, false);
        return (_high << 6) | _lowa;
    }

    //the parameters represent UTF-8 character that is part of BMP ->
    utf32 ToUTF32(unsigned char _high, unsigned char _lowa, unsigned char _lowb)
    {
        SetBits(_high, 4, 7, false);
        SetBits(_lowa, 6, 7, false);
        SetBits(_lowb, 6, 7, false);
        return (_high << 12) | (_lowa << 6) | _lowb;
    }

    //the parameters represent UTF-8 character that is not part of BMP ->
    utf32 ToUTF32(unsigned char _high, unsigned char _lowa, unsigned char _lowb, unsigned char _lowc)
    {
        SetBits(_high, 3, 7, false);
        SetBits(_lowa, 6, 7, false);
        SetBits(_lowb, 6, 7, false);
        SetBits(_lowc, 6, 7, false);
        return (_high << 18) | (_lowa << 12) | (_lowb << 6) | _lowc;
    }

    //the parameters represent a valid surrogate pair ->
    utf32 ToUTF32(utf16 _highSurrogate, utf16 _lowSurrogate)
    {
        utf16 highSurrogateOffset = _highSurrogate - HIGH_SURROGATES.begin();
        utf16 lowSurrogateOffset = _lowSurrogate - LOW_SURROGATES.begin();
        return ((highSurrogateOffset << 10) | lowSurrogateOffset) + 65536;
    }

    //the parameters represent UTF-8 character that is part of BMP ->
    CodePoint ToCodePoint(unsigned char _high, unsigned char _lowa)
    {
        return ToUTF32(_high, _lowa);
    }

    //the parameters represent UTF-8 character that is not part of BMP ->
    CodePoint ToCodePoint(unsigned char _high, unsigned char _lowa, unsigned char _lowb)
    {
        return ToUTF32(_high, _lowa, _lowb);
    }

    //the parameters represent a valid UTF-8 sequence ->
    utf32 ToCodePoint(unsigned char _high, unsigned char _lowa, unsigned char _lowb, unsigned char _lowc)
    {
        return ToUTF32(_high, _lowa, _lowb, _lowc);
    }

    //(SYNONYM:ToUTF32)
    //the parameters represent a valid surrogate pair ->
    utf32 ToCodePoint(utf16 _highSurrogate, utf16 _lowSurrogate)
    {
        return ToUTF32(_highSurrogate, _lowSurrogate);
    }
}
