#!/bin/bash

#SBATCH --job-name=ex1_1thr
#SBATCH --output=ex1_1thr_%j.out
#SBATCH --error=ex1_1thr_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:00:05
#SBATCH --exclusive

module load GCC/8.3.0

make || exit 1      # Exit if compilation fails

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

./axpby 100000000