#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <iostream>
using namespace std;
class Movie
{
	/*
	 * Declaring Protected variables so that the classicMovie class that inherits from the movie class
	 * is able to access those same attributes.
	 */
protected:
	string movieType;		//Private Member attribute that holds the type of movie
	int movieStock;			//Private Member attribute that holds the number of copies of each movie that the store owns 
	string director;		//Private Member attribute that holds the movies director's name
	string movieTitle;		//Private Member attribute that holds the movies title
	string movieYear;		//Private Member attribute that holds the year the movie was released
	int copiesAvailable;	//Private Member attribute that holds the number of copies currently in stock to rent out
public:	
	string getMovieType() const;				//Getter of the Type of movie attribute
	void setMovieType(const string c);			//Setter of the Type of movie attribute
	
	int getMovieStock() const;					//Getter of the Movie Stock attribute
	void setMovieStock(const int n);			//Setter of the Movie Stock attribute

	string getDirector() const;					//Getter of the Director attribute 
	void setDirector(const string director);	//Setter of the Director Attribute
		
	string getMovieTitle() const;				//Getter of the Movie Title attribute
	void setMovieTitle(const string title);		//Setter of the Movie Title attribute

	string getMovieYear() const;				//Getter of the Movie's release year attribute
	void setMovieYear(const string& myear);		//Setter of the Movie's release year attribute

	int getCopiesAvailable() const;				//Getter of the Available copies attribute
	void setCopiesAvailable(const int n);		//Setter of the Available copies attribute
	
	friend class inventory;											//Allows the Inventory class to access all of the movies attributes and functions
	friend ostream& operator<<(ostream& os, const Movie& m);		//Overloading the ostream operator to control the way the movie object outputs itself

	Movie();																		//Default Object Constructor
	Movie(string type, int stock, string director, string title, string year);		//Movie Object Constructor
	~Movie();																		//Movie Object Destructor
};
/*
 *Inherited Class that has additional private members (releaseMonth, majorActor)
 */
class classicMovie : public Movie	
{	
	string releaseMonth;		//Private member attribute that holds the release date month
	string majorActor;			//Private member attribute that holds the majorActor of the movie

	friend class inventory;		//Allows the inventory class to access all oof the classicMovie objects attributes and functions
	friend ostream& operator<<(ostream& os, const classicMovie& m);		//Overloading the ostream operator to control the way the movie object outputs itself
	
public:
	
	/*
	 * inherited Constructor that passes additional information on to the movie constructor
	 */
	classicMovie(string type, int stock, string director, string title, string releaseMonth, string releaseYear, string majorActor) : Movie(type, stock, director, title, releaseYear) {
		this->releaseMonth = releaseMonth;		//Initializing the classicMovie's releaseMonth member
		this->majorActor = majorActor;			//Initializing the classicMovie's majorActor member
	}

	/*
	 * Getters and Setters for releaseMonth
	 */
	string getReleaseMonth() const;				
	void setReleaseMonth(const string month);
	/*
	 * Getters and Setters for majorActor
	 */
	string getMajorActor() const;
	void setMajorActor(const string& majorActor);
};

#endif
