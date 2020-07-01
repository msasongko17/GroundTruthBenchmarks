#!/bin/sh

GOMP_CPU_AFFINITY="0 1 10 11" LD_LIBRARY_PATH=/home/msasongko17/project/feather-project/adamant-double/src /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/project/feather-project/hpctoolkit-bin/bin/hpcrun -o test1_output_folder -e WP_FALSE_SHARING -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./ubench -g 2 -n 4 -s 1.0 1.0 -d 2 2 -t 0 1 2 3 -r 2 -i 1000000000

GOMP_CPU_AFFINITY="0 1 10 11" LD_LIBRARY_PATH=/home/msasongko17/project/feather-project/adamant-double/src /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/project/feather-project/hpctoolkit-bin/bin/hpcrun -o test1_output_folder -e WP_FALSE_SHARING -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./ubench -g 2 -n 4 -s 1.0 1.0 -d 2 2 -t 0 1 2 3 -r 2 -i 1000000000

GOMP_CPU_AFFINITY="0 1 10 11" LD_LIBRARY_PATH=/home/msasongko17/project/feather-project/adamant-double/src /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/project/feather-project/hpctoolkit-bin/bin/hpcrun -o test1_output_folder -e WP_FALSE_SHARING -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./ubench -g 2 -n 4 -s 1.0 1.0 -d 2 2 -t 0 1 2 3 -r 2 -i 1000000000

GOMP_CPU_AFFINITY="0 1 10 11" LD_LIBRARY_PATH=/home/msasongko17/project/feather-project/adamant-double/src /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/project/feather-project/hpctoolkit-bin/bin/hpcrun -o test1_output_folder -e WP_FALSE_SHARING -e MEM_UOPS_RETIRED:ALL_LOADS@1000 -e MEM_UOPS_RETIRED:ALL_STORES@1000 ./ubench -g 2 -n 4 -s 1.0 1.0 -d 2 2 -t 0 1 2 3 -r 2 -i 1000000000

GOMP_CPU_AFFINITY="0 1 10 11" LD_LIBRARY_PATH=/home/msasongko17/project/feather-project/adamant-double/src /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/project/feather-project/hpctoolkit-bin/bin/hpcrun -o test1_output_folder -e WP_FALSE_SHARING -e MEM_UOPS_RETIRED:ALL_LOADS@1000 -e MEM_UOPS_RETIRED:ALL_STORES@1000 ./ubench -g 2 -n 4 -s 1.0 1.0 -d 2 2 -t 0 1 2 3 -r 2 -i 1000000000

GOMP_CPU_AFFINITY="0 1 10 11" LD_LIBRARY_PATH=/home/msasongko17/project/feather-project/adamant-double/src /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/project/feather-project/hpctoolkit-bin/bin/hpcrun -o test1_output_folder -e WP_FALSE_SHARING -e MEM_UOPS_RETIRED:ALL_LOADS@1000 -e MEM_UOPS_RETIRED:ALL_STORES@1000 ./ubench -g 2 -n 4 -s 1.0 1.0 -d 2 2 -t 0 1 2 3 -r 2 -i 1000000000
