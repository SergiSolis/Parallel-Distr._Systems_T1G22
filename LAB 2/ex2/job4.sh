#!/bin/bash
  
#SBATCH --job-name=ex2
#SBATCH --output=ex2_4pr_%j.out
#SBATCH --error=ex2_4pr_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=4
#SBATCH --time=00:00:15

module load GCC/8.3.0

make || exit 1      # Exit if make fails
mpirun ./pi 100000000

