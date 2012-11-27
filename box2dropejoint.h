#ifndef BOX2DROPEJOINT_H
#define BOX2DROPEJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2RopeJoint;
class b2RopeJointDef;

class Box2DRopeJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float maxLength READ getMaxLength WRITE setMaxLength NOTIFY maxLengthChanged )
    Q_PROPERTY(QPointF localAnchorA READ localAnchorA WRITE setLocalAnchorA NOTIFY localAnchorAChanged)
    Q_PROPERTY(QPointF localAnchorB READ localAnchorB WRITE setLocalAnchorB NOTIFY localAnchorBChanged)

public:
    explicit Box2DRopeJoint(QDeclarativeItem *parent = 0);

    QPointF localAnchorA() const;
    void setLocalAnchorA(const QPointF &anchor);

    QPointF localAnchorB() const;
    void setLocalAnchorB(const QPointF &anchor);

    void createJoint();
    void cleanup(b2World *world);
    void nullifyJoint();

    Q_INVOKABLE QPointF const reactionForce(float inv);
    Q_INVOKABLE float reactionTorque(float inv);

    void setMaxLength(float len);
    Q_INVOKABLE float getMaxLength();

signals:
    void maxLengthChanged();
    void localAnchorAChanged();
    void localAnchorBChanged();

public slots:

private:
    b2RopeJointDef mRopeJointDef;
    b2RopeJoint *mRopeJoint;
};

#endif // BOX2DROPEJOINT_H
