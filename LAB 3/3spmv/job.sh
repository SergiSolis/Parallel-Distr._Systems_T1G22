#!/bin/bash

#SBATCH --job-name=spmv
#SBATCH --output=spmv_%j.out
#SBATCH --error=spmv_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:00:35
#SBATCH --exclusive

module load NVHPC

make || exit 1
./spmv.x
