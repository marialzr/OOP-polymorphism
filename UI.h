#pragma once
#include "Controller.h"
//#include "RepositoryException.h"
class UI
{
private:
	Controller _ctrl;
	

public:
	//UI(const Controller& ctrl);
	//UI();
	UI(const Controller& c) : _ctrl(c) {};
	void printMenu();
	void printAdmin();
	void printUser();
	void printPlayListMenu();
	void printFilms();
	//void printWatchList();
	Film readFilm();
	void adminAdd();
	void adminRemove();
	void userRemove();
	void adminUpdate();
	void saveWatchlistToFile();
	void seeTheMoviesByGenre();
	void adminMode();
	void userMode();
	void run();
};