#!/bin/bash
#SBATCH -q regular
#SBATCH --time 01:00:00
#SBATCH --ntasks-per-node=1
#SBATCH -A m2616
#SBATCH -C cpu
#SBATCH -N 40

EVENTS_PER_CORE=10
# 2 hyperthreads per core
NCORES=$((${SLURM_CPUS_ON_NODE} / 2))
NEVENTS_PER_NODE=$((${EVENTS_PER_CORE} * ${NCORES}))

cd /global/homes/e/esseivaj/devel/HPXDistributed/build-5algs
OUTPUT_DIR=/global/homes/e/esseivaj/devel/HPXDistributed/strong_scaling-numa_sensitive-${NCORES}cores-5algs-$SLURM_JOBID

mkdir $OUTPUT_DIR

# do cache warm-up
for i in {2..6}; do
    srun HPXDistributed $((${NEVENTS_PER_NODE} * ${SLURM_NNODES}))
done

NEVENTS=51200
for i in {40..2}; do
    srun -n${i} -N${i} -c ${NCORES} --cpu-bind=sockets HPXDistributed ${NEVENTS} -Ihpx.stacks.use_guard_pages=0 --hpx:numa_sensitive=1 --hpx:print-counter-destination=$OUTPUT_DIR/perf_counters_$i --hpx:print-counter=/threads{locality#*/total}/idle-rate > $OUTPUT_DIR/${i}_nodes_${NEVENTS}_events
done
