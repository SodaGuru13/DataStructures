// CSC 300 Fall 2020
/*
 - C++ class for introducing graphs & graph algorithms
 - for simplification, we have the following restrictions:
    - less than 100 nodes
    - no self edges
    - all graph description files will be weighted
    - all weights > 0

 - node order
    print out the nodes, on 1 line, in the order dictated by algorithm
 - spanning tree
    print out edges     start-end   in the order dictated by algorithm



Graph Description File format
  Number of Nodes
  Number of Edges
  Source  Destination  Weight     [ for each edge ] 

*/
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class graph
{
	public:
		int i;
		int *nodes;
		int *edges;
		int **arr;
		graph();
		graph( int n );              // constructor, x is # of nodes
		graph( int n, int e );       // constructor, n is # of nodes	
                                     //              e is # of edges
		//void bfs( int x );           // breadth-first node order
		//void bfssp( int x );         // breadth-first spanning tree
		//void dfs( int x );           // depth-first node order
		//void dfssp( int x );         // depth-first spanning tree
		void mprint();               // print representation 
		void fill( ifstream& file ); // fill graph from data file
               // file is open;pay attention to read before & in 
	private:
};


graph::graph()
{
	nodes = new int[100];
	arr = new int*[100];
	for(i = 0; i < 100; i++)
		arr[i] = new int[100];
	return;
}
graph::graph( int n )
{
	nodes = new int[n];
	arr = new int*[n];
	for(i = 0; i < n; i++)
		arr[i] = new int[n];
	return;
}
graph::graph( int n, int e )
{
	nodes = new int[n];
	for(i = 0; i < n; i++)
		nodes[i] = i+1;
	edges = new int[e];
	arr = new int*[n];
	for(i = 0; i < n; i++)
		arr[i] = new int[n];
	return;
}
void graph::mprint()
{
	int j, l;
	for(l = 0; l < i; l++)
	{
		cout << setw(4) << nodes[l];
	}
	cout << endl;
	for(j = 0; j < i; j++)
	{
		cout << setw(4) << nodes[j];
		for(l = 0; l < i; l++)
		{
			cout << setw(4) << arr[j][l];
		}
		cout << endl;
	}
}
void graph::fill( ifstream& file )
{
	int n1, n2, w, j, l;
	for(j = 0; j < i; j++)
	{
		for(l = 0; l < i; l++)
		{
			arr[j][l] = 0;
		}
	}
	file >> n1 >> n2 >> w;
	while(!file.eof())
	{
		cout << "First: " << n1-1 << "Second: "<< n2-1;
		--n1;
		--n2;
		arr[n1][n2] = w;
		arr[n2][n1] = w;
		file >> n1 >> n2 >> w;
	}
}

int main( int argc, char *argv[] )
{
	int size, numnode, numedge;
	int location;
	ifstream ifp;

	//checking to see if file was entered on command line
	if ( argc != 2 )
	{
		cout << "File was not entered\n";
		return 2;
	}

	ifp.open( argv[1] );

	// checking to see if file was opened successfully
	if( ! ifp.is_open() )
	{
		cout << "File could not be opened\n";
		return 3;
	}
	// reading in number of nodes
	ifp >> numnode;
	cout << numnode;
	// reading in number of edge 
	ifp >> numedge;
	cout << numedge;
	//create graph with an an adjadceny matrix of 
    // size = num of nodes x num of nodes
	// array can be bigger if needed so you can make it work
	graph g( numnode, numedge );
	//fill adjacency matrix
	g.fill( ifp );
	//print the matrix
	g.mprint();
	cout << endl << endl;

	/*
	//ask for starting location
	cout << "Enter the starting location: ";
	cin >> location;

	// calculate DFS
	g.dfs( location );
	cout << endl << endl;

	//calculate DFS-SP
	g.dfssp( location );
	cout << endl << endl;

	//calculate BFS
	g.bfs( location );
	cout << endl << endl;

	//calculate BFS-SP
	g.bfssp( location );
	cout << endl << endl;

	*/

	return 0;
}
