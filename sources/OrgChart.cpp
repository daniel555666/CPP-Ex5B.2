#include <stdexcept>
#include "OrgChart.hpp"
#include <queue>

using namespace std;

namespace ariel
{

    OrgChart &OrgChart::add_root(const string &root)
    {
        if (this->head == NULL)
        {
            Node *new_root = new Node;
            new_root->data = root;
            new_root->my_idChild = 0;
            new_root->my_lvl = 0;
            new_root->next = NULL;
            this->highest_lvl = 0;
            new_root->Lower_Lvl_Arr = new vector<Node *>;
            this->head = new_root;
            this->lvls = new vector<Node *>;
            this->lvls->push_back(new_root);
            return *this;
        }

        this->head->data = root;
        return *this;
    }

    Node *OrgChart::DFS_get_bos(const string &bos, Node *root)
    {
        if (root->data == bos)
        { // for the first time
            return root;
        }
        Node *temp = root;
        for (size_t i = 0; i < temp->Lower_Lvl_Arr->size(); i++)
        {
            if (temp->Lower_Lvl_Arr->at(i)->data == bos)
            {
                return temp->Lower_Lvl_Arr->at(i);
            }
            Node *check_Node = DFS_get_bos(bos, temp->Lower_Lvl_Arr->at(i));
            if (check_Node != NULL)
            {
                return check_Node;
            }
        }

        return NULL;
    }

    OrgChart &OrgChart::add_sub(const string &bos, string object)
    {
        if (this->head == NULL)
        {
            throw runtime_error("no root");
        }
        Node *temp = nullptr; // get the node father
        if ((temp = DFS_get_bos(bos, this->head)) == NULL)
        {
            throw runtime_error("error,wrong boss name");
        }
        Node *add = new Node;
        add->data = move(object);
        add->father = temp;
        add->next = NULL;
        add->my_lvl = temp->my_lvl + 1;
        add->Lower_Lvl_Arr = new vector<Node *>;
        add->my_idChild = temp->Lower_Lvl_Arr->size();
        temp->Lower_Lvl_Arr->push_back(add);

        if (this->highest_lvl < add->my_lvl)
        { // if he the first in this lvl
            this->lvls->push_back(add);
        }
        else
        {
            Node *temp2 = this->lvls->at(add->my_lvl);
            while (temp2->next != NULL)
            {
                temp2 = temp2->next;
            }
            temp->next = add; // put add in the end
        }

        if (add->my_lvl > this->highest_lvl) // save the highest lvl
        {
            this->highest_lvl = add->my_lvl;
        }

        return *this;
    }
    OrgChart::Iterator OrgChart::begin_level_order() const
    {
        if (this->head == NULL)
        {
            throw runtime_error("empt tree");
        }
        vector<Node *> *v = new vector<Node *>;
        queue<Node *> q;
        q.push(this->head);
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            v->push_back(temp); // insert the node to the vector
            for (size_t i = 0; i < temp->Lower_Lvl_Arr->size(); i++)
            {
                q.push(temp->Lower_Lvl_Arr->at(i));
            }
        }

        return Iterator(v);
    }
    OrgChart::Iterator OrgChart::end_level_order() const
    {
        if (this->head == NULL)
        {
            throw runtime_error("empt tree");
        }
        return Iterator();
    }
    OrgChart::Iterator OrgChart::begin_reverse_order() const
    {
        if (this->head == NULL)
        {
            throw runtime_error("empt tree");
        }
        vector<Node *> *v = new vector<Node *>;
        vector<Node *> *t = new vector<Node *>;
        queue<Node *> q;
        q.push(this->head);
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            v->push_back(temp); // insert the node to the vector
            
            for (int i = (int)temp->Lower_Lvl_Arr->size() - 1; i >= 0; i--)
            {
                q.push(temp->Lower_Lvl_Arr->at((unsigned int)i));
            }
        }
        for (int i = (int)v->size() - 1; i >= 0; i--)
        {

            t->push_back(v->at((size_t)i));
        }
        delete (v);
        return Iterator(t);
    }
    void OrgChart::DFS(vector<Node *> *v, Node *head) const
    {
        Node *temp = head;
        for (size_t i = 0; i < temp->Lower_Lvl_Arr->size(); i++)
        {
            v->push_back(temp->Lower_Lvl_Arr->at(i));
            DFS(v, temp->Lower_Lvl_Arr->at(i));
        }
    }
    OrgChart::Iterator OrgChart::reverse_order() const
    {
        if (this->head == NULL)
        {
            throw runtime_error("empt tree");
        }
        return Iterator();
    }
    OrgChart::Iterator OrgChart::begin_preorder() const
    {
        if (this->head == NULL)
        {
            throw runtime_error("empt tree");
        }
        vector<Node *> *v = new vector<Node *>;
        v->push_back(this->head);
        DFS(v, this->head); // we fill v;
        return Iterator(v);
    }
    OrgChart::Iterator OrgChart::end_preorder() const
    {
        if (this->head == NULL)
        {
            throw runtime_error("empt tree");
        }
        return Iterator();
    }
    ostream &operator<<(ostream &output, OrgChart &org)
    {
        for (OrgChart::Iterator it = org.begin_level_order(); it != org.end_level_order(); ++it)
        {
            Node *temp = it.v_it->at(it.index);
            output << "boss-" << temp->data << " : his workers - ";
            // print them and the sons
            for (size_t i = 0; i < temp->Lower_Lvl_Arr->size(); i++)
            {
                if (i == temp->Lower_Lvl_Arr->size() - 1)
                {
                    output << temp->Lower_Lvl_Arr->at(i)->data << ".";
                }
                else
                {
                    output << temp->Lower_Lvl_Arr->at(i)->data << " , ";
                }
            }
            output << "\n";
        }

        return output;
    }
    OrgChart::Iterator OrgChart::begin() const
    {
        if (this->head == NULL)
        {
            throw runtime_error("empt tree");
        }
        vector<Node *> *v = new vector<Node *>;
        queue<Node *> q;
        q.push(this->head);
        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            v->push_back(temp); // insert the node to the vector
            for (size_t i = 0; i < temp->Lower_Lvl_Arr->size(); i++)
            {
                q.push(temp->Lower_Lvl_Arr->at(i));
            }
        }
        return Iterator(v);
    }
    OrgChart::Iterator OrgChart::end() const
    {
        if (this->head == NULL)
        {
            throw runtime_error("empt tree");
        }
        return Iterator();
    }

    OrgChart::Iterator &OrgChart::Iterator::operator++()
    {
        if (this->v_it == NULL)
        {
            return *this;
        }
        if (this->index >= this->v_it->size())
        {
            return *this;
        }
        this->index++;
        return *this;
    }

    bool OrgChart::Iterator::operator!=(const Iterator &other) const
    {
        if (this->v_it == NULL)
        {
            return false;
        }
        if (this->index >= this->v_it->size())
        {
            return false;
        }
        return true;
    }

    string *OrgChart::Iterator::operator->() const
    {
        if (this->v_it == NULL)
        {
            throw runtime_error("error , cant print from null object");
        }
        return &(this->v_it->at(this->index)->data);
    }
    string OrgChart::Iterator::operator*() const
    {
        if (this->v_it == NULL)
        {
            throw runtime_error("error , cant print from null object");
        }
        return (this->v_it->at(this->index)->data);
    }
    OrgChart::Iterator::~Iterator()
    {
        delete (this->v_it);
    }
    OrgChart::~OrgChart()
    {
        try
        {
            if (this->head == NULL)
            {
                return;
            }
            for (OrgChart::Iterator it = begin_level_order(); it != this->end_level_order(); ++it)
            {
                Node *temp = it.v_it->at(it.index);
                delete (temp->Lower_Lvl_Arr);
                delete (temp);
            }
            this->highest_lvl = 0;
            delete (this->lvls);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    };
}
// int main(){
// using namespace ariel;
//
//   OrgChart org1;
//
//   org1.add_root("dad").
//   add_sub("dad","son").
//   add_sub("dad","son2").
//   add_sub("son","sonson");
//
//   cout<<org1<<endl;

//   for(auto it:org1){
//       cout<<*it<<",";
//   }

// }