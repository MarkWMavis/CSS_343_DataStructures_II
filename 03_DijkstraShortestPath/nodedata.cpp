#include "nodedata.h"

//------------------- constructors/destructor  -------------------------------
NodeData::NodeData()  // default
{
	data = "";
}                        

NodeData::~NodeData()  // needed so strings are deleted properly
{
	
}           

NodeData::NodeData(const NodeData& nd)	// copy
{
	data = nd.data;
} 

NodeData::NodeData(const string& s)	// cast string to NodeData
{
	data = s;
}    

//------------------------------ setData -------------------------------------
// returns true if the data is set, false when bad data, i.e., is eof
bool NodeData::setData(istream& infile) {
	getline(infile, data);
	return !infile.eof();       // eof function is true when eof char is read
}

//------------------------- operator= ----------------------------------------
NodeData& NodeData::operator=(const NodeData& rhs) {
	if (this != &rhs) {
		data = rhs.data;
	}
	return *this;
}

//------------------------- operator==,!= ------------------------------------
bool NodeData::operator==(const NodeData& rhs) const {
	return data == rhs.data;
}

bool NodeData::operator!=(const NodeData& rhs) const {
	return data != rhs.data;
}

//------------------------ operator<,>,<=,>= ---------------------------------
bool NodeData::operator<(const NodeData& rhs) const {
	return data < rhs.data;
}

bool NodeData::operator>(const NodeData& rhs) const {
	return data > rhs.data;
}

bool NodeData::operator<=(const NodeData& rhs) const {
	return data <= rhs.data;
}

bool NodeData::operator>=(const NodeData& rhs) const {
	return data >= rhs.data;
}

//-------------------------- operator<< --------------------------------------
ostream& operator<<(ostream& output, const NodeData& nd) {
	output << nd.data;
	return output;
}
