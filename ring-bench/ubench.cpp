#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<omp.h>
#include<stdint.h>
#include<atomic>
#include "util.cpp"

#define CACHELINE_SZ (64)

struct SharedData_t{
	volatile uint64_t dummy1[CACHELINE_SZ/sizeof(uint64_t)]; // avoid buddy cacheline prefetching
	atomic<uint64_t> data[CACHELINE_SZ/sizeof(uint64_t)];
	volatile uint64_t dummy2[CACHELINE_SZ/sizeof(uint64_t)]; // avoid buddy cacheline prefetching
}__attribute__((aligned(64)));

struct SharedLock_t{
	volatile uint64_t dummy1[CACHELINE_SZ/sizeof(uint64_t)]; // avoid buddy cacheline prefetching
	omp_lock_t locks[CACHELINE_SZ/4];
	volatile uint64_t dummy2[CACHELINE_SZ/sizeof(uint64_t)]; // avoid buddy cacheline prefetching
}__attribute__((aligned(64)));

SharedData_t * shared_data;
SharedLock_t * shared_locks;

using namespace std;

int main(int argc, char ** argv){
	int nThreads = -1;
	int nIter = -1;

	//printf("before \n");
	//ParseArg(argc, argv, nIter, nGroups, nThreads, shareFracArray, groupMarker, readWriteMarker, threadList);	
	ParseArg(argc, argv, nIter, nThreads);

	shared_data = (SharedData_t *) malloc ((nThreads) * sizeof(struct SharedData_t));

	shared_locks = (SharedLock_t *) malloc ((nThreads) * sizeof(struct SharedLock_t));

	atomic<uint64_t> justToAvoidCompilerOptimization;	

	for(int i = 0; i < nThreads; i++) {
		omp_init_lock(&(shared_locks[i].locks[0]));
	}

	#pragma omp parallel num_threads(nThreads) firstprivate(nThreads, nIter)
	{
		int me = omp_get_thread_num();
		
		int operation_count = 0;
		int source = ((me - 1) < 0) ? (nThreads - 1) : (me - 1);
		int first = (source % 2) ? source : me;
		int second = (first == source) ? me : source;
		omp_lock_t * first_lock = &(shared_locks[first].locks[0]);
		omp_lock_t * second_lock = &(shared_locks[second].locks[0]);  
		atomic<uint64_t> * sourceVar = &(shared_data[source].data[0]);
		atomic<uint64_t> * sharedVar = &(shared_data[me].data[0]);

		for(int i = 0; i < nIter; i++) {
			//#pragma omp for
			//for(int j = 0; j < nThreads; j++) { 
				omp_set_lock(first_lock); 
				omp_set_lock(second_lock);
				//printf("assignment happens from %ld to %ld in thread %d\n", *sourceVar, *sharedVar, mytid);
				uint64_t temp = *sourceVar;
				*sharedVar = temp;
				operation_count++; 
				omp_unset_lock(second_lock);
				omp_unset_lock(first_lock);
			//}
		}
		justToAvoidCompilerOptimization += *sharedVar;
		printf("assignment count in thread %d is %d\n", me, operation_count);		
	}

	for(int i = 0; i < nThreads; i++) {
		omp_destroy_lock(&(shared_locks[i].locks[0]));
	}

	if(nThreads > 0) {
		free(shared_data);
		free(shared_locks);
	}
	return justToAvoidCompilerOptimization.load() ^ justToAvoidCompilerOptimization.load();
}
