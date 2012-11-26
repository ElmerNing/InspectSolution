#ifndef SOLUTIONMODULE_H
#define SOLUTIONMODULE_H

class Solution;

//solution�Ĳ���,��FocaLaw, GroupLaw, BeamLaw, Gconfig, Wedge, 
//ͳһ����,�ṩһЩ���ú���
class SolutionModule : public QObject
{
public:
    SolutionModule(QObject* parent = NULL);
    //��ȡӵ�д˶����Solutionָ��,Null�ű�ʾ�˶���,�������κ�Solution
    Solution* OwnedSolution();
    //�Ƿ�һ��Solutionӵ��
    bool IsOwned();
    //��ȡ��Solution�е��ٶ�
    float Velocity();
    //��ֹʹ��setParent
    void setParent(QObject *) {Q_ASSERT(false);}

    //Ĭ��ֵ 
    virtual void Default() = 0;

private:
    Solution* m_solution;
};




#endif 