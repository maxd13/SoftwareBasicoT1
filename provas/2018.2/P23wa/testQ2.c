#include <stdio.h>
int n = 1;
int mal (int t);
int boa (int t);
int verif(int val) {
int r;
if (val > 0) r = mal(val);
else r = boa(val);
return r;
}
int geracc(char off, int cum, int *v) {
int i; int tot = cum;
n += off;
printf("n = %d\n", n);
for (i=0; i<n; i++)
tot += verif(v[i]);
return tot;
}