f-code

© November 2021, Stanislav Petrov

**OVERVIEW** 

(!) f-code stands for 'fundamental code'; it is supposed to contain only (relatively) fundamental code - data collections, filesystem manipulation, networking, time functions, regular expressions, 2D graphics rendering and few other things; this is a very early version - at this stage the library contains only a small portion of the planned features and it also may contain some bugs 

(!) the library is intended to work on Windows 10 and 64-byte processor

(!) the library is tested on Windows 10 (Microsoft Visual C++ compiler, C++14)

(!) the library does not use third-party source code

(!) the functionality of the library will be expanded in the near future by (adding new files) and (expanding the capabilities of the existing files)

(!) sometimes in the comments the name of a (global object, local object(that is not an argument) or pointer 'this') is preceded by character '&'

(!) some constructors/functions accept 'activation atoms' - these are enum values that force a specific constructor/function call; this is needed when there is a
    conflict between constructors/functions with otherwise exact signatures

(!) the ranges used in the library are inclusive

(!) the library consists of the following files:
- array.cpp
- range.cpp
- tuple.cpp
- pair.cpp
- list.cpp
- string.cpp
- bit_operations.cpp
- byte_operations.cpp
- numeric.cpp
- unicode.cpp
- time.cpp
- filesystem.cpp

(!) all of the functionality in the library can be used in a program by including the following files:
- #include <Windows.h>
- #include <iostream>
- #include <functional>
- #include <ctime>
(!) here the order of includes is important
- #include "array.cpp"
- #include "range.cpp"
- #include "tuple.cpp"
- #include "pair.cpp"
- #include "list.cpp"
- #include "bit_operations.cpp"
- #include "byte_operations.cpp"
- #include "numeric.cpp"
- #include "unicode.cpp"
- #include "string.cpp"
- #include "time.cpp"
- #include "filesystem.cpp"

(!) file dependencies:
- array.cpp - depends on <Windows.h>
- range.cpp - do not depend on other files
- tuple.cpp - do not depend on other files
- pair.cpp - do not depend on other files
- list.cpp - depends on <functional> and range.cpp
- bit_operations.cpp - depends on list.cpp
- byte_operations.cpp - depends on list.cpp
- numeric.cpp - depends on list.cpp
- unicode.cpp - depends on bit_operations.cpp, list.cpp, range.cpp and tuple.cpp
- string.cpp - depends on <iostream>, byte_operations.cpp, numeric.cpp и unicode.cpp
- time.cpp - depends on <ctime> and numeric.cpp
- filesystem.cpp - depends on string.cpp and time.cpp
- (example) as numeric.cpp depends on list.cpp we must first include the files on which list.cpp depends, i.e. <functional> and range.cpp;  therefore numeric.cpp can be used in the program by including the following code:
  - #include <functional>
  - #include "range.cpp"
  - #include "list.cpp"
  - #include "numeric.cpp"

(!) some functions contains notes describing the following (in the order shown below):
- description of the function
- description of one or more parameters of the function (if their meaning is not clear at first)
- the result from (a function call with specific argument values) in the format "<argument-values> => <result>",
  where 'argument-values' consists of one or more argument values; the character '|' means 'or'
- examples in format "<function-call> => <result>"; some arguments in the example can have value 'x' which means that the value of the argument
  does not matter for the specific example; the examples not always show every possible variant of the particular function call; most of the time
  only the variants for which the result is not clear (which is subjective) are shown - (a set of one or more argument values) followed by character '->' means that (the   argument(s) must have the specified values) for the correct execution of the function

(!) (a character '->' after the body of a function) followed by (set of object values) means that the objects receive the specified values

(!) (a character '->' after the body of a function) followed by (an operation or operations) means that the specified operation(s) must be executed after
    the function is finished

(!) f-code use five tags that gives additional information to the programmer; these tags can be applied to a file or
    a program object (a variable, function, structure, etc.); some tags can be applied only to specific program objects;
    if a tag is applied to a file then the tag should be included in the beginning of the file, and if it's applied to a program object it is included right before the object; the tags used in the library (and the description of their meaning) are the following:
   - (!) { value } - a very important note
   - (EXAMPLE) { value }  - example of a certain functionality  
   - (MAY-NEED-BETTER-EXPLANATION) { value } - the functionality described by 'value' may need better explanation  
   - (STATE) { value } - describes the state of a specific object  (if the code is correctly executed) at the location of the tag  
   - (END-STATE) this tag is always preceded by tag (STATE); this tag specifies that the state of the object specified by tag (STATE) is no more valid, i.e. after the line in  which the tag (END-STATE) is located the state of the object may be different than the state of the object described in the tag (STATE)
   
**EXAMPLES (incomplete list)**
 
list<int> ls { 5, 0, 9, 1, 8, 4 };  
list<int> lx(ls, 2, 4); //creates a 'list segment'; &lx is a segment of &ls; &ls is a source list for &lx; list segments are computationally fast way to access a continuous range; of elements of an existing list; the segment can be treated like a separate list and in some situations this makes things easier; adding and deletion of elements to/from a segment is not allowed, the values of the individual elements can be changed though; this functionality (in some form or another) is also known by different names in other languages/libraries  

list<int> ls(1000000); //allocates space for 1000000 int values; this functionality is useful if the maximum number of elements that will be added to the list is known beforehand - in this way resize operations can be avoided 

string s("republic", ascii, Encoding::UTF16LE); //creates a UTF16LE string from an ASCII input  

//"ĞȸĨ𠀔У" = Unicode[286, 568, 296, 131092, 1059] = UTF8[196 158 200 184 196 168 240 160 128 148 208 163]  
list<unsigned char> ls { 196, 158, 200, 184, 196, 168, 240, 160, 128, 148, 208, 163, 0 };  
string s(ls.elements(), u8, Encoding::UTF16LE); //creates a UTF16LE string from an UTF8 input  

//"𠀔λΨΡ" = Unicode[131092, 955, 936, 929] = UTF16[55360, 56340, 955, 936, 929] = byte[216, 64, 220, 20, 3, 187, 3, 168, 3, 161]  
list<unsigned char> ls { 216, 64, 220, 20, 3, 187, 3, 168, 3, 161, 0, 0 };  
string bs(ls.elements(), u16, BE, static_cast<unsigned int>(10), Encoding::UTF32BE); //creates an UTF32BE string (from UTF16BE byte input)  

string s(L"oak↕country₢planet", Encoding::UTF8); //creates an UTF8 string from (UTF16LE byte input)

(!) (the constructors accepting byte arrays) may accept the array length (in bytes), (in code units) or (in characters); in order to pass
        the length in bytes one have to use <N> or <N>|b, to pass the length in code units <N>|u, and to pass the length in characters <N>|c;
		the maximum value of <N> is 1073741823 (constant MAX_LENGTH)
        (ЕXAMPLE) 162 (162 bytes)
        (ЕXAMPLE) 495|b (495 bytes)
        (EXAMPLE) 829|u (829 code units)
        (ЕXAMPLE) 327|c (327 characters)
        
//"ĞȸĨ𠀔У" = U[286, 568, 296, 131092, 1059] = UTF8[196 158 200 184 196 168 240 160 128 148 208 163]  
list<unsigned char> ls { 196, 158, 200, 184, 196, 168, 240, 160, 128, 148, 208, 163, 0 };  
string s(ls.elements(), u8, 5|characters, Encoding::UTF32LE); //creates an UTF32LE string from (UTF8 input consisting of 5 characters)  

//"ĞȸĨ𠀔У" = U[286, 568, 296, 131092, 1059] = UTF8[196 158 200 184 196 168 240 160 128 148 208 163]  
list<unsigned char> ls { 196, 158, 200, 184, 196, 168, 240, 160, 128, 148, 208, 163, 0 };  
string s(ls.elements(), u8, 12|units, Encoding::UTF32LE); //creates an UTF32LE string from (UTF8 input consisting of 12 code units)  

//"ĞȸĨ𠀔У" = U[286, 568, 296, 131092, 1059] = UTF8[196 158 200 184 196 168 240 160 128 148 208 163]  
list<unsigned char> ls { 196, 158, 200, 184, 196, 168, 240, 160, 128, 148, 208, 163, 0 };  
string s(ls.elements(), u8, 12|bytes, Encoding::UTF32LE); //creates an UTF32LE string from (UTF8 input consisting of 12 bytes)  

string dir = "C:\\documents";  
filesystem::DeleteFile(dir + "\\documents\\sunset.jpeg");   
filesystem::CreateDirectory(dir + "\\notes");  
filesystem::RenameFile(dir + "\\notes\\note1.txt", "note2.txt");  
  
bool b1 = IsSystem("E:\\folder1");  
bool b2 = IsReadOnly("E:\\notes.txt");  
 
list<string> files = filesystem::FilesOf("G:");  
list<string> directories = filesystem::DirectoriesOf("G:");











