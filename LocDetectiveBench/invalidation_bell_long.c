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
	char shared_array[4000000];
	int a1=200000, b1=500000, c1=1000000, d1=2000000, e1=4000000, a2=200000;
#pragma omp parallel
	{
	int output;
	char array1[4000000];
	// time distance: 200000, frequency: 10 M 
	__asm__ __volatile__ ("movl $50, %%edx\n\t"
		"loop1:\n\t"
                "movl %%edi, %%eax\n\t"
                "movq %%rsi, %%r8\n\t"
                "loop01:\n\t"
                "movl %%edx, (%%r8)\n\t"
                "addq $1, %%r8\n\t"
                "decl %%eax\n\t"
                "jnz loop01\n\t"
		"movl %%ebx, %%eax\n\t"
		"movq %%rcx, %%r8\n\t"
		"loop:\n\t"
		"movl %%edx, (%%r8)\n\t"
		"addq $1, %%r8\n\t"
		"decl %%eax\n\t"
		"jnz loop\n\t"
		"decl %%edx\n\t"
		"jnz loop1\n\t"
                :
                : "c" (array1), "S" (shared_array), "b" (a1), "D" (a2)
                : "%edx", "%eax", "memory", "cc"
            );
	//fprintf(stderr, "output: %d\n", output);
	// time distance: 500000, frequency: 20 M 
	__asm__ __volatile__ ("movl $40, %%edx\n\t"
		"loop3:\n\t"
                "movl %%edi, %%eax\n\t"
                "movq %%rsi, %%r8\n\t"
                "loop21:\n\t"
                "movl %%edx, (%%r8)\n\t"
                "addq $1, %%r8\n\t"
                "decl %%eax\n\t"
                "jnz loop21\n\t"
		"movl %%ebx, %%eax\n\t"
		"movq %%rcx, %%r8\n\t"
		"loop2:\n\t"
		"movl %%edx, (%%r8)\n\t"
		"addq $1, %%r8\n\t"
		"decl %%eax\n\t"
		"jnz loop2\n\t"
		"decl %%edx\n\t"
		"jnz loop3\n\t"
                :
                : "c" (array1), "S" (shared_array), "b" (b1), "D" (a2)
                : "%edx", "%eax", "memory", "cc"
            );	
	// time distance: 1000000, frequency: 40 M 
	__asm__ __volatile__ ("movl $40, %%edx\n\t"
		"loop5:\n\t"
                "movl %%edi, %%eax\n\t"
                "movq %%rsi, %%r8\n\t"
                "loop41:\n\t"
                "movl %%edx, (%%r8)\n\t"
                "addq $1, %%r8\n\t"
                "decl %%eax\n\t"
                "jnz loop41\n\t"
		"movl %%ebx, %%eax\n\t"
		"movq %%rcx, %%r8\n\t"
		"loop4:\n\t"
		"movl %%edx, (%%r8)\n\t"
		"addq $1, %%r8\n\t"
		"decl %%eax\n\t"
		"jnz loop4\n\t"
		"decl %%edx\n\t"
		"jnz loop5\n\t"
                :
                : "c" (array1), "S" (shared_array), "b" (c1), "D" (a2)
                : "%edx", "%eax", "memory", "cc"
            );
	// time distance: 2000000, frequency: 20 M 
	__asm__ __volatile__ ("movl $10, %%edx\n\t"
		"loop7:\n\t"
                "movl %%edi, %%eax\n\t"
                "movq %%rsi, %%r8\n\t"
                "loop61:\n\t"
                "movl %%edx, (%%r8)\n\t"
                "addq $1, %%r8\n\t"
                "decl %%eax\n\t"
                "jnz loop61\n\t"
		"movl %%ebx, %%eax\n\t"
		"movq %%rcx, %%r8\n\t"
		"loop6:\n\t"
		"movl %%edx, (%%r8)\n\t"
		"addq $1, %%r8\n\t"
		"decl %%eax\n\t"
		"jnz loop6\n\t"
		"decl %%edx\n\t"
		"jnz loop7\n\t"
                :
                : "c" (array1), "S" (shared_array), "b" (d1), "D" (a2)
                : "%edx", "%eax", "memory", "cc"
            );
        // time distance: 4000000, frequency: 8 M 
	__asm__ __volatile__ ("movl $3, %%edx\n\t"
		"loop9:\n\t"
                "movl %%edi, %%eax\n\t"
                "movq %%rsi, %%r8\n\t"
                "loop81:\n\t"
                "movl %%edx, (%%r8)\n\t"
                "addq $1, %%r8\n\t"
                "decl %%eax\n\t"
                "jnz loop81\n\t"
		"movl %%ebx, %%eax\n\t"
		"movq %%rcx, %%r8\n\t"
		"loop8:\n\t"
		"movl %%edx, (%%r8)\n\t"
		"addq $1, %%r8\n\t"
		"decl %%eax\n\t"
		"jnz loop8\n\t"
		"decl %%edx\n\t"
		"jnz loop9\n\t"
                : 
                : "c" (array1), "S" (shared_array), "b" (e1), "D" (a2)
                : "%edx", "%eax", "memory", "cc"
            );
	#pragma omp single
	num_threads = omp_get_num_threads();
	}
	printf("RD: 200000, expected frequency %d M, RD: 500000, expected frequency %d M, RD: 1000000, expected frequency %d M, RD: 2000000, expected frequency %d M, RD: 4000000, expected frequency %d M\n", 10 * num_threads, 20 * num_threads, 40 * num_threads, 20 * num_threads, 8 * num_threads);
	return 0;
}
