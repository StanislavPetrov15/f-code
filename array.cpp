//this file contains low-level functions for manipulation of byte arrays

/* (!) The functions in this file are non-validating - in other words one have to be sure that the arguments passed to
       the functions are correct */

template<typename T> struct array
{
    T* pointer;
    int length;
};

struct range
{
    int begin;
    int end;
};

///NON-MUTATING FUNCTIONS

//_length specifies the length of _array
//_length_ specifies the length of _value
template<typename T> bool beginsWith(const T* _array, const T* _value, int _length, int _length_)
{
      if (_length_ > _length) return false;

      for (int i = 0; i < _length_; i++)
      {
           if (_array[i] != _value[i])
           {
                return false;
           }
      }

      return true;
}

//_length specifies the length of _array
//_length_ specifies the length of _value
template<typename T> bool endsWith(const T* _array, const T* _value, int _length, int _length_)
{
    if (_length_ > _length) return false;

    int counter = 0;
    for (int i = _length - 1, n = _length_ - 1; (i > - 1) && (n > - 1); i--, n--)
    {
        if (_array[i] == _value[n])
        {
            counter++;
        }
    }

    return _length_ == counter;
}

//_length specifies the length of _array
template<typename T> bool contains(const T* _array, int _length, T _value)
{
    for (int i = 0; i < _length; i++)
    {
        if (_array[i] == _value)
        {
            return true;
        }
    }

    return false;
}

//_length specifies the length of _array
//_length_ specifies the length of _value
template<typename T> bool contains(const T* _array, const T* _value, int _length, int _length_)
{
    int matches = 0;

    for (int i = 0; i < _length; i++)
    {
        T element = _array[i];

        if (element == _value[matches])
        {
            matches++;
        }
        else
        {
            matches = 0;
        }

        if (matches == _length_)
        {
            return true;
        }
    }

    return false;
}

template<typename T> void resize(T*&, int, int);

//_length specifies the length of _array
//except([2, 9, 0, 1, 4, 9, 7, 3], 8, 9) => [2, 0, 1, 4, 7, 3]
template<typename T> array<T> except(const T* _array, int _length, T _value)
{
    T* accumulator = new T[_length];

    int matchCount = 0;

    for (int i = 0; i < _length; i ++)
    {
        if (_array[i] != _value)
        {
            accumulator[matchCount++] = _array[i];
        }
    }

    resize(accumulator, _length, matchCount);

    return { accumulator, matchCount };
} //-> delete [] <array>.pointer

//_length is the length of _array
//_length_ is the length of _set
//except([2, 9, 0, 1, 4, 9, 7, 3], [9, 7, 0], 8, 3) => array([2, 1, 4, 3], 4)
template<typename T> array<T> except(const T* _array, const T* _set, int _length, int _length_)
{
    T* accumulator = new T[_length];

    int matchCount = 0;

    for (int i = 0; i < _length; i ++)
    {
        if (!contains(_set, _length_, _array[i]))
        {
            accumulator[matchCount ++] = _array[i];
        }
    }

    resize(accumulator, _length, matchCount);

    return { accumulator, matchCount };
} //-> delete [] <array.pointer>

//_length1 specifies the length of _array1
//_length2 specifies the length of _array2
//_array1 == _array2 => true
//equality(nullptr, nullptr, x, x) => true
//equality([5, 0, 9], [5, 0, 9, 5], 3, 4) => false
//equality([5, 0, 9], [6, 4, 1], 3, 3) => false
//equality([5, 0, 9], [5, 9, 0], 3, 3) => false
//equality([5, 0, 9], [5, 0, 9], 3, 3) => true
template<typename T> bool equality(const T* _array1, const T* _array2, int _length1, int _length2)
{
    if (_array1 == _array2) return true;
    else if (_array1 == nullptr && _array2 != nullptr) return false;
    else if (_array1 != nullptr && _array2 == nullptr) return false;
    else if (_length1 != _length2) return false;

    //(STATE) both arrays are non-null and have the same length

    for (int i = 0; i < _length1; i ++)
    {
        if (_array1[i] != _array2[i])
        {
            return false;
        }
    }

    return true;
}

//_length specifies the length of _array
//the specified value does not exist => -1
template<typename T> int indexOf(const T* _array, int _length, T _value)
{
    for (int i = 0; i < _length; i ++)
    {
        if (_array[i] == _value)
        {
            return i;
        }
    }

    return -1;
}

//_length1 specifies the length of _array1
//_length2 specifies the length of _array2
//_value2 does not exist in _value1 => -1
template<typename T> int indexOf(const T* _array1, const T* _array2, int _length1, int _length2, int _begin)
{
    for (int i = _begin, matches = 0; i < _length1 && matches < _length2; i++)
    {
        if (_array1[i] == _array2[matches])
        {
            matches++;
        }
        else
        {
            i -= matches;
            matches = 0;
        }

        if (matches == _length2)
        {
            return (i - _length2) + 1;
        }
    }

    return -1;
}

//_length specifies the length of _array
//indexOfNot([9, 9, 9, 5, 8, 10, 2, 7], 8, 9) => 3
//indexOfNot([9, 9, 9, 5, 8, 10, 2, 7], 8, 4) => 0
template<typename T> int indexOfNot(const T* _array, int _length, T _value)
{
    for (int i = 0; i < _length; i++)
    {
        if (_array[i] != _value)
        {
            return i;
        }
    }

    return 0;
}

//_length specifies the length of _array
template<typename T> bool isHeterogenous(const T* _array, int _length)
{
    for (int i = 1; i < _length; i++)
    {
        if (_array[i - 1] != _array[i])
        {
            return true;
        }
    }

    return false;
}

//_length specifies the length of _array
template<typename T> bool isHomogenous(const T* _array, int _length)
{
    for (int i = 1; i < _length; i++)
    {
        if (_array[i - 1] != _array[i])
        {
            return false;
        }
    }

    return true;
}

//_length specifies the length of _array
//the specified value does not exist => -1
template<typename T> int lastIndexOf(const T* _array, int _length, T _value)
{
    for (int i = _length - 1; i > -1; i--)
    {
        if (_array[i] == _value)
        {
            return i;
        }
    }

    return -1;
}

//return the maximum element in the range (begin, end)
//_length == 0 => nullptr
//<T> implements operator '>' or it is a primitive numerical type ->
template<typename T> const T* max_(const T* _array, int _length, int _begin, int _end)
{
    if (_length == 0) return nullptr;

    const T* max = _array + _begin;

    for (int i = _begin; i <= _end; i++)
    {
        const T* element = _array + i;

        if (*element > *max)
        {
            max = element;
        }
    }

    return max;
}

//return the minimum element in the range (begin, end)
//_length == 0 => nullptr
//<T> implements operator '>' or it is a primitive numerical type ->
template<typename T> const T* min_(const T* _array, int _length, int _begin, int _end)
{
    if (_length == 0) return nullptr;

    const T* min = _array + _begin;

    for (int i = _begin; i <= _end; i++)
    {
        const T* element = _array + i;

        if (*element < *min)
        {
            min = element;
        }
    }

    return min;
}

//returns the range of a sequence consisting of certain set of values (it is not mandatory for the sequence to contain each value in the set)
//_length specifies the length of _array
//_length_ specifies the length of _set
//[3, 10, 15, 12, 8, 5, 7, 5, 5, 7, 7, 3, 9].RangeOf([2, 5, 7]) => (5, 10)
//[3, 10, 15, 12, 8, 5, 7, 2, 2, 7, 7, 3, 9].RangeOf([2, 5, 7]) => (5, 10)
//[3, 10, 15, 12, 0, 5, 7, 2, 2, 7, 7, 3, 9].RangeOf([4, 0, 1]) => (4, 4)
//[3, 10, 15, 12, 8, 5, 7, 2, 2, 7, 7, 3, 9].RangeOf([4, 0, 1]) => (-1, -1)
template<typename T> range rangeOf(const T* _array, const T* _set, int _length, int _length_)
{
    for (int i = 0, n = -1; i < _length; i++)
    {
        bool equality = contains(_set, _length_, _array[i]);

        if (n == -1 && equality)
        {
            n = i;
        }
        else if (n > - 1 && !equality)
        {
            return { n, i - 1 };
        }
        else if (n > - 1 && i == _length - 1)
        {
            return { n, i };
        }
    }

    return { -1, -1 };
}

//_length specifies the length of _array
template<typename T> array<T> where(const T* _array, int _length, const std::function<bool(T)>& _predicate)
{
    T* accumulator = new T[_length];
    int matchCount = 0;

    for (int i = 0; i < _length; i ++)
    {
        if (_predicate(_array[i]))
        {
            accumulator[matchCount++] = _array[i];
        }
    }

    resize(accumulator, _length, matchCount);

    return { accumulator, matchCount };
} //-> delete [] <array>.pointer

/* - the first element represent the number of matches in the sequence
   - the elements after the first are (begin, end) pairs for each match in the sequence; therefore a sequence with 2 matches will consist of
     5 elements with the following values: [0]=2, [1]=Match1_Begin, [2]=Match1_End, [3]=Match2_Begin, [4]=Match2_End;
     non-empty match is described by (begin <= end) and an empty match is described by (begin > end) */
//returns only values that are (between the beginning and a separator), (between separator and the end) or (between two separators)
//empty sequences are generated (and eventually are appended to the result) only if they are between two separators
//_length specifies the length of _array
//_ignoreEmptyValues = true -> empty sequences (if there are any) are not appended to the result
//split([3, 7, 18, 5, 19, 76, 15], 7, 353) => []
//split([18, 5, 19, 76, 15, 9, 20, 5], 8, 9) => [[18, 5, 19, 76, 15], [20, 5]]
//split([56, 3, 7, 18, 5, 19, 76, 7], 8, 7) => [[56, 3], [18, 5, 19, 76]]
//split([56, 7, 7, 18, 5, 19, 76, 15, 9], 9, 7) => [[56], [], [18, 5, 19, 76, 15, 9]]
//split([56, 7, 7, 18, 5, 19, 76, 15, 9], 9, 7) => [[56], [18, 5, 19, 76, 15, 9]]
//split([7, 41, 56, 7, 18, 76, 15, 9, 7], 9,7 ) => [[41, 56], [18, 76, 15, 9]]
//split([7, 41, 56, 7, 7, 7, 18, 5, 15], 9, 7) => [[41, 56], [], [], [18, 5, 15]]
//split([7, 41, 56, 7, 7, 7, 18, 5, 15], 9, 7, true) => [[41, 56], [18, 5, 15]]
template<typename T> int* split(T* _array, int _length, T _separator, bool _ignoreEmptyValues = false)
{
    int* accumulator = new int[10];

    int size = 5;
    int extensor = 5;
    int count = 1;

    accumulator[0] = 0;

    for (int i = 0; i < _length;)
    {
        bool currentIsMatched = _array[i] == _separator;
        bool nextIsMatched = i < _length - 1 && _array[i + 1] == _separator;

        //[separator, separator]
        if (currentIsMatched && nextIsMatched)
        {
            //extending the accumulator if needed
            if (count + 2 > size)
            {
                resize(accumulator, size, size + extensor);
                size += extensor;
            }

            i++;

            continue;
        }
        //[separator, !separator]
        else if (currentIsMatched && !nextIsMatched)
        {
            i++;
            continue;
        }

        //(STATE) the current element is not a separator

        int index = indexOf<T>(_array + i, _length - i, _separator);

        //[0!separator...!separator]
        if (count == 2 && index == -1)
        {
            break;
        }
        //[!separator...separator]
        else if (!currentIsMatched && index != -1)
        {
            index += i;

            //extending the accumulator if needed
            if (count + 2 > size)
            {
                resize(accumulator, size, size + extensor);
                size += extensor;
            }

            accumulator[0]++;
            accumulator[count++] = i;
            accumulator[count++] = index - 1;
            i = index;
        }
            //[!separator...]
        else if (!currentIsMatched && index == -1)
        {
            //extending the accumulator if needed
            if (count + 2 > size)
            {
                resize(accumulator, size, size + extensor);
                size += extensor;
            }

            accumulator[0]++;
            accumulator[count++] = i;
            accumulator[count++] = _length - 1;
            break;
        }
    }

    //extending the accumulator if needed
    if (count + 4 > size)
    {
        resize(accumulator, size, size + 4);
    }

    return accumulator;
} //-> delete [] <array>.pointer

///MUTATION FUNCTIONS

//it copies segment (from _source to _destination) (beginning at _sourceBegin) and (with length specified by _length)
//copy("variance", "namespace", 8, 9, 2, 4, 5) >> "namerianc"
//copy("variance", "namespace", 8, 9, 2, 7, 5) >> "namespari"
//copy("variance", "namespace", 8, 9, 6, 2, 5) >> "nacespace"
template<typename T> void copy(const T* _source, T* _destination, int _sourceLength, int _destinationLength, int _sourceBegin,
         int _destinationBegin, int _copyLength)
{
    for (int n = 0; ; n++)
    {
        if (n == _copyLength)
        {
            break;
        }
        else if (_destinationBegin + n == _destinationLength)
        {
            break;
        }
        else if (_sourceBegin + n == _sourceLength)
        {
            break;
        }

        _destination[_destinationBegin + n] = _source[_sourceBegin + n];
    }
}

//it copies segment (from _source to _destination) (beginning at_sourceBegin and ending at _sourceEnd)
//copyRange("variance", "namespace", 8, 9, 2, 4, 5) >> "namesriae"
//copyRange("variance", "namespace", 8, 9, 5, 5, 3) >> "namespace"
//copyRange("variance", "namespace", 8, 9, 5, 7, 8) >> "namespacn"
template<typename T> void copyRange(const T* _source, T* _destination, int _sourceLength, int _destinationLength,
int _sourceBegin, int _sourceEnd, int _destinationBegin)
{
    for (int n = 0; ; n++)
    {
        if (_destinationBegin + n == _destinationLength)
        {
            break;
        }
        else if (_sourceBegin + n == _sourceLength)
        {
             break;
        }
        else if (_sourceBegin + n > _sourceEnd)
        {
            break;
        }

        _destination[_destinationBegin + n] = _source[_sourceBegin + n];
    }
}

//_length specifies the length of _array
//extendLeft([1, 2, 3, 4, 5], 5, 2) >> [x, x, 1, 2, 3, 4, 5]
template<typename T> void extendLeft(T*& _array, int _length, int _extensor)
{
    int newLength = _length + _extensor;

    T* newArray = new T[newLength];

    copyRange(_array, newArray, _length, newLength, 0, _length - 1, _extensor);

    delete[] _array;

    _array = newArray;
}

//_length specifies the length of _array
//extendRight([1, 2, 3, 4, 5], 5, 2) >> [1, 2, 3, 4, 5, x, x]
template<typename T> void extendRight(T*& _array, int _length, int _extensor)
{
    int newLength = _length + _extensor;

    T* newArray = new T[newLength];

    copyRange(_array, newArray, _length, newLength, 0, _length - 1, 0);

    delete[] _array;

    _array = newArray;
}

//_length specifies the length of _array
//reduceLeft([1, 2, 3, 4, 5], 5, 2) >> [3, 4, 5]
template<typename T> void reduceLeft(T*& _array, int _length, int _reducer)
{
    int newLength = _length - _reducer;

    T* newArray = new T[newLength];

    copy(_array, newArray, _length, newLength, _reducer, 0, _length - _reducer);

    delete[] _array;

    _array = newArray;
}

//_length specifies the length of _array
//reduceRight([1, 2, 3, 4, 5], 5, 2) >> [1, 2, 3]
template<typename T> void reduceRight(T*& _array, int _length, int _reducer)
{
    int newLength = _length - _reducer;

    T* newArray = new T[newLength];

    copy(_array, newArray, _length, newLength, 0, 0, newLength);

    delete[] _array;

    _array = newArray;
}

//_length specifies the length of _array
//remove([5, 8, 1, 9, 2, 4, 7], 7, 2, 3) >> [5, 8, 4, 7]
//remove([5, 8, 1, 9, 2, 4, 7], 7, 5, 3) >> [5, 8, 1, 9, 2]
template<typename T> void remove(T*& _array, int _length, int _begin, int _reducer)
{
    if (_length - _begin < _reducer) _reducer = _length - _begin;

    int newLength = _length - _reducer;

    T* newArray = new T[newLength];

    //copying of _array[0.._begin] into &newArray
    copyRange(_array, newArray, _length, newLength, 0, _begin - 1, 0);

    //copying of _array[_begin + _reducer.._length - 1] into &newArray
    copyRange(_array, newArray, _length, newLength, _begin + _reducer, _length - 1, _begin);

    delete[] _array;

    _array = newArray;
}

//_length specifies the length of _array
template<typename T> void removeRange(T*& _array, int _length, int _begin, int _end)
{
    int newLength = _length - ((_end - _begin) + 1);

    T* newArray = new T[newLength];

    //copying of _array[0.._begin] into newArray
    copyRange(_array, newArray, _length, newLength, 0, _begin - 1, 0);

    //copying of _array[_end + 1.._length - 1] into newArray
    copyRange(_array, newArray, _length, newLength, _end + 1, _length - 1, _begin);

    delete[] _array;

    _array = newArray;
}

//T = built-in integral type ->
template<typename T > void resize(T*& _array, int _currentLength, int _newLength)
{
     T* oldElements = _array;

     _array = new T[_newLength];

     //if the list is being extended
     if (_newLength > _currentLength)
     {
         for (int i = 0; i < _currentLength; i ++)
         {
             _array[i] = oldElements[i];
         }
     }
     //if the list is being shrinked
     else if (_newLength < _currentLength)
     {
         for (int i = 0; i < _newLength; i ++)
         {
             _array[i] = oldElements[i];
         }
     }

     delete[] oldElements;
}

template<typename T> void swap(T*&, int, int, int);
//_length specifies the length of _array
template<typename T> void reverse(T*& _array, int _length)
{
    for (int i = 0; i < _length / 2; i ++)
    {
        swap(_array, _length, i, (_length - i) - 1);
    }
}

//_length specifies the length of _array
//rotateLeft([1, 2, 3, 4, 5], 5, 5) >> [4, 5, 1, 2, 3]
template<typename T> void rotateLeft(T*& _array, int _length, int _positions)
{
    if (_positions > _length)
    {
        _positions = _positions % _length;
    }

    T* newArray = new T[_length];

    //(EXAMPLE) [1, 2, 3, 4, 5] (2)
    for (int i = _positions, n = 0; i < _length; i++, n++)
    {
        newArray[n] = _array[i];
    } //-> [3, 4, 5, x, x]

    for (int i = 0, n = _length - _positions; i < _positions; i++, n++)
    {
        newArray[n] = _array[i];
    } //-> [x, x, x, 1, 2]

    delete[] _array;

    _array = newArray;
}

//_length specifies the length of _array
//rotateRight([1, 2, 3, 4, 5], 5, 4) >> [5, 1, 2, 3, 4]
template<typename T> void rotateRight(T*& _array, int _length, int _positions)
{
    if (_positions > _length)
    {
        _positions = _positions % _length;
    }

    T* newArray = new T[_length];

    //(EXAMPLE) [1, 2, 3, 4, 5] (2)

    for (int i = _length - _positions, n = 0; i < _length; i++, n++)
    {
        newArray[n] = _array[i];
    } //-> [4, 5, x, x, x]

    for (int i = 0, n = _positions; i < _length - _positions; i++, n++)
    {
        newArray[n] = _array[i];
    } //-> [x, x, 1, 2, 3]

    delete[] _array;

    _array = newArray;
}

//_length specifies the length of _array
//set([1, 2, 3, 4, 5], 5, 2, 4, 19) >> [1, 2, 19, 19, 19]
template<typename T> void set(T*& _array, int _length, int _begin, int _end, T _value)
{
    for (int i = _begin; i < _end + 1; i++)
    {
        _array[i] = _value;
    }
}

//_length specifies the length of _array
template<typename T> void swap(T*& _array, int _length, int _i1, int _i2)
{
    T c = _array[_i1];
    _array[_i1] = _array[_i2];
    _array[_i2] = c;
}

//_length specifies the length of _array
template<typename T> void trimBegin(T*& _array, int _length, T _value)
{
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
    T* newArray = new T[newLength];

    copy(_array, newArray, _length, newLength, begin, 0, newLength);

    delete[] _array;

    _array = newArray;
}

//_length specifies the length of _array
template<typename T> void trimEnd(T*& _array, int _length, T _value)
{
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
    T* newArray = new T[newLength];

    copy(_array, newArray, _length, newLength, 0, 0, newLength);

    delete[] _array;

    _array = newArray;
}

