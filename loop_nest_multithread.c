#include <stdio.h>

int main () {
	int val = 0;

	#pragma omp parallel num_threads(4) 
	{
	int array1[200];
	__asm__ __volatile__ ("movl $1000000, %%edx\n\t"
		"loop1:\n\t"
		"movl $200, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop:\n\t"
		"movl %%edx, (%%rbx)\n\t"
		"addq $4, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop\n\t"
		"decl %%edx\n\t"
		"jnz loop1\n\t"
                : 
                : "c" (array1)
                : "%edx", "%eax", "memory", "cc"
            );
	}

	printf("RD: 200, expected frequency 800 M\n");
	return 0;
}
