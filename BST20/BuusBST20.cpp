#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

struct treenode
{
	int dat;
	treenode *lchild;
	treenode *rchild;
};

class bstree
{
	public:
		bstree();
		void in( );
		void pre( );
		void post( );
		void insert( int x );
		int findval( int x );
		void remove( int x );
		int numnodes();
		int height();
	private:
		treenode *root;
		void in( treenode *t );
		void pre( treenode *t );
		void post( treenode *t );
		void insert( treenode *t, treenode *n );
		treenode *findval( int x, treenode *t);
		treenode *findparent( int x, treenode *t);
		treenode *_minNode(treenode * t);
		int _numnodes(treenode *t);
		int _height(treenode *t);
};

bstree::bstree()
{
		root = NULL;
}

void bstree::in( treenode *t )
{
    if ( t == NULL )
         return;

    in(t->lchild);
    printf("%2d ", t->dat);
    in(t->rchild);
}

void bstree::pre(treenode * t)
{
	if ( t == NULL )
		 return;

	printf("%2d ", t->dat);
	pre(t->lchild);
	pre(t->rchild);
}

void bstree::post(treenode * t)
{
	if( t == NULL )
		return;
	post(t->lchild);
	post(t->rchild);
	printf(" %2d", t->dat);
}

void bstree::in()
{
	in(root);
}

void bstree::pre()
{
	pre(root);
}

void bstree::post()
{
	post(root);
}

void bstree::insert( int x )
{
	treenode *t1;
	treenode *tmp;
	treenode *ltmp;

	t1 = new treenode();
	t1->dat = x;
	t1->lchild = NULL;
	t1->rchild = NULL;
	if( root == NULL )
	{
		root = t1;
		return;
	}
	insert(root, t1);
}
void bstree::insert( treenode *t, treenode *n )
{
	treenode *child;

	if( n->dat < t->dat)
		child = t->lchild;
	else
		child = t->rchild;

	if(child != NULL)
		insert(child, n);
	else
	{
		if( n->dat < t->dat)
			t->lchild = n;
		else
			t->rchild = n;
	}
}

int bstree::findval( int x )
{
	if((findval(x, root)) != NULL)
		return 1;
	else
		return 0;
}

treenode *bstree::findval( int x, treenode *t)
{
	if ( t == NULL )
		 return NULL;
	if( x > t->dat && t->rchild != NULL )
		return findval(x, t->rchild);
	else if( x < t->dat && t->lchild != NULL )
		return findval(x, t->lchild);
	else if( x == t->dat )
		return t;
	else
		return NULL;
}

treenode *bstree::findparent( int x, treenode *t)
{
	if ( t == NULL )
		 return NULL;
	if((t->rchild != NULL && x == t->rchild->dat) || (t->lchild != NULL && x == t->lchild->dat))
		return t;
	else if( x > t->dat && t->rchild != NULL )
		return findparent(x, t->rchild);
	else if( x < t->dat && t->lchild != NULL )
		return findparent(x, t->lchild);
	else
		return NULL;
}
treenode *bstree::_minNode(treenode * t)
{
	if ( t == NULL )
		 return NULL;
    treenode *returnedNode;
//    cout << " in  t->dat " << t->dat << endl; 
	returnedNode = _minNode(t->lchild);
//    cout << " out t->dat " << t->dat << endl;
    if(returnedNode == NULL)
		return t;
	else
    	return returnedNode;
}

void bstree::remove( int x )
{
	treenode *rem, *parent, *smallestChild;
	rem = findval( x, root );
	if(rem == NULL) 
		return;
    if(rem->rchild != NULL)
	{
        cout << "Get Right Child" << endl;
        smallestChild = _minNode(rem->rchild);
		if(smallestChild != NULL)
		{
			int smallestValue = smallestChild->dat;
			cout << "smallest child is " << smallestValue << endl;
			parent = findparent(smallestValue, root);
			rem->dat = smallestValue;
			if(parent != NULL)
			{
				if (parent->lchild == smallestChild)
					if(smallestChild->lchild == NULL)
						parent->lchild = smallestChild->rchild;
					else
						parent->lchild = smallestChild->lchild;
				if (parent->rchild == smallestChild) 
					parent->rchild = smallestChild->rchild;
			}
			else
			{
				cout << "Warning Parent Not Found" << endl;
				return;
			}
		    cout << "Deleting node: " << smallestChild->dat << endl;
			delete(smallestChild);
		}
		else
		{
			cout << "no smaller min childern found" << endl;
		}
	}
	else 
	{
		parent = findparent(rem->dat, root);

		if(parent != NULL)
		{
        	if(parent->lchild ==  rem)
			{
				if (rem->lchild != NULL)
					parent->lchild = rem->lchild;
				else
					parent->lchild = NULL;
			}
        	if(parent->rchild ==  rem)
					parent->rchild = NULL;
		}
		if(rem == root)
			root = NULL;
	    cout << "Deleting node: " << rem->dat << endl;
		delete(rem);
	}
}

int bstree::_numnodes(treenode * t)
{
	int r, l;
	r = 0;
	l = 0;
	// for you
	if( t->rchild != NULL )
		r = _numnodes(t->rchild);
	if( t->lchild != NULL )
		l = _numnodes(t->lchild);
//	cout << " Number " << t->dat << " r: " << r << " l: " << l << " +1" << endl;
	return l+r+1;
	// for you
}
int bstree::numnodes()
{
	int ans;
	ans = _numnodes(root);
	return ans;
}

int bstree::_height(treenode * t)
{
	int r, l;
	r = 0;
	l = 0;
	// for you
	if( t->rchild != NULL )
		r = _height(t->rchild);
	if( t->lchild != NULL )
		l = _height(t->lchild);
	if( r > l)
		return r+1;
	else
		return l+1;
}
int bstree::height()
{
	int ans;
	ans = _height(root);
	return ans;
}


int main(int argc, char *argv[])
{
	bstree * t;
	int i, x, cmd;
	ifstream ifp;

	if (argc != 2)
	{
		cout << "ERROR:  no BST CMD file " << endl;
		return 2;
	}

	ifp.open( argv[1] );

	if ( ! ifp.is_open() )
	{
		 cout << "ERROR: file " << argv[1] << " could not be opened" << endl;
		 return 3;
	}

	t = new bstree();
	// read the command file
	ifp >> cmd;
	while ( !ifp.eof())
	{
		cout << cmd;
		if( cmd == 1 || cmd == -1 || cmd == 2)
		{
			ifp >> x;
			cout << " " << x;
		}
		switch(cmd)
		{
			case 0:
				return 0;
			break;
			case 1:
				t->insert(x);
			break;
			case -1:
				//cout << "Before -1";
				t->remove(x);
			break;
			case 2:
				if((t->findval(x)) == 1)
					cout << " Found ";
				else
					cout << " Not Found ";
			break;
			case 3:
				t->pre();
				//cout << endl;
				//cout << "After 3";
			break;
			case 4:
				t->in();
			break;
			case 5:
				t->post();
			break;
			case 7:
				cout << " Number of Nodes: " << t->numnodes();
			break;
			case 8:
				cout << " Height: " << t->height();
			break;
		}
		//cout << "endofswitch";
		cout << endl;
		//cout << "afternewLine";
		ifp >> cmd;
		//cout << "atendofloop";
	}
	return 0;
}
