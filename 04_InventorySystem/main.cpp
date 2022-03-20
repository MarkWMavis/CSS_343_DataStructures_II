#include "inventory.h"
#include <fstream>
using namespace std;


int main()
{
	
	//-------Opening and importing movies into the moveFile Object------------
	ifstream movieFile("data4movies.txt");
	if(!movieFile.is_open())
	{
		cout << "File did not open";
		return 0;
	}
	//-------Opening and importing movies into the moveFile Object------------
	ifstream customerFile("data4customers.txt");
	if (!customerFile.is_open())
	{
		cout << "File did not open";
		return 0;
	}
	//-------Opening and importing movies into the moveFile Object------------
	ifstream commands("data4commands.txt");
	if (!commands.is_open())
	{
		cout << "File did not open";
		return 0;
	}

	
	inventory db;												//Creating the inventory
	db.buildInventory(movieFile, customerFile);			//Building the inventory
	db.processCommands(commands);								//Processing the commands

	movieFile.close();											//Closing the movie Object file
	customerFile.close();										//Closing the customer object file
	commands.close();											//Closing the commands object file
	return 0;
}