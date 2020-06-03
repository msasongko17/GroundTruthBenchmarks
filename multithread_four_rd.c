#include <stdio.h>

int main () {
	int val = 0;
	/*__asm__ __volatile__ ("movl $100000000, %%ecx\n\t"
                "movl $0, %%edx\n\t"
                "1:\n\t"
                "incl %0\n\t"
                "loop 1b\n\t"
		: "=m" (val)
		:
		: "memory", "%ecx", "%edx"
            );*/
#pragma omp parallel num_threads (4)
	{
	int array1[50];
	int array2[200];
	int array3[400];
	int array4[800];
	__asm__ __volatile__ ("movl $1000000, %%edx\n\t"
		"loop1:\n\t"
		"movl $50, %%eax\n\t"
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
	__asm__ __volatile__ ("movl $1000000, %%edx\n\t"
                "loop3:\n\t"
                "movl $200, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop2:\n\t"
                "movl %%edx, (%%rbx)\n\t"
                "addq $4, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop2\n\t"
                "decl %%edx\n\t"
                "jnz loop3\n\t"
                :
                : "c" (array2)
                : "%edx", "%eax", "memory", "cc"
            );	
	__asm__ __volatile__ ("movl $1000000, %%edx\n\t"
                "loop4:\n\t"
                "movl $400, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop5:\n\t"
                "movl %%edx, (%%rbx)\n\t"
                "addq $4, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop5\n\t"
                "decl %%edx\n\t"
                "jnz loop4\n\t"
                :
                : "c" (array3)
                : "%edx", "%eax", "memory", "cc"
            );
	__asm__ __volatile__ ("movl $1000000, %%edx\n\t"
                "loop6:\n\t"
                "movl $800, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop7:\n\t"
                "movl %%edx, (%%rbx)\n\t"
                "addq $4, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop7\n\t"
                "decl %%edx\n\t"
                "jnz loop6\n\t"
                :
                : "c" (array4)
                : "%edx", "%eax", "memory", "cc"
            );
	}
	printf("RD: 49, expected frequency 200 M, RD: 199, expected frequency 800 M, RD: 399, expected frequency 1600 M, RD: 799, expected frequency 3200 M\n");
	return 0;
}
