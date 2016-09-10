//
// Netflix Movie Review Analysis
//
// <<Daniel Pulley>>
// U. of Illinois, Chicago
// CS341, Fall 2016
// HW #02
//

// Preprocess Directives
#include <iostream>
#include <iterator>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include "Movie.h"
#include "Review.h"

// using namespace std
using std::string;
using std::ifstream;
using std::vector;
using std::map;
using std::pair;
using std::stringstream;
using std::getline;
using std::stoi;
using std::sort;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::count;

/*
 * inputMovies function
 * 
 * Function takes movie vector and then inputs data from movies CSV file into the vector
 */
void inputMovies(vector<Movie>& myMovie)
{
	// Open movie.csv file
	ifstream movie_file("movies.csv");


	// String values to get Movie statistics
	string line, movie_id, movie_name, publish_year, avg, num_reviews;
	avg = "0.0";
	num_reviews = "0";
	// Check if movies file exist, if not exit program
	if (!movie_file.good()) {
		cout << "Cannot open movie file!" << endl;
		cout << "Exiting Program!" << endl;
		return;
	}

	// Skip header
	getline(movie_file, line);

	while (getline(movie_file, line)) {

		// Use stringstream to help parse CSV file
		stringstream ss(line);

		// parse line:
		getline(ss, movie_id, ',');
		getline(ss, movie_name, ',');
		getline(ss, publish_year, ',');
		getline(ss, avg, ',');
		getline(ss, num_reviews);
		Movie M(stoi(movie_id), movie_name, stoi(publish_year),stoi(avg),stoi(num_reviews));

		// insert @ end
		myMovie.push_back(M);
	}
}
/* End of inputMovies File */

/*
* inputReviews function
*
* Function takes review vector and then inputs data from reviews CSV file into the vector
*/
void inputReviews(vector<Review>& myReview)
{
	// Open Review CSV file
	ifstream review_file("reviews.csv");


	// String values to get Movie statistics
	string line, movie_id, user_id, movie_rating, review_date;

	// Check if movies file exist, if not exit program
	if (!review_file.good()) {
		cout << "Cannot open review file!" << endl;
		cout << "Exiting Program!" << endl;
		return;
	}

	// Skip header
	getline(review_file, line);

	while (getline(review_file, line)) {

		// Use stringstream to help parse CSV file
		stringstream ss(line);

		// parse line:
		getline(ss, movie_id, ',');
		getline(ss, user_id, ',');
		getline(ss, movie_rating, ',');
		getline(ss, review_date);

		Review R(stoi(movie_id), stoi(user_id), stoi(movie_rating), review_date);

		// insert @ end
		myReview.push_back(R);
	}
}
/* End of inputReviews Function */

/*
 * topTenMovies Function
 * Function displays the top-10 movies (based on average rating)
 *
 */
void topTenMovies(vector<Movie>& myMovie, vector<Review>& myReview)
{
	
	cout << endl << ">> Top-10 Movies <<" << endl << endl;
	
	// Display top ten movies
	cout << "Rank" << "\t" << "ID" << "\t" << "Reviews" << "\t" << "Avg" << "\t" << "Name" << endl;
	
	for (Review& myR : myReview) {
		
		myMovie[myR.movieID - 1].avg += myR.rating;
		myMovie[myR.movieID - 1].nreviews++;
		myMovie[myR.movieID - 1].num_of_reviews[myR.rating - 1]++;
	}

	// Calculate the average rating for each movie listed
	for (Movie& myM : myMovie) {
		myM.avg = (myM.avg / myM.nreviews);
	}

	// Sort the average ratings
	sort(myMovie.begin(), myMovie.end(), [&](Movie a, Movie b) {
		
		return a.avg > b.avg;
	});

	for (auto i = 0; i < 10; ++i) {
		cout << i+1 << ".\t" << myMovie[i].movieID << "\t" << myMovie[i].nreviews << "\t" 
			<< myMovie[i].avg << "\t'" << myMovie[i].movieName << "'" << endl;
	}
}	
/* End of topTenMovies */

/*
 * topTenUsers Function
 * Display the top-10 users based on number of reviews submitted
 *
 */
void topTenUsers(vector<Movie>& myMovie, vector<Review>& myReview)
{
	cout << ">> Top-10 Users <<" << endl << endl;

	// Implement a map to put userIDs with Number of reviews together
	map<int, int> myUserReview;

	for (Review& myR : myReview)
		myUserReview[myR.userID]++;

	// user vector combination
	vector<pair<int, int>> myNewUserInfo(myUserReview.begin(), myUserReview.end());

	// Sort the new vector
	sort(myNewUserInfo.begin(), myNewUserInfo.end(), [&](pair<int, int> a, pair<int, int> b) {
		
		return (a.second > b.second);
	});

	cout << "Rank" << "\t" << "ID" << "\t" << "Reviews" << endl;
	for (auto i = 0; i < 10; ++i) {
		cout << i + 1 << ".\t" << myNewUserInfo[i].first << "\t" << myNewUserInfo[i].second << endl;
	}
}
/* End of topTenUsers */

/*
 * movieInformation Function
 * Interactive loop that allows the user to search by movie id.
 * If movie is found, output data about the movie
 */
void movieInformation(vector<Movie>& myMovie, vector<Review>& myReview)
{
	cout << ">> Movie Information <<" << endl << endl;

	// get movie ID from user
	int movie_id;

	// Sort movies by movieID
	sort(myMovie.begin(), myMovie.end(), [&](Movie a, Movie b) {
		
		return (a.movieID < b.movieID);
	});

	// Prompt User to enter a movieID to be searched
	cout << "Please enter a movie ID " << "[1.." << myMovie.size() << "], 0 to stop: ";
	cin >> movie_id;
	cout << endl;
	// Create while loop to for interactive loop that will stop when user inputs 0
	while (movie_id != 0) {
		// Condition - if user inputs a movie id greater than number of movies or less than 0 
		// Prompt them to try again
		if (movie_id > myMovie.size() || movie_id < 0)
			cout << "** Invalid movie id, please try again..." << endl;
		else {
			
			// Output the data of the movie depending on the inputted movie ID
			Movie selectedMovie = myMovie[movie_id - 1];	// Create new Movie object

			cout << "Movie:" << "\t\t'" << selectedMovie.movieName << "'" << endl;
			cout << "Year: " << "\t\t" << selectedMovie.publishYear << endl;
			cout << "Avg rating:" << "\t" << selectedMovie.avg << endl;
			cout << "Num reviews: " << "\t" << selectedMovie.nreviews << endl;
			cout << "Num 1's:" << "\t" << selectedMovie.num_of_reviews[0] << endl;
			cout << "Num 2's:" << "\t" << selectedMovie.num_of_reviews[1] << endl;
			cout << "Num 3's:" << "\t" << selectedMovie.num_of_reviews[2] << endl;
			cout << "Num 4's:" << "\t" << selectedMovie.num_of_reviews[3] << endl;
			cout << "Num 5's:" << "\t" << selectedMovie.num_of_reviews[4] << endl;
			
		}
		cout << endl;
		// Prompt User to enter a movieID to be searched again
		cout << "Please enter a movie ID" << "[1.." << myMovie.size() << "], 0 to stop: ";
		cin >> movie_id;
	} 

	
}
/* End of movieInformation*/
/* 
 * main Function 
 *
 */
int main()
{
	// Print Title of Program
	cout << "** Netflix Movie Review Analysis **" << endl << endl;
	
	// Create Movie vector to input movie data from file
	vector<Movie> movies;
	// Input movies into vector
	inputMovies(movies);
	// Create Review vector to input review data from file
	vector<Review> reviews;
	// Input reviews into vector
	inputReviews(reviews);
	
	// Display number of movies and number of reviews
	cout << ">> Reading movies... " << movies.size() << endl;
	cout << ">> Reading reviews... " <<  reviews.size() << endl;
	// Display top 10 movies based on average rating
	topTenMovies(movies,reviews);
	cout << endl;
	// Display top 10 users based on number of reviews
	topTenUsers(movies, reviews);
	cout << endl;

	// Movie Information
	movieInformation(movies, reviews);

	// Done
	cout << endl << endl << "** DONE! ** " << endl;
	system("PAUSE");
}
/* End of Main Function */