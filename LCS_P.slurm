#!/bin/bash
#SBATCH --job-name=LCS_P
#SBATCH --output slurm.out
#SBATCH --error slurm.err
#SBATCH --partition=batch
#SBATCH --qos=short
#SBATCH --constraint=hpcf2013
#SBATCH --exclusive
#SBATCH --cpus-per-task=16
#SBATCH --ntasks=1

export KMP_AFFINITY="verbose,compact"

export OMP_NUM_THREADS=1
srun ./LCS_P text1.txt text2.txt

export OMP_NUM_THREADS=2
srun ./LCS_P text1.txt text2.txt

export OMP_NUM_THREADS=4
srun ./LCS_P text1.txt text2.txt

export OMP_NUM_THREADS=8
srun ./LCS_P text1.txt text2.txt

export OMP_NUM_THREADS=16
srun ./LCS_P text1.txt text2.txt