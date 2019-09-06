#include <stdio.h>

void dump (void *p, int n) {
  unsigned char *p1 = p;
  while (n--) {
    printf("%p - %02x\n", p1, *p1);
    p1++;
  }
}

int main (void) {
  char c = 150; // 96
  short s = -3; // FD FF
  int i = -151; // 69 FF FF FF
  printf("dump de c: \n");
  dump(&c, sizeof(c));
  printf("dump de s: \n");
  dump(&s, sizeof(s));
  printf("dump de i: \n");
  dump(&i, sizeof(i));
  return 0;
}