#ifndef __NODE_H__
#define __NODE_H__

#include "Interval.h"

class Node
{
public:
    Node(Interval hInterval, Interval vInterval);
    virtual ~Node();
    Node(const Node& thatNode);

public:
    /**
     * add a point specified by h and v to to the node that contains only the point;
     * if necessary, it creates all parent nodes
     */
    void add(int h, int v);

    /**
     * tell if all child nodes contains the point specified by h and v
     * once simplified by calling simplify, use contains2 below
     */
    bool contains(int h, int v);

    void walk(int depth);

private:
    Interval m_hInterval;
    Interval m_vInterval;

private:
    /**
     * tell how many hits are in the smallest node, which contains one one point; 0 for other nodes
     *
     * this is an example of information for the smallest node; not used in current application
     */
    unsigned m_hits;

private:
    Node* m_nw_ptr;
    Node* m_ne_ptr;
    Node* m_sw_ptr;
    Node* m_se_ptr;

public:
    /** if all child nodes exist, it can be simplified in order to check quickly if a node contains a point */
    void simplify(bool freeAllChildNodesOnceSimplified = false);
    /** same as contains but it is better once simplified */
    bool contains2(int h, int v) {return m_simplified ? true : contains(h, v);}
private:
    bool m_simplified; /**< set if all children nodes are occupied */
};

#endif  // !__NODE_H__
