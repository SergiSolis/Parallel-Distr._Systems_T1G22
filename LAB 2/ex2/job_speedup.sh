#!/bin/bash

#SBATCH --job-name=ex2_speedup
#SBATCH --output=ex2_speedup_%j.out
#SBATCH --error=ex2_speedup_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:00:05

module load Python numpy matplotlib

python3 speedup.py
