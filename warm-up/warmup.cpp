#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <stdio.h>
#include <cstdlib>

void futureworld(vector<vector<int> > &world) {

	 for (size_t n = 0; n < world.size(); n++) {
	for( size_t l = 0; l < world[0].size(); l++) {

	if(world[n][l] == 0) {

		cout << ".";
	}
		else {

			cout << "O";
		}
	}
	cout << endl;
}

}

/*conditions for game of life:

if a live cell has fewer than 2 neigbors, it dies (underpopulation)

if a live cell has more than 3 neigbors, it dies  (overpopulation)

if a dead cell has exactly 3 neigbors, it becomes alive (reproduction)


*/
/* make future a copy of world. */
	/* NOTE: the vector 'world' above corresponds to the contents
	 * of ../res/tests/0.  TODO: apply the rules to the vector,
	 * write the result to standard output, and compare with the
	 * contents of ../tests/1. */

int main(int argc, char *argv[])



{


   vector<vector<int> > world = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


	vector<vector<int> > future = {
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

	int x = atoi(argv[1]);



	for (int i = 0; i < x; i++) {

// use proper syntax to initialize rows and columns
	size_t rows = world.size() ;

 size_t columns = world[0].size();


// set rows and columns to proper syntax


// iterate through the rows and columns
	for (size_t j = 0; j < rows; j++ ) {


		for (size_t k = 0; k < columns; k++) {


int count = 0;


			count = count + world[(rows + j - 1)%(rows)][(columns + k - 1)%(columns)] + // top left


world[(rows + j + 1)%(rows)][(columns + k + 1)%(columns)] +  //bottom right

			world[(rows + j + 1)%(rows)][(columns + k - 1)%(columns)] +  //bottom left

			world[(rows + j )%(rows)][(columns + k + 1)%(columns)] +    // right

			world[(rows + j )%rows][(columns + k - 1)%(columns)] +  // left

			world[(rows + j - 1)%(rows)][(columns + k)%(columns)] +  // up

			world[(rows + j -1)%rows][(columns + k + 1)%(columns)] +  // top right

			world[(rows + j +1)%(rows)][(columns + k)%(columns)]; // down


             if ( (world[j][k] == 0) && (count == 3)) {

              future[j][k] = 1; //alive

            }

               else if ( (world[j][k] == 1) && (count < 2)) {

									future[j][k] = 0; //dead

}

									else if((world[j][k] == 1) && (count > 3)) {

	                   future[j][k] = 0; //dead

}
                    else
                  {
                      	future[j][k] = world[j][k]; // Everything else stays the same.

										}

	}

}




world = future;


}


// Displays the future generation of cells
futureworld(world);



	return 0;
}






