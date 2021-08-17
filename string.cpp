using bit_operations::GetBits;
using bit_operations::SetBits;
using bit_operations::BitOrder;
using byte_operations::Endianity;
using byte_operations::LE;
using byte_operations::BE;
using byte_operations::_16;
using byte_operations::_32;
using byte_operations::ByteOf;
using byte_operations::BytesOf;
using unicode::utf8;
using unicode::utf16;
using unicode::utf32;
using unicode::CodePoint;
using unicode::UTF8_BOM;
using unicode::UTF16LE_BOM;
using unicode::UTF16BE_BOM;
using unicode::UTF32LE_BOM;
using unicode::UTF32BE_BOM;
using unicode::UTF8_CODE_UNIT_LENGTH;
using unicode::UTF16_CODE_UNIT_LENGTH;
using unicode::UTF32_CODE_UNIT_LENGTH;
using unicode::IsDigit;
using unicode::IsBMP;
using unicode::IsHighSurrogate;
using unicode::ToUTF8;
using unicode::ToUTF16;
using unicode::ToUTF32;
using unicode::GetSurrogatePair;
using unicode::ToCodePoint;

//constructor activation atoms
enum ASCII { ascii };
enum U8 { u8 };
enum U16 { u16 };
enum U32 { u32 };

//activation atoms for string::ToInteger()
enum DECIMAL_ { DECIMAL_A };
enum BINARY_ { BINARY_A };
enum HEX_ { HEX_A };

//encoding format for (input and output string data) 
enum Encoding { ASCII_, UTF8, UTF16LE, UTF16BE, UTF32LE, UTF32BE };

const int INVALID_INTEGER = INT_MIN;

//maximum length in (bytes/code units/characters)
const int MAX_LENGTH = 1073741823;

//marker specifying (the length of a string in bytes)
const unsigned int b = 0; //[31] = 0, [30] = 0
const unsigned int bytes = b; //pseudonym of &b

//marker specifying (the length of a string in code units)
const unsigned int u = 1073741824; //[31] = 0, [30] = 1
const unsigned int units = u; //pseudonym of &u

//marker specifying (the length of a string in characters)
const unsigned int c = 2147483648; //[31] = 1, [30] = 0
const unsigned int characters = c; //pseudonym of &c

//the default endianity value of the arguments in constructors of t:string; it is not possible to be a static field of t:string
Endianity DefaultEndianity = LE;

//the default encoding format of (the values passed to the constructors of t:string that are not marked with BOM)
Encoding DefaultInputEncoding = ASCII_;

//the default encoding format of the stored value of a string
Encoding DefaultStorageEncoding = UTF8;

/* this type belongs to the 'Sequence' type category; t:string and t:list share many equivalent functions, but t:string do not implement 
   First(), Generate(), Intersects(), IntersectionOf(), IsHeterogenous(), IsHomogenous(), Max(), Min(), fm:Sort() and Swap(*, *), while at the same time
   implements a set of extension functions */
//the input string (passed to the constructors) is in ASCII, UTF-8, UTF-16LE, UTF-16BE, UTF-32LE or UTF-32BE format
//the input string (may contain a terminating character) or (it's length may be explicitly specified)
//the output string (the string value after the construction process has ended) is stored as (byte sequence) representing (a sequence of UTF-8, UTF-16LE or UTF-32LE code units)
//(ASCII|UTF-8|UTF-16LE|UTF-16BE|UTF-32LE|UTF-32BE:input-string) -> (UTF-8|UTF-16LE|UTF-32LE:output-string)
//<T> is the type of the output string
//(!) if certain input string is character-terminated, then the terminating character must be U+0000
//(!) the public functions of this type operate on characters(code points), not on bytes or code units
//(!) elements() returns a pointer to byte array containing (the characters represented as a sequence of (UTF-8, UTF-16LE, UTF-16BE, UTF-32LE or UTF-32BE) code units)
//(!) the constructors accept (byte arrays) or (arrays of UTF-16/UTF-32 code units)
/*(!) (the constructors accepting byte arrays) may accept the array length (in bytes), (in code units) or (in characters); in order to pass
        the length in bytes one have to use <N> or <N>|b, to pass the length in code units <N>|u, and to pass the length in characters <N>|c; 
		the maximum value of <N> is 1073741823 (constant MAX_LENGTH)
        (ЕXAMPLE) 162 (162 bytes)
        (ЕXAMPLE) 495|b (495 bytes)
        (EXAMPLE) 829|u (829 code units)
        (ЕXAMPLE) 327|c (327 characters)
        (ЕXAMPLE) [utf16]:array -> string(array, 94|c) (construction of a string accepting an array of UTF-16 code units with length 94 characters) */
/*(!) (MAY-NEED-BETTER-EXPLANATION) 
	    when an incorrect length value is passed to a (constructor accepting UTF-16 or UTF-32 arrays) it is possible for a discrepancy to occur between
        the number of the specified number of bytes/code-units/characters and the number of the processed bytes/code-units/characters
        (EXAMPLE) string(const utf16*...) receive a length of 4 bytes; the first code unit is BMP character, and the second and third 
            code units are respectively high and low surrogate of a non-BMP character; in this case 6 bytes (not 4) will be processed, because in 
			constructors there is an iteration over characters (the first character is represented by the first two bytes, and the second
			by the next four bytes) */
/*(!) the constructors must not receive an empty string or a string without terminating character(for ASCII and UTF-8) or terminating sequence
	    (for UTF-16 and UTF-32); accessing of (an element outside the range of string) is 'undefined behavior' */
//(!) the size(accessed by size()) of a segment is equal to the size of the list that the segment refers to
struct string
{
    protected:

    int ByteCount = 0; //the size of (the sequence representing the characters) in bytes
    int Size = 0; //the size of &Elements (in bytes)
    int CharacterCount = 0; //number of characters
    int Position = 0; //iteration position 
    unsigned char* Elements = nullptr;
    SpatialKind SpatialKind = SpatialKind::COMPLETE;
    Encoding StorageEncoding = DefaultStorageEncoding;

    bool InRange(int _index) const
    {
        return _index >= 0 || _index <= CharacterCount - 1;
    }

    bool InRange(int _begin, int _end) const
    {
        if (_begin < 0 || _end > CharacterCount - 1)
        {
            return false;
        }
        else if (_begin > _end)
        {
            return false;
        }

        return true;
    }

    //(INTERNAL)
    //_characterIndex < 0 => (-1, -1)
    //_characterIndex is larger than the number of characters | the binary size of the string is incorrect => (-2, -2)
    Range<int> byteRangeOf(int _characterIndex) const
    {
        if (_characterIndex < 0)
        {
            return Range(- 1, - 1);
        }

        for (int i = 0, n = -1; i < ByteCount; )
        {
            //if the storage format is UTF-8 and the character is encoded by one byte
            if (StorageEncoding == UTF8 && (Elements[i] >> 7) == 0b0)
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i);
                }

                i++;
            }
			//if the storage format is UTF-8 and the character is encoded by two bytes
            else if (StorageEncoding == UTF8 && (Elements[i] >> 5) == 0b110)
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i + 1);
                }
                else
                {
                    i += 2;
                }
            }
			//if the storage format is UTF-8 and the character is encoded by three bytes
            else if (StorageEncoding == UTF8 && (Elements[i] >> 4) == 0b1110)
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i + 2);
                }
                else
                {
                    i += 3;
                }
            }
			//if the storage format is UTF-8 and the character is encoded by four bytes
            else if (StorageEncoding == UTF8 && (Elements[i] >> 3) == 0b11110)
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i + 3);
                }
                else
                {
                    i += 4;
                }
            }
            //if the storage format is UTF-16LE and the character is part of BMP
            else if (StorageEncoding == UTF16LE && IsBMP(_16(Elements[i], Elements[i + 1], LE)))
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i + 1);
                }
                else
                {
                    i += UTF16_CODE_UNIT_LENGTH;
                }
            }
			//if the storage format is UTF-16BE and the character is part of BMP
            else if (StorageEncoding == UTF16BE && IsBMP(_16(Elements[i], Elements[i + 1], BE)))
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i + 1);
                }
                else
                {
                    i += UTF16_CODE_UNIT_LENGTH;
                }
            }
            //(STATE) the character is not part of BMP
			//if the storage format is UTF-16LE and the character is not part of BMP
            else if (StorageEncoding == UTF16LE)
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i + 3);
                }
                else
                {
                    i += UTF16_CODE_UNIT_LENGTH * 2;
                }
            }
			//if the storage format is UTF-16BE and the character is not part of BMP
            else if (StorageEncoding == UTF16BE)
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i + 3);
                }
                else
                {
                    i += UTF16_CODE_UNIT_LENGTH * 2;
                }
            }
            //(END-STATE)
            //if the storage format is UTF-32LE
            else if (StorageEncoding == UTF32LE)
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i + 3);
                }
                else
                {
                    i += UTF32_CODE_UNIT_LENGTH;
                }
            }
            //if the storage format is UTF-32BE
            else if (StorageEncoding == UTF32BE)
            {
                if (++ n == _characterIndex)
                {
                    return Range(i, i + 3);
                }
                else
                {
                    i += UTF32_CODE_UNIT_LENGTH;
                }
            }
        }

        return Range(- 2, - 2);
    }

    //(INTERNAL)
    list<unsigned char> bytesOf(CodePoint _codePoint)
    {
        //if the storage format is UTF8
        if (StorageEncoding == UTF8)
        {
            return ToUTF8(_codePoint).Generate<unsigned char>();
        }
        //if the character is part of BMP and the storage format is UTF-16LE
        else if (IsBMP(_codePoint) && StorageEncoding == UTF16LE)
        {
            return BytesOf(static_cast<unsigned short>(_codePoint)).Generate<unsigned char>();
        }
		//if the character is part of BMP and the storage format is UTF-16BE
        else if (IsBMP(_codePoint) && StorageEncoding == UTF16BE)
        {
            return BytesOf(static_cast<unsigned short>(_codePoint)).Reverse().Generate<unsigned char>();
        }
        //(STATE) the character is not part of BMP
        //if the character is not part of BMP and the storage format is UTF-16LE
        else if (StorageEncoding == UTF16LE)
        {
            t2<utf16, utf16> surrogatePair = GetSurrogatePair(_codePoint);
            return BytesOf(surrogatePair.e1()).Generate<unsigned char>() + BytesOf(surrogatePair.e2()).Generate<unsigned char>();
        }
        //if the character is not part of BMP and the storage format is UTF-16BE
        else if (StorageEncoding == UTF16BE)
        {
            t2<utf16, utf16> surrogatePair = GetSurrogatePair(_codePoint);
            return BytesOf(surrogatePair.e1()).Reverse().Generate<unsigned char>() + BytesOf(surrogatePair.e2()).Reverse().Generate<unsigned char>();
        }
        //(END-STATE)
        //if the storage format is UTF32LE
        else if (StorageEncoding == UTF32LE)
        {
            return BytesOf(_codePoint).Generate<unsigned char>();
        }
        //if the storage format is UTF32BE
        else if (StorageEncoding == UTF32BE)
        {
            return BytesOf(_codePoint).Reverse().Generate<unsigned char>();
        }
    }

    public:

    /* this variable plays a role for the speed of string generation; the larger the final size of the string is (i.e. the size after 
	   ending of the generation process), the larger the value of this variable must be; it needs to be increased by 1 every 2kb;
	   if the string is very large and it's final size is known before the construction, then it is better to set the binary size before
	   the start of the generation process - in such a way there wouldn't be need for (potentialy multiple) resize operations */
    int Extensor = 50; //in bytes 

    TraversalMode TraversalMode = TraversalMode::BOUNDED;

    /* when an instance of this type is about to be destructed the elements (are freed automatically and immediately
      (when IMMEDIATE is used)) or (are stored for future use and are freed manually in a specific future 
	   moment (when FUTURE is used)) */
    ReleaseMode ReleaseMode = ReleaseMode::IMMEDIATE;

    ///CONSTRUCTORS:

    string() = default;

    explicit string(int _size)
    {
        extend(_size);
    }

    //_array is an ASCII string with an available terminating character ->
    string(const char* _array)
    {
        this->string::string(_array, ascii, DefaultStorageEncoding);
    }

    //_array is an ASCII|UTF-8|UTF-16|UTF-32 string with an available terminating character ->
    string(const unsigned char* _array)
    {
        /* (!) calling the appropriate constructor directly through string(...) creates a local copy (i.e. the state of &this is not updated);
                for this reason the 'this->string::string(...)' construct has to be used */

        if (DefaultInputEncoding == ASCII_)
        {
            this->string::string(reinterpret_cast<const char*>(_array), ascii, DefaultStorageEncoding);
        }
        else if (DefaultInputEncoding == UTF8)
        {
            this->string::string(_array, u8, DefaultStorageEncoding);
        }
        else if (DefaultInputEncoding == UTF16LE)
        {
            this->string::string(_array, u16, LE, DefaultStorageEncoding);
        }
        else if (DefaultInputEncoding == UTF16BE)
        {
            this->string::string(_array, u16, BE, DefaultStorageEncoding);
        }
        else if (DefaultInputEncoding == UTF32LE)
        {
            this->string::string(_array, u32, LE, DefaultStorageEncoding);
        }
        else if (DefaultInputEncoding == UTF32BE)
        {
            this->string::string(_array, u32, BE, DefaultStorageEncoding);
        }
    }

    //_array is an ASCII string with an available terminating character ->
    string(const char* _array, ASCII, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        while (true)
        {
            auto sd = _array[i];

            if (_array[i] == 0)
            {
                break;
            }
            else
            {
                if (_storageEncoding == UTF8)
                {
                    Append(_array[i]);
                }
                else if (_storageEncoding == UTF16LE)
                {
                    utf16 codeUnit = _array[i];
                    Append(BytesOf(codeUnit).Generate<unsigned char>());
                }
                else if (_storageEncoding == UTF16BE)
                {
                    utf16 codeUnit = _array[i];
                    Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                }
                else if (_storageEncoding == UTF32LE)
                {
                    utf32 codeUnit = _array[i];
                    Append(BytesOf(codeUnit).Generate<unsigned char>());
                }
                else if (_storageEncoding == UTF32BE)
                {
                    utf32 codeUnit = _array[i];
                    Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                }
            }

            i++;
        }
    }

    //_array is an ASCII string with an available terminating character ->
    string(const char* _array, ASCII) : string(_array, ascii, DefaultStorageEncoding) {}

    //_length specifies the length of _array
    //_array is an ASCII string ->
    string(const char* _array, ASCII, unsigned int _length, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        //in case that _length is <N>|c or <N>|u
        SetBits(_length, false, 30, 31);

        for (int i = 0; i < _length; i++)
        {
            if (_storageEncoding == UTF8)
            {
                Append(_array[i]);
            }
            else if (_storageEncoding == UTF16LE)
            {
                utf16 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Generate<unsigned char>());
            }
            else if (_storageEncoding == UTF16BE)
            {
                utf16 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
            }
            else if (_storageEncoding == UTF32LE)
            {
                utf32 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Generate<unsigned char>());
            }
            else if (_storageEncoding == UTF32BE)
            {
                utf32 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
            }
        }
    }

    //_length specifies the length of _array
    //_array is an ASCII string ->
    string(const char* _array, ASCII, unsigned int _length) : string(_array, ascii, _length, DefaultStorageEncoding) {}

    //_array is a UTF-8 string with an available terminating character ->
    string(const unsigned char* _array, U8, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        if (_array[0] == UTF8_BOM[0] && _array[1] == UTF8_BOM[1] && _array[2] == UTF8_BOM[2])
        {
            i = 3;
        }

        while (true)
        {
            if (_array[i] == 0) break;

            //if the character is encoded by one byte and the storage format is UTF-8
            if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF8)
            {
                Append(_array[i]);
                i++;
            }
			//if the character is encoded by one byte and the storage format is UTF-16LE
            else if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF16LE)
            {
                utf16 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i++;
            }
			//if the character is encoded by one byte and the storage format is UTF-16BE
            else if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF16BE)
            {
                utf16 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i++;
            }
                //if the character is encoded by one byte and the storage format is UTF-32LE
            else if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF32LE)
            {
                utf32 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i++;
            }
                //if the character is encoded by one byte and the storage format is UTF-32BE
            else if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF32BE)
            {
                utf32 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i++;
            }
			//if the character is encoded by two bytes and the storage format is UTF-8
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF8)
            {
                Append(list<unsigned char> { _array[i], _array[i + 1] });
                i += 2;
            }
			//if the character is encoded by two bytes and the storage format is UTF-16LE
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF16LE)
            {
                utf16 codeUnit = ToUTF16(_array[i], _array[i + 1]);
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i += 2;
            }
			//if the character is encoded by two bytes and the storage format is UTF-16BE
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF16BE)
            {
                utf16 codeUnit = ToUTF16(_array[i], _array[i + 1]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 2;
            }
			//if the character is encoded by two bytes and the storage format is UTF-32LE
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF32LE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1]);
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i += 2;
            }
			//if the character is encoded by two bytes and the storage format is UTF-32BE
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF32BE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 2;
            }
			//if the character is encoded by three bytes and the storage format is UTF-8
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF8)
            {
                Append(list<unsigned char> { _array[i], _array[i + 1], _array[i + 2] });
                i += 3;
            }
			//if the character is encoded by three bytes and the storage format is UTF-16LE
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF16LE)
            {
                utf16 codeUnit = ToUTF16(_array[i], _array[i + 1], _array[i + 2]);
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i += 3;
            }
			//if the character is encoded by three bytes and the storage format is UTF-16BE
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF16BE)
            {
                utf16 codeUnit = ToUTF16(_array[i], _array[i + 1], _array[i + 2]);;
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 3;
            }
			//if the character is encoded by three bytes and the storage format is UTF-32LE
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF32LE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1], _array[i + 2]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 3;
            }
			//if the character is encoded by three bytes and the storage format is UTF-32BE
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF32BE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1], _array[i + 2]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 3;
            }
			//if the character is encoded by four bytes and the storage format is UTF-8
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF8)
            {
                Append(list<unsigned char> { _array[i], _array[i + 1], _array[i + 2], _array[i + 3] });
                i += 4;
            }
			//if the character is encoded by four bytes and the storage format is UTF-16LE
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF16LE)
            {
                CodePoint codePoint = ToCodePoint(_array[i], _array[i + 1], _array[i + 2], _array[i + 3]);
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codePoint);
                utf16 highSurrogate = surrogatePair.e1();
                utf16 lowSurrogate = surrogatePair.e2();
                Append(BytesOf(highSurrogate).Generate<unsigned char>() + BytesOf(lowSurrogate).Generate<unsigned char>());
                i += 4;
            }
			//if the character is encoded by four bytes and the storage format is UTF-16BE
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF16BE)
            {
                CodePoint codePoint = ToCodePoint(_array[i], _array[i + 1], _array[i + 2], _array[i + 3]);
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codePoint);
                utf16 highSurrogate = surrogatePair.e1();
                utf16 lowSurrogate = surrogatePair.e2();
                Append(BytesOf(highSurrogate).Reverse().Generate<unsigned char>() + BytesOf(lowSurrogate).Reverse().Generate<unsigned char>());
                i += 4;
            }
			//if the character is encoded by four bytes and the storage format is UTF-32LE
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF32LE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1], _array[i + 2], _array[i + 3]);
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i += 4;
            }
			//if the character is encoded by four bytes and the storage format is UTF-32BE
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF32BE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1], _array[i + 2], _array[i + 3]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 4;
            }
        }
    }

    //_array is a UTF-8 string with an available terminating character ->
    string(const unsigned char*_array, U8) : string(_array, u8, DefaultStorageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-8 string ->
    string(const unsigned char* _array, U8, unsigned int _length, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        if (_array[0] == UTF8_BOM[0] && _array[1] == UTF8_BOM[1] && _array[2] == UTF8_BOM[2])
        {
            i = 3;
        }

        int lengthMarker = GetBits(_length, 30, 31);
        //-> clearing the marking bits
        SetBits(_length, false, 30, 31);

        while (true)
        {
            //if a terminating character is reached
            if (_array[i] == 0) break;
			//if the length is specified in bytes and the end of the string is reached
            else if (lengthMarker == 0 && i == _length) break;
			//if the length is specified in code units and the end of the string is reached
            else if (lengthMarker == 1 && i == _length) break;
			//if the length is specified in characters and the end of the string is reached
            else if (lengthMarker == 2 && CharacterCount == _length) break;

            //if the character is encoded by one byte and the storage format is UTF-8
            if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF8)
            {
                Append(_array[i]);
                i++;
            }
                //if the character is encoded by one byte and the storage format is UTF-16LE
            else if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF16LE)
            {
                utf16 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i++;
            }
                //if the character is encoded by one byte and the storage format is UTF-16BE
            else if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF16BE)
            {
                utf16 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i++;
            }
                //if the character is encoded by one byte and the storage format is UTF-32LE
            else if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF32LE)
            {
                utf32 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i++;
            }
                //if the character is encoded by one byte and the storage format is UTF-32BE
            else if ((_array[i] >> 7) == 0b0 && _storageEncoding == UTF32BE)
            {
                utf32 codeUnit = _array[i];
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i++;
            }
                //if the character is encoded by two bytes and the storage format is UTF-8
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF8)
            {
                Append(list<unsigned char> { _array[i], _array[i + 1] });
                i += 2;
            }
                //if the character is encoded by two bytes and the storage format is UTF-16LE
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF16LE)
            {
                utf16 codeUnit = ToUTF16(_array[i], _array[i + 1]);
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i += 2;
            }
                //if the character is encoded by two bytes and the storage format is UTF-16BE
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF16BE)
            {
                utf16 codeUnit = ToUTF16(_array[i], _array[i + 1]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 2;
            }
                //if the character is encoded by two bytes and the storage format is UTF-32LE
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF32LE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1]);
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i += 2;
            }
                //if the character is encoded by two bytes and the storage format is UTF-32BE
            else if ((_array[i] >> 5) == 0b110 && _storageEncoding == UTF32BE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 2;
            }
                //if the character is encoded by three bytes and the storage format is UTF-8
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF8)
            {
                Append(list<unsigned char> { _array[i], _array[i + 1], _array[i + 2] });
                i += 3;
            }
                //if the character is encoded by three bytes and the storage format is UTF-16LE
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF16LE)
            {
                utf16 codeUnit = ToUTF16(_array[i], _array[i + 1], _array[i + 2]);
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i += 3;
            }
                //if the character is encoded by three bytes and the storage format is UTF-16BE
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF16BE)
            {
                utf16 codeUnit = ToUTF16(_array[i], _array[i + 1], _array[i + 2]);;
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 3;
            }
                //if the character is encoded by three bytes and the storage format is UTF-32LE
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF32LE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1], _array[i + 2]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 3;
            }
                //if the character is encoded by three bytes and the storage format is UTF-32BE
            else if ((_array[i] >> 4) == 0b1110 && _storageEncoding == UTF32BE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1], _array[i + 2]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 3;
            }
                //if the character is encoded by four bytes and the storage format is UTF-8
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF8)
            {
                Append(list<unsigned char> { _array[i], _array[i + 1], _array[i + 2], _array[i + 3] });
                i += 4;
            }
                //if the character is encoded by four bytes and the storage format is UTF-16LE
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF16LE)
            {
                CodePoint codePoint = ToCodePoint(_array[i], _array[i + 1], _array[i + 2], _array[i + 3]);
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codePoint);
                utf16 highSurrogate = surrogatePair.e1();
                utf16 lowSurrogate = surrogatePair.e2();
                Append(BytesOf(highSurrogate).Generate<unsigned char>() + BytesOf(lowSurrogate).Generate<unsigned char>());
                i += 4;
            }
                //if the character is encoded by four bytes and the storage format is UTF-16BE
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF16BE)
            {
                CodePoint codePoint = ToCodePoint(_array[i], _array[i + 1], _array[i + 2], _array[i + 3]);
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codePoint);
                utf16 highSurrogate = surrogatePair.e1();
                utf16 lowSurrogate = surrogatePair.e2();
                Append(BytesOf(highSurrogate).Reverse().Generate<unsigned char>() + BytesOf(lowSurrogate).Reverse().Generate<unsigned char>());
                i += 4;
            }
                //if the character is encoded by four bytes and the storage format is UTF-32LE
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF32LE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1], _array[i + 2], _array[i + 3]);
                Append(BytesOf(codeUnit).Generate<unsigned char>());
                i += 4;
            }
                //if the character is encoded by four bytes and the storage format is UTF-32BE
            else if ((_array[i] >> 3) == 0b11110 && _storageEncoding == UTF32BE)
            {
                utf32 codeUnit = ToUTF32(_array[i], _array[i + 1], _array[i + 2], _array[i + 3]);
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                i += 4;
            }
        }
    }

    //_length specifies the length of _array
    //_array is a UTF-8 string ->
    string(const unsigned char*_array, U8, unsigned int _length) : string(_array, u8, _length, DefaultStorageEncoding) {}

    //_array is a UTF-16 string with an available terminating character ->
    string(const unsigned char*_array, U16, Endianity _endianity, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        if (_array[0] == UTF16LE_BOM[0] && _array[1] == UTF16LE_BOM[1])
        {
            _endianity = LE;
            i = UTF16_CODE_UNIT_LENGTH;
        }
        else if (_array[0] == UTF16BE_BOM[0] && _array[1] == UTF16BE_BOM[1])
        {
            _endianity = BE;
            i = UTF16_CODE_UNIT_LENGTH;
        }

        while (true)
        {
            utf16 codeUnit = _16(_array[i], _array[i + 1], _endianity);

            if (codeUnit == 0) break;

            //if codeUnit is a high surrogate
            if (IsHighSurrogate(codeUnit))
            {
                utf16 highSurrogate = codeUnit;
                utf16 lowSurrogate = _16(_array[i + 2], _array[i + 3], _endianity);

                //if the storage format is UTF-8
                if (_storageEncoding == UTF8)
                {
                    Append(ToUTF8(highSurrogate, lowSurrogate).Generate<unsigned char>());
                }
                //if the storage format is UTF-16LE
                else if (_storageEncoding == UTF16LE)
                {
                    Append(BytesOf(highSurrogate).Generate<unsigned char>() + BytesOf(lowSurrogate).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16BE
                else if (_storageEncoding == UTF16BE)
                {
                    Append(BytesOf(highSurrogate).Reverse().Generate<unsigned char>() +
                    BytesOf(lowSurrogate).Reverse().Generate<unsigned char>());
                }
                    //if the storage format is UTF-32LE
                else if (_storageEncoding == UTF32LE)
                {
                    Append(BytesOf(ToUTF32(highSurrogate, lowSurrogate)).Generate<unsigned char>());
                }
                    //if the storage format is UTF-32BE
                else if (_storageEncoding == UTF32BE)
                {
                    Append(BytesOf(ToUTF32(highSurrogate, lowSurrogate)).Reverse().Generate<unsigned char>());
                }

                i += UTF16_CODE_UNIT_LENGTH * 2;
            }
                //if codeUnit is a code point of BMP
            else
            {
                //if the storage format is UTF-8
                if (_storageEncoding == UTF8)
                {
                    Append(ToUTF8(codeUnit).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16LE
                else if (_storageEncoding == UTF16LE)
                {
                    Append(BytesOf(codeUnit).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16BE
                else if (_storageEncoding == UTF16BE)
                {
                    Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                }
                    //if the storage format is UTF-32LE
                else if (_storageEncoding == UTF32LE)
                {
                    Append(BytesOf(static_cast<unsigned int>(codeUnit)).Generate<unsigned char>());
                }
                    //if the storage format is UTF-32BE
                else if (_storageEncoding == UTF32BE)
                {
                    Append(BytesOf(static_cast<unsigned int>(codeUnit)).Reverse().Generate<unsigned char>());
                }

                i += UTF16_CODE_UNIT_LENGTH;
            }
        }
    }

    //_array is a UTF-16 string with an available terminating character ->
    string(const unsigned char* _array, U16, Endianity _endianity) : string(_array, u16, _endianity, DefaultStorageEncoding) {}

    //_array is a UTF-16 string with an available terminating character ->
    string(const unsigned char* _array, U16, Encoding _storageEncoding) : string(_array, u16, DefaultEndianity,
    _storageEncoding) {}

    //_array is a UTF-16 string with an available terminating character ->
    string(const unsigned char* _array, U16) : string(_array, u16, DefaultEndianity, DefaultStorageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-16 string ->
    string(const unsigned char* _array, U16, Endianity _endianity, unsigned int _length, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        if (_array[0] == UTF16LE_BOM[0] && _array[1] == UTF16LE_BOM[1])
        {
            _endianity = LE;
            i = UTF16_CODE_UNIT_LENGTH;
        }
        else if (_array[0] == UTF16BE_BOM[0] && _array[1] == UTF16BE_BOM[1])
        {
            _endianity = BE;
            i = UTF16_CODE_UNIT_LENGTH;
        }

        int lengthMarker = GetBits(_length, 30, 31);
        //-> clearing the marking bits
        SetBits(_length, false, 30, 31);

        while (true)
        {
            //if a terminating character is reached
            if (_array[i] == 0) break;
            //if the length is specified in bytes and the end of the string is reached
            else if (lengthMarker == 0 && i >= _length) break;
            //if the length is specified in code units and the end of the string is reached
            else if (lengthMarker == 1 && (i / UTF16_CODE_UNIT_LENGTH) == _length) break;
			//if the length is specified in characters and the end of the string is reached
            else if (lengthMarker == 2 && CharacterCount == _length) break;

            utf16 codeUnit = _16(_array[i], _array[i + 1], _endianity);

            //if codeUnit is a high surrogate
            if (IsHighSurrogate(codeUnit))
            {
                utf16 highSurrogate = codeUnit;
                utf16 lowSurrogate = _16(_array[i + 2], _array[i + 3], _endianity);

                //if the storage format is UTF-8
                if (_storageEncoding == UTF8)
                {
                    Append(ToUTF8(highSurrogate, lowSurrogate).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16LE
                else if (_storageEncoding == UTF16LE)
                {
                    Append(BytesOf(highSurrogate).Generate<unsigned char>() + BytesOf(lowSurrogate).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16BE
                else if (_storageEncoding == UTF16BE)
                {
                    Append(BytesOf(highSurrogate).Reverse().Generate<unsigned char>() +
                    BytesOf(lowSurrogate).Reverse().Generate<unsigned char>());
                }
                    //if the storage format is UTF-32LE
                else if (_storageEncoding == UTF32LE)
                {
                    Append(BytesOf(ToUTF32(highSurrogate, lowSurrogate)).Generate<unsigned char>());
                }
                    //if the storage format is UTF-32BE
                else if (_storageEncoding == UTF32BE)
                {
                    Append(BytesOf(ToUTF32(highSurrogate, lowSurrogate)).Reverse().Generate<unsigned char>());
                }

                i += UTF16_CODE_UNIT_LENGTH * 2;
            }
                //if codeUnit is a code point of BMP
            else
            {
                //if the storage format is UTF-8
                if (_storageEncoding == UTF8)
                {
                    Append(ToUTF8(codeUnit).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16LE
                else if (_storageEncoding == UTF16LE)
                {
                    Append(BytesOf(codeUnit).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16BE
                else if (_storageEncoding == UTF16BE)
                {
                    Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                }
                    //if the storage format is UTF-32LE
                else if (_storageEncoding == UTF32LE)
                {
                    Append(BytesOf(static_cast<unsigned int>(codeUnit)).Generate<unsigned char>());
                }
                    //if the storage format is UTF-32BE
                else if (_storageEncoding == UTF32BE)
                {
                    Append(BytesOf(static_cast<unsigned int>(codeUnit)).Reverse().Generate<unsigned char>());
                }

                i += UTF16_CODE_UNIT_LENGTH;
            }
        }
    }

    //_length specifies the length of _array
    //_array is a UTF-16 string ->
    string(const unsigned char*_array, U16, Endianity _endianity, unsigned int _length) : string(_array, u16, _endianity, _length,
    DefaultStorageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-16 string ->
    string(const unsigned char*_array, U16, unsigned int _length, Encoding _storageEncoding) : string(_array, u16, DefaultEndianity,
    _length, _storageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-16 string ->
    string(const unsigned char*_array, U16, unsigned int _length) : string(_array, u16, DefaultEndianity, _length,
    DefaultStorageEncoding) {}

    //_array is a UTF-32 string with an available terminating character ->
    string(const unsigned char*_array, U32, Endianity _endianity, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        if (_array[0] == UTF32LE_BOM[0] && _array[1] == UTF32LE_BOM[1] && _array[2] == UTF32LE_BOM[2] &&
        _array[3] == UTF32LE_BOM[3])
        {
            _endianity = LE;
            i = UTF32_CODE_UNIT_LENGTH;
        }
        else if (_array[0] == UTF32BE_BOM[0] && _array[1] == UTF32BE_BOM[1] && _array[2] == UTF32BE_BOM[2] &&
        _array[3] == UTF32BE_BOM[3])
        {
            _endianity = BE;
            i = UTF32_CODE_UNIT_LENGTH;
        }

        while (true)
        {
            utf32 codeUnit = _32(_array[i], _array[i + 1], _array[i + 2], _array[i + 3], _endianity);

            if (codeUnit == 0) break;

            //if the storage format is UTF-8
            if (_storageEncoding == UTF8)
            {
                Append(ToUTF8(codeUnit).Generate<unsigned char>());
            }
                //if the character is part of BMP and the storage format is UTF-16LE
            else if (IsBMP(codeUnit) && _storageEncoding == UTF16LE)
            {
                Append(BytesOf(static_cast<unsigned short>(codeUnit)).Generate<unsigned char>());
            }
                //if the character is part of BMP and the storage format is UTF-16BE
            else if (IsBMP(codeUnit) && _storageEncoding == UTF16BE)
            {
                Append(BytesOf(static_cast<unsigned short>(codeUnit)).Reverse().Generate<unsigned char>());
            }
                //(STATE) the character is not part of BMP
                //if the character is not part of BMP and the storage format is UTF-16LE
            else if (_storageEncoding == UTF16LE)
            {
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codeUnit);
                Append(BytesOf(surrogatePair.e1()).Generate<unsigned char>() + BytesOf(surrogatePair.e2()).Generate<unsigned char>());
            }
                //if the character is not part of BMP and the storage format is UTF-16BE
            else if (_storageEncoding == UTF16BE)
            {
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codeUnit);
                Append(BytesOf(surrogatePair.e1()).Reverse().Generate<unsigned char>() +
                BytesOf(surrogatePair.e2()).Reverse().Generate<unsigned char>());
            }
                //(END-STATE)
                //if the storage format is UTF-32LE
            else if (_storageEncoding == UTF32LE)
            {
                Append(BytesOf(codeUnit).Generate<unsigned char>());
            }
                //if the storage format is UTF-32BE
            else if (_storageEncoding == UTF32BE)
            {
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
            }

            i += UTF32_CODE_UNIT_LENGTH;
        }
    }

    //_array is a UTF-32 string with an available terminating character ->
    string(const unsigned char*_array, U32, Endianity _endianity) : string(_array, u32, _endianity, DefaultStorageEncoding) {}

    //_array is a UTF-32 string with an available terminating character ->
    string(const unsigned char*_array, U32, Encoding _storageEncoding) : string(_array, u32, DefaultEndianity,
    _storageEncoding) {}

    //_array is a UTF-32 string with an available terminating character ->
    string(const unsigned char* _array, U32) : string(_array, u32, DefaultEndianity, DefaultStorageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-32 string ->
    string(const unsigned char*_array, U32, Endianity _endianity, unsigned int _length, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        if (_array[0] == UTF32LE_BOM[0] && _array[1] == UTF32LE_BOM[1] && _array[2] == UTF32LE_BOM[2] &&
        _array[3] == UTF32LE_BOM[3])
        {
            _endianity = LE;
            i = UTF32_CODE_UNIT_LENGTH;
        }
        else if (_array[0] == UTF32BE_BOM[0] && _array[1] == UTF32BE_BOM[1] && _array[2] == UTF32BE_BOM[2] &&
        _array[3] == UTF32BE_BOM[3])
        {
            _endianity = BE;
            i = UTF32_CODE_UNIT_LENGTH;
        }

        int lengthMarker = GetBits(_length, 30, 31);
        //-> clearing the marking bits
        SetBits(_length, false, 30, 31);

        while (true)
        {
			//if a terminating character is reached
            if (_array[i] == 0) break;
			//if the length is specified in bytes and the end of the string is reached
            else if (lengthMarker == 0 && i >= _length) break;
			//if the length is specified in code units and the end of the string is reached
            else if (lengthMarker == 1 && (i / UTF32_CODE_UNIT_LENGTH) == _length) break;
			//if the length is specified in characters and the end of the string is reached
            else if (lengthMarker == 2 && CharacterCount == _length) break;

            utf32 codeUnit = _32(_array[i], _array[i + 1], _array[i + 2], _array[i + 3], _endianity);

            //if the storage format is UTF-8
            if (_storageEncoding == UTF8)
            {
                Append(ToUTF8(codeUnit).Generate<unsigned char>());
            }
                //if the character is part of BMP and the storage format is UTF-16LE
            else if (IsBMP(codeUnit) && _storageEncoding == UTF16LE)
            {
                Append(BytesOf(static_cast<unsigned short>(codeUnit)).Generate<unsigned char>());
            }
                //if the character is part of BMP and the storage format is UTF-16BE
            else if (IsBMP(codeUnit) && _storageEncoding == UTF16BE)
            {
                Append(BytesOf(static_cast<unsigned short>(codeUnit)).Reverse().Generate<unsigned char>());
            }
                //(STATE) the character is not part of BMP
                //if the character is not part of BMP and the storage format is UTF-16LE
            else if (_storageEncoding == UTF16LE)
            {
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codeUnit);
                Append(BytesOf(surrogatePair.e1()).Generate<unsigned char>() + BytesOf(surrogatePair.e2()).Generate<unsigned char>());
            }
                //if the character is not part of BMP and the storage format is UTF-16BE
            else if (_storageEncoding == UTF16BE)
            {
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codeUnit);
                Append(BytesOf(surrogatePair.e1()).Reverse().Generate<unsigned char>() +
                BytesOf(surrogatePair.e2()).Reverse().Generate<unsigned char>());
            }
                //(END-STATE)
                //if the storage format is UTF-32LE
            else if (_storageEncoding == UTF32LE)
            {
                Append(BytesOf(codeUnit).Generate<unsigned char>());
            }
                //if the storage format is UTF-32BE
            else if (_storageEncoding == UTF32BE)
            {
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
            }

            i += UTF32_CODE_UNIT_LENGTH;
        }
    }

    //_length specifies the length of _array
    //_array is a UTF-32 string ->
    string(const unsigned char*_array, U32, Endianity _endianity, unsigned int _length) : string(_array, u32, _endianity, _length,
    DefaultStorageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-32 string ->
    string(const unsigned char*_array, U32, unsigned int _length, Encoding _storageEncoding) : string(_array, u32, DefaultEndianity,
    _length, _storageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-32 string ->
    string(const unsigned char* _array, U32, unsigned int _length) : string(_array, u32, DefaultEndianity, _length,
    DefaultStorageEncoding) {}

    //_array is a UTF-16 string with an available terminating character ->
    string(const utf16* _array, Endianity _endianity, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        if (_array[0] == UTF16LE_BOM[0] && _array[1] == UTF16LE_BOM[1])
        {
            _endianity = LE;
            i = UTF16_CODE_UNIT_LENGTH;
        }
        else if (_array[0] == UTF16BE_BOM[0] && _array[1] == UTF16BE_BOM[1])
        {
            _endianity = BE;
            i = UTF16_CODE_UNIT_LENGTH;
        }

        while (true)
        {
            utf16 codeUnit = _array[i];

            if (codeUnit == 0) break;

            //if codeUnit is a high surrogate
            if (IsHighSurrogate(codeUnit))
            {
                utf16 highSurrogate = codeUnit;
                utf16 lowSurrogate = _array[i + 1];

                //if the storage format is UTF-8
                if (_storageEncoding == UTF8)
                {
                    Append(ToUTF8(highSurrogate, lowSurrogate).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16LE
                else if (_storageEncoding == UTF16LE)
                {
                    Append(BytesOf(highSurrogate).Generate<unsigned char>() + BytesOf(lowSurrogate).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16BE
                else if (_storageEncoding == UTF16BE)
                {
                    Append(BytesOf(highSurrogate).Reverse().Generate<unsigned char>() + BytesOf(lowSurrogate).Reverse().Generate<unsigned char>());
                }
                    //if the storage format is UTF-32LE
                else if (_storageEncoding == UTF32LE)
                {
                    Append(BytesOf(ToUTF32(highSurrogate, lowSurrogate)).Generate<unsigned char>());
                }
                    //if the storage format is UTF-32BE
                else if (_storageEncoding == UTF32BE)
                {
                    Append(BytesOf(ToUTF32(highSurrogate, lowSurrogate)).Reverse().Generate<unsigned char>());
                }

                i += 2;
            }
                //if codeUnit is a code point of BMP
            else
            {
                //if the storage format is UTF-8
                if (_storageEncoding == UTF8)
                {
                    Append(ToUTF8(codeUnit).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16LE
                else if (_storageEncoding == UTF16LE)
                {
                    Append(BytesOf(codeUnit).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16BE
                else if (_storageEncoding == UTF16BE)
                {
                    Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                }
                    //if the storage format is UTF-32LE
                else if (_storageEncoding == UTF32LE)
                {
                    Append(BytesOf(static_cast<unsigned int>(codeUnit)).Generate<unsigned char>());
                }
                    //if the storage format is UTF-32BE
                else if (_storageEncoding == UTF32BE)
                {
                    Append(BytesOf(static_cast<unsigned int>(codeUnit)).Reverse().Generate<unsigned char>());
                }

                i++;
            }
        }
    }

    //_array is a UTF-16 string with an available terminating character ->
    string(const utf16* _array, Endianity _endianity) : string(_array, _endianity, DefaultStorageEncoding) {}

    //_array is a UTF-16 string ->
    string(const utf16* _array, Encoding _storageEncoding) : string(_array, DefaultEndianity,
    _storageEncoding) {}

    //_array is a UTF-16 string ->
    string(const utf16* _array) : string(_array, DefaultEndianity, DefaultStorageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-16 string ->
    string(const utf16* _array, Endianity _endianity, unsigned int _length, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        if (_array[0] == UTF16LE_BOM[0] && _array[1] == UTF16LE_BOM[1])
        {
            _endianity = LE;
            i = UTF16_CODE_UNIT_LENGTH;
        }
        else if (_array[0] == UTF16BE_BOM[0] && _array[1] == UTF16BE_BOM[1])
        {
            _endianity = BE;
            i = UTF16_CODE_UNIT_LENGTH;
        }

        int lengthMarker = GetBits(_length, 30, 31);
        //-> clearing the marking bits
        SetBits(_length, false, 30, 31);

        while (true)
        {
            //if a terminating character is reached
            if (_array[i] == 0) break;
			//if the length is specified in bytes and the end of the string is reached
            else if (lengthMarker == 0 && i >= _length) break;
			//if the length is specified in code units and the end of the string is reached
            else if (lengthMarker == 1 && i >= _length) break;
			//if the length is specified in characters and the end of the string is reached
            else if (lengthMarker == 2 && CharacterCount == _length) break;

            utf16 codeUnit = _array[i];

            //if codeUnit is a high surrogate
            if (IsHighSurrogate(codeUnit))
            {
                utf16 highSurrogate = codeUnit;
                utf16 lowSurrogate = _array[i + 1];

                //if the storage format is UTF-8
                if (_storageEncoding == UTF8)
                {
                    Append(ToUTF8(highSurrogate, lowSurrogate).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16LE
                else if (_storageEncoding == UTF16LE)
                {
                    Append(BytesOf(highSurrogate).Generate<unsigned char>() + BytesOf(lowSurrogate).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16BE
                else if (_storageEncoding == UTF16BE)
                {
                    Append(BytesOf(highSurrogate).Reverse().Generate<unsigned char>() +
                    BytesOf(lowSurrogate).Reverse().Generate<unsigned char>());
                }
                    //if the storage format is UTF-32LE
                else if (_storageEncoding == UTF32LE)
                {
                    Append(BytesOf(ToUTF32(highSurrogate, lowSurrogate)).Generate<unsigned char>());
                }
                    //if the storage format is UTF-32BE
                else if (_storageEncoding == UTF32BE)
                {
                    Append(BytesOf(ToUTF32(highSurrogate, lowSurrogate)).Reverse().Generate<unsigned char>());
                }

                i += 2;
            }
                //if codeUnit is a code point of BMP
            else
            {
                //if the storage format is UTF-8
                if (_storageEncoding == UTF8)
                {
                    Append(ToUTF8(codeUnit).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16LE
                else if (_storageEncoding == UTF16LE)
                {
                    Append(BytesOf(codeUnit).Generate<unsigned char>());
                }
                    //if the storage format is UTF-16BE
                else if (_storageEncoding == UTF16BE)
                {
                    Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
                }
                    //if the storage format is UTF-32LE
                else if (_storageEncoding == UTF32LE)
                {
                    Append(BytesOf(static_cast<unsigned int>(codeUnit)).Generate<unsigned char>());
                }
                    //if the storage format is UTF-32BE
                else if (_storageEncoding == UTF32BE)
                {
                    Append(BytesOf(static_cast<unsigned int>(codeUnit)).Reverse().Generate<unsigned char>());
                }

                i++;
            }
        }
    }

    //_length specifies the length of _array
    //_array is a UTF-16 string ->
    string(const utf16*_array, Endianity _endianity, unsigned int _length) : string(_array, _length,
    DefaultStorageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-16 string ->
    string(const utf16*_array, unsigned int _length, Encoding _storageEncoding) : string(_array, DefaultEndianity,
    _length, _storageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-16 string ->
    string(const utf16*_array, unsigned int _length) : string(_array, DefaultEndianity, _length,
    DefaultStorageEncoding) {}

    //_array is a UTF-32 string with an available terminating character ->
    string(const utf32*_array, Endianity _endianity, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        using byte_operations::ByteOf;

        if (ByteOf(_array[0], 0) == UTF32LE_BOM[0] && ByteOf(_array[1], 1) == UTF32LE_BOM[1] &&
        ByteOf(_array[2], 2) == UTF32LE_BOM[2] && ByteOf(_array[3], 3 == UTF32LE_BOM[3]))
        {
            _endianity = LE;
            i ++;
        }
        else if (ByteOf(_array[0], 0) == UTF32BE_BOM[0] && ByteOf(_array[1], 1) == UTF32BE_BOM[1] &&
        ByteOf(_array[2], 2) == UTF32BE_BOM[2] && ByteOf(_array[3], 3 == UTF32BE_BOM[3]))
        {
            _endianity = BE;
            i ++;
        }

        while (true)
        {
            utf32 codeUnit = _array[i];

            if (codeUnit == 0) break;

            //if the storage format is UTF-8
            if (_storageEncoding == UTF8)
            {
                Append(ToUTF8(codeUnit).Generate<unsigned char>());
            }
                //if the character is part of BMP and the storage format is UTF-16LE
            else if (IsBMP(codeUnit) && _storageEncoding == UTF16LE)
            {
                Append(BytesOf(static_cast<unsigned short>(codeUnit)).Generate<unsigned char>());
            }
                //if the character is part of BMP and the storage format is UTF-16BE
            else if (IsBMP(codeUnit) && _storageEncoding == UTF16BE)
            {
                Append(BytesOf(static_cast<unsigned short>(codeUnit)).Reverse().Generate<unsigned char>());
            }
                //(STATE) the character is not part of BMP
                //if the character is not part of BMP and the storage format is UTF-16LE
            else if (_storageEncoding == UTF16LE)
            {
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codeUnit);
                Append(BytesOf(surrogatePair.e1()).Generate<unsigned char>() + BytesOf(surrogatePair.e2()).Generate<unsigned char>());
            }
                //if the character is not part of BMP and the storage format is UTF-16BE
            else if (_storageEncoding == UTF16BE)
            {
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codeUnit);
                Append(BytesOf(surrogatePair.e1()).Reverse().Generate<unsigned char>() +
                BytesOf(surrogatePair.e2()).Reverse().Generate<unsigned char>());
            }
                //(END-STATE)
                //if the storage format is UTF-32LE
            else if (_storageEncoding == UTF32LE)
            {
                Append(BytesOf(codeUnit).Generate<unsigned char>());
            }
                //if the storage format is UTF-32BE
            else if (_storageEncoding == UTF32BE)
            {
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
            }

            i ++;
        }
    }
        
    //_array is a UTF-32 string with an available terminating character ->
    string(const utf32* _array, Endianity _endianity) : string(_array, _endianity, DefaultStorageEncoding) {}

    //_array is a UTF-32 string ->
    string(const utf32*_array, Encoding _storageEncoding) : string(_array, DefaultEndianity, _storageEncoding) {}

    //_array is a UTF-32 string ->
    string(const utf32*_array) : string(_array, DefaultEndianity, DefaultStorageEncoding) {}

    //_length specifies the length of _array
    //_array is a UTF-32 string ->
    string(const utf32*_array, Endianity _endianity, unsigned int _length, Encoding _storageEncoding)
    {
        if (_array == nullptr) return;

        StorageEncoding = _storageEncoding;

        int i = 0;

        using byte_operations::ByteOf;

        if (ByteOf(_array[0], 0) == UTF32LE_BOM[0] && ByteOf(_array[1], 1) == UTF32LE_BOM[1] &&
        ByteOf(_array[2], 2) == UTF32LE_BOM[2] && ByteOf(_array[3], 3 == UTF32LE_BOM[3]))
        {
            _endianity = LE;
            i ++;
        }
        else if (ByteOf(_array[0], 0) == UTF32BE_BOM[0] && ByteOf(_array[1], 1) == UTF32BE_BOM[1] &&
        ByteOf(_array[2], 2) == UTF32BE_BOM[2] && ByteOf(_array[3], 3 == UTF32BE_BOM[3]))
        {
            _endianity = BE;
            i ++;
        }

        int lengthMarker = GetBits(_length, 30, 31);
        //-> clearing the marking bits
        SetBits(_length, false, 30, 31);

        while (true)
        {
			//if a terminating character is reached
            if (_array[i] == 0) break;
			//if the length is specified in bytes and the end of the string is reached
            else if (lengthMarker == 0 && i >= _length) break;
			//if the length is specified in code units and the end of the string is reached
            else if (lengthMarker == 1 && UTF16_CODE_UNIT_LENGTH >= _length) break;
			//if the length is specified in characters and the end of the string is reached
            else if (lengthMarker == 2 && CharacterCount == _length) break;

            utf32 codeUnit = _array[i];

            //if the storage format is UTF-8
            if (_storageEncoding == UTF8)
            {
                Append(ToUTF8(codeUnit).Generate<unsigned char>());
            }
                //if the character is part of BMP and the storage format is UTF-16LE
            else if (IsBMP(codeUnit) && _storageEncoding == UTF16LE)
            {
                Append(BytesOf(static_cast<unsigned short>(codeUnit)).Generate<unsigned char>());
            }
                //if the character is part of BMP and the storage format is UTF-16BE
            else if (IsBMP(codeUnit) && _storageEncoding == UTF16BE)
            {
                Append(BytesOf(static_cast<unsigned short>(codeUnit)).Reverse().Generate<unsigned char>());
            }
                //(STATE) the character is not part of BMP
                //if the character is not part of BMP and the storage format is UTF-16LE
            else if (_storageEncoding == UTF16LE)
            {
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codeUnit);
                Append(BytesOf(surrogatePair.e1()).Generate<unsigned char>() + BytesOf(surrogatePair.e2()).Generate<unsigned char>());
            }
                //if the character is not part of BMP and the storage format is UTF-16BE
            else if (_storageEncoding == UTF16BE)
            {
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codeUnit);
                Append(BytesOf(surrogatePair.e1()).Reverse().Generate<unsigned char>() +
                BytesOf(surrogatePair.e2()).Reverse().Generate<unsigned char>());
            }
                //(END-STATE)
                //if the storage format is UTF-32LE
            else if (_storageEncoding == UTF32LE)
            {
                Append(BytesOf(codeUnit).Generate<unsigned char>());
            }
                //if the storage format is UTF-32BE
            else if (_storageEncoding == UTF32BE)
            {
                Append(BytesOf(codeUnit).Reverse().Generate<unsigned char>());
            }

            i++;
        }
    }

        //_length specifies the length of _array
    //_array is a UTF-32 string ->
    string(const utf32*_array, Endianity _endianity, unsigned int _length) : string(_array, _endianity, _length,
    DefaultStorageEncoding) {}

        //_length specifies the length of _array
    //_array is a UTF-32 string ->
    string(const utf32*_array, unsigned int _length, Encoding _storageEncoding) : string(_array, DefaultEndianity,
    _length, _storageEncoding) {}

        //_length specifies the length of _array
    //_array is a UTF-32 string ->
    string(const utf32*_array, unsigned int _length) : string(_array, DefaultEndianity, _length,
    DefaultStorageEncoding) {}

    string(const wchar_t* _string, Encoding _storageEncoding) : string(reinterpret_cast<const utf16*>(_string), LE, _storageEncoding) {}

    string(const string& _string)
    {
        if (this == &_string) return;

        Extensor = _string.Extensor;
        StorageEncoding = _string.StorageEncoding;

        Clear();

        extend(_string.byteCount());

        Append(_string);
    }

    //it generates a segment
    string(const string& _source, int _begin, int _end)
    {
        if (_begin < 0 || _end > _source.CharacterCount - 1) return;
        else if (_begin > _end) return;

        Range byteRange { _source.byteRangeOf(_begin).begin(), _source.byteRangeOf(_end).end() };
        Elements = &(_source.Elements[byteRange.begin()]);
        CharacterCount = (_end - _begin) + 1;
        ByteCount = byteRange.length();
        Size = byteRange.length();
        SpatialKind = SpatialKind::SEGMENT;
    }

	//it generates a segment
    string(const string& _source, const Range<int>& _range)
    {
        if (_range.begin() < 0 || _range.end() > _source.CharacterCount - 1) return;
        else if (_range.begin() > _range.end()) return;

        Range byteRange { _source.byteRangeOf(_range.begin()).begin(), _source.byteRangeOf(_range.end()).end() };
        Elements = &(_source.Elements[byteRange.begin()]);
        CharacterCount = _range.length();
        ByteCount = byteRange.length();
        Size = byteRange.length();
        SpatialKind = SpatialKind::SEGMENT;
    }

    ///DESTRUCTOR

    ~string()
    {
        if (IsSegment())
        {
            return;
        }
        else if (ReleaseMode == ReleaseMode::IMMEDIATE)
        {
            delete[] Elements;
        }
    }

    ///OPERATORS

    //this operator does not compare the fields of the two objects; it compares only the character content
    bool operator==(const string& _string) const
    {
        if (CharacterCount != _string.CharacterCount)
        {
            return false;
        }

        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] != _string[i])
            {
                return false;
            }
        }

        return true;
    }

	//this operator does not compare the fields of the two objects; it compares only the character content
    bool operator!=(const string& _string) const
    {
        if (CharacterCount != _string.CharacterCount)
        {
            return true;
        }

        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] != _string[i])
            {
                return true;
            }
        }

        return false;
    }

    string& operator=(const string& _string)
    {
        if (this == &_string) return *this;

        Extensor = _string.Extensor;
        StorageEncoding = _string.StorageEncoding;

        Clear();

        extend(_string.byteCount());

        Append(_string);
    }

    string operator+(CodePoint _value) const
    {
        return Clone().Append(_value);
    }

    string operator+(const string& _string) const
    {
        return Clone().Append(_string);
    }

    string& operator+=(CodePoint _codePoint)
    {
        return Append(_codePoint);
    }

    string& operator+=(const string& _string)
    {
        return Append(_string);
    }

    //_index is in the range of list ->
    CodePoint operator[](int _index)
    {
        int i = byteRangeOf(_index).begin();

        //if the storage format is UTF-8 and the character is encoded by one byte
        if (StorageEncoding == UTF8 && (Elements[i] >> 7) == 0b0)
        {
            return Elements[i];
        }
        //if the storage format is UTF-8 and the character is encoded by two bytes
        else if (StorageEncoding == UTF8 && (Elements[i] >> 5) == 0b110)
        {
            return ToUTF32(static_cast<unsigned char>(Elements[i]), static_cast<unsigned char>(Elements[i + 1]));
        }
        //if the storage format is UTF-8 and the character is encoded by three bytes
        else if (StorageEncoding == UTF8 && (Elements[i] >> 4) == 0b1110)
        {
            return ToUTF32(static_cast<unsigned char>(Elements[i]), static_cast<unsigned char>(Elements[i + 1]), static_cast<unsigned char>(Elements[i + 2]));
        }
        //if the storage format is UTF-8 and the character is encoded by four bytes
        else if (StorageEncoding == UTF8 && (Elements[i] >> 3) == 0b11110)
        {
            return ToCodePoint(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3]);
        }
        //if the storage format is UTF-16LE and the character is part of BMP
        else if (StorageEncoding == UTF16LE && IsBMP(_16(Elements[i], Elements[i + 1], LE)))
        {
            return _16(Elements[i], Elements[i + 1], LE);
        }
        //if the storage format is UTF-16BE and the character is part of BMP
        else if (StorageEncoding == UTF16BE && IsBMP(_16(Elements[i], Elements[i + 1], BE)))
        {
            return _16(Elements[i], Elements[i + 1], BE);
        }
        //(STATE) the character is not part of BMP
        //if the storage format is UTF-16LE and the character is not part of BMP
        else if (StorageEncoding == UTF16LE)
        {
            utf16 highSurrogate = _16(Elements[i], Elements[i + 1], LE);
            utf16 lowSurrogate = _16(Elements[i + 2], Elements[i + 3], LE);
            return ToCodePoint(highSurrogate, lowSurrogate);
        }
        //if the storage format is UTF-16BE and the character is not part of BMP
        else if (StorageEncoding == UTF16BE)
        {
            utf16 highSurrogate = _16(Elements[i], Elements[i + 1], BE);
            utf16 lowSurrogate = _16(Elements[i + 2], Elements[i + 3], BE);
            return ToCodePoint(highSurrogate, lowSurrogate);
        }
        //(END-STATE)
        else if (StorageEncoding == UTF32LE)
        {
            return _32(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3], LE);
        }
        else if (StorageEncoding == UTF32BE)
        {
            return _32(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3], BE);
        }
    }

    //_index is in the range of list ->
    CodePoint operator[](int _index) const
    {
        int i = byteRangeOf(_index).begin();

        //if the storage format is UTF-8 and the character is encoded by one byte
        if (StorageEncoding == UTF8 && (Elements[i] >> 7) == 0b0)
        {
            return Elements[i];
        }
            //if the storage format is UTF-8 and the character is encoded by two bytes
        else if (StorageEncoding == UTF8 && (Elements[i] >> 5) == 0b110)
        {
            return ToUTF32(static_cast<unsigned char>(Elements[i]), static_cast<unsigned char>(Elements[i + 1]));
        }
            //if the storage format is UTF-8 and the character is encoded by three bytes
        else if (StorageEncoding == UTF8 && (Elements[i] >> 4) == 0b1110)
        {
            return ToUTF32(static_cast<unsigned char>(Elements[i]), static_cast<unsigned char>(Elements[i + 1]), static_cast<unsigned char>(Elements[i + 2]));
        }
            //if the storage format is UTF-8 and the character is encoded by four bytes
        else if (StorageEncoding == UTF8 && (Elements[i] >> 3) == 0b11110)
        {
            return ToCodePoint(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3]);
        }
            //if the storage format is UTF-16LE and the character is part of BMP
        else if (StorageEncoding == UTF16LE && IsBMP(_16(Elements[i], Elements[i + 1], LE)))
        {
            return _16(Elements[i], Elements[i + 1], LE);
        }
            //if the storage format is UTF-16BE and the character is part of BMP
        else if (StorageEncoding == UTF16BE && IsBMP(_16(Elements[i], Elements[i + 1], BE)))
        {
            return _16(Elements[i], Elements[i + 1], BE);
        }
            //(STATE) the character is not part of BMP
            //if the storage format is UTF-16LE and the character is not part of BMP
        else if (StorageEncoding == UTF16LE)
        {
            utf16 highSurrogate = _16(Elements[i], Elements[i + 1], LE);
            utf16 lowSurrogate = _16(Elements[i + 2], Elements[i + 3], LE);
            return ToCodePoint(highSurrogate, lowSurrogate);
        }
            //if the storage format is UTF-16BE and the character is not part of BMP
        else if (StorageEncoding == UTF16BE)
        {
            utf16 highSurrogate = _16(Elements[i], Elements[i + 1], BE);
            utf16 lowSurrogate = _16(Elements[i + 2], Elements[i + 3], BE);
            return ToCodePoint(highSurrogate, lowSurrogate);
        }
            //(END-STATE)
        else if (StorageEncoding == UTF32LE)
        {
            return _32(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3], LE);
        }
        else if (StorageEncoding == UTF32BE)
        {
            return _32(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3], BE);
        }
    }

    ///FIELDS

    int byteCount() const
    {
        return ByteCount;
    }

    int count() const
    {
        return CharacterCount;
    }

    int size() const
    {
        return Size;
    }

    int position() const
    {
        return Position;
    }

    Encoding storageEncoding() const
    {
        return StorageEncoding;
    }

    const unsigned char* elements() const
    {
        return Elements;
    }

    ///

    bool IsSegment() const
    {
        return SpatialKind == SpatialKind::SEGMENT;
    }

    //"205" => false
    //"205." => false
    //"205.0" => true
    //"205.12" => true
    bool IsFractional() const
    {
        if (CharacterCount == 0) return false;
        else if ((*this)[0] != '-' && ! IsDigit((*this)[0])) return false;

        string absoluteValue = (*this)[0] == '-' ? Sublist(1) : Sublist(0);

        if (!absoluteValue.ContainsOnly([](utf32 x){ return IsDigit(x) || x == '.'; }))
        {
            return false;
        }
        else if (!absoluteValue.Contains('.'))
        {
            return false;
        }
        else if (absoluteValue[0] == '.')
        {
            return false;
        }
        else if (absoluteValue[CharacterCount - 1] == '.')
        {
            return false;
        }
        else if (absoluteValue.CountOf('.') > 1)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    //_index is outside the range of list => -1
    //<T> is utf8, utf16 or utf32 ->
    template<typename T> T codeUnitAt(int _index) const
    {
        if (StorageEncoding == UTF8)
        {
            return Elements[_index];
        }
        else if (StorageEncoding == UTF16LE)
        {
            return _16(Elements[_index * UTF16_CODE_UNIT_LENGTH], Elements[(_index * UTF16_CODE_UNIT_LENGTH) + 1], LE);
        }
        else if (StorageEncoding == UTF16BE)
        {
            return _16(Elements[_index * UTF16_CODE_UNIT_LENGTH], Elements[(_index * UTF16_CODE_UNIT_LENGTH) + 1], BE);
        }
        else if (StorageEncoding == UTF32LE)
        {
            return _32(
            Elements[_index * UTF32_CODE_UNIT_LENGTH],
            Elements[(_index * UTF32_CODE_UNIT_LENGTH) + 1],
            Elements[(_index * UTF32_CODE_UNIT_LENGTH) + 2],
            Elements[(_index * UTF32_CODE_UNIT_LENGTH) + 3],
            LE);
        }
        else if (StorageEncoding == UTF32BE)
        {
            return _32(
            Elements[_index * UTF32_CODE_UNIT_LENGTH],
            Elements[(_index * UTF32_CODE_UNIT_LENGTH) + 1],
            Elements[(_index * UTF32_CODE_UNIT_LENGTH) + 2],
            Elements[(_index * UTF32_CODE_UNIT_LENGTH) + 3],
            BE);
        }
    }

    ///TRAVERSAL FUNCTIONS

    bool can_reverse() const
    {
        return position() > 0;
    }

    bool can_advance() const
    {
        return position() < CharacterCount - 1;
    }

    //position() > 0 >> position() = position() - 1
    //traversalMode() == BOUNDED && position() == 0 >> position() = position()
    //traversalMode() == CIRCULAR && position() == 0 >> position() = characterCount() - 1
    string& back()
    {
        if (Position > 0)
        {
            Position--;
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Position == 0)
        {
            Position = CharacterCount - 1;
        }

        return *this;
    }

    //position() < characterCount() - 1 >> position() = position() + 1
    //traversalMode() == BOUNDED && position() == characterCount() - 1 >> position() = position()
    //traversalMode() == CIRCULAR && position() == characterCount() - 1 >> position() = 0
    string& advance()
    {
        if (Position < CharacterCount - 1)
        {
            Position++;
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Position == CharacterCount - 1)
        {
            Position = 0;
        }

        return *this;
    }

    //position() > 0 => [position() - 1]
    //traversalMode() == BOUNDED && position() == 0 => [0]
    //traversalMode() == CIRCULAR && position() == 0 => [characterCount() - 1]
    CodePoint previous() const
    {
        if (Position > 0)
        {
            return (*this)[Position - 1];
        }
        else if (TraversalMode == TraversalMode::BOUNDED && Position == 0)
        {
            return (*this)[0];
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Position == 0)
        {
            return (*this)[CharacterCount - 1];
        }
    }

    //count() > 0 ->
    CodePoint current() const
    {
        return (*this)[Position];
    }

    //position() < characterCount() - 1 => [position() + 1]
    //traversalMode() == BOUNDED && position() == characterCount() - 1 => [position()]
    //traversalMode() == CIRCULAR && position() == characterCount() - 1 => [0]
    CodePoint next() const
    {
        if (Position < CharacterCount - 1)
        {
            return (*this)[Position + 1];
        }
        else if (TraversalMode == TraversalMode::BOUNDED && Position == CharacterCount - 1)
        {
            return (*this)[Position];
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Position == CharacterCount - 1)
        {
            return (*this)[0];
        }
    }

    //_position < -1 || _position > characterCount() - 1 => -1
    int set_position(int _position)
    {
        if (_position < - 1 || _position > CharacterCount - 1) return - 1;

        Position = _position;

        return 0;
    }

    ///MUTATION FUNCTIONS

    //the bytes in _value represent a single character (in a specific encoding) and (are appended to &elements() in the same order as they are in _value)
    string& Append(const list<unsigned char>& _value)
    {
        if (IsSegment()) return *this;

        if (CharacterCount + _value.count() > Size)
        {
            extend(Size + (_value.count() * Extensor)
        }

        for (int i = 0, n = ByteCount; i < _value.count(); i++, n++)
        {
            Elements[n] = _value[i];
        }

        ByteCount += _value.count();
        CharacterCount++;

        return *this;
    }

    string& Append(CodePoint _value)
    {
        if (IsSegment()) return *this;

        list<unsigned char> bytes = bytesOf(_value); //байтовете are in natural form

        if (ByteCount + bytes.count() > Size)
        {
            extend(Size + (bytes.count() * Extensor)
        }

        for (int i = 0, n = ByteCount; i < bytes.count(); i++, n++)
        {
            Elements[n] = bytes[i];
        }

        ByteCount += bytes.count();
        CharacterCount++;

        return *this;
    }

    string& Append(CodePoint _value, int _times)
    {
        if (IsSegment()) return *this;

        for (int i = 0; i < _times; i++)
        {
            Append(_value);
        }

        return *this;
    }

    string& Append(const list<CodePoint>& _value)
    {
        if (IsSegment()) return *this;

        for (CodePoint __element : _value)
        {
            Append(__element);
        }

        return *this;
    }

    string& Append(const string& _value)
    {
        if (IsSegment()) return *this;

        for (int i = 0; i < _value.CharacterCount; i++)
        {
            Append(_value[i]);
        }

        return *this;
    }

    //_size < 0 -> state of the list doesn't change
    string& Clear(int _size = 0)
    {
        if (IsSegment()) return *this;
        else if (_size < 0) return *this;

        ByteCount = 0;
        CharacterCount = 0;
        Size = _size;
        delete [] Elements;
        Elements = new unsigned char[Size];

        return *this;
    }

    //[1, 2, 10].FillLeft(5, 7) => [5, 5, 5, 5, 1, 2, 10]
    string& FillLeft(CodePoint _value, int _length)
    {
        if (IsSegment()) return *this;

        for (int i = 0; CharacterCount < _length; i++)
        {
            Insert(_value, 0);
        }

        return *this;
    }

    //[1, 2, 10].FillRight(5, 7) => [1, 2, 10, 5, 5, 5, 5]
    string& FillRight(CodePoint _value, int _length)
    {
        if (IsSegment()) return *this;

        for (int i = 0; CharacterCount < _length; i++)
        {
            Append(_value);
        }

        return *this;
    }

    //(count() > 0 && _index > 0 && _index < characterCount()) ->
    string& Insert(CodePoint _value, int _index)
    {
        if (IsSegment()) return *this;
        else if (count() == 0) return *this;
        else if (_index < 0 || _index >= count()) return *this;

        list<unsigned char> bytes = bytesOf(_value);

        unsigned char* array = new unsigned char[ByteCount + bytes.count()];

        int byteIndex = byteRangeOf(_index).begin();

        //copying of (the bytes to the left of byteIndex)
        for (int i = 0; i < byteIndex; i++)
        {
            array[i] = Elements[i];
        }

        //copying of &bytes
        for (int i = 0; i < bytes.count(); i++)
        {
            array[byteIndex + i] = bytes[i];
        }

        //copying (the bytes after (byteIndex + bytes.count()))
        for (int i = byteIndex + bytes.count(), n = 0; i < ByteCount + bytes.count(); i++, n++)
        {
            array[i] = Elements[byteIndex + n];
        }

        delete [] Elements;
        Elements = array;

        ByteCount += bytes.count();
        CharacterCount++;

        return *this;
    }

    //(count() > 0 && _index > 0 && (_index <= characterCount())) ->
    string& Insert(const string& _value, int _index)
    {
        if (IsSegment()) return *this;
        else if (count() == 0) return *this;
        else if (_index < 0 || _index >= count()) return *this;

        //equalization of (the encoding of the inserted string) to the encoding of &this

        string convertedString;

        if (_value.StorageEncoding == UTF8)
        {
            convertedString = string(_value.elements(), u8, _value.CharacterCount|c, StorageEncoding);
        }
        else if (_value.StorageEncoding == UTF16LE || _value.StorageEncoding == UTF16BE)
        {
            convertedString = string(_value.elements(), u16, _value.CharacterCount|c, StorageEncoding);
        }
        else if (_value.StorageEncoding == UTF32LE || _value.StorageEncoding == UTF32BE)
        {
            convertedString = string(_value.elements(), u32, _value.CharacterCount|c, StorageEncoding);
        }

        unsigned char* array = new unsigned char[ByteCount + convertedString.ByteCount];

        int byteIndex = byteRangeOf(_index).begin();

        //copying (the bytes to the left of byteIndex)
        for (int i = 0; i < byteIndex; i++)
        {
            array[i] = Elements[i];
        }

        //copying (the bytes of _value.elements())
        for (int i = 0; i < convertedString.ByteCount; i++)
        {
            array[byteIndex + i] = convertedString.Elements[i];
        }

        //copying (the bytes after (byteIndex + bytes.count()))
        for (int i = byteIndex + convertedString.ByteCount, n = 0; i < ByteCount + convertedString.ByteCount; i++, n++)
        {
            array[i] = Elements[byteIndex + n];
        }

        delete [] Elements;
        Elements = array;

        ByteCount += convertedString.ByteCount;
        CharacterCount += convertedString.CharacterCount;

        return *this;
    }

    //[1, 2, 3, 4, 5].Move(2, 4) => [1, 2, 4, 5, 3]
    string& Move(int _sourceIndex, int _destinationIndex)
    {
        if (IsSegment()) return *this;
        else if (!InRange(_sourceIndex) || !InRange(_destinationIndex)) return *this;

        int smaller = numeric::SmallerOf(_sourceIndex, _destinationIndex);
        int larger = numeric::LargerOf(_sourceIndex, _destinationIndex);

        CodePoint sourceElement = (*this)[_sourceIndex];

        if (_destinationIndex < _sourceIndex)
		{
				//moving of the sequence (_destinationIndex.._sourceIndex - 1) N positions to the right
            for (int i = _sourceIndex; i > _destinationIndex; i--)
            {
                Set(i, (*this)[i - 1]);
            }
        }
        else if (_destinationIndex > _sourceIndex)
        {
			//moving of the sequence (_sourceIndex.._destinationIndex - 1) N positions to the left
            for (int i = _sourceIndex; i < _destinationIndex; i++)
            {
                Set(i, (*this)[i + 1]);
            }
        } 

        Set(_destinationIndex, sourceElement);

        return *this;
    }

    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].Reduce(2) => [10, 5, 4, 18, 9, 5]
    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].Reduce(11) => [11, 2, 10, 5, 4, 18, 9, 5, 0, 3]
    string Reduce(int _reducer)
    {
        if (IsSegment()) return *this;

        return ReduceLeft(_reducer).ReduceRight(_reducer);
    }

    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].ReduceLeft(4) => [4, 18, 9, 5, 0, 3]
    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].ReduceLeft(11) => [11, 2, 10, 5, 4, 18, 9, 5, 0, 3]
    string ReduceLeft(int _reducer)
    {
        if (IsSegment()) return *this;
        else if (_reducer < 0 || _reducer > CharacterCount) return *this;

        return Remove(0, _reducer - 1);
    }

    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].ReduceRight(4) => [11, 2, 10, 5, 4, 18]
    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].ReduceRight(11) => [11, 2, 10, 5, 4, 18, 9, 5, 0, 3]
    string ReduceRight(int _reducer)
    {
        if (IsSegment()) return *this;
        else if (_reducer < 0 || _reducer > CharacterCount) return *this;

        return Remove(CharacterCount - _reducer, CharacterCount - 1);
    }

    string& Remove(int _begin, int _end)
    {
        if (IsSegment()) return *this;
        else if (!InRange(_begin, _end)) return *this;

        string accumulator;

        for (int i = 0; i < _begin; i++)
        {
            accumulator.Append((*this)[i]);
        }

        for (int i = _end + 1; i < CharacterCount; i++)
        {
            accumulator.Append((*this)[i]);
        }

        *this = accumulator;

        return *this;
    }

    string& RemoveAt(int _index, int _length = 1)
    {
        if (IsSegment()) return *this;
        else if (!InRange(_index)) return *this;
        else if (_length < 1) return *this;

        string accumulator;

        for (int i = 0; i < _index; i++)
        {
            accumulator.Append((*this)[i]);
        }

        for (int i = _index + _length; i < CharacterCount; i++)
        {
            accumulator.Append((*this)[i]);
        }

        *this = accumulator;

        return *this;
    }

	//removes the elements that match _value
    //[1, 25, 4, 3, 4, 6, 5, 2, 41, 4, 52, 7, 8, 9].RemoveAll(4) => [1, 25, 3, 6, 5, 2, 41, 52, 7, 8, 9]
    string RemoveAll(CodePoint _value)
    {
        if (IsSegment()) return *this;

        string accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] != _value)
            {
                accumulator.Append((*this)[i]);
            }
        }

        *this = accumulator;

        return *this;
    }

	//removes the elements that match an element elements of _set
    //[1, 2, 3, 4, 5, 6, 5, 2, 7, 8, 9].RemoveAll(2, 4, 5, 8) => [1, 3, 6, 7, 8, 9]
    string RemoveAll(const string& _set)
    {
        if (IsSegment()) return *this;

        string accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            if (!_set.Contains((*this)[i]))
            {
                accumulator.Append((*this)[i]);
            }
        }

        *this = accumulator;

        return *this;
    }

    string RemoveIf(const std::function<bool(CodePoint)>& _predicate)
    {
        if (IsSegment()) return *this;

        string accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            if (!_predicate((*this)[i]))
            {
                accumulator.Append((*this)[i]);
            }
        }

        *this = accumulator;

        return *this;
    }

    //[9, 2, 7].Repeat(2) => [9, 2, 7, 9, 2, 7, 9, 2, 7]
    string Repeat(int _times)
    {
        if (IsSegment()) return *this;

        int originalLength = CharacterCount;
        for (int n = 0; n < _times; n++)
        {
            for (int i = 0; i < originalLength; i++)
            {
                Append((*this)[i]);
            }
        }

        return *this;
    }

    //[5, 9, 0, 3, 7, 18, 4, 2, 6].Replace(4, 7, [2, 6, 1]) => [5, 9, 0, 3, 2, 6, 1, 6]
    string Replace(int _begin, int _end, const string& _replacement)
    {
        if (IsSegment()) return *this;
        else if (!InRange(_begin, _end)) return *this;

        Remove(_begin, _end);
        Insert(_replacement, _begin);

        return *this;
    }

	//replace every occurrence of _replaced with _replacement
    string& Replace(CodePoint _replaced, CodePoint _replacement)
    {
        if (IsSegment()) return *this;

        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] == _replaced)
            {
                Set(i, _replacement);
            }
        }

        return *this;
    }

	//replace every occurrence of _replaced with _replacement
    string& Replace(const string& _replaced, const string& _replacement)
    {
        if (IsSegment()) return *this;

        while (true)
        {
            int index = IndexOf(_replaced);

            if (index == - 1) break;

            RemoveAt(index, _replaced.CharacterCount);

            Insert(_replacement, index);
        }

        return *this;
    }

    //[9, 7, 2, 5, 9, 0, 6, 2, 8, 4].Reverse() => [4, 8, 2, 6, 0, 9, 5, 2, 7, 9]
    string& Reverse()
    {
        if (IsSegment()) return *this;

        for (int i = 0; i < CharacterCount / 2; i++)
        {
            Swap(i, (CharacterCount - i) - 1);
        }

        return *this;
    }

    //[1, 2, 3, 4, 5].RotateLeft(3) => [4, 5, 1, 2, 3]
    string& RotateLeft(int _positions = 1)
    {
        if (IsSegment()) return *this;
        else if (CharacterCount == 0) return *this;

        string accumulator = *this;
        string copy = *this;

        for (int n = 0; n < _positions; n++)
        {
            Set(accumulator.CharacterCount - 1, copy[0]);

            for (int i = 0; i < CharacterCount - 1; i++)
            {
                Set(i, copy[i + 1]);
            }

            copy = accumulator;
        }

        *this = accumulator;

        return *this;
    }

    //[1, 2, 3, 4, 5].RotateRight(3) => [3, 4, 5, 1, 2]
    string& RotateRight(int _positions = 1)
    {
        if (IsSegment()) return *this;
        else if (CharacterCount == 0) return *this;

        string accumulator = *this;
        string copy = *this;

        for (int n = 0; n < _positions; n++)
        {
            accumulator.Set(0, copy[copy.CharacterCount - 1]);

            for (int i = 1; i < CharacterCount; i++)
            {
                Set(i, copy[i - 1]);
            }

            copy = accumulator;
        }

        *this = accumulator;

        return *this;
    }

    string& Set(int _index, CodePoint _value)
    {
        if (IsSegment()) return *this;
        else if (count() == 0) return *this;
        else if (_index < 0 || _index >= count()) return *this;

        list<unsigned char> bytes = bytesOf(_value);

        unsigned char* array = new unsigned char[ByteCount + bytes.count()];

        Range<int> byteRange = byteRangeOf(_index);

        //copying (the bytes to the left of byteIndex)
        for (int i = 0; i < byteRange.begin(); i++)
        {
            array[i] = Elements[i];
        }

        //copying of &bytes
        for (int i = 0; i < bytes.count(); i++)
        {
            array[byteRange.begin() + i] = bytes[i];
        }

        //copying (the bytes after (byteIndex + bytes.count()))
        for (int i = byteRange.begin() + bytes.count(), n = 1; i < ByteCount + bytes.count(); i++, n++)
        {
            array[i] = Elements[byteRange.end() + n];
        }

        delete [] Elements;
        Elements = array;

        ByteCount += bytes.count() - byteRange.length();

        return *this;
    }

    string& Swap(int _index1, int _index2)
    {
        if (IsSegment()) return *this;
        else if (!InRange(_index1) || !InRange(_index2)) return *this;

        CodePoint element = (*this)[_index1];
        Set(_index1, (*this)[_index2]);
        Set(_index2, element);

        return *this;
    }

    //[2, 2, 2, 5, 9, 0, 6, 2, 2, 2, 2, 2].Trim(2) => [5, 9, 0, 6]
    string& Trim(CodePoint _value)
    {
        if (IsSegment()) return *this;

        TrimBegin(_value);
        TrimEnd(_value);

        return *this;
    }

    //[2, 2, 2, 5, 9, 0, 6, 2, 2, 2, 2, 2].TrimBegin(2) => [5, 9, 0, 6, 2, 2, 2, 2, 2]
    string& TrimBegin(CodePoint _value)
    {
        if (IsSegment()) return *this;

        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] != _value)
            {
                *this = Subrange(i, CharacterCount - 1);
                break;
            }
        }

        return *this;
    }

    //[2, 2, 2, 5, 9, 0, 6, 2, 2, 2, 2, 2].TrimEnd(2) => [2, 2, 2, 5, 9, 0, 6]
    string& TrimEnd(CodePoint _value)
    {
        if (IsSegment()) return *this;

        for (int i = CharacterCount - 1; i > - 1; i--)
        {
            if ((*this)[i] != _value)
            {
                *this = Subrange(0, i);
                break;
            }
        }

        return *this;
    }

    ///NON-MUTATING FUNCTIONS

    bool BeginsWith(const string& _value) const
    {
        int counter = 0;

        for (int i = 0; i < _value.CharacterCount; i++)
        {
            if ((*this)[i] == _value[i])
            {
                counter++;
            }
        }

        return _value.CharacterCount == counter;
    }

	//returns 'true' if &this begins with atleast one of the sequences in _value
    //[8, 2, 5, 10, 7, 15, 12, 9, 1].BeginsWith([[5, 9, 1], [8, 1, 5], [9, 12, 0]]) => false
    //[8, 2, 5, 10, 7, 15, 12, 9, 1].BeginsWith([[5, 9, 1], [8, 2, 5], [9, 12, 0]]) => true
    bool BeginsWith(const list<string>& _values) const
    {
        for (const string& __value : _values)
        {
            if (BeginsWith(__value))
            {
                return true;
            }
        }

        return false;
    }

	//returns copy of &this
    string Clone() const
    {
        return *this;
    }

    bool Contains(CodePoint _value) const
    {
        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] == _value)
            {
                return true;
            }
        }

        return false;
    }

    //[1, 2, 3, 4, 5, 6, 7, 8, 9].Contains([2, 3, 4]) => true
    bool Contains(const string& _value) const
    {
        int matches = 0;

        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] == _value[matches])
            {
                matches++;
            }
            else
            {
                matches = 0;
            }

            if (matches == _value.CharacterCount)
            {
                return true;
            }
        }

        return false;
    }

    bool Contains(const std::function<bool(CodePoint)>& _predicate) const
    {
        for (int i = 0; i < CharacterCount; i++)
        {
            if (_predicate((*this)[i]))
            {
                return true;
            }
        }

        return false;
    }

    bool ContainsAll(const string& _set) const
    {
        for (int i = 0; i < _set.CharacterCount; i++)
        {
            if (!(*this).Contains(_set[i]))
            {
                return false;
            }
        }

        return true;
    }

    //[9, 7, 3, 20, 15, 18, 4, 7].ContainsAny([21, 8, 5, 1]) => false
    //[9, 7, 3, 20, 15, 18, 4, 7].ContainsAny([6, 30, 3, 1]) => true
    bool ContainsAny(const list<CodePoint>& _set) const
    {
        for (int i = 0; i < CharacterCount; i++)
        {
            for (int n = 0; n < _set.count(); n++)
            {
                if ((*this)[i] == _set[n])
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool ContainsOnly(CodePoint _value) const
    {
        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] != _value)
            {
                return false;
            }
        }

        return true;
    }

    //[9, 1, 0, 3, 1, 5, 9, 1, 15, 3, 7, 5, 9, 1, 1].ContainsOnly([1, 9, 10]) => false
    //[9, 1, 0, 3, 1, 5, 9, 1, 15, 3, 7, 5, 9, 1, 1].ContainsOnly([5, 9, 1, 0, 7, 3, 15]) => true
    bool ContainsOnly(const list<CodePoint>& _set) const
    {
        if (CharacterCount == 0) return false;

        for (int i = 0; i < CharacterCount; i++)
        {
            if (!_set.Contains((*this)[i]))
            {
                return false;
            }
        }

        return true;
    }

    bool ContainsOnly(const std::function<bool(CodePoint)>& _predicate) const
    {
        if (CharacterCount == 0) return false;

        for (int i = 0; i < CharacterCount; i++)
        {
            if (!_predicate((*this)[i]))
            {
                return false;
            }
        }

        return true;
    }

    int CountOf(CodePoint _value) const
    {
        int accumulator = 0;

        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] == _value)
            {
                accumulator++;
            }
        }

        return accumulator;
    }

    //[5, 9, 1, 0, 3, 5, 9, 1, 4, 5, 9, 1, 10, 15, 3, 7, 5, 9, 1, 1].CountOf([5, 9, 1]) => 4
    //[5, 9, 1, 0, 3, 5, 9, 1, 4, 5, 9, 1, 10, 15, 3, 7, 5, 9, 1, 1].CountOf([5, 9, 1, 7]) => 0
    int CountOf(const string& _value) const
    {
        if (_value.count() == 0) return 0;

        int count = 0;

        for (int i = 0; i < CharacterCount; i++)
        {
            if (Subrange(i, (i + _value.CharacterCount) - 1) == _value)
            {
                i += _value.CharacterCount - 1;
                count++;
            }
        }

        return count;
    }

    int CountOf(const std::function<bool(CodePoint)>& _predicate) const
    {
        int count = 0;

        for (int i = 0; i < CharacterCount; i++)
        {
            if (_predicate((*this)[i]))
            {
                count++;
            }
        }

        return count;
    }

    //[7, 8, 3, 19, 20, 71, 15, 71, 3, 31, 108, 3]).Duplicates() => [3, 71]
    string Duplicates() const
    {
        string accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            for (int n = i + 1; n < CharacterCount; n++)
            {
                if ((*this)[i] == (*this)[n] && !accumulator.Contains((*this)[i]))
                {
                    accumulator.Append((*this)[i]);
                }
            }
        }

        return accumulator;
    }

    bool EndsWith(const string& _value) const
    {
        int counter = 0;
        for (int i = CharacterCount - 1, n = _value.CharacterCount - 1; (i > - 1) && (n > - 1); i--, n--)
        {
            if ((*this)[i] == _value[n])
            {
                counter++;
            }
        }

        return _value.CharacterCount == counter;
    }

    bool EndsWithWith(const list<string>& _values) const
    {
        for (const string& __value : _values)
        {
            if (EndsWith(__value))
            {
                return true;
            }
        }

        return false;
    }

    //[2, 9, 0, 1, 4, 9, 7, 3].Except(9) => [2, 0, 1, 4, 7, 3]
    string Except(CodePoint _value) const
    {
        string accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] != _value)
            {
                accumulator.Append((*this)[i]);
            }
        }

        return accumulator;
    }

    //[2, 9, 0, 1, 4, 9, 7, 3].Except([9, 7, 0]) => [2, 1, 4, 3]
    string Except(const list<CodePoint>& _set) const
    {
        string accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            if (!_set.Contains((*this)[i]))
            {
                accumulator.Append((*this)[i]);
            }
        }

        return accumulator;
    }

    string Except(const std::function<bool(CodePoint)>& _predicate) const
    {
        string accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            if (!_predicate((*this)[i]))
            {
                accumulator.Append((*this)[i]);
            }
        }

        return accumulator;
    }

    bool HasDuplicates() const
    {
        for (int i = 0; i < CharacterCount; i++)
        {
            for (int n = 0; n < CharacterCount; n++)
            {
                if ((*this)[i] == (*this)[n])
                {
                    return true;
                }
            }
        }

        return false;
    }

    int IndexOf(CodePoint _value, int _begin = 0) const
    {
        if (!InRange(_begin)) return -1;

        for (int i = _begin; i < CharacterCount; i++)
        {
            if ((*this)[i] == _value)
            {
                return i;
            }
        }

        return - 1;
    }

    int IndexOf(const string& _value, int _begin = 0) const
    {
        if (!InRange(_begin)) return -1;

        for (int i = _begin, matches = 0; i < CharacterCount && matches < _value.count(); i++)
        {
            if ((*this)[i] == _value[matches])
            {
                matches++;
            }
            else
            {
                i -= matches;
                matches = 0;
            }

            if (matches == _value.CharacterCount)
            {
                return (i - _value.CharacterCount) + 1;
            }
        }

        return -1;
    }

    int IndexOf(const std::function<bool(CodePoint)>& _predicate, int _begin = 0) const
    {
        if (!InRange(_begin)) return -1;

        for (int i = _begin; i < CharacterCount; i++)
        {
            if (_predicate((*this)[i]))
            {
                return i;
            }
        }

        return - 1;
    }

    int IndexOfAny(const list<CodePoint>& _set, int _begin = 0) const
    {
        if (!InRange(_begin)) return -1;

        for (int i = _begin; i < CharacterCount; i++)
        {
            for (int n = 0; n < _set.count(); n++)
            {
                if ((*this)[i] == _set[n])
                {
                    return i;
                }
            }
        }

        return - 1;
    }

    int IndexOfNot(const std::function<bool(CodePoint)>& _predicate, int _begin = 0) const
    {
        if (!InRange(_begin)) return -1;

        for (int i = _begin; i < CharacterCount; i++)
        {
            if (!_predicate((*this)[i]))
            {
                return i;
            }
        }

        return - 1;
    }

	//_begin is outside the range of list => -2
    //[].IndexOf(4) => -1
    //[9, 9, 9, 5, 8, 10, 2, 7].IndexOfNot(9) => 3
	//[9, 9, 9, 5, 8, 10, 2, 7].IndexOfNot(4) => 0
    int IndexOfNot(CodePoint _value, int _begin = 0) const
    {
        if (!InRange(_begin)) return -2;

        for (int i = _begin; i < CharacterCount; i++)
        {
            if ((*this)[i] != _value)
            {
                return i;
            }
        }

        return - 1;
    }

    int LastIndexOf(CodePoint _value) const
    {
        for (int i = CharacterCount - 1; i > - 1; i--)
        {
            if ((*this)[i] == _value)
            {
                return i;
            }
        }

        return -1;
    }

    int LastIndexOf(const string& _value) const
    {
        int index = - 1;

        while (true)
        {
            int index_ = IndexOf(_value, index + _value.CharacterCount);

            if (index_ == - 1)
            {
                return index;
            }
            else
            {
                index = index_;
            }
        }
    }

    int LastIndexOf(const std::function<bool(CodePoint)>& _predicate) const
    {
        for (int i = CharacterCount - 1; i > - 1; i--)
        {
            if (_predicate((*this)[i]))
            {
                return i;
            }
        }

        return - 1;
    }

	//returns only values that are (between the beginning and a separator), (between separator and the end) or (between two separators)
	//empty sequences are generated (and eventually are appended to the result) only if they are between two separators
	//_ignoreEmptyValues = true -> empty sequences (if there are any) are not appended to the result 
    //[41, 56, 3, 7, 18, 5, 19, 76, 15].Multisplit([353, 12]) => [[41, 56, 3, 7, 18, 5, 19, 76, 15]]
    //[41, 56, 3, 7, 18, 5, 19, 76, 15, 9, 20, 5].Multisplit([56, 9]) => [[41], [3, 7, 18, 5, 19, 76, 15], [20, 5]]
    //[9, 41, 56, 3, 7, 18, 5, 19, 76, 15, 9, 9, 20, 7].Multisplit([7, 9]) => [[41, 56, 3], [18, 5, 19, 76, 15], [], [20]]
    //[9, 41, 56, 3, 7, 18, 5, 19, 76, 15, 9, 9, 20, 7].Multisplit([7, 9], true) => [[41, 56, 3], [18, 5, 19, 76, 15], [20]]
    list<string> Multisplit(const list<CodePoint>& _set, bool _ignoreEmptyValues = false) const
    {
        list<string> accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            bool match = _set.Contains((*this)[i]);
            int index = IndexOf([&](auto _e){ return _set.Contains(_e); }, i + 1);

            //[separator, separator]
            if (match && index == i + 1 && !_ignoreEmptyValues)
            {
                accumulator.Append(string {});
            }
            //[!separator...separator]
            else if (!match && index >= i + 1)
            {
                accumulator.Append(Subrange(i, index - 1));
                i = index - 1;
            }
            //[!separator...]
            else if (!match && index == - 1)
            {
                accumulator.Append(Subrange(i, CharacterCount - 1));
                break;
            }
        }

        return accumulator;
    }

	//returns the range of a sequence consisting of certain set of values (it is not mandatory for the sequence to contain each value in the set)
    //[3, 10, 15, 12, 8, 5, 7, 5, 5, 7, 7, 3, 9].RangeOf([2, 5, 7]) => (5, 10)
    //[3, 10, 15, 12, 8, 5, 7, 2, 2, 7, 7, 3, 9].RangeOf([2, 5, 7]) => (5, 10)
    //[3, 10, 15, 12, 0, 5, 7, 2, 2, 7, 7, 3, 9].RangeOf([4, 0, 1]) => (4, 4)
    //[3, 10, 15, 12, 8, 5, 7, 2, 2, 7, 7, 3, 9].RangeOf([4, 0, 1]) => (-1, -1)
    Range<int> RangeOf(const list<CodePoint>& _set, int _sindex = 0) const
    {
        if (!InRange(_sindex)) return {};

        for (int i = _sindex, n = - 1; i < CharacterCount; i++)
        {
            bool equality = _set.Contains((*this)[i]);

            if (n == - 1 && equality)
            {
                n = i;
            }
            else if (n > - 1 && !equality)
            {
                return Range<int>(n, i - 1);
            }
            else if (n > - 1 && i == CharacterCount - 1)
            {
                return Range<int>(n, i);
            }
        }

        return { - 1, - 1 };
    }

	//returns the range of a sequence not consisting of certain set of values (it is mandatory for the sequence to not contain any of the values in the set)
    //[5, 7, 5, 5, 7, 7, 3, 10, 15, 12, 8, 2, 9].RangeOfNot([2, 5, 7]) => (6, 10)
    //[3, 10, 15, 12, 8, 5, 7, 2, 2, 7, 7, 3, 9].RangeOfNot([2, 5, 7]) => (0, 4)
    //[5, 7, 2, 2, 7, 7, 5, 4, 2, 7, 5].RangeOfNot([2, 5, 7]) => (7, 7)
    //[4, 0, 0, 1, 1, 4, 0, 1, 4, 4, 1].RangeOfNot([4, 0, 1]) => (-1, -1)
    Range<int> RangeOfNot(const list<CodePoint>& _set, int _sindex = 0) const
    {
        if (!InRange(_sindex)) return {};

        for (int i = _sindex, n = - 1; i < CharacterCount; i++)
        {
            bool equality = _set.Contains(Elements[i]);

            if (n == - 1 && !equality)
            {
                n = i;
            }
            else if (n > - 1 && equality)
            {
                return Range<int>(n, i - 1);
            }
            else if (n > - 1 && i == CharacterCount - 1)
            {
                return Range<int>(n, i);
            }
        }

        return { -1, -1 };
    }

	//returns only values that are (between the beginning and a separator), (between separator and the end) or (between two separators)
	//empty sequences are generated (and eventually are appended to the result) only if they are between two separators
	//_ignoreEmptyValues = true -> empty sequences (if there are any) are not appended to the result 
    //[3, 7, 18, 5, 19, 76, 15].Split(353) => [[3, 7, 18, 5, 19, 76, 15]]
    //[18, 5, 19, 76, 15, 9, 20, 5].Split(9) => [[18, 5, 19, 76, 15], [20, 5]]
    //[56, 3, 7, 18, 5, 19, 76, 7].Split(7) => [[56, 3], [18, 5, 19, 76]]
    //[56, 7, 7, 18, 5, 19, 76, 15, 9].Split(7) => [[56], [], [18, 5, 19, 76, 15, 9]]
    //[56, 7, 7, 18, 5, 19, 76, 15, 9].Split(7, true) => [[56], [18, 5, 19, 76, 15, 9]]
    //[7, 41, 56, 7, 18, 76, 15, 9, 7].Split(7) => [[41, 56], [18, 76, 15, 9]]
    //[7, 41, 56, 7, 7, 7, 18, 5, 15].Split(7) => [[41, 56], [], [], [18, 5, 15]]
    list<string> Split(CodePoint _separator, bool _ignoreEmptyValues = false) const
    {
        list<string> accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            bool match = (*this)[i] == _separator;
            int index = IndexOf(_separator, i + 1);

            //[separator, separator]
            if (match && index == i + 1 && !_ignoreEmptyValues)
            {
                accumulator.Append(string {});
            }
                //[!separator...separator]
            else if (!match && index >= i + 1)
            {
                accumulator.Append(Subrange(i, index - 1));
                i = index - 1;
            }
                //[!separator...]
            else if (!match && index == - 1)
            {
                accumulator.Append(Subrange(i, CharacterCount - 1));
                break;
            }
        }

        return accumulator;
    }

	//returns only values that are (between the beginning and a separator), (between separator and the end) or (between two separators)
	//empty sequences are generated (and eventually are appended to the result) only if they are between two separators
	//_ignoreEmptyValues = true -> empty sequences (if there are any) are not appended to the result 
    //[41, 56, 3, 5, 7, 18, 5, 19, 76, 15].Split([3, 8]) => [[41, 56, 3, 5, 7, 18, 5, 19, 76, 15]]
    //[41, 56, 3, 5, 7, 18, 5, 19, 9, 7, 76, 15, 9].Split([9, 7]) => [[41, 56, 3, 5, 7, 18, 5, 19], [76, 15, 9]]
    //[41, 56, 3, 9, 7, 18, 5, 19, 76, 15, 9, 20, 9, 7].Split([9, 7]) => [[41, 56, 3], [18, 5, 19, 76, 15, 9, 20]]
    //[41, 56, 9, 7, 9, 7, 18, 5, 19, 76, 15, 9, 20, 3].Split([9, 7]) => [[41, 56], [], [18, 5, 19, 76, 15, 9, 20, 3]]
    //[41, 56, 9, 7, 9, 7, 18, 5, 19, 76, 15, 9, 20, 3].Split([9, 7], true) => [[41, 56], [18, 5, 19, 76, 15, 9, 20, 3]]
    //[9, 7, 41, 56, 9, 9, 7, 18, 76, 15, 9, 20, 3, 9, 7].Split([9, 7]) => [[41, 56, 9], [18, 76, 15, 9, 20, 3]]
    //[9, 7, 41, 56, 9, 7, 9, 7, 9, 7, 18].Split([9, 7]) => [[41, 56], [], [], [18]]
    list<string> Split(const string& _separator, bool _ignoreEmptyValues = false) const
    {
        list<string> accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            bool match = string(*this, i, i + _separator.CharacterCount - 1) == _separator;
            int index = IndexOf(_separator, i + 1);

            //[separator, separator]
            if (match && index == i + _separator.CharacterCount && !_ignoreEmptyValues)
            {
                accumulator.Append(string {});
                i = index - 1;
            }
            //[separator, separator]
            else if (match && index == i + _separator.CharacterCount && _ignoreEmptyValues)
            {
                i = index - 1;
            }
            //[!separator...separator]
            else if (!match && index >= i)
            {
                accumulator.Append(Subrange(i, index - 1));
                i = index - 1;
            }
            //[!separator...]
            else if (!match && index == - 1)
            {
                accumulator.Append(Subrange(i, CharacterCount - 1));
                break;
            }
            //[separator, value, separator] 
            else if (match && (index > i + _separator.CharacterCount || index == - 1))
            {
                i += _separator.CharacterCount - 1;
            }
            //[...separator]
            else if (match && index == - 1)
            {
                break;
            }
        }

        return accumulator;
    }

	//returns only values that are (between the beginning and a separator), (between separator and the end) or (between two separators)
	//empty sequences are generated (and eventually are appended to the result) only if they are between two separators
	//_ignoreEmptyValues = true -> empty sequences (if there are any) are not appended to the result 
    //[3, 7, 18, 5, 19, 76, 15].Split([](int x) { return x == 353; }) => [[3, 7, 18, 5, 19, 76, 15]]
    //[18, 5, 19, 76, 15, 9, 20, 5].Split([](int x) { return x == 9; }) => [[18, 5, 19, 76, 15], [20, 5]]
    //[56, 3, 7, 18, 5, 19, 76, 7].Split([](int x) { return x == 7; }) => [[56, 3], [18, 5, 19, 76]]
    //[56, 7, 7, 18, 5, 19, 76, 15, 9].Split([](int x) { return x == 7; }) => [[56], [], [18, 5, 19, 76, 15, 9]]
    //[56, 7, 7, 18, 5, 19, 76, 15, 9].Split([](int x) { return x == 7; }, true) => [[56], [18, 5, 19, 76, 15, 9]]
    //[7, 41, 56, 7, 18, 76, 15, 9, 7].Split([](int x) { return x == 7; }) => [[41, 56], [18, 76, 15, 9]]
    //[7, 41, 56, 7, 7, 7, 18, 5, 15].Split([](int x) { return x == 7; }) => [[41, 56], [], [], [18, 5, 15]]
    list<string> Split(const std::function<bool(CodePoint)>& _predicate, bool _ignoreEmptyValues = false) const
    {
        list<string> accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            bool match = _predicate((*this)[i]);
            int index = IndexOf(_predicate, i + 1);

            //[separator, separator]
            if (match && index == i + 1 && !_ignoreEmptyValues)
            {
                accumulator.Append(string {});
            }
            //[!separator...separator]
            else if (!match && index >= i + 1)
            {
                accumulator.Append(Subrange(i, index - 1));
                i = index - 1;
            }
            //[!separator...]
            else if (!match && index == - 1)
            {
                accumulator.Append(Subrange(i, CharacterCount - 1));
                break;
            }
        }

        return accumulator;
    }

    //_length = 0 => [_begin..]
    //(_begin + _length) > characterCount() => {}
    string Sublist(int _begin, int _length = 0) const
    {
        if (!InRange(_begin)) return {};

        string accumulator;

        int end = _length == 0 ? CharacterCount : _begin + _length;
        for (int i = _begin; i < end; i++)
        {
            accumulator.Append((*this)[i]);
        }

        return accumulator;
    }

    //[5, 8, 4, 1, 9, 6, 2, 3, 0, 5, 5, 1, 7].Subrange(2, 5) => [4, 1, 9, 6]
    string Subrange(int _begin, int _end) const
    {
        if (!InRange(_begin, _end)) return {};

        string accumulator;

        for (int i = _begin; i < _end + 1; i++)
        {
            accumulator.Append((*this)[i]);
        }

        return accumulator;
    }

    string Where(const std::function<bool(CodePoint)>& _predicate) const
    {
        string accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            if (_predicate((*this)[i]))
            {
                accumulator.Append((*this)[i]);
            }
        }

        return accumulator;
    }

    string Until(CodePoint _value) const
    {
        string accumulator;

        for (int i = 0; i < CharacterCount; i++)
        {
            if ((*this)[i] != _value)
            {
                accumulator.Append((*this)[i]);
            }
            else
            {
                return accumulator;
            }
        }

        return accumulator;
    }

    ///OTHER FUNCTIONS

    //*this == "true" | "false" ->
    bool ToBool() const
    {
        return *this == "true";
    }

    static string FromBool(bool _value)
    {
        return _value ? "true" : "false";
    }

    //the value of the number is outside the valid range for (long long) => incorrect value
	//the string is valid decimal value in the valid range for (long long) ->
    long long ToInteger(BINARY_, BitOrder _bitOrder) const
    {
        long long result = 0;
        int multiplier = 1;

        if (_bitOrder == BitOrder::LSB0)
        {
            for (int i = 0; i < CharacterCount; i++)
            {
                result += ((*this)[i] == '1') * multiplier;
                multiplier *= 2;
            }
        }
        else
        {
            for (int i = CharacterCount - 1; i > -1; i--)
            {
                result += ((*this)[i] == '1') * multiplier;
                multiplier *= 2;
            }
        }

        return result;
    }

	//the value of the number is outside the valid range for (long long) => incorrect value
    //the string is valid decimal value in the valid range for (long long) ->
    long long ToInteger(DECIMAL_) const
    {
        bool isPositive = (*this)[0] != '-';
        long long result = 0;
        long long multiplier = 1;

        for (int i = CharacterCount - 1; i > (isPositive ? - 1 : 0); i--)
        {
            int digit = (*this)[i] - '0';
            result += digit * multiplier;
            multiplier *= 10;
        }

        return isPositive ? result : -result;
    }

	//the value of the number is outside the valid range for (unsigned long long) => incorrect value
	//the string is valid decimal value in the valid range for (unsigned long long) ->
    unsigned long long ToIntegerU(DECIMAL_) const
    {
        unsigned long long result = 0;
        unsigned long long multiplier = 1;

        for (int i = CharacterCount - 1; i > - 1; i--)
        {
            int digit = (*this)[i] - '0';
            result += digit * multiplier;
            multiplier *= 10;
        }

        return result;
    }

	//the value of the number is outside the valid range for (unsigned long long) => incorrect value
	//the string is valid hexadecimal value in the valid range for (unsigned long long) ->
    long long ToInteger(HEX_) const
    {
        long long result = 0;

        for (int i = CharacterCount - 1, n = 0; i > - 1; i--, n++)
        {
            char _character = (*this)[i];

            if (_character == '1')
            {
                result += numeric::Pow(16, n);
            }
            else if (_character == '2')
            {
                result += 2 * numeric::Pow(16, n);
            }
            else if (_character == '3')
            {
                result += 3 * numeric::Pow(16, n);
            }
            else if (_character == '4')
            {
                result += 4 * numeric::Pow(16, n);
            }
            else if (_character == '5')
            {
                result += 5 * numeric::Pow(16, n);
            }
            else if (_character == '6')
            {
                result += 6 * numeric::Pow(16, n);
            }
            else if (_character == '7')
            {
                result += 7 * numeric::Pow(16, n);
            }
            else if (_character == '8')
            {
                result += 8 * numeric::Pow(16, n);
            }
            else if (_character == '9')
            {
                result += 9 * numeric::Pow(16, n);
            }
            else if (_character == 'A')
            {
                result += 10 * numeric::Pow(16, n);
            }
            else if (_character == 'B')
            {
                result += 11 * numeric::Pow(16, n);
            }
            else if (_character == 'C')
            {
                result += 12 * numeric::Pow(16, n);
            }
            else if (_character == 'D')
            {
                result += 13 * numeric::Pow(16, n);
            }
            else if (_character == 'E')
            {
                result += 14 * numeric::Pow(16, n);
            }
            else if (_character == 'F')
            {
                result += 15 * numeric::Pow(16, n);
            }
        }

        return result;
    }

    //_number < 1 quadrillion ->
    static string FromInteger(long long _number)
    {
        if (_number == 0) return "0";

        string accumulator;
        double f = _number > 0 ? _number : numeric::Abs(_number); 

        while (f > 0.9)
        {
            f /= 10.0; /

            double rounded = numeric::RoundDown(f); 

            double digit_f = f - rounded; 

            digit_f = numeric::RoundToNearest(digit_f * 10.0); 

            f = rounded;

            char digit_i = digit_f + '0';

            accumulator += digit_i;
        }

        if (_number < 0)
        {
            accumulator.Insert('-', 0);
        }

        return accumulator.Reverse();
    }

    float ToFloat() const
    {
        bool isPositive = (*this)[0] != '-';

        int indexOfDot = IndexOf('.');
        int whole = string(Subrange(isPositive ? 0 : 1, indexOfDot - 1)).ToInteger(DECIMAL_A);
        string fractional = string(Sublist(indexOfDot + 1)); 

        if (fractional.ContainsOnly('0')) return whole;

        float fractional_ = string(fractional.Sublist(fractional.IndexOfNot('0'))).ToInteger(DECIMAL_A); 

        for (int i = 0; i < fractional.CharacterCount; i++)
        {
            fractional_ /= 10;
        }

        while (fractional_ >= 1.0)
        {
            fractional_ /= 10.0;
        }

        if (isPositive)
        {
            return whole + fractional_;
        }
        else
        {
            return - (whole + fractional_);
        }
    }

    double ToDouble() const
    {
        bool isPositive = (*this)[0] != '-';

        int indexOfDot = IndexOf('.');
        int whole = string(Subrange(isPositive ? 0 : 1, indexOfDot - 1)).ToInteger(DECIMAL_A);
        string fractional = string(Sublist(indexOfDot + 1)); //(п:А) => "0000291"

        if (fractional.ContainsOnly('0')) return whole;

        double fractional_ = string(fractional.Sublist(fractional.IndexOfNot('0'))).ToInteger(DECIMAL_A); 

        for (int i = 0; i < fractional.CharacterCount; i++)
        {
            fractional_ /= 10;
        }

        while (fractional_ >= 1.0)
        {
            fractional_ /= 10.0;
        }

        if (isPositive)
        {
            return whole + fractional_;
        }
        else
        {
            return - (whole + fractional_);
        }
    }

    //the current value of the string contains only ASCII characters ->
    const char* ToASCII() const
    {
        char* result = new char[ByteCount + 1];

        for (int i = 0; i < ByteCount; i++)
        {
            //if the storage format is UTF-8 and the character is encoded by one byte
            if (StorageEncoding == UTF8 && (Elements[i] >> 7) == 0b0)
            {
                result[i] = Elements[i];
            }
            //if the storage format is UTF-16LE
            else if (StorageEncoding == UTF16LE)
            {
                result[i] = Elements[i * 2];
            }
            //if the storage format is UTF-16BE and the character is part of BMP
            else if (StorageEncoding == UTF16BE)
            {
                result[i] = Elements[(i * 2) + 1];
            }
            //if the storage format is UTF-32LE
            else if (StorageEncoding == UTF32LE)
            {
                result[i] = Elements[i * 4];
            }
            //if the storage format is UTF-32BE
            else if (StorageEncoding == UTF32BE)
            {
                result[i] = Elements[(i * 4) + 3];
            }
        }

        result[CharacterCount] = '\0';

        return result;
    } // -> delete []

    //returns a list of UTF-32 characters
    //the string does not contain composite characters ->
    const char32_t* ToChar32() const
    {
		char32_t* result = new char32_t[CharacterCount + 1/*for the terminating character*/];
            
		int n = 0; 

        for (int i = 0, n = 0; i < ByteCount; )
        {
            //if the storage format is UTF-8 and the character is encoded by one byte
            if (StorageEncoding == UTF8 && (Elements[i] >> 7) == 0b0)
            {
				result[n++] = Elements[i];
                i += 1;
            }
            //if the storage format is UTF-8 and the character is encoded by two bytes
            else if (StorageEncoding == UTF8 && (Elements[i] >> 5) == 0b110)
            {
				result[n++] = ToUTF32(Elements[i], Elements[i + 1]);
                i += 2;
            }
            //if the storage format is UTF-8 and the character is encoded by three bytes
            else if (StorageEncoding == UTF8 && (Elements[i] >> 4) == 0b1110)
            {
				result[n++] = ToUTF32(Elements[i], Elements[i + 1], Elements[i + 2]);
                i += 3;
            }
            //if the storage format is UTF-8 and the character is encoded by four bytes
            else if (StorageEncoding == UTF8 && (Elements[i] >> 3) == 0b11110)
            {
				result[n++] = ToUTF32(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3]);
                i += 4;
            }
            //if the storage format is UTF-16LE and the character is part of BMP
            else if (StorageEncoding == UTF16LE && IsBMP(_16(Elements[i], Elements[i + 1], LE)))
            {
				result[n++] = _16(Elements[i], Elements[i + 1], LE);
                i += UTF16_CODE_UNIT_LENGTH;
            }
            //if the storage format is UTF-16BE and the character is part of BMP
            else if (StorageEncoding == UTF16BE && IsBMP(_16(Elements[i], Elements[i + 1], BE)))
            {
				result[n++] = _16(Elements[i], Elements[i + 1], BE);
                i += UTF16_CODE_UNIT_LENGTH;
            }
                //(STATE) the character is not part of BMP
                //if the storage format is UTF-16LE and the character is not part of BMP
            else if (StorageEncoding == UTF16LE)
            {
                utf16 highSurrogate = _16(Elements[i], Elements[i + 1], LE);
                utf16 lowSurrogate = _16(Elements[i + 2], Elements[i + 3], LE);
				result[n++] = ToUTF32(highSurrogate, lowSurrogate);
                i += UTF16_CODE_UNIT_LENGTH * 2;
            }
            //if the storage format is UTF-16BE and the character is not part of BMP
            else if (StorageEncoding == UTF16BE)
            {
                utf16 highSurrogate = _16(Elements[i], Elements[i + 1], BE);
                utf16 lowSurrogate = _16(Elements[i + 2], Elements[i + 3], BE);
				result[n++] = ToUTF32(highSurrogate, lowSurrogate);
                i += UTF16_CODE_UNIT_LENGTH * 2;
            }
            //(END-STATE)
            //if the storage format is UTF-32LE
            else if (StorageEncoding == UTF32LE)
            {
				result[n++] = _32(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3], LE);
                i += UTF32_CODE_UNIT_LENGTH;
            }
            //if the storage format is UTF-32BE
            else if (StorageEncoding == UTF32BE)
            {
				result[n++] = _32(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3], BE);
                i += UTF32_CODE_UNIT_LENGTH;
            }
        }

        result[n] = '\0';

        return result;
    } // -> delete []

    //the string does not contain composite characters ->
    const wchar_t* ToWide() const
    {
        list<wchar_t> result; //as the number of the code units is not known (without calculation), t:list must be used instead of wchar_t*

        result.ReleaseMode = ReleaseMode::FUTURE; //because &result->Elements is the return value

        for (int i = 0; i < ByteCount; )
        {
            //if the storage format is UTF-8 and the character is encoded by one byte
            if (StorageEncoding == UTF8 && (Elements[i] >> 7) == 0b0)
            {
                result.Append(Elements[i]);
                i += 1;
            }
                //if the storage format is UTF-8 and the character is encoded by two bytes
            else if (StorageEncoding == UTF8 && (Elements[i] >> 5) == 0b110)
            {
                result.Append(ToUTF16(Elements[i], Elements[i + 1]));
                i += 2;
            }
                //if the storage format is UTF-8 and the character is encoded by three bytes
            else if (StorageEncoding == UTF8 && (Elements[i] >> 4) == 0b1110)
            {
                result.Append(ToUTF16(Elements[i], Elements[i + 1], Elements[i + 2]));
                i += 3;
            }
                //if the storage format is UTF-8 and the character is encoded by four bytes
            else if (StorageEncoding == UTF8 && (Elements[i] >> 3) == 0b11110)
            {
                CodePoint codePoint = ToCodePoint(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3]);
                t2<utf16, utf16> surrogatePair = GetSurrogatePair(codePoint);
                result.Append(surrogatePair.e1());
                result.Append(surrogatePair.e2());
                i += 4;
            }
                //if the storage format is UTF-16LE and the character is part of BMP
            else if (StorageEncoding == UTF16LE && IsBMP(_16(Elements[i], Elements[i + 1], LE)))
            {
                result.Append(_16(Elements[i], Elements[i + 1], LE));
                i += UTF16_CODE_UNIT_LENGTH;
            }
                //if the storage format is UTF-16BE and the character is part of BMP
            else if (StorageEncoding == UTF16BE && IsBMP(_16(Elements[i], Elements[i + 1], BE)))
            {
                result.Append(_16(Elements[i], Elements[i + 1], BE));
                i += UTF16_CODE_UNIT_LENGTH;
            }
                //(STATE) the character is not part of BMP
                //if the storage format is UTF-16LE and the character is not part of BMP
            else if (StorageEncoding == UTF16LE)
            {
                utf16 highSurrogate = _16(Elements[i], Elements[i + 1], LE);
                utf16 lowSurrogate = _16(Elements[i + 2], Elements[i + 3], LE);
                result.Append(highSurrogate);
                result.Append(lowSurrogate);
                i += UTF16_CODE_UNIT_LENGTH * 2;
            }
                //if the storage format is UTF-16BE and the character is not part of BMP
            else if (StorageEncoding == UTF16BE)
            {
                utf16 highSurrogate = _16(Elements[i], Elements[i + 1], BE);
                utf16 lowSurrogate = _16(Elements[i + 2], Elements[i + 3], BE);
                result.Append(highSurrogate);
                result.Append(lowSurrogate);
                i += UTF16_CODE_UNIT_LENGTH * 2;
            }
                //(END-STATE)
                //if the storage format is UTF-32LE
            else if (StorageEncoding == UTF32LE)
            {
                CodePoint codePoint = _32(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3], LE);

                if (IsBMP(codePoint))
                {
                        result.Append(codePoint);
                }
                else
                {
                    t2<utf16, utf16> surrogatePair = GetSurrogatePair(codePoint);
                    result.Append(surrogatePair.e1());
                    result.Append(surrogatePair.e2());
                }

                i += 4;
            }
                //if the storage format is UTF-32BE
            else if (StorageEncoding == UTF32BE)
            {
                CodePoint codePoint = _32(Elements[i], Elements[i + 1], Elements[i + 2], Elements[i + 3], BE);

                if (IsBMP(codePoint))
                {
                    result.Append(codePoint);
                }
                else
                {
                    t2<utf16, utf16> surrogatePair = GetSurrogatePair(codePoint);
                    result.Append(surrogatePair.e1());
                    result.Append(surrogatePair.e2());
                }

                i += 4;
            }
        }

        result.Append('\0');

        return result.elements();
    } // -> delete []

    list<char> ToBytes() const
    {
        list<char> accumulator;

        for (int i = 0; i < ByteCount; i++)
        {
            accumulator.Append(Elements[i]);
        }

        return accumulator;
    }

    ///

	void extend(int _size)
	{
		Size = _size;

		unsigned char* oldElements = Elements;

		Elements = new unsigned char[Size];

		for (int i = 0; i < ByteCount; i++)
		{
			Elements[i] = oldElements[i];
		}

		delete[] oldElements;
	}
};

//the value of _string contains only ASCII characters ->
void print(const string& _string)
{
    const char* value = _string.ToASCII();
    std::cout << value;
    delete [] value;
}
