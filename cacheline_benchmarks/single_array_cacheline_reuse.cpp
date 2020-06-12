#include <iostream>

using namespace std;

#define CACHELINE_SZ (64)
/*
struct SharedData_t{
	volatile uint64_t dummy1[CACHELINE_SZ/sizeof(uint64_t)]; // avoid buddy cacheline prefetching
	//volatile uint64_t data[CACHELINE_SZ/sizeof(uint64_t)]; 
	int data[CACHELINE_SZ/sizeof(int)]; 
	volatile uint64_t dummy2[CACHELINE_SZ/sizeof(uint64_t)]; // avoid buddy cacheline prefetching
}__attribute__((aligned(64)));

SharedData_t sharedData;*/

int array1[16000000] __attribute__((aligned(64)));

int main () {
	int val = 0;

	__asm__ __volatile__ ("movl $16000000, %%edx\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop:\n\t"
		"movl $1, (%%rbx)\n\t"
		"addq $4, %%rbx\n\t"
		"decl %%edx\n\t"
		"jnz loop\n\t"
                : 
                : "c" (array1)
                : "%edx", "%rbx", "memory", "cc"
            );
	cout << "RD: 0, expected count: 1.5 M" << endl;
	//printf("%ld\n", &array1[0]);
	return 0;
}
