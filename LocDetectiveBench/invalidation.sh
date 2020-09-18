#! /bin/bash

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=2 GOMP_CPU_AFFINITY="0 1" HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation 2>&1 | tee invalidation_2_log

mkdir invalidation_2_threads

mv *hpcrun invalidation_2_threads

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=4 GOMP_CPU_AFFINITY="0 1 2 3" HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation 2>&1 | tee invalidation_4_log

mkdir invalidation_4_threads

mv *hpcrun invalidation_4_threads

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=8 GOMP_CPU_AFFINITY="0 1 2 3 4 5 6 7"  HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation 2>&1 | tee invalidation_8_log

mkdir invalidation_8_threads

mv *hpcrun invalidation_8_threads

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=16 GOMP_CPU_AFFINITY="0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15" HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation 2>&1 | tee invalidation_16_log

mkdir invalidation_16_threads

mv *hpcrun invalidation_16_threads

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=32 GOMP_CPU_AFFINITY="0 20 1 21 2 22 3 23 4 24 5 25 6 26 7 27 10 30 11 31 12 32 13 33 14 34 15 35 16 36 17 37" HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation 2>&1 | tee invalidation_32_log

mkdir invalidation_32_threads

mv *hpcrun invalidation_32_threads
