#ifndef GRAPHM_H
#define GRAPHM_H
#define MAXNODES 101
#include "nodedata.h"
#include <iomanip>
#include <vector>
#include <climits>
#include <stack>
#include <sstream>
using namespace std;

struct TableType
{
	bool visited;
	int dist;
	int path;
};

class GraphM
{

private:
	NodeData data[MAXNODES];			//The Names of the Nodes
	int C[MAXNODES][MAXNODES];			//Adjacency Matrix
	int size;							//The Amount of Nodes in the graph
	TableType T[MAXNODES][MAXNODES];	//The Visited, Distance, and path for each pair of nodes
	vector< vector<int> > paths;

	//Utility Function that zeros out both matrices
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

	//Utility function that resets all visited attributes back to false 
	void clearVisited()
	{
		for (int i = 1; i <= size; i++)
		{
			for (int j = 1; j <= size; j++)
			{
				T[i][j].visited = false;
			}
		}
	}

	//Utility function that finds and returns the index of the closest vertex 
	int findClosestVertix(int source)
	{
		int closest_vertex = 0;			//Initialize variable to track closest vertex (w) to source
		int min_distance = INT_MAX;		//Initialize min_distance to max value so that any distance will be assigned to
										// the min_distance in the loop below

		//Loop starts at the 1 column and iterates over the row of the Adjacency Matrix 
		for (int i = 1; i <= size; i++)
		{
			//If the Weight to the adjacent Vertix is not zero, The visited attribute is false, and the weight to the adjacent vertex
			//is less then the current minimum distance
			if (C[source][i] != 0 && T[source][i].visited == false && C[source][i] < min_distance)
			{
				min_distance = C[source][i];		//Record the Cost at the current (source, index) in the min_distance
				closest_vertex = i;					//Record the Index that has the smallest distance
			}
		}
		return closest_vertex;						//Return the index of the closest vertex to the source
	}

	//Utility function that displays shortest path from a given source to a given destination
	void displayPath(int source, int destination, bool displayNames)
	{
		vector<int> currentpath = paths.at(source);		//create a vector of ints that is named current path
														// 
		//int index = destination;		
		
		stack<int> path;					//Initializing stack of ints store the index and order of Nodes
		stack<NodeData> locationNames;		//Initializing a stack of NodeData items that contain the Names

		//If the distance between source and destination equals infinity
		if (T[source][destination].dist == INT_MAX)
		{
			//Do nothing and return
			cout << endl;
			return;
		}

		//While the destination does not equal the source
		while (destination != source)
		{
			path.push(destination);						//Add the destination to the path vector
			locationNames.push(data[destination - 1]);	//Add the destination name to the vector
			destination = currentpath.at(destination);	//Assign the index value at the destination index of current path to the destination
		}

		path.push(source);						//Push the source index to the path
		locationNames.push(data[source - 1]);	//Push the Name to the vector

		//While the Path is not empty
		while (!path.empty())		
		{
			int Vertex = path.top();	//Assign top index value to the Vertex
			cout << Vertex << " ";		//Print the Vertex
			path.pop();					//Delete the Vertex from the vector
		}
		cout << endl;					//Formatting

		if (displayNames)	//If displayingNames is true
		{
			while (!locationNames.empty())	//While the locationNames vector is not empty
			{
				NodeData name = locationNames.top();	//Assign top Name to the NodeData
				cout << name << endl << endl;			//Print the name
				locationNames.pop();					//Delete the name from the locationNames vector
			}
		}
	}

public:

	GraphM()
	{
		for (int i = 0; i < MAXNODES; i++)
		{
			for (int j = 0; j < MAXNODES; j++)
			{
				C[i][j] = 0;
				T[i][j] = { false, INT_MAX, 0 };
			}
		}


		for(int i = 0; i <= MAXNODES; i++)
		{
			vector<int> temp;
			paths.push_back(temp);
		}
	}

	void buildGraph(ifstream& file)
	{

		file >> size;		//The in file stream stores the first
							//line of the file into the size variable
							
		string str;			//Create a temp string variable to store strings
							//as the come out of the file
							
		getline(file, str);	//pulls lines out of file and assigns
									//them to the str variable

		//Loop to initialize the data fields of the NodeData
		for (int i = 0; i < size; i++)
		{
			data[i].setData(file);	//Calls the setData method on the DataNode
										//object and takes the instream reference of the
										//line of file and assigns it to the DataNodes
										//data attribute
		}
		
		zeroOut();	//Clears out the both adjacency array and the informational
					//array in between each graph

		paths.clear();						//Clears the Path Vector attribute for each graph analysis
		paths.resize(size + 1);		//Resizes the array

		//Loop to pushes "size + 1" number of of ints into the paths vector 
		for (int i = 0; i <= size; i++)
		{
			paths.at(i).push_back(1);
		}
		getline(file, str);			//Grabs the line of source, destination, and weight information

		int source, destination, cost;		//Creating global variables
		
		stringstream ss(str);				//Constructs a stringstream object with a copy of str as content
		ss >> source >> destination;		//inputs source and destination information into variables

		
		//If the ss object is empty, assign a cost of 1 to the weight
		if (ss.str().empty())		
		{
			cost = 1;
		}
		//else, assign the weight to the cost
		else						
		{
			ss >> cost;
		}


		//While the text file does not have 3 consecutive 0 input do this
		while (source != 0 && destination != 0 && cost != 0)
		{
			
			C[source][destination] = cost;		//Assign the weight to the adjacency matrix

			getline(file, str);			//Get the next line from the file and store it in the str variable

			stringstream ss(str);				//Constructs a stringstream object with a copy of str as content

			ss >> source >> destination;		//Output the stringstream to the source and destination

			//If the ss object is empty, assign a cost of 1 to the weight
			if (ss.str().empty())
			{
				cost = 1;
			}
			//else, assign the weight to the cost
			else
			{
				ss >> cost;
			}
		}
	}

	void findShortestPath()
	{
		//Loop that controls and iterates through the source rows
		for (int source = 1; source <= size; source++) {

			vector<int> current_pred(size + 1);		//Initialize a vector of ints that stores the order of current predecessor nodes

			clearVisited();					//Reset all Visited attributes to false
			bool firstTime = true;			//Setting a flag to control the if-else statement on line 228
			T[source][source].dist = 0;		//Setting the source vertex distance at 0
			
			// finds the shortest distance from source to all other nodes
			for (int i = 1; i <= size; i++) {

				int v = 0;					//Initializing the source vertex to 0

				//This basically for the first time visits itself first to set the distance from the source to source is zero
				if (firstTime)				
				{
					v = source;			//Update v as the current source
					firstTime = false;	//Trip the firstTime flag to execute else statement next time and find the closest vertex distance
				}
				//If it is not the first time visiting this vertex search the other adjacent vertexes and find the closest
				else
				{
					v = findClosestVertix(source);	//Using the current source, find and return the closest_Vertix that has
													//	not been visited. This will be the shortest distance at this point
				}

				T[source][v].visited = true;		//Mark closest vertex as visited

				//Loop that inspects all adjacent Vertexes to the closest vertex
				for (int w = 1; w <= size; w++)		//for each w adjacent to v
				{
					//If the Adjacent vertex has a positive weight value (has an edge) and the node has not been visited 
					if (C[v][w] > 0 && T[v][w].visited == false)
					{
						//If the adjacent nodes distance is greater then the sources closest adjacent vertex 
						if (T[source][w].dist > T[source][v].dist + C[v][w])
						{
							current_pred.at(w) = v;		//add the closest vertex to the predecessor vector at the appropriate location
						}
						
						T[source][w].dist = min(T[source][w].dist, T[source][v].dist + C[v][w]);	//Assign the minimum distance to the Table
																											//at the location of the sources adjacent vertex
					}
				}
			}
			paths.at(source) = current_pred;		//add the found predecessor to the paths vector
		}
	}

	void displayAll()
	{
		//Formatting to print out the column headers
		cout << left << setw(20) << "Description" << left << setw(12) << "From node" << 
				left << setw(10) << "To node" << left << setw(15) << "Dijkstra's" << 
				left << setw(10) << "Path" << endl;

		//Loop iterates through the matrix rows
		for(int i = 1; i <= size; i++)
		{
			cout << data[i-1] << endl << endl;		//Print out the data fields

			//Loop that iterates through the matrix columns 
			for(int j = 1; j <= size; j++)			
			{
				//If the loop is not looking at the same node
				if(j != i)
				{
					//output the "from node" and the "To node" and....
					cout << setw(24) << " " << left << setw(10) << i << left << setw(7) << j;

					//If the distance is anything other then INT_MAX
					if(T[i][j].dist < INT_MAX)
					{
						cout << right << setw(4) << T[i][j].dist;	//output the total distance	
					}
					//If the distance equal to INT_MAX
					else
					{
						cout << "----" << " ";	//Output that there is not path to this node
					}

					cout << setw(12) << " ";
					displayPath(i, j, false);		//Display the shortest path
				}
			}
		}
	}

	//Function that displays what it the shortest distance between 2 given nodes
	void display(int source, int destination)
	{
		cout << endl;			//Formatting
		int i = source;			//Creating the source
		int j = destination;	//Creating the Destination

		//If the destination is not the same as the source
		if (j != i)
		{
			
			cout << setw(5) << i << setw(10) << j << setw(10);

			//It there any other distance than "infinity"
			if (T[i][j].dist < INT_MAX)
			{
				cout << T[i][j].dist << " ";	//Print the distance
			}
			//If the distance is "infinity"
			else
			{
				cout << "----" << " ";			//Print 4 dashes
			}
			cout << setw(12) << " ";

			displayPath(i, j, true);			//Display optimal path
		}
	}
	
};
#endif
