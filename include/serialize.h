#ifndef SERIALIZE_H
#define SERIALIZE_H

#include <QDataStream>
#include <QStack>
#include <QHash>

//���л�ʱ,���浱ǰ�����һ����ջ
extern QStack<QObject*> __serial_current_obj;
//QMetaObject��������һ��ӳ��
QHash<QString, const QMetaObject*>& __metaObjects_hash();

template <class T>
class SerializeClassRegister
{
public:
    SerializeClassRegister()
    {
        __metaObjects_hash().insert( QString(T::staticMetaObject.className()),
                                    &(T::staticMetaObject) );
    }
};

//ע������л�����,���� ����̳���QObject
#define SERIALIZE_ENABLE_CLASS(classname) \
    friend QDataStream& operator<<(QDataStream&, classname *); \
    friend QDataStream& operator<<(QDataStream&, classname &); \
    friend QDataStream& operator>>(QDataStream&, classname *&); \
    friend QDataStream& operator>>(QDataStream&, classname &); \
    virtual void __serialize_helper(QDataStream&); \
    virtual void __de_serialize_helper(QDataStream&);

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
//Q_ASSERT(dynamic_cast<classname*>(data));
//stream << (*data);
//return stream;
#define SERIALIZE_BEGIN(classname) \
SerializeClassRegister<classname> __##classname##_SerializeClassregister; \
void classname::__serialize_helper(QDataStream& stream) \
{ \
    stream<< QString(#classname); \
    stream<<(*this); \
} \
QDataStream& operator<<(QDataStream& stream, classname * data) \
{ \
    data->__serialize_helper(stream); \
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
//Q_ASSERT(!__serial_current_obj.isEmpty());
//data = new classname (__serial_current_obj.top());
//stream >> (*data);
//return stream;
#define DE_SERIALIZE_BEGIN(classname) \
void classname::__de_serialize_helper(QDataStream& stream) \
{\
    stream>>(*this); \
}\
QDataStream& operator>>(QDataStream& stream, classname *& data) \
{ \
    QString __classname__; \
    stream>>__classname__; \
    const QMetaObject* mobj = __metaObjects_hash().value(__classname__); \
    QObject* __parent__ = __serial_current_obj.top(); \
    data = (classname *)mobj->newInstance(Q_ARG(QObject*, __parent__)); \
    if (data == NULL) \
    { \
        stream.setStatus(QDataStream::ReadCorruptData); \
        return stream; \
    } \
    data->__de_serialize_helper(stream); \
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
