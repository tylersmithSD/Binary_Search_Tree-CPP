/*
 * Binary Search Tree Program
 * Tyler N. Smith
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
using namespace std;

/*
 * Node Declaration
 */
struct node
{
    int info;
    struct node *left;
    struct node *right;
}*root;

/*
 * Class Declaration
 */
class BST
{
    public:
        void find(int, node **, node **);
        void insert(node *tree, node *newnode);
        void del(int);
        void case_a(node *,node *);
        void case_b(node *,node *);
        void case_c(node *,node *);
        void display(node *, int);
        BST()
        {
            root = NULL;
        }
};

/*
 * Main Function
 */
int main()
{
    int choice, textNum;
    BST bst;
    node *temp;
    ifstream infile;
	stringstream ss;
	string textNumString, textFileName;
	char nextChar;

    while (1)
    {
        cout<<endl;
        cout<<"***************************" <<endl;
        cout<<"Binary Search Tree Program"<<endl;
        cout<<"***************************" <<endl;
        cout<<"1.Read in text file"<<endl;
        cout<<"2.Display Tree"<<endl;
        cout<<"3.Quit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Enter file name including extension (.txt): ";
                cin >> textFileName;
				infile.open (textFileName);

				if (infile.is_open())
				{
					while (infile.good())
					{
						nextChar = (char) infile.get();

						if (nextChar != ',')
						{
							textNumString = textNumString + nextChar;
						}
						else
						{
							stringstream ss(textNumString);
							ss >> textNum;
							temp = new node;
                            temp->info = textNum;
							bst.insert(root, temp);
							textNum = 0;
							textNumString = "";
						}

					}
					infile.close();
				}
				else
				{
					cout << "Error opening file";
				}

				break;
            case 2:
                cout<<"Display BST:"<<endl;
                bst.display(root,1);
                cout<<endl;
                break;
			case 3:
                exit(1);
				break;
            default:
                cout<<"Wrong choice"<<endl;
        }
    }
}

/*
 * Find Element in the Tree
 */
void BST::find(int item, node **par, node **loc)
{
    node *ptr, *ptrsave;
    if (root == NULL)
    {
        *loc = NULL;
        *par = NULL;
        return;
    }
    if (item == root->info)
    {
        *loc = root;
        *par = NULL;
        return;
    }
    if (item < root->info)
        ptr = root->left;
    else
        ptr = root->right;
    ptrsave = root;
    while (ptr != NULL)
    {
        if (item == ptr->info)
        {
            *loc = ptr;
            *par = ptrsave;
            return;
        }
        ptrsave = ptr;
        if (item < ptr->info)
            ptr = ptr->left;
	else
	    ptr = ptr->right;
    }
    *loc = NULL;
    *par = ptrsave;
}

/*
 * Inserting Element into the Tree
 */
void BST::insert(node *tree, node *newnode)
{
    if (root == NULL)
    {
        root = new node;
        root->info = newnode->info;
        root->left = NULL;
        root->right = NULL;
        cout<<"Root Node is Added"<<endl;
        return;
    }
    if (tree->info == newnode->info)
    {
        cout<<"Element already in the tree"<<endl;
        return;
    }
    if (tree->info > newnode->info)
    {
        if (tree->left != NULL)
        {
            insert(tree->left, newnode);
	}
	else
	{
            tree->left = newnode;
            (tree->left)->left = NULL;
            (tree->left)->right = NULL;
            return;
        }
    }
    else
    {
        if (tree->right != NULL)
        {
            insert(tree->right, newnode);
        }
        else
        {
            tree->right = newnode;
            (tree->right)->left = NULL;
            (tree->right)->right = NULL;
            return;
        }
    }
}


/*
 * Case A
 */
void BST::case_a(node *par, node *loc )
{
    if (par == NULL)
    {
        root = NULL;
    }
    else
    {
        if (loc == par->left)
            par->left = NULL;
        else
            par->right = NULL;
    }
}

/*
 * Case B
 */
void BST::case_b(node *par, node *loc)
{
    node *child;
    if (loc->left != NULL)
        child = loc->left;
    else
        child = loc->right;
    if (par == NULL)
    {
        root = child;
    }
    else
    {
        if (loc == par->left)
            par->left = child;
        else
            par->right = child;
    }
}

/*
 * Case C
 */
void BST::case_c(node *par, node *loc)
{
    node *ptr, *ptrsave, *suc, *parsuc;
    ptrsave = loc;
    ptr = loc->right;
    while (ptr->left != NULL)
    {
        ptrsave = ptr;
        ptr = ptr->left;
    }
    suc = ptr;
    parsuc = ptrsave;
    if (suc->left == NULL && suc->right == NULL)
        case_a(parsuc, suc);
    else
        case_b(parsuc, suc);
    if (par == NULL)
    {
        root = suc;
    }
    else
    {
        if (loc == par->left)
            par->left = suc;
        else
            par->right = suc;
    }
    suc->left = loc->left;
    suc->right = loc->right;
}

/*
 * Display Tree Structure
 */
void BST::display(node *ptr, int level)
{
    int i;
    if (ptr != NULL)
    {
        display(ptr->right, level+1);
        cout<<endl;
        if (ptr == root)
            cout<<"Root->:  ";
        else
        {
            for (i = 0;i < level;i++)
                cout<<"       ";
	}
        cout<<ptr->info;
        display(ptr->left, level+1);
    }
}



