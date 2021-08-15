// This file contains low-level functions for manipulation of byte arrays

    //These two values are defined in minwindef.h
    //FALSE = 0
    //TRUE = 1

    ///NON-MUTATING FUNCTIONS

    //_length1 specifies the length of _array1
    //_length2 specifies the length of _array2
    //equality(nullptr, nullptr, x, x) => TRUE
    //equality([5, 0, 9], [5, 0, 9, 5], 3, 4) => FALSE
    //equality([5, 0, 9], [6, 4, 1], 3, 3) => FALSE
    //equality([5, 0, 9], [5, 9, 0], 3, 3) => FALSE
    //equality([5, 0, 9], [5, 0, 9], 3, 3) => TRUE
    int equality(const char* const _array1, const char* const _array2, int _length1, int _length2)
    {
        if (_array1 == _array2) return TRUE;
        else if (_array1 == nullptr && _array2 != nullptr) return FALSE;
        else if (_array1 != nullptr && _array2 == nullptr) return FALSE;
        else if (_length1 != _length2) return FALSE;

        //(S) both arrays are non-null and have the same length

        for (int i = 0; i < _length1; i ++)
        {
            if (_array1[i] != _array2[i])
            {
                return FALSE;
            }
        }
    }

    //_length specifies the length of _array
    //_array = nullptr | the specified value does not exist => -1
    //_length < 1 => -2
    int indexOf(const char* const _array, int _length, char _value)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;

        for (int i = 0; i < _length; i ++)
        {
            if (_array[i] == _value)
            {
                return i;
            }
        }

        return -1;
    }

    //_length specifies the length of _array
    //_array = nullptr => -1
    //_length < 1 => -2
    //indexOfNot([9, 9, 9, 5, 8, 10, 2, 7], 8, 9) => 3
    //indexOfNot([9, 9, 9, 5, 8, 10, 2, 7], 8, 4) => 0
    int indexOfNot(const char* const _array, int _length, char _value)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;

        for (int i = 0; i < _length; i++)
        {
            if (_array[i] != _value)
            {
                return i;
            }
        }

        return -1;
    }

    //_length specifies the length of _array
    //_array = nullptr | the specified value does not exist => -1
    //_length < 1 => -2
    int lastIndexOf(const char* const _array, int _length, char _value)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;

        for (int i = _length - 1; i > -1; i--)
        {
            if (_array[i] == _value)
            {
                return i;
            }
        }

        return -1;
    }

    ///MUTATING FUNCTIONS 

    //it copies segment (from _source to _destination) (beginning at _sourceBegin) and (with length specified by _length)
    //_source = nullptr | _destination = nullptr => -1
    //invalid parameter_sourceLength|_destinationLength|_sourceBegin|_sourceEnd|_destinationBegin => -2
    //returns 0 on successful execution
    //copy("variance", "namespace", 8, 9, 2, 4, 5) >> "namerianc"
    //copy("variance", "namespace", 8, 9, 2, 7, 5) >> "namespari"
    //copy("variance", "namespace", 8, 9, 6, 2, 5) >> "nacespace"
    int copy(const char* const _source, char* const _destination, int _sourceLength, int _destinationLength, int _sourceBegin,
             int _destinationBegin, int _copyLength)
    {
        if (_source == nullptr || _destination == nullptr) return -1;
        else if (_sourceLength < 1 || _destinationLength < 1) return -2;
        else if (_sourceBegin < 0 || _destinationBegin < 0) return -2;

        for (int n = 0; ; n++)
        {
            if (n == _copyLength) break;
            else if (_destinationBegin + n == _destinationLength) break;
            else if (_sourceBegin + n == _sourceLength) break;

            _destination[_destinationBegin + n] = _source[_sourceBegin + n];
        }

        return 0;
    }

    //it copies segment (from _source to _destination) (beginning at_sourceBegin and ending at _sourceEnd)
    //_source = nullptr | _destination = nullptr => -1
    //invalid parameter_sourceLength|_destinationLength|_sourceBegin|_sourceEnd|_destinationBegin => -2
    //returns 0 on successful execution
    //copyRange("variance", "namespace", 8, 9, 2, 4, 5) >> "namesriae"
    //copyRange("variance", "namespace", 8, 9, 5, 5, 3) >> "namespace"
    //copyRange("variance", "namespace", 8, 9, 5, 7, 8) >> "namespacn"
    int copyRange(const char* const _source, char* const _destination, int _sourceLength, int _destinationLength,
    int _sourceBegin, int _sourceEnd, int _destinationBegin)
    {
        if (_source == nullptr || _destination == nullptr) return -1;
        else if (_sourceLength < 1 || _destinationLength < 1) return -2;
        else if (_sourceBegin < 0 || _destinationBegin < 0 || _sourceEnd >= _sourceLength) return -2;

        for (int n = 0; ; n ++)
        {
            if (_destinationBegin + n == _destinationLength) break;
            else if (_sourceBegin + n == _sourceLength) break;
            else if (_sourceBegin + n > _sourceEnd) break;

            _destination[_destinationBegin + n] = _source[_sourceBegin + n];
        }

        return 0;
    }

    //_length specifies the length of _array
     //returns the new length of _array
    //_array = nullptr => -1
    //_length < 0 => -2
//extendLeft([1, 2, 3, 4, 5], 5, 2) >> [x, x, 1, 2, 3, 4, 5]
    int extendLeft(char*& _array, int _length, int _extensor)
    {
        if (_array == nullptr) return -1;
        else if (_length < 0) return -2;

        int newLength = _length + _extensor;
        char* newArray = new char[newLength];

        copyRange(_array, newArray, _length, newLength, 0, _length - 1, _extensor);

        delete[] _array;

        _array = newArray;

        return newLength;
    }

    //_length specifies the length of _array
     //returns the new length of _array
    //_array = nullptr => -1
    //_length < 0 => -2
    //extendRight([1, 2, 3, 4, 5], 5, 2) >> [1, 2, 3, 4, 5, x, x]
    int extendRight(char*& _array, int _length, int _extensor)
    {
        if (_array == nullptr) return -1;
        else if (_length < 0) return -2;

        int newLength = _length + _extensor;
        char* newArray = new char[newLength];

        copyRange(_array, newArray, _length, newLength, 0, _length - 1, 0);

        delete[] _array;

        _array = newArray;

        return newLength;
    }

    //_length specifies the length of _array
    //returns the new length of _array
    //_array = nullptr => -1
    //_length < 0 => -2
    //_reducer > _length => -3
    //reduceLeft([1, 2, 3, 4, 5], 5, 2) >> [3, 4, 5]
    int reduceLeft(char*& _array, int _length, int _reducer)
    {
        if (_array == nullptr) return -1;
        else if (_length < 0) return -2;
        else if (_reducer > _length) return -3;

        int newLength = _length - _reducer;
        char*newArray = new char[newLength];

        copy(_array, newArray, _length, newLength, _reducer, 0, _length - _reducer);

        delete[] _array;

        _array = newArray;

        return newLength;
    }

    //_length specifies the length of _array
     //returns the new length of _array
    //_array = nullptr => -1
    //_length < 0 => -2
    //_reducer > _length => -3
//reduceRight([1, 2, 3, 4, 5], 5, 2) >> [1, 2, 3]
    int reduceRight(char*& _array, int _length, int _reducer)
    {
        if (_array == nullptr) return -1;
        else if (_length < 0) return -2;
        else if (_reducer > _length) return -3;

        int newLength = _length - _reducer;
        char*newArray = new char[newLength];

        copy(_array, newArray, _length, newLength, 0, 0, newLength);

        delete[] _array;

        _array = newArray;

        return newLength;
    }

    //_length specifies the length of _array
     //returns the new length of _array
    //_array = nullptr => -1
    //_length < 1 => -2
    //_begin < 0 | _begin > _length - 1 => -2
    //_reducer > _length => -3
    //remove([5, 8, 1, 9, 2, 4, 7], 7, 2, 3) >> [5, 8, 4, 7]
    //remove([5, 8, 1, 9, 2, 4, 7], 7, 5, 3) >> [5, 8, 1, 9, 2]
    int remove(char*& _array, int _length, int _begin, int _reducer)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;
        else if (_begin < 0 || _begin > _length - 1) return -2;
        else if (_reducer > _length) return -3;

        if (_length - _begin < _reducer) _reducer = _length - _begin;

        int newLength = _length - _reducer;

        char*newArray = new char[newLength];

        //copying of _array[0.._begin] into &newArray
        copyRange(_array, newArray, _length, newLength, 0, _begin - 1, 0);

        //copying of _array[_begin + _reducer.._length - 1] into &newArray
        copyRange(_array, newArray, _length, newLength, _begin + _reducer, _length - 1, _begin);

        delete[] _array;

        _array = newArray;

        return newLength;
    }

    //_length specifies the length of _array
     //returns the new length of _array
    //_array = nullptr => -1
    //_length < 1 => -2
    //_begin > _end => -3
    int removeRange(char*& _array, int _length, int _begin, int _end)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;
        else if (_begin > _end) return -3;

        int newLength = _length - ((_end - _begin) + 1);
        char*newArray = new char[newLength];

        //copying of _array[0.._begin] into newArray
        copyRange(_array, newArray, _length, newLength, 0, _begin - 1, 0);

        //copying of _array[_end + 1.._length - 1] into newArray
        copyRange(_array, newArray, _length, newLength, _end + 1, _length - 1, _begin);

        delete[] _array;

        _array = newArray;

        return newLength;
    }

    int swap(char*, int, int, int);

    //_length specifies the length of _array
    //_array = nullptr => -1
    //_length < 1 => -2
    //returns 0 on successful execution
    int reverse(char* const _array, int _length)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;

        for (int i = 0; i < _length / 2; i ++)
        {
            swap(_array, _length, i, (_length - i) - 1);
        }

        return 0;
    }

    //_length specifies the length of _array
    //_array = nullptr => -1
    //_length < 1 => -2
    //returns 0 on successful execution
    int set(char* const _array, int _length, int _begin, int _end, char _value)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;

        for (int i = _begin; i < _end + 1; i ++)
        {
            _array[i] = _value;
        }

        return 0;
    }

     //_length specifies the length of _array
    //_array = nullptr => -1
    //_length < 1 => -2
    //returns 0 on successful execution
    int swap(char* const _array, int _length, int _i1, int _i2)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;

        char c = _array[_i1];
        _array[_i1] = _array[_i2];
        _array[_i2] = c;

        return 0;
    }

    //_length specifies the length of _array
    //returns the new length of _array
    //_array = nullptr => -1
    //_length < 1 => -2
    int trimBegin(char*& _array, int _length, char _value)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;

        int begin = 0;

        for (int i = 0; i < _length; i ++)
        {
            if (_array[i] != _value)
            {
                begin = i;
                break;
            }
        }

        int newLength = _length - begin;
        char* newArray = new char[newLength];

        copy(_array, newArray, _length, newLength, begin, 0, newLength);

        delete[] _array;

        _array = newArray;

        return newLength;
    }

    //_length specifies the length of _array
    //returns the new length of _array
    //_array = nullptr => -1
    //_length < 1 => -2
    int trimEnd(char*& _array, int _length, char _value)
    {
        if (_array == nullptr) return -1;
        else if (_length < 1) return -2;

        int end = _length - 1;
        for (int i = end; i > - 1; i--)
        {
            if (_array[i] != _value)
            {
                end = i;
                break;
            }
        }

        int newLength = end + 1;
        char* newArray = new char[newLength];

        copy(_array, newArray, _length, newLength, 0, 0, newLength);

        delete[] _array;

        _array = newArray;

        return newLength;
    }

