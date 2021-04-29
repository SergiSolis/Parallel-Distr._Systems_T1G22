#!/bin/bash

#SBATCH --job-name=ex2_4thr
#SBATCH --output=ex2_4thr_%j.out
#SBATCH --error=ex2_4thr_%j.err
#SBATCH --cpus-per-task=4
#SBATCH --ntasks=1
#SBATCH --time=00:00:05
#SBATCH --exclusive

module load GCC/8.3.0

make $SLURM_CPUS_PER_TASK || exit 1      # Exit if compilation fails

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./montecarlo