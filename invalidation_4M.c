#include <stdio.h>
#include <omp.h>

int atomic_var;
int main () {
	int val = 0;
	#pragma omp parallel num_threads(2) 
	{
	if(omp_get_thread_num() == 0) {
	    __asm__ __volatile__ (
                "movl $2000000, %%edx\n\t"
                "loop1:\n\t"
                "movl $10000, %%eax\n\t"
                "loop2:\n\t"
		"decl %%eax\n\t"
                "jnz loop2\n\t"
		
		"movl %%edx, %0\n\t"
		"mfence\n\t"

		"movl $20000, %%eax\n\t"
                "loop3:\n\t"
                "decl %%eax\n\t"
                "jnz loop3\n\t"

                "decl %%edx\n\t"
                "jnz loop1\n\t"
                : "=m" (atomic_var)
                :
                : "%edx", "%eax", "memory", "cc"
            );
	}

	if(omp_get_thread_num() == 1) {
            __asm__ __volatile__ (
                "movl $2000000, %%edx\n\t"
                "loop4:\n\t"
                "movl $20000, %%eax\n\t"
                "loop5:\n\t"
                "decl %%eax\n\t"
                "jnz loop5\n\t"

                "movl %%edx, %0\n\t"
                "mfence\n\t"

                "movl $10000, %%eax\n\t"
                "loop6:\n\t"
                "decl %%eax\n\t"
                "jnz loop6\n\t"

                "decl %%edx\n\t"
                "jnz loop4\n\t"
                : "=m" (atomic_var)
                :
                : "%edx", "%eax", "memory", "cc"
            );
        }

	}
	//printf("val: %d\n", val);
	printf("no RD (due to the memory addresses keep being invalidated) and invalidation count: 2M times\n");
	return 0;
}
