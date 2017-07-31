#include "UI.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "RepositoryException.h"
#include "CSVWatchlist.h"
#include "HTMLWatchlist.h"
using namespace std;


void UI::printMenu()
{
	cout << "Available commands:\n";
	cout << "1-Administrator mode\n";
	cout << "2-User mode:\n";
	cout << "0-exit\n";
}

void UI::printAdmin()
{
	cout << "Available commands:\n";
	cout << "0-Back\n";
	cout << "1-Print movie\n";
	cout << "2-Add a movie\n";
	cout << "3-Remove a movie:\n";
	cout << "4-Update a movie:\n";
}

void UI::printUser()
{
	cout << "Possible commands:\n";
	cout << "0-Back\n";
	cout << "1-See movies by genre\n";
	cout << "2-Display playlist\n";
	cout << "3-Delete a movie from my watch list\n";
	cout << "4-Save playlist to file\n";
}

void UI::printPlayListMenu()
{
	cout << "Possible commands: " << endl;
	cout << "\t 1 - Add song." << endl;
	cout << "\t 2 - Play." << endl;
	cout << "\t 3 - Next." << endl;
	cout << "\t 0 - Back." << endl;
}


void UI::printFilms()
{
	vector<Film> dv = this->_ctrl.getRepo().getFilms();
	for (int i = 0; i < dv.size(); i++)
	{
		cout << "The movie is: " << dv[i].getTitle() << " " << dv[i].getGenre() << " " << dv[i].getNrLikes() << " " << dv[i].getYear() << "\n";
	}
}

Film UI::readFilm()
{
	string tit, genre, trailer;
	int year, nrlik;
	cout << "Give the title ";
	cin >> tit;
	cout << "Give the genre ";
	cin >> genre;
	cout << "Give year ";
	cin >> year;
	cout << "Give no of likes ";
	cin >> nrlik;
	cout << "Give trailer ";
	cin >> trailer;
	Film f = Film(tit, genre, year, nrlik, trailer);
	return f;
}


void UI::adminAdd()
{
	Film f = readFilm();
	try
	{
		this->_ctrl.addFilm(f);
		cout << "The movie was successfully added!\n";
	}
	catch (ValidatorException& e)
	{
		for (auto s : e.getMessage())
			cout << s;
	}
	catch (RepositoryException& e)
	{
		cout << e.what() << endl;
	}
	catch (FileException& e)
	{
		cout << e.what() << endl;
	}
}

void UI::adminRemove()
{
	cout << "Give the title of the movie\n";
	string name;
	cin >> name;
	try
	{
		this->_ctrl.removeFilmCtrl(name);
		cout << "The movie was succesfully removed\n";

	}
	catch (RepositoryException& ve)
	{
		std::string s = ve.what();
		cout << s;
	}
	catch (FileException& e)
	{
		cout << e.what() << endl;
	}
}

void UI::userRemove()
{
	cout << "Give the title of the movie\n";
	string name;
	cin >> name;

	this->_ctrl.removeFilmCtrlWatch(name);
	cout << "The movie was succesfully removed\n";
}

void UI::adminUpdate()
{
	cout << "Give movie to be updated\n";
	Film f = readFilm();

	try
	{
		this->_ctrl.updateFilmCtrl(f);
		cout << "The movie was successfully updated!\n";
	}
	catch (ValidatorException& e)
	{
		for (auto s : e.getMessage())
			cout << s;
	}
	catch (RepositoryException& e)
	{
		cout << e.what() << endl;
	}
	catch (FileException& e)
	{
		cout << e.what() << endl;
	}

}

void UI::saveWatchlistToFile()
{
	try
	{
		this->_ctrl.saveWatchlist();

		if (this->_ctrl.getWatchList() == nullptr)
		{
			cout << "Playlist cannot be displayed!\n" << endl;
			return;
		}
		cout << "The movies are stored!\n";
	}
	catch (FileException& e)
	{
		cout << e.what() << endl;
	}
}

void UI::seeTheMoviesByGenre()
{
	cout << "Give the genre of the movie ";
	string genre;
	cin >> genre;
	int n = 0;
	vector<Film> films = this->_ctrl.getByGenre(genre);
	int i = 0;
	Film f{};
	while (true)
	{
		UI::printPlayListMenu();
		int commandPlaylist{ 0 };
		if (i == films.size())
			i = 0;
		cout << "The movie has the title: " << films[i].getTitle()<<"\n";
		cout << "Input the command: ";
		cin >> commandPlaylist;
		cin.ignore();
		if (commandPlaylist == 0)
			break;
		switch (commandPlaylist)
		{
		case 1:
			try
			{
				this->_ctrl.addWatch(films[i]);
				i++;
				std::cout << "The movie was successfully added to your watch list\n";
			}
			catch (FileException& e)
			{
				cout << e.what() << endl;
			};
			break;
		case 2:
		{
			if (this->_ctrl.getWatchList()->isEmpty())
			{
				cout << "Nothing to play, the playlist is empty." << endl;
				continue;
			}
			this->_ctrl.startWatchlist();
			f = this->_ctrl.getWatchList()->getCurrentFilm();
			cout << "Now playing: " << f.getTitle() << endl;
			break;
		}
		case 3:
		{
			if (this->_ctrl.getWatchList()->isEmpty())
			{
				cout << "Nothing to play, the playlist is empty." << endl;
				continue;
			}
			this->_ctrl.nextMovieWatchlist();
			f = this->_ctrl.getWatchList()->getCurrentFilm();
			cout << "Now playing: " << f.getTitle() << endl;
			break;
		}
			}
		
		}
	}

void UI::adminMode()
{
	printAdmin();
	int cmd;
	cout << "Give the command:\n";
	cin >> cmd;
	if (cmd == 0)
		return;
	else if (cmd == 1)
		printFilms();
	else if (cmd == 2)
	{
		adminAdd();
	}
	else if (cmd == 3)
		adminRemove();
	else if (cmd == 4)
		adminUpdate();
	adminMode();
}

void UI::userMode()
{
	printUser();
	int cmd;
	cout << "Give the command:\n";
	cin >> cmd;
	if (cmd == 0)
		return;
	else if (cmd == 1)
		seeTheMoviesByGenre();
	else if (cmd == 2)
		this->_ctrl.openWatchlist();
	else if (cmd == 3)
		userRemove();
	else if (cmd == 4)
		this->saveWatchlistToFile();
	userMode();
}

void UI::run()
{
	cout << "With which type of file do you want to save your playlist?\n";
	cout << "1-CSV file\n";
	cout << "2-HTML file\n";
	int c;
	cin >> c;
	if (c == 1)
	{
		FileWatchList* fw = new CSVWatchlist{}; 
		this->_ctrl.setWatchList(fw);
	}
	else
	{
		FileWatchList* fw = new HTMLWatchlist{};
		this->_ctrl.setWatchList(fw);
	}

	std::string filename;
	cout << "Input the file name ";
	cin >> filename;
	this->_ctrl.setFileWatchList(filename);

	printMenu();
	int cmd;
	cout << "Give the command:\n";
	cin >> cmd;
	switch (cmd)
	{
	case 0:
		break;
	case 1:
		adminMode();
	case 2:
		userMode();
	default:
		run();
	}
}

