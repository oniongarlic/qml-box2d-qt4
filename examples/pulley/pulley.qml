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
        switch (event.key) {
        case Qt.Key_Left:
            movableBox.moveBackward();
        break;
        case Qt.Key_Right:
            movableBox.moveForward();
        break;
        case Qt.Key_Up:
            movableBox.jump();
        break;
        case Qt.Key_F:
            world.reportFps!=world.reportFps;
            console.debug("ReportFps: "+world.reportFps)
        break;
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
	anchors.left: parent.left;
	y: 120
	text: "--"
    }
    Text {
	id: lenb;
	anchors.right: parent.right
	y: 120
	text: "--"
    }
    Text {
	id: fps
        visible: world.reportFps
	anchors.left: parent.left
	anchors.bottom: parent.bottom
	text: "FPS:"+world.fps
    }


    Timer {
	repeat: true;
	interval: 100
	running: true
	onTriggered: {
		lena.text=pj.getLengthA();
		lenb.text=pj.getLengthB();
	}
    }

    World {
        id: world;
        anchors.fill: parent
        reportFps: true;

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
		x: 100
		y: 20;
	}

	Pulley {
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

        MovableBox {
            id: movableBox
            width: 40
            height: width
        }

	FrictionJoint {
		bodyA: wb1;
		bodyB: ground;
		maxForce: 10
		maxTorque: 10
		collideConnected: true
	}

	FrictionJoint {
		bodyA: wb2;
		bodyB: ground;
		maxForce: 10
		maxTorque: 10
		collideConnected: true
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
