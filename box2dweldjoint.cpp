#include "box2dweldjoint.h"
#include "box2dbody.h"
#include "box2dworld.h"

Box2DWeldJoint::Box2DWeldJoint(QDeclarativeItem *parent) :
    Box2DJoint(parent),
    mWeldJointDef(),
    mWeldJoint(0)
{
}

void Box2DWeldJoint::createJoint()
{
    mWeldJointDef.Initialize(bodyA()->body(), bodyB()->body(), bodyA()->body()->GetWorldCenter());
    mWeldJointDef.collideConnected = collideConnected();

    mWeldJoint = static_cast<b2WeldJoint*>(world()->CreateJoint(&mWeldJointDef));
    mInitializePending = false;
}

void Box2DWeldJoint::nullifyJoint()
{
    mWeldJoint = 0;
}

void Box2DWeldJoint::cleanup(b2World *world)
{
    if (mWeldJoint && bodyA() && bodyB()) {
        mWeldJoint->SetUserData(0);
        world->DestroyJoint(mWeldJoint);
        mWeldJoint = 0;
    }
}
