#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP
#include"binaryTree.h"
#include"nodedata.h"

Node::Node() {
	nodeData = nullptr;
	LeftNode = nullptr;
	RightNode = nullptr;
}
Node::Node(NodeData* val) {
	nodeData = val;
	LeftNode = nullptr;
	RightNode = nullptr;
}
NodeData* Node::getNodeData() const {
	return nodeData;
}


BinTree::BinTree() {
	this->root = nullptr;	
}
BinTree::BinTree(BinTree& tree)
{
	this->root = nullptr;
	NodeData* arr[100] = {NULL};
	bstreePreToArrayHelper(tree.root, arr);
	arrayToBSTree(arr);

}
Node* BinTree::_InsertNode(Node* root, NodeData* nodeData) {
	/* If the tree is empty, return a new node */
	if (root == nullptr) {
		return new Node(nodeData);
	}
	/* Otherwise, recur down the tree */
	if (*nodeData < *(root->nodeData))
		root->LeftNode = _InsertNode(root->LeftNode, nodeData);
	else if (*nodeData > *(root->nodeData))
		root->RightNode = _InsertNode(root->RightNode, nodeData);

	/* return the (unchanged) node pointer */
	return root;
	
}
void BinTree::InsertNode(NodeData* nodedata) {
	root = _InsertNode(root, nodedata);
}
void BinTree::_InOrderTraversal(Node* root, ostream& os) {
	if (root == nullptr) {
		return;
	}
	else {
		_InOrderTraversal(root->LeftNode, cout);
		cout << root->nodeData->getData() << " ";
		_InOrderTraversal(root->RightNode, cout);
	}
}
void BinTree::InOrderTraversal() {
	_InOrderTraversal(root, cout);
	cout << endl;
}
void BinTree::_PostOrderTraversal(Node* root) {
	if (root == nullptr) {
		return;
	}
	else {
		_PostOrderTraversal(root->LeftNode);
		_PostOrderTraversal(root->RightNode);
		cout << root->nodeData->getData() << " ";
	}
}
void BinTree::PostOrderTraversal() {
	_PostOrderTraversal(root);
	cout << endl;
}
void BinTree::_PreOrderTraversal(Node* root) {
	if (root == nullptr) {
		return;
	}
	else {
		cout << root->nodeData->getData() << " ";
		_PreOrderTraversal(root->LeftNode);
		_PreOrderTraversal(root->RightNode);
		
	}
}
void BinTree::PreOrderTraversal() {
	_PreOrderTraversal(root);
	cout << endl;
}
bool BinTree::retrieve(const NodeData& nodeData, NodeData*& nodeDataRef) const {

	/*
	 *	Creates a new Node pointer and uses the retrieveDataHelper to pass the reference (address) of the NodeData
	 *	
	*/
	Node* retrievedNode = retrieveDataHelper(nodeData);

	
	if (retrievedNode == nullptr) {
		return false;
	}
	else {
		nodeDataRef = retrievedNode->nodeData;
		return true;
	}
}
Node* BinTree::retrieveDataHelper(const NodeData& nodeData) const {
	Node* currentNode = root;
	while (currentNode != nullptr && nodeData != (*(currentNode->nodeData))) {
		if (nodeData < *(currentNode->nodeData)) {
			currentNode = currentNode->LeftNode;
		}
		else {
			currentNode = currentNode->RightNode;
		}
	}

	if (currentNode == nullptr) {
		return nullptr;
	}
	else {
		return currentNode;
	}
}
int BinTree::HightHelper(Node* node) const {
	//Base Case
	//If the node == nullptr, the tree is empty for return height 0
	if (node == nullptr) {
		return 0;
	}
	//Base Case
	//If the Node's LeftNode and RightNode ar nullptr, there is a root node with not children so return Height 1
	else if(node->LeftNode == nullptr && node->RightNode == nullptr) {
		return 1;
	}
	//Recursive call
	else {
		//Adds 1 plus which ever has more calls, the rightNode or the leftNode and returns the Height(int)
		return 1 + max(HightHelper(node->LeftNode), HightHelper(node->RightNode));
	}
}
int BinTree::getHeight(const NodeData& dataNode)  {

	//NodeData* nodeDataRef;
	Node* retrievedNode = retrieveDataHelper(dataNode);
	if (retrievedNode == nullptr) {
		return 0;
	}
	else {
		
		return HightHelper(retrievedNode);
	}


}
void BinTree::clearTree(Node* node) {
	if (node == nullptr) {
		return;
	}
	else {
		clearTree(node->LeftNode);
		clearTree(node->RightNode);
		delete node;
		
	}
}
void BinTree::clear()
{
	clearTree(root);
	root = nullptr;
}
void clearArray(NodeData* arr[])
{
	static int pos = 0;
	while(arr != nullptr)
	{
		arr[pos++] = nullptr;
	}
}
void BinTree::bstreeToArrayHelper(Node* root, NodeData* arr[]) {
	static int pos = 0;
	if (root == nullptr) {
		return;
	}
	else {
		bstreeToArrayHelper(root->LeftNode, arr);
		arr[pos++] = root->nodeData;
		bstreeToArrayHelper(root->RightNode, arr);
	}
}
void BinTree::bstreeToArray(NodeData* arr[]) {
	bstreeToArrayHelper(root, arr);
	clearTree(root);
	root = nullptr;

}
void BinTree::bstreePreToArrayHelper(Node* root, NodeData* arr[]) {
	static int pos = 0;
	if (root == nullptr) {
		return;
	}
	else {
		arr[pos++] = root->nodeData;
		bstreePreToArrayHelper(root->LeftNode, arr);
		bstreePreToArrayHelper(root->RightNode, arr);
	}
}
void BinTree::arrayToBSTreeHelper(int first, int last, int index, NodeData* arr[])
{
	if(first > last)
	{
		return;
	}
	
	InsertNode(arr[index]);
	arr[index] = NULL;
	int childLeft = (first + index - 1) / 2;
	int childRight = (index + 1 + last) / 2;
	arrayToBSTreeHelper(first, index - 1, childLeft, arr);
	arrayToBSTreeHelper(index + 1, last, childRight, arr);
}
void BinTree::arrayToBSTree(NodeData* arr[])
{
	int size = 0;
	for(int i = 0; arr[i] != NULL; i++)
	{
		size++;
	}
	arrayToBSTreeHelper(0, size - 1, (size-1)/2,  arr);
	
	
}
//BinTree& BinTree::operator=(const BinTree& rightHandSide)
bool BinTree::equalsHelper(const Node* leftnode, const Node* rightnode) const
{
	if(leftnode == nullptr && rightnode == nullptr)
	{
		return true;
	}else if(leftnode != nullptr && rightnode == nullptr)
	{
		return false;
	}else if(leftnode == nullptr && rightnode != nullptr)
	{
		return false;
	}else if(leftnode->getNodeData()->getData() == rightnode->getNodeData()->getData())
	{
		bool leftAnswer = equalsHelper(leftnode->LeftNode, rightnode->LeftNode);
		bool RightAnswer = equalsHelper(leftnode->RightNode, rightnode->RightNode);
		
		return leftAnswer && RightAnswer;
	}else
	{
		return false;
	}
}
bool BinTree::operator==(const BinTree& rightHandSide) const
{
	return equalsHelper(root, rightHandSide.root);
}
bool BinTree::operator!=(const BinTree& rightHandSide) const
{
	return !equalsHelper(root, rightHandSide.root);
}
BinTree& BinTree::operator=(const BinTree& rightHandSide)
{
	clearTree(root);
	NodeData* arr[100] = { NULL };
	bstreePreToArrayHelper(root, arr);
	arrayToBSTree(arr);
	return *this;
	
}
ostream& operator<<(ostream& outputStream, BinTree& outputList)
{
	outputList._InOrderTraversal(outputList.root, outputStream);
	return outputStream;
}

#endif
