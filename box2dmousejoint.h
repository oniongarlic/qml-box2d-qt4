#ifndef BOX2DMOUSEJOINT_H
#define BOX2DMOUSEJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2MouseJoint;
class b2MouseJointDef;

class Box2DMouseJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float maxForce READ maxForce WRITE setMaxForce NOTIFY maxForceChanged)
    Q_PROPERTY(float frequencyHz READ frequencyHz WRITE setFrequencyHz NOTIFY frequencyHzChanged)
    Q_PROPERTY(float dampingRatio READ dampingRatio WRITE setDampingRatio NOTIFY dampingRatioChanged)

public:
    explicit Box2DMouseJoint(QDeclarativeItem *parent = 0);

    float maxForce() const;
    void setMaxForce(float force);

    float frequencyHz() const;
    void setFrequencyHz(float frequency);

    float dampingRatio() const;
    void setDampingRatio(float damping);

    void createJoint();
    void cleanup(b2World *world);
    void nullifyJoint();

    Q_INVOKABLE QPointF const reactionForce(float inv);
    Q_INVOKABLE float reactionTorque(float inv);
    Q_INVOKABLE void setTarget(const QPointF &targetxy);
    Q_INVOKABLE QPointF const getTarget();

signals:
    void maxForceChanged();
    void frequencyHzChanged();
    void dampingRatioChanged();

public slots:

private:
    b2MouseJointDef mMouseJointDef;
    b2MouseJoint *mMouseJoint;
    QPointF target;
    bool targetIsValid;
};

#endif // BOX2DFRICTIONJOINT_H
