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
	int a2=1000, b2=300000, c2=800000, d2=1800000, e2=3800000, a3=1, a = 10;
#pragma omp parallel shared(a2, b2, c2, d2, e2, a3, a)
	{
	int output;
	char array1[4000000];
	// time distance: 200000, frequency: 10 M 
	__asm__ __volatile__ ("loop0:\n\t"
		"movl $50, %%r8d\n\t"
		"loop1:\n\t"
                "movl %%edx, %%ebx\n\t"
                "movq %%rsi, %%r9\n\t"
                "loop11:\n\t"
                //"movb $1, (%%r9)\n\t"
                "movl %%r8d, (%%r9)\n\t"
                "addq $1, %%r9\n\t"
                "decl %%ebx\n\t"
                "jnz loop11\n\t"
                "movl $200000, %%ebx\n\t"
		"movq %%rdi, %%r9\n\t"
		"loop12:\n\t"
		"movl %%r8d, (%%r9)\n\t"
		"addq $1, %%r9\n\t"
		"movb (%%r9), %%r10b\n\t"
		"addq $1, %%r9\n\t"
		"subl $2, %%ebx\n\t"
		"jnz loop12\n\t"
		"decl %%r8d\n\t"
		"jnz loop1\n\t"
		
		"movl $40, %%r8d\n\t"
		"loop2:\n\t"
                "movl %%edx, %%ebx\n\t"
                "movq %%rsi, %%r9\n\t"
                "loop21:\n\t"
                "movb $1, (%%r9)\n\t"
                "addq $1, %%r9\n\t"
                "decl %%ebx\n\t"
                "jnz loop21\n\t"
                "movl $500000, %%ebx\n\t"
		"movq %%rdi, %%r9\n\t"
		"loop22:\n\t"
		"movb %%dl, (%%r9)\n\t"
		"addq $1, %%r9\n\t"
		"movb (%%r9), %%r10b\n\t"
		"addq $1, %%r9\n\t"
		"subl $2, %%ebx\n\t"
		"jnz loop22\n\t"
		"decl %%r8d\n\t"
		"jnz loop2\n\t"
		
		"movl $40, %%r8d\n\t"
		"loop3:\n\t"
                "movl %%edx, %%ebx\n\t"
                "movq %%rsi, %%r9\n\t"
                "loop31:\n\t"
                "movb $1, (%%r9)\n\t"
                "addq $1, %%r9\n\t"
                "decl %%ebx\n\t"
                "jnz loop31\n\t"
                "movl $1000000, %%ebx\n\t"
		"movq %%rdi, %%r9\n\t"
		"loop32:\n\t"
		"movb %%dl, (%%r9)\n\t"
		"addq $1, %%r9\n\t"
		"movb (%%r9), %%r10b\n\t"
		"addq $1, %%r9\n\t"
		"subl $2, %%ebx\n\t"
		"jnz loop32\n\t"
		"decl %%r8d\n\t"
		"jnz loop3\n\t"

		"movl $10, %%r8d\n\t"
		"loop4:\n\t"
                "movl %%edx, %%ebx\n\t"
                "movq %%rsi, %%r9\n\t"
                "loop41:\n\t"
                "movb $1, (%%r9)\n\t"
                "addq $1, %%r9\n\t"
                "decl %%ebx\n\t"
                "jnz loop41\n\t"
                "movl $2000000, %%ebx\n\t"
		"movq %%rdi, %%r9\n\t"
		"loop42:\n\t"
		"movb %%dl, (%%r9)\n\t"
		"addq $1, %%r9\n\t"
		"movb (%%r9), %%r10b\n\t"
		"addq $1, %%r9\n\t"
		"subl $2, %%ebx\n\t"
		"jnz loop42\n\t"
		"decl %%r8d\n\t"
		"jnz loop4\n\t"
		
		"movl $3, %%r8d\n\t"
		"loop5:\n\t"
                "movl %%edx, %%ebx\n\t"
                "movq %%rsi, %%r9\n\t"
                "loop51:\n\t"
                "movb $1, (%%r9)\n\t"
                "addq $1, %%r9\n\t"
                "decl %%ebx\n\t"
                "jnz loop51\n\t"
                "movl $4000000, %%ebx\n\t"
		"movq %%rdi, %%r9\n\t"
		"loop52:\n\t"
		"movb %%dl, (%%r9)\n\t"
		"addq $1, %%r9\n\t"
		"movb (%%r9), %%r10b\n\t"
		"addq $1, %%r9\n\t"
		"subl $2, %%ebx\n\t"
		"jnz loop52\n\t"
		"decl %%r8d\n\t"
		"jnz loop5\n\t"
		
		"decl %%ecx\n\t"
		"jnz loop0\n\t"
                :
                : "S" (array1), "D" (shared_array), "c" (a), "d" (a3)
                : "%r8", "%r9", "%r10", "memory", "cc"
            );
	#pragma omp single
	num_threads = omp_get_num_threads();
	}
	//printf("expected RD1: %d, reuse count1: %d, expected RD2: %d, reuse count2: %d, expected RD3: %d, reuse count3: %d, expected RD4: %d, reuse count4: %d, expected RD5: %d, reuse count5: %d\n", a1 + a2, 50 * a1 * num_threads, b1 + a2, 40 * b1 * num_threads, c1 + a2, 40 * c1 * num_threads, d1 + a2, 10 * d1 * num_threads, e1 + a2, 3 * e1 * num_threads);
	return 0;
}
