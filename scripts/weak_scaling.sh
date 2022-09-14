#!/bin/bash
#SBATCH -q regular
#SBATCH --time 01:00:00
#SBATCH --ntasks-per-node=1
#SBATCH -A m2616
#SBATCH -C cpu
#SBATCH -N 40

DBG=$1

cd /global/homes/e/esseivaj/devel/HPXDistributed/build
OUTPUT_DIR=/global/homes/e/esseivaj/devel/HPXDistributed/weak_scaling-$SLURM_JOBID

mkdir $OUTPUT_DIR

EVENTS_PER_CORE=10
# 2 hyperthreads per core
NCORES=$((${SLURM_CPUS_ON_NODE} / 2))
NEVENTS_PER_NODE=$((${EVENTS_PER_CORE} * ${NCORES}))

# do cache warm-up
for i in {2..6}; do
    srun HPXDistributed $((${NEVENTS_PER_NODE} * ${SLURM_NNODES}))
done

for i in {40..2}; do
    NEVENTS=$(((${i} - 1) * ${NEVENTS_PER_NODE}))
    srun -n${i} -N${i} HPXDistributed ${NEVENTS} --hpx:threads ${NCORES} -Ihpx.stacks.use_guard_pages=0 > $OUTPUT_DIR/${i}_nodes_${NEVENTS}_events
done
