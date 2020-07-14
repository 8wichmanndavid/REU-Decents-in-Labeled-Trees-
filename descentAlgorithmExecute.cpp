#include <cstddef>
#include <iostream>

#include "descentAlgorithm.hpp"

int main(int, char**) {
    Node* stem2 = new Node{1, 0, false};
    Node* stem1 = stem2->addChild(false);
    Node* root = stem1->addChild(false);
    Node* a = root->addChild(true);
    Node* b = root->addChild(false);
    Node* c = root->addChild(true);
    Node* d = a->addChild(true);
    Node* e = a->addChild(false);
    Node* f = b->addChild(false);
    Node* g = b->addChild(false);
    Node* h = c->addChild(false);
    Node* i = c->addChild(false);
    Node* j = f->addChild(true);
    cout << stem2->des() << endl;

    /*Node* b = a->addChild(true);
    Node* c = root->addChild(false);

    // Testing ascentifyCopy
    Node* newRoot = new Node{1,0,false};
    newRoot->ascentifyCopy(*root, *b);
    for (list<Node*>::iterator it=newRoot->children_.begin(); 
            it != newRoot->children_.end(); ++it) { 
        std::cout << "New Node" << endl;
        std::cout << (**it).size_ << endl;
        std::cout << (**it).numDescents_ << endl;
        std::cout << (**it).isDescent_ << endl;
    }
    list<Node*>::iterator it=newRoot->children_.begin();
    Node* newa = *it;
    ++it;
    Node* newb = *it;
    if (*(newa->parent_) == *(newb->parent_)) {
        std::cout << "yeah those are the same" << endl;
    }


    std::cout << "root size = " << root->size_ << ". root descents = " << root->numDescents_ << ". b size = " << b->size_ << ". b descents = " << b->numDescents_ << ". b isDescent = " << b->isDescent_ << endl;
    std::cout << "new root size = " <<newRoot->size_ << ". new root descents = " << newRoot->numDescents_ << endl;
    */
}