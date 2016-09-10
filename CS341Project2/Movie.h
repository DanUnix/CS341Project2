//
// Netflix Movie Review Analysis
//
// <<Daniel Pulley>>
// U. of Illinois, Chicago
// CS341, Fall 2016
// HW #02
//

#pragma once
#include <string>
#include <vector>

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
	double avg;			// The average rating
	int nreviews;		// Used to calculate number of reviews
	int num_of_reviews[5];
	Movie(int movie_id, string movie_name, int publish_year, double my_avg, int my_review)
		: movieID(movie_id), movieName(movie_name), publishYear(publish_year), avg(my_avg), nreviews(my_review)
	{ }
};
/* End of Movie Class */

