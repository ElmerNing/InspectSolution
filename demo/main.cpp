
#include "stdafx.h"
#include <QCoreApplication>
#include "solution_sc.h"
#include "inspectdata.h"
#include "datadevice.h"

int main(int argc, char *argv[])
{
    int grpQty = 10;
    BlockInfo info(grpQty);
    for (int i=0; i<grpQty; i++)
    {
        info.SetGrp(i, 2, 480);
    }
    int blockSize = info.GetBlockSize();
    InspectData data;
    data.Init(info);

    uchar* p = new uchar[blockSize];
    for (int i=0; i<blockSize; i++)
    {
        p[i] = (i%512)/2;
    }
    data.OnReceiveBlock(p,0);

    QFile file("a.dat");
    file.open(QFile::ReadWrite);
    QDataStream out(&file);
    out<<data;
    int end = 333;
    out<<end;
    file.close();

    file.open(QFile::ReadWrite);
    QDataStream in(&file);
    InspectData data2;
    in>>data2;
    int start = 0;
    in>>start;

}
