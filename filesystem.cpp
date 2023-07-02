namespace filesystem
{
    using byte_operations::LE;
    using unicode::CodePoint;
    using unicode::utf16;
    using unicode::utf32;

    //Errors:
    const char E_UNSUCCESSFUL_OPERATION = -1;
    const char E_UNKNOWN_ERROR = -2;
    //------------------------------------------
    const char E_FILE_DOES_NOT_EXIST = -3;
    const char E_DIRECTORY_DOES_NOT_EXIST = -4;
    const char E_SOURCE_DIRECTORY_DOES_NOT_EXIST = -5;
    const char E_DESTINATION_DIRECTORY_DOES_NOT_EXIST = -6;
    const char E_FILE_ALREADY_EXISTS = -7;
    const char E_DIRECTORY_ALREADY_EXISTS = -8;
    //------------------------------------------
    const char E_INVALID_PATH = -9;
    const char E_INVALID_SOURCE_PATH = -10;
    const char E_INVALID_DESTINATION_PATH = -11;
    //------------------------------------------
    const char E_EMPTY_NAME = -12;
    const char E_NAME_CONTAINS_INVALID_CHARACTERS = -13;
    const char E_NAME_ENDS_WITH_EMPTY_SPACE = -14;
    const char E_NAME_HAS_FORBIDDEN_VALUE = -15;
    //------------------------------------------
    const char E_FILENAME_CONTAINS_INVALID_CHARACTERS = -16;
    const char E_FILENAME_ENDS_WITH_EMPTY_SPACE = -17;
    const char E_EMPTY_FILENAME = -18;
    const char E_MISSING_EXTENSION = -19;
    const char E_FILE_EXTENSION_CONTAINS_INVALID_CHARACTERS = -20;
    //------------------------------------------
    const char E_INVALID_ROOT_ELEMENT = -21;
    const char E_PATH_MISSING_FINAL_ELEMENT = -22;
    const char E_EMPTY_PATH = -23;
    const char E_EMPTY_PATH_ELEMENT = -24;
    const char E_PATH_ELEMENT_ENDS_WITH_EMPTY_SPACE = -25;
    const char E_PATH_CONTAINS_INVALID_CHARACTERS = -26;
    const char E_PATH_TOO_LONG = -27;
    //------------------------------------------
    const char E_FILE_NOT_BOUND = -28;
    const char E_READONLY_FILE = -29;
    const char E_ACCESS_DENIED = -30;
    const char E_SYSTEM_FILE_MANIPULATION_ATTEMPT = -31;
    const char E_SYSTEM_DIRECTORY_MANIPULATION_ATTEMPT = -32;
    //------------------------------------------
    const char E_INDEX_OUT_OF_RANGE = -33;
    const char E_FIRST_INDEX_LARGER_THAN_SECOND_INDEX = -34;

    /* TERMINOLOGY:
       - (directory path) (EXAMPLE) "E:\Compiler\parser"
       - (filepath) (EXAMPLE) "E:\Compiler\parser.bca"
       - (name) (EXAMPLE) "E:\Compiler\parser.bca" => "parser"
                (EXAMPLE) "E:\Compiler\Lexer" => "Lexer"
       - (filename) (EXAMPLE) "E:\Compiler\parser.bca" => "parser.cpp"
       - (extension) (EXAMPLE) "E:\Compiler\parser.cpp" => "cpp"
       - (root element) (EXAMPLE) "E:\Compiler\parser.cpp" => "E:"
       - (non-root element) (EXAMPLE) "E:\Compiler\parser.cpp" => "Compiler", "parser.cpp"
       - (stem element :: an element that is not (the root element or the last element)) (EXAMPLE) "E:\Compiler\parser.cpp" => "Compiler"
       - (syntactically valid path :: a path that is syntactically valid but not necessarily referring to an existing physical file)
       - (existentially valid path :: a path that is referring to an existing physical file) */

    /* (!) the functions accept only absolute paths
       (!) a path cannot begins with an empty space
       (!) a path must begins with (a letter from the English alphabet) followed by ':' or '\'
       (!) a path cannot have an empty stem element
       (!) a stem element cannot contain invalid characters
       (!) the length of a path cannot be larger than (&MAX_PATH - 1)
       (!) access to some system directories may be redirected (for example '...\Windows\System32' -> '...\Windows\SysWOW64' on 64-bit Windows) */

    const string TEMPORARY_FILE_NAME = "gxzjzrtkfrgtytsdgq4g(gbcjowna;ktlhklssvwh9eixmoqwjdw3b97vhjzgsr.";

    //(REFERENCE) https://docs.microsoft.com/en-us/windows/win32/fileio/naming-a-file#naming-conventions
    const list<CodePoint> INVALID_NAME_CHARACTERS{ 0, '.', ':', '/', '\\', '*', '?', '"', '<', '>', '|' };

    //(REFERENCE) https://docs.microsoft.com/en-us/windows/win32/fileio/naming-a-file#naming-conventions
    const list<string> INVALID_NAME_VALUES{ "CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5",
        "COM6", "COM7", "COM8", "COM9", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9" };

    //"" => E_EMPTY_NAME
    //"ocea:n" => E_NAME_CONTAINS_INVALID_CHARACTERS
    //"LPT3" => E_NAME_HAS_FORBIDDEN_VALUE
    //"   " => E_NAME_ENDS_WITH_EMPTY_SPACE;
    //"ocean " => E_NAME_ENDS_WITH_EMPTY_SPACE;
    //_name is a valid name => 0
    int IsValidName(const string& _name)
    {
        if (_name.characterCount() == 0)
        {
            return E_EMPTY_NAME;
        }
        else if (_name.ContainsAny(INVALID_NAME_CHARACTERS))
        {
             return E_NAME_CONTAINS_INVALID_CHARACTERS;
        }
        else if(INVALID_NAME_VALUES.Contains(_name))
        {
            return E_NAME_HAS_FORBIDDEN_VALUE;
        }
        else if (_name.EndsWith(' '))
        {
             return E_NAME_ENDS_WITH_EMPTY_SPACE;
        }

        return 0;
    }

    //".jpeg" => E_EMPTY_NAME
    //" .jpeg" => E_NAME_ENDS_WITH_EMPTY_SPACE
    //"ocean" => E_MISSING_EXTENSION
    //"ocea:n.jpeg" => E_FILENAME_CONTAINS_INVALID_CHARACTERS
    //"ocean.jpeg " => E_FILENAME_ENDS_WITH_EMPTY_SPACE
    //"ocean.jpeg" => 0
    //"ocean." => 0
    //_filename is a valid filename => 0
    int IsValidFilename(const string& _filename)
    {
        int indexOfDot = _filename.IndexOf('.');

        if (indexOfDot == -1) return E_MISSING_EXTENSION;

        string name = _filename.Subrange(0, indexOfDot - 1);

        if (name.characterCount() == 0) return E_EMPTY_NAME;

        if (name[name.characterCount() - 1] == ' ') return E_NAME_ENDS_WITH_EMPTY_SPACE;

        int result = IsValidName(name);

        if (result != 0) return result;

        string extension = _filename.Sublist(indexOfDot + 1);

        if (extension.EndsWith(string(' ')))
        {
            return E_FILENAME_ENDS_WITH_EMPTY_SPACE;
        }
        else if (extension.ContainsAny(INVALID_NAME_CHARACTERS))
        {
            return E_FILE_EXTENSION_CONTAINS_INVALID_CHARACTERS;
        }

        return 0;
    }

//"" => E_EMPTY_PATH
//"Es\pictures\travels" => E_INVALID_ROOT_ELEMENT
//"E:\pictures\travels \" => E_MISSING_FINAL_ELEMENT
//"E:\pictures\travels \desert" => E_PATH_ELEMENT_ENDS_WITH_EMPTY_SPACE
//"E:\pictures\fo:rest" => E_PATH_CONTAINS_INVALID_CHARACTERS
//"E:\pictures\travels\desert" => 0
//_path is a valid directory path => 0
int IsValidDirectoryPath(const string& _path)
{
    //if the path is empty
    if (_path.characterCount() == 0)
    {
        return E_EMPTY_PATH;
    }
    //if the path length exceeds MAX_PATH
    else if (_path.characterCount() > MAX_PATH - 1/*because of the string terminator*/)
    {
        return E_PATH_TOO_LONG;
    }
    //if the first character is not a letter from the English alphabet
    else if (_path[0] < 65 && _path[0] > 90)
    {
        return E_INVALID_ROOT_ELEMENT;
    }
    //if the second character is not ':'
    else if (_path.characterCount() >= 2 && _path[1] != ':')
    {
        return E_INVALID_ROOT_ELEMENT;
    }
    //if the third character is not '\'
    else if (_path.characterCount() >= 3 && _path[2] != '\\')
    {
        return E_INVALID_ROOT_ELEMENT;
    }
    //if the path ends with '\'
    else if (_path.EndsWith('\\'))
    {
        return E_PATH_MISSING_FINAL_ELEMENT;
    }

    //(STATE) _path begins with "<A-Z>:\\"

    //validation of the stem elements

    list<string> stemElements = _path.Clone().ReduceLeft(3).Split('\\');

    for (int i = 0; i < stemElements.count(); i++)
    {
        string& stemElement = stemElements[i];

        //if the element is empty
        if (stemElement.characterCount() == 0)
        {
            return E_EMPTY_PATH_ELEMENT;
        }
        //if the elementy ends with ' '
        else if (stemElement[stemElement.characterCount() - 1] == ' ')
        {
            return E_PATH_ELEMENT_ENDS_WITH_EMPTY_SPACE;
        }
        //if the element is not the root element and it contains invalid characters
        else if (i > 0 && stemElement.ContainsAny(INVALID_NAME_CHARACTERS))
        {
            return E_PATH_CONTAINS_INVALID_CHARACTERS;
        }
    }

    return 0;
}

//"" => E_EMPTY_PATH
//"Es\pictures\travels \291.jpg" => E_INVALID_ROOT_ELEMENT
//"E:\pictures\travels \" => E_MISSING_FINAL_ELEMENT
//"E:\pictures\travels \291.jpg" => E_PATH_ELEMENT_ENDS_WITH_EMPTY_SPACE
//"E:\pictures\travels\291.jpg" => 0
//_path is a valid file path => 0
int IsValidFilePath(const string& _path)
{
    //if the path is empty
    if (_path.size() == 0)
    {
        return E_EMPTY_PATH;
    }
    //if the path length exceeds MAX_PATH
    else if (_path.characterCount() > MAX_PATH - 1/*because of the string terminator*/)
    {
        return E_PATH_TOO_LONG;
    }
    //if the first character of the path is not a letter from the English alphabet
    else if (_path[0] < 65 && _path[0] > 90)
    {
        return E_INVALID_ROOT_ELEMENT;
    }
    //if the second character is not ':'
    else if (_path[1] != ':')
    {
        return E_INVALID_ROOT_ELEMENT;
    }
    //if the third character is not '\'
    else if (_path[2] != '\\')
    {
        return E_INVALID_ROOT_ELEMENT;
    }
    //if the path ends with '\'
    else if (_path.EndsWith('\\'))
    {
        return E_PATH_MISSING_FINAL_ELEMENT;
    }

    //(STATE) _path begins with "<A-Z>:\\"

    //validation of the stem elements

    list<string> stemElements = _path.Clone().ReduceLeft(3).Split('\\');

    //if the path does not contain stem elements
    if (stemElements.count() == 0)
    {
        int result = IsValidFilename(_path.Clone().ReduceLeft(3));

        return result != 0 ? result : 0;
    }

    //(STATE) the path contain stem elements

        for (int i = 0; i < stemElements.count(); i++)
    {
        string& stemElement = stemElements[i];

        //if the element is empty
        if (stemElement.characterCount() == 0)
        {
            return E_EMPTY_PATH_ELEMENT;
        }
        //if the elementy ends with ' '
        else if (stemElement[stemElement.characterCount() - 1] == ' ')
        {
            return E_PATH_ELEMENT_ENDS_WITH_EMPTY_SPACE;
        }
        //if the element contains invalid characters
        else if (i < stemElements.count() - 1 && stemElement.ContainsAny(INVALID_NAME_CHARACTERS))
        {
            return E_PATH_CONTAINS_INVALID_CHARACTERS;
        }
        //if the element is the filename
        else if (i == stemElements.count() - 1)
        {
            int result = IsValidFilename(stemElement);

            return result != 0 ? result : 0;
        }
    }

    return 0;
}

//_path is syntactically valid path ->
bool IsFilePath(const string& _path)
{
    if (_path.Contains('\\'))
    {
        return _path.Sublist(_path.LastIndexOf('\\') + 1).Contains('.');
    }
    else
    {
        return _path.Sublist(_path.IndexOf(':') + 1).Contains('.');
    }
}

//_path is syntactically valid path ->
bool IsDirectoryPath(const string& _path)
{
    if (_path.Contains('\\'))
    {
        return !_path.Sublist(_path.LastIndexOf('\\') + 1).Contains('.');
    }
    else
    {
        return !_path.Sublist(_path.IndexOf(':') + 1).Contains('.');
    }
}

//"D:\\images\\forest.bmp" => "forest.bmp"
//_path is syntactically valid path ->
string FilenameOf(const string& _path)
{
    if (_path.Contains('\\'))
    {
        return _path.Sublist(_path.LastIndexOf('\\') + 1);
    }
    else if (_path.Contains(':'))
    {
        return _path.Sublist(_path.IndexOf(':') + 1);
    }
    else
    {
        return _path;
    }
}

//"D:\\images\\forest.bmp" => "forest"
//_path is syntactically valid path ->
string NameOf(const string& _path)
{
    string name;

    if (_path.Contains('\\'))
    {
        name = _path.Sublist(_path.LastIndexOf('\\') + 1);
    }
    else if (_path.Contains(':'))
    {
        name = _path.Sublist(_path.IndexOf(':') + 1);
    }
    else
    {
        name = _path;
    }

    if (name.Contains('.'))
    {
        return name.Until('.');
    }
    else
    {
        return name;
    }
}

//"a.jpg" => "jpg"
//_filepath is syntactically valid file path ->
string ExtensionOf(const string& _filepath)
{
    string name = FilenameOf(_filepath);
    return name.Sublist(name.IndexOf('.') + 1);
}

//"C:contents" => "C:"
//"C:\\contents\\images" => "C:\\contents"
//_path is syntactically valid path ->
string ParentDirectoryOf(const string& _path)
{
    if (_path.Contains('\\'))
    {
        return _path.Subrange(0, _path.LastIndexOf('\\') - 1);
    }
    else
    {
        return _path.Subrange(0, _path.IndexOf(':'));
    }
}

int RenameFile(const string &, const string &);
int DeleteFile(const string &);
int CreateFile(const string &);
bool DirectoryExists(const string &);

/* (!) this type is used to (conveniently read or mutate) files without making a copy of the file in RAM, ofcourse at the expense of
       performance (due to writing/reading to/from the permanent storage)
   (!) an instance of this type is always associated with the same physical file, i.e. with the same 'path' */
struct File
{
    private:

    enum AccessMode { ReadWrite, ReadOnly };

    AccessMode Mode;
    string Path;
    string Name;
    string Extension;
    int Size = 0;
    mutable int Position = 0;
    mutable FILE* Stream = nullptr;
    mutable char os = 0; //:: File Operation Status

    //_index1 and _index2 can be (two separate indexes) or (to specify a range)
    char set_os(int _index1, int _index2, AccessMode _mode) const
    {
        os = 0;

        //if _file is not associated with a physical file
        if (Stream == nullptr)
        {
            os = E_FILE_NOT_BOUND;
        }

        //if _index1 is out of range
        if (_index1 != -1 && _index1 < 0 || _index1 > Size)
        {
            os = E_INDEX_OUT_OF_RANGE;
        }

        //if _index2 is out of range
        if (_index2 != -1 && (_index2 < 0 || _index2 > Size))
        {
            os = E_INDEX_OUT_OF_RANGE;
        }

        //if _index1 is after _index2
        if (_index2 != -1 && _index1 > _index2)
        {
            os = E_FIRST_INDEX_LARGER_THAN_SECOND_INDEX;
        }

        //if the file is readonly and the caller of set_os() is a mutating function
        if (Mode == ReadOnly & _mode == ReadWrite)
        {
            os = E_READONLY_FILE;
        }

        return os;
    }

    public:

    TraversalMode TraversalMode = TraversalMode::BOUNDED;

    ///CONSTRUCTORS

    File() = default;

    //if the file is successfully opened then &Path and &Name will have a set value
    //_path is ASCII value ->
    explicit File(const string& _path)
    {
        const wchar_t* path = _path.ToWide();
        DWORD attributes = GetFileAttributesW(path);

        if (attributes & FILE_ATTRIBUTE_READONLY)
        {
            Mode = ReadOnly;
            Stream = _wfopen(path, L"rb"); //"rb" :: binary file in read mode
        }
        else
        {
            Mode = ReadWrite;
            Stream = _wfopen(path, L"rb+"); //"rb+" :: binary file in write/read mode
        }

        delete[] path;

        if (Stream != nullptr)
        {
            Path = _path;
            Extension = Path.Subrange(Path.LastIndexOf('.') + 1, Path.characterCount() - 1);
            Name = Path.Subrange(Path.LastIndexOf('\\') + 1, (Path.characterCount() - (Extension.characterCount()) - 2));

            //determining the filesize
            fseek(Stream, 0, SEEK_END);
            Size = ftell(Stream);
            fseek(Stream, 0, SEEK_SET);
        }

        if (GetLastError() != 0)
        {
            SetLastError(0); //it's needed because GetLastError() does not clear the value (sometimes only ???)
        }
    }

    File(const File&) = delete;

    ~File()
    {
        Close();
    }

    void Close()
    {
        if (Stream != nullptr)
        {
            fclose(Stream);
            Stream = nullptr; //to prevent mutation attempt of a closed file
        }
    }

    ///OPERATORS

    //if the function returns UNSUCCESSFUL_OPERATION then it is recommended to check field &os_
    //_index is in the range of file ->
    unsigned char operator[](int _index)
    {
        if (set_os(_index, -1, ReadWrite) != 0) return E_UNSUCCESSFUL_OPERATION;

        fseek(Stream, _index, SEEK_SET);

        return fgetc(Stream);
    }

    //if the function returns UNSUCCESSFUL_OPERATION then it is recommended to check field &os_
    //_index is in the range of file ->
    unsigned char operator[](int _index) const
    {
        if (set_os(_index, -1, ReadOnly) != 0) return E_UNSUCCESSFUL_OPERATION;

        fseek(Stream, _index, SEEK_SET);

        return fgetc(Stream);
    }

    //assignment is performed only on uncostructed object, i.e. if *this is not associated with a physical file
    //after the operation is completed the old object becomes invalid
    //field &os is not copied
    File& operator=(const File& _file)
    {
        if (IsBound()) return *this;

        Mode = _file.Mode;
        Path = _file.Path;
        Name = _file.Name;
        Extension = _file.Extension;
        Size = _file.Size;
        Position = 0;
        Stream = _file.Stream;
        _file.Stream = nullptr; //to prevent release of _file.Stream when the destructor of _file is invoked

        return *this;
    }

    ///FIELDS

    int size() const
    {
        return Size;
    }

    int position() const
    {
        return Position;
    }

    const string &path() const
    {
        return Path;
    }

    const string &name() const
    {
        return Name;
    }

    const string &extension() const
    {
        return Extension;
    }

    char os_() const
    {
        return os;
    }

    ///

    bool IsBound() const
    {
        return Stream != nullptr;
    }

    ///TRAVERSAL FUNCTIONS

    bool can_reverse() const
    {
        return position() > 0;
    }

    bool can_advance() const
    {
        return position() < Size - 1;
    }

    //traversalMode() == BOUNDED && position() - _value < 0 >> position() = position()
    //traversalMode() == BOUNDED && position() - _value > -1 >> position() = position() - _value
    //traversalMode() == CIRCULAR -> circular addition; (EXAMPLE) size() = 19, position() = 4, back(9) >> position() = 14
    File& back(int _value)
    {
        if (TraversalMode == TraversalMode::BOUNDED && Position - _value >= 0)
        {
            Position -= _value;
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Size > 0)
        {
            Position = numeric::CircularSubtraction(0, Size - 1, Position, _value);
        }

        return *this;
    }

    //traversalMode() == BOUNDED && position() + _value >= size() >> position() = position()
    //traversalMode() == BOUNDED && position() + _value < size() - 1 >> position() = position() + _value
    //traversalMode() == CIRCULAR -> circular addition; (EXAMPLE) size() = 21, position() = 16, advance(10) >> position() = 5
    File& advance(int _value)
    {
        if (TraversalMode == TraversalMode::BOUNDED && Position + _value < Size)
        {
            Position += _value;
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Size > 0)
        {
            Position = numeric::CircularAddition(0, Size - 1, Position, _value);
        }

        return *this;
    }

    //position() > 0 => [position() - 1]
    //traversalMode() == BOUNDED && position() == 0 => [0]
    //traversalMode() == CIRCULAR && position() == 0 => [size() - 1]
    unsigned char previous() const
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
            return (*this)[Size - 1];
        }
    }

    //size() > 0 ->
    unsigned char current() const
    {
        return (*this)[Position];
    }

    //position() < size() - 1 => [position() + 1]
    //traversalMode() == BOUNDED && position() == size() - 1 => [position()]
    //traversalMode() == CIRCULAR && position() == size() - 1 => [0]
    unsigned char next() const
    {
        if (Position < Size - 1)
        {
            return (*this)[Position + 1];
        }
        else if (TraversalMode == TraversalMode::BOUNDED && Position == Size - 1)
        {
            return (*this)[Position];
        }
        else if (TraversalMode == TraversalMode::CIRCULAR && Position == Size - 1)
        {
            return (*this)[0];
        }
    }

    //_position < -1 || _position > size() - 1 => -1
    int set_position(int _position)
    {
        if (_position < - 1 || _position > Size - 1) return - 1;

        Position = _position;
        fseek(Stream, Position, SEEK_SET);

        return 0;
    }

    ///NON-MUTATING FUNCTIONS

    bool BeginsWith(const list<unsigned char>& _value) const
    {
        if (set_os(-1, -1, ReadOnly) != 0)
        {
            return false;
        }

        int counter = 0;

        for (int i = 0; i < _value.count(); i++)
        {
            if ((*this)[i] == _value[i])
            {
                counter++;
            }
        }

        return _value.count() == counter;
    }

    bool Contains(unsigned char _value) const
    {
        if (set_os(-1, -1, ReadOnly) != 0) return false;

        for (int i = 0; i < Size; i++)
        {
            if ((*this)[i] == _value)
            {
                return true;
            }
        }

        return false;
    }

    //[1, 2, 3, 4, 5, 6, 7, 8, 9].Contains([2, 3, 4]) => true
    bool Contains(const list<unsigned char>& _value) const
    {
        if (set_os(-1, -1, ReadOnly) != 0) return false;

        for (int i = 0, matches = 0; i < Size - _value.count();)
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

            if (matches == _value.count())
            {
                return true;
            }
        }

        return false;
    }

    bool Contains(std::function<bool(unsigned char)> _predicate) const
    {
        if (set_os(-1, -1, ReadOnly) != 0) return false;

        for (int i = 0; i < Size; i++)
        {
            if (_predicate((*this)[i]))
            {
                return true;
            }
        }

        return false;
    }

    bool EndsWith(const list<unsigned char>& _value) const
    {
        if (set_os(-1, -1, ReadOnly) != 0)
        {
            return false;
        }

        int counter = 0;
        for (int i = Size - 1, n = _value.count() - 1; (i > -1) && (n > -1); i--, n--)
        {
            if ((*this)[i] == _value[n])
            {
                counter++;
            }
        }

        return _value.count() == counter;
    }

    //the specified value does not exist => -1
    int IndexOf(unsigned char _value, int _begin = 0) const
    {
        if (set_os(-1, -1, ReadOnly) != 0) return E_UNSUCCESSFUL_OPERATION;

        for (int i = _begin; i < Size; i++)
        {
            if ((*this)[i] == _value)
            {
                return i;
            }
        }

        return -1;
    }

    //the specified value does not exist => -1
    int IndexOf(const list<unsigned char>& _value, int _begin = 0) const
    {
        if (set_os(_begin, -1, ReadWrite) != 0)
        {
            return -1;
        }
        else if (_value.count() == 0)
        {
            return -1;
        }

        for (int i = _begin, matches = 0; i < Size; i++)
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

            if (matches == _value.count())
            {
                return (i - _value.count()) + 1;
            }
        }

        return -1;
    }

    //the specified value does not exist or _begin is outside the range of list => -1
    int IndexOf(std::function<bool(unsigned char)> _predicate, int _begin = 0) const
    {
        if (set_os(-1, -1, ReadOnly) != 0) return -1;

        for (int i = _begin; i < Size; i++)
        {
            if (_predicate((*this)[i]))
            {
                return i;
            }
        }

        return -1;
    }

    //the specified value does not exist => -1
    int LastIndexOf(unsigned char _value) const
    {
        if (set_os(-1, -1, ReadOnly) != 0) return -1;

        for (int i = Size - 1; i > -1; i--)
        {
            if ((*this)[i] == _value)
            {
                return i;
            }
        }

        return -1;
    }

    //the specified value does not exist => -1
    int LastIndexOf(const list<unsigned char>& _value) const
    {
        if (set_os(-1, -1, ReadOnly) != 0) return -1;

        int index = -1;
        while (true)
        {
            int index_ = IndexOf(_value, index + _value.count());

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
    int LastIndexOf(std::function<bool(unsigned char)> _predicate) const
    {
        if (set_os(-1, -1, ReadOnly) != 0) return -1;

        for (int i = Size - 1; i > -1; i--)
        {
            if (_predicate((*this)[i]))
            {
                return i;
            }
        }

        return -1;
    }

    //buffered read-operation; reads a block at the current position
    //_size + position() < (size() + 1) ->
    void ReadBlock(unsigned char* _array, int _size, bool _advancePosition) const
    {
        fread(_array, sizeof(unsigned char), _size, Stream);

        if (_advancePosition)
        {
             Position += _size;
        }
    }

    //position() + 1 < (size() + 1) ->
    unsigned char ReadI8(bool _advancePosition) const
    {
        unsigned char x = (*this)[Position];

        if (_advancePosition)
        {
             Position++;
        }

        return x;
    }

    //(!) _endianity is the endianity of the source-integral
    //reads a 16-bit unsigned integral value at the current position
    //position() + 2 < (size() + 1) ->
    unsigned short ReadI16(Endianity _endianity, bool _advancePosition) const
    {
        char byte1 = fgetc(Stream);
        char byte2 = fgetc(Stream);

        if (_advancePosition)
        {
            Position += 2;
        }

        return _16(byte1, byte2, _endianity);
    }

    //(!) _endianity is the endianity of the source-integral
    //reads a 32-bit unsigned integral value at the current position
    //position() + 4 < (size() + 1) ->
    unsigned int ReadI32(Endianity _endianity, bool _advancePosition) const
    {
        char byte1 = fgetc(Stream);
        char byte2 = fgetc(Stream);
        char byte3 = fgetc(Stream);
        char byte4 = fgetc(Stream);

        if (_advancePosition)
        {
            Position += 4;
        }

        return _32(byte1, byte2, byte3, byte4, _endianity);
    }

    //_length = 0 => [_begin..]
    //(_begin + _length) >= size() => []
    list<unsigned char> Sublist(int _begin, int _length = 0) const
    {
        if (set_os(_begin, (_begin + _length) - 1, ReadOnly) != 0) return {};

        list<unsigned char> accumulator;

        int end = _length == 0 ? Size : _begin + _length;
        for (int i = _begin; i < end; i++)
        {
            accumulator.Append((*this)[i]);
        }

        return accumulator;
    }

    //[5, 8, 4, 1, 9, 6, 2, 3, 0, 5, 5, 1, 7].Subrange(2, 5) => [4, 1, 9, 6]
    list<unsigned char> Subrange(int _begin, int _end) const
    {
        if (set_os(_begin, _end, ReadOnly) != 0) return {};

        list<unsigned char> accumulator;

        for (int i = _begin; i < _end + 1; i++)
        {
            accumulator.Append((*this)[i]);
        }

        return accumulator;
    }

    ///MUTATION FUNCTIONS

    File& Append(unsigned char _value)
    {
        if (set_os(-1, -1, ReadWrite) != 0) return *this;

        fseek(Stream, Size, SEEK_SET);

        fputc(_value, Stream);

        Size++;

        return *this;
    }

    File& Append(const list<unsigned char>& _value)
    {
        if (set_os(-1, -1, ReadWrite) != 0) return *this;

        fseek(Stream, Size, SEEK_SET);

        for (unsigned char __byte : _value)
        {
            fputc(__byte, Stream);
            Size++;
        }

        return *this;
    }

    File& Append(const unsigned char* _value, int _length)
    {
        if (set_os(-1, -1, ReadWrite) != 0) return *this;

        fseek(Stream, Size, SEEK_SET);

        for (int i = 0; i < _length; i++)
        {
            fputc(_value[i], Stream);
            Size++;
        }

        return *this;
    }

    File& Clear()
    {
        if (set_os(-1, -1, ReadWrite) != 0) return *this;

        Size = 0;
        Position = 0;

        //creating a new file in (the directory in which the file associated with *this is located)
        string path = ParentDirectoryOf(Path) + "\\" + TEMPORARY_FILE_NAME;
        filesystem::CreateFile(path);
        File newFile(path);

        //deleting the old file
        Close();
        filesystem::DeleteFile(Path);

        //renaming the new file
        newFile.Close();

        RenameFile(path, Name + "." + Extension);

        //associating *this with the new physical file
        *this = File(Path);

        return *this;
    }

    //(size() > 0 && _index > 0 && (_index <= size())) =>
    File& Insert(unsigned char _value, int _index)
    {
        if (set_os(-1, -1, ReadWrite) != 0) return *this;

        //creating a new file in (the directory in which the file associated with *this is located)
        string path = ParentDirectoryOf(Path) + "\\" + TEMPORARY_FILE_NAME;
        filesystem::CreateFile(path);
        File newFile(path);

        //copying (the data before _index) in the new file
        newFile.Append(Sublist(0, _index));

        //appending _value to the new file
        newFile.Append(_value);

        //copying of (the data after _index) in the new file
        if (Size - _index > 0)
        {
            newFile.Append(Sublist(_index, Size - _index));
        }

        //deleting the old file
        Close();
        filesystem::DeleteFile(Path);

        //renaming the new file
        newFile.Close();
        RenameFile(path, Name + "." + Extension);

        //associating *this with the new physical file
        *this = File(Path);

        return *this;
    }

    //(size() > 0 && _index > 0 && (_index <= size())) =>
    File& Insert(const list<unsigned char>& _list, int _index)
    {
        if (set_os(-1, -1, ReadWrite) != 0) return *this;

        //creating a new file in (the directory in which the file associated with *this is located)
        string path = ParentDirectoryOf(Path) + "\\" + TEMPORARY_FILE_NAME;
        filesystem::CreateFile(path);
        File newFile(path);

        //copying (the data before _index) in the new file
        newFile.Append(Sublist(0, _index));

        //appending _value to the new file
        newFile.Append(_list);

        //copying of (the data after _index) in the new file
        if (Size - _index > 0)
        {
            newFile.Append(Sublist(_index, Size - _index));
        }

        //deleting the old file
        Close();
        filesystem::DeleteFile(Path);

        //renaming the new file
        newFile.Close();
        RenameFile(path, Name + "." + Extension);

        //associating *this with the new physical file
        *this = File(Path);

        return *this;
    }

    File& RemoveAt(int _index, int _length = 1)
    {
        if (set_os(_index, (_index + _length) - 1, ReadWrite) != 0) return *this;

        //creating a new file in (the directory in which the file associated with *this is located)
        string path = ParentDirectoryOf(Path) + "\\" + TEMPORARY_FILE_NAME;
        filesystem::CreateFile(path);
        File newFile(path);

        for (int i = 0; i < _index; i++)
        {
            newFile.Append((*this)[i]);
        }

        for (int i = _index + _length; i < Size; i++)
        {
            newFile.Append((*this)[i]);
        }

        //deleting the old file
        Close();
        filesystem::DeleteFile(Path);

        //renaming the new file
        newFile.Close();
        RenameFile(path, Name + "." + Extension);

        //associating *this with the new physical file
        *this = File(Path);

        return *this;
    }

    File& Remove(int _begin, int _end)
    {
        if (set_os(_begin, _end, ReadWrite) != 0) return *this;

        //creating a new file in (the directory in which the file associated with *this is located)
        string path = ParentDirectoryOf(Path) + "\\" + TEMPORARY_FILE_NAME;
        filesystem::CreateFile(path);
        File newFile(path);

        for (int i = 0; i < _begin; i++)
        {
            newFile.Append((*this)[i]);
        }

        for (int i = _end + 1; i < Size; i++)
        {
            newFile.Append((*this)[i]);
        }

        //deleting the old file
        Close();
        filesystem::DeleteFile(Path);

        //renaming the new file
        newFile.Close();
        RenameFile(path, Name + "." + Extension);

        //associating *this with the new physical file
        *this = File(Path);

        return *this;
    }

    File& SetAt(int _index, unsigned char _value)
    {
        if (set_os(_index, -1, ReadWrite) != 0) return *this;

        set_position(_index);

        fputc(_value, Stream);

        return *this;
    }

    //_index1 <= _index2 ->
    File& Swap(int _index1, int _index2)
    {
        if (set_os(_index1, _index2, ReadWrite) != 0) return *this;

        unsigned char byte = (*this)[_index1];
        SetAt(_index1, (*this)[_index2]);
        SetAt(_index2, byte);

        return *this;
    }

    //buffered write-operation; overwrites the block at the current position; if the current position is at the end of the file then it appends data
    //(!) it cannot insert data
    //_size + position() < (size() + 1) ->
    File& WriteBlock(const unsigned char* _array, int _size, bool _advancePosition)
    {
        fwrite(_array, sizeof(unsigned char), _size, Stream);

        Size += _size;

        if (_advancePosition)
        {
            Position += _size;
        }

        return *this;
    }

    //(!) _endianity is the endianity of the source-integral
    //writes a 16-bit unsigned integral value at the current position
    //position() + 2 < (size() + 1) ->
    File& WriteI16(unsigned short _value, Endianity _endianity, bool _advancePosition)
    {
        if (set_os(-1, -1, ReadWrite) != 0) return *this;

        if (_endianity == LE)
        {
            fputc(byte_operations::ByteOf(_value, 0), Stream);
            fputc(byte_operations::ByteOf(_value, 1), Stream);
        }
        else
        {
            fputc(byte_operations::ByteOf(_value, 1), Stream);
            fputc(byte_operations::ByteOf(_value, 0), Stream);
        }

        Size += 2;

        if (_advancePosition)
        {
             Position += 2;
        }

        return *this;
    }

    //(!) _endianity is the endianity of the source-integral
    //writes a 32-bit unsigned integral value at the current position
    //position() + 4 < (size() + 1) ->
    File& WriteI32(unsigned int _value, Endianity _endianity, bool _advancePosition)
    {
        if (set_os(-1, -1, ReadWrite) != 0) return *this;

        if (_endianity == LE)
        {
            fputc(byte_operations::ByteOf(_value, 0), Stream);
            fputc(byte_operations::ByteOf(_value, 1), Stream);
            fputc(byte_operations::ByteOf(_value, 2), Stream);
            fputc(byte_operations::ByteOf(_value, 3), Stream);
        }
        else
        {
            fputc(byte_operations::ByteOf(_value, 3), Stream);
            fputc(byte_operations::ByteOf(_value, 2), Stream);
            fputc(byte_operations::ByteOf(_value, 1), Stream);
            fputc(byte_operations::ByteOf(_value, 0), Stream);
        }

        Size += 4;

        if (_advancePosition)
        {
            Position += 4;
        }

        return *this;
    }
};

//if the directory exists successfully opened then &Path and &Name will have a set value
struct Directory
{
    private:

    string Path;
    string Name;

    public:

    Directory() = default;

    explicit Directory(const string& _path)
    {
        if (DirectoryExists(_path))
        {
            Path = _path;
            Name = string(Path.Subrange(Path.LastIndexOf('\\') + 1, Path.characterCount() - 1));
        }
    }

    Directory(const Directory&) = delete;

    Directory& operator=(const Directory&) = default;

    bool operator==(const Directory& _directory) const
    {
        return Path == _directory.path() && Name == _directory.name();
    }

    bool operator!=(const Directory& _directory) const
    {
        return Path != _directory.path() || Name != _directory.name();
    }

    const string &path() const
    {
        return Path;
    }

    const string &name() const
    {
        return Name;
    }
};

//returns the paths of all subdirectories in the specified directory
//(!) shows the hidden directories as well
//the specified directory exists and can be accessed ->
list<string> DirectoriesOf(const string& _directoryPath)
{
    list<string> subdirectories;

    const wchar_t* path = (_directoryPath + string("\\*")).ToWide();

    ::WIN32_FIND_DATAW findData;

    void *handle = ::FindFirstFileW(path, &findData);

    int result = ::FindNextFileW(handle, &findData);

    delete [] path;

    //for each directory and file in (the physical directory associated with _directory)
    while (result)
    {
        string identifier = string(reinterpret_cast<const utf16*>(findData.cFileName), LE);

        //if the identifier specifies the parent directory
        if (identifier == "..")
        {
            result = FindNextFileW(handle, &findData);
            continue;
        }

        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            subdirectories.Append(_directoryPath + string("\\") + identifier);
        }

        result = FindNextFileW(handle, &findData);
    }

    ::FindClose(handle);

    return subdirectories;
}

//returns the filepaths of all files in the specified directory
//(!) shows the hidden files as well
//the specified directory exists and can be accessed ->
list<string> FilesOf(const string& _directoryPath)
{
    list<string> filepaths;

    const wchar_t* path = (_directoryPath + string("\\*")).ToWide();
    ::WIN32_FIND_DATAW findData;

    void *handle = ::FindFirstFileW(path, &findData);

    bool result = ::FindNextFileW(handle, &findData);

    delete [] path;

    //for each directory and file in (the physical directory associated with _directory)
    while (result)
    {
        string identifier = string(reinterpret_cast<const utf16*>(findData.cFileName), LE);

        if (identifier == "..")
        {
            result = FindNextFileW(handle, &findData);
            continue;
        }

        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            filepaths.Append(_directoryPath + string("\\") + identifier);
        }

        result = FindNextFileW(handle, &findData);
    }

    ::FindClose(handle);

    return filepaths;
}

bool FileExists(const string& _path)
{
    const wchar_t* path = _path.ToWide();
    GetFileAttributesW(path);
    delete[] path;

    DWORD lastError = GetLastError();

    if (lastError != 0)
    {
        SetLastError(0); //it's needed because GetLastError() does not clear the value (sometimes only ???)
    }

    return lastError != ERROR_FILE_NOT_FOUND && lastError != ERROR_PATH_NOT_FOUND && lastError != ERROR_INVALID_NAME;
}

bool DirectoryExists(const string& _path)
{
    const wchar_t* path = _path.ToWide();
    GetFileAttributesW(path);
    delete[] path;

    DWORD lastError = GetLastError();

    if (lastError != 0)
    {
        SetLastError(0); //it's needed because GetLastError() does not clear the value (sometimes only ???)
    }

    return lastError != ERROR_FILE_NOT_FOUND && lastError != ERROR_PATH_NOT_FOUND && lastError != ERROR_INVALID_NAME;
}

//the specified file exists ->
int SizeOf(const string& _path)
{
    if (IsValidFilePath(_path) != 0)
    {
        return E_INVALID_PATH;
    }
    else if (!FileExists(_path))
    {
        return E_FILE_DOES_NOT_EXIST;
    }

    const wchar_t* path = _path.ToWide();

    FILE* stream = _wfopen(path, L"r+b");

    if (stream == nullptr && errno == 13)
    {
        return E_ACCESS_DENIED;
    }

    delete[] path;

    fseek(stream, 0, SEEK_END);

    int size = ftell(stream);

    fclose(stream);

    return size;
}

//the specified file/directory exists ->
bool IsReadOnly(const string& _path)
{
    const wchar_t* path = _path.ToWide();
    DWORD attributes = GetFileAttributesW(path);
    delete[] path;

    return attributes & FILE_ATTRIBUTE_READONLY;
}

//the specified file/directory exists ->
bool IsHidden(const string& _path)
{
const wchar_t* path = _path.ToWide();
DWORD attributes = GetFileAttributesW(path);
delete[] path;

return attributes & FILE_ATTRIBUTE_HIDDEN;
}

//the specified file/directory exists ->
bool IsSystem(const string& _path)
{
const wchar_t* path = _path.ToWide();
DWORD attributes = GetFileAttributesW(path);
delete[] path;

return attributes & FILE_ATTRIBUTE_SYSTEM;
}

//the specified file/directory exists ->
time_::DateTime GetCreationTime(const string& _path)
{
    using namespace time_;

    HANDLE file = ::CreateFileW(_path.ToWide(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    FILETIME filetime;

    GetFileTime(file, &filetime, NULL, NULL);

    CloseHandle(file);

    //number of 100-nanosecond intervals since 01.01.1601 00:00:00 (UTC)
    unsigned long long intervalsSinceEpoch = byte_operations::_64(filetime.dwLowDateTime, filetime.dwHighDateTime);

    //number of seconds since 01.01.1601 00:00:00 (UTC)
    unsigned long long secondsSinceEpoch = intervalsSinceEpoch / 10000000;

    unsigned long long seconds = secondsSinceEpoch;

    int year = 1601;
    int month = 1;

    //determine the year
    while (true)
    {
        int daysInYear = IsLeap(year) ? 366 : 365;

        if (seconds < (daysInYear * SECONDS_IN_A_DAY)) break;

        int secondsInYear = daysInYear * SECONDS_IN_A_DAY;

        seconds -= secondsInYear;

        year++;
    }

    //determine the month
    while (true)
    {
        int daysInMonth = IsLeap(year) && month == 2 ? 29 : MONTH_LENGTHS[month];

        if (seconds < (daysInMonth * SECONDS_IN_A_DAY)) break;

        int secondsInMonth = daysInMonth * SECONDS_IN_A_DAY;

        seconds -= secondsInMonth;

        month++;
    }

    int day = (seconds / SECONDS_IN_A_DAY);

    int secondOfDay = numeric::Mod(seconds, SECONDS_IN_A_DAY);

    int hour = secondOfDay / SECONDS_IN_AN_HOUR;

    int secondOfHour = numeric::Mod(secondOfDay, SECONDS_IN_AN_HOUR);

    int minute = secondOfHour / 60;

    int secondOfMinute = numeric::Mod(secondOfHour, 60);

    return DateTime(day, month, year, hour, minute, secondOfMinute);
}

//the specified file/directory exists ->
time_::DateTime GetLastAccessTime(const string& _path)
{
    using namespace time_;

    HANDLE file = ::CreateFileW(_path.ToWide(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    FILETIME filetime;

    GetFileTime(file, NULL, &filetime, NULL);

    CloseHandle(file);

    //number of 100-nanosecond intervals since 01.01.1601 00:00:00 (UTC)
    unsigned long long intervalsSinceEpoch = byte_operations::_64(filetime.dwLowDateTime, filetime.dwHighDateTime);

    //number of seconds since 01.01.1601 00:00:00 (UTC)
    unsigned long long secondsSinceEpoch = intervalsSinceEpoch / 10000000;

    unsigned long long seconds = secondsSinceEpoch;

    int year = 1601;
    int month = 1;

    //determine the year
    while (true)
    {
        int daysInYear = IsLeap(year) ? 366 : 365;

        if (seconds < (daysInYear * SECONDS_IN_A_DAY)) break;

        int secondsInYear = daysInYear * SECONDS_IN_A_DAY;

        seconds -= secondsInYear;

        year++;
    }

    //determine the month
    while (true)
    {
        int daysInMonth = IsLeap(year) && month == 2 ? 29 : MONTH_LENGTHS[month];

        if (seconds < (daysInMonth * SECONDS_IN_A_DAY)) break;

        int secondsInMonth = daysInMonth * SECONDS_IN_A_DAY;

        seconds -= secondsInMonth;

        month++;
    }


    int day = (seconds / SECONDS_IN_A_DAY);

    int secondOfDay = numeric::Mod(seconds, SECONDS_IN_A_DAY);

    int hour = secondOfDay / SECONDS_IN_AN_HOUR;

    int secondOfHour = numeric::Mod(secondOfDay, SECONDS_IN_AN_HOUR);

    int minute = secondOfHour / 60;

    int secondOfMinute = numeric::Mod(secondOfHour, 60);

    return DateTime(day, month, year, hour, minute, secondOfMinute);
}

//the specified file/directory exists ->
time_::DateTime GetLastMutationTime(const string& _path)
{
    using namespace time_;

    HANDLE file = ::CreateFileW(_path.ToWide(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    FILETIME filetime;

    GetFileTime(file, NULL, NULL, &filetime);

    CloseHandle(file);

    //number of 100-nanosecond intervals since 01.01.1601 00:00:00 (UTC)
    unsigned long long intervalsSinceEpoch = byte_operations::_64(filetime.dwLowDateTime, filetime.dwHighDateTime);

    //number of seconds since 01.01.1601 00:00:00 (UTC)
    unsigned long long secondsSinceEpoch = intervalsSinceEpoch / 10000000;

    unsigned long long seconds = secondsSinceEpoch;

    int year = 1601;
    int month = 1;

    //determine the year
    while (true)
    {
        int daysInYear = IsLeap(year) ? 366 : 365;

        if (seconds < (daysInYear * SECONDS_IN_A_DAY)) break;

        int secondsInYear = daysInYear * SECONDS_IN_A_DAY;

        seconds -= secondsInYear;

        year++;
    }

    //determine the month
    while (true)
    {
        int daysInMonth = IsLeap(year) && month == 2 ? 29 : MONTH_LENGTHS[month];

        if (seconds < (daysInMonth * SECONDS_IN_A_DAY)) break;

        int secondsInMonth = daysInMonth * SECONDS_IN_A_DAY;

        seconds -= secondsInMonth;

        month++;
    }

    int day = (seconds / SECONDS_IN_A_DAY);

    int secondOfDay = numeric::Mod(seconds, SECONDS_IN_A_DAY);

    int hour = secondOfDay / SECONDS_IN_AN_HOUR;

    int secondOfHour = numeric::Mod(secondOfDay, SECONDS_IN_AN_HOUR);

    int minute = secondOfHour / 60;

    int secondOfMinute = numeric::Mod(secondOfHour, 60);

    return DateTime(day, month, year, hour, minute, secondOfMinute);
}

//returns 0 on successful execution
int CreateFile(const string& _path)
{
    if (IsValidFilePath(_path) != 0)
    {
        return E_INVALID_PATH;
    }
    else if (FileExists(_path))
    {
        return E_FILE_ALREADY_EXISTS;
    }
    else if (!DirectoryExists(ParentDirectoryOf(_path)))
    {
        return E_DESTINATION_DIRECTORY_DOES_NOT_EXIST;
    }

    const wchar_t* path = _path.ToWide();

    FILE *file = _wfopen(path, L"w+b");

    if (file == nullptr)
    {
        return E_UNKNOWN_ERROR;
    }

    delete [] path;

    fclose(file);

    return 0;
}

//returns 0 on successful execution
int CreateDirectory(const string& _path)
{
    if (IsValidDirectoryPath(_path) != 0)
    {
        return E_INVALID_PATH;
    }
    else if (!DirectoryExists(ParentDirectoryOf(_path)))
    {
        return E_DESTINATION_DIRECTORY_DOES_NOT_EXIST;
    }

    const wchar_t* path = _path.ToWide();
    bool result = ::CreateDirectoryW(path, NULL);
    delete [] path;

    return result ? 0 : E_UNKNOWN_ERROR;
}

int CopyDirectory(const string &, const string &);
int DeleteDirectory(const string &);

//returns 0 on successful execution
int RenameFile(const string& _filepath, const string& _newFilename)
{
    if (IsValidFilePath(_filepath) != 0)
    {
        return E_INVALID_PATH;
    }
    else if (IsValidFilename(_newFilename) != 0)
    {
        return E_FILENAME_CONTAINS_INVALID_CHARACTERS;
    }
    else if (!FileExists(_filepath))
    {
        return E_FILE_DOES_NOT_EXIST;
    }
    else if (FileExists(ParentDirectoryOf(_filepath) + "\\" + _newFilename))
    {
        return E_FILE_ALREADY_EXISTS;
    }

    //creating an empty file

    if (filesystem::CreateFile(ParentDirectoryOf(_filepath) + "\\" + _newFilename) != 0)
    {
        return E_UNKNOWN_ERROR;
    }

    //copying (the contents of the old file) into the new file

    const wchar_t* oldPath = _filepath.ToWide();
    const wchar_t* newPath = (ParentDirectoryOf(_filepath) + "\\" + _newFilename).ToWide();
    FILE *sourceFile = _wfopen(oldPath, L"r+b");
    FILE *destinationFile = _wfopen(newPath, L"w+b");
    delete [] oldPath;
    delete [] newPath;

    while (true)
    {
        int value = fgetc(sourceFile);

        if (value == EOF)
        {
            break;
        }

        fputc(value, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    filesystem::DeleteFile(_filepath);

    return 0;
}

//returns 0 on successful execution
int RenameDirectory(const string& _path, const string& _newName)
{
    int result = IsValidName(_newName);

    if (result != 0) return result;

    if (!IsValidDirectoryPath(_path))
    {
        return E_INVALID_PATH;
    }
    else if (!DirectoryExists(_path))
    {
        return E_DIRECTORY_DOES_NOT_EXIST;
    }
    else if (DirectoryExists(ParentDirectoryOf(_path) + "\\" + _newName))
    {
        return E_DIRECTORY_ALREADY_EXISTS;
    }

    CreateDirectory(ParentDirectoryOf(_path) + "\\" + _newName);

    DeleteDirectory(_path);

    return 0;
}

//returns 0 on successful execution
//_sourcePath specifies the copied file
//_destinationPath specifies the directory in which the file should be copied
int CopyFile(const string& _sourcePath, const string& _destinationPath)
{
    if (IsValidFilePath(_sourcePath) != 0)
    {
        return E_INVALID_SOURCE_PATH;
    }
    else if (!IsValidDirectoryPath(_destinationPath))
    {
        return E_INVALID_DESTINATION_PATH;
    }
    else if (!DirectoryExists(_destinationPath))
    {
        return E_DESTINATION_DIRECTORY_DOES_NOT_EXIST;
    }
    else if (!FileExists(_sourcePath))
    {
        return E_FILE_DOES_NOT_EXIST;
    }

    string filename = _sourcePath.Sublist(_sourcePath.LastIndexOf('\\'));

    if (FileExists(_destinationPath + string("\\") + filename))
    {
        return E_FILE_ALREADY_EXISTS;
    }

    //creating an empty file

    if (filesystem::CreateFile(_destinationPath + "\\" + FilenameOf(_sourcePath)) != 0)
    {
        return E_UNKNOWN_ERROR;
    }

    //copying (the contents of the old file) into the new file

    const wchar_t* filepath = _sourcePath.ToWide();
    const wchar_t* destinationPath = (_destinationPath + "\\" + FilenameOf(_sourcePath)).ToWide();
    FILE* sourceFile = _wfopen(filepath, L"r+b");
    FILE* destinationFile = _wfopen(destinationPath, L"w+b");
    delete [] filepath;
    delete [] destinationPath;

    while (true)
    {
        int value = fgetc(sourceFile);

        if (value == EOF)
        {
            break;
        }

        fputc(value, destinationFile);
    }

    fclose(sourceFile);
    fclose(destinationFile);

    return 0;
}

//returns 0 on successful execution
//_sourcePath specifies the copied directory
//_destinationPath specifies the directory in which the directory should be copied
int CopyDirectory(const string& _sourcePath, const string& _destinationPath)
{
    if (!IsValidDirectoryPath(_sourcePath))
    {
        return E_INVALID_SOURCE_PATH;
    }
    else if (!IsValidDirectoryPath(_destinationPath))
    {
        return E_INVALID_DESTINATION_PATH;
    }
    else if (!DirectoryExists(_sourcePath))
    {
        return E_SOURCE_DIRECTORY_DOES_NOT_EXIST;
    }
    else if (!DirectoryExists(ParentDirectoryOf(_destinationPath)))
    {
        return E_DESTINATION_DIRECTORY_DOES_NOT_EXIST;
    }

    string destinationPath(_destinationPath + "\\" + NameOf(_sourcePath));

    CreateDirectory(destinationPath);

    //copying the files
    for (const string& __filepath : FilesOf(_sourcePath))
    {
        CopyFile(__filepath, destinationPath);
    }

    //copying the directories (recursive)
    for (const string& __subdirectoryPath : DirectoriesOf(_sourcePath))
    {
        CopyDirectory(__subdirectoryPath, destinationPath);
    }

    return 0;
}

//returns 0 on successful execution
int DeleteFile(const string& _path)
{
    if (IsValidFilePath(_path) != 0)
    {
        return E_INVALID_PATH;
    }
    else if (IsSystem(_path))
    {
        return E_SYSTEM_FILE_MANIPULATION_ATTEMPT;
    }
    else if (!FileExists(_path))
    {
        return E_FILE_DOES_NOT_EXIST;
    }


    const wchar_t* path = _path.ToWide();

    int result = _wremove(path);

    if (errno == EACCES)
    {
        delete [] path;
        return E_ACCESS_DENIED;
    }

    delete[] path;

    return result == 0 ? 0 : E_UNKNOWN_ERROR;
}

//returns 0 on successful execution
int DeleteDirectory(const string& _path)
{
    if (!IsValidDirectoryPath(_path))
    {
        return E_INVALID_PATH;
    }
    else if (IsSystem(_path))
    {
        return E_SYSTEM_DIRECTORY_MANIPULATION_ATTEMPT;
    }
    else if (!DirectoryExists(_path))
    {
        return E_DIRECTORY_DOES_NOT_EXIST;
    }

    //deleting the contents of __directory
    for (const string& __filepath : FilesOf(_path))
    {
        filesystem::DeleteFile(__filepath);
    }

    for (const string& __directoryPath : DirectoriesOf(_path))
    {
        if (IsSystem(__directoryPath))
        {
            return E_SYSTEM_DIRECTORY_MANIPULATION_ATTEMPT;
        }
        else if (DeleteDirectory(__directoryPath) == E_SYSTEM_DIRECTORY_MANIPULATION_ATTEMPT)
        {
            return E_SYSTEM_DIRECTORY_MANIPULATION_ATTEMPT;
        }
    }

    const wchar_t* path = _path.ToWide();

    bool result = ::RemoveDirectoryW(path);

    if (GetLastError() != 0)
    {
        SetLastError(0); //it's needed because GetLastError() does not clear the value (sometimes only ???)
    }

    delete [] path;

    return result ? 0 : E_UNKNOWN_ERROR;
}

//error => ""
string GetApplicationDirectory()
{
    wchar_t array[MAX_PATH + 1/*because of the terminating character*/];

    //&result specifies the length of the result (in UTF-16 code units and without counting the terminating character)

    unsigned int result = GetCurrentDirectoryW(MAX_PATH, array);

    if (GetLastError() != 0)
    {
        SetLastError(0); //it's needed because GetLastError() does not clear the value (sometimes only ???)
        return {};
    }

    return string(reinterpret_cast<utf16*>(array), LE, result);
}
}




