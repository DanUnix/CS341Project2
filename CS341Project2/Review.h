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

using std::string;

class Review
{
public:
	Review();			// Review Constructor
	~Review();			// Review Destructor
	int movieID;		//; Movie ID for this review
	int userID;			// User ID
	int rating;			// an integer vaule in the range 1..5, inclusive
	string reviewDate;	// The date of the review

	Review(int movie_id, int user_id, int user_rating, string review_date)
		: movieID(movie_id), userID(user_id), rating(user_rating), reviewDate(review_date)
	{ }
	
};

