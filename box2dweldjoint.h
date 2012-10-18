#ifndef BOX2DWELDJOINT_H
#define BOX2DWELDJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2WeldJoint;
class b2WeldJointDef;

class Box2DWeldJoint : public Box2DJoint
{
    Q_OBJECT
public:
    explicit Box2DWeldJoint(QDeclarativeItem *parent = 0);

    void createJoint();
    void cleanup(b2World *world);
    void nullifyJoint();

signals:

public slots:

private:
    b2WeldJointDef mWeldJointDef;
    b2WeldJoint *mWeldJoint;
};

#endif // BOX2DWELDJOINT_H
