#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "graph.h"
#include "Graph.cpp"
using namespace std;
int main(int argc, char** argv)
{

	int i,n,m;
	ifstream file (argv[1]);
	string input;
	char firstLine[input.length()];
	char* tok;
	size_t pos;
	getline(file, input);
	for (i = 0; i < input.length();i++)
	{
		firstLine[i] = input[i];
	}
	tok = strtok(firstLine, " ");
	
	n = stoi(tok);
	tok = strtok(NULL, " ");
	m = stoi(tok);
	edge** adjList = new edge*[n];//adjacency list
	i = 0;
	
	while (getline(file, input))
	{
		edge* newGuy = new edge;
		char temp[25];
		strcpy(temp, input.c_str());
		tok = strtok(temp, " ");
		tok = strdup(tok);
		newGuy->edgeID = stoi(tok);
		tok = strtok(NULL, " ");
		tok = strdup(tok);
		newGuy->vertexU = stoi(tok);
		tok = strtok(NULL, " ");
		tok = strdup(tok);
		newGuy->vertexV = stoi(tok);
		tok = strtok(NULL, " ");
		tok = strdup(tok);
		newGuy->weight = stof(tok);
		if (strcmp(argv[2], "directed") == 0)
		{
			if (adjList[(newGuy->vertexU) - 1] == NULL)
			{
				adjList[(newGuy->vertexU) - 1] = newGuy;
			}
			else
			{
				edge* temp = adjList[(newGuy->vertexU) - 1];
				adjList[(newGuy->vertexU) - 1] = newGuy;
				newGuy->next = temp;
			}
		}
		else
		{
			edge* newGvy = new edge;
			newGvy->edgeID = newGuy->edgeID;
			newGvy->vertexU = newGuy->vertexU;
			newGvy->vertexV = newGuy->vertexV;
			newGvy->weight = newGuy->weight;
			if (adjList[(newGuy->vertexU) - 1] == NULL)
			{
				adjList[(newGuy->vertexU) - 1] = newGuy;
			}
			else
			{
				edge* temp = adjList[(newGuy->vertexU) - 1];
				adjList[(newGuy->vertexU) - 1] = newGuy;
				newGuy->next = temp;
			}
			if (adjList[(newGuy->vertexV) - 1] == NULL)
			{
				adjList[(newGuy->vertexV) - 1] = newGvy;
			}
			else
			{
				edge* temp = adjList[(newGuy->vertexV) - 1];
				adjList[(newGuy->vertexV) - 1] = newGvy;
				newGvy->next = temp;
			}
		}
		//	path test = dijkstra(adjList, 1, 2, 0, n);
			//cout << test.d << "\n" << test.pi << "\n" << test.v;

	}struct path test;
	string line;
	int source=0;
	int dest;
	int flag;
	int c;
	int* S = new int[n];
	int* D = new int[n];
	while (getline(cin, line))
	{
		if (line.find("find") != string::npos)
		{
			size_t pos = line.find(' ');
			size_t fin = line.find(' ', pos + 1);
			size_t low = line.find(' ', fin + 1);
			string temp = line.substr(pos + 1, fin - pos);
			string temp1 = line.substr(fin + 1, low - fin);
			string temp2 = line.substr(low + 1);
			source = stoi(temp);
			dest = stoi(temp1);
			flag = stoi(temp2);
			if (0 < source && source <= n && dest != source && floor(flag / 2) == 0)
			{
				test = dijkstra(adjList, source, dest, flag, n, S, c);
			}
			else
			{
				cout << "Error: invalid find query\n";
				test.d = -11;
			}

		}
		else if (line.find("write") != string::npos)
		{
			size_t pos = line.find(' ');
			size_t fin = line.find(' ', pos + 1);
			string temp = line.substr(pos + 1, fin - pos);
			string temp1 = line.substr(fin + 1);
			int s = stoi(temp);
			int d = stoi(temp1);
			if (test.d == -11)
			{
				cout << "Error: no path computation done\n";
			}
			else if (s == source && 0 < d && d <= n)
			{
				if (c == 0)
				{
					cout << "Shortest path: <";
					i = 0;
					while (S[i + 1] != -1)
					{
						cout << S[i] << ", ";
						i++;
					}
					cout << S[i] << ">\n" << "The path weight is: " << test.d<<"\n";
				}
				else
					cout << "Error: invalid source destination pair\n";

			}
		}
		else
			break;
		delete[] S;
		delete[] D;
	}
/*	for(i=0;i<n;i++)
                {

                        edge* temp=adjList[i];
                        while(temp!=NULL)
                        {
                        cout<<temp->edgeID<<"  "<<temp->vertexU<<"  "<<temp->vertexV<<"  "<<temp->weight<<"\n";
                        
                        temp=temp->next;
                        }cout<<"\n";
                }*/       
	for(i=0;i<n;i++)
                {
			
                        edge* temp=adjList[i];
                        while(temp!=NULL)
                        {	
                        adjList[i]=adjList[i]->next;
                        delete temp;
                        temp=adjList[i];
                        }
                }   

}
