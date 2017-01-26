#include <iostream>
#include <string>
using namespace std;

#include "Interval.h"
#include "Node.h"

Node::Node(Interval hInterval, Interval vInterval) : m_hInterval(hInterval), m_vInterval(vInterval), m_hits(0), m_nw_ptr(0), m_ne_ptr(0), m_sw_ptr(0), m_se_ptr(0), m_simplified(false)
{
}

Node::~Node()
{
    if (m_nw_ptr) {
        delete m_nw_ptr;
        m_nw_ptr = 0;
    }
    if (m_ne_ptr) {
        delete m_ne_ptr;
        m_ne_ptr = 0;
    }
    if (m_sw_ptr) {
        delete m_sw_ptr;
        m_sw_ptr = 0;
    }
    if (m_se_ptr) {
        delete m_se_ptr;
        m_se_ptr = 0;
    }
}

Node::Node(const Node& thatNode) : m_hInterval(thatNode.m_hInterval), m_vInterval(thatNode.m_vInterval)
{
    if (thatNode.m_nw_ptr) {
        m_nw_ptr = new Node(*thatNode.m_nw_ptr);
    } else {
        m_nw_ptr = 0;
    }
    if (thatNode.m_ne_ptr) {
        m_ne_ptr = new Node(*thatNode.m_ne_ptr);
    } else {
        m_ne_ptr = 0;
    }
    if (thatNode.m_sw_ptr) {
        m_sw_ptr = new Node(*thatNode.m_sw_ptr);
    } else {
        m_sw_ptr = 0;
    }
    if (thatNode.m_se_ptr) {
        m_se_ptr = new Node(*thatNode.m_se_ptr);
    } else {
        m_se_ptr = 0;
    }
}


void Node::add(int h, int v)
{
    if (m_hInterval.outOfRange(h))
        throw "h: out of range";
    if (m_vInterval.outOfRange(v))
        throw "v: out of range";

    if (m_hInterval.hasOnlyOnePoint() && m_vInterval.hasOnlyOnePoint()) {
        ++m_hits;
        return;
    }
    // at least one of intervals can be divided into two non-empty sub-intervals

    int hMin, hMax;
    bool hInFirstHalf = m_hInterval.getSubIntervalContains(h, hMin, hMax);
    int vMin, vMax;
    bool vInFirstHalf = m_vInterval.getSubIntervalContains(v, vMin, vMax);
    if (hInFirstHalf && vInFirstHalf) {
        if (!m_nw_ptr)
            m_nw_ptr = new Node(Interval(hMin, hMax), Interval(vMin, vMax));
        m_nw_ptr->add(h, v);
    } else if (hInFirstHalf && !vInFirstHalf) {
        if (!m_sw_ptr)
            m_sw_ptr = new Node(Interval(hMin, hMax), Interval(vMin, vMax));
        m_sw_ptr->add(h, v);
    } else if (!hInFirstHalf && vInFirstHalf) {
        if (!m_ne_ptr)
            m_ne_ptr = new Node(Interval(hMin, hMax), Interval(vMin, vMax));
        m_ne_ptr->add(h, v);
    } else {
        if (!m_se_ptr)
            m_se_ptr = new Node(Interval(hMin, hMax), Interval(vMin, vMax));
        m_se_ptr->add(h, v);
    }
}

bool Node::contains(int h, int v)
{
    if (m_hInterval.outOfRange(h))
        throw "h: out of range";
    if (m_vInterval.outOfRange(v))
        throw "v: out of range";

    if (m_hInterval.hasOnlyOnePoint() && m_vInterval.hasOnlyOnePoint()) {
        return true;
    }

    bool hInFirstHalf = m_hInterval.firstHalfContains(h);
    bool vInFirstHalf = m_vInterval.firstHalfContains(v);
    if (hInFirstHalf) {
        if (vInFirstHalf)
            return m_nw_ptr && m_nw_ptr->contains(h, v);
        return m_sw_ptr && m_sw_ptr->contains(h, v);
    }
    if (vInFirstHalf)
        return m_ne_ptr && m_ne_ptr->contains(h, v);
    return m_se_ptr && m_se_ptr->contains(h, v);
}

void Node::walk(int depth = 0)
{
    string indent_str(2 * depth, ' ');
    cout << indent_str << "[" << m_hInterval.min() << ", " << m_hInterval.max() << "], [" << m_vInterval.min() << ", " << m_vInterval.max() << "]" << endl;
    cout << indent_str << "NW: " << m_nw_ptr << endl;
    if (m_nw_ptr)
        m_nw_ptr->walk(depth + 1);
    cout << indent_str << "NE: " << m_ne_ptr << endl;
    if (m_ne_ptr)
        m_ne_ptr->walk(depth + 1);
    cout << indent_str << "SW: " << m_sw_ptr << endl;
    if (m_sw_ptr)
        m_sw_ptr->walk(depth + 1);
    cout << indent_str << "SE: " << m_se_ptr << endl;
    if (m_se_ptr)
        m_se_ptr->walk(depth + 1);
    cout << indent_str << "hits = " << m_hits << endl;
}


void Node::simplify(bool freeAllChildNodesOnceSimplified)
{
    if (m_nw_ptr)
        m_nw_ptr->simplify();
    if (m_ne_ptr)
        m_ne_ptr->simplify();
    if (m_sw_ptr)
        m_sw_ptr->simplify();
    if (m_se_ptr)
        m_se_ptr->simplify();

    if (m_hInterval.hasOnlyOnePoint() && m_vInterval.hasOnlyOnePoint()) {
        m_simplified = true;
        return;
    }

    // Check if two sub-intervals in h-direction can be simplified
    // There are three cases that can be simplified:
    //  Case 1. NW NE SW SE
    //      a(NW)  b(NE)
    //      c(SW)  d(SE)
    //  Case 2. NE SE; no h-direction
    //      a (NE)
    //      b (SE)
    //  Case 3. SW SE; no v-direction
    //      a(SW) b(SE)
    if (m_nw_ptr && m_ne_ptr && m_sw_ptr && m_se_ptr) { // Case 1
        if (m_nw_ptr->m_simplified && m_ne_ptr->m_simplified && m_sw_ptr->m_simplified && m_se_ptr->m_simplified) {
            // can be simplified below
        } else {
            return;
        }
    } else if (!m_nw_ptr && m_ne_ptr && !m_sw_ptr && m_se_ptr) { // Case 2
        if (
            m_hInterval.hasOnlyOnePoint() &&   // no h-direction
            m_ne_ptr->m_simplified && m_se_ptr->m_simplified
        ) {
            // can be simplified below
        } else {
            return;
        }
    } else if (!m_nw_ptr && !m_ne_ptr && m_sw_ptr && m_se_ptr) { // Case 3
        if (
            m_vInterval.hasOnlyOnePoint() &&   // no v-direction
            m_sw_ptr->m_simplified && m_se_ptr->m_simplified
        ) {
            // can be simplified below
        } else {
            return;
        }
    } else {
        return;
    }

    m_simplified = true;
    cout << "[" << m_hInterval.min() << ", " << m_hInterval.max() << "], [" << m_vInterval.min() << ", " << m_vInterval.max() << "]: simplified" << endl;

    if (!freeAllChildNodesOnceSimplified)
        return;

    if (m_nw_ptr) {
        delete m_nw_ptr;
        m_nw_ptr = 0;
    }
    if (m_ne_ptr) {
        delete m_ne_ptr;
        m_ne_ptr = 0;
    }
    if (m_sw_ptr) {
        delete m_sw_ptr;
        m_sw_ptr = 0;
    }
    if (m_se_ptr) {
        delete m_se_ptr;
        m_se_ptr = 0;
    }
}
