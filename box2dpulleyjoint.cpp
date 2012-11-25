#include "box2dweldjoint.h"
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
    if (mPulleyJoint)
        mPulleyJoint->SetRatio(ratio);
    emit ratioChanged();
}

void Box2DPulleyJoint::createJoint()
{
    mPulleyJointDef.Initialize(bodyA()->body(), bodyB()->body(), bodyA()->body()->GetWorldCenter(), bodyB()->body()->GetWorldCenter());
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
