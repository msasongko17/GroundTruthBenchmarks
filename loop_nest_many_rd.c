#include <stdio.h>
#include <omp.h>

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
#pragma omp parallel
{
	int array1[800];
	__asm__ __volatile__ ("movl $1000000, %%edx\n\t"
		"loop1:\n\t"
		"movl $50, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop:\n\t"
		"movl %%edx, (%%rbx)\n\t"
		"addq $4, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop\n\t"

		"movl $200, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop2:\n\t"
                "movl %%edx, (%%rbx)\n\t"
                "addq $4, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop2\n\t"

		"movl $400, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop3:\n\t"
                "movl %%edx, (%%rbx)\n\t"
                "addq $4, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop3\n\t"

		"movl $800, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop4:\n\t"
                "movl %%edx, (%%rbx)\n\t"
                "addq $4, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop4\n\t"

		"decl %%edx\n\t"
		"jnz loop1\n\t"
                : 
                : "c" (array1)
                : "%edx", "%eax", "memory", "cc"
            );
}	
	printf("RD: 50, expected count: 50 M, RD: 200, expected count: 200 M, RD: 400, expected count: 400 M, RD: 800, expected count: 50 M, RD850, expected count: 150 M, RD: 1050, expected count 200 M, RD: 1450, expected count 400M\n");
	return 0;
}
