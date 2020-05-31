#include <iostream>

using namespace std;

#define CACHELINE_SZ (64)

struct SharedData_t{
	volatile uint64_t dummy1[CACHELINE_SZ/sizeof(uint64_t)]; // avoid buddy cacheline prefetching
	//volatile uint64_t data[CACHELINE_SZ/sizeof(uint64_t)]; 
	int data[CACHELINE_SZ/sizeof(int)]; 
	volatile uint64_t dummy2[CACHELINE_SZ/sizeof(uint64_t)]; // avoid buddy cacheline prefetching
}__attribute__((aligned(64)));

SharedData_t sharedData;

int main () {
	int val = 0;

	int array1[50];
	__asm__ __volatile__ ("movl $1000000, %%edx\n\t"
		"loop1:\n\t"
		"movl $16, %%eax\n\t"
		"movq %%rcx, %%rbx\n\t"
		"loop:\n\t"
		"movl %%edx, (%%rbx)\n\t"
		"addq $4, %%rbx\n\t"
		"decl %%eax\n\t"
		"jnz loop\n\t"
		"decl %%edx\n\t"
		"jnz loop1\n\t"
                : 
                : "c" (sharedData.data)
                : "%edx", "%eax", "memory", "cc"
            );
	cout << "RD: 0, expected count: 16 M" << endl;
	return 0;
}
