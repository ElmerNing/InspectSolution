#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <QDataStream>
#include <QStack>
#include <QHash>

//注册可序列化的类,此类 必须继承于QObject
#define SERIALIZE_ENABLE_CLASS(classname) \
    friend QDataStream& operator<<(QDataStream&, const classname &); \
    friend QDataStream& operator>>(QDataStream&, classname &); 


//注册可序列化的 enum
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

//序列化
//Q_ASSERT(dynamic_cast<classname*>(data));
//stream << (*data);
//return stream;
#define SERIALIZE_BEGIN(classname) \
QDataStream& operator<<(QDataStream& stream, const classname & data) \
{ \
    stream<< QString(#classname);//data .metaObject()->className());

//序列化普通变量
#define SERIALIZE_VAR(var) \
    stream<<data. var;

//序列化一个基类
#define SERIALIZE_BASE(basename) \
    stream<<( basename & )data;

#define  SERIALIZE_END \
    return stream; \
}

//反序列化
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

//反序列化普通变量
#define DE_SERIALIZE_VAR(var) \
    stream>> data. var;

//反序列化一个基类
#define DE_SERIALIZE_BASE(basename) \
    stream>>( basename & )data;

#define DE_SERIALIZE_END \
    return stream; \
}

#endif // serialize_h
