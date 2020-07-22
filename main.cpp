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
    Node* root = new Node{1, 0, static_cast<bool>(parameters[0])};
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
    int para[] = {0, 2, 1, 1, 1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
    Node* tree = buildTree(para);
    cout << tree->sumOfHooklengthsOfMaximalDecents() << endl; 
    tree->getPolynomialPoints();   
}