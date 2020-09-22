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
	// a2 must be bigger than 0
	int a1=1, b1=300000, c1=800000, d1=1800000, e1=3800000, a2=800000;
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
//#pragma omp barrier
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
//#pragma omp barrier
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
//#pragma omp barrier
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
//#pragma omp barrier
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
	printf("expected RD1: %d, reuse count1: %d, expected RD2: %d, reuse count2: %d, expected RD3: %d, reuse count3: %d, expected RD4: %d, reuse count4: %d, expected RD5: %d, reuse count5: %d\n", a1 + a2, 50 * a1 * num_threads, b1 + a2, 40 * b1 * num_threads, c1 + a2, 40 * c1 * num_threads, d1 + a2, 10 * d1 * num_threads, e1 + a2, 3 * e1 * num_threads);
	return 0;
}
