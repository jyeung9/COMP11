

#include <iostream>
using namespace std;

struct cell_coord {
	int row;
	int col;
};

struct cell_coord dummy ()
{
	struct cell_coord blah = {3, 5};
	return blah;
}

int main ()
{
	struct cell_coord receive; 
	receive = dummy ();
	cout << receive.row << " " << receive.col << endl;
}

