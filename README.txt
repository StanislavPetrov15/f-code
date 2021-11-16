f-code

© November 2021, Stanislav Petrov

(!) f-code stands for 'fundamental code'; it is supposed to contain only (relatively) fundamental code - data collections, filesystem manipulation,
    networking, time functions, regular expressions, 2D graphics rendering and few other things; at this stage though the library contains only a small portion of the planned
    features

(!) the library is intended to work on Windows 10 and 64-byte processor 

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

(!) all of the functionality in the library can be used in a program by including the following files:
- #include <Windows.h>
- #include <iostream>
- #include <functional>
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
- (example) as numeric.cpp depends on list.cpp we must first include the files on which list.cpp depends, i.e. <functional> and range.cpp; 
  therefore numeric.cpp can be used in the program by including the following code:
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
    if a tag is applied to a file then the tag should be included in the beginning of the file, and if it's applied to a program object it is
	included right before the object; the tags used in the library (and the description of their meaning) are the following:
   - (!) { value } - a very important note
   - (EXAMPLE) { value }  - example of a certain functionality 
   - (MAY-NEED-BETTER-EXPLANATION) { value } - the functionality described by 'value' may need better explanation
   - (STATE) { value } - describes the state of a specific object  (if the code is correctly executed) at the location of the tag
   - (END-STATE) this tag is always preceded by tag (STATE); this tag specifies that the state of the object specified by tag (STATE) is no more valid, i.e. after the line in  which the tag (END-STATE) is located the state of the object may be different than the state of the object described in the tag (STATE)
  








