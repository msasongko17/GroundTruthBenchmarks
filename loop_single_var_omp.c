#include <stdio.h>
#include <omp.h>

int main () {
#pragma omp parallel 
{
	int val = 0;
	__asm__ __volatile__ ("movl $100000000, %%ecx\n\t"
                "1:\n\t"
                "movl $1, %0\n\t"
                "loop 1b\n\t"
                : "=m" (val)
                :
                : "memory", "%ecx"
            );
}
	//printf("val: %d, address of val: %lx\n", val, (long) &val);
	printf("RD: 0, expected count: 100 M\n");
	return 0;
}
