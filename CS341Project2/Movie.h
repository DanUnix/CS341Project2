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

	Movie(int movie_id, string movie_name, int publish_year)
		: movieID(movie_id), movieName(movie_name), publishYear(publish_year)
	{ }
};
/* End of Movie Class */

