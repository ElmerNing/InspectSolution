#ifndef QRANGE_H
#define QRANGE_H
#include <qmap.h>

template <class T>
class QRange
{
public:
    QRange(){};
    QRange(T start, T end){ m_start = start; m_end = end;}

    inline const T& Start() const { return m_start; }
    inline T& Start() { return m_start; }
    inline void Start(T start){ m_start = start; }

    inline const T& End() const {return m_end;}
    inline T& End()  { return m_end; }
    inline void End(T end) { m_end = end; }

    inline T Range() const { return m_end - m_start; }
    inline void Range(T range) { m_end = m_start + range; }

    bool Contain(T val) {return (val >= m_start) && (val <= m_end);}

private:
    T m_start;
    T m_end;
};

template <class T>
QDataStream& operator<<(QDataStream & stream, const QRange<T> & range)
{
    stream<<range.Start()<<range.End();
    return stream;
}

template <class T>
QDataStream& operator>>(QDataStream & stream, QRange<T> & range)
{
    stream>>range.Start()>>range.End();
    return stream;
}

typedef QRange<float> QRangeF;


#endif // qrange_h__