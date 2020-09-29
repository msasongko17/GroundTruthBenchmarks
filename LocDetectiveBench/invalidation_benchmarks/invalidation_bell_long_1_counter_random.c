#include <stdio.h>
#include <stdint.h>
#include <omp.h>

static inline  uint64_t rdtsc(){
        unsigned int lo,hi;
        __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
        return ((uint64_t)hi << 32) | lo;
}

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
	int a = 1000, a1=200000, b1=500000, c1=1000000, d1=2000000, e1=4000000, a2=1000;
	uint64_t prob1 = 34, prob2 = 61, prob3 = 88, prob4 = 95;
	uint64_t rand_num;
	#pragma omp parallel
	{
		int output;
		char array1[4000000];
		for(int i = 0; i < a; i++) {
		#pragma omp single
		{
			rand_num = rdtsc() % 100;
		}
		#pragma omp barrier
		if(rand_num < prob1) {
		__asm__ __volatile__ ("movl $2, %%edx\n\t"
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
            	} else if (rand_num < prob2) {
		__asm__ __volatile__ ("movl $2, %%edx\n\t"
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
            	} else if (rand_num < prob3) {
		__asm__ __volatile__ ("movl $2, %%edx\n\t"
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
            	} else if (rand_num < prob4) { 
		__asm__ __volatile__ ("movl $2, %%edx\n\t"
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
            	} else {
		__asm__ __volatile__ ("movl $2, %%edx\n\t"
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
            	}
            	}
		#pragma omp single
		{
		num_threads = omp_get_num_threads();
		}
	}
	return 0;
}
