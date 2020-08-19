#include <omp.h>

int main() {
	char array1[1000000];
	int loop_trip_count = 2;
	#pragma omp parallel num_threads(2)
	{
		if(omp_get_thread_num() == 0)
		{
    			char array2[1000000];
    			int i = 0;
    			while(i < 1000000) {
    				if((i%loop_trip_count) == 0) {
    					array1[i] = 1;
    				} else {
    					array2[i] = 1;
    				}
    				i++;
    			}
		}

		if(omp_get_thread_num() == 1)
		{
    			char array2[1000000];
    			int i = 0;
    			while(i < 1000000) {
    				if((i%loop_trip_count) == 0) {
    					array1[i] = 1;
    				} else {
    					array2[i] = 1;
    				}
    				i+=2;
    			}
		}
	}
	return 0;
}
