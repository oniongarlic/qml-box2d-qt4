import QtQuick 1.1
import Box2D 1.0

Rectangle {
    id: screen
    width: 400
    height: 600
    focus: true
    color: "white";
    Keys.onPressed: onKeysPressed(event)
    Keys.onReleased: onKeysReleased(event)

    function onKeysPressed(event) {
        if (event.key == Qt.Key_Left) {
            movableBox.moveBackward();
        }
        else if (event.key == Qt.Key_Right) {
            movableBox.moveForward();
        }
        else if (event.key == Qt.Key_Up) {
            movableBox.jump();
        }
    }

    function onKeysReleased(event) {
        if (event.isAutoRepeat)
            return ;

        if (event.key == Qt.Key_Left || event.key == Qt.Key_Right) {
            movableBox.stopMoving();
        }
    }

    Text {
	id: lena;
	x: 10
	y: 32
	text: "--"
    }
    Text {
	id: lenb;
	x: 10
	y: 64
	text: "--"
    }

    Timer {
	repeat: true;
	interval: 250
	running: true
	onTriggered: {
		lena.text=pj.getLengthA();
		lenb.text=pj.getLengthB();
	}
    }

    World {
        id: world;
        anchors.fill: parent

	WoodenBox {
		id: wb1
            x: 100
            y: 180
        }

	WoodenBox {
		id: wb2
            x: 300
            y: 180
        }

	Pulley {
		id: pp1;
		x: 100
		y: 20;
	}

	Pulley {
		id: pp2;
		x: 300
		y: 20;
	}

	PulleyJoint {
		id: pj
		bodyA: wb1
		bodyB: wb2
		ratio: 1.0;
		groundAnchorA: Qt.point(100, 20)
		groundAnchorB: Qt.point(300, 20)
		collideConnected: true
	}

	RopeJoint {
		bodyA: pp1
		bodyB: wb1
		maxLength: 250
	}

	RopeJoint {
		bodyA: pp2
		bodyB: wb2
		maxLength: 250
	}

        MovableBox {
            id: movableBox
            width: 40
            height: width
        }

        Wall {
            id: ground
            height: 20
            anchors { left: parent.left; right: parent.right; top: parent.bottom }
        }
        Wall {
            id: ceiling
            height: 20
            anchors { left: parent.left; right: parent.right; bottom: parent.top }
        }
        Wall {
            id: leftWall
            width: 20
            anchors { right: parent.left; bottom: ground.top; top: ceiling.bottom }
        }
        Wall {
            id: rightWall
            width: 20
            anchors { left: parent.right; bottom: ground.top; top: ceiling.bottom }
        }
        DebugDraw {
		world: world
	        opacity: 0.75
		visible: false;
        }
    }
}
