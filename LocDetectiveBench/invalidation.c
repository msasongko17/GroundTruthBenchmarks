#include <stdio.h>
#include <omp.h>

int main () {
	int val = 0;
	int num_threads = 0;
	/*__asm__ __volatile__ ("movl $100000000, %%ecx\n\t"
                "movl $0, %%edx\n\t"
                "1:\n\t"
                "incl %0\n\t"
                "loop 1b\n\t"
		: "=m" (val)
		:
		: "memory", "%ecx", "%edx"
            );*/
	char array1[4000000];
#pragma omp parallel
{
	__asm__ __volatile__ (
		"movl $1000, %%edx\n\t"
		"loop4:\n\t"
		"movl $1000000, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop:\n\t"
		"movl $4, (%%rbx)\n\t"
		"mfence\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop\n\t"
                "decl %%edx\n\t"
		"jnz loop4\n\t"
                : 
                : "c" (array1)
                : "%eax", "%rbx", "memory", "cc"
            );
	#pragma omp single
	num_threads = omp_get_num_threads();
}
	/*for(int i = 0; i < 5; i++) {
		__asm__ __volatile__("movl $1, %%eax\n\t"
			"movl %%eax, %0\n\t"
			: "=m" (array1[i])
			: "r" (i)
			: "memory", "%eax"
		);
	}*/
	/*for(int i = 0; i < 4000000; i++) {
		printf("%d: %d\n", i, array1[i]);
	}*/
	//printf("val: %d\n", val);
	return 0;
}
