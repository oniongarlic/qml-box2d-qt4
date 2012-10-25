#ifndef BOX2DFRICTIONJOINT_H
#define BOX2DFRICTIONJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2FrictionJoint;
class b2FrictionJointDef;

class Box2DFrictionJoint : public Box2DJoint
{
    Q_OBJECT
public:
    explicit Box2DFrictionJoint(QDeclarativeItem *parent = 0);

    void createJoint();
    void cleanup(b2World *world);
    void nullifyJoint();

signals:

public slots:

private:
    b2FrictionJointDef mFrictionJointDef;
    b2FrictionJoint *mFrictionJoint;
};

#endif // BOX2DFRICTIONJOINT_H
