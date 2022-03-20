#include "movie.h"
/*
 * Overloading of the ostream operator to tell the compiler how to print a movie object when using the cout function
 */
ostream& operator<<(ostream& os, const Movie& m)
{
	os << m.movieType << ", " << m.movieStock << ", " << m.director << ", " << m.movieTitle << ", " << m.movieYear;
	return os;
}
/*
 * Default Constructor
 */
Movie::Movie()
{
	this->movieType = "";
	this->movieStock = 0;
	this->director = "";
	this->movieTitle = "";
	this->movieYear = "";
	this->copiesAvailable = 1;
}
/*
 * Movie Constructor
 */
Movie::Movie(string type, int stock, string director, string title, string year)
{
	this->movieType = type;
	this->movieStock = stock;
	this->director = director;
	this->movieTitle = title;
	this->movieYear = year;
	this->copiesAvailable = stock;
}
/*
 * Movie Destructor
 */
Movie::~Movie()
 {

	 //cout << "Movie Destructor Called" << endl;
 }
/*
 * Getters and Setters for MovieType member
 */
string Movie::getMovieType() const
{
	return movieType;
}
void Movie::setMovieType(const string movieType)
{
	this->movieType = movieType;
}
/*
 * Getters and Setters for MovieStock member
 */
int Movie::getMovieStock() const
{
	return movieStock;
}
void Movie::setMovieStock(const int n)
{
	if(n >= 0)
	{
		this->movieStock = n;
	}else
	{
		cout << "Can not set stock number to a negative number" << endl;
	}
}
/*
 * Getters and Setters for Director member
 */
string Movie::getDirector() const
{
	return director;
}
void Movie::setDirector(const string director)
{
	this->director = director;
}
/*
 * Getters and Setters for MovieTitle member
 */
string Movie::getMovieTitle() const
{
	return movieTitle;
}
void Movie::setMovieTitle(const string title)
{
	this->movieTitle = title;
}
/*
 * Getters and Setters for MovieYear member
 */
string Movie::getMovieYear() const
{
	return movieYear;
}
void Movie::setMovieYear(const string& myear)
{
	this->movieYear = myear;
}
/*
 * Getters and Setters for CopiesAvailable member
 */
int Movie::getCopiesAvailable() const
{
	return copiesAvailable;
}
void Movie::setCopiesAvailable(const int n)
{
	this->copiesAvailable = n;
}