#ifndef LEAFACTION_H
#define LEAFACTION_H
namespace AI {
class LeafAction
{
public:
    LeafAction();
    virtual ~LeafAction();


    virtual void execute(void) = 0;

};
}

#endif // LEAFACTION_H
