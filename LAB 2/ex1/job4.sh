#!/bin/bash
  
#SBATCH --job-name=ex1
#SBATCH --output=ex1_%j.out
#SBATCH --error=ex1_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=4
#SBATCH --time=00:00:15

module load GCC/8.3.0

make || exit 1      # Exit if make fails
mpirun ./matrix

