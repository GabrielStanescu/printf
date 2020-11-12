#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

//converts an integer into a string
char * int2string(int input) {
	char *output;
	output = (char *)calloc(11, sizeof(char));
	int i = 0, negative = 1;
	if (input < 0)
		negative = -1;
	//creating an array which contains the digits (chars) of the input number
	while (input) {
		output[i] = input % 10 * negative + '0';
		input /= 10;
		i++;
	}
	int length = strlen(output);
	//reversing the 'output' string
	char *revoutput = (char *) calloc(length, sizeof(char));
	for (i = 0; i < length; i++) {
		revoutput[i] = output[length - i - 1];
	}
	free(output);
	return revoutput;
}

//converts an unsigned integer into a string
char * uint2string(unsigned int input) {
	char *output;
	output = (char *)calloc(11, sizeof(char));
	int i = 0;
	//creating the array which contains the digits as shown before
	while (input) {
		output[i] = input % 10 + '0';
		input /= 10;
		i++;
	}
	int length = strlen(output);
	//reversing the string
	char *revoutput = (char *)calloc(length, sizeof(char));
	for (i = 0; i < length; i++) {
		revoutput[i] = output[length - i - 1];
	}
	free(output);
	return revoutput;
}

//returns the number of digits of an integer
int intlen(int integer) {
	int length = 0;
	while(integer != 0) {
		integer /= 10;
		length++;
	}
	return length;
}

//returns the number of digits of an unsigned integer
int uintlen(unsigned int unsgnd) {
	int length = 0;
	while(unsgnd != 0) {
		unsgnd /= 10;
		length++;
	}
	return length;	
}

//returns a string which represents a hex number
char * hex2string(unsigned int dec) {
	char *output;
	int mod, i = 0, j;
	output = (char *)calloc(8, sizeof(char));
	//creating the char array which contains the letters/digits of the number
	while (dec != 0) {
		mod = dec % 16;
		if (mod < 10) {
			//converts an integer(digit / 0 - 9) into a char
			output[i] = mod + 48;
			i++;
		}
		else {
			//converts an integer(letter / A-F) into a char
			output[i] = mod + 87;
			i++;
		}
		dec /= 16;
	}
	//reversing the string
	char *revoutput = (char *)calloc(8, sizeof(char));
	for (j = 0; j < i; j++) {
		revoutput[j] = output[i - j - 1];
	}
	free(output);
	return revoutput;
}

int iocla_printf(const char *format, ...)
{
	//'len' stores the format's number of characters
	//'ilen' stores the number of digits of an integer
	//'ulen' stores the number of digits of an unsigned integer
	//'integer'/'unsgnd' stores an (unsigned) integer
	//'retvalue' stores the number of characters which have been printed
	int len = strlen(format), i, ilen, ulen, unsgnd, integer, retvalue = 0;
	char *string, ch;
	va_list args;
	va_start(args, 0);
	//iterating the 'format' array
	for (i = 0; i < len; i++) {
		if (format[i] != '%') {
			write_stdout(&format[i], 1);
			retvalue++;
		}
		else {
			//'%' has been found
			//checking the next character
			switch(format[i + 1]) {
			//printing '%%'
			case '%':
				write_stdout("%", 1);
				i++;
				retvalue++;
				break;
			//printing an integer
			case 'd':
				integer = va_arg(args, int);
				ilen = intlen(integer);
				//if the integer is negative, '-' will be printed first
				if (integer < 0) {
					write_stdout("-", 1);
					retvalue++;
				}
				write_stdout(int2string(integer), ilen);
				i++;
				retvalue += ilen;
				break;
			//printing an unsigned int
			case 'u':
				unsgnd = va_arg(args, int);
				ulen = uintlen(unsgnd);
				write_stdout(uint2string(unsgnd), ulen);
				i++;
				retvalue += ulen;
				break;
			//printing a string
			case 's':
				string = va_arg(args, char *);
				write_stdout(string, strlen(string));
				i++;
				retvalue += strlen(string);
				break;
			//printing a char
			case 'c':
				ch = va_arg(args, int);
				write_stdout(&ch, 1);
				i++;
				retvalue++;
				break;
			//printing a hex
			case 'x':
				unsgnd = va_arg(args, int);
				string = hex2string(unsgnd);
				write_stdout(string, strlen(string));
				retvalue += strlen(string);
				i++;
				break;
			}
		}
	}
	//if at least one character was printed,
	//the number of chars will be returned
	if (retvalue)
		return retvalue;

	return -1;
}
