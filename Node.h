/**
 * descentAlgorithm.hpp
 * Describing our trees as collections of Node objects. There
 * is no "tree" object. The algorithm will recognize each node 
 * as the root of its own tree. 
 */

#ifndef DESCENTALGORITHM_HPP_INCLUDED
#define DESCENTALGORITHM_HPP_INCLUDED

#include <cstddef>
#include <list>

using namespace std;

class Node {
    public: 
        Node* parent_;
        list<Node*> children_;
        bool isDescent_;
        size_t size_;
        size_t numDescents_; // inclusive
        // Constructor stuff 
        Node();
        Node(Node* parent);
        Node(size_t size, size_t numDescents, bool isDescent);

        // Equality stuff
        bool operator==(const Node& rhs) const;
        bool operator!=(const Node& rhs) const;
        
        /************************
         * Algorithm Methods ****
         ************************/ 
        
        // Partial node-copy (ignores children and parents)
        void kidlessTransfer(Node& original);

        // Helpers for ascentify and prune (the deep-copiers)
        void ancestorsLostDescentPoints(size_t num);
        void ancestorsLostSubtree(size_t size);

        // Modified deep-copiers 
        void ascentifyCopy(Node& original, Node& changePoint);
        void pruneCopy(Node& original, Node& changePoint);

        // Helper for calculating natural labelings 
        size_t productOfDescendantSize();

        // Finding a maximal descent point
        Node* findMaximal();
        
        size_t sumOfHooklengthsOfMaximalDecents();

        // The Big Bad Boy Himself
        size_t des();
        
        size_t baseCase();
        
        //find points for polinomial
        void getPolynomialPoints();

        /******************************
         * Tree Constructing Methods***
         ******************************/
        Node* addChild(bool isDescent);
        void combineTree(Node* root);
        Node* addStem(int n);
};

#endif