#include<omp.h>
#include<assert.h>
#include<stdio.h>
#include <iostream>
#include<stdint.h>
#include<atomic>
#define MAX_THREADS (1024)
#define SRC_NOT_ARRIVED (0)
#define SRC_ARRIVED (1)


using namespace std;

struct DS {
	char pad0[64];
	atomic<uint64_t> sum;
	char pad1[64];
	atomic <int> flag;	
	char pad2[64];
	atomic <int> ack;
	char pad3[64];
	DS(): sum(0), flag(SRC_NOT_ARRIVED), ack(SRC_NOT_ARRIVED){
	}
};

DS  ds[ 2 * MAX_THREADS];


void WaitSrcArrival(DS & x) {
	while(atomic_load_explicit(&x.flag, memory_order_acquire) != SRC_ARRIVED);
	atomic_store_explicit( &x.flag, SRC_NOT_ARRIVED, memory_order_release);
}

void SignalDest(DS & p, uint64_t val) {
	atomic_fetch_add_explicit(&p.sum, val, memory_order_seq_cst);
	//atomic_store_explicit(&p.flag, SRC_ARRIVED, memory_order_release);
	//while(atomic_load_explicit(&p.ack, memory_order_acquire) != SRC_ARRIVED)
	atomic_store_explicit(&p.flag, SRC_ARRIVED, memory_order_release);
	//atomic_store_explicit(&p.flag, SRC_ARRIVED, memory_order_release);
}

int main(){
	
#pragma omp parallel 
{
	int me = omp_get_thread_num();
        int nThreads = omp_get_num_threads();
	int dest; 
	if((me % 2) == 0)
		dest = (me + 1) % nThreads;
	else
		dest = (me - 1 + nThreads) % nThreads;
	//int src = (me - 1 + nThreads) % nThreads;
	for(int i = 0; i < 10000000; i++) {
		//assert((__builtin_popcount(nThreads) == 1) && "OMP_NUM_THREADS must be a power of 2");
		ds[me + nThreads - 1].sum  = i + me;
		if((me % 2) == 1) {
			// send to (me + 1) % nThreads
			//cout << "thread " << me << " before SignalDest" << endl;
			SignalDest(ds[dest], ds[me].sum);
			//cout << "thread " << me << " after SignalDest" << endl;
			// receive from (me - 1 + nThreads) % nThreads
			WaitSrcArrival(ds[me]);
			//cout << "thread " << me << " after WaitSrcArrival" << endl;
		}
		else {
			// receive from (me - 1 + nThreads) % nThreads
			//cout << "thread " << me << " before WaitSrcArrival" << endl;
			WaitSrcArrival(ds[me]);
			//cout << "thread " << me << " after WaitSrcArrival" << endl;
			// send to (me + 1) % nThreads
			SignalDest(ds[dest], ds[me].sum);
			//cout << "thread " << me << " after SignalDest" << endl;
		}
		atomic_store_explicit( &ds[me].sum, (long unsigned int) 0, memory_order_release);
                //atomic_store_explicit( &ds[me].flag, SRC_NOT_ARRIVED, memory_order_release);
		//atomic_store_explicit( &ds[me].ack, SRC_NOT_ARRIVED, memory_order_release);
		//uint64_t sum = AllReduce(me, 0, nThreads); 
		//uint64_t exp = nThreads * i + (nThreads * (nThreads-1) / 2);
		//assert(sum == exp);
		//if (me == 0) printf("\n sum = %lu:%lu, .. ds[2].sum = %lu", sum, exp, atomic_load(&ds[2].sum));
	}
}
	return 0;
}

