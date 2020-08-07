#include <stdio.h>
#include <omp.h>

// bin start size: 130
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
#pragma omp parallel
	{
	
	char array1[400000];
	// time distance: 200000, frequency: 40 M 
	__asm__ __volatile__ ("movl $200, %%edx\n\t"
		"loop1:\n\t"
		"movl $200000, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop:\n\t"
		"movl %%edx, (%%rbx)\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop\n\t"
		"decl %%edx\n\t"
		"jnz loop1\n\t"
                : 
                : "c" (array1)
                : "%edx", "%eax", "memory", "cc"
            );
	// time distance: 500000, frequency: 20 M 
	__asm__ __volatile__ ("movl $40, %%edx\n\t"
		"loop3:\n\t"
		"movl $500000, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop2:\n\t"
		"movl %%edx, (%%rbx)\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop2\n\t"
		"decl %%edx\n\t"
		"jnz loop3\n\t"
                : 
                : "c" (array1)
                : "%edx", "%eax", "memory", "cc"
            );	
	// time distance: 1000000, frequency: 10 M 
	__asm__ __volatile__ ("movl $10, %%edx\n\t"
		"loop5:\n\t"
		"movl $1000000, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop4:\n\t"
		"movl %%edx, (%%rbx)\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop4\n\t"
		"decl %%edx\n\t"
		"jnz loop5\n\t"
                : 
                : "c" (array1)
                : "%edx", "%eax", "memory", "cc"
            );
	// time distance: 2000000, frequency: 8 M 
	__asm__ __volatile__ ("movl $4, %%edx\n\t"
		"loop7:\n\t"
		"movl $2000000, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop6:\n\t"
		"movl %%edx, (%%rbx)\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop6\n\t"
		"decl %%edx\n\t"
		"jnz loop7\n\t"
                : 
                : "c" (array1)
                : "%edx", "%eax", "memory", "cc"
            );
        // time distance: 4000000, frequency: 4 M 
	__asm__ __volatile__ ("movl $2, %%edx\n\t"
		"loop9:\n\t"
		"movl $4000000, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop8:\n\t"
		"movl %%edx, (%%rbx)\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop8\n\t"
		"decl %%edx\n\t"
		"jnz loop9\n\t"
                : 
                : "c" (array1)
                : "%edx", "%eax", "memory", "cc"
            );    
	#pragma omp single
	num_threads = omp_get_num_threads();
	}
	printf("RD: 200000, expected frequency %d M, RD: 500000, expected frequency %d M, RD: 1000000, expected frequency %d M, RD: 2000000, expected frequency %d M, RD: 4000000, expected frequency %d M\n", 40 * num_threads, 20 * num_threads, 10 * num_threads, 8 * num_threads, 4 * num_threads);
	return 0;
}
