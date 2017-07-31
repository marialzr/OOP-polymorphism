#include "main.h"
#include <crtdbg.h>
#include <iostream>
#include "CSVWatchlist.h"
#include "tester.h"
using namespace std;

void  main2()
{
	testRepo();
	testController();
	testFilmValidator();
	testFilm();
	testTokenize();
	/*
	Repository repo("readFilm.txt");
	FileWatchList *p = new CSVWatchlist{};
	Controller ctrl(repo, p, FilmValidator{});
	UI ui(ctrl);
	ui.run();
	delete p;*/
}

int main()
{
	main2();
	/*
	_CrtDumpMemoryLeaks();*/
	return 0;
}