#!/bin/bash

#SBATCH --job-name=cg
#SBATCH --output=cg_%j.out
#SBATCH --error=cg_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:00:45
#SBATCH --exclusive

module load CUDA NVHPC

make || exit 1
nvprof --print-gpu-summary ./cg.x

