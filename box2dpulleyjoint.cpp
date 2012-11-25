#include "box2dpulleyjoint.h"
#include "box2dbody.h"
#include "box2dworld.h"

Box2DPulleyJoint::Box2DPulleyJoint(QDeclarativeItem *parent) :
    Box2DJoint(parent),
    mPulleyJointDef(),
    mPulleyJoint(0)
{
}

float Box2DPulleyJoint::ratio() const
{
    return mPulleyJointDef.ratio;
}

void Box2DPulleyJoint::setRatio(float ratio)
{
    if (mPulleyJointDef.ratio == ratio)
        return;

    mPulleyJointDef.ratio = ratio;
    emit ratioChanged();
}

QPointF Box2DPulleyJoint::groundAnchorA() const
{
    return QPointF(mPulleyJointDef.groundAnchorA.x, -mPulleyJointDef.groundAnchorA.y);
}

void Box2DPulleyJoint::setGroundAnchorA(const QPointF &anchor)
{
    if (mPulleyJointDef.groundAnchorA == b2Vec2(anchor.x() / scaleRatio, -anchor.y() / scaleRatio))
        return;

    mPulleyJointDef.groundAnchorA = b2Vec2(anchor.x() / scaleRatio, -anchor.y() / scaleRatio);

    emit groundAnchorAChanged();
}

QPointF Box2DPulleyJoint::groundAnchorB() const
{
    return QPointF(mPulleyJointDef.groundAnchorB.x, -mPulleyJointDef.groundAnchorB.y);
}

void Box2DPulleyJoint::setGroundAnchorB(const QPointF &anchor)
{
    if (mPulleyJointDef.groundAnchorB == b2Vec2(anchor.x() / scaleRatio, -anchor.y() / scaleRatio))
        return;

    mPulleyJointDef.groundAnchorB = b2Vec2(anchor.x() / scaleRatio, -anchor.y() / scaleRatio);

    emit groundAnchorBChanged();
}

QPointF const Box2DPulleyJoint::reactionForce(float inv)
{
    const b2Vec2 rf = mPulleyJoint->GetReactionForce(inv);
    
    return QPointF(rf.x, rf.y);
}

float Box2DPulleyJoint::reactionTorque(float inv)
{
    return mPulleyJoint->GetReactionTorque(inv);
}

void Box2DPulleyJoint::createJoint()
{
    mPulleyJointDef.Initialize(bodyA()->body(), bodyB()->body(),
	mPulleyJointDef.groundAnchorA,mPulleyJointDef.groundAnchorB,
	bodyA()->body()->GetWorldCenter(), bodyB()->body()->GetWorldCenter(),
	mPulleyJointDef.ratio);
    mPulleyJointDef.collideConnected = collideConnected();

    mPulleyJoint = static_cast<b2PulleyJoint*>(world()->CreateJoint(&mPulleyJointDef));
    mInitializePending = false;
}

void Box2DPulleyJoint::nullifyJoint()
{
    mPulleyJoint = 0;
}

void Box2DPulleyJoint::cleanup(b2World *world)
{
    if (mPulleyJoint && bodyA() && bodyB()) {
        mPulleyJoint->SetUserData(0);
        world->DestroyJoint(mPulleyJoint);
        mPulleyJoint = 0;
    }
}
