#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    int state[9];
    Node *parent;
    
};

Node* BFS(int[]);
bool goalTest(int[]);
int blankIndex(int[]);
bool leftLegal(int[]);
bool rightLegal(int[]);
bool upLegal(int[]);
bool downLegal(int[]);
bool contains(int[],vector<Node*>);
void displayPath(Node*,int&);
void displayFormat(int[]);
void arrCopy(int[],int[]);
void swap(int[],int,int);

vector<Node*> frontier;
vector<Node*> explored;

int main()
{
    int input[9];
    
    cout << "Enter initial state: ";
    
    for (int i = 0; i < 9; i++)
    {
        cin >> input[i];
    }
    
    Node *result = BFS(input);
    
    if (!result)
        cout << "\nSolution not found.\n\n";
    
    else
    {
        int pathCost = -1;
        displayPath(result, pathCost);
        cout << "\nPath cost: " << pathCost << endl;
        cout << "Number of states stored in frontier: " << frontier.size() << endl;
        cout << "Number of states stored in explored: " << explored.size() << endl;
        cout << endl;
    }
    
    return 0;
}

Node* BFS(int initialState[])
{
    // if initial state is the goal
    if (goalTest(initialState))
    {
        Node *goalNode = (Node*)malloc(sizeof(Node));
        arrCopy(goalNode->state,initialState);
        goalNode->parent = NULL;
        return goalNode;
    }
    
    // add initial state to frontier
    Node *newNode = (Node*)malloc(sizeof(Node));
    arrCopy(newNode->state,initialState);
    newNode->parent = NULL;
    frontier.push_back(newNode);
    
    while (!frontier.empty())
    {
        // remove first node from frontier
        Node *currentNode = frontier[0];
        frontier.erase(frontier.begin());
        
        // add node to explored
        explored.push_back(currentNode);
        
        // check moves
        int space = blankIndex(currentNode->state); // location of 0
        
        if (leftLegal(currentNode->state))
        {
            // child node
            Node *left = (Node*)malloc(sizeof(Node));
            arrCopy(left->state,currentNode->state);
            left->parent = currentNode;
            
            // move left
            swap(left->state, space, space - 1);
            
            if (!contains(left->state,frontier) && !contains(left->state,explored))
            {
                // check goal test
                if (goalTest(left->state))
                    return left;
                
                // add child to frontier
                frontier.push_back(left);
            }
        }
        
        if (rightLegal(currentNode->state))
        {
            // child node
            Node *right = (Node*)malloc(sizeof(Node));
            arrCopy(right->state,currentNode->state);
            right->parent = currentNode;
            
            // move right
            swap(right->state, space, space + 1);
            
            if (!contains(right->state,frontier) && !contains(right->state,explored))
            {
                // check goal test
                if (goalTest(right->state))
                    return right;
                
                // add child to frontier
                frontier.push_back(right);
            }
        }
        
        if (upLegal(currentNode->state))
        {
            // child node
            Node *up = (Node*)malloc(sizeof(Node));
            arrCopy(up->state,currentNode->state);
            up->parent = currentNode;
            
            // move up
            swap(up->state, space, space - 3);
            
            if (!contains(up->state,frontier) && !contains(up->state,explored))
            {
                // check goal test
                if (goalTest(up->state))
                    return up;
                
                // add child to frontier
                frontier.push_back(up);
            }
        }
        
        if (downLegal(currentNode->state))
        {
            // child node
            Node *down = (Node*)malloc(sizeof(Node));
            arrCopy(down->state,currentNode->state);
            down->parent = currentNode;
            
            // move down
            swap(down->state, space, space + 3);
            
            if (!contains(down->state,frontier) && !contains(down->state,explored))
            {
                // check goal test
                if (goalTest(down->state))
                    return down;
                
                // add child to frontier
                frontier.push_back(down);
            }
        }
    }
    
    return NULL; // solution not found
}

// compare given state to goal state
bool goalTest(int state[])
{
    int goal[9] = {0,1,2,3,4,5,6,7,8};
    
    for (int i = 0; i < 9; i++)
    {
        if (state[i] != goal[i])
            return false;
    }
    
    return true;
}

int blankIndex(int state[])
{
    for (int i = 0; i < 9; i++)
    {
        if (state[i] == 0)
            return i;
    }
    return -1;
}

// find legal moves for a given state

bool leftLegal(int state[])
{
    return blankIndex(state) % 3 > 0;
}

bool rightLegal(int state[])
{
    return blankIndex(state) % 3 < 2;
}

bool upLegal(int state[])
{
    return blankIndex(state) / 3 > 0;
}

bool downLegal(int state[])
{
    return blankIndex(state) / 3 < 2;
}

// check contents of vectors
bool contains(int state[], vector<Node*> vect)
{
    if (vect.size() == 0)
        return false;
    
    for (int i = 0; i < vect.size(); i++) // elements of vector
    {
        for (int j = 0; j < 9; j++) // elements of state
        {
            if (state[j] != vect[i]->state[j]) // end loop at first mismatch
                break;
            
            else if (j == 8) // if loop runs through complete state without breaking
                return true;
        }
    }
    
    return false;
}

void displayPath(Node *node, int &pathCost)
{
    pathCost++;
    
    if (node->parent)
        displayPath(node->parent, pathCost);
    
    displayFormat(node->state);
}

void displayFormat(int state[])
{
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
            cout << endl;
        
        cout << state[i] << " ";
    }
    cout << endl;
}

void arrCopy(int arr1[], int arr2[])
{
    for (int i = 0; i < 9; i++)
    {
        arr1[i] = arr2[i];
    }
}

void swap(int state[], int index1, int index2)
{
    int temp = state[index1];
    state[index1] = state[index2];
    state[index2] = temp;
}
