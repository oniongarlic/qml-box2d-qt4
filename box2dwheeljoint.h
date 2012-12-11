/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2012 Kaj-Michael Lang
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

#ifndef BOX2DWHEELJOINT_H
#define BOX2DWHEELJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2WheelJoint;
class b2WheelJointDef;

class Box2DWheelJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float frequencyHz READ frequencyHz WRITE setFrequencyHz NOTIFY frequencyHzChanged)
    Q_PROPERTY(float dampingRatio READ dampingRatio WRITE setDampingRatio NOTIFY dampingRatioChanged)
    Q_PROPERTY(float maxMotorTorque READ maxMotorTorque WRITE setMaxMotorTorque NOTIFY maxMotorTorqueChanged)
    Q_PROPERTY(float motorSpeed READ motorSpeed WRITE setMotorSpeed NOTIFY motorSpeedChanged)
    Q_PROPERTY(bool enableMotor READ enableMotor WRITE setEnableMotor NOTIFY enableMotorChanged)
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)

public:
    explicit Box2DWheelJoint(QDeclarativeItem *parent = 0);
    ~Box2DWheelJoint();

    float frequencyHz() const;
    void setFrequencyHz(float frequency);

    float dampingRatio() const;
    void setDampingRatio(float damping);

    float maxMotorTorque() const;
    void setMaxMotorTorque(float maxMotorTorque);

    float motorSpeed() const;
    void setMotorSpeed(float motorSpeed);

    bool enableLimit() const;
    void setEnableLimit(bool enableLimit);

    bool enableMotor() const;
    void setEnableMotor(bool enableMotor);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &localAnchorA);

    void nullifyJoint();
    void createJoint();
    void cleanup(b2World *world);

    Q_INVOKABLE QPointF const reactionForce(float inv);
    Q_INVOKABLE float reactionTorque(float inv);

    Q_INVOKABLE float jointSpeed();

signals:
    void frequencyHzChanged();
    void dampingRatioChanged();
    void maxMotorTorqueChanged();
    void motorSpeedChanged();
    void enableMotorChanged();
    void localAnchorAChanged();

private:
    b2WheelJointDef mWheelJointDef;
    b2WheelJoint *mWheelJoint;
    bool mOverrideLocalAnchorA;
    QPointF mLocalAnchorA;
};

#endif
