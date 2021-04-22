#include "graph.h"
#include "heap.cpp"
#include <iostream>
#include <iomanip>
void relax(path**& pathHeap, int*&S, int vertex, float weight, int n, int flag)
{
	int found = 0;//finds the node in the path heap
	int found1 = 0;//finds the node in the set S
	int j = 1;
	int i = 0;
	while (S[i] != -1 && i < n&&found1==0)//makes sure the node has not already been calculated
	{
		if (vertex == S[i])
		{
			found1 = 1;
		}
		i++;
	}
	if(found1==0)
	{
		while (pathHeap[j] != NULL && found == 0 && j < n)//finds and relaxes the vertex in the path heap
		{

			if (pathHeap[j]->v == vertex)
			{
				found = 1;
			}
			else
				j++;
		}
		if (found == 1 && j < n)//when vertex is found in the heap, use the relax algorithm p.649
		{
			if (pathHeap[j]->d > pathHeap[0]->d + weight)
			{	
				if (flag == 1)
				{
					std::cout << std::fixed
						<< std::setprecision(4);
					std::cout << "Decrease key of vertex " << vertex << ", from" << std::setw(12) << pathHeap[j]->d<<" to "<< pathHeap[0]->d + weight<<"\n";
				}
				pathHeap[j]->pi = pathHeap[0]->v;
				pathHeap[j]->d = pathHeap[0]->d + weight;
				
			}
		}
		else if (j < n)//when vertex is not found in the heap, initialize the vertex at the bottom of the heap
		{
			pathHeap[j] = new struct path;
			pathHeap[j]->pi = pathHeap[0]->v;
			pathHeap[j]->v = vertex;
			pathHeap[j]->d = pathHeap[0]->d + weight;
			if (flag == 1)
			{
				std::cout << std::fixed             
					<< std::setprecision(4);
				std::cout << "Insert vertex " << vertex << ", key=" << std::setw(12) << pathHeap[j]->d<<"\n";
			}
		}
	}

}
path dijkstra(edge** edges, int source, int dest, int flag, int n, int*& S, int& c)
{
	struct path** pathHeap = new path * [n];
	pathHeap[0] = new struct path;
	pathHeap[0]->d = 0;
	pathHeap[0]->pi = 0;
	pathHeap[0]->v = source;
	S[0] = source;
	int i = 1, k = 0, j = 0;
	for (i = 1; i < n; i++)
	{
		S[i] = -1;
		pathHeap[i] = NULL;
	}
	int found = 0;
	i = 0;
	while (pathHeap[0] != NULL)
	{
		S[i] = pathHeap[0]->v;
		i++;
		if (pathHeap[0]->v != dest)
		{

			edge* temp = edges[S[i - 1] - 1];
			while (temp != NULL && found == 0)
			{
				if (temp->vertexU == pathHeap[0]->v)//add vertexV to the pathHeap
				{
					relax(pathHeap, S, temp->vertexV, temp->weight, n, flag);

				}
				else//add vertexU to the pathHeap
				{
					relax(pathHeap, S, temp->vertexV, temp->weight, n, flag);
				}
				temp = temp->next;

			}
		}
		else
		{
			c = 0;
			break;
		}

		if (flag == 1)
		{
			std::cout << std::fixed
				<< std::setprecision(4);
			std::cout << "Delete vertex " << pathHeap[0]->v << ", key=" << std::setw(12) << pathHeap[0]->d << "\n";
		}
		delete pathHeap[0];
		pathHeap[0] = NULL;
		k = 1;
		while (pathHeap[k] != NULL)
		{
			k++;
		}
		pathHeap[0] = pathHeap[k - 1];
		pathHeap[k - 1] = NULL;
		buildMinHeap(pathHeap, k - 1);
	}
	path foundPath;
	if (pathHeap[0] != NULL)
	{
		foundPath.d = pathHeap[0]->d;
		foundPath.pi = pathHeap[0]->pi;
		foundPath.v = pathHeap[0]->v;
		while (pathHeap[i] != NULL)
		{
			delete pathHeap[i];
		}
	}
	else
		c = 1;
	delete[] pathHeap;
	return foundPath;


}
