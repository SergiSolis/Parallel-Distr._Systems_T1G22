#!/bin/bash

#SBATCH --job-name=dot
#SBATCH --output=dot_%j.out
#SBATCH --error=dot_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:00:25
#SBATCH --exclusive

module load NVHPC

make || exit 1
./dot.x
