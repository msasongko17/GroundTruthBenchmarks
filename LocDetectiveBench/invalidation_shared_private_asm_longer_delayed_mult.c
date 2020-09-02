#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main (int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Usage: ./exec jump_size\n");
		return -1;
	}
	int jump_size = atoi(argv[1]);
	char array1[1000000];
#pragma omp parallel
{
	char array2[1000000];
	if(!(omp_get_thread_num() % 2)) {
	__asm__ __volatile__ (
		"movl $1000, %%edx\n\t"
		"loop4:\n\t"
		"movl $0, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"movq %%rsi, %%r9\n\t"
		"loop:\n\t"
		"lea -1(%%edi,1),%%r8d\n\t"
		"and %%eax, %%r8d\n\t"
		"jnz private\n\t"
		"movl $4, (%%rbx)\n\t"
		"mfence\n\t"
		"jmp increment\n\t"
		"private:\n\t"
		"movl $4, (%%r9)\n\t"
		"mfence\n\t"
		"increment:\n\t"
		"addq $1, %%rbx\n\t"
		"addq $1, %%r9\n\t"
		"incl %%eax\n\t"
		"cmp $1000000, %%eax\n\t"
		"jne loop\n\t"
                "decl %%edx\n\t"
		"jnz loop4\n\t"
                : 
                : "c" (array1), "S" (array2), "D" (jump_size)
                : "%eax", "%rbx", "%r8", "%r9", "memory", "cc"
            );
	}

	if(omp_get_thread_num() % 2) {
       		__asm__ __volatile__ (
		"movl $500000, %%edx\n\t"
		"loop13:\n\t"
		"decl %%edx\n\t"
		"jnz loop13\n\t"
                "movl $1000, %%edx\n\t"
                "loop5:\n\t"
                "movl $0, %%eax\n\t"
                "movq %%rcx, %%rbx\n\t"
                "movq %%rsi, %%r9\n\t"
                "loop1:\n\t"
                "lea -1(%%edi,1),%%r8d\n\t"
                "and %%eax, %%r8d\n\t"
                "jnz private1\n\t"
                "movl $4, (%%rbx)\n\t"
                "mfence\n\t"
                "jmp increment1\n\t"
                "private1:\n\t"
                "movl $4, (%%r9)\n\t"
		"mfence\n\t"
                "increment1:\n\t"
                "addq $1, %%rbx\n\t"
                "addq $1, %%r9\n\t"
                "incl %%eax\n\t"
                "cmp $1000000, %%eax\n\t"
                "jne loop1\n\t"
                "decl %%edx\n\t"
                "jnz loop5\n\t"
                :
                : "c" (array1), "S" (array2), "D" (jump_size)
                : "%eax", "%rbx", "%r8", "%r9", "memory", "cc"
            );	 
        }
		
}
	/*for(int i = 0; i <1000000; i++)
		fprintf(stderr, "array1[%d]: %d\t", i, array1[i]);*/
	fprintf(stderr, "\n");
	fprintf(stderr, "jump_size: %d\n", jump_size);	
	return 0;
}
