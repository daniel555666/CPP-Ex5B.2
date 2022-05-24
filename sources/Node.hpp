#include<vector>
#include<string>
using namespace std;

typedef struct Node
        {
            string data;
            struct Node* father;
            int my_idChild;
            size_t my_lvl;
            Node* next; // the next node in the list of the same lvl
            vector<struct Node*> *Lower_Lvl_Arr;

        } Node;