#!/bin/bash

#SBATCH --job-name=dot
#SBATCH --output=dot_%j.out
#SBATCH --error=dot_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:00:15
#SBATCH --exclusive

module load CUDA NVHPC

make || exit 1
nvprof --print-gpu-summary ./dot.x
