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
#pragma omp parallel
	{
	int array1[50];
	int array2[100];
	int array3[200];
	int array4[500];
	int array5[1000];
	__asm__ __volatile__ ("movl $10000000, %%edx\n\t"
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
	__asm__ __volatile__ ("movl $4000000, %%edx\n\t"
                "loop3:\n\t"
                "movl $100, %%eax\n\t"
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
                "movl $200, %%eax\n\t"
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
                "movl $500, %%eax\n\t"
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
        __asm__ __volatile__ ("movl $1000000, %%edx\n\t"
                "loop8:\n\t"
                "movl $1000, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "loop9:\n\t"
                "movl %%edx, (%%rbx)\n\t"
                "addq $4, %%rbx\n\t"
                "decl %%eax\n\t"
                "jnz loop9\n\t"
                "decl %%edx\n\t"
                "jnz loop8\n\t"
                :
                : "c" (array4)
                : "%edx", "%eax", "memory", "cc"
            );
	#pragma omp single
	num_threads = omp_get_num_threads();
	}
	printf("RD: 49, expected frequency %d M, RD: 199, expected frequency %d M, RD: 399, expected frequency %d M, RD: 799, expected frequency %d M\n", 50 * 10 * num_threads, 4 * 100 * num_threads, 200 * num_threads, 500 * num_threads, 1000 * num_threads);
	return 0;
}
