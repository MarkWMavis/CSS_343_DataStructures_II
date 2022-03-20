#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <iterator>
#include "inventory.h"

/*
 * Utility function that takes a vector and prints the list of movies in that vector
 */
void inventory::printMovies(vector<Movie*> list)	
{
	//Loop through vector and print what is at the location of the Movie pointer which is a movie. This will invoke the
	// overloaded ostream operator to print out all movie information
	for (size_t i = 0; i < list.size(); i++)
	{
		cout << *list[i] << endl;
	}
}		
/*
 * Utility function that prints out transactions in the inventory system
 */
void inventory::printTransactions()
{
	//Loop through the transaction vector and print out all transactions at i. This will invoke the overloaded ostream operator
	// to print all transaction information
	for (size_t i = 0; i < transactions.size(); i++)
	{
		cout << transactions[i];
	}
}		

/*
 * Responsible for Authenticating the action type passed
 */
bool inventory::actionTypeAuthentication(string action)
{
	//Authenticate that the process requested is a valid one and if so,
	// return true.
	if (action == "I" || action == "B" || action == "R" || action == "H")
	{
		return true;
	}
	else
	{
		//If not Valid, notify the user and
		// return false
		cout << "Not a valid action type" << endl;
		return false;
	}
}

/*
 * Responsible for customer ID authentication
 */
bool inventory::customerAuthentication(string custID)
{
	const int customerID = stoi(custID);				//- Convert incoming customer string ID to a const int for comparison
														//  against the customer objects idNumber member
	for (size_t i = 0; i < customers.size(); i++)		//- Loop through customers vector
	{
		if (customers[i].idNumber == customerID)		//- If the customer at i idNumber equals the given customer number
		{
			return true;								//- return true
		}
	}																
	cout << "The customer ID does not exist in Database" << endl;		//- If the end of the customer vector is reached without matching the customerID
																		//  alert user that customer does not exist in database
	return false;														//- return false
}
/*
 * Responsible for searching the movie inventory to compare the passed movie title against all inventory movie titles to indicate a match
 */
bool inventory::movieTitleAuthentication(string movieTitle)
{
	//Creating a vector iterator to iterate over the movies container. When the the passed movieTitle matches what the movieObject's
	//m.getMovieTitle method returns, then the iterator will be pointing at the correct movie.
	auto it = find_if(movies.begin(), movies.end(), [&movieTitle](Movie* m) {return m->getMovieTitle() == movieTitle; });

	//Check to see if iterator is at the end of the movie container
	if (it == movies.end())
	{
		//If the iterator is at the end, alert the user that there was not movie of that title in database
		// and return false
		cout << "Movie title is not valid! We do not carry a movie with that title" << endl;
		return false;
	}
					// If Not at the end
	return true;	// return true
}

/*
 * Responsible for Authentication through the comparison of the passed director against all other directors in movie inventory
 */
bool inventory::directorAuthentication(string director)
{
	//Create a movie vector iterator and iterator over the movies container. When the iterator is pointing at a movie that has
	//a director that matches the name passed, stop looking 
	auto it = find_if(movies.begin(), movies.end(), [&director](Movie* m) {return m->getDirector() == director; });

	//if the iterator is at the end of the movies container
	if (it == movies.end())
	{
		//The movie has not be found. Alert user that there is no movie with that director
		//and return false
		cout << "We do not have any movies by this director" << endl;
		return false;
	}

	//if the iterator is not at the end, it has found the movie
	//return true
	return true;
}

/*
 * Responsible for Authentication of all elements being passed from the process commands related to Drama Movies
 */
bool inventory::dramaMovieAuthentication(string action, string customerID, string mediaType, string movieType, string director, string movieTitle)
{
	//short circuit test that authenticates all conditions before returning true
	return actionTypeAuthentication(action) && customerAuthentication(customerID) && mediaTypeAuthentication(mediaType) && movieTypeAuthentication(movieType) && directorAuthentication(director) && movieTitleAuthentication(movieTitle);
}

/*
 * Responsible for Authentication of all elements being passed from the process commands related to Classic Movies
 */
bool inventory::classicMovieAuthentication(string action, string customerID, string mediaType, string movieType)
{
	//short circuit test that authenticates all conditions before returning true
	return actionTypeAuthentication(action) && customerAuthentication(customerID) && mediaTypeAuthentication(mediaType) && movieTypeAuthentication(movieType);
}

/*
 * Responsible for Authentication of all elements being passed from the process commands related to Comedy Movies
 */
bool inventory::comedyMovieAuthentication(string action, string customerID, string mediaType, string movieType, string movieTitle)
{
	//short circuit test that authenticates all conditions before returning true
	return actionTypeAuthentication(action) && customerAuthentication(customerID) && mediaTypeAuthentication(mediaType) && movieTypeAuthentication(movieType) && movieTitleAuthentication(movieTitle);
}

/*
 * Responsible for takings the actors name and the year the movie was released and finding a classic movie that matches the criteria
 */
Movie& inventory::findClassicMovie(const string actor, const string movieYear)
{
	
	vector<Movie*> classics(movies.size());		//Creating a temporary vector of pointers to classic movies

	//Using the copy_if function of the algorithm class to iterator over the movies vector container and copy the pointers to the classic movies that have a movie type of Classic
	auto it = copy_if(movies.begin(), movies.end(), classics.begin(), [](Movie* m) { return ((classicMovie*)m)->getMovieType() == "C"; });

	//Resizing the temporary vector to correct size
	classics.resize(distance(classics.begin(), it));	

	//Iterate over the temporary classic movie vector to find the movie that matches both the actor and the movie release year
	//and return that movie object that the iterator is pointing to
	it = find_if(classics.begin(), classics.end(), [&actor, &movieYear](Movie* m) {return ((classicMovie*)m)->getMajorActor() == actor && ((classicMovie*)m)->getMovieYear() == movieYear; });

	
	return **it;		//Return the movie at the location of the iterator
}

/*
 * Responsible for taking the movie title and converting the Movie Title to a hashTable index and then getting and return the movie index that is stored
 * at the hashTable index location
 */
Movie& inventory::findComedyMovie(const string movieTitle)
{
	
	const auto index = moviesHash.find(movieTitle);		//returning the index of the movie in the movies vector
	return *movies.at(index);									//Returning the movie at the the index location in the movies vector

}

/*
 * Responsible for finding the movie that matches the passed director and movie Title and returning the location of that movie
 */
Movie& inventory::findDramaMovie(const string director, const string movieTitle)
{
	//Create a vector iterator and iterator of the movies container looking for a movie that matches the passed director and movie title
	auto it = find_if(movies.begin(), movies.end(), [&director, &movieTitle](Movie* m) {return m->getDirector() == director && m->getMovieTitle() == movieTitle; });

	//if the iterator is not pointing at the end, the iterator must be pointing at the movie
	if (it != movies.end())
	{
		return **it;		//Return movie
	}
	else
	{
		//if the iterator is pointing at the end, the movie must not exist so notify user and
		//return nothing
		cout << "movie with that director is not available" << endl;
		return **movies.end();
	}

}

/*
 * Responsible for taking a string customer ID and finding the customer object in the database based on that string
 */
customer& inventory::findCustomer(const string custID)
{
	const auto customerID = stoi(custID);		//Convert the string to an integer for comparison

	//Create an vector iterator that searches through the customers vector and returns the customer object that matches the idNumber
	const auto it = find_if(customers.begin(), customers.end(), [&customerID](customer c) {return c.idNumber == customerID; });

	//If the iterator is not pointing at the end of the customers vector, then it must have found the customer and is pointing at the customer object
	if (it != customers.end())
	{
		//Letting the user know that it found the customer in the database
		cout << "Customer Found-> " << "Name: " << it->name << " CustomerID: " << it->idNumber << endl;
		return *it;		//Returning the customer object
	}
	else
	{
		//Alert the user that there is no customer with that customer ID in the database
		cout << "customer does not exist" << endl;
		//return nothing
		return *customers.end();
	}

}
/*
 * Responsible for Authenticating that the system is only taking in DVD movies
 */
bool inventory::mediaTypeAuthentication(const string mediaT)
{
	//If the media type is D for dvd
	if (mediaT == "D")
	{
		//return true
		return true;
	}
	else
	{
		//If not correct media type, alert user that they do not accept any other then Dvd
		//and return false
		cout << "This is an Invalid media type. We do not accept VHS" << endl;
		return false;
	}
}

/*
 * Responsible for authentication of the Action Types
 */
bool inventory::movieTypeAuthentication(const string movieT)
{
	//If the action type matches one of the following three
	//return true
	if (movieT == "F" || movieT == "C" || movieT == "D")
	{
		return true;
	}
	else
	{
		//If not alert the user of invalid type and
		//return false
		cout << "You entered an invalid movie type. That genre is not available" << endl;
		return false;
	}
}

/*
 * Utility function used in the sortedInventoryPrintOut() class to compare and sort the comedy movie vector
 * by movie title and then year
 */
struct inventory::comedyless
{
	bool operator()(const Movie* m1, const Movie* m2) const
	{
		if (m1->movieTitle < m2->movieTitle)
		{
			return true;
		}
		else if (m1->movieTitle > m2->movieTitle)
		{
			return false;
		}
		else
		{

			return m1->movieYear < m2->movieYear;
		}
		return true;
	}
};

/*
 * Utility function used in the sortedInventoryPrintOut() class to compare and sort the drama movie vector
 * by Director then title
 */
struct inventory::dramaless
{
	bool operator()(const Movie* m1, const Movie* m2) const
	{
		if (m1->director < m2->director)
		{
			return true;
		}
		else if (m1->director > m2->director)
		{
			return false;
		}
		else
		{

			return m1->movieTitle < m2->movieTitle;
		}
		return true;
	}
};

/*
 * Utility function used in the sortedInventoryPrintOut() class to compare and sort the classic movie vector
 * by Release date, then major actor
 */
struct inventory::classicsless
{

	bool operator()(Movie* m1, Movie* m2)
	{
		const int month1 = stoi(((classicMovie*)m1)->getReleaseMonth());
		const int month2 = stoi(((classicMovie*)m2)->getReleaseMonth());
		const int year1 = stoi(((classicMovie*)m1)->getMovieYear());
		const int year2 = stoi(((classicMovie*)m2)->getMovieYear());

		if (year1 < year2)
		{
			return true;
		}
		else if (year1 > year2)
		{
			return false;
		}
		if (month1 < month2)
		{
			return true;
		}
		else if (month1 > month2)
		{
			return false;
		}
		else
		{
			return ((classicMovie*)m1)->getMajorActor() < ((classicMovie*)m2)->getMajorActor();
		}
		return true;
	}
};

void inventory::sortedInventoryPrintOut()
{
	//output Comedys (sorted by title and then titleYear),
	vector<Movie*> comedys(movies.size());

	//Iterator through the movies vector to find all movies of type F and copy them off into the temporary comedy Vector
	auto it = copy_if(movies.begin(), movies.end(), comedys.begin(), [](Movie* m) { return m->getMovieType() == "F"; });
	//Resize the temporary vector
	comedys.resize(distance(comedys.begin(), it));
	//Sort the vector with comedyless structure function
	sort(comedys.begin(), comedys.end(), comedyless{});
	//Print all movie information
	printMovies(comedys);

	//then Dramas (sorted by Director, then Title)
	vector<Movie*> dramas(movies.size());
	//Iterator through the movies vector to find all movies of type D and copy them off into the temporary dramas Vector
	it = copy_if(movies.begin(), movies.end(), dramas.begin(), [](Movie* m) { return m->getMovieType() == "D"; });
	//Resize the temporary vector
	dramas.resize(distance(dramas.begin(), it));
	//Sort the vector with the dramaless structure function
	sort(dramas.begin(), dramas.end(), dramaless{});
	//Print all movie information
	printMovies(dramas);


	//then Classics (sorted by Release date, then major actor)
	vector<Movie*> classics(movies.size());
	//Iterator through the movies vector to find all movies of type C and copy them off into the temporary classics Vector
	it = copy_if(movies.begin(), movies.end(), classics.begin(), [](Movie* m) { return m->getMovieType() == "C"; });
	//Resize the temporary vector
	classics.resize(distance(classics.begin(), it));
	//Sort the vector with the classicsless structure function
	sort(classics.begin(), classics.end(), classicsless{});
	//Print all movie information
	printMovies(classics);
}
void inventory::customerTransactionHistory(char actionType, string ID)
{
	//Create temporary transacations to store all transactions that matches the passed customer ID 
	vector<transaction> customerTransactions(transactions.size());
	int customerID = stoi(ID);	//Convert string to integer

	//Check to see if the transaction vector is empty
	if (!transactions.empty())
	{
		//if the vector is not empty, iterator through the transactions and collect all of the ones that have the customer ID
		auto it = copy_if(transactions.begin(), transactions.end(), customerTransactions.begin(), [&customerID](transaction t) {return t.customerIDNumber == customerID; });
		//Resize the collected transaction vector to the appropriate size
		customerTransactions.resize(distance(customerTransactions.begin(), it));

		//if the customer transactions vector is not empty
		if (!customerTransactions.empty())
		{
			//print out all of the transactions collected
			for (size_t i = 0; i < customerTransactions.size(); i++)
			{
				cout << customerTransactions[i];
			}
		}
		else
		{
			//If the customer transactions is empty, notify the user that the customer doesn't have any transaction under their account
			cout << "There are no available transactions for this customer" << endl;
		}
	}
	else
	{
		cout << "There are no transactions available" << endl;
	}
}

/*
 * Responsible for all borrowing actions processed
 */
void inventory::borrowMovie(string& information)
{
	
	if(information.substr(9, 1) == "F")
	{
		cout << "Borrowing A Comedy" << endl;
		string action;
		string customerID;
		string mediaType;
		string movieType;
		string movieTitle;
		string movieYear;

		stringstream ss(information);
		ss >> action >> customerID >> mediaType >> movieType;
		getline(ss >> ws, movieTitle, ',');
		ss >> movieYear;
		
		if(comedyMovieAuthentication(action, customerID, mediaType, movieType, movieTitle))
		{
			cout << "Comedy Movie Authenticated" << endl; //Lets the user know that the movie has be
			Movie* mp = &findComedyMovie(movieTitle);
			cout << "Movie Found is: " << mp->movieTitle << ", " << "Director: " << mp->director << " Year: " << mp->movieYear << endl;
			if (mp->copiesAvailable > 0)
			{
				customer* cp = &findCustomer(customerID);									//Find and return customer object
				transaction t(action, cp->idNumber, mp->movieType, mp->movieTitle);			//Create transaction from customer pointer object and movie pointer object
				cout << "Transaction Created" << endl;										//Notifying user that transaction was successfully created
				transactions.push_back(t);													//push new transactions to the vector
				cout << t;																	//Print the transaction for the user
				cout << "New Transaction added to Vector" << endl;							//Notify user of success
				mp->copiesAvailable--;														//Decrement the copiesAvailable member
				cout << "Copies Available After: " << mp->copiesAvailable << endl;			//Update User how many movies are left
			}
			else
			{
				cout << "Movie is not available for rent" << endl;
			}
		}
	}
	else if(information.substr(9, 1) == "D")
	{
		cout << "Borrowing A Drama" << endl;
		string action;
		string customerID;
		string mediaType;
		string movieType;
		string director;
		string movieTitle;

		stringstream ss(information);
		ss >> action >> customerID >> mediaType >> movieType;
		getline(ss >> ws, director, ',');
		getline(ss >> ws, movieTitle, ',');

		if(dramaMovieAuthentication(action, customerID, mediaType, movieType, director, movieTitle))
		{
			cout << "drama Movie Authenticated" << endl;
			Movie* mp = &findDramaMovie(director, movieTitle);
			cout << "Movie Found: " << "Title: " << mp->getMovieTitle() << " Director: " << mp->getDirector() << " " << " Year: " << mp->getMovieYear() << endl;
			if (mp->copiesAvailable > 0)
			{
				customer* cp = &findCustomer(customerID);								//Find and return customer object
				transaction t(action, cp->idNumber, mp->movieType, mp->movieTitle);		//Create transaction from customer pointer object and movie pointer object
				cout << "--------Transaction created--------" << endl;					//Notifying user that transaction was successfully created
				cout << t;																//Print out transaction for user
				transactions.push_back(t);												//Push transaction into vector
				cout << "Transaction Added" << endl;									//Notify user of success
				mp->copiesAvailable--;													//Decrement copies available
				cout << "Copies Available After: " << mp->copiesAvailable << endl;		//Notify user of updated copies
			}
			else
			{
				cout << "Movie is not available for rent" << endl;
			}
		}
	}
	else if(information.substr(9, 1) == "C")
	{
		cout << "Borrowing A Classic Movie" << endl;
		string action;
		string customerID;
		string mediaType;
		string movieType;
		string releaseMonth;
		string releaseYear;
		string majorActor;

		stringstream ss(information);
		ss >> action >> customerID >> mediaType >> movieType >> releaseMonth >> releaseYear;
		getline(ss >> ws, majorActor);
		
		if(classicMovieAuthentication(action, customerID, mediaType, movieType))
		{
			cout << "Classic Movie Authenticated" << endl;
			Movie* mp = &findClassicMovie(majorActor, releaseYear);
			cout << "Movie Found: " << "Name: " << mp->getMovieTitle() << " Director: " << mp->getDirector() << " Year: " << ((classicMovie*)mp)->getMovieYear() << " Major Actor: " << ((classicMovie*)mp)->getMajorActor() << endl;
			
			if (mp->copiesAvailable > 0)
			{
				customer* cp = &findCustomer(customerID);
				transaction t(action, cp->idNumber, mp->movieType, mp->movieTitle);
				cout << "Transaction Created" << endl;
				transactions.push_back(t);
				mp->copiesAvailable--;
				cout << "Copies Available After: " << mp->copiesAvailable << endl;
			}
			else
			{
				cout << "Movie is not available for rent" << endl;
			}
		};
	}
	else
	{
		cout << "This media genre is incorrect" << endl;
	}
	
}

/*
 * Responsible for all processing of returns
 */
void inventory::returnMovie(string information)
{

	if (information.at(9) == 'F')
	{
		cout << "Returning A Comedy Movie" << endl;
		string action;
		string customerID;
		string mediaType;
		string movieType;
		string movieTitle;
		string movieYear;

		stringstream ss(information);
		ss >> action >> customerID >> mediaType >> movieType;
		getline(ss >> ws, movieTitle, ',');
		ss >> movieYear;
		
		if(comedyMovieAuthentication(action, customerID, mediaType, movieType, movieTitle))
		{
			//cout << "Comedy Movie Authenticated" << endl;
			Movie* mp = &findComedyMovie(movieTitle);
			cout << "Movie Found is: " << mp->movieTitle << ", " << "Director: " << mp->director << "Year: " << mp->movieYear << endl;
			customer* cp = &findCustomer(customerID);
			transaction t(action, cp->idNumber, mp->movieType, mp->movieTitle);
			//cout << "Transaction Created" << endl;
			transactions.push_back(t);
			mp->copiesAvailable++;
			cout << "Copies Available After: " << mp->copiesAvailable << endl;
		}
	}
	else if (information.at(9) == 'D')
	{
		cout << "Returning A Drama Movie" << endl;
		string action;
		string customerID;
		string mediaType;
		string movieType;
		string director;
		string movieTitle;

		stringstream ss(information);
		ss >> action >> customerID >> mediaType >> movieType;
		getline(ss >> ws, director, ',');
		getline(ss >> ws, movieTitle, ',');

		
		if(dramaMovieAuthentication(action, customerID, mediaType, movieType, director, movieTitle))
		{
			cout << "Drama Movie Authenticated" << endl;
			Movie* mp = &findDramaMovie(director, movieTitle);
			cout << "Movie Found is: " << mp->movieTitle << ", " << "Director: " << mp->director << "Year: " << mp->movieYear << endl;
			customer* cp = &findCustomer(customerID);
			transaction t(action, cp->idNumber, mp->movieType, mp->movieTitle);
			cout << "Transaction Created" << endl;
			transactions.push_back(t);
			mp->copiesAvailable++;
			cout << "Copies Available After: " << mp->copiesAvailable << endl;
		}
	}
	else if (information.at(9) == 'C')
	{
		cout << "Returning A Classic Movie" << endl;
		string action;
		string customerID;
		string mediaType;
		string movieType;
		string releaseMonth;
		string releaseYear;
		string majorActor;

		stringstream ss(information);
		ss >> action >> customerID >> mediaType >> movieType >> releaseMonth >> releaseYear;
		getline(ss >> ws, majorActor);

		
		if (classicMovieAuthentication(action, customerID, mediaType, movieType))
		{
			cout << "Classic Movie Authenticated" << endl;
			Movie* mp = &findClassicMovie(majorActor, releaseYear);
			cout << "Movie Found is: " << mp->movieTitle << ", " << "Director: " << mp->director << "Year: " << mp->movieYear << "Major Actor: "  << ((classicMovie*)mp)->getMajorActor() << endl;
			if ((mp->getCopiesAvailable()) > 0)
			{
				customer* cp = &findCustomer(customerID);
				transaction t(action, cp->idNumber, mp->movieType, mp->movieTitle);
				cout << "Transaction Created" << endl;
				transactions.push_back(t);
				mp->copiesAvailable--;
				cout << "Copies Available After: " << mp->copiesAvailable << endl;
			}
			else
			{
				cout << "Movie is not available for rent" << endl;
			}
		};
	}
	else
	{
		cout << "This media genre is incorrect" << endl;
	}
}


/*
 * Responsible for destructing the m
 */
inventory::~inventory()
{

	//cout << "Inventory Destructor Called" << endl;

	for (size_t i = 0; i < movies.size(); i++)
	{
		delete movies.at(i);
	}

	//cout << "Inventory Destructor Finished" << endl;
}

void inventory::buildInventory(ifstream& movieFile, ifstream& customerFile)
{

	string line;	//Create variable to store strings coming out of data4movies file

	//While movieFile has lines to get, get them and assign to line variable
	while (getline(movieFile, line))
	{
		//Creating an in String Stream to convert the
		// the movieStock string into an integer
		istringstream iss(line);

		//Global Variables
		string movieType;
		string stockString;
		int movieStock;
		string director;
		string movieTitle;

		//input from the in String Stream up till the comma and
		//assign string to movieType
		getline(iss, movieType, ',');
		
		//input from the in String Stream up till the comma and
		//assign string to stockString to convert
		getline(iss >> ws, stockString, ',');

		//convert stockString to an int and assign it
		//to movieStock
		movieStock = stoi(stockString);
		
		//input from the in String Stream up till the comma and
		//assigns string to the director
		getline(iss >> ws, director, ',');

		//input from the in String Stream up till the comma and
		//assigns string to the movieTitle
		getline(iss >> ws, movieTitle, ',');
		//input from the in String Stream up till the comma and
		//assigns string to the director

		//If the movie type is D or F, then store the remaining movieYear data and then create the movie object and push it back into the vector
		if (movieType == "D" || movieType == "F")
		{
			
			string movieYear;
			getline(iss >> ws, movieYear);
			Movie* newMovie = new Movie(movieType, movieStock, director, movieTitle, movieYear);
			movies.push_back(newMovie);
			moviesHash.insert(movieTitle, movies.size() - 1);

		}
		//If the movie type is C, then store the majorActor name and the release month and year and then create a new movie object and push it back into the
		//movie vector along with updateing the hashtable
		else if(movieType == "C")
		{
			string firstName;
			string lastName;

			getline(iss >> ws, firstName, ' ');
			getline(iss >> ws, lastName, ' ');
			string majorActor = firstName + " " + lastName;
			
			string releaseMonth;
			getline(iss >> ws, releaseMonth, ' ');

			string movieYear;
			getline(iss >> ws, movieYear, ' ');

			Movie* newMovie = new classicMovie(movieType, movieStock, director, movieTitle, releaseMonth, movieYear, majorActor);
			movies.push_back(newMovie);
			moviesHash.insert(movieTitle, movies.size() - 1);
		}else
		{
			cout << "Not a valid movieType. Can not upload this moving into database" << endl;
			continue;
		}
	}

	int customerNumber;
	string customerName;

	//creating customer database
	while (customerFile >> customerNumber)
	{
		getline(customerFile >> ws, customerName);
		customer newCustomer(customerNumber, customerName);		//Creating new customer object
		customers.push_back(newCustomer);						//Pushing object to vector
	}

};

/*
 * Responsible for appropriatly processing each command by the text file
 */
void inventory::processCommands(ifstream& command)
{
	string line;
	while (getline(command, line))
	{
		cout << "*" << line << "*" << endl;
		switch (line[0])
		{
		case 'I':
			sortedInventoryPrintOut();
			break;

		case 'H':
			if (!customerAuthentication(line.substr(2, 4)))
			{
				cout << "Customer ID is not valid" << endl;
			}
			else
			{
				customerTransactionHistory(line[0], line.substr(2, 4));
			}
			break;

		case 'B':
			if (customerAuthentication(line.substr(2, 4)))
			{
				borrowMovie(line);
			}
			else
			{
				cout << "Customer ID is not valid" << endl;
			}
			break;

		case 'R':
			returnMovie(line);
			break;

		case 'P':
			cout << "Printing All Transactions" << endl;
			printTransactions();
			break;

		case 'X':

		default:
			cout << "Invalid Command" << endl;
		}

		cout << endl;
	}
};

