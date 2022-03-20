#ifndef POLY_H
#define POLY_H
#include <iostream>
using namespace std;

struct Term
{
	int exponent;
	int coefficient;
};

class Poly {
private:
	Term* p;		
	int degree;

	//Expander helper function that expands the smaller polynomial for all 
	// of the arthemtic operator overloads
	Poly Expand(const Poly& other, int degree);
	//Compares the coefficiants in two polynomials and returns a bool of
	// whether or not they have the same coefficiants
	bool comparePolynomial(const Poly& object, const Poly& other);
	

public:
	//Constructor that initializes both the coefficient and the degree of the polynomial
	Poly(int coefficient, int degree);
	//Constructor that takes a coefficient int and initializes polynomial to a constant because
	// there is no degree given
	Poly(int coefficient);
	// Default constructor
	Poly();
	// Deep copy constructor
	Poly(const Poly& obj);
	// Destructor
	~Poly();

	//returns the coefficient at the index passed in
	int getCoeff(int index) {
		if (index > degree || index < 0) {
			return 0;
		}
		return this->p[index].coefficient;
	}

	//sets the Coefficient of the given index. It the degree of the polynomial
	// is larger then the index passed in, the polynomial is expanded and then
	// the coefficient is assigned to the appropriate index
	void setCoeff(int value, int index) {
		if (index < 0) {
			return;
		}
		else if (index > degree) {
			*this = Expand(*this, index);
		}
		this->p[index].coefficient = value;
	}

	//Overloading the instream operator to keep asking the user to input
	// coefficients and exponents until the user enters consecutive -1's
	friend istream& operator>> (istream& input, Poly& poly);

	//Overloading the outstream operator to output each term in a polynomial
	friend ostream& operator<< (ostream& os, const Poly& poly);

	//Adds two polynomials together and returns a new polynomial
	Poly operator+ (const Poly& obj);

	//Subtracts two polynomials and returns a new polynomial
	Poly operator- (const Poly& other);

	//Multiplies two polynomials and return a new polynomial
	Poly operator* (const Poly& obj) const;

	//Assigns an existing polynomial to other polynomial
	Poly& operator= (const Poly& obj);

	//Adds two operands together and assigns that value to the left operand
	Poly& operator+= (Poly& other);
	//Subtracts two operands together and assigns that value to the left operand
	Poly& operator-= (Poly& other);
	//Multiplies two operands together and assigns that value to the left operand
	Poly& operator*= (Poly& other);
	
	//Compares two polynomials and returns whether or not they are the same
	// Returns true if they ARE the same
	bool operator== (const Poly& other);
	
	//Compares two polynomials and returns whether or not they are the same
	// Returns true if they are NOT the same
	bool operator!= (Poly& other);
};
#endif