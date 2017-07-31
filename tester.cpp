#include "tester.h"
#include <assert.h>
#include "Controller.h" 
#include <vector>
#include <iostream>
#include <fstream>
#include "RepositoryException.h"
#include "CSVWatchlist.h"
void testRepo()
{
	Repository repo("readFilmTest.txt");
	int nr;
	/*test find*/
	Film f = Film("titlu2", "gen", 2000, 200, "trailer");
	repo.addFilm(f);
	std::vector<Film> v = repo.getFilms();
	assert(repo.find(f) == 4);

	Film f2 = Film("titlu3", "g", 10, 10, "tr2");
	assert(repo.find(f2) == -1);

	/*test finds*/
	f = Film("movie2", "genmovie", 2000, 200, "trailer");
	repo.addFilm(f);
	assert(repo.finds("movie2") == 5);
	assert(repo.finds("titlu3") == -1);

	/*test add*/
	std::string msg;
	f = Film("movie2", "genmovie", 2000, 200, "trailer");
	try
	{
		repo.addFilm(f);
	}
	catch (RepositoryException& ve)
	{
		msg = ve.what();
	}
	assert(msg == "There is another movie having this title!");


	/*test remove*/
	try
	{
		repo.removeFilm("movie");
	}
	catch (RepositoryException& rve)
	{
		msg = rve.what();
	}
	assert(msg == "The element does not exist!\n");


	/*test update*/
	f = Film{ "titlu499", "g", 20002, 2002, "trailerupdated" };
	try
	{
		repo.updateFilm(f);
	}
	catch (RepositoryException& ve)
	{
		msg = ve.what();
	}
	assert(msg == "The movie with this title does not exist!\n");

}


void testController()
{
	Repository repo("filmTest2.txt");
	Repository watch("filmTest2.txt");
	FileWatchList *p = new CSVWatchlist{};
	Controller ctrl(repo, p, FilmValidator{});

	/*test add*/
	std::string msg;
	Film f = Film("t", "g", 2000, 200, "trailer");
	try
	{
		ctrl.addFilm(f);
	}
	catch (ValidatorException& ve)
	{
		msg = ve.getMessage();
	}
	assert(msg == "The title should contain at least 3 characters\nThe genre should contain at least 3 characters!\n");

	ctrl.addFilm(Film{ "titlu4", "gen2", 20002, 2002, "trailer4" });
	f = Film{ "titlu4", "gen2", 20002, 2002, "trailer4" };
	try
	{
		ctrl.addFilm(f);
	}
	catch (RepositoryException& rve)
	{
		msg = rve.what();
	}
	assert(msg == "There is another movie having this title!");

	/*test remove*/
	try
	{
		ctrl.removeFilmCtrl("movie");
	}
	catch (RepositoryException& rve)
	{
		msg = rve.what();
	}
	assert(msg == "The element does not exist!\n");

	ctrl.removeFilmCtrl("titlu4");


	/*test update*/
	f = Film{ "titlu4", "g", 20002, 2002, "trailerupdated" };
	try
	{
		ctrl.updateFilmCtrl(f);
	}
	catch (ValidatorException& ve)
	{
		msg = ve.getMessage();
	}

	assert(msg == "The genre should contain at least 3 characters!\n");


	f = Film{ "movie4", "genreupdated", 20002, 2002, "trailerupdated" };
	try
	{
		ctrl.updateFilmCtrl(f);
	}
	catch (RepositoryException& rve)
	{
		msg = rve.what();
	}
	assert(msg == "The movie with this title does not exist!\n");


	ctrl.addFilm(f);
	ctrl.updateFilmCtrl(f);

	f = Film{ "movie", "genre", 5874, 2011, "trailerr" };
	ctrl.addWatch(f);

	ctrl.removeFilmCtrlWatch("movie");
}

void testFilmValidator()
{
	Film f = Film("t", "g", 2000, 200, "trailer");
	std::string msg;
	try
	{
		FilmValidator v;
		v.validate(f);
	}
	catch (ValidatorException& ve)
	{
		msg = ve.getMessage();
	};
	assert(msg == "The title should contain at least 3 characters\nThe genre should contain at least 3 characters!\n");
}

void testFilm()
{
	Film f = Film("filmname", "genre", 2000, 200, "trailer");
	assert(f.getNrLikes() == 200);
	assert(f.getYear() == 2000);

	Film f2 = Film("filmname", "genre", 2000, 200, "trailer");
	assert(f == f2);
	Film f3 = Film("f", "genre", 2000, 200, "trailer");
	assert(!(f == f3));

	Film m{};
	std::ifstream g("");
}

void testTokenize()
{
	Film f = Film();
	std::string line = "filmname genre 2000 200 trailer";
	std::vector < std::string > strs;
	strs.push_back("filmname");
	strs.push_back("genre");
	strs.push_back("2000");
	strs.push_back("200");
	strs.push_back("trailer");
	char d = ' ';
	assert(strs == f.tokenize(line, d));
}