#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <QDataStream>
#include <QStack>

//���л�ʱ,���浱ǰ�����һ����ջ
extern QStack<QObject*> __serial_current_obj;

//ע������л�����,���� ����̳���QObject
#define SERIALIZE_ENABLE_CLASS(classname) \
    friend QDataStream& operator<<(QDataStream&, classname *); \
    friend QDataStream& operator<<(QDataStream&, classname &); \
    friend QDataStream& operator>>(QDataStream&, classname *&); \
    friend QDataStream& operator>>(QDataStream&, classname &);  

//ע������л��� enum
#define SERIALIZE_ENABLE_ENUM(enumname) \
inline QDataStream& operator>>(QDataStream& stream, enumname & data) \
{ \
    stream >> (int&)data; \
    return stream; \
} \
inline QDataStream& operator<<(QDataStream& stream, enumname & data) \
{ \
    stream << (int&)data; \
    return stream;\
}

//���л�
#define SERIALIZE_BEGIN(classname) \
QDataStream& operator<<(QDataStream& stream, classname * data) \
{ \
    Q_ASSERT(dynamic_cast<classname*>(data)); \
    stream << (*data); \
    return stream; \
} \
QDataStream& operator<<(QDataStream& stream, classname & data) \
{ \
    Q_ASSERT(dynamic_cast<QObject*>( &data )); \
    stream<< QString(#classname);//data .metaObject()->className()); 

//���л���ͨ����
#define SERIALIZE_VAR(var) \
    stream<<data. var;

//���л�һ������
#define SERIALIZE_BASE(basename) \
    stream<<( basename & )data;

#define  SERIALIZE_END \
    return stream; \
}

//�����л�
#define DE_SERIALIZE_BEGIN(classname) \
QDataStream& operator>>(QDataStream& stream, classname *& data) \
{ \
    Q_ASSERT(!__serial_current_obj.isEmpty()); \
    data = new classname (__serial_current_obj.top()); \
    stream >> (*data); \
    return stream; \
} \
QDataStream& operator>>(QDataStream& stream, classname & data) \
{ \
    QObject* __current = dynamic_cast<QObject*>(&data); \
    Q_ASSERT(__current); \
    __serial_current_obj.push(__current); \
    QString __classname__; \
    stream>>__classname__; \
    if (QString(#classname) != __classname__) \
    { \
    stream.setStatus(QDataStream::ReadCorruptData); \
    __serial_current_obj.pop(); \
    return stream; \
    }

//�����л���ͨ����
#define DE_SERIALIZE_VAR(var) \
    stream>> data. var;

//�����л�һ������
#define DE_SERIALIZE_BASE(basename) \
    stream>>( basename & )data;

#define DE_SERIALIZE_END \
    __serial_current_obj.pop(); \
    return stream; \
}

#endif // serialize_h
