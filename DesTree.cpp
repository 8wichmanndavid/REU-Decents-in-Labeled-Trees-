#include <string>
#include <iostream>
using namespace std;
template <class T>
class DesTree {
    public:
        DesTree() {
            curr = NULL;
            prev = NULL
            ct = 0;
        };

        DesTree(DesTree<T>& cq){
            curr = NULL;
            prev = NULL;
            ct = 0;
            while (cq.curr != cq.prev){
                cq.next()
            };
            addChild(cq.curr -> item, cq.curr -> isDes);
            cq.next();
            while (cq.curr != cq.prev){
                for (list<int>::iterator it=(cq.prev -> children).begin(); it != (cq.prev -> children).end(); ++it){
                    if (*it == cq.curr){
                        addChild(cq.curr -> item, cq.curr -> isDes)
                    };
                };
                cq.next();
                next();
            };
        };
       
        node& copyNode(node& cq){
            node *n;
            list<node*> tempList;
            n-> item = cq->item;
            n-> isDes = cq-> isDes;
            n-> hookLength = cq -> hookLength;
            n -> parent = n;
            n-> children = tempList;
            n-> desDes = 0
            for (list<int>::iterator it=(cq -> children).begin(); it != (cq -> children).end(); ++it){
                node *temp = copyNode(it);
                (n-> children).push_back(temp)
            };
            return n;
        };
       
        DesTree& nodeTree(node& cq){
            node *n = copyNode(cq);
            DesTree *tree;
            tree.curr = n;
            tree.prev = n;
            tree.ct = n -> hookLength;
            return tree;
        };
        
        DesTree& removeNode(node& cq){
            DesTree *tree= nodeTree(cq);
            for (list<int>::iterator it=(cq-> parent -> children).begin(); it != (cq -> parent -> children).end(); ++it){
                if (it == cq){
                    node *n = cq;
                    node *n2 = cq->parent;
                    int descent =0;
                    while (n!=n2){
                        n2->desDes = n2->desDes - cq -> desDes;
                        n2->hookLength = n2->hookLength - cq->hookLength;
                    };
                    (cq->parent->children).erase(it);
                    break;
                };
            };
            cq -> parent = cq;
            tree.curr = cq;
            tree.prev = cq;
            tree.ct = cq->hookLength;
            cq -> isDes = false;
            cq -> desDes = cq -> desDes - 1;
            return tree;
        };
       
        int solve(){
            while (prev != curr){
                next();
            };
            if (curr -> desDes = 0){
                return baseCase();
            };
            else{
                while(!(curr->isDes)){
                    next();
                };
                DesTree *TwoK= DesTree(self)
                
            };
            
        };
        
        int baseCase(){
            long long int top=1;
            for(int lcv=1; lcv<tree.ct; lcv++){
                top = top * lcv
            };
            while (prev != curr){
                next();
            };
            next();
            long long int bot= 1;
            while (prev != curr){
                if (prev.parent==curr){
                    bot = bot * prev.hookLength;
                };
            };
            long long int quo = top/bot;
            return quo;
        };

        void next(){
            if ((curr==prev && (curr->children).empty()) || curr->parent == prev){
                prev = curr;
                curr = (curr->children).front();
            };
            else if(prev == (curr->children).back()){
                prev = curr;
                curr = curr->parent
            };
            else{
                for (list<int>::iterator it=(curr -> children).begin(); it != (curr -> children).end(); ++it){
                    if (it == prev){
                        it++;
                        prev = curr;
                        curr = it;
                        break;
                    };
                };
            };
        };
   
        T& curr(){
            return current->item;
        };
       
        int get_ct(){
            return ct;
        };
       
        bool is_empty(){
            return ct == 0;
        };
       
        void addChild(T& data, bool des){
            if (ct==0){
                node *n = new node;
                list<node*> tempList;
                n-> item = data;
                n-> isDes = des;
                n-> hookLength = 1;
                n -> parent = n;
                n-> children = tempList;
                n-> desDes = 0
                curr =n;
                prev =n;
                ct++;
            };
            else{
                int desAdd = 0;
                if (des){
                    desAdd++;
                };
                node *n = new node;
                list<int> tempList;
                n-> item = data;
                n-> isDes = des;
                n-> hookLength = 1;
                n -> parent = curr;
                n-> children = tempList;
                n-> desDes = desAdd
                (curr->children).push_back(n);
                node *par = n-> parent;
                desAdd = 0;

                while (par != par->parent){
                    (par->hookLength)++;
                    par->desDes= (par->desDes) + desAdd;
                    par = par->parent;
                };
            };
        };
       
    private:
        struct node;
        struct node {
            list<node *> children;
            node * parent;
            T item;
            bool isDes;
            int hookLength;
            int desDes;
        };
        struct node * curr;
        struct node * prev;
        int ct;

};