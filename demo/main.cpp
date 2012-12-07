
#include "stdafx.h"
#include <QCoreApplication>
#include "solution_sc.h"


int main(int argc, char *argv[])
{/*
    SCsolution solution;
    solution.m_velocity = 111.11f;
    solution.m_config.DampUt1(UD_500R);
    solution.m_config.DampUt2(UD_500R);
    solution.m_config.EncoderPolarX(EP_REVERSE);
    solution.m_config.EncoderStatusX(ES_PAUSE);
    for (int i=0; i<20; i++)
    {
        GroupLaw* group = solution.GroupLaws().Append();
        QObjectVector<BeamLaw> beamlaws = group->BeamLaws();
        beamlaws.Clear();
        for (int i=0; i<50; i++)
        {
            BeamLaw* beam = beamlaws.Append();
            beam->Angle(90);
            beam->FocusDepth(333);
        }
    }

    {
        QFile file("aaa.ccc");
        QDataStream stream(&file);
        file.open(QFile::ReadWrite);
        stream<<solution;
        file.close();
    }
    {
        QFile file("aaa.ccc");
        QDataStream stream(&file);
        file.open(QFile::ReadWrite);
        SCsolution ss;
        stream>>ss;
        file.close();
    }*/
    
}
