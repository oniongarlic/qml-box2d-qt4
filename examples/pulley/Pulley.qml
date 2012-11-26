import QtQuick 1.1
import Box2D 1.0

Body {
	property real size: 50
	width: size;
	height: size;
	sleepingAllowed: true
	bodyType: Body.Static

    fixtures: Circle {
	id: c
        anchors.fill: parent
        density: 1.0;
        friction: 1.0;
        restitution: 0.3;
	radius: size/2;
    }

    Rectangle {
//	anchors.centerIn: c
        color: "blue"
	radius: size/2
        width: parent.width
        height: parent.height
        x: c.x - c.radius
        y: c.y - c.radius
    }
}
