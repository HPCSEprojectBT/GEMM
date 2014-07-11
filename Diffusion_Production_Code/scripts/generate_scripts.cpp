#include <iostream>
#include <math.h>
#include <fstream>


using namespace std;

char filename[160];
ofstream out;

int main (int argc, char** argv)
{
	for (int i=1; i<=256; ++i) {
		// Weak scaling, blocking
		sprintf(filename,"batch_ws_%d.txt",i);
		out.open(filename);
		out << "#!/bin/bash -l\n";
		out << "#SBATCH --job-name=\"weak_scaling_diffusion 1\"\n"; 
		out << "#SBATCH --nodes=" << i << endl;
		out << "#SBATCH --ntasks=" << i << endl;
		out << "#SBATCH --cpus-per-task=16\n";
		out << "#SBATCH --ntasks-per-node=1\n";
		out << "#SBATCH --time=05:00:00\n\n";
		out << "#======START===============================\n"; 
		out << "echo \"On which nodes it executes\"\n";
		out << "echo $SLURM_JOB_NODELIST\n"; 
		out << "echo \"Now run the MPI tasks...\"\n"; 
		out << "aprun -B ../timing.out " << i*5040 << " " << 100 << " " << 10 << " " << 16 << " 0 " << i <<endl;
		out << "#======END=================================\n";
		out.close();				
	}
	
}
