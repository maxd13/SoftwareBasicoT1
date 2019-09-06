#include <stdio.h>
void dump (void *p, int n) {
unsigned char *p1 = (unsigned char *) p;
while (n--) {
printf("%p - %02x\n", p1, *p1);
p1++;
}
}
struct S {
short cs;
int ci;
} s = {0x55aa, -2050};
struct S1 {
struct S *ps;
long cl1;
short cs1;
} s1;
int main (void) {
s1.ps = (struct S*) 0x55d060f70010;
s1.cl1 = (long) s.ci;
s1.cs1 = (s.cs >> 8) & 3;
dump (&s1, sizeof(s1));
return 0;
}
