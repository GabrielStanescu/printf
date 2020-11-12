General procedure: the "format" array given as input was iterated character by
character using a "for" structure. if a "%" is found, the algorithm checks the
next position of the array in order to find a conversion specifier or another "%"
using a switch statement. If the current character is not a "%", it will be
printed anyways.

Functions:

int2string() - returns a (char *) string which contains an integer given as input
-I am extracting the last digit of the number and then i will place it into
the "output" string as a char (int + '0')
-if the number is negative, it's not recommended to multiply it by -1 because
if the int is INT_MIN, multiplying this value wil exceed the INT_MAX by 1. So,
I was multiplying the last digit of the number with -1 if the int was negative.
-the "output" contains the reverse number given as input, therefore "revoutput"
contains the reverse string of "output"

uint2string() - same as int2string(), but the input is an unsigned int

hex2string() - same as uint2string(), but the string contains a hex number
-if the last digit of the unsgnd int is less than 10, then a digit will be
placed into the "output" string(mod + 48), else a letter will be placed(mod+87)

intlen(), uintlen() - returns the number of digits of an int/unsigned int

write_stdout() - writes on the stdout a given string as a parameter

Other informations can be found into the source code as comments.
