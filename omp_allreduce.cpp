#include<omp.h>
#include<assert.h>
#include<stdio.h>
#include<stdint.h>
#include<atomic>
#define MAX_THREADS (1024)
#define CHILD_NOT_ARRIVED (0)
#define CHILD_ARRIVED (2)

using namespace std;

struct DS {
	char pad0[64];
	atomic<uint64_t> sum;
	char pad1[64];
	atomic <int> flag;	
	char pad2[64];
	DS(): sum(0), flag(CHILD_NOT_ARRIVED){
	}
};

DS  ds[ 2 * MAX_THREADS];


void WaitChildArrival(DS & x) {
	while(atomic_load_explicit(&x.flag, memory_order_acquire) != CHILD_ARRIVED);
}

void SignalParent(DS & p, uint64_t val) {
	atomic_fetch_add_explicit(&p.sum, val, memory_order_seq_cst);
	atomic_fetch_add_explicit(&p.flag, 1, memory_order_seq_cst);
}

void WaitParent(DS & x) {
	while(atomic_load_explicit(&x.flag, memory_order_acquire) != CHILD_NOT_ARRIVED) ;
}

void SignalChild(DS & c1, DS & c2, DS & p) {
	auto v = atomic_load_explicit(&p.sum, memory_order_acquire);
	atomic_store_explicit(&p.sum, (long unsigned int)0, memory_order_release);
	atomic_store_explicit( &p.flag, CHILD_NOT_ARRIVED, memory_order_release);
	atomic_store_explicit(& c1.sum, v, memory_order_release);
	atomic_store_explicit(& c2.sum, v, memory_order_release);
	atomic_store_explicit( &c1.flag, CHILD_NOT_ARRIVED, memory_order_release);
	atomic_store_explicit( &c2.flag, CHILD_NOT_ARRIVED, memory_order_release);
	//printf("\n %d Wrote %lu to %d and %d and rest %d\n", &p - &ds[0], v, &c1 - &ds[0], &c2 - &ds[0], &p - &ds[0]);
}

uint64_t AllReduce(int me, int round, int nThreads) {
	int mySlot = (round == 0) ? nThreads  - 1 + me : me;
	bool leaf = round == 0;
	bool root = mySlot == 0;
	int myParent = (mySlot - 1) / 2;
	int myChild1 = 2 * mySlot + 1;
	int myChild2 = 2 * mySlot + 2;

	if (! leaf) {
		if (nThreads > 1)
			WaitChildArrival(ds[mySlot]);
	} else {
		ds[mySlot].flag = CHILD_ARRIVED;
	}

	// Proceed to parent is odd number.
	bool proceedToParent = (mySlot & 1) ;

	if (! root) {
		//printf("\n Value at parent %d = %lu", myParent, atomic_load_explicit( &ds[myParent].sum, memory_order_seq_cst));
		SignalParent(ds[myParent], ds[mySlot].sum);
		if ( proceedToParent ) {
			AllReduce(myParent, round + 1, nThreads);
		} else {
			WaitParent(ds[mySlot]);	
		}
	} else {
		printf("\n Value at root = %lu", atomic_load_explicit(&ds[mySlot].sum, memory_order_seq_cst));
	}
	uint64_t retVal = ds[mySlot].sum;
	if (! leaf) {
		SignalChild(ds[myChild1], ds[myChild2], ds[mySlot]);
	} else {
		// reset 
	        atomic_store_explicit( &ds[mySlot].sum, (long unsigned int) 0, memory_order_release);
       	 	atomic_store_explicit( &ds[mySlot].flag, CHILD_NOT_ARRIVED, memory_order_release);
	}

	return retVal;
}


int main(){
	
#pragma omp parallel 
{
	for(int i = 0; i < 100000; i++) {
		int me = omp_get_thread_num();
		int nThreads = omp_get_num_threads();
		assert((__builtin_popcount(nThreads) == 1) && "OMP_NUM_THREADS must be a power of 2");
		ds[me + nThreads - 1].sum  = i + me;
		uint64_t sum = AllReduce(me, 0, nThreads); 
		uint64_t exp = nThreads * i + (nThreads * (nThreads-1) / 2);
		assert(sum == exp);
		//if (me == 0) printf("\n sum = %lu:%lu, .. ds[2].sum = %lu", sum, exp, atomic_load(&ds[2].sum));
	}
}
	return 0;
}

