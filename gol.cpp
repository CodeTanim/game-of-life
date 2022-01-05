// CSc103 Project 3: Game of Life

#include <iostream>

#include <fstream>

#include <cstdio>

#include <stdlib.h> // for exit();

#include <getopt.h> // to parse long arguments.

#include <unistd.h> // sleep

#include <vector>

using std::vector;#include <string>

using std::string;
using namespace std;

static
const char * usage =
  "Usage: %s [OPTIONS]...\n"
"Text-based version of Conway's game of life.\n\n"
"   --seed,-s     FILE     read start state from FILE.\n"
"   --world,-w    FILE     store current world in FILE.\n"
"   --fast-fw,-f  NUM      evolve system for NUM g`nerations and quit.\n"
"   --help,-h              show this message and exit.\n";

//Global Variables
size_t max_gen = 0; /* if > 0, fast forward to this generation. */
string wfilename = "/tmp/gol-world-current"; /* write state here */
FILE * fworld = 0; /* handle to file wfilename. */
string initfilename = "/tmp/gol-world-current"; /* read initial state from here. */

//Function Prototypes
void initFromFile(vector < vector < bool > > & , vector < bool > & );
void print(vector < vector < bool > > & );
bool nbrcount(const vector < vector < bool > > & , size_t, size_t);
void update(vector < vector < bool > > & oldgame, vector < vector < bool > > & newgame);
void mainLoop();
void dumpState(vector < vector < bool > > );

void initFromFile(vector < vector < bool > > & game, vector < bool > & line) {
  // read initial state from file and storing whatever is in it into vectors
  /* open the file (for reading), storing the handle in f: */
  FILE * f = fopen(initfilename.c_str(), "rb");
  //initfilename is the file and it changes into c_str to become readable using c.
  /* make sure file was opened properly: */
  if (!f) {
    //in case file is not existance, it prints out an error message.
    cout << "FILE INVALID!. Please find the right file." << endl;
    exit(1);
  }
  /* read a single character from the file: */
  char c; // storage for the byte we'll read
  while (fread( & c, 1, 1, f) != 0) {
    //used to read the file and stores into vector for whatever is in it
    if (c == 'O') { //reading o and stores into vector
      line.push_back(true);
    } else if (c == '.') { //reading . and stores into vector
      line.push_back(false);
    } else if (c == '\n') { //reading new line and stores into the main vector
      game.push_back(line); //everything done before gets stored into game so it's presentable
      line.clear(); //start from new so it could continue the loop
    }
  }
  fclose(f); //finishes program
}

void print(vector < vector < bool > > & game) {
  // this will display the game any time it's called for
  size_t rows = game.size();
  size_t columns = game[0].size();
  for (size_t i = 0; i < rows; i++) { //get the row of the function to print out by looking at vector
    for (size_t j = 0; j < columns; j++) { //gets the column of the function for each line by looking into the vector of the vector
      if (game[i][j]) //if inside the vector is true then it prints out 'O'
        cout << "O";
      else
        cout << "."; //otherwise print out '.'
    }
    cout << endl; //new line after finishing with one row because of the for loop
  }

}

void update(vector < vector < bool > > & game, vector < vector < bool > > & newgame) {
  // transform the old version of the world into the new one
  //start all over again and tranfer the new to the old

  size_t rows = game.size();

  size_t columns = game[0].size();

  for (size_t j = 0; j < rows; j++) {

    for (size_t k = 0; k < columns; k++) {

      int count = 0;

      count = count + game[(rows + j - 1) % (rows)][(columns + k - 1) % (columns)] + // top left

       		      game[(rows + j + 1) % (rows)][(columns + k + 1) % (columns)] + // bottom right

        	      game[(rows + j + 1) % (rows)][(columns + k - 1) % (columns)] + // bottom left

        	      game[(rows + j) % (rows)][(columns + k + 1) % (columns)] + // right

        	      game[(rows + j) % rows][(columns + k - 1) % (columns)] + // left

        	      game[(rows + j - 1) % (rows)][(columns + k) % (columns)] + // up

       		      game[(rows + j - 1) % rows][(columns + k + 1) % (columns)] + // top right

        	      game[(rows + j + 1) % (rows)][(columns + k) % (columns)]; // down

      if ((game[j][k] == 0) && (count == 3)) {

        newgame[j][k] = 1; //alive

      } else if ((game[j][k] == 1) && (count < 2)) {

        newgame[j][k] = 0; //dead

      } else if ((game[j][k] == 1) && (count > 3)) {

        newgame[j][k] = 0; //dead
      } else {

        newgame[j][k] = game[j][k];
      }

    }

  }

  game = newgame;

}

void dumpState(vector < vector < bool > > newgame) {
  // write the state to a file
  /* Open the file (for writing), storing the handle in f: */

  FILE * f = fopen(wfilename.c_str(), "wb");

  /* Write a single character to the file: */
  bool b;
  char c;
  char n = '\n';

  for (size_t i = 0; i < newgame.size(); i++) {
    for (size_t j = 0; j < newgame[i].size(); j++) {
      b = newgame[i][j];
      if (b == 0) c = '.';
      else if (b == 1) c = 'O';
      fwrite( & c, 1, 1, f);
    }
    fwrite( & n, 1, 1, f);
  }
  /* close f when done: */
  fclose(f);
}

void mainLoop() {
  // update state, write state, sleep, repeat...
  vector < vector < bool > > game; //declares the game

  vector < vector < bool > > newgame; //declares the changed game

  vector < bool > line; //declare line to make lines based off reading

  initFromFile(game, line); //gets data and line of the file, declaring of oldgame

  initFromFile(newgame, line); //gets file and line of the file, declaring new game, should be the same as above

  if (max_gen == 0) { //uses max gen for the -s function as it always prints and updates
    while (max_gen == 0) { //when maxgen is set to zero it runs the loop over and over again.
      printf("%s", string(100, '\n').c_str());
      print(game); //starts off with the original and gets updated later
      cout << endl; //next line :D
      update(game, newgame); //updates it with the newgame
      usleep(200000); //set a delay
    }
  } else if (max_gen != 0) {
    for (size_t generation = 0; generation < (size_t) max_gen; generation++) { //gets the input for max gen base on -f number and prints out that specific generation
      update(game, newgame); //updates it with the newgame
    }
    print(newgame); //starts off with original and gets updated later
    dumpState(newgame);
  }
}

int main(int argc, char * argv[]) {
  // define long options
  static struct option long_opts[] = {
    {
      "seed",
      required_argument,
      0,
      's'
    },
    {
      "world",
      required_argument,
      0,
      'w'
    },
    {
      "fast-fw",
      required_argument,
      0,
      'f'
    },
    {
      "help",
      no_argument,
      0,
      'h'
    },
    {
      0,
      0,
      0,
      0
    }
  };
  // process options:
  char c;
  int opt_index = 0;
  while ((c = getopt_long(argc, argv, "hs:w:f:", long_opts, & opt_index)) != -1) {
    switch (c) {
    case 'h':
      printf(usage, argv[0]);
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
      printf(usage, argv[0]);
      return 1;
    }
  }
  mainLoop();
  return 0;
}
