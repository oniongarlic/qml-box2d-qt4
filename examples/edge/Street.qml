import QtQuick 1.1
import Box2D 1.0

Body {
    id: edge
    bodyType: Body.Static

    fixtures: [
	Edge { vertices: [ Qt.point(0, 0), Qt.point(100, 0) ] },
	Edge { vertices: [ Qt.point(100, 0), Qt.point(200, 20) ] },
	Edge { vertices: [ Qt.point(200, 20), Qt.point(300, 40) ] },
	Edge { vertices: [ Qt.point(300, 40), Qt.point(330, 60) ] }
	]
    Component.onCompleted: {
                var i;

                console.debug("FC: "+fixtures);
                console.debug("FC: "+fixtures.length);

                for (i=0;i<fixtures.length;i++) {
                    var e=fixtures[i];
                    console.debug("E: "+e);
                    console.debug("EV: "+e.vertices);
                    console.debug("EV0: "+e.vertices[0]);
                    console.debug("EV1: "+e.vertices[1]);

                    console.debug("E0x: "+e.vertices[0].x);
                    console.debug("E0y: "+e.vertices[0].y);
                }
            }
}
