import QtQuick 1.1
import Box2D 1.0

Image {
    id: screen;
    width: 640;
    height: 480;

    source: "background.png"

    World {
        id: world;
        anchors.fill: parent

	WoodenBox {
		id: wb
               x: Math.random() * (screen.width - 100);
               y: Math.random() * (screen.height / 3);
               rotation: Math.random() * 90;
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
            id: debugDraw
            world: world
            anchors.fill: world
            opacity: 0.75
            visible: true
        }

	Component {
		id: mjc

		MouseJoint {

		}
	}

        MouseArea {
		property variant mj;
            anchors.fill: world
            onPressed: {
		mj=mjc.createObject(world, {"x": mouse.x, "y": mouse.y, "maxForce": 1000*wb.mass, "dampingRatio": 1.0, "bodyA": ground, "bodyB": wb })
		mj.setTarget(Qt.point(mouse.x, mouse.y));
		}
		onPositionChanged: {
		if (mj && pressed) {
			console.debug("STargetX: "+mouse.x);
			console.debug("STargetY: "+mouse.y);
			mj.setTarget(Qt.point(mouse.x, mouse.y));

			var st=mj.getTarget();
			console.debug("GTX: "+st.x);
			console.debug("GTY: "+st.y);
			}
		}
	    onReleased: {
		mj.destroy();
	    }
        }
    }
}
