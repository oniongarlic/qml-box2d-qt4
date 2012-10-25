#include "box2dfrictionjoint.h"
#include "box2dbody.h"
#include "box2dworld.h"

Box2DFrictionJoint::Box2DFrictionJoint(QDeclarativeItem *parent) :
    Box2DJoint(parent),
    mFrictionJointDef(),
    mFrictionJoint(0)
{
}

float Box2DFrictionJoint::maxForce() const
{
    return mFrictionJointDef.maxForce;
}

void Box2DFrictionJoint::setMaxForce(float force)
{
    if (mFrictionJointDef.maxForce == force)
        return;

    mFrictionJointDef.maxForce = force;
    if (mFrictionJoint)
        mFrictionJoint->SetMaxForce(force);
    emit maxForceChanged();
}

float Box2DFrictionJoint::maxTorque() const
{
    return mFrictionJointDef.maxTorque;
}

void Box2DFrictionJoint::setMaxTorque(float torque)
{
    if (mFrictionJointDef.maxTorque == torque)
        return;

    mFrictionJointDef.maxTorque = torque;
    if (mFrictionJoint)
        mFrictionJoint->SetMaxTorque(torque);
    emit maxTorqueChanged();
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
