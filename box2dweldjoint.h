#ifndef BOX2DWELDJOINT_H
#define BOX2DWELDJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2WeldJoint;
class b2WeldJointDef;

class Box2DWeldJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float frequencyHz READ frequencyHz WRITE setFrequencyHz NOTIFY frequencyHzChanged)
    Q_PROPERTY(float dampingRatio READ dampingRatio WRITE setDampingRatio NOTIFY dampingRatioChanged)

public:
    explicit Box2DWeldJoint(QDeclarativeItem *parent = 0);

    float frequencyHz() const;
    void setFrequencyHz(float frequency);

    float dampingRatio() const;
    void setDampingRatio(float damping);

    void createJoint();
    void cleanup(b2World *world);
    void nullifyJoint();

    Q_INVOKABLE QPointF const reactionForce(float inv);
    Q_INVOKABLE float reactionTorque(float inv);

signals:
    void frequencyHzChanged();
    void dampingRatioChanged();

public slots:

private:
    b2WeldJointDef mWeldJointDef;
    b2WeldJoint *mWeldJoint;
};

#endif // BOX2DWELDJOINT_H
