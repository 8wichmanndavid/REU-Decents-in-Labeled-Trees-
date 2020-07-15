#include <cstddef>
#include <iostream>
#include <utility>
#include <queue>
#include "Node.h"

void addChildren(int numChildren, bool isDes, Node* cn, queue<Node*>& cq){
    for (int lcv = 0; lcv < numChildren; lcv++){
        Node* child = cn->addChild(isDes);
        cq.push(child);
    };
};

// Parameters first value is a 1 if the root is a decent
//or a 0 if it's not
Node* buildTree(int parameters[]){
    queue<Node*> nodeQueue;
    Node* root = new Node{1, 0, parameters[0]};
    nodeQueue.push(root);
    int idx = 1;
    while (!nodeQueue.empty()){
        addChildren(parameters[idx], 1, nodeQueue.front(), nodeQueue);
        idx++;
        addChildren(parameters[idx], 0, nodeQueue.front(), nodeQueue);
        idx++;
        nodeQueue.pop();
    };
    return root;
};


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

    
    int para[] = {0,0,1,0,1,2,1,1,1,0,2,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0};
    Node* stem22 = buildTree(para);
    cout << stem22->des() << endl;
    
    
    int para2[] = {0,2,1,1,1,0,2,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0};
    Node* baseTree = buildTree(para2);
    Node* stem32 = baseTree->addStem(13);
    cout << stem32->des() << endl;
    
    int para3[] = {0,2,0,1,1,0,2,0,0,0,0,0,0,0,0};
    int para4[] = {0,0,2,1,0,0,0,0,0};
    Node* parentTree = buildTree(para3);
    Node* childTree = buildTree(para4);
    parentTree->combineTree(childTree);
    Node* stem42 = parentTree->addStem(13);
    cout << stem42->des() << endl;
    
    
    int para5[] = {0,3,0,1,1,0,2,0,2,0,0,0,0,0,0,0,0,1,0,0,0,0,0};
    Node* testCoords = buildTree(para5);
    Node* stem52 = testCoords->addStem(12);
    cout << stem52->des() << endl;
    
}