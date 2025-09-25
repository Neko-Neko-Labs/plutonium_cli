# DOCUMENTING INFO!
> This documenting system is too niche that only `koofte` uses cosue he inwented

## Overflow
Insanly niche info. Like:
This prints
Even less deatiled then 8 Byte

## 8 Byte
Not so detailed.
`printf`: Takes const char* and ... args and pritns stuff

## 4 Byte
Litle deatiled then 8 Byte
`printf`: Comes from `stdio.h` part of clib, takes args of const char* s and ..., Used to print stuff;

## 2 Byte -- Default documenting;
Normal level documenting:
The printf() function writes a formatted string to the console.

The printf() function is defined in the <stdio.h> header file.

Note: More accurately, it writes to the location specified by stdout which is usually the console but it may be configured to point to a file or other location.
Usaly a wraper for `fprintf(stdout, s, ...);`

## 1 Byte 
deatiled then usual;
The printf() function writes a formatted string to the console.

The printf() function is defined in the <stdio.h> header file.

Note: More accurately, it writes to the location specified by stdout which is usually the console but it may be configured to point to a file or other location.

Formating:
s -> char*
p -> pointer
d -> int 
f -> float
used as printf("%s", string); so % then the format id 

## 1 Bit
Insanly detailed 
Definition and Usage

The printf() function writes a formatted string to the console.

The printf() function is defined in the <stdio.h> header file.

Note: More accurately, it writes to the location specified by stdout which is usually the console but it may be configured to point to a file or other location.
Format specifiers

The format string can contain format specifiers which describe where and how to represent additional arguments that are passed into the function.

The format specifiers have the form %[flags][width][.precision][length]specifier. The components in [square brackets] are optional.

An explanation of each of the components:

    flags - Optional. A sequence of any of the following characters:
        - - Makes the output left-justified by adding any padding spaces to the right instead of to the left.
        # - Shows an alternate representation of the formatted data depending on the conversion.
        + - Causes positive numbers to always be prefixed with "+".
         - (A space character) This prefixes a space to positive numbers, primarily so that the digits can be lined up with the digits of negative numbers.
        0 - Pads numbers with zeroes on the left.
    width - Optional. A whole number specifying the minimum number of characters that the output should occupy. If necessary, spaces are added to the left to reach this number, or to the right if the - flag is used. If an *asterisk is used then the width is given by the argument preceding the one being represented.
    .precision - Optional. A . followed by a whole number indicating how many decimal digits to show in the formatted data.
    length - Optional. A sequence of characters which changes the expected data type of the argument. It can be one of the following:
        hh - Expect char type for whole numbers.
        h - Expect short int type for whole numbers.
        l - Expect long int type for whole numbers.
               Expect wint_t type for characters.
               Expect wchar_t* type for strings.
        ll - Expect long long int type for whole numbers.
        j - Expect intmax_tor uintmax_t type for whole numbers.
        z - Expect size_t type for whole numbers.
        t - Expect ptrdiff_t type for whole numbers.
        L - Expect long double type for floating point numbers.
    specifier - Required. A character which indicates how an argument's data should be represented. The list of possible characters is shown in the table below.

List of specifiers
Character 	Specifier 	Description
d or i 	Decimal integer 	Represents a whole number as a decimal integer.
u 	Unsigned decimal integer 	Represents a whole number as an unsigned decimal integer.
o 	Octal integer 	Represents a whole number as an octal integer. The "#" flag will prefix the number with "0".
x or X 	Hexadecimal integer 	Represents a whole number as a hexadecimal integer. The "#" flag will prefix the number with "0x". If "X" is used then digits A to F and the letter X are shown in uppercase.
f or F 	Floating point number 	Represents a floating point number. If "F" is used then letters (from values like "nan") will be represented in uppercase. The "#" flag will force a decimal point even if there are no decimal digits.
e or E 	Scientific notation 	Represents a floating point number in scientific notation. If "E" is used then letters will be represented in uppercase. The "#" flag will force a decimal point even if there are no decimal digits.
g or G 	General number 	Uses the shortest representation between f and e for a floating point number. If "G" is used then it chooses between F and E instead.
a or A 	Hexadecimal floating point number 	Displays a floating point number's internal representation with hexadecimal digits. If "A" is used then the digits are represented in uppercase.
c 	Character 	Represents a character. If the argument is an integer then it represents the character for the ASCII value specified by the integer.
s 	String 	Represents a string.
p 	Pointer 	Represents the memory address of a pointer, usually with hexadecimal digits.
n 	No output 	The number of characters that have been printed up to this point is written into the argument. The argument must be a pointer to an integer.
% 	Percent symbol 	Represents a literal "%" character.
Syntax

printf(const char * format, arg1, arg2...);

Parameter Values
Parameter 	Description
format 	Required. A string representing the format of the data to be written to the file.
arg1, arg2... 	Optional. Any number of additional arguments, their values can be formatted and printed to the console using the specifiers in the format argument.
Technical Details
Returns: 	An int value representing the number of characters that were printed. If an error occurred then it returns a negative number.


## Underflow
Even detailed then 1 Bit. Covers evry single detail and edge case;
