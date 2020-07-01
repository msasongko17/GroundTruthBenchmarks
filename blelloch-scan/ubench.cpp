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

SharedData_t ** sumData;
SharedData_t ** tempData;

using namespace std;

int main(int argc, char ** argv){
	int nThreads = -1;
	int nIter = -1;

	//printf("before \n");
	//ParseArg(argc, argv, nIter, nGroups, nThreads, shareFracArray, groupMarker, readWriteMarker, threadList);	
	ParseArg(argc, argv, nIter, nThreads);

	sumData = (SharedData_t **) malloc ((nThreads) * sizeof(struct SharedData_t *));

	for(int i = 0; i < nThreads; i++) {
		sumData[i] = (SharedData_t *) malloc (sizeof(struct SharedData_t));
	}

	tempData = (SharedData_t **) malloc ((nThreads) * sizeof(struct SharedData_t *));

	for(int i = 0; i < nThreads; i++) {
		tempData[i] = (SharedData_t *) malloc (sizeof(struct SharedData_t));
	}

	atomic<uint64_t> justToAvoidCompilerOptimization;	

	#pragma omp parallel num_threads(nThreads) firstprivate(nIter)
	{
		int me = omp_get_thread_num();
		sumData[me]->data[0] = me;
		#pragma omp barrier
		atomic<uint64_t> *sData = &(sumData[me]->data[0]);
		atomic<uint64_t> *tData = &(tempData[me]->data[0]);
		int iterator = me;
		int send_flag = 1;
		int leap = 1;
		uint64_t tmp_data;
		printf("thread %d is started\n", me);
		for(int i = nThreads; i > 1; i/=2) {
			//if(me+leap < nThreads) {
			//atomic<uint64_t> *pData = &(sumData[me+leap]->data[0]);
			//if((iterator % 2) && send_flag) {
			if(me % (leap * 2) == 0) {
				atomic<uint64_t> *pData = &(sumData[me+leap]->data[0]);
				for(int j = 0; j < nIter; j++) {
					if(j == 0) {
						tmp_data = *sData;
						*sData = tmp_data + *pData;
					}
					else {
						*sData = tmp_data + *pData;
					}
				}
				printf("thread %d active is iteration: %d as receiver\n", me, i);
			} else if((iterator % 2) && send_flag){
				for(int j = 0; j < nIter; j++) {
					*sData += 0;
				}
				send_flag = 0;
				printf("thread %d active is iteration: %d as sender\n", me, i);
			}
			//}
			iterator /= 2;
			leap *= 2;
			#pragma omp barrier
		}
		leap /= 2;
		//printf("first pass is finished\n");
		//printf("first pass is finished send_flag: %d, leap: %d, thread: %d\n", send_flag, leap, me);
		// second pass	
		if(send_flag) {
			*sData = 0;
		}
		if((me % leap) == 0) {
			tmp_data = *sData;
			*tData = tmp_data;
		}
		//printf("thread: %d, *tData: %ld\n", me, *tData);
		#pragma omp barrier
		for(int i = nThreads; i > 0; i/=2) {
			if(leap > 0) {
				if((me % leap) == 0) {
					tmp_data = *tData;
					*sData = tmp_data;
				}
				#pragma omp barrier
				if((me % leap) == 0) {
					if((me % (leap*2)) == 0) {
						atomic<uint64_t> *pData = &(sumData[me+leap]->data[0]);
						for(int j = 0; j < nIter; j++) {
			
							*sData += 0;

							tmp_data = *sData;
							*tData = tmp_data;
							tmp_data = *pData;
							*tData += tmp_data;
						}
					} else {
						atomic<uint64_t> *pData = &(sumData[me-leap]->data[0]);
						for(int j = 0; j < nIter; j++) {

							*sData += 0;

							tmp_data = *pData; 
							*tData = tmp_data;
						}
					}
				} else if ( (leap/2 > 0) && (me % (leap/2)) == 0) {
					tmp_data = *sData;
					*tData = tmp_data;
				}
			}
			//printf("thread: %d, i: %d\n", me, i);
			leap /= 2;
			#pragma omp barrier
		}
		tmp_data = *tData;
		*sData = tmp_data;
		uint64_t printed_data = *sData;
		printf("thread %d, accumulated value is %ld, leap: %d, send_flag: %d\n", me, printed_data, leap, send_flag);
	}

	if(nThreads > 0) {
        	for(int i = 0; i < nThreads; i++) {
                	free(sumData[i]);
        	}
		free(sumData);
		for(int i = 0; i < nThreads; i++) {
                	free(tempData[i]);
        	}
		free(tempData);
	}
	return justToAvoidCompilerOptimization.load() ^ justToAvoidCompilerOptimization.load();
}
