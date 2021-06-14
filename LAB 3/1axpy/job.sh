#!/bin/bash

#SBATCH --job-name=axpy
#SBATCH --output=axpy_%j.out
#SBATCH --error=axpy_%j.err
#SBATCH --cpus-per-task=4
#SBATCH --ntasks=1
#SBATCH --time=00:00:15
#SBATCH --exclusive

module load NVHPC

make || exit 1

./axpy.x
