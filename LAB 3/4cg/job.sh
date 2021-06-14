#!/bin/bash

#SBATCH --job-name=cg
#SBATCH --output=cg_%j.out
#SBATCH --error=cg_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:01:35
#SBATCH --exclusive

module load NVHPC

make || exit 1
./cg.x

