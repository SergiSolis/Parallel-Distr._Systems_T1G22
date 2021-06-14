#!/bin/bash

#SBATCH --job-name=cg_cpu
#SBATCH --output=cg_cpu_%j.out
#SBATCH --error=cg_cpu_%j.err
#SBATCH --cpus-per-task=1
#SBATCH --ntasks=1
#SBATCH --time=00:01:45
#SBATCH --exclusive

module load NVHPC

nvc -ta=host cg.c -o cpu_cg.x

module purge
module load PGI

pgprof --cpu-profiling-mode flat ./cpu_cg.x
