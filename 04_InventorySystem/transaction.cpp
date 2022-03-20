#include "transaction.h"
ostream& operator<<(ostream& os, const transaction& t)
{
	os << "Action Type: " << t.action << endl;
	os << "CustomerID Number: " << t.customerIDNumber << endl;
	os << "TypeOfMedia: " << t.typeOfMedia << endl;
	os << "Movie Title: " << t.movieTitle << endl;
	return os;
};

transaction::transaction()
{
	this->action = ' ';
	this->customerIDNumber = 0;
	this->typeOfMedia = ' ';
	this->movieTitle = " ";
}

transaction::transaction(string action, int customerIDNumber, string typeOfMedia, string movieTitle)
{
	this->action = action;
	this->customerIDNumber = customerIDNumber;
	this->typeOfMedia = typeOfMedia;
	this->movieTitle = movieTitle;
}

transaction::~transaction() = default;