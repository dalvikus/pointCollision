#ifndef __INTERVAL_H__
#define __INTERVAL_H__

class Interval
{
public:
    Interval(int min, int max);
    virtual ~Interval();
/*
    Interval(const Interval& that_i);
 */

public:
    bool getSubIntervalContains(int i, int& min, int& max);
    bool firstHalfContains(int i);

public:
    /** tell if given index is out of range */
    bool outOfRange(int i) {return i < m_min || i > m_max;}
    int min(void) {return m_min;}
    int max(void) {return m_max;}
private:
    int m_min;
    int m_max;
public:
    bool hasOnlyOnePoint(void) {return m_hasOnlyOnePoint;}
    bool minOfSecondHalf(void) {return m_minOfSecondHalf;}
private:
    bool m_hasOnlyOnePoint; /**< if set, it means 1) there is only one point in interval, so in general it cannot be divided into two sub-intervals, but if it must be so as combined with other direction, the point is contained in the second sub-interval and there is no the first sub-interval */
    int m_minOfSecondHalf; /**< it gives the second sub-interval: [m_minOfSecondHalf, m_max] even though there is no the first sub-interval (m_hasOnlyOnePoint = true) */
};

#endif  // !__INTERVAL_H__
