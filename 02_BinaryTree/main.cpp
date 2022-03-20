#include <fstream>
#include "BinaryTree.h"
#include <iomanip>

int main() {

	ifstream data("data2.txt");
	if(!data.is_open())
	{
		cout << "Could not open file" << endl;
		return -1;
	}

	BinTree newTree;
	string word;

	while(data>>word)
	{
		if(word != "$$")
		{
			NodeData* p = new NodeData(word);
			newTree.InsertNode(p);
		}else
		{
			newTree.PostOrderTraversal();
			newTree.clear();
		}
	}
	
	return 0;
}
