#! /bin/bash

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=32 GOMP_CPU_AFFINITY="0 20 1 21 2 22 3 23 4 24 5 25 6 26 7 27 10 30 11 31 12 32 13 33 14 34 15 35 16 36 17 37" HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation_shared_private_asm_longer_mult 2 2>&1 | tee invalidation_shared_private_asm_longer_mult_2_log

mkdir invalidation_shared_private_jump_size_2_thread_32

mv *hpcrun invalidation_shared_private_jump_size_2_thread_32

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=32 GOMP_CPU_AFFINITY="0 20 1 21 2 22 3 23 4 24 5 25 6 26 7 27 10 30 11 31 12 32 13 33 14 34 15 35 16 36 17 37" HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation_shared_private_asm_longer_mult 4 2>&1 | tee invalidation_shared_private_asm_longer_mult_4_log

mkdir invalidation_shared_private_jump_size_4_thread_32

mv *hpcrun invalidation_shared_private_jump_size_4_thread_32

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=32 GOMP_CPU_AFFINITY="0 20 1 21 2 22 3 23 4 24 5 25 6 26 7 27 10 30 11 31 12 32 13 33 14 34 15 35 16 36 17 37" HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation_shared_private_asm_longer_mult 8 2>&1 | tee invalidation_shared_private_asm_longer_mult_8_log

mkdir invalidation_shared_private_jump_size_8_thread_32

mv *hpcrun invalidation_shared_private_jump_size_8_thread_32

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=32 GOMP_CPU_AFFINITY="0 20 1 21 2 22 3 23 4 24 5 25 6 26 7 27 10 30 11 31 12 32 13 33 14 34 15 35 16 36 17 37" HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation_shared_private_asm_longer_mult 16 2>&1 | tee invalidation_shared_private_asm_longer_mult_16_log

mkdir invalidation_shared_private_jump_size_16_thread_32

mv *hpcrun invalidation_shared_private_jump_size_16_thread_32

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=32 GOMP_CPU_AFFINITY="0 20 1 21 2 22 3 23 4 24 5 25 6 26 7 27 10 30 11 31 12 32 13 33 14 34 15 35 16 36 17 37" HPCRUN_WP_REUSE_BIN_SCHEME=1000000,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./invalidation_shared_private_asm_longer_mult 32 2>&1 | tee invalidation_shared_private_asm_longer_mult_32_log

mkdir invalidation_shared_private_jump_size_32_thread_32

mv *hpcrun invalidation_shared_private_jump_size_32_thread_32
