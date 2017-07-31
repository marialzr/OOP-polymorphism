# OOP-polymorphism and UML-MovieStore

So many movies, so little time… To make sure you do not miss any good movies, you absolutely need a
software application to help you manage your films and create watch lists. The application can be used
in two modes: administrator and user. When the application is started, it will offer the option to choose
the mode.
Administrator mode: The application will have a database, which holds all the movies. You must be
able to update the database, meaning: add a new movie, delete a movie and update the information of
a movie. Each Movie has a title, a genre, a year of release, a number of likes and a trailer. The trailer is
memorised as a link towards an online resource. The administrators will also have the option to see all
the movies in the database.
User mode: A user can create a watch list with the movies that he wants to watch. The application will
allow the user to:

a. See the movies in the database having a given genre (if the genre is empty, see all the
movies), one by one. When the user chooses this option, the data of the first movie (title,
genre, year of release, number of likes) is displayed and the trailer is played in the browser.
b. If the user likes the trailer, he/she can choose to add the movie to his/her watch list.
c. If the trailer is not satisfactory, the user can choose not to add the movie to the watch list
and to continue to the next. In this case, the information corresponding to the next movie is
shown and the user is again offered the possibility to add it to the watch list. This can
continue as long as the user wants, as when arriving to the end of the list of movies with the
given genre, if the user chooses next, the application will again show the first movie.
d. Delete a movie from the watch list, after the user watched the movie.
e. See the watch list.  Store your movie watch listin a file. When the application starts, the user should choose the type of file (CSV or HTML). Depending on this type, the application should save the list in the correct format. Add a new command, allowing the user to see the movie watch list.
Displaying the list means opening the saved file (csv or html) with the correct application:
- CSV file – with Notepad, Notepad++, Microsoft Excel or OpenOffice Calc
- HTML file – with a browser


The application provides a UML diagram for your entire application.
All code is tested.
