#include "box2dropejoint.h"
#include "box2dbody.h"
#include "box2dworld.h"

Box2DRopeJoint::Box2DRopeJoint(QDeclarativeItem *parent) :
    Box2DJoint(parent),
    mRopeJointDef(),
    mRopeJoint(0)
{
}

QPointF Box2DRopeJoint::localAnchorA() const
{
    return QPointF(mRopeJointDef.localAnchorA.x, -mRopeJointDef.localAnchorA.y);
}

void Box2DRopeJoint::setLocalAnchorA(const QPointF &anchor)
{
    if (mRopeJointDef.localAnchorA == b2Vec2(anchor.x() / scaleRatio, -anchor.y() / scaleRatio))
        return;

    mRopeJointDef.localAnchorA = b2Vec2(anchor.x() / scaleRatio, -anchor.y() / scaleRatio);

    emit localAnchorAChanged();
}

QPointF Box2DRopeJoint::localAnchorB() const
{
    return QPointF(mRopeJointDef.localAnchorB.x, -mRopeJointDef.localAnchorB.y);
}

void Box2DRopeJoint::setLocalAnchorB(const QPointF &anchor)
{
    if (mRopeJointDef.localAnchorB == b2Vec2(anchor.x() / scaleRatio, -anchor.y() / scaleRatio))
        return;

    mRopeJointDef.localAnchorB = b2Vec2(anchor.x() / scaleRatio, -anchor.y() / scaleRatio);

    emit localAnchorBChanged();
}

QPointF const Box2DRopeJoint::reactionForce(float inv)
{
    const b2Vec2 rf = mRopeJoint->GetReactionForce(inv);

    return QPointF(rf.x, rf.y);
}

float Box2DRopeJoint::reactionTorque(float inv)
{
    return mRopeJoint->GetReactionTorque(inv);
}

float Box2DRopeJoint::getMaxLength()
{
    if (mRopeJoint)
        return mRopeJoint->GetMaxLength();
    return mRopeJointDef.maxLength;
}

void Box2DRopeJoint::setMaxLength(float len)
{
    mRopeJointDef.maxLength = len / scaleRatio;
    if (mRopeJoint)
        mRopeJoint->SetMaxLength(mRopeJointDef.maxLength);
}

void Box2DRopeJoint::createJoint()
{
    mRopeJointDef.collideConnected = collideConnected();

    mRopeJointDef.bodyA = bodyA()->body();
    mRopeJointDef.bodyB = bodyB()->body();

    mRopeJoint = static_cast<b2RopeJoint*>(world()->CreateJoint(&mRopeJointDef));
    mInitializePending = false;
}

void Box2DRopeJoint::nullifyJoint()
{
    mRopeJoint = 0;
}

void Box2DRopeJoint::cleanup(b2World *world)
{
    if (mRopeJoint && bodyA() && bodyB()) {
        mRopeJoint->SetUserData(0);
        world->DestroyJoint(mRopeJoint);
        mRopeJoint = 0;
    }
}
