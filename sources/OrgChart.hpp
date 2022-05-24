#include <iostream>
#include <string>
#include "Node.hpp"
using namespace std;

namespace ariel
{

    class OrgChart
    {

    public:
        Node *head;
        OrgChart &add_root(const string &root);
        OrgChart &add_sub(const string& bos, string object);
        vector<Node*> *lvls;
        size_t highest_lvl;

        OrgChart()
        {            
            this->head = NULL;
            this->lvls=NULL;
            this->highest_lvl=0;
        }
        OrgChart(const OrgChart &o){
            this->head=o.head;
            this->lvls=o.lvls;
            this->highest_lvl=o.highest_lvl;
        }

        class Iterator
        {

        private:
            

        public:
            // Node *pitr;
            vector<Node*>* v_it;
            // OrgChart *this_one;
            Node* end_NULL;
            size_t index;
            Iterator(){
                this->end_NULL=NULL;
                this->v_it=NULL;
                this->index=0;
            }
            Iterator(vector<Node*>* v)
            {   this->v_it=v;
                this->end_NULL=NULL;
                this->index=0;
            }
            Iterator( Iterator &it){
                this->end_NULL=it.end_NULL;
                this->v_it=it.v_it;
                this->index=it.index;
            }
       
           
            ~Iterator();
            Iterator &operator++();
            bool operator!=(const Iterator &other) const;
            bool operator==(const Iterator &other) const;
            string *operator->()const;
            string operator*()const;
             Iterator& operator=(Iterator&& it)=default;
        Iterator(Iterator&&It)=default;
        Iterator& operator=(const Iterator & it)=default;
           
        };
      
        void DFS(vector<Node *> *v, Node *head)const;
        Iterator end()const;
        Iterator begin()const;
        Iterator end_level_order()const;
        Iterator begin_reverse_order()const;
        Iterator begin_level_order()const;
        Iterator reverse_order()const;
        Iterator begin_preorder()const;
        Iterator end_preorder()const;
        OrgChart& operator=(OrgChart&& org)=default;
        OrgChart(OrgChart& org)=default;
        OrgChart(OrgChart&&OrgChart)=default;
        ~OrgChart();
        OrgChart& operator=(const OrgChart & org)=default;

    private:
        Node *DFS_get_bos(const string& bos, Node *root);
        friend ostream &operator<<(ostream &output, OrgChart &org);
    };

}