#pragma once

typedef unsigned short ushort;

// very basic and static itoa
// only works for base 10 and small signed numbers
// (up to 2**16)
ushort itoa(ushort x, char* outbuf);
