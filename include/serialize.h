#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <QDataStream>
#include <QStack>
#include <QHash>

//ע������л�����,���� ����̳���QObject
#define SERIALIZE_ENABLE_CLASS(classname) \
    friend QDataStream& operator<<(QDataStream&, const classname &); \
    friend QDataStream& operator>>(QDataStream&, classname &); 


//ע������л��� enum
#define SERIALIZE_ENABLE_ENUM(enumname) \
inline QDataStream& operator>>(QDataStream& stream, enumname & data) \
{ \
    stream >> (int&)data; \
    return stream; \
} \
inline QDataStream& operator<<(QDataStream& stream, const enumname & data) \
{ \
    stream << (int&)data; \
    return stream;\
}

//���л�
//Q_ASSERT(dynamic_cast<classname*>(data));
//stream << (*data);
//return stream;
#define SERIALIZE_BEGIN(classname) \
QDataStream& operator<<(QDataStream& stream, const classname & data) \
{ \
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
QDataStream& operator>>(QDataStream& stream, classname & data) \
{ \
    QString __classname__; \
    stream>>__classname__; \
    if (QString(#classname) != __classname__) \
    { \
        stream.setStatus(QDataStream::ReadCorruptData); \
        return stream; \
    }

//�����л���ͨ����
#define DE_SERIALIZE_VAR(var) \
    stream>> data. var;

//�����л�һ������
#define DE_SERIALIZE_BASE(basename) \
    stream>>( basename & )data;

#define DE_SERIALIZE_END \
    return stream; \
}

#endif // serialize_h
