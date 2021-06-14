#!/bin/bash

#SBATCH --job-name=cuspmv
#SBATCH --output=cuspmv_%j.out
#SBATCH --error=cuspmv_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:00:15

module load CUDA

make || exit 1
./spmv.x
