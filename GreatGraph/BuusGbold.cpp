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
#include <climits>
using namespace std;

class graph
{
	public:
		int i;
		int numE;
		int *nodes;
		int *edges;
		int **arr;
		graph();
		graph( int n );              // constructor, x is # of nodes
		graph( int n, int e );       // constructor, n is # of nodes	
		void dijkstra(int startN);
        int findNodeIndex(int x);//              e is # of edges
		void bfs( int x );           // breadth-first node order
		void bfssp( int x );         // breadth-first spanning tree
		void dfs( int x );
		void dfs(int *mark, int x);           // depth-first node order
		void dfssp( int x );
		void dfssp(int *mark, int x);         // depth-first spanning tree
		void mprint();               // print representation 
		void fill( ifstream& file );
		 // fill graph from data file
               // file is open;pay attention to read before & in 
		void	End(int A[], int *sz, int val);
		int	Begin(int A[], int *sz);
		void prim(int startN);
		int isIn(int A[], int sz, int val);
		int indexOfElement(int A[], int sz, int val);
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
	e *= 3;
	edges = new int[e];
	numE = e;
	for(i = 0; i < e; i++)
		edges[i] = 0;
	arr = new int*[n];
	for(i = 0; i < n; i++)
		arr[i] = new int[n];
	return;
}
void graph::mprint()
{
	int j, l;
	cout << "    ";
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
	int n1, n2, w, j, l, r;
	r = 0;
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
		arr[n1-1][n2-1] = 1;
		arr[n2-1][n1-1] = 1;
		edges[r * 3 + 0] = n1;
		edges[r * 3 + 1] = n2;
		edges[r * 3 + 2] = w;
		file >> n1 >> n2 >> w;
		r++;
	}
}
void graph::End(int A[], int *sz, int val)
{
	int n;
	n = *sz;
	A[n] = val;
	n++;
	*sz = n;
}
// remove and return first value
int graph::Begin(int A[], int *sz)
{
    int val, n, k;
    n = *sz;
    val = A[0];
    for(k = 0; k < n; k++)
    {
        A[k] = A[k+1];
    }
    n--;
    *sz = n;
    return val;
}
void graph::bfs(int x)
{
	int j;
	int d[100];
	int dSize = 1, v = 0;
	cout << "bfs -- breadth - first node order starting at " << x << endl;
	int *mark = new int[i];
	for(j = 0; j < i; j++)
	{
		mark[j] = 0;
	}
	d[0] = x;
	while(dSize > 0)
	{
		v = Begin(d, &dSize);
		if(!mark[v-1])
		{
			cout << v << " ";
			mark[v - 1] = true;
			for(j = 0; j < i; ++j)
			{
				if(arr[v - 1][j] && !mark[j])
				{
					End(d, &dSize, nodes[j]);
				}
			}
		}
	}
	cout << endl;
}
void graph::bfssp(int x)
{
    int j;
    int d[100];
    int dSize = 1, v = 0;
    cout << "bfssp -- breadth - first node order starting at " << x << endl;
    int *mark = new int[i];
    for(j = 0; j < i; j++)
    {
        mark[j] = 0;
    }
    d[0] = x;
    while(dSize > 0)
    {
        v = Begin(d, &dSize);
        if(!mark[v-1])
        {
            mark[v - 1] = true;
            for(j = 0; j < i; ++j)
            {
                if(arr[v - 1][j] && !mark[j])
                {
                    End(d, &dSize, nodes[j]);
					cout << "{" << v << "," << nodes[j] << "}; ";
                }
            }
        }
    }
    cout << endl;
}
void graph::dfs(int *mark, int x)
{
	int v,j;
	v = x;
	cout << v << " ";
	mark[v - 1] = true;
	for(j = 0; j < i; ++j)
	{
		if(arr[v - 1][j] && !mark[j])
		{
			dfs(mark, nodes[j]);
		}
	}
}
void graph::dfs(int x)
{
	int j;
	cout << "dfs -- depth-first node order starting at " << x << endl;
	int *mark = new int[i];
	for(j = 0; j < i; j++)
	{
		mark[j] = 0;
	}
	dfs(mark, x);
	cout << endl;
}
void graph::dfssp(int *mark, int x)
{
	int j, v;
	v = x;
	mark[v - 1] = true;
	for(j = 0; j < i; j++)
	{
		if(arr[v - 1][j] && !mark[j])
		{
			cout << "{" << v << "," << nodes[j] << "}; ";
			dfssp(mark, nodes[j]);
		}
	}
}
void graph::dfssp(int x)
{
	int j;
	cout << "dfssp -- depth - first spanning tree starting at " << x << endl;
	int *mark = new int[i];
	for(j = 0; j < i; j++)
	{
		mark[j] = 0;
	}
	dfssp(mark, x);
	cout << endl;
}
int graph::findNodeIndex(int x)
{
	int j;
	for(j = 0; j <= i; j++)
	{
		if(x == nodes[j])
			return j;
	}
	return 0;
}
void graph::dijkstra(int startN)
{
	int *visited = new int[i];
	int *unvisited = new int[i];
	int *shortestPD = new int[i];
	int *prevN = new int[i];
	int numV = -1;
	int numU;
	int j,l;
	int nodeI;
	int minPV;
	int minPI;
	int unvisitedITR;
	int *unvisitedNEI;
	int numUNEI;
	int oppsiteEN;
	int oppsiteENU;
	int *unvisitedNITD;
	int neighborN;
	int neighborNI;
	for(j = 0; j < i; j++)
	{
		if(nodes[j] == startN)
		{
			shortestPD[j] = 0;
			prevN[j] = 0;
		}
		else
		{
			shortestPD[j] = INT_MAX;
			prevN[j] = -1;
		}
		unvisited[j] = nodes[j];
		visited[j] = 0;
	}
	numU = i;
	for(numU = i; numU >= 0; numU--)
	{
		minPV = INT_MAX;
		minPI = 0;
		unvisitedITR = 0;
		for(j = 0; j < numU; j++)
		{
			nodeI = findNodeIndex(unvisited[j]);
			if(shortestPD[nodeI] <= minPV)
			{
				minPV = shortestPD[nodeI];
				minPI = nodeI;
				unvisitedITR = j;
			}
		}
		unvisitedNEI = new int[numE/3];
		numUNEI = -1;
		for(j = 0; j < numE/3; j++)
		{
			oppsiteEN = -1;
			if(nodes[minPI] == edges[j * 3 + 0])
			{
				oppsiteEN = edges[j * 3 + 1];
			}
			else if(nodes[minPI] == edges[j * 3 + 1])
			{
				oppsiteEN = edges[j * 3 + 0];
			}
			oppsiteENU = 0;
			if(oppsiteEN != -1)
			{
				for(l = 0; l < numU; l++)
				{
					if(oppsiteEN == unvisited[l])
					{
						oppsiteENU = 1;
						break;
					}
				}
				if(oppsiteENU == 1)
				{
					unvisitedNEI[++numUNEI] = j;
				}
			}
		}
		unvisitedNITD = new int[numE/3];
		for(j = 0; j <= numUNEI; j++)
		{
			unvisitedNITD[j] = edges[unvisitedNEI[j] * 3 + 2] + shortestPD[minPI];
		}
		for(j = 0; j <= numUNEI; j++)
		{
			neighborN = -1;
			if(edges[unvisitedNEI[j] * 3 + 0] = nodes[minPI])
				neighborN = edges[unvisitedNEI[j] * 3 + 1];
			else
				neighborN = edges[unvisitedNEI[j] * 3 + 0];
			neighborNI = findNodeIndex(neighborN);
			if(unvisitedNITD[j] < shortestPD[neighborNI])
			{
				shortestPD[neighborNI] = unvisitedNITD[j];
				prevN[neighborNI] = nodes[minPI];
			}
		}
		visited[++numV] = unvisited[unvisitedITR];
		for(j = unvisitedITR; j < numU && j < numE-1; j++)
		{
			unvisited[j] = unvisited[j+1];
		}
	}
	cout << "Starting At " << startN << endl;
	cout << "Nodes Shortest Distance Previous Node" << endl;
	for(j = 0; j < i; j++)
	{
		cout << setw(6) << nodes[j] << setw(19) << shortestPD[j] << setw(14) << prevN[j] << endl;
	}
}
int graph::isIn(int A[], int sz, int val)
{
	int k;
	int found = 0;
	for(k = 0; k < sz; k++)
	{
		if(A[k] == val)
		{
			found = 1;
			break;
		}
	}
	return found;
}
int graph::indexOfElement(int A[], int sz, int val)
{
	int k;
	int found = 0;
	for(k = 0; k < sz; k++)
	{
		if(A[k] == val)
		{
			return k;
			break;
		}
	}
	return -1;
}
void graph::prim(int startN)
{
	int *visited = new int[i];
	int *unvisited = new int[i];
	int *visitedEI = new int[i - 1];
	int numVEI = -1;
	int numV = -1;
	int numU = -1;
	int graphCost = 0;
	int j;
	int minE;
	int minEI;
	int newVN;
	int cost;
	int unvisitedITR;
	for(j = 0; j < i; j++)
	{
		if(nodes[j] == startN)
		{
			visited[++numV] = startN;
		}
		else
			unvisited[++numU] = nodes[j];
	}
	for(numU = numU; numU >= 0; numU--)
	{
		minE = INT_MAX;
		minEI = 0;
		for(j = 0; j < numE/3; j++)
		{
			if((isIn(visited, numV + 1, edges[j * 3 + 0]) || isIn(visited, numV + 1, edges[j * 3 + 1])) && (isIn(unvisited, numU + 1, edges[j * 3 + 0]) || isIn(unvisited, numU + 1, edges[j * 3 + 1])))
			{
				if(edges[j * 3 + 2] < minE)
				{
					minE = edges[j * 3 + 2];
					minEI = j;
				}
			}
		}
		newVN = -1;
		if(isIn(unvisited, numU + 1, edges[minEI * 3 + 0]))
			newVN = edges[minEI * 3 + 0];
		else
			newVN = edges[minEI * 3 + 1];
		visited[++numV] = newVN;
		visitedEI[++numVEI] = minEI;
		unvisitedITR = indexOfElement(unvisited, numU + 1, newVN);
		for(j = unvisitedITR; j < numU && j < numE - 1; j++)
		{
			unvisited[j] = unvisited[j + 1];
		}
	}
	cout << "Prim - Starting At " << startN << endl;
	cout << "Node1 Node2 Wieght" << endl;
	cost = 0;
	for(j = 0; j <= numVEI; j++)
	{
		cout << setw(6) << edges[visitedEI[j] * 3 + 0] << setw(6) << edges[visitedEI[j] * 3 + 1] << setw(7) << edges[visitedEI[j] * 3 + 2] << endl;
		cost += edges[visitedEI[j] * 3 + 2];
	}
	cout << "Cost: " << cost;
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
	// reading in number of edge 
	ifp >> numedge;
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

	g.dijkstra( location );
	cout << endl << endl;

	g.prim(location);
	cout << endl << endl;

	return 0;
}
