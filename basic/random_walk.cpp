#include <iostream>
#include <cstdlib>
#include <time.h>
#include <mpi.h>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

typedef struct
{
	int location;
	int num_steps_left_in_walk;
} Walker;

void decompose_domain(int domain_size, int rank, int size, int *subdomain_start, int *subdomain_size)
{
	cout << "============= process " << rank << "===============" << endl;
	*subdomain_start = domain_size / size * rank;
	*subdomain_size = domain_size / size;
	if (rank == size - 1)
	{
		*subdomain_size += domain_size % size;
	}
	cout << "process " << rank << " subdomain_start = " << *subdomain_start << " subdomain_size = " << *subdomain_size << endl;
}

void initialize_walkers(int num_walkers_per_pro, int max_walk_size, int subdomain_start, int rank, vector<Walker> &incoming_walkers)
{
	Walker walker;

	for (int i = 0; i < num_walkers_per_pro; i++)
	{
		walker.location = subdomain_start;
		walker.num_steps_left_in_walk = (rand() / (float)RAND_MAX) * max_walk_size;
		cout << "walker location : " << walker.location << " left_steps : " << walker.num_steps_left_in_walk << endl;
		incoming_walkers.push_back(walker);
	}
	cout << endl;
}

void walk(Walker &walker, int subdomain_start, int subdomain_size, int domain_size, vector<Walker> &outgoing_walkers)
{
	while(walker.num_steps_left_in_walk > 0){
		if(walker.location == subdomain_start + subdomain_size){
			if(walker.location == domain_size){
				walker.location = 0;
			}
			outgoing_walkers.push_back(walker);
			break;
		}else{
			walker.num_steps_left_in_walk --;
			walker.location ++;
		}
	}
}

void send_outgoing_walkers(vector<Walker> &outgoing_walkers, int rank, int size)
{
	MPI_Send((void *)outgoing_walkers.data(), outgoing_walkers.size() * sizeof(Walker), MPI_BYTE, (rank + 1) % size, 0, MPI_COMM_WORLD);
	outgoing_walkers.clear();
}

void recv_incoming_walkers(vector<Walker> &incoming_walkers, int rank, int size)
{
	MPI_Status status;
	int incoming_rank = rank == 0 ? size - 1 : rank - 1;
	MPI_Probe(incoming_rank, 0, MPI_COMM_WORLD, &status);
	int incoming_walkers_size;
	MPI_Get_count(&status, MPI_BYTE, &incoming_walkers_size);
	incoming_walkers.resize(incoming_walkers_size / sizeof(Walker));
	MPI_Recv((void *)incoming_walkers.data(), incoming_walkers_size, MPI_BYTE, incoming_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}
int main()
{
	int domain_size = 20;
	int max_walk_size = 30;
	int num_walkers_per_pro = 5;

	int rank;
	int size;

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	cout << endl;

	srand(time(NULL) * rank);

	int subdomain_start;
	int subdomain_size;
	decompose_domain(domain_size, rank, size, &subdomain_start, &subdomain_size);

	vector<Walker> incoming_walkers;
	vector<Walker> outgoing_walkers;
	initialize_walkers(num_walkers_per_pro, max_walk_size, subdomain_start, rank, incoming_walkers);
	

	int maximum_sends_recvs = max_walk_size / (domain_size / size) + 1;
	

	for (int i = 0; i < maximum_sends_recvs; i++)
	{
		for(int j = 0; j < incoming_walkers.size(); j++){
			walk(incoming_walkers[j], subdomain_start, subdomain_size, domain_size, outgoing_walkers);
		}

		cout << "Process " << rank << " sending " << outgoing_walkers.size() << " outgoing walkers to process " << (rank + 1) % size << endl;
		if(rank % 2 == 0){
			send_outgoing_walkers(outgoing_walkers, rank, size);
			recv_incoming_walkers(incoming_walkers, rank, size);

		} else {
			recv_incoming_walkers(incoming_walkers, rank, size);
			send_outgoing_walkers(outgoing_walkers, rank, size);
		}
		cout << "Process " << rank << " sending " << outgoing_walkers.size() << " outgoing walkers to process " << (rank + 1) % size << endl;
	}
 


	MPI_Finalize();
	return 0;
}