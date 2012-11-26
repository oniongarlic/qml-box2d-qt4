#ifndef BOX2DPULLEYJOINT_H
#define BOX2DPULLEYJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2PulleyJoint;
class b2PulleyJointDef;

class Box2DPulleyJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float ratio READ ratio WRITE setRatio NOTIFY ratioChanged)
    Q_PROPERTY(float lengthA READ getLengthA)
    Q_PROPERTY(float lengthB READ getLengthB)
    Q_PROPERTY(QPointF groundAnchorA READ groundAnchorA WRITE setGroundAnchorA NOTIFY groundAnchorAChanged)
    Q_PROPERTY(QPointF groundAnchorB READ groundAnchorB WRITE setGroundAnchorB NOTIFY groundAnchorBChanged)

public:
    explicit Box2DPulleyJoint(QDeclarativeItem *parent = 0);

    float ratio() const;
    void setRatio(float ratio);

    QPointF groundAnchorA() const;
    void setGroundAnchorA(const QPointF &anchor);

    QPointF groundAnchorB() const;
    void setGroundAnchorB(const QPointF &anchor);

    void createJoint();
    void cleanup(b2World *world);
    void nullifyJoint();

    Q_INVOKABLE QPointF const reactionForce(float inv);
    Q_INVOKABLE float reactionTorque(float inv);

    Q_INVOKABLE float getLengthA();
    Q_INVOKABLE float getLengthB();

signals:
    void ratioChanged();
    void groundAnchorAChanged();
    void groundAnchorBChanged();

public slots:

private:
    b2PulleyJointDef mPulleyJointDef;
    b2PulleyJoint *mPulleyJoint;
};

#endif // BOX2DPULLEYJOINT_H
