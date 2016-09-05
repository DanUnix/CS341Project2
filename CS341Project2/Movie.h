#pragma once
#include <string>

// To use string
using std::string;

/* Movie Class */
class Movie
{
public:
	Movie();			// Constructor
	~Movie();			// Destructor 
	int movieID;		// ID of Movie
	string movieName;	// Name of Movie
	int publishYear;	// Year movie was published

	Movie(int movieid, string moviename, int publishyear)
		: movieID(movieid), movieName(moviename), publishYear(publishyear)
	{ }
};
/* End of Movie Class */

