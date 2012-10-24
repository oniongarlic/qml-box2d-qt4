/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the Box2D QML plugin.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library;  If not, see <http://www.gnu.org/licenses/>.
 */

#include "box2dwheeljoint.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DWheelJoint::Box2DWheelJoint(QDeclarativeItem *parent) :
    Box2DJoint(parent),
    mWheelJointDef(),
    mWheelJoint(0),
    mOverrideLocalAnchorA(false)
{
}

Box2DWheelJoint::~Box2DWheelJoint()
{
    cleanup(world());
}

float Box2DWheelJoint::frequencyHz() const
{
    return mWheelJointDef.frequencyHz;
}

void Box2DWheelJoint::setFrequencyHz(float frequency)
{
    if (mWheelJointDef.frequencyHz == frequency)
        return;

    mWheelJointDef.frequencyHz = frequency;
    if (mWheelJoint)
        mWheelJoint->SetSpringFrequencyHz(frequency);
    emit frequencyHzChanged();
}

float Box2DWheelJoint::dampingRatio() const
{
    return mWheelJointDef.dampingRatio;
}

void Box2DWheelJoint::setDampingRatio(float damping)
{
    if (mWheelJointDef.dampingRatio == damping)
        return;

    mWheelJointDef.dampingRatio = damping;
    if (mWheelJoint)
        mWheelJoint->SetSpringDampingRatio(damping);
    emit dampingRatioChanged();
}

float Box2DWheelJoint::maxMotorTorque() const
{
    return mWheelJointDef.maxMotorTorque;
}

void Box2DWheelJoint::setMaxMotorTorque(float maxMotorTorque)
{
    if (mWheelJointDef.maxMotorTorque == maxMotorTorque)
        return;

    mWheelJointDef.maxMotorTorque = maxMotorTorque;
    if (mWheelJoint)
        mWheelJoint->SetMaxMotorTorque(maxMotorTorque);
    emit maxMotorTorqueChanged();
}

float Box2DWheelJoint::motorSpeed() const
{
    return mWheelJointDef.motorSpeed;
}

void Box2DWheelJoint::setMotorSpeed(float motorSpeed)
{
    if (mWheelJointDef.motorSpeed == motorSpeed)
        return;

    mWheelJointDef.motorSpeed = motorSpeed;
    if (mWheelJoint)
        mWheelJoint->SetMotorSpeed(motorSpeed);
    emit motorSpeedChanged();
}

bool Box2DWheelJoint::enableMotor() const
{
    return mWheelJointDef.enableMotor;
}

void Box2DWheelJoint::setEnableMotor(bool enableMotor)
{
    if (mWheelJointDef.enableMotor == enableMotor)
        return;

    mWheelJointDef.enableMotor = enableMotor;
    if (mWheelJoint)
        mWheelJoint->EnableMotor(enableMotor);
    emit enableMotorChanged();
}

QPointF Box2DWheelJoint::localAnchorA() const
{
    if (mOverrideLocalAnchorA)
        return mLocalAnchorA;
    else
        return QPointF(mWheelJointDef.localAnchorA.x * scaleRatio, -mWheelJointDef.localAnchorA.y * scaleRatio);
}

void Box2DWheelJoint::setLocalAnchorA(const QPointF &localAnchorA)
{
    if (mOverrideLocalAnchorA && mLocalAnchorA == localAnchorA)
        return;

    mOverrideLocalAnchorA = true;
    mLocalAnchorA = localAnchorA;

    emit localAnchorAChanged();
}

void Box2DWheelJoint::nullifyJoint()
{
    mWheelJoint = 0;
}

void Box2DWheelJoint::createJoint()
{
    b2Vec2 anchor = mOverrideLocalAnchorA ?
		b2Vec2(mLocalAnchorA.x() / scaleRatio, -mLocalAnchorA.y() / scaleRatio) + bodyA()->body()->GetPosition() 
		: bodyB()->body()->GetWorldCenter();
    b2Vec2 axis(0.0f, 1.0f);

    mWheelJointDef.Initialize(bodyA()->body(), bodyB()->body(), anchor, axis);
    mWheelJointDef.collideConnected = collideConnected();

    mWheelJoint = static_cast<b2WheelJoint*>(world()->CreateJoint(&mWheelJointDef));
    mWheelJoint->SetUserData(this);
    mInitializePending = false;
}

void Box2DWheelJoint::release()
{
    if (!mReleased)
        mReleased = true;
    cleanup(world());
}

void Box2DWheelJoint::grab()
{
    if (mReleased)
        mReleased = false;
    createJoint();
}

void Box2DWheelJoint::cleanup(b2World *world)
{
    if (mWheelJoint && bodyA() && bodyB()) {
        mWheelJoint->SetUserData(0);
        world->DestroyJoint(mWheelJoint);
        mWheelJoint = 0;
    }
}
