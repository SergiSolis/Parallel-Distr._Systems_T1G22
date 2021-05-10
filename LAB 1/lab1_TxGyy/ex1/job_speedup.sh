#!/bin/bash

#SBATCH --job-name=ex4_speedup
#SBATCH --output=ex4_speedup_%j.out
#SBATCH --error=ex4_speedup_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:00:05

module load Python numpy matplotlib

python3 speedup.py