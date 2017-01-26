#include "Interval.h"

Interval::Interval(int min, int max)
{
    if (min > max)
        throw "min > max";

    m_min = min;
    m_max = max;
    int points = (m_max - m_min) + 1;
    int pointsInFirstHalf = points / 2;
    m_hasOnlyOnePoint = pointsInFirstHalf == 0;
    m_minOfSecondHalf = m_min + pointsInFirstHalf;
}

Interval::~Interval()
{
}

/*
Interval::Interval(const Interval& that_i)
{
    cout << "Interval::Interval(const Interval&)(" << this << " <- " << &that_i << "): [" << that_i.m_min << ", " << that_i.m_max << "]" << endl;
    m_min = that_i.m_min;
    m_max = that_i.m_max;
}
 */


bool Interval::getSubIntervalContains(int i, int& min, int& max)
{
    if (outOfRange(i))
        throw "i: out of range";

    if (m_hasOnlyOnePoint) {
        min = m_min;
        max = m_max;
        return false;
    }

    if (i < m_minOfSecondHalf) {
        min = m_min;
        max = m_minOfSecondHalf - 1;
        return true;
    }
    min = m_minOfSecondHalf;
    max = m_max;
    return false;
}

bool Interval::firstHalfContains(int i)
{
    if (outOfRange(i))
        throw "i: out of range";

    return m_hasOnlyOnePoint ? false : i < m_minOfSecondHalf;
}
