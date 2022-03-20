#include "customer.h"
#include <iostream>
using namespace std;
/*
 * Overloading the ostream object to tell the compiler how to print out itself when using cout function
 */
ostream& operator<<(ostream& os, const customer& c)
{
	os << c.idNumber << ", " << c.name;
	return os;
};
/*
 * Customer Constructor
 */
customer::customer(int idNumber, string name)
{
	this->idNumber = idNumber;
	this->name = name;
}
/*
 * Customer Destructor
 */
customer::~customer()
{
	
}
	