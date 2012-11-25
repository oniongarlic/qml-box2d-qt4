import Qt 4.7
import Box2D 1.0

Body {
    id: edge
    bodyType: Body.Static
    width: 200;
    height: 10;

    Rectangle { anchors.fill: parent; color: "red"; }

    fixtures: Edge { vertices: [Qt.point(0, 0), Qt.point(200, 50) ] }
}
