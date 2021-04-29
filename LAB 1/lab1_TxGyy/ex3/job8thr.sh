#!/bin/bash

#SBATCH --job-name=ex3_8thr
#SBATCH --output=ex3_8thr_%j.out
#SBATCH --error=ex3_8thr_%j.err
#SBATCH --cpus-per-task=8
#SBATCH --ntasks=1
#SBATCH --time=00:00:05
#SBATCH --exclusive

module load GCC/8.3.0

make || exit 1      # Exit if compilation fails

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
./mandelbrot

/shared/2021-24301-angles/ImageMagick-7.0.11/utilities/magick convert mandelbrot.ppm mandelbrot.png