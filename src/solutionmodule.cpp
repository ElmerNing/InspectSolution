#include "stdafx.h"
#include "solutionmodule.h"
#include "solution.h"

SolutionModule::SolutionModule( QObject* parent ) :
QObject(parent),
m_solution(NULL)
{
}

Solution* SolutionModule::OwnedSolution()
{
    if (m_solution == NULL)
    {
        QObject* obj = (QObject*)this;
        while (obj != NULL)
        {
            m_solution = dynamic_cast<Solution*>(obj) ;
            if (m_solution)
                break;
            else
                obj = obj->parent();
        }
        m_solution = dynamic_cast<Solution*>(obj);
        return m_solution;
    }
    else
        return m_solution;
}
