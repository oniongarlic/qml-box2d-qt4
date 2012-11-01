#include "box2dweldjoint.h"
#include "box2dbody.h"
#include "box2dworld.h"

Box2DWeldJoint::Box2DWeldJoint(QDeclarativeItem *parent) :
    Box2DJoint(parent),
    mWeldJointDef(),
    mWeldJoint(0)
{
}

float Box2DWeldJoint::frequencyHz() const
{
    return mWeldJointDef.frequencyHz;
}

void Box2DWeldJoint::setFrequencyHz(float frequency)
{
    if (mWeldJointDef.frequencyHz == frequency)
        return;

    mWeldJointDef.frequencyHz = frequency;
    if (mWeldJoint)
        mWeldJoint->SetFrequency(frequency);
    emit frequencyHzChanged();
}

float Box2DWeldJoint::dampingRatio() const
{
    return mWeldJointDef.dampingRatio;
}

void Box2DWeldJoint::setDampingRatio(float damping)
{
    if (mWeldJointDef.dampingRatio == damping)
        return;

    mWeldJointDef.dampingRatio = damping;
    if (mWeldJoint)
        mWeldJoint->SetDampingRatio(damping);
    emit dampingRatioChanged();
}

QPointF const Box2DWeldJoint::reactionForce(float inv)
{
    const b2Vec2 rf = mWeldJoint->GetReactionForce(inv);
    
    return QPointF(rf.x, rf.y);
}

float Box2DWeldJoint::reactionTorque(float inv)
{
    return mWeldJoint->GetReactionTorque(inv);
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
