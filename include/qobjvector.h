#ifndef QOBJVECTOR_H
#define QOBJVECTOR_H
#include <qobject.h>
#include <qvector.h>
#include <qdatastream.h>

//为了解决QObject无法复制拷贝,导致QVecotr<QObject>无法使用的情况
//内部使用QVector<QObject*>实现
template <class T>
class QObjectVector
{
public:
    QObjectVector(QObject* parent, int size = 0);
    ~QObjectVector();

    //增加一个T, 并返回所增加的T的指针
    T* Append();
    //插入一个T, 并返回所插入的T的指针
    T* Insert(int index);
    //返回指定位置的T
    T* At(int index);
    //移除所有T
    void Clear();
    //移除指定位置的T
    void Remove(int index);
    //获取或设置Vector大小
    int Size() const;
    void Size(int size);
    //operator
    T* operator[]( int index ) const { return m_vector->at(index); }
    template <class T>
    friend QDataStream& operator<<(QDataStream& stream, const QObjectVector<T>& data);
    template <class T>
    friend QDataStream& operator>>(QDataStream& stream, QObjectVector<T>& data);

private:
    QVector<T*>* m_vector;
    QObject* m_parent;
};

template <class T>
QObjectVector<T>::QObjectVector( QObject* parent /*= NULL*/, int size /*= 0*/ )
{
    //父类不能为0
    Q_ASSERT(parent);
    m_parent = parent;
    m_vector = new QVector<T*>(size);
    foreach (T* x, *m_vector)
        x = new T(parent);
}

template <class T>
QObjectVector<T>::~QObjectVector()
{

}

template <class T>
T* QObjectVector<T>::Append()
{
    T* t = new T(m_parent);
    m_vector->append(t);
    return t;
}

template <class T>
T* QObjectVector<T>::Insert( int index )
{
    T* t = new T(m_parent);
    m_vector->insert(index, t);
    return t;
}

template <class T>
T* QObjectVector<T>::At( int index )
{
    return m_vector->at(index);
}

template <class T>
void QObjectVector<T>::Clear()
{
    foreach (T* t, *m_vector)
        delete t;
    m_vector->clear();
}

template <class T>
void QObjectVector<T>::Remove( int index )
{
    delete m_vector->at(index);
    m_vector->remove(index);
}

template <class T>
int QObjectVector<T>::Size() const
{
    return m_vector->size();
}

template <class T>
void QObjectVector<T>::Size( int size )
{
    if (size < 0)
        size = 0;
    int oldsize = m_vector->size();
    if (size == oldsize)
        return;
    else if (size > oldsize)
    {
        for (int i=0; i<(size-oldsize); i++)
            Append();
    }
    else
    {
        for (int i=oldsize; i>size; i--)
            Remove(i-1);
    }
}

template<class T>
QDataStream& operator<<(QDataStream& stream, const QObjectVector<T>& data)
{
    stream << (*data.m_vector);
    return stream;
}

template<class T>
QDataStream& operator>>(QDataStream& stream, QObjectVector<T>& data)
{
    __serial_current_obj.push(data.m_parent);
    stream >> (*data.m_vector);
    __serial_current_obj.pop();
    return stream;
}

#endif // qobjvector_h__
