//(INTERNAL)
enum class SpatialKind { COMPLETE, SEGMENT };

//(INTERNAL)
enum class MutabilityKind { MUTABLE, IMMUTABLE };

/* this type determines what happens (when an instance of a sequence type is traversed) and these four scenarios happen:
   - the current traversal position is 0 and either previous() or back() is used - if the traversal mdoe is set to BOUNDED then
     (previous() returns the first element) and (back() does nothing)
   - the current traversal position is 0 and either previous() or back() is used - if the traversal mode is set to CIRCULAR then
     (previous() returns the last element) and (back() sets the current traversal position to a value that points to the last element)
   - the current traversal position is the position of the last element and either next() or advance() is used -
	 if the traversal mode is set to BOUNDED then (next() returns the last element) and (advance() does nothing)
   - the current traversal position is the position of the last element and either next() or advance() is used -
     if the traversal mode is set to CIRCULAR then (next() returns the first element) and
     (advance() sets the current traversal position to a value that points to the first element) */
enum class TraversalMode { BOUNDED, CIRCULAR };

/* when an instance of (a sequence type that uses ReleaseMode) is about to be destructed the elements are freed automatically and immediately
	 (when IMMEDIATE is used)) or (are stored for future use and are freed manually in a specific future moment (when FUTURE is used)) */
enum class ReleaseMode { IMMEDIATE, FUTURE };

//(INTERNAL)
const int EXCLUDED_BLOCK_BEGIN = INT_MIN + 1;

//(INTERNAL)
const int EXCLUDED_BLOCK_END = INT_MAX - 1;

//(!) the size(accessed by size()) of a segment is equal to the size of the list that the segment refers to
template<typename T> struct list
{
    protected:

    int Count = 0;
    int Size = 0;
    int Position = 0; //iteration position
    T* Elements = nullptr;
    SpatialKind SpatialKind = SpatialKind::COMPLETE;

    bool InRange(int _index) const
    {
        return _index >= 0 && _index <= Count - 1;
    }

    bool InRange(int _begin, int _end) const
    {
        if (_begin < 0 || _end > Count - 1)
        {
            return false;
        }
        else if (_begin > _end)
        {
            return false;
        }

        return true;
    }

    void copy(const list<T>& _source)
    {
        delete [] Elements;
        Elements = new T[_source.Size];

        for (int i = 0; i < _source.count(); i++)
        {
            Elements[i] = _source[i];
        }

        Size = _source.Size;
        Count = _source.Count;
    }

    public:

    TraversalMode TraversalMode = TraversalMode::BOUNDED;

    MutabilityKind MutabilityKind = MutabilityKind::MUTABLE;

    ReleaseMode ReleaseMode = ReleaseMode::IMMEDIATE;

    int ExtensionValue = 4.0; //in percent of the current size

    ///CONSTRUCTORS

    list() = default;

    /* _extendCount is needed in cases where the allocated slots must be treated as existing elements (without being added first through another operation);
        if that parameter is true then &Count equals &Size */
    explicit list(int _size, bool _extendCount)
    {
        resize(_size);

        if (_extendCount)
        {
            Count = _size;
        }
    }

    list(const list<T>& _value)
    {
        if (this == &_value) return;

        Size = _value.Size;
        Count = _value.Count;
        SpatialKind = _value.SpatialKind;
        TraversalMode = _value.TraversalMode;
        MutabilityKind = _value.MutabilityKind;
        ReleaseMode = _value.ReleaseMode;

        if (Elements != nullptr)
        {
            delete [] Elements;
        }

        Elements = new T[Size];

        for (int i = 0; i < Count; i++)
        {
            Elements[i] = _value.Elements[i];
        }
    }

    list(const std::initializer_list<T>& _value)
    {
        Size = _value.size();
        Count = _value.size();

        if (Elements != nullptr)
        {
            delete [] Elements;
        }

        Elements = new T[Size];

        const T* value = data(_value);
        for (int i = 0; i < Count; i++)
        {
            Elements[i] = value[i];
        }
    }

    //it generates a segment
    list(const list<T>& _source, int _begin, int _end)
    {
        if (_begin < 0 || _end > _source.count() - 1) return;
        else if (_begin > _end) return;

        Elements = &(_source[_begin]);
        Count = (_end - _begin) + 1;
        Size = Count;
        SpatialKind = SpatialKind::SEGMENT;
    }

    //it generates a segment
    list(const list<T>& _source, const Range<int>& _range)
    {
        if (_range.begin() < 0 || _range.end() > _source.count() - 1) return;
        else if (_range.begin() > _range.end()) return;

        Elements = &(_source[_range.begin()]);
        Count = _range.length();
        Size = Count;
        SpatialKind = SpatialKind::SEGMENT;
    }

    //it generates a segment
    list(const T* _source, int _elementsCount, int _begin, int _end)
    {
        if (_begin < 0 || _end > _elementsCount - 1) return;
        else if (_begin > _end) return;

        Elements = const_cast<T*>(&(_source[_begin]));
        Count = (_end - _begin) + 1;
        Size = Count;
        SpatialKind = SpatialKind::SEGMENT;
    }

    //it generates a segment
    list(const T* _source, int _elementsCount, const Range<int>& _range)
    {
        if (_range.begin() < 0 || _range.end() > _elementsCount - 1) return;
        else if (_range.begin() > _range.end()) return;

        Elements = const_cast<T*>(&(_source[_range.begin()]));
        Count = (_range.end() - _range.begin()) + 1;
        Size = Count;
        SpatialKind = SpatialKind::SEGMENT;
    }

    ///DESTRUCTOR

    ~list()
    {
        if (SpatialKind == SpatialKind::SEGMENT)
        {
            return;
        }
        else if (ReleaseMode == ReleaseMode::IMMEDIATE)
        {
            delete[] Elements;
        }
    }

    ///POINTERS NEEDED FOR 'RANGE-FOR'

    T* begin() const
    {
        if (Count > 0)
        {
            return Elements;
        }
        else
        {
            return nullptr;
        }
    }

    T* end() const
    {
        if (Count > 0)
        {
            return &Elements[Count];
        }
        else
        {
            return nullptr;
        }
    }

    ///OPERATORS

    bool operator==(const list<T>& _value) const
    {
        if (Count != _value.Count)
        {
            return false;
        }

        for (int i = 0; i < Count; i++)
        {
            if (Elements[i] != _value[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const list<T>& _value) const
    {
        if (Count != _value.Count)
        {
            return true;
        }

        for (int i = 0; i < Count; i++)
        {
            if (Elements[i] != _value[i])
            {
                return true;
            }
        }

        return false;
    }

    //[5, 0, 9] == [[5, 1, 3], [5, 1, 9], [5, 0, 0]] => false
    //[5, 0, 9] == [[5, 1, 0], [5, 0, 9], [4, 3, 1]] => true
    bool operator==(const list<list<T>>& _values) const
    {
        for (const list<T>& __list : _values)
        {
            if ((*this) == __list)
            {
                return true;
            }
        }

        return false;
    }

    //[5, 0, 9] == [[5, 1, 0], [5, 0, 9], [4, 3, 1]] => false
    //[5, 0, 9] == [[5, 1, 3], [5, 1, 9], [5, 0, 0]] => true
    bool operator!=(const list<list<T>>& _values) const
    {
        for (const list<T>& __list : _values)
        {
            if ((*this) == __list)
            {
                return false;
            }
        }

        return true;
    }

    list<T>& operator=(const list<T>& _value)
    {
        if (SpatialKind == SpatialKind::SEGMENT) return *this;
        if (this == &_value) return *this;

        Clear();
        resize(_value.size());
        Append(_value);

        return *this;
    }

    list<T> operator+(const T& _value) const
    {
        return Clone().Append(_value);
    }

    list<T> operator+(const list<T>& _value) const
    {
        return Clone().Append(_value);
    }

    list<T>& operator+=(const T& _value)
    {
        return Append(_value);
    }

    list<T>& operator+=(const list<T>& _value)
    {
        return Append(_value);
    }

    //_index is in the range of list ->
    T& operator[](int _index)
    {
        return Elements[_index];
    }

    //_index is in the range of list ->
    T& operator[](int _index) const
    {
        return Elements[_index];
    }

    ///FIELDS

    int count() const
    {
        return Count;
    }

    int size() const
    {
        return Size;
    }

    int position() const
    {
        return Position;
    }

    T* elements()
    {
        return Elements;
    }

    T* elements() const
    {
        return Elements;
    }

    ///TRAVERSAL FUNCTIONS

    bool can_reverse() const
    {
        return position() > 0;
    }

    bool can_advance() const
    {
        return position() < Count - 1;
    }

    //traversalMode() == BOUNDED && position() - _value < 0 >> position() = position()
    //traversalMode() == BOUNDED && position() - _value > -1 >> position() = position() - _value
    //traversalMode() == CIRCULAR -> circular addition; (EXAMPLE) count() = 19, position() = 4, back(9) >> position() = 14
    list<T>& back(int _value)
    {
        if (TraversalMode == TraversalMode::BOUNDED && Position - _value >= 0)
        {
            Position -= _value;
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Count > 0)
        {
            Position = numeric::CircularSubtraction(0, Count - 1, Position, _value);
        }

        return *this;
    }

    //traversalMode() == BOUNDED && position() + _value >= count() >> position() = position()
    //traversalMode() == BOUNDED && position() + _value < count() - 1 >> position() = position() + _value
    //traversalMode() == CIRCULAR -> circular addition; (EXAMPLE) size() = 21, position() = 16, advance(10) >> position() = 5
    list<T>& advance(int _value)
    {
        if (TraversalMode == TraversalMode::BOUNDED && Position + _value < Count)
        {
            Position += _value;
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Count > 0)
        {
            Position = numeric::CircularAddition(0, Count - 1, Position, _value);
        }

        return *this;
    }

    //position() > 0 => [position() - 1]
    //traversalMode() == BOUNDED && position() == 0 => [0]
    //traversalMode() == CIRCULAR && position() == 0 => [count() - 1]
    T& previous() const
    {
        if (Position > 0)
        {
            return Elements[Position - 1];
        }
        else if (TraversalMode == TraversalMode::BOUNDED && Position == 0)
        {
            return Elements[0];
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Position == 0)
        {
            return Elements[Count - 1];
        }
    }

    //count() > 0 ->
    T& current() const
    {
        return Elements[Position];
    }

    //position() < count() - 1 => [position() + 1]
    //traversalMode() == BOUNDED && position() == count() - 1 => [position()]
    //traversalMode() == CIRCULAR && position() == count() - 1 => [0]
    T& next() const
    {
        if (Position < Count - 1)
        {
            return Elements[Position + 1];
        }
        else if (TraversalMode == TraversalMode::BOUNDED && Position == Count - 1)
        {
            return Elements[Position];
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Position == Count - 1)
        {
            return Elements[0];
        }
    }

    //the list has atleast one value ->
    T& last() const
    {
        return Elements[Count - 1];
    }

    //_position < -1 || _position > count() - 1 => -1
    int set_position(int _position)
    {
        if (_position < - 1 || _position > Count - 1) return - 1;

        Position = _position;

        return 0;
    }

    ///MUTATION FUNCTIONS

    //acquire ownership of _array
    void Acquire(T* _array, int _arrayLength)
    {
        Count = _arrayLength;
        Size = _arrayLength;
        Position = 0;
        delete[] Elements;
        Elements = _array;
    }

    //acquire ownership of _list; after the operation is completed _list becomes invalid
    void Acquire(list<T>& _list)
    {
        if (this == &_list) return;

        Count = _list.Count;
        Size = _list.Size;
        Position = _list.Position;
        ExtensionValue = _list.ExtensionValue;
        SpatialKind = _list.SpatialKind;
        TraversalMode = _list.TraversalMode;
        ReleaseMode = _list.ReleaseMode;
        delete[] Elements;
        Elements = _list.Elements;
        _list.Count = 0;
        _list.Size = 0;
        _list.Position = 0;
        _list.Elements = nullptr;
    }

   list<T>& Append(const T& _value)
   {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

       if (Count + 1 > Size)
       {
           int value = (Size / 100.0) * ExtensionValue;
           resize(Size + (value > 0 ? value : 1));
       }

       Elements[Count++] = _value;

       return *this;
   }

    list<T>& Append(const T& _value, int _times)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (int i = 0; i < _times; i++)
        {
            Elements[Count++] = _value;
        }

        return *this;
    }

    list<T>& Append(const list<T>& _value)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (const T& __element : _value)
        {
            Append(__element);
        }

        return *this;
    }

    list<T>& Append(const T* _value, int _length)
	{
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
		
		for (int i = 0; i < _length; i++)
		{
			Append(_value[i]);
		}
		
		return *this;
	}

    //<T> implements operator '<' or it is a primitive numerical type ->
    list<T>& BubbleSort(bool _ascending = true)
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        while (true)
        {
            bool isSorted = true;

            for (int i = 0; i < Count - 1; i++)
            {
                if (Elements[i + 1] < Elements[i])
                {
                    isSorted = false;
                    Swap(i, i + 1);
                }
            }

            if (isSorted) break;
        }

        return _ascending ? *this : Reverse();
    }

    //<T> implements operator '<' or it is a primitive numerical type ->
    list<T>& BubbleSort(const std::function<bool(const T&, const T&)>& _predicate, bool _ascending = true)
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        while (true)
        {
            bool isSorted = true;

            for (int i = 0; i < Count - 1; i++)
            {
                if (_predicate(Elements[i + 1], Elements[i]))
                {
                    isSorted = false;
                    Swap(i, i + 1);
                }
            }

            if (isSorted) break;
        }

        return _ascending ? *this : Reverse();
    }

    //the contents of _data are copied inside the list
	list<T>& BuiltFromArray(const T* _data, int _dataLength)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        Count = _dataLength;
        Size = _dataLength;
        delete[] Elements;
        Elements = new T[Size];

        for (int i = 0; i < _dataLength; i++)
        {
            Elements[i] = _data[i];
        }

        return *this;
    }

    //_size < 0 -> state of the list doesn't change
    list<T>& Clear(int _size = 0)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
        else if (_size < 0) return *this;

        Count = 0;
        Size = _size;
        delete[] Elements;
        Elements = new T[Size];

        return *this;
    }

    /* - this function marks certain memory block as 'excluded', which means that the data in the excluded block wouldn't
         be used anymore; the reason for using this function is performance (in some cases, not all) - the alternative is deleting
         the specific element(s) which would cause deletion of &Elements, assigning new array to &Elements and copying the old data
         into the new array which would slow down the program, so using exclusion instead of real deletion can increase the performance
         in some cases
       - a memory block is excluded by using the following 4 markers:
         - an exclusion marker for the beginning of the block (at position 0 in the block) (4 bytes)
         - integer value (following the beginning marker) that specifies the length of the block (in number of elements, not bytes) (4 bytes)
         - an exclusion marker at the end of the block (at position (length - sizeof(int))) (4 bytes)
         - integer value (before the end marker) that specifies the length of the block (in number of elements, not bytes) (4 bytes)
         (EXAMPLE) begin marker, length...length, end marker
       - the programmer can determine the beginning and the end of an excluded block by detecting the two exclusion markers; by default
         the function uses the constants EXCLUDED_BLOCK_BEGIN as a begin marker, and EXCLUDED_BLOCK_END as an end marker, but other values
         can be used if desired
        /* <T> must be compound type and must have (two <int> fields at the beginning of the declaration) and (two <int> fields at the end of the declaration)
           (EXAMPLE) struct S { int a; int b; ...other fields... int c; int d; } */
        //(_end > _begin) & (sizeof(T) > (sizeof(int) * 4)) ->
		list<T>& Exclude(int _begin, int _end, int _excludedBlockBeginMarker = EXCLUDED_BLOCK_BEGIN, int _excludedBlockEndMarker = EXCLUDED_BLOCK_END)
		{
			if (_begin >= _end) return *this;

			//a pointer to the first <int> element of the current excluded block
			int* currentBlockBegin = reinterpret_cast<int*>(&(*this)[_begin]);

			//a pointer to the last <int> element of the current excluded block
			int* currentBlockEnd = (reinterpret_cast<int*>(&(*this)[_end]) + (sizeof(T) / sizeof(int))) - 1;

            //specifies if there is an excluded block to the left of the current excluded block
			bool leftAdjacent = _begin > 0 && *(currentBlockBegin - 1) == _excludedBlockEndMarker;

			//specifies if there is an excluded block to the right of the current excluded block
			bool rightAdjacent = _end < Count - 1 && *(reinterpret_cast<int*>(&(*this)[_end + 1])) == _excludedBlockBeginMarker;

			//if there is no other adjacent excluded block to the left or right of the current block (there is no need for merging the two blocks)
			if ((!leftAdjacent && !rightAdjacent))
			{
				//a begin marker
                *currentBlockBegin = _excludedBlockBeginMarker;

				//(length of the block) after the first marker
				*(currentBlockBegin + 1) = (_end - _begin) + 1;

				//(length of the block) before the end marker
				*(currentBlockEnd - 1) = (_end - _begin) + 1;

				//an end marker
				*currentBlockEnd = _excludedBlockEndMarker;
			}
			//if there is an adjacent excluded block to the left of the current block (the two blocks must be merged)
			else if (leftAdjacent && !rightAdjacent)
			{
				//length of the previous block
				int previousBlockLength = *(currentBlockBegin - 2);

                //a pointer to the first <int> element of the previous block
                int* previousBlockBegin = reinterpret_cast<int*>(&(*this)[_begin - previousBlockLength]);

				//length of the current block
				int currentBlockLength = (_end - _begin) + 1;

                //new length
                *(previousBlockBegin + 1) = previousBlockLength + currentBlockLength;
				*(currentBlockEnd - 1) = previousBlockLength + currentBlockLength;

				//an end marker
				*currentBlockEnd = _excludedBlockEndMarker;

				//zeroing the last two <int> fields of the previous block
				*(currentBlockBegin - 1) = 0;
				*(currentBlockBegin - 2) = 0;
			}
            //if there is an adjacent excluded block to the right of the current block (the two blocks must be merged)
			else if (!leftAdjacent && rightAdjacent)
			{
				//begin marker
				*currentBlockBegin = _excludedBlockBeginMarker;

				//a pointer to the first <int> element of the next block
				int* nextBlockBegin = reinterpret_cast<int*>(&(*this)[_end + 1]);

				//length of the next block
				int nextBlockLength = *(nextBlockBegin + 1);

				//a pointer to the last <int> element of the next block
				int* nextBlockEnd = (reinterpret_cast<int*>(&(*this)[_end + nextBlockLength]) + (sizeof(T) / sizeof(int))) - 1;

				//length of the current block
				int currentBlockLength = (_end - _begin) + 1;

                //new length
                *(currentBlockBegin + 1) = currentBlockLength + nextBlockLength;
                *(nextBlockEnd - 1) = currentBlockLength + nextBlockLength;

                //zeroing the first two <int> fields of the next block
				*(nextBlockBegin) = 0;
				*(nextBlockBegin + 1) = 0;
			}
            //if there are adjacent excluded blocks to the left and right of the current block (the three blocks must be merged)
			else if (leftAdjacent && rightAdjacent)
			{
				//a pointer to the first <int> element of the next block
				int* nextBlockBegin = reinterpret_cast<int*>(&(*this)[_end + 1]);

				//length of the previous block
				int previousBlockLength = *(currentBlockBegin - 2);

				//length of the current block
				int currentBlockLength = (_end - _begin) + 1;

				//length of the next block
				int nextBlockLength = *(nextBlockBegin + 1);

				//a pointer to the first <int> element of the previous block
				int* previousBlockBegin = reinterpret_cast<int*>(&(*this)[_begin - previousBlockLength]);

				//a pointer to the last <int> element of the next block
				int* nextBlockEnd = (reinterpret_cast<int*>(&(*this)[_end + nextBlockLength]) + (sizeof(T) / sizeof(int))) - 1;

				//new length of the previous block
				*(previousBlockBegin + 1) = previousBlockLength + currentBlockLength + nextBlockLength;

				//new length of the next block
                *(nextBlockEnd - 1) = previousBlockLength + currentBlockLength + nextBlockLength;

                //zeroing the last two <int> fields of the previous block
				*(currentBlockBegin - 1) = 0;
				*(currentBlockBegin - 2) = 0;

                //zeroing the first two <int> fields of the next block
				*(nextBlockBegin) = 0;
				*(nextBlockBegin + 1) = 0;
			}

			return *this;
		}

    /* - this function marks certain memory block as 'excluded', which means that the data in the excluded block wouldn't
             be used anymore; the reason for using this function is performance (in some cases, not all) - the alternative is deleting
             the specific element(s) which would cause deletion of &Elements, assigning new array to &Elements and copying the old data
             into the new array which would slow down the program, so using exclusion instead of real deletion can increase the performance
             in some cases
           - a memory block is excluded by using the following 4 markers:
             - an exclusion marker for the beginning of the block (at position 0 in the block)
             - integer value (following the beginning marker) that specifies the length of the block (in number of elements, not bytes)
             - an exclusion marker at the end of the block (at position (length - sizeof(int)))
             - integer value (before the end marker) that specifies the length of the block (in number of elements, not bytes)
             (EXAMPLE) begin marker, length...length, end marker
           - the programmer can determine the beginning and the end of an excluded block by detecting the two exclusion markers; by default
             the function uses the constants EXCLUDED_BLOCK_BEGIN as a begin marker, and EXCLUDED_BLOCK_END as an end marker, but other values
             can be used if desired
            /* <T> must be compound type and must have (two <int> fields at the beginning of the declaration) and (two <int> fields at the end of the declaration)
               (EXAMPLE) struct S { int a; int b; ...other fields... int c; int d; } */
    //(_end > _begin) & (sizeof(T) > (sizeof(int) * 4)) ->
    list<T>& Exclude(const Range<int>& _range, int _excludedBlockBeginMarker = EXCLUDED_BLOCK_BEGIN, int _excludedBlockEndMarker = EXCLUDED_BLOCK_END)
    {
            return Exclude(_range.begin(), _range.end());
    }

    //[1, 2, 10].FillLeft(5, 7) => [5, 5, 5, 5, 1, 2, 10]
    list<T>& FillLeft(const T& _value, int _length)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (int i = 0; Count < _length; i++)
        {
            Insert(_value, 0);
        }

        return *this; this();
    }

    //[1, 2, 10].FillRight(5, 7) => [1, 2, 10, 5, 5, 5, 5]
    list<T>& FillRight(const T& _value, int _length)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (int i = 0; Count < _length; i++)
        {
            Append(_value);
        }

        return *this;
    }

    //(count() > 0 && _index > 0 && _index < count()) ->
    list<T>& Insert(const T& _value, int _index)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
        else if (count() == 0) return *this;
        else if (_index < 0 || _index >= count()) return *this;

        if (Count + 1 > Size)
        {
             int value = (Size / 100.0) * ExtensionValue;
             resize(Size + (value > 0 ? value : 1));
        }

        Count++;

        //moving of (the elements after _index) one position to the right
        for (int i = Count - 1; i > _index; i--)
        {
            Elements[i] = Elements[i - 1];
        }

        Elements[_index] = _value;

        return *this;
    }

    //(count() > 0 && _index > 0 && _index < count()) ->
    list<T>& Insert(const list<T>& _value, int _index)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
        else if (count() == 0) return *this;
        else if (_index < 0 || _index >= count()) return *this;

        list<T> accumulator(Size + _value.Count);

        //copying of the (elements to the left of _index)
        for (int i = 0; i < _index; i++)
        {
            accumulator[i] = Elements[i];
        }

        //copying of the elements of _value
        for (int i = 0; i < _value.Count; i++)
        {
            accumulator[_index + i] = _value[i];
        }

        //copying of the (elements to the right of _index)
        for (int i = _index; i < Count; i++)
        {
            accumulator[_value.Count + i] = Elements[i];
        }

        accumulator.Count = Count + _value.Count; //->
        copy(accumulator);

        return *this;
    }

    //[1, 2, 3, 4, 5].Move(2, 4) => [1, 2, 4, 5, 3]
    list<T>& Move(int _sourceIndex, int _destinationIndex)
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
        else if (!InRange(_sourceIndex) || !InRange(_destinationIndex)) return *this;

        int smaller = numeric::SmallerOf(_sourceIndex, _destinationIndex);
        int larger = numeric::LargerOf(_sourceIndex, _destinationIndex);

        T sourceElement = Elements[_sourceIndex];

        if (_destinationIndex < _sourceIndex)
        {
            //moving of the sequence (_destinationIndex.._sourceIndex - 1) N positions to the right
            for (int i = _sourceIndex; i > _destinationIndex; i--)
            {
                Elements[i] = Elements[i - 1];
            }
        }
        else if (_destinationIndex > _sourceIndex)
        {
            //moving of the sequence (_sourceIndex.._destinationIndex - 1) N positions to the left
            for (int i = _sourceIndex; i < _destinationIndex; i++)
            {
                Elements[i] = Elements[i + 1];
            }
        }

        Elements[_destinationIndex] = sourceElement;

        return *this;
    }

    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].Reduce(2) => [10, 5, 4, 18, 9, 5]
    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].Reduce(11) => [11, 2, 10, 5, 4, 18, 9, 5, 0, 3]
    list<T>& Reduce(int _reducer)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        return ReduceLeft(_reducer).ReduceRight(_reducer);
    }

    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].ReduceLeft(4) => [4, 18, 9, 5, 0, 3]
    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].ReduceLeft(11) => [11, 2, 10, 5, 4, 18, 9, 5, 0, 3]
    list<T>& ReduceLeft(int _reducer)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        return Remove(0, _reducer - 1);
    }

    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].ReduceRight(4) => [11, 2, 10, 5, 4, 18]
    //[11, 2, 10, 5, 4, 18, 9, 5, 0, 3].ReduceRight(11) => [11, 2, 10, 5, 4, 18, 9, 5, 0, 3]
    list<T>& ReduceRight(int _reducer)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        return Remove(Count - _reducer, Count - 1);
    }

    list<T>& Remove(int _begin, int _end)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
        else if (!InRange(_begin, _end)) return *this;

        list<T> accumulator;

        for (int i = 0; i < _begin; i++)
        {
            accumulator.Append(Elements[i]);
        }

        for (int i = _end + 1; i < Count; i++)
        {
            accumulator.Append(Elements[i]);
        }

        copy(accumulator);

        return *this;
    }

    list<T>& Remove(const Range<int>& _range)
    {
        return Remove(_range.begin(), _range.end());
    }

    list<T>& RemoveAt(int _index, int _length = 1)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
        else if (!InRange(_index)) return *this;
        else if (_length < 1) return *this;

        list<T> accumulator;

        for (int i = 0; i < _index; i++)
        {
            accumulator.Append(Elements[i]);
        }

        for (int i = _index + _length; i < Count; i++)
        {
            accumulator.Append(Elements[i]);
        }

        copy(accumulator);

        return *this;
    }

    //removes the elements that match _value
    //[1, 25, 4, 3, 4, 6, 5, 2, 41, 4, 52, 7, 8, 9].RemoveAll(4) => [1, 25, 3, 6, 5, 2, 41, 52, 7, 8, 9]
    list<T>& RemoveAll(const T& _value)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (element != _value)
            {
                accumulator.Append(element);
            }
        }

        copy(accumulator);

        return *this;
    }

    //removes the elements that match an element in _set
    //[1, 2, 3, 4, 5, 6, 5, 2, 7, 8, 9].RemoveAll(2, 4, 5, 8) => [1, 3, 6, 7, 8, 9]
    list<T>& RemoveAll(const list<T>& _set)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (!_set.Contains(element))
            {
                accumulator.Append(element);
            }
        }

        copy(accumulator);

        return *this;
    }

    list<T>& RemoveIf(const std::function<bool(const T&)>& _predicate)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (!_predicate(element))
            {
                accumulator.Append(element);
            }
        }

        copy(accumulator);

        return *this;
    }

    //[9, 2, 7].Repeat(2) => [9, 2, 7, 9, 2, 7, 9, 2, 7]
    list<T>& Repeat(int _times)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        int originalLength = Count;
        for (int n = 0; n < _times; n++)
        {
            for (int i = 0; i < originalLength; i++)
            {
				//here a copy is needed; Append(Elements[i]) cannot be used because it can lead to incorrect result
                T element = Elements[i];
                Append(element);
            }
        }

        return *this;
    }

    //[5, 9, 0, 3, 7, 18, 4, 2, 6].Replace(4, 7, [2, 6, 1]) => [5, 9, 0, 3, 2, 6, 1, 6]
    list<T>& Replace(int _begin, int _end, const list<T>& _replacement)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
        else if (!InRange(_begin, _end)) return *this;

        Remove(_begin, _end);
        Insert(_replacement, _begin);

        return *this;
    }

    //[5, 9, 0, 3, 7, 18, 4, 2, 6].Replace((4, 7), [2, 6, 1]) => [5, 9, 0, 3, 2, 6, 1, 6]
    list<T>& Replace(const Range<int>& _range, const list<T>& _replacement)
    {
        return Replace(_range.begin(), _range.end(), _replacement);
    }

    //replace every occurrence of _replaced with _replacement
    list<T>& Replace(const T& _replaced, const T& _replacement)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (element == _replaced)
            {
                element = _replacement;
            }
        }

        return *this;
    }

    //replace every occurrence of _replaced with _replacement
    list<T>& Replace(const list<T>& _replaced, const list<T>& _replacement)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        while (true)
        {
            int index = IndexOf(_replaced);

            if (index == -1) break;

            RemoveAt(index, _replaced.count());

            Insert(_replacement, index);
        }

        return *this;
    }

    //[9, 7, 2, 5, 9, 0, 6, 2, 8, 4].Reverse() => [4, 8, 2, 6, 0, 9, 5, 2, 7, 9]
    list<T>& Reverse()
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (int i = 0; i < Count / 2; i++)
        {
            Swap(i, (Count - i) - 1);
        }

        return *this;
    }

	//[1, 2, 3, 4, 5].RotateLeft(3) => [4, 5, 1, 2, 3]
	list<T>& RotateLeft(int _positions = 1)
	{
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

		list<T> newList(Count, true);

		if (_positions > Count)
		{
			_positions = _positions % Count;
		}

		//(EXAMPLE) [1, 2, 3, 4, 5] (2)
		for (int i = _positions, n = 0; i < Count; i++, n++)
		{
			newList[n] = Elements[i];
		} //-> [3, 4, 5, x, x]

		for (int i = 0, n = Count - _positions; i < _positions; i++, n++)
		{
			newList[n] = Elements[i];
		} //-> [x, x, x, 1, 2]

        copy(newList);

		return *this;
	}

	//[1, 2, 3, 4, 5].RotateRight(3) => [3, 4, 5, 1, 2]
	list<T>& RotateRight(int _positions = 1)
	{
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

		list<T> newList(Count, true);

		if (_positions > Count)
		{
			_positions = _positions % Count;
		}

		//(EXAMPLE) [1, 2, 3, 4, 5] (2)

		for (int i = Count - _positions, n = 0; i < Count; i++, n++)
		{
			newList[n] = Elements[i];
		} //-> [4, 5, x, x, x]

		for (int i = 0, n = _positions; i < Count - _positions; i++, n++)
		{
			newList[n] = Elements[i];
		} //-> [x, x, 1, 2, 3]

		copy(newList);

		return *this;
	}

    //performs an unstable sorting
    //<T> implements operator '<' or it is a primitive numerical type ->
    list<T>& SelectionSort(bool _ascending = true)
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (int i = 0; i < Count; i++)
        {
            Swap(&Elements[i], Min(i));
        }

        return _ascending ? *this : Reverse();
    }

    //performs an unstable sorting
    //<T> implements operator '<' or it is a primitive numerical type ->
    list<T>& SelectionSort(const std::function<bool(const T&, const T&)>& _predicate, bool _ascending = true)
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (int i = 0; i < Count; i++)
        {
            T* min = &Elements[i];

            for (int n = i; n < Count; n++)
            {
                T* element = &Elements[n];

                if (_predicate(*element, *min))
                {
                    min = element;
                }
            }

            Swap(&Elements[i], min);
        }

        return _ascending ? *this : Reverse();
    }

    //[9, 1, 5, 3, 0, 4, 7, 0, 6, 5, 1].Set(3, 5, 192) => [9, 1, 5, 192, 192, 192, 7, 0, 6, 5, 1]
    list<T>& Set(int _begin, int _end, const T& _value)
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE)  return *this;
        else if (!InRange(_begin) || !InRange(_end)) return *this;

        for (int i = _begin; i <= _end; i++)
        {
            Elements[i] = _value;
        }

        return *this;
    }

    //[9, 1, 5, 3, 0, 4, 7, 0, 6, 5, 1].Set((3, 5), 192) => [9, 1, 5, 192, 192, 192, 7, 0, 6, 5, 1]
    list<T>& Set(const Range<int>& _range, const T& _value)
    {
        return Set(_range.begin(), _range.end(), _value);
    }

    //[9, 1, 5, 3, 0, 4, 7, 0, 6, 5, 1].Set(3, [8, 2, 0, 1]) => [9, 1, 5, 8, 2, 0, 1, 0, 6, 5, 1]
    list<T>& Set(int _begin, const list<bool>& _value)
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
        else if (!InRange(_begin)) return *this;
        else if (!InRange(_begin + (_value.Count) - 1)) return *this;

        for (int i = 0; i < _value.Count; i++)
        {
            Elements[_begin + i] = _value[i];
        }

        return *this;
    }

    list<T>& Swap(int _index1, int _index2)
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;
        else if (!InRange(_index1) || !InRange(_index2)) return *this;

        T element = Elements[_index1];
        Elements[_index1] = Elements[_index2];
        Elements[_index2] = element;

        return *this;
    }

    //_element1 and _element2 are pointers to elements of the list ->
    list<T>& Swap(T* _element1, T* _element2)
    {
        if (MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        T element = *_element1;
        *_element1 = *_element2;
        *_element2 = element;

        return *this;
    }

    //[2, 2, 2, 5, 9, 0, 6, 2, 2, 2, 2, 2].Trim(2) => [5, 9, 0, 6]
    list<T>& Trim(const T& _value)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        TrimBegin(_value);
        TrimEnd(_value);

        return *this;
    }

    //[2, 2, 2, 5, 9, 0, 6, 2, 2, 2, 2, 2].TrimBegin(2) => [5, 9, 0, 6, 2, 2, 2, 2, 2]
    list<T>& TrimBegin(const T& _value)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (int i = 0; i < Count; i++)
        {
            if (Elements[i] != _value)
            {
                copy(Subrange(i, Count - 1));
                break;
            }

            if (i == Count - 1)
            {
                Clear();
            }
        }

        return *this;
    }

    //[2, 2, 2, 5, 9, 0, 6, 2, 2, 2, 2, 2].TrimEnd(2) => [2, 2, 2, 5, 9, 0, 6]
    list<T>& TrimEnd(const T& _value)
    {
        if (SpatialKind == SpatialKind::SEGMENT || MutabilityKind == MutabilityKind::IMMUTABLE) return *this;

        for (int i = Count - 1; i > -1; i--)
        {
            if (Elements[i] != _value)
            {
                copy(Subrange(0, i));
                break;
            }

            if (i == 0)
            {
                Clear();
            }
        }

        return *this;
    }

    ///NON-MUTATING FUNCTIONS

    //[2, 9, 1].As()<float>() => [2.0, 9.0, 1.0]
    //T is a pointer type ->
    template<typename T> list<T*> As() const
    {
        list<T*> accumulator;

        for (int i = 0; i < Count; i++)
        {
            accumulator.Append(reinterpret_cast<T*>(Elements[i]));
        }

        return accumulator;
    }

    bool BeginsWith(const list<T>& _value) const
    {
        if (Count < _value.Count) return false;

        int counter = 0;

        for (int i = 0; i < _value.Count; i++)
        {
            if (Elements[i] == _value[i])
            {
                counter++;
            }
        }

        return _value.Count == counter;
    }

    //returns 'true' if &this begins with atleast one of the sequences in _value
    //[8, 2, 5, 10, 7, 15, 12, 9, 1].BeginsWith([[5, 9, 1], [8, 1, 5], [9, 12, 0]]) => false
    //[8, 2, 5, 10, 7, 15, 12, 9, 1].BeginsWith([[5, 9, 1], [8, 2, 5], [9, 12, 0]]) => true
    bool BeginsWith(const list<list<T>>& _values) const
    {
        for (const list<T>& __value : _values)
        {
            if (BeginsWith(__value))
            {
                return true;
            }
        }

        return false;
    }

    //returns the index of the specified element (if the elements exists)
    //the specified value does not exist => -1
    //the list is sorted in ascending order ->
    int BinarySearch(const T& _value) const
    {
        int segmentBegin = 0;
        int middleIndex = Count / 2;
        int segmentEnd = Count - 1;

        while (true)
        {
            if (middleIndex == Count)
            {
                return -1;
            }

            T& element = Elements[middleIndex];

            if (element == _value)
            {
                return middleIndex;
            }
            //(STATE) no match; check if the search must continue in the left segment
            else if (_value < Elements[middleIndex])
            {
                 segmentEnd = middleIndex;

                int segmentLength = segmentEnd - segmentBegin;

                if (segmentLength >= 2)
                {
                    middleIndex = segmentBegin + (segmentLength / 2);
                }
                else
                {
                    middleIndex--;
                }
            }
            //(STATE) the search must continue in the right segment
            else
            {
                segmentBegin = middleIndex;

                int segmentLength = segmentEnd - segmentBegin;

                if (segmentLength >= 2)
                {
                    middleIndex = segmentBegin + (segmentLength / 2);
                }
                else
                {
                    middleIndex++;
                }
            }
        }

        return -1;
    }

    //returns copy of &this
    list<T> Clone() const
    {
        return *this;
    }

    bool Contains(const T& _value) const
    {
        for (int i = 0; i < Count; i++)
        {
            if (Elements[i] == _value)
            {
                return true;
            }
        }

        return false;
    }

    //[1, 2, 3, 4, 5, 6, 7, 8, 9].Contains([2, 3, 4]) => true
    bool Contains(const list<T>& _value) const
    {
        for (int i = 0, matches = 0; i < Size - _value.Count;)
        {
            if ((*this)[i + matches] == _value[matches])
            {
                matches++;
            }
            else
            {
                matches = 0;
                i++;
            }

            if (matches == _value.Count)
            {
                return true;
            }
        }

        return false;
    }

    bool Contains(const std::function<bool(const T&)>& _predicate) const
    {
        for (int i = 0; i < Count; i++)
        {
            if (_predicate(Elements[i]))
            {
                return true;
            }
        }

        return false;
    }

    bool ContainsAll(const list<T>& _set) const
    {
        for (const T& __element : _set)
        {
            if (!(*this).Contains(__element))
            {
                return false;
            }
        }

        return true;
    }

    //[9, 7, 3, 20, 15, 18, 4, 7].ContainsAny([21, 8, 5, 1]) => false
    //[9, 7, 3, 20, 15, 18, 4, 7].ContainsAny([6, 30, 3, 1]) => true
    bool ContainsAny(const list<T>& _set) const
    {
        for (int i = 0; i < Count; i++)
        {
            for (int n = 0; n < _set.count(); n++)
            {
                if (Elements[i] == _set[n])
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool ContainsOnly(const T& _value) const
    {
        for (int i = 0; i < Count; i++)
        {
            if (Elements[i] != _value)
            {
                return false;
            }
        }

        return true;
    }

    //[9, 1, 0, 3, 1, 5, 9, 1, 15, 3, 7, 5, 9, 1, 1].ContainsOnly([1, 9, 10]) => false
    //[9, 1, 0, 3, 1, 5, 9, 1, 15, 3, 7, 5, 9, 1, 1].ContainsOnly([5, 9, 1, 0, 7, 3, 15]) => true
    bool ContainsOnly(const list<T>& _set) const
    {
        if (Count == 0) return false;

        for (int i = 0; i < Count; i++)
        {
            if (!_set.Contains(Elements[i]))
            {
                return false;
            }
        }

        return true;
    }

    bool ContainsOnly(const std::function<bool(const T&)>& _predicate) const
    {
        if (Count == 0) return false;

        for (int i = 0; i < Count; i++)
        {
            if (!_predicate(Elements[i]))
            {
                return false;
            }
        }

        return true;
    }

    int CountOf(const T& _value) const
    {
        int accumulator = 0;

        for (int i = 0; i < Count; i++)
        {
            if (Elements[i] == _value)
            {
                accumulator++;
            }
        }

        return accumulator;
    }

    //[5, 9, 1, 0, 3, 5, 9, 1, 4, 5, 9, 1, 10, 15, 3, 7, 5, 9, 1, 1].CountOf([5, 9, 1]) => 4
    //[5, 9, 1, 0, 3, 5, 9, 1, 4, 5, 9, 1, 10, 15, 3, 7, 5, 9, 1, 1].CountOf([5, 9, 1, 7]) => 0
    int CountOf(const list<T>& _value) const
    {
        if (_value.Count == 0) return 0;

        int count = 0;

        for (int i = 0; i < Count; i++)
        {
            if (Subrange(i, (i + _value.Count) - 1) == _value)
            {
                i += _value.Count - 1;
                count++;
            }
        }

        return count;
    }

    int CountOf(const std::function<bool(const T&)>& _predicate) const
    {
        int count = 0;

        for (int i = 0; i < Count; i++)
        {
            if (_predicate(Elements[i]))
            {
                count++;
            }
        }

        return count;
    }

    //[7, 8, 3, 19, 20, 71, 15, 71, 3, 31, 108, 3]).Duplicates() => [3, 71]
    list<T> Duplicates() const
    {
        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            for (int n = i + 1; n < Count; n++)
            {
                if (Elements[i] == Elements[n] && !accumulator.Contains(Elements[i]))
                {
                    accumulator.Append(Elements[i]);
                }
            }
        }

        return accumulator;
    }

    bool EndsWith(const list<T>& _value) const
    {
        if (Count < _value.Count) return false;

        int counter = 0;
        for (int i = Count - 1, n = _value.Count - 1; (i > - 1) && (n > - 1); i--, n--)
        {
            if (Elements[i] == _value[n])
            {
                counter++;
            }
        }

        return _value.Count == counter;
    }

    bool EndsWith(const list<list<T>>& _values) const
    {
        for (const list<T>& __value : _values)
        {
            if (EndsWith(__value))
            {
                return true;
            }
        }

        return false;
    }

    //[2, 9, 0, 1, 4, 9, 7, 3].Except(9) => [2, 0, 1, 4, 7, 3]
    list<T> Except(const T& _value) const
    {
        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (element != _value)
            {
                accumulator.Append(element);
            }
        }

        return accumulator;
    }

    //[2, 9, 0, 1, 4, 9, 7, 3].Except([9, 7, 0]) => [2, 1, 4, 3]
    list<T> Except(const list<T>& _set) const
    {
        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (!_set.Contains(element))
            {
                accumulator.Append(element);
            }
        }

        return accumulator;
    }

    list<T> Except(const std::function<bool(const T&)>& _predicate) const
    {
        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (!_predicate(element))
            {
                accumulator.Append(element);
            }
        }

        return accumulator;
    }

    //(if the element specified by the predicate is present in the list) the function returns a pointer to it
    //(if the element specified by the predicate is not present in the list) the functions returns a null pointer
    T* First(const std::function<bool(const T&)>& _predicate) const
    {
        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (_predicate(element))
            {
                return &element;
            }
        }

        return nullptr;
    }

    //there is an implicit conversion from <T> to <A> ->
    template<typename A> list<A> Generate() const
    {
        list<A> accumulator;

        for (int i = 0; i < Count; i++)
        {
            accumulator.Append(A(Elements[i]));
        }

        return accumulator;
    }

    /* struct Item { int Price; Item() = default; Item(int _price): Price(_price) {} };
        Item a(5);
        Item b(2);
        Item c(35);
        list<Item> items { a, b, c };
        list<int> l = items.Generate<int>([](const Item& _item) { return _item.Price * 2; }); => [10, 4, 70] */
    template<typename A> list<A> Generate(const std::function<A(const T&)>& _generator) const
    {
        list<A> accumulator;

        for (int i = 0; i < Count; i++)
        {
            accumulator.Append(_generator(Elements[i]));
        }

        return accumulator;
    }

    //it checks whether the list contains an element with the specified index
    bool Has(int _index) const
    {
        return _index < Count;
    }

    bool HasDuplicates() const
    {
        for (int i = 0; i < Count; i++)
        {
            for (int n = 0; n < Count; n++)
            {
                if (Elements[i] == Elements[n])
                {
                    return true;
                }
            }
        }

        return false;
    }

    //the specified value does not exist or _begin is outside the range of list => -1
    int IndexOf(const T& _value, int _begin = 0) const
    {
        if (!InRange(_begin)) return -1;

        for (int i = _begin; i < Count; i++)
        {
            if (Elements[i] == _value)
            {
                return i;
            }
        }

        return - 1;
    }

    //the specified value does not exist or _begin is outside the range of list => -1
    int IndexOf(const list<T>& _value, int _begin = 0) const
    {
        if (!InRange(_begin)) return -1;

        for (int i = _begin, matches = 0; i < Count && matches < _value.Count; i++)
        {
            if (Elements[i] == _value[matches])
            {
                matches++;
            }
            else
            {
                i -= matches;
                matches = 0;
            }

            if (matches == _value.Count)
            {
                return (i - _value.Count) + 1;
            }
        }

        return -1;
    }

    //the specified value does not exist or _begin is outside the range of list => -1
    int IndexOf(const std::function<bool(const T&)>& _predicate, int _begin = 0) const
    {
        if (!InRange(_begin)) return -1;

        for (int i = _begin; i < Count; i++)
        {
            if (_predicate(Elements[i]))
            {
                return i;
            }
        }

        return - 1;
    }

    //the specified value does not exist or _begin is outside the range of list => -1
    int IndexOfAny(const list<T>& _set, int _begin = 0) const
    {
        if (!InRange(_begin)) return -1;

        for (int i = _begin; i < Count; i++)
        {
            for (const T& __element : _set)
            {
                if (Elements[i] == __element)
                {
                    return i;
                }
            }
        }

        return - 1;
    }

	//_begin is outside the range of list => -2
	//[].IndexOf(4) => -1
    //[9, 9, 9, 5, 8, 10, 2, 7].IndexOfNot(9) => 3
    //[9, 9, 9, 5, 8, 10, 2, 7].IndexOfNot(4) => 0
    int IndexOfNot(const T& _value, int _begin = 0) const
    {
        if (!InRange(_begin)) return -2;

        for (int i = _begin; i < Count; i++)
        {
            if (Elements[i] != _value)
            {
                return i;
            }
        }

        return -1;
    }

	//_begin is outside the range of string => -2
	//[].IndexOf(4) => -1
	//[9, 9, 9, 5, 8, 10, 2, 7].IndexOfNot([](const CodePoint& x) { return x == 9; }) => 3
	//[9, 9, 9, 5, 8, 10, 2, 7].IndexOfNot(4) => 0
    int IndexOfNot(const std::function<bool(const T&)>& _predicate, int _begin = 0) const
    {
        if (!InRange(_begin)) return -2;

        for (int i = _begin; i < Count; i++)
        {
            if (!_predicate(Elements[i]))
            {
                return i;
            }
        }

        return -1;
    }

    /* A = [5, 0, 3, 6]
       B = [3, 2, 4, 5, 9]
        IntersectionOf(A, B) => [3, 5] */
    static list<T> IntersectionOf(const list<T>& _list1, const list<T>& _list2)
    {
        list<T> accumulator;

        for (int i = 0; i < _list1.count(); i++)
        {
            T& element = _list1[i];

            if (_list2.Contains(element) && !accumulator.Contains(element))
            {
                accumulator.Append(element);
            }
        }

        return accumulator;
    }

    //count() > 1 ->
    bool IsHeterogeneous() const
    {
        for (int i = 1; i < Count; i++)
        {
            if (Elements[i - 1] != Elements[i])
            {
                return true;
            }
        }

        return false;
    }

    //count() > 1 ->
    bool IsHomogeneous() const
    {
        for (int i = 1; i < Count; i++)
        {
            if (Elements[i - 1] != Elements[i])
            {
                return false;
            }
        }

        return true;
    }

	//the specified value does not exist => -1
    int LastIndexOf(const T& _value) const
    {
        for (int i = Count - 1; i > - 1; i--)
        {
            if (Elements[i] == _value)
            {
                return i;
            }
        }

        return -1;
    }

	//the specified value does not exist => -1
    int LastIndexOf(const list<T>& _value) const
    {
        int index = -1;

        while (true)
        {
            int index_ = IndexOf(_value, index + _value.Count);

            if (index_ == -1)
            {
                return index;
            }
            else
            {
                index = index_;
            }
        }
    }

	//the specified value does not exist => -1
    int LastIndexOf(const std::function<bool(const T&)>& _predicate) const
    {
        for (int i = Count - 1; i > - 1; i--)
        {
            if (_predicate(Elements[i]))
            {
                return i;
            }
        }

        return - 1;
    }

    //return the maximum element in the range (_begin, Count - 1)
    //count() == 0 => nullptr
    //_begin is outside the range of list => nullptr
	//<T> implements operator '>' or it is a primitive numerical type ->
    T* Max(int _begin = 0) const
    {
        if (Count == 0) return nullptr;
        else if (!InRange(_begin)) return nullptr;

        T* max = &Elements[_begin];

        for (int i = _begin; i < Count; i++)
        {
            T* element = &Elements[i];

            if (*element > *max)
            {
                max = element;
            }
        }

        return max;
    }

    //return the minimum element in the range (_begin, Count - 1)
    //count() == 0 => nullptr
    //_begin is outside the range of list => nullptr
    //<T> implements operator '>' or it is a primitive numerical type ->
    T* Min(int _begin = 0) const
    {
        if (Count == 0) return nullptr;
        else if (!InRange(_begin)) return nullptr;

        T* min = &Elements[_begin];

        for (int i = _begin; i < Count; i++)
        {
            T* element = &Elements[i];

            if (*element < *min)
            {
                min = element;
            }
        }

        return min;
    }

    //returns only values that are (between the beginning and a separator), (between separator and the end) or (between two separators)
    //empty sequences are generated (and eventually are appended to the result) only if they are between two separators
    //_ignoreEmptyValues = true -> empty sequences (if there are any) are not appended to the result
    //[41, 56, 3, 7, 18, 5, 19, 76, 15].Multisplit([353, 12]) => []
    //[41, 56, 3, 7, 18, 5, 19, 76, 15, 9, 20, 5].Multisplit([56, 9]) => [[41], [3, 7, 18, 5, 19, 76, 15], [20, 5]]
    //[9, 41, 56, 3, 7, 18, 5, 19, 76, 15, 9, 9, 20, 7].Multisplit([7, 9]) => [[41, 56, 3], [18, 5, 19, 76, 15], [], [20]]
    //[9, 41, 56, 3, 7, 18, 5, 19, 76, 15, 9, 9, 20, 7].Multisplit([7, 9], true) => [[41, 56, 3], [18, 5, 19, 76, 15], [20]]
    list<list<T>> Multisplit(const list<T>& _set, bool _ignoreEmptyValues = false) const
    {
        list<list<T>> accumulator;

        for (int i = 0; i < Count; i++)
        {
            bool match = _set.Contains(Elements[i]);
            int index = IndexOf([&](T x){ return _set.Contains(x); }, i + 1);

            //[separator, separator]
            if (match && index == i + 1 && !_ignoreEmptyValues)
            {
                accumulator.Append(list<T> {});
            }
            //[!separator...separator]
            else if (!match && index >= i + 1)
            {
                accumulator.Append(Subrange(i, index - 1));
                i = index - 1;
            }
            //[separator...]
			else if (match && index == -1)
			{
				accumulator.Append(Subrange(i + 1, Count - 1));
				break;
			}
            //[!separator...]
            else if (!match && index == - 1)
            {
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
    Range<int> RangeOf(const list<T>& _set, int _startIndex = 0) const
    {
        if (!InRange(_startIndex)) return {};

        for (int i = _startIndex, n = -1; i < Count; i++)
        {
            bool equality = _set.Contains(Elements[i]);

            if (n == -1 && equality)
            {
                n = i;
            }
            else if (n > - 1 && !equality)
            {
                return Range<int>(n, i - 1);
            }
            else if (n > - 1 && i == Count - 1)
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
    Range<int> RangeOfNot(const list<T>& _set, int _startIndex = 0) const
    {
        if (!InRange(_startIndex)) return {};

        for (int i = _startIndex, n = - 1; i < Count; i++)
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
            else if (n > - 1 && i == Count - 1)
            {
                return Range<int>(n, i);
            }
        }

        return { -1, -1 };
    }

    //returns only values that are (between the beginning and a separator), (between separator and the end) or (between two separators)
    //empty sequences are generated (and eventually are appended to the result) only if they are between two separators
    //_ignoreEmptyValues = true -> empty sequences (if there are any) are not appended to the result
    //[3, 7, 18, 5, 19, 76, 15].Split(353) => []
    //[18, 5, 19, 76, 15, 9, 20, 5].Split(9) => [[18, 5, 19, 76, 15], [20, 5]]
    //[56, 3, 7, 18, 5, 19, 76, 7].Split(7) => [[56, 3], [18, 5, 19, 76], []]
    //[56, 7, 7, 18, 5, 19, 76, 15, 9].Split(7) => [[56], [], [18, 5, 19, 76, 15, 9]]
    //[56, 7, 7, 18, 5, 19, 76, 15, 9].Split(7, true) => [[56], [18, 5, 19, 76, 15, 9]]
    //[7, 41, 56, 7, 18, 76, 15, 9, 7].Split(7) => [[41, 56], [18, 76, 15, 9]]
    //[7, 41, 56, 7, 7, 7, 18, 5, 15].Split(7) => [[41, 56], [], [], [18, 5, 15]]
    //[7, 41, 56, 7, 7, 7, 18, 5, 15].Split(7, true) => [[41, 56], [18, 5, 15]]
    list<list<T>> Split(const T& _separator, bool _ignoreEmptyValues = false) const
    {
        list<list<T>> accumulator;

        for (int i = 0; i < Count; i++)
        {
            bool match = Elements[i] == _separator;
            int index = IndexOf(_separator, i + 1);

            //[separator, separator]
            if (match && index == i + 1 && !_ignoreEmptyValues)
            {
                accumulator.Append(list<T> {});
            }
            //[!separator...separator]
            else if (!match && index >= i + 1)
            {
                accumulator.Append(Subrange(i, index - 1));
                i = index - 1;
            }
			//[separator...]
			else if (match && index == -1)
			{
				accumulator.Append(Subrange(i + 1, Count - 1));
				break;
			}
            //[!separator...]
            else if (!match && index == - 1)
            {
                break;
            }	
        }

        return accumulator;
    }

    //returns only values that are (between the beginning and a separator), (between separator and the end) or (between two separators)
    //empty sequences are generated (and eventually are appended to the result) only if they are between two separators
    //_ignoreEmptyValues = true -> empty sequences (if there are any) are not appended to the result
    //[41, 56, 3, 5, 7, 18, 5, 19, 76, 15].Split([3, 8]) => []
    //[41, 56, 3, 5, 7, 18, 5, 19, 9, 7, 76, 15, 9].Split([9, 7]) => [[41, 56, 3, 5, 7, 18, 5, 19], [76, 15, 9]]
    //[41, 56, 3, 9, 7, 18, 5, 19, 76, 15, 9, 20, 9, 7].Split([9, 7]) => [[41, 56, 3], [18, 5, 19, 76, 15, 9, 20]]
    //[41, 56, 9, 7, 9, 7, 18, 5, 19, 76, 15, 9, 20, 3].Split([9, 7]) => [[41, 56], [], [18, 5, 19, 76, 15, 9, 20, 3]]
    //[41, 56, 9, 7, 9, 7, 18, 5, 19, 76, 15, 9, 20, 3].Split([9, 7], true) => [[41, 56], [18, 5, 19, 76, 15, 9, 20, 3]]
    //[9, 7, 41, 56, 9, 9, 7, 18, 76, 15, 9, 20, 3, 9, 7].Split([9, 7]) => [[41, 56, 9], [18, 76, 15, 9, 20, 3]]
    //[9, 7, 41, 56, 9, 7, 9, 7, 9, 7, 18].Split([9, 7]) => [[41, 56], [], [], [18]]
    //[9, 7, 41, 56, 9, 7, 9, 7, 9, 7, 18].Split([9, 7], true) => [[41, 56], [18]]
    list<list<T>> Split(const list<T>& _separator, bool _ignoreEmptyValues = false) const
    {
        list<list<T>> accumulator;

        for (int i = 0; i < Count; i++)
        {
            bool match = list<T>(*this, i, i + _separator.count() - 1) == _separator;
            int index = IndexOf(_separator, i + 1);

            //[separator, separator]
            if (match && index == i + _separator.count() && !_ignoreEmptyValues)
            {
                accumulator.Append(list<T> {});
                i = index - 1;
            }
            //[separator, separator]
            else if (match && index == i + _separator.count() && _ignoreEmptyValues)
            {
                i = index - 1;
            }
            //[!separator...separator]
            else if (!match && index >= i)
            {
                accumulator.Append(Subrange(i, index - 1));
                i = index - 1;
            }
			//[separator...]
			else if (match && index == -1)
			{
				accumulator.Append(Subrange(i + 1, Count - 1));
				break;
			}
            //[!separator...]
            else if (!match && index == - 1)
            {
                break;
            }
            //[separator, value, separator]
            else if (match && (index > i + _separator.count() || index == - 1))
            {
                i += _separator.count() - 1;
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
    //[3, 7, 18, 5, 19, 76, 15].Split([](int x) { return x == 353; }) => []
    //[18, 5, 19, 76, 15, 9, 20, 5].Split([](int x) { return x == 9; }) => [[18, 5, 19, 76, 15], [20, 5]]
    //[56, 3, 7, 18, 5, 19, 76, 7].Split([](int x) { return x == 7; }) => [[56, 3], [18, 5, 19, 76]]
    //[56, 7, 7, 18, 5, 19, 76, 15, 9].Split([](int x) { return x == 7; }) => [[56], [], [18, 5, 19, 76, 15, 9]]
    //[56, 7, 7, 18, 5, 19, 76, 15, 9].Split([](int x) { return x == 7; }, true) => [[56], [18, 5, 19, 76, 15, 9]]
    //[7, 41, 56, 7, 18, 76, 15, 9, 7].Split([](int x) { return x == 7; }) => [[41, 56], [18, 76, 15, 9]]
    //[7, 41, 56, 7, 7, 7, 18, 5, 15].Split([](int x) { return x == 7; }) => [[41, 56], [], [], [18, 5, 15]]
    //[7, 41, 56, 7, 7, 7, 18, 5, 15].Split([](int x) { return x == 7; }, true) => [[41, 56], [18, 5, 15]]
    list<list<T>> Split(const std::function<bool(const T&)>& _predicate, bool _ignoreEmptyValues = false) const
    {
        list<list<T>> accumulator;

        for (int i = 0; i < Count; i++)
        {
            bool match = _predicate(Elements[i]);
            int index = IndexOf(_predicate, i + 1);

            //[separator, separator]
            if (match && index == i + 1 && !_ignoreEmptyValues)
            {
                accumulator.Append(list<T> {});
            }
            //[!separator...separator]
            else if (!match && index >= i + 1)
            {
                accumulator.Append(Subrange(i, index - 1));
                i = index - 1;
            }
			//[separator...]
			else if (match && index == -1)
			{
				accumulator.Append(Subrange(i + 1, Count - 1));
				break;
			}
            //[!separator...]
            else if (!match && index == - 1)
            {
                break;
            }
        }

        return accumulator;
    }

    //_length = 0 => [_begin..]
    //(_begin + _length) > count() => {}
    list<T> Sublist(int _begin, int _length = 0) const
    {
        if (!InRange(_begin)) return {};

        int end = _length == 0 ? Count : _begin + _length;

        list<T> accumulator(_length, false);

        for (int i = _begin; i < end; i++)
        {
            accumulator.Append(Elements[i]);
        }

        return accumulator;
    }

    //[5, 8, 4, 1, 9, 6, 2, 3, 0, 5, 5, 1, 7].Subrange(2, 5) => [4, 1, 9, 6]
    list<T> Subrange(int _begin, int _end) const
    {
        if (!InRange(_begin, _end)) return {};

        list<T> accumulator((_end - _begin) + 1, false);

        for (int i = _begin; i < _end + 1; i++)
        {
            accumulator.Append(Elements[i]);
        }

        return accumulator;
    }

    //[5, 8, 4, 1, 9, 6, 2, 3, 0, 5, 5, 1, 7].Subrange((2, 5)) => [4, 1, 9, 6]
    list<T> Subrange(const Range<int>& _range) const
    {
        return Subrange(_range.begin(), _range.end());
    }

    list<T> Where(const std::function<bool(const T&)>& _predicate) const
    {
        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (_predicate(element))
            {
                accumulator.Append(element);
            }
        }

        return accumulator;
    }

    /* A = [8, 19, 2, 5, 5, 0, 2, 7, 10, 4]
       B = [23, 21, 4, 7, 5, 19, 17, 26]
       UnionOf(A, B) => [8, 19, 2, 5, 0, 7, 10, 4, 23, 21, 17, 26] */
    static list<T> UnionOf(const list<T>& _list1, const list<T>& _list2)
    {
        list<T> accumulator;

        for (int i = 0; i < _list1.count(); i++)
        {
            T& element = _list1[i];

            if (!accumulator.Contains(element))
            {
                accumulator.Append(element);
            }
        }

        for (int i = 0; i < _list2.count(); i++)
        {
            T& element = _list2[i];

            if (!accumulator.Contains(element))
            {
                accumulator.Append(element);
            }
        }

        return accumulator;
    }

    //[21, 35, 2, 9, 40, 31, 52, 9, 24, 52, 35, 18].Unique() => [21, 35, 2, 9, 40, 31, 24, 18]
    list<T> Unique() const
    {
        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

              if (!accumulator.Contains(element))
              {
                  accumulator.Append(element);
              }
        }

        return accumulator;
    }

    //[21, 35, 2, 9, 40, 31, 52, 9, 24, 52, 35, 18].Until(52) => [21, 35, 2, 9, 40, 31, 52, 9, 24]
    list<T> Until(const T& _value) const
    {
        list<T> accumulator;

        for (int i = 0; i < Count; i++)
        {
            T& element = Elements[i];

            if (element != _value)
            {
                accumulator.Append(element);
            }
            else
            {
                return accumulator;
            }
        }

        return accumulator;
    }

    ///

    //_size is the new size (number of elements, not bytes) of the list
	 void resize(int _size)
     {
         T* oldElements = Elements;

         Elements = new T[_size];

         //if the list is being extended
         if (_size > Size)
         {
             for (int i = 0; i < Count; i ++)
             {
                 Elements[i] = oldElements[i];
             }
         }
         //if the list is being shrinked
         else if (_size < Size)
         {
             for (int i = 0; i < _size; i ++)
             {
                 Elements[i] = oldElements[i];
             }

             Count = _size;
         }

         Size = _size;

         delete[] oldElements;
     }
};
