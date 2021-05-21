#!/bin/bash
  
#SBATCH --job-name=ex3
#SBATCH --output=ex3_8pr_%j.out
#SBATCH --error=ex3_8pr_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=8
#SBATCH --time=00:00:15

module load GCC/8.3.0

make || exit 1      # Exit if make fails
mpirun ./count
