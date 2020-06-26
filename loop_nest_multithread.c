#include <stdio.h>
#include <omp.h>

int main () {
	int val = 0;
	int num_threads;

	#pragma omp parallel
	{
	int array1[200];
	__asm__ __volatile__ ("movl $1000000, %%edx\n\t"
		"loop1:\n\t"
		"movl $200, %%eax\n\t"
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
		//fprintf(stderr, "in thread %d out of %d threads()\n", omp_get_thread_num(), omp_get_num_threads());
		#pragma omp single
		num_threads = omp_get_num_threads();
	}

	printf("RD: 200, expected frequency %d M\n", 200 * num_threads);
	return 0;
}
