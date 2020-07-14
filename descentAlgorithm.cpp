#include <cstddef>
#include <list>
#include <iostream>

#include "descentAlgorithm.hpp"

using namespace std;

/*********************
 * Factorial and nCr *
 ********************/


// lmao no built in factorial
size_t fact(size_t n){
    return (n==0) || (n==1) ? 1 : n* fact(n-1);
}

// and here's an N choose R I took from stackoverflow
size_t NCR(size_t n, size_t r)
{
    if (r == 0) return 1;

    /*
     Extra computation saving for large R,
     using property:
     N choose R = N choose (N-R)
    */
    if (r > n / 2) return NCR(n, n - r); 

    long res = 1; 

    for (size_t k = 1; k <= r; ++k)
    {
        res *= n - k + 1;
        res /= k;
    }

    return res;
}

// This constructor is used only for the deep-copy methods. The parent must be passed in and the 
// child list must be empty
Node::Node(Node* parent) : parent_{parent}, isDescent_{false}, size_{1}, numDescents_{0} {}

Node::Node(size_t size, size_t numDescents, bool isDescent) : 
    parent_{nullptr}, isDescent_{isDescent}, size_{size}, numDescents_{numDescents} {}

Node::Node() : parent_{nullptr}, isDescent_{false}, size_{1}, numDescents_{0} {}

bool Node::operator==(const Node& rhs) const {
    return this == &rhs;
}

bool Node::operator!=(const Node& rhs) const {
    return !(*this == rhs);
}

void Node::kidlessTransfer(Node& original) {
    isDescent_ = original.isDescent_;
    size_ = original.size_;
    numDescents_ = original.numDescents_;
}


void Node::ancestorsLostDescentPoints(size_t num) {
    numDescents_ -= num;
    if (parent_ != nullptr) {
        parent_->ancestorsLostDescentPoints(num);
    }
}


void Node::ancestorsLostSubtree(size_t size) {
    size_ -= size;
    if (parent_ != nullptr) {
        parent_->ancestorsLostSubtree(size);
    }
}

void Node::ascentifyCopy(Node& original, Node& changePoint) {
    kidlessTransfer(original);
    for (list<Node*>::iterator it=original.children_.begin(); 
            it != original.children_.end(); ++it) { 
        Node* temp = new Node{this};
        children_.push_back(temp);
        temp->ascentifyCopy(**it, changePoint);
    }
}


void Node::pruneCopy(Node& original, Node& changePoint) {
    kidlessTransfer(original);
    if (original != changePoint) {
        for (list<Node*>::iterator it=original.children_.begin(); 
            it != original.children_.end(); ++it) { 
        Node* temp = new Node{this};
        children_.push_back(temp);
        temp->pruneCopy(**it, changePoint);
        }
    } else {
        ancestorsLostSubtree(size_);
        ancestorsLostDescentPoints(numDescents_);
        if(parent_ != nullptr) {
            parent_->children_.remove(this);       
        }
    }
}

size_t Node::productOfDescendantSize() {
    if (size_ == 0) {
        return 1;
    }
    size_t meAndMyKids = size_;
    for (list<Node*>::iterator it=children_.begin(); it != children_.end(); ++it) { 
        meAndMyKids *= (**it).productOfDescendantSize();
    }
    return meAndMyKids;
}

Node* Node::findMaximal() {
    if (isDescent_== true){
        return this;
    } else {
        for (list<Node*>::iterator it=children_.begin(); it != children_.end(); ++it) { 
        Node* maxCandidate = (**it).findMaximal();
        if (maxCandidate != nullptr) {
            return maxCandidate;
        }
        }
    }
    // this should never be reached, but I think it would cause a compiler error if left out 
    // (no return statement on the else branch)
    return nullptr;
}

// The moment of truth
size_t Node::des() {
    if (numDescents_ == 0) {
        cout << "Base Case!" << endl;
        cout << "    this base case returned " << fact(size_) / productOfDescendantSize() << endl;
        if (size_ == 0) {
            return 1;
        }
        return fact(size_) / productOfDescendantSize();
    } else {
        Node* maximal = findMaximal();
        /*
        cout << "I made it here with numDescents_ = " << numDescents_ << endl;
        if (maximal == nullptr) {
            cout << "yeah, it's null bro" << endl;
        }
        cout << "information about maximal: size = " << maximal->size_ << endl;
        */
        maximal->isDescent_ = false;
        maximal->ancestorsLostDescentPoints(1);
        Node* subtreeBranch = new Node{1, 0, false};
        Node* ascentifyBranch = new Node{1, 0, false};
        Node* pruneBranch = new Node{1, 0, false};
        subtreeBranch->ascentifyCopy(*maximal, *maximal);
        ascentifyBranch->ascentifyCopy(*this, *maximal);
        pruneBranch->pruneCopy(*this, *maximal);
        /*
        cout << "information about ascentify and prune: ascentify size = " << ascentifyBranch->size_ << ". ascentify descents = " << ascentifyBranch->numDescents_ << "." << endl;
        cout << "prune size = " << pruneBranch->size_ << ". prune descents = " << pruneBranch->numDescents_ << endl; 
        */
        size_t A = subtreeBranch->des();
        size_t B = ascentifyBranch->des();
        size_t C = pruneBranch->des();
        cout << "root size = " << size_ << ". maximal size = " << maximal->size_ << ". A = " << A << ". B = " << B << ". C = " << C << endl;
        return NCR(size_, maximal->size_)*A*C - B;
    }
}

Node* Node::addChild(bool isDescent) {
    Node* temp = new Node{this};
    temp->size_ = 1;
    temp->isDescent_ = false;
    temp->numDescents_ = 0;
    if (isDescent) {
        ancestorsLostDescentPoints(-1);
        temp->isDescent_ = true;
        temp->numDescents_ = 1;
    }
    ancestorsLostSubtree(-1);
    children_.push_back(temp);
    return temp;
}

