#!/bin/bash

#SBATCH --job-name=ex2_8thr
#SBATCH --output=ex2_8thr_%j.out
#SBATCH --error=ex2_8thr_%j.err
#SBATCH --cpus-per-task=8
#SBATCH --ntasks=1
#SBATCH --time=00:00:05
#SBATCH --exclusive

module load GCC/8.3.0

make $SLURM_CPUS_PER_TASK || exit 1      # Exit if compilation fails

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./montecarlo