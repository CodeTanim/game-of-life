/*
 * CSc103 Project 3: Game of Life
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours:
 */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdlib.h> // for exit();
#include <getopt.h> // to parse long arguments.
#include <unistd.h> // sleep
#include <vector>
using std::vector;
#include <string>
using std::string;
using namespace std;


static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM g`nerations and quit.\n"
"   --help,-h              show this message and exit.\n";

//Global Variables
size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename =  "/tmp/gol-world-current"; /* write state here */
FILE* fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current"; /* read initial state from here. */

//Function Prototypes
void initFromFile(vector<vector<bool> >&, vector<bool>&);
void print(vector<vector<bool> >&);
bool nbrcount(const vector<vector<bool> >& ,size_t, size_t);
void update(vector<vector<bool> >& oldgame, vector<vector<bool> >& newgame);
void mainLoop();
void dumpState(vector<vector<bool> >);


void initFromFile(vector<vector<bool> >& game, vector<bool>& line){
// read initial state from file and storing whatever is in it into vectors
/* open the file (for reading), storing the handle in f: */
FILE* f =fopen(initfilename.c_str(),"rb");
//initfilename is the file and it changes into c_str to become readable using c.
/* make sure file was opened properly: */
if (!f) {
	//in case file is not existance, it prints out an error message.
	cout << "invalid file. please find the right file." << endl;
    exit(1);
}
/* read a single character from the file: */
char c; // storage for the byte we'll read
while(fread(&c,1,1,f) != 0){
	//used to read the file and stores into vector for whatever is in it
	if (c=='O'){ //reading o and stores into vector
		line.push_back(true);
	}
	else if (c=='.'){ //reading . and stores into vector
		line.push_back(false);
	}
	else if (c=='\n') { //reading new line and stores into the main vector
		game.push_back(line); //everything done before gets stored into game so it's presentable
		line.clear(); //start from new so it could continue the loop
}
}
fclose(f); //finishes program
}


void print(vector<vector<bool> >& game){
// this will display the game any time it's called for
for(size_t i = 0; i < game.size(); i++) //get the row of the function to print out by looking at vector
{
	for (size_t j=0;j< game[i].size(); j++) //gets the column of the function for each line by looking into the vector of the vector
	if (game[i][j]) //if inside the vector is true then it prints out 'O'
		cout << "O";
	else
		cout << "."; //otherwise print out '.'
	cout << endl; //new line after finishing with one row because of the for loop
}
}



bool nbrCount(const vector<vector<bool> >& game,const int i,const int j){
//-this functions counts the neighbors and if the cell original cell should be alive, it returns true.
int count= 0;
size_t toptest = i-1; //-the (top) row number of the cell that we want to test
size_t bottest = i + 1; //-the (bottom) row number of the cell that we want to test
size_t columntest = j-1; //-the column number of the cell that we want to test

for (size_t topcount=0;topcount< 3;topcount++){ //- Tests the cells in the top (above the original cell) row, for 3 consecutive columns
		if (toptest == (size_t) -1) //- Looping the Grid (Torus): at the very top row
		toptest=game.size() - 1;
		if (columntest== (size_t)-1){ //- Looping the Grid (Torus): at the very left column
			int temp = game[i].size() - 1;
			if (game[toptest][temp]==true) //- Testing if cell is alive
				count++; //- adds a count to the total number of alive cells
		}
		else if (columntest == game[i].size()){ //- Looping the Grid (Torus): at the very right column
			if (game[toptest][0]==true) //- Testing if cell is alive
				count++; //- adds a count to the total number of alive cells
		}
		else {
			if (game[toptest][columntest]==true) //- General testing if not a special case near the edges
				count++; //- adds a count to the total number of alive cells
		}

columntest++; //- Tests the cells in the next column for 3 columns total
}

columntest = j-1;
for (size_t midcount=0;midcount<2;midcount++){ //- Tests the cells in the middle (same row as the original cell) row, for 2 columns
	size_t midtest = i;
		if (columntest== (size_t) -1){ //- Looping the Grid (Torus): at the very left column
			size_t temp = game[i].size() - 1;
			if (game[midtest][temp]==true) //- Testing if cell is alive
				count++; //- adds a count to the total number of alive cells
		}
		else if (columntest == game[i].size()){ //- Looping the Grid (Torus): at the very right column
			if (game[midtest][0]==true) //- Testing if cell is alive
				count++; //- adds a count to the total number of alive cells
		}
		else {
			if (game[midtest][columntest]==true) //- General testing if not a special case near the edges
				count++; //- adds a count to the total number of alive cells
		}
columntest= columntest + 2; // testing for 1 more column that is 2 units away
}
columntest = j-1;
for (size_t botcount=0;botcount<3;botcount++){ //- Tests the cells in the bottom (below the original cell) row, for 3 consecutive columns
	if(bottest == game.size()){ //- Looping the Grid (Torus): at the very bottom row
		bottest= 0;
	}
		if (columntest== (size_t) -1){ //- Looping the Grid (Torus): at the very left column
			size_t temp = game[i].size() - 1;
			if (game[bottest][temp]==true) //- Testing if cell is alive
				count++; //- adds a count to the total number of alive cells
		}
		else if (columntest == game[i].size()){ //- Looping the Grid (Torus): at the very right column
			if (game[bottest][0]==true) //- Testing if cell is alive
				count++; //- adds a count to the total number of alive cells
		}
		else {
			if (game[bottest][columntest]==true) //- General testing if not a special case near the edges
				count++; //- adds a count to the total number of alive cells
		}
columntest++; //- Tests the cells in the next column for 3 columns total
}
//- Finished checking all the neighbors and added up the count of alive neighbors
if (game[i][j] == true){
	if(count == 2|| count == 3)
	return true; // Keep the original cell alive if 2 or 3 cells are alive
else
	return false;
}
else {
	if(count == 3) // Bringing a dead original cell ALIVE if 3 neighbors are next to it
		return true;
	else
		return false;
}
}




void update(vector<vector<bool> >& oldgame, vector<vector<bool> >& newgame){
// transform the old version of the world into the new one
//start all over again and tranfer the new to the old
	for(size_t i=0;i<oldgame.size();i++){ //reads the vector of i row
	for(size_t j=0;j<oldgame[i].size();j++){ //reads the vector of j column
		newgame[i][j] =  nbrCount(oldgame,i,j);//Take the previous function and do a neighbor count from the old game, and create the new game.

}
}
for(size_t i=0;i<oldgame.size();i++){ //reads the vector of the i row
	for(size_t j=0;j<oldgame[i].size();j++){ // reads the vector of the j column
		oldgame[i][j] = newgame[i][j];// Does the same thing above by creating a loop
}
}
}

void dumpState(vector<vector<bool> > newgame){
// write the state to a file
/* Open the file (for writing), storing the handle in f: */

FILE* f = fopen(wfilename.c_str(),"wb");

/* Write a single character to the file: */
	bool b;
	char c;
	char n = '\n';

	for (size_t i = 0; i<newgame.size(); i++){
	for(size_t j=0;j<newgame[i].size();j++){
		b = newgame[i][j];
		if (b == 0)  c = '.';
		else if (b == 1) c = 'O';
		fwrite(&c, 1, 1, f);
	}
	fwrite(&n, 1, 1, f);
	}
/* close f when done: */
fclose(f);
}

void mainLoop(){
// update state, write state, sleep, repeat...
vector<vector<bool> > oldgame; //declares the game
vector<vector<bool> > newgame; //declares the changed game
vector<bool> line; //declare line to make lines based off reading
initFromFile(oldgame,line); //gets data and line of the file, declaring of oldgame
initFromFile(newgame,line); //gets file and line of the file, declaring new game, should be the same as above
if (max_gen == 0) //uses max gen for the -s function as it always prints and updates
		while (max_gen == 0){ //when maxgen is set to zero it runs the loop over and over again.
		printf("%s",string(100,'\n').c_str());
		print(oldgame); //starts off with the original and gets updated later
		cout << endl; //next line :D
		update(oldgame,newgame); //updates it with the newgame
		sleep(1); //set a delay
}
else if (max_gen != 0) {
		for (size_t generation=0 ; generation < (size_t) max_gen ; generation++){ //gets the input for max gen base on -f number and prints out that specific generation
		update(oldgame,newgame); //updates it with the newgame
		}
		print(newgame); //starts off with original and gets updated later
		dumpState(newgame);
}
}



int main(int argc, char *argv[]) {
	// define long options
	static struct option long_opts[] = {
		{"seed",    required_argument, 0, 's'},
		{"world",   required_argument, 0, 'w'},
		{"fast-fw", required_argument, 0, 'f'},
		{"help",    no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case 's':
				initfilename = optarg; /*  ./gol -s myfile ==> optarg = "myfile" */
				break;
			case 'w':
				wfilename = optarg;
				break;
			case 'f':
				max_gen = atoi(optarg);
				break;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	mainLoop();
	return 0;
}