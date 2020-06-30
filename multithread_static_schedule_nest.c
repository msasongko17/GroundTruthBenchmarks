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
            char array1[1000000];
            char array2[2000000];
            char array3[4000000];
#pragma omp parallel shared(array1, array2, array3)
{

	int num_threads = omp_get_num_threads();
	int thread_id = omp_get_thread_num();
	
	int chunk_size = 1000000/num_threads;
	int index = chunk_size*thread_id;
	int max_index = index + chunk_size;

	__asm__ __volatile__ (
		"movl $100, %%edi\n\t"
		"loop:\n\t"
		"movl %%edx, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop1:\n\t"
		"movl $6, (%%rbx)\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop1\n\t"
                "decl %%edi\n\t"
                "jnz loop\n\t"
                : 
                : "c" (&array1[index]), "d" (chunk_size)
                : "%eax", "%rbx", "%edi", "memory", "cc"
            );

	chunk_size = 2000000/num_threads;
        index = chunk_size*thread_id;

        __asm__ __volatile__ (
		"movl $100, %%edi\n\t"
		"loop2:\n\t"
		"movl %%edx, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop3:\n\t"
		"movl $6, (%%rbx)\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop3\n\t"
                "decl %%edi\n\t"
                "jnz loop2\n\t"
                : 
                : "c" (&array2[index]), "d" (chunk_size)
                : "%eax", "%rbx", "%edi", "memory", "cc"
            );
            
        chunk_size = 4000000/num_threads;
        index = chunk_size*thread_id;

        __asm__ __volatile__ (
		"movl $100, %%edi\n\t"
		"loop4:\n\t"
		"movl %%edx, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop5:\n\t"
		"movl $6, (%%rbx)\n\t"
		"addq $1, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop5\n\t"
                "decl %%edi\n\t"
                "jnz loop4\n\t"
                : 
                : "c" (&array3[index]), "d" (chunk_size)
                : "%eax", "%rbx", "%edi", "memory", "cc"
            );
}
	//printf("RD 1 M expected count: %d M, RD 2 M expected count: %d M, RD 4 M expected count: %d M\n", num_threads, 2 * num_threads, 4 * num_threads);
	//printf("val: %d\n", val);
	return 0;
}
