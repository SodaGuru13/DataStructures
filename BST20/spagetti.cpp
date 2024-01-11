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
		//treenode *_minNode(treenode * t);
		int _numnodes(treenode *t);
		int _height(treenode *t);
		//void deleteTree(treenode** node_ref);
		//void _deleteTree(treenode* node);
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
	// for you
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
	// for you
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

	// for you
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
	// for you
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
	// for you
	if((t->rchild != NULL && x == t->rchild->dat) || (t->lchild != NULL && x == t->lchild->dat))
		return t;
	else if( x > t->dat && t->rchild != NULL )
		return findparent(x, t->rchild);
	else if( x < t->dat && t->lchild != NULL )
		return findparent(x, t->lchild);
	else
		return NULL;
}
/*
treenode *bstree::_minNode(treenode * t)
{
	if ( t == NULL )
		 return NULL;
    treenode *returnedNode;
    cout << " in  t->dat " << t->dat << endl; 
	returnedNode = _minNode(t->lchild);
    cout << " out t->dat " << t->dat << endl;
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
       			if(parent->lchild ==  smallestChild)
					parent->lchild = NULL;
				if (parent->rchild == smallestChild) // could just be an else since it is binary
					parent->rchild = NULL;
			}
			else
			{
				cout << "Warning Parent Not Found" << endl;
				return;
			}
			deleteTree(&smallestChild);
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
				parent->lchild = NULL;
			if (parent->rchild == rem) // could just be an else since it is binary
				parent->rchild = NULL;
		}
		if(rem == root)
			root = NULL;
    	deleteTree(&rem);
	}
}
*/
/*
void bstree::_deleteTree(treenode* node)
{
    if (node == NULL) return;
*/
    /* first delete both subtrees */
/*    _deleteTree(node->lchild);
    _deleteTree(node->rchild);
*/
    /* then delete the node */
/*    cout << "Deleting node: " << node->dat << endl;
    delete node;
}
*/
/* Deletes a tree and sets the root as NULL */
/*
void bstree::deleteTree(treenode** node_ref)
{
    if(*node_ref == root)
		cout << "Abort delete if root" << endl;
	else 
    	_deleteTree(*node_ref);
    *node_ref = NULL;
}
*/

void bstree::remove( int x )
{
	treenode *t, *t1;
	treenode *rem, *parent;
	int low;
	rem = findval( x, root );
	if(rem == NULL)
		return;
	t = rem;
	if(t->lchild == NULL && t->rchild == NULL)
	{
		if(t == root)
		{
			root = NULL;
			return;
		}
		cout << "Hit me baby one more time";
		parent = findparent(x, root); 
		if(parent == NULL)
			return;
		if(parent->rchild != NULL && parent->rchild->dat == x)
			parent->rchild = NULL;
		else if(parent->lchild != NULL && parent->lchild->dat == x)
			parent->lchild = NULL;
	}
	else if(t->lchild != NULL && t->rchild == NULL)
	{
		t = t->lchild;
		rem->dat = t->dat;
		rem->lchild = t->lchild;
		rem->rchild = t->rchild;
	}
	else if(t->rchild != NULL && t->lchild == NULL)
	{
		t = t->rchild;
		rem->dat = t->dat;
		rem->lchild = t->lchild;
		rem->rchild = t->rchild;
	}
	else if(t->lchild != NULL && t->rchild != NULL)
	{
		t = t->rchild;
		low = t->dat;
		parent = t;
		printf("d");
		while(t->lchild != NULL)
		{
			if(low > t->lchild->dat)
			{
				parent = t;
				low = t->lchild->dat;
			}
			t = t->lchild;
		}
		int parentval;
		parentval = rem->dat;
		rem->dat = low;
		if(parent->lchild->rchild != NULL && parent->lchild->lchild != NULL)
		{
			printf("test1");
			parent->lchild->dat = 0;
			remove(0);
		}
		else if(parent->lchild->lchild != NULL)
		{
			printf("test2");
			parent->lchild = parent->lchild->lchild;
		}
		else if(parent->lchild->rchild != NULL)
		{
			printf("test3");
			parent->lchild = parent->lchild->rchild;
		}
		else
		{
			*t = *parent->lchild;
			delete(t);
			parent->lchild = NULL;
		}
	}
/*
			printf("test4");
			cout << "Hit me baby one more time";

            treenode *lowNode;//, *freeNode1;
            lowNode = parent->lchild;

			if(parent->rchild == lowNode)
			{
//				freeNode1 = parent->rchild;
                parent->rchild = NULL;
			}
			else
			{
//				freeNode1 = parent->lchild;
				parent->lchild = NULL;
			}
            delete(lowNode);
//			free(lowNode);
//			free(freeNode1);

//			rem->dat = parentval;


//			treenode *xparent;
//            rem->dat = 58;
            treenode *lowNode;
//			xparent = findparent(x, root);
			lowNode = parent->lchild;
			cout << "lowNode" << lowNode->dat;
            cout << "rem" <<  rem-> dat;
            cout << "parent" << parent -> dat;

			treenode *cleanupNode;
			if(parent->rchild == lowNode)
			{
				cleanupNode = parent->rchild;
                parent->rchild = NULL;
			}
			else
			{
				cleanupNode = parent->lchild;
				parent->lchild = NULL;
			}
			delete(lowNode);
//			free(cleanupNode);

			if(xparent != NULL)
			{
				cout << "xparent" << xparent->dat;
				if(xparent->rchild == rem)
					xparent->rchild = lowNode;
				else
					xparent->lchild = lowNode;
			}

 			lowNode->rchild = rem->rchild;
            cout << "rem data: " << rem->dat;
			lowNode->lchild = rem->lchild;

//			delete(lowNode);

            free(freeNode4);
            free(freeNode3);
            free(freeNode2);
            free(freeNode1);
		}
	}

	parent = rem;
	if( parent->rchild != NULL)
	{
		t = parent->rchild;
		cout << "Right" << endl;
	}
	else
	{
		t = parent->lchild;
		cout << "Left" << endl;
	}
	if( t != NULL )
	{
		parent->dat = t->dat;
		parent->rchild = t->rchild;
		parent->lchild = t->lchild;
	}
	else
	{
		parent->parent = NULL;
	}

	// for you
	// 2-child case should use smallest on right
*/
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


