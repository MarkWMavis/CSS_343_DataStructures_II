#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include "nodedata.h"

class Node {
private:
	NodeData* nodeData;
	Node* LeftNode;
	Node* RightNode;
	friend class BinTree;
public:
	Node();
	Node(NodeData* val);
	NodeData* getNodeData() const;
};
class BinTree {
private:
	Node* root = nullptr;
	Node* _InsertNode(Node* root, NodeData* nodedata);
	void _InOrderTraversal(Node* root, ostream& os);
	void _PostOrderTraversal(Node* root);
	void _PreOrderTraversal(Node* root);
	
public:
	BinTree();
	BinTree(BinTree& tree);
	
	void InsertNode( NodeData* nodedata);
	void PreOrderTraversal();
	void InOrderTraversal();
	void PostOrderTraversal();

	bool retrieve(const NodeData& nodeData, NodeData*& nodeDataRef) const;
	Node* retrieveDataHelper(const NodeData& nodeData) const;
	int HightHelper(Node* node) const;
	int getHeight(const NodeData& dataNode) ;
	
	void clearTree(Node* node);
	void clear();
	void bstreeToArrayHelper(Node* node, NodeData* arr[]);
	void bstreeToArray(NodeData*[]);
	void arrayToBSTreeHelper(int first, int last, int index, NodeData* arr[]);
	void arrayToBSTree(NodeData*[]);
	void bstreePreToArrayHelper(Node* root, NodeData* arr[]);
	bool equalsHelper(const Node* leftnode, const Node* rightnode) const;
	bool operator==(const BinTree& rightHandSide) const;

	bool notequalsHelper(const Node* leftnode, const Node* rightnode) const;
	bool operator!=(const BinTree& rightHandSide) const;

BinTree& operator=(const BinTree& rightHandSide);	
	friend ostream& operator<<(ostream& outputStream, BinTree& outputList);

};

#endif
