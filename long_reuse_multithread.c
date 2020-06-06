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
#pragma omp parallel num_threads(4)
{
	char array1[4000000];
	__asm__ __volatile__ (
		"movl $1000000, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop:\n\t"
		"movl $4, (%%rbx)\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop\n\t"
		"movl $2000000, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop1:\n\t"
                "movl $2, (%%rbx)\n\t"
                "addq $1, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop1\n\t"
		"movl $4000000, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop2:\n\t"
                "movl $1, (%%rbx)\n\t"
                "addq $1, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop2\n\t"
		"movl $4000000, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop3:\n\t"
                "movl $1, (%%rbx)\n\t"
                "addq $1, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop3\n\t"
                : 
                : "c" (array1)
                : "%eax", "%rbx", "memory", "cc"
            );
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
	printf("RD 1 M expected count: 4 M, RD 2 M expected count: 8 M, RD 4 M expected count: 16 M\n");
	//printf("val: %d\n", val);
	return 0;
}
