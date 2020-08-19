#include <stdio.h>
#include <omp.h>

int main () {
	int jump_size = 16;
	char array1[1000000];
#pragma omp parallel num_threads(2)
{
	char array2[1000000];
	if(omp_get_thread_num() == 0) {
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

	if(omp_get_thread_num() == 1) {
        __asm__ __volatile__ (
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
                "increment1:\n\t"
                "addq $2, %%rbx\n\t"
                "addq $2, %%r9\n\t"
                "addl $2, %%eax\n\t"
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
	/*for(int i = 0; i < 5; i++) {
		__asm__ __volatile__("movl $1, %%eax\n\t"
			"movl %%eax, %0\n\t"
			: "=m" (array1[i])
			: "r" (i)
			: "memory", "%eax"
		);
	}*/
	/*for(int i = 0; i < 4000000; i++) {
		printf("%d: %d\n", i, array1[i]);
	}*/
	//printf("val: %d\n", val);
	return 0;
}
