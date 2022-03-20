#include "movie.h"
using namespace std;
/*
 * Overloading of the ostream operator to tell the compiler how to print a classic movie object when using the cout function
 */
ostream& operator<<(ostream& os, const classicMovie& m)
{
	os << m.movieType << ", " << m.movieStock << ", " << m.director << ", " << m.movieTitle << ", " << m.majorActor << ", " << m.releaseMonth << "/" << m.movieYear;
	return os;
}
/*
 * Getter and Setters of the releaseMonth member of the classic Movie
 */
string classicMovie::getReleaseMonth() const
{
	return releaseMonth;
}
void classicMovie::setReleaseMonth(const string month)
{
	this->releaseMonth = month;
}
/*
 * Getter and Setters of the majorActor member of the classic Movie
 */
string classicMovie::getMajorActor() const
{
	return majorActor;
}
void classicMovie::setMajorActor(const string& majorActor)
{
	this->majorActor = majorActor;
}
