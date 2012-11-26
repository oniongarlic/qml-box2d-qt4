import QtQuick 1.1
import Box2D 1.0

Body {
    sleepingAllowed: false
    bullet: true
    fixedRotation: true

    function moveForward() {
        linearVelocity.x = 300;
    }

    function moveBackward() {
        linearVelocity.x = -300;
    }

    function stopMoving() {
        linearVelocity.x = 0;
    }

    function jump() {
        var impulse = Qt.point(0, -2600);
        applyLinearImpulse(impulse, getWorldCenter());
    }

    fixtures: Box {
        anchors.fill: parent
        density: 6;
        friction: 0.3;
        restitution: 0.2;
        groupIndex: 1
    }

    Rectangle {
        anchors.fill: parent
        color: "red"
    }
}
