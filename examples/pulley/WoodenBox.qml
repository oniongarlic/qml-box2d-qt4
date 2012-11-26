import QtQuick 1.1
import Box2D 1.0

Body {
    width: 100
    height: 100
    sleepingAllowed: false
    bodyType: Body.Dynamic

    fixtures: Box {
        anchors.fill: parent
        density: 1.0;
        friction: 1.0;
        restitution: 0.6;
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
    }
}
