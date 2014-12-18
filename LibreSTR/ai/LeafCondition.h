#ifndef LEAFCONDITION_H
#define LEAFCONDITION_H
namespace AI {
class LeafCondition
{
public:
    LeafCondition();
    virtual ~LeafCondition();

    virtual bool isPassed(void) = 0;

};

}
#endif // LEAFCONDITION_H
