#include "box2dmousejoint.h"
#include "box2dbody.h"
#include "box2dworld.h"

Box2DMouseJoint::Box2DMouseJoint(QDeclarativeItem *parent) :
    Box2DJoint(parent),
    mMouseJointDef(),
    mMouseJoint(0)
{
}

float Box2DMouseJoint::maxForce() const
{
    return mMouseJointDef.maxForce;
}

void Box2DMouseJoint::setMaxForce(float force)
{
    if (mMouseJointDef.maxForce == force)
        return;

    mMouseJointDef.maxForce = force;
    if (mMouseJoint)
        mMouseJoint->SetMaxForce(force);
    emit maxForceChanged();
}

float Box2DMouseJoint::frequencyHz() const
{
    return mMouseJointDef.frequencyHz;
}

void Box2DMouseJoint::setFrequencyHz(float frequency)
{
    if (mMouseJointDef.frequencyHz == frequency)
        return;

    mMouseJointDef.frequencyHz = frequency;
    if (mMouseJoint)
        mMouseJoint->SetFrequency(frequency);
    emit frequencyHzChanged();
}

float Box2DMouseJoint::dampingRatio() const
{
    return mMouseJointDef.dampingRatio;
}

void Box2DMouseJoint::setDampingRatio(float damping)
{
    if (mMouseJointDef.dampingRatio == damping)
        return;

    mMouseJointDef.dampingRatio = damping;
    if (mMouseJoint)
        mMouseJoint->SetDampingRatio(damping);
    emit dampingRatioChanged();
}

QPointF const Box2DMouseJoint::reactionForce(float inv)
{
    const b2Vec2 rf = mMouseJoint->GetReactionForce(inv);

    return QPointF(rf.x, rf.y);
}

float Box2DMouseJoint::reactionTorque(float inv)
{
    return mMouseJoint->GetReactionTorque(inv);
}

void Box2DMouseJoint::setTarget(const QPointF &targetxy)
{
    if (mMouseJoint) {
        mMouseJoint->SetTarget(b2Vec2(targetxy.x() / scaleRatio, -targetxy.y() / scaleRatio));
    } else {
        mMouseJointDef.target = b2Vec2(x() / scaleRatio, -y() / scaleRatio);
    }
}

QPointF const Box2DMouseJoint::getTarget()
{
    const b2Vec2 rf = mMouseJoint->GetTarget();

    return QPointF(rf.x, rf.y);
}

void Box2DMouseJoint::createJoint()
{
    mMouseJointDef.collideConnected = collideConnected();
    mMouseJointDef.bodyA = bodyA()->body();
    mMouseJointDef.bodyB = bodyB()->body();
    mMouseJointDef.target = b2Vec2(x() / scaleRatio, -y() / scaleRatio);

    mMouseJoint = static_cast<b2MouseJoint*>(world()->CreateJoint(&mMouseJointDef));
    mMouseJointDef.bodyB->SetAwake(true);
    mInitializePending = false;
}

void Box2DMouseJoint::nullifyJoint()
{
    targetIsValid=false;
    mMouseJoint = 0;
}

void Box2DMouseJoint::cleanup(b2World *world)
{
    if (mMouseJoint && bodyA() && bodyB()) {
        mMouseJoint->SetUserData(0);
        world->DestroyJoint(mMouseJoint);
        mMouseJoint = 0;
    }
}
