#! /bin/bash

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=1 GOMP_CPU_AFFINITY="0" HPCRUN_WP_REUSE_BIN_SCHEME=130,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./short_rd/multithread_five_rd_inc 2>&1 | tee multithread_five_rd_inc_log

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=1 GOMP_CPU_AFFINITY="0" HPCRUN_WP_REUSE_BIN_SCHEME=130,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./short_rd/multithread_five_rd_dec 2>&1 | tee multithread_five_rd_dec_log

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=1 GOMP_CPU_AFFINITY="0" HPCRUN_WP_REUSE_BIN_SCHEME=130,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./short_rd/multithread_five_rd_bell 2>&1 | tee multithread_five_rd_bell_log

HPCRUN_WP_REUSE_PROFILE_TYPE="TEMPORAL" HPCRUN_PROFILE_L3=false OMP_NUM_THREADS=1 GOMP_CPU_AFFINITY="0" HPCRUN_WP_REUSE_BIN_SCHEME=130,2 HPCRUN_WP_DONT_FIX_IP=true HPCRUN_WP_DONT_DISASSEMBLE_TRIGGER_ADDRESS=true /usr/bin/time -f "Elapsed Time , %e, system, %S, user, %U, memory, %M" /home/msasongko17/reusetracker/hpctoolkit-bin/bin/hpcrun -e WP_REUSETRACKER -e MEM_UOPS_RETIRED:ALL_LOADS@100000 -e MEM_UOPS_RETIRED:ALL_STORES@100000 ./short_rd/multithread_five_rd_multi_mod 2>&1 | tee multithread_five_rd_multi_mod_log