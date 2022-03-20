#ifndef GRAPHL_H
#define GRAPHL_H
#define MAXNODES 101
#include "nodedata.h"
#include <iomanip>
#include <vector>
#include <climits>
#include <sstream>
using namespace std;

class GraphL
{
	struct TableType
	{
		bool visited;
		int dist;
		int path;
	};
	
private:
	NodeData data[MAXNODES];			//The Names of the Nodes
	int C[MAXNODES][MAXNODES];			//Adjacency Matrix
	int size;							//The Amount of Nodes in the graph
	TableType T[MAXNODES][MAXNODES];	//The Visited, Distance, and path for each pair of nodes
	vector<int> path;

	//Utility function to zero out both matrices
	void zeroOut()
	{
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j <= size; j++)
			{
				T[i][j].visited = false;
				T[i][j].dist = INT_MAX;
				T[i][j].path = 0;
				C[i][j] = 0;
			}
		}
	}

	//Recursive Utility function to find the shortest path using a greedy approach 
	void depthFirstSearchUtil(int source)
	{
		T[source][source].visited = true;		//Mark the source as visited

		path.push_back(source);					//Record the source as the first in in the path

		for (int i = 1; i <= size; i++)			
		{
			if (C[source][i] == 1 && T[i][i].visited == false)		// if the next nodes have an edge with the 														
			{														// source and the next node hasn't be visited
				depthFirstSearchUtil(i);	//Find the next closest node
			}
		}
	}
	
public:

	//Default Constructor
	GraphL()
	{
		for (int i = 0; i < MAXNODES; i++)
		{
			for (int j = 0; j < MAXNODES; j++)
			{
				//Initializes all visited to false, distance = INT_MAX, and path = 0;
				C[i][j] = 0;
				T[i][j] = { false, INT_MAX, 0 };
			}
		}
	}

	void buildGraph(ifstream& file)
	{
		file >> size;	//Assigns the first value to the size variable

		string str;		//Creating string variable to store string values as they come from the instream file
		getline(file, str);		//Getline pulls the second line and stores it int the str variable
	
		//zeroOut();		//Zeros out both matrices

		//Loop to pull "size" number of lines and assign the destination names to the data array at index i
		for (int i = 0; i < size; i++)
		{
			data[i].setData(file);	//Going to pull 5 lines and 
		}

		//Pull the next line from file and store in str
		getline(file, str);

		//Create global variables for source and destination
		int source, destination;

		stringstream ss(str);
		ss >> source >> destination;
		
		while (source != 0 && destination != 0)
		{
			C[source][destination] = 1;
			getline(file, str);
			stringstream ss(str);
			ss >> source >> destination;
		}
	}

	void depthFirstSearch()
	{
		//Build the Matrix
		for(int i = 1; i <= size; i++)
		{
			for(int j = 1; j <= size; j++)
			{
				T[i][j].visited = false;
				T[i][j].dist = INT_MAX;
				T[i][j].path = 0;
			}
		}
		
		depthFirstSearchUtil(1);		//Begin depth first search starting at the source

		cout << endl;
		cout << "Depth-first ordering: ";

		//Print the entire path until your arrive at the destination
		for(int i = 0; i < path.size(); i++)
		{
			cout << path.at(i) << " ";
		}
		cout << endl;
	}
	
	void displayGraph()
	{
		cout << endl;
		cout << "Graph: " << endl;
		
		for (int i = 1; i <= size; i++)
		{
			//Prints the Node and its name
			cout << "Node" << i << "          " << data[i - 1] << endl << endl;

			for (int j = 1; j <= size; j++)
			{
				//Print out all of the edges
				if(C[i][j] != 0)
				{
					cout << right << setw(6) << "edge" << right << setw(4) << i  << right << setw(3) << j << endl;
				}
			}
		}
	}
};




#endif
