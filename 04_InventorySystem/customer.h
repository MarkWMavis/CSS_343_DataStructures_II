#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <ostream>
using namespace std;

class customer
{
private:
	int idNumber;
	string name;

	friend class inventory;
public:
	friend ostream& operator<<(ostream& os, const customer& c);
	customer(int idNumber, string name);
	~customer();
};



#endif
