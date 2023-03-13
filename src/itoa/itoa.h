#pragma once

// conversion from integer to string
// only works for base 10 and positive numbers up to 2**16
// returns number of digits (or characters in the string)
unsigned short base10_itoa(unsigned short x, char* outbuf);
