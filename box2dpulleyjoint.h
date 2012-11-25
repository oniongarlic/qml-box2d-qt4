#ifndef BOX2DWELDJOINT_H
#define BOX2DWELDJOINT_H

#include "box2djoint.h"
#include <Box2D.h>

class b2World;
class b2PulleyJoint;
class b2PulleyJointDef;

class Box2DPulleyJoint : public Box2DJoint
{
    Q_OBJECT

    Q_PROPERTY(float ratio READ ratio WRITE setRatio NOTIFY ratioChanged)

public:
    explicit Box2DPulleyJoint(QDeclarativeItem *parent = 0);

    float ratio() const;
    void setRatio(float ratio);

    void createJoint();
    void cleanup(b2World *world);
    void nullifyJoint();

signals:
    void frequencyHzChanged();
    void dampingRatioChanged();

public slots:

private:
    b2PulleyJointDef mPulleyJointDef;
    b2PulleyJoint *mPulleyJoint;
};

#endif // BOX2DPULLEYJOINT_H
