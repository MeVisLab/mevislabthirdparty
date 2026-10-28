import numpy
from Inventor import actions, base, nodes

if not base.SoDB.isInitialized():
    base.SoDB.init()

cube = nodes.SoCube()
cube.width.setValue(2.5)
translation = nodes.SoTranslation()
translation.translation.setValue(1, 2, 3)
scene = nodes.SoSeparator()
scene.addChild(translation)
scene.addChild(cube)
assert scene.getNumChildren() == 2
assert cube.width.getValue() == 2.5
assert isinstance(scene.getChild(1), nodes.SoCube)

bounding_box_action = actions.SoGetBoundingBoxAction(base.SbViewportRegion(100, 100))
bounding_box_action.apply(scene)
bounding_box = bounding_box_action.getBoundingBox()
assert bounding_box.getMin().getValue() == (-0.25, 1.0, 2.0)
assert bounding_box.getMax().getValue() == (2.25, 3.0, 4.0)

search_action = actions.SoSearchAction()
search_action.setType(nodes.SoCube.getClassTypeId())
search_action.apply(scene)
assert search_action.getPath().getLength() == 2

coordinates = nodes.SoCoordinate3()
points = numpy.array([[0, 0, 0], [1, 0, 0], [1, 1, 0]], dtype=numpy.float32)
coordinates.point.setValues(0, points)
assert coordinates.point.getNum() == 3
assert numpy.array_equal(coordinates.point.getValues(), points)
