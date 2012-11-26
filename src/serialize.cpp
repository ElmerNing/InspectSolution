#include "stdafx.h"

QStack<QObject*> __serial_current_obj;

/*
    序列化,线程不安全的
    
    用法

    in myclass.h

Class myclass : QObject
{
    int member1;
    QString member2;
    QVector member3;
    enum member4;

    DE_SERIALIZE_ENABLE(myclass);
    SERIALIZE_ENABLE(myclass);
}

    in myclass.cpp

DE_SERIALIZE_BEGIN
    DE_SERIALIZE_VAR(member1)
    DE_SERIALIZE_VAR(member2)
    DE_SERIALIZE_VAR(member3)
    DE_SERIALIZE_enum(member4)
DE_SERIALIZE_END

SERIALIZE_BEGIN
    SERIALIZE_VAR(member1)
    SERIALIZE_VAR(member2)
    SERIALIZE_VAR(member3)
    SERIALIZE_enum(member4)
SERIALIZE_END

    then
    QDataStream out(&file);
    out << myclass;
    or
    QDataStream in(&file);
    in >> myclass;
*/
