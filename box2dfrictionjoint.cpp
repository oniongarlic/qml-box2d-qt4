#include "box2dfrictionjoint.h"
#include "box2dbody.h"
#include "box2dworld.h"

Box2DFrictionJoint::Box2DFrictionJoint(QDeclarativeItem *parent) :
    Box2DJoint(parent),
    mFrictionJointDef(),
    mFrictionJoint(0)
{
}

void Box2DFrictionJoint::createJoint()
{
    mFrictionJointDef.Initialize(bodyA()->body(), bodyB()->body(), bodyA()->body()->GetWorldCenter());
    mFrictionJointDef.collideConnected = collideConnected();

    mFrictionJoint = static_cast<b2FrictionJoint*>(world()->CreateJoint(&mFrictionJointDef));
    mInitializePending = false;
}

void Box2DFrictionJoint::nullifyJoint()
{
    mFrictionJoint = 0;
}

void Box2DFrictionJoint::cleanup(b2World *world)
{
    if (mFrictionJoint && bodyA() && bodyB()) {
        mFrictionJoint->SetUserData(0);
        world->DestroyJoint(mFrictionJoint);
        mFrictionJoint = 0;
    }
}
