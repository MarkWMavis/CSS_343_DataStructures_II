#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>
#include "movie.h"
#include <string>
#include "transaction.h"
#include "customer.h"
#include "hashTable.h"

using namespace std;

class inventory
{
	vector<Movie*> movies;				//Vector that holds all movies in inventory
	vector<customer> customers;			//Vector that holds all customer accounts 
	vector<transaction> transactions;	//Vector that holds all transactions from all customers
	hashTable moviesHash;				//Movie Title hashTable

	void printMovies(vector<Movie*> list);				//Prints all information to all movies in the current inventory 
	void printTransactions();							//Prints all past Transactions
	bool actionTypeAuthentication(string action);		//Authenticates that the passed Action is available in the borrow movie and return movie functionality
	bool customerAuthentication(string custID);			//Authenticates the passed customerID matches an existing account member
	bool movieTitleAuthentication(string movieTitle);	//Authenticates the passed movieTitle matchs an existing movie in the inventory
	bool directorAuthentication(string director);		//Authenticates the passed directorName matches an existing movie with that director
	
	Movie& findClassicMovie(const string actor, const string movieYear);		//Searches the movie inventory for a matching MajorActor and the releaseYear of the movie and returns the movie address reference
	Movie& findComedyMovie(const string movieTitle);							//Uses a hashTable to find where a movie is located in the inventory and then returns the address reference of that movie
	Movie& findDramaMovie(const string director, const string movieTitle);		//Searches for a movie that has a director
	customer& findCustomer(const string custID);
	
	bool mediaTypeAuthentication(const string mediaT);		//Utility function used by all of the movie Authentication functions to validate the media type
	bool movieTypeAuthentication(const string movieT);		//Utility function used by all of the movie Authentication functions to validate the movie type
	/*
	 * Function that authenticates the action, customerID, mediaType, movieType, and movieTitle for all comedy movies
	 */
	bool comedyMovieAuthentication(string action, string customerID, string mediaType, string movieType, string movieTitle);
	/*
	 * Function that authenticates the action, customerID, mediaType, movieType, director, and movieTitle for all drama movies
	 */
	bool dramaMovieAuthentication(string action, string customerID, string mediaType, string movieType, string director, string movieTitle);
	/*
	 * Function that authenticates the action, customerID, mediaType, movieType, director, and movieTitle for all classic movies
	 */
	bool classicMovieAuthentication(string action, string customerID, string mediaType, string movieType);

	struct comedyless;	//Structure used for comedy movie attributes comparison print the movies in acceding order from movie title then release year
	struct dramaless;	//Structure used for drama movie attributes comparison print the movies in acceding order from director name and then movieTitle
	struct classicsless;//Structure used for Classic movie attributes comparison print the movies in acceding order from release date, then major actor

	/*
	 * Function that uses the above structures to sort and print out all the movie in the inventory 
	 */
	void sortedInventoryPrintOut();
	/*
	 * Function responsible for printing out all transactions that match the given customer ID
	 */
	void customerTransactionHistory(char actionType, string ID);
	/*
	 * Function responsible for validating all movie information and if so,  find the movie in the inventory, find the customer in the database, create
	 * a transaction and then update the inventory by incrementing that movies availability variable
	 */
	void borrowMovie(string& information);
	/*
	 * Function responsible for validating all movie information and if so,  find the movie in the inventory, find the customer in the database, create
	 * a transaction and then update the inventory by decrementing that movies availability variable
	 */
	void returnMovie(string information);
	
public:
	inventory() : moviesHash(100)	//Default constructor that initializes a hashTable of size 100
	{
		
	};
	~inventory();						//Inventory Destructor

	/*
	 * Function responsible for building the movie inventory and the customer database txt files
	 */
	void buildInventory(ifstream& movieFile, ifstream& customerFile);
	/*
	 * Function responsible for processing the commands txt file
	 */
	void processCommands(ifstream& command);
	
};
#endif


