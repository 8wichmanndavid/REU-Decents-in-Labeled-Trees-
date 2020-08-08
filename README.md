# Helper Code for Calculating Descents in Labeled Trees
## Introduction
This code is currently helpful for perfmorming two tasks: 
* Calculating the number of possible labelings for a given tree 
* Producing enough points to interpolate the polynomial d(T;n) for a given tree

Currently, there are two methods of tree-building supported by the code. The two methods produce the exact same object, but there are advantages and disadvantages to the user. 
The "Reference" method is more approachable but potentially more tedious. With practice, the "Integer List" method is much quicker and has the advantage of easily storing 
a tree's critical information, but is more prone to user error and less approachable. 

## Caution: 
Before getting too far in the tutorial, we advise that this code can be overwhelmed by very large trees. Trees with a low concentration of descents in the upper part of the tree can get larger while staying safe. We are not sure exactly at what point accuracy starts getting lost but are pretty confident that any tree with less than 30 vertices should be safe and we have found that trees with descents only in the lower region of the tree are safe for rather large trees. Regardless, take heart that it is quite easy to tell when accuracy has been lost. Due to the precision of polynomial interpolation and the nice structure of d(T;n), you can tell that the code has likely lost accuracy if you observe irrational polynomial coefficients, a lack of integer roots, or end behavior that approaches negative infinity. 

## Tree Building
One crucial thing to note about tree building with this code is that there is no tree object. You build a tree by creating a node and keeping a reference to that node as you give
it children
### The Reference Method 
In the reference method, you use the fact that our addChild method returns a reference to the node that it adds and keep references to every new node you add. For the tree pictured below the reference method would look something like the following (for a descent at the root, change the root constructor parameters to {1, 1, true}): 

<img src="https://github.com/8wichmanndavid/REU-Decents-in-Labeled-Trees-/blob/master/images/IMG_1557.PNG" width="300">

```c++
Node* root = new Node{1, 0, false};
Node* a = root->addChild(true);
Node* b = root->addChild(false);
Node* c = b->addChild(true);
```

The parameter passed into addChild determines if the node will be created as a descent (if true) or an ascent (if false). 
### The Integer List Method
The integer list method condenses the tree's information into a list of integers which can then be easily stored in a database or sent between collaborators.
For those new to this encoding, it will help greatly to redraw the tree such that whenever a node has both descent children and ascent children, the descent children are drawn on the left. Then, follow these guidelines: 
1. The first integer in the list always either a 1 (if the root is a descent) or a 0 (if the root is an ascent). 
2. The next pair of integers represents the number of the root's children that are descents, then the number of the root's children that are ascents.
3. Continue traversing the tree breadth-first, recording each new vertex's children. When you reach a node that has no children, it is important to record that node's children as 0, 0. 
4. Once the list is complete, you can create the tree with the following two lines of code: 

```c++
int parameters[] = {0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0};
Node* root = buildTree(parameters);
```

Since this method is difficult to explain in an abstract way, here is an example: 

Consider the same tree pictured above. To encode this tree with the Integer List method we would do the following: 
1. We ensure the tree is drawn such that descents are always to the left of their ascent siblings
2. The root of the tree is an ascent so the first integer is a 0
3. The root has one descent child and one ascent child so the next two numbers are 1, 1
4. After visiting the root, the next vertex in the breadth-first search is the root's leftmost child. That vertex has no children so the next pair of numbers are 0, 0
5. The next vertex is the root's other child, which has only a descent, so its pair of numbers is 1, 0
6. Finally, we visit the lowest vertex in the tree and see that it has no children, which means that its pair of numbers is 0, 0

<img src="https://github.com/8wichmanndavid/REU-Decents-in-Labeled-Trees-/blob/master/images/IMG_1558.PNG" width="300">

### Adding a "Stem" to the tree
Once the tree is built, you may be interested in evaluating d(T;n) for a particular n > s. In this case, you can take advantage of our addStem function. For example, if you have built a tree of size 6 and wish to evaluate d(T;9), you might do the following:

```c++
int parameters[] = {0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0};
Node* root = buildTree(parameters);
root->addStem(9);
cout << root->des() << endl;
```

## Using the trees 

As described above, it is quite simple to evaluate d(T;n) for some particular n using our code. 

We also have some limited support for automating calculation of the actual polynomial d(T;n). Since the degree of the polynomial is known, we have written code that will accept a tree of size s and return a comma separated list of d(T;n) for all integers s+1 <= n <= s+h+2 (where h is the degree of the polynomial). Then, you can use some simple linear algebra to interpolate the polynomial through those points (in our case, in another piece of software we have automated the production of the appropriate Vandermonde matrix and used that to create the polynomial coefficients). 

Here's an example of what that might look like: 
```c++
int parameters[] = {0, 0, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
Node* root = buildTree(parameters);
root->getPolynomialPoints();
```

Which would print out the following: 

```
96, 152, 220,
```

And the coefficient vector could be solved with the following linear algebra: 

<img src="https://github.com/8wichmanndavid/REU-Decents-in-Labeled-Trees-/blob/master/images/IMG_1570.jpg" width="300">
