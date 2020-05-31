#include <stdio.h>

int main () {
	int array1[50];
	int array2[200];
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
	printf("RD: 50, expected frequency 50 M, RD: 200, expected frequency 200 M\n");
	return 0;
}
