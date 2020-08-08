# Helper Code for Calculating Descents in Labeled Trees
## Introduction
This code is currently helpful for perfmorming two tasks: 
* Calculating the number of possible labelings for a given tree 
* Producing enough points to interpolate the polynomial d(T;n) for a given tree

Currently, there are two methods of tree-building supported by the code. The two methods produce the exact same object, but there are advantages and disadvantages to the user. 
The "Reference" method is more approachable but potentially more tedious. With practice, the "Integer List" method is much quicker and has the advantage of easily storing 
a tree's critical information, but is more prone to user error and less approachable. 

## Tree Building
One crucial thing to note about tree building with this code is that there is no tree object. You build a tree by creating a node and keeping a reference to that node as you give
it children
### The Reference Method 
In the reference method, you use the fact that our addChild method returns a reference to the node that it adds and keep references to every new node you add. For the tree pictured below the reference method would look something like the following (for a descent at the root, change the root constructor parameters to {1, 1, true}): 
```c++
Node* root = new Node{1, 0, false};
Node* a = root->addChild(true);
Node* b = root->addChild(false);
Node* c = b->addChild(true);
```
![BaseTree](/images/IMG_1557.PNG)

The parameter passed into addChild determines if the node will be created as a descent (if true) or an ascent (if false). 
### The Integer List Method
The integer list method condenses the tree's information into a list of integers which can then be easily stored in a database or sent between collaborators.
