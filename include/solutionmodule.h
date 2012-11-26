#ifndef SOLUTIONMODULE_H
#define SOLUTIONMODULE_H

class Solution;

//solution的部件,如FocaLaw, GroupLaw, BeamLaw, Gconfig, Wedge, 
//统一父类,提供一些共用函数
class SolutionModule : public QObject
{
public:
    SolutionModule(QObject* parent = NULL);
    //获取拥有此对象的Solution指针,Null着表示此对象,不属于任何Solution
    Solution* OwnedSolution();
    //是否被一个Solution拥有
    bool IsOwned();
    //获取此Solution中的速度
    float Velocity();
    //禁止使用setParent
    void setParent(QObject *) {Q_ASSERT(false);}

    //默认值 
    virtual void Default() = 0;

private:
    Solution* m_solution;
};




#endif 