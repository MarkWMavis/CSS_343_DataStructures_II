#ifndef POLY_CPP
#define POLY_CPP
#include "poly.h"
using namespace std;


Poly Poly::Expand(const Poly& other, int degree) {

	Poly temp(0, degree);
	for (int i = 0; i < other.degree + 1; i++) {
		temp.p[i] = other.p[i];
	}
	return temp;
}
bool Poly::comparePolynomial(const Poly& object, const Poly& other)
{
	bool temp = true;
	for (int i = 0; i < object.degree + 1; i++)
	{
		if (object.p[i].coefficient != other.p[i].coefficient)
		{
			temp = false;
		}
	}
	return temp;
}

Poly::Poly(int coefficient, int degree) {
	p = new Term[degree + 1];
	this->degree = degree;
	for (int i = 0; i < degree + 1; i++) {
		p[i].exponent = i;
		p[i].coefficient = 0;
	}
	p[degree].coefficient = coefficient;
}
Poly::Poly(int coefficient) {
	p = new Term[1];
	this->degree = 0;
	p[0].exponent = 0;
	p[0].coefficient = coefficient;
}
Poly::Poly() {
	p = new Term[1];
	this->degree = 0;
	p[0].exponent = 0;
	p[0].coefficient = 0;
}
Poly::Poly(const Poly& obj) {
	p = new Term[obj.degree + 1];
	this->degree = obj.degree;
	for (int i = 0; i < degree + 1; i++) {
		p[i].exponent = obj.p[i].exponent;
		p[i].coefficient = obj.p[i].coefficient;
	}
}
Poly::~Poly() {
	delete[]p;
}

istream& operator>> (istream& input, Poly& poly) {
	int coeff;
	int exp;
	
	while (true) {
		input >> coeff >> exp;
		if (coeff == -1 && exp == -1) {
			break;
		}
		else if(exp > poly.degree){
			//Skip invalid exponent input
		}
		else {
			poly.p[exp].coefficient = coeff;
		}
	}
	return input;
}
ostream& operator<< (ostream& os, const Poly& poly) {
	for (int i = poly.degree; i >= 0; i--) {
		if (poly.p[i].coefficient != 0 && poly.p[i].exponent >1) {
			os << showpos << poly.p[i].coefficient << "x^" << noshowpos << poly.p[i].exponent << " ";
		}else if(poly.p[i].coefficient != 0 && poly.p[i].exponent == 1){
			os << showpos << poly.p[i].coefficient << "x" << " ";
		}else if(poly.p[i].coefficient != 0 && poly.p[i].exponent == 0){
			os << showpos << poly.p[i].coefficient;
		}else {
			os;
		}
	}
	os << endl;
	return os;
}

Poly Poly::operator+ (const Poly& obj) {
	if (obj.degree < degree) {
		Poly temp = Expand(obj, degree);
		for (int i = 0; i < temp.degree + 1; i++) {
			temp.p[i].coefficient += this->p[i].coefficient;
		}
		return temp;
	}
	else if (obj.degree > degree) {

		Poly temp = Expand(*this, obj.degree);
		for (int i = 0; i < temp.degree + 1; i++) {
			temp.p[i].coefficient += obj.p[i].coefficient;
		}
		return temp;
	}
	else {
		Poly temp(obj);
		for (int i = 0; i < temp.degree + 1; i++) {
			temp.p[i].coefficient += this->p[i].coefficient;
		}
		return temp;
	}

}
Poly Poly::operator- (const Poly& other) {

	if (other.degree < degree) {
		Poly temp = Expand(other, degree);
		for (int i = 0; i < temp.degree + 1; i++) {
			this->p[i].coefficient -= temp.p[i].coefficient;
		}
		return *this;
	}
	else if (other.degree > degree) {

		Poly temp = Expand(*this, other.degree);
		for (int i = 0; i < temp.degree + 1; i++) {
			temp.p[i].coefficient -= other.p[i].coefficient;
		}
		return temp;
	}
	else {
		Poly temp(other);
		for (int i = 0; i < temp.degree + 1; i++) {
			this->p[i].coefficient -= temp.p[i].coefficient;
		}
		return *this;
	}
}
Poly Poly::operator* (const Poly& obj) const {
	int resdegree = this->degree + obj.degree;
	Poly temp(0, resdegree);
	for (int i = 0; i < this->degree + 1; i++) {
		for (int j = 0; j < obj.degree + 1; j++) {
			int tempindex = i + j;
			temp.p[tempindex].coefficient += this->p[i].coefficient * obj.p[j].coefficient;
		}
	}
	return temp;
}
Poly& Poly::operator= (const Poly& obj) {
	if (*this == obj) {
		return *this;
	}
	delete[]p;
	p = new Term[obj.degree + 1];
	this->degree = obj.degree;
	for (int i = 0; i < degree + 1; i++) {
		p[i].exponent = obj.p[i].exponent;
		p[i].coefficient = obj.p[i].coefficient;
	}
	return *this;
}
Poly& Poly::operator+= (Poly& other) {
	*this = *this + other;
	return *this;
}
Poly& Poly::operator-= (Poly& other) {
	*this = *this - other;
	return *this;
}
Poly& Poly::operator*= (Poly& other) {
	*this = *this * other;
	return *this;
}

bool Poly::operator== (const Poly& other) {

	if ((this->degree == other.degree) && (comparePolynomial(*this, other) != false))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Poly::operator!= (Poly& other) {
	if ((this->degree != other.degree) || (comparePolynomial(*this, other) != true))
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif