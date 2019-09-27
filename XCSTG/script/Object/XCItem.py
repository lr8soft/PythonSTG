from enum import  Enum
import uuid
from script.RenderItem.TranslateItem import TranslateItem
class BlendType(Enum):
    COLOR_NONE = 0
    COLOR_ONE_MINUS_SRC = 1
    COLOR_ONE = 2
    ALPHA_NONE = 0
    ALPHA_ONE_MINUS_SRC = 1
    ALPHA_ONE = 2
class XCItem(TranslateItem):
    def __init__(self):
        super().__init__()
        self._pos = [0.0, 0.0, 0.0]
        self._uuid = str(uuid.uuid1())
        self._imagePath = "assets/Item/fairy.png"
        self._divideInfo = [1, 1, 0, 0]
        self._scaleSize = [1.0, 1.0, 1.0]
        self._isFlexible = True
        self._rotateAngle = 0.0
        self._rotateWork = [ 1, 0, 0]
        self._divideInfo = [1, 1, 0, 0]
        self._useBlend = True
        self._blendFunc = [BlendType.COLOR_NONE.value, BlendType.ALPHA_ONE_MINUS_SRC.value]

    def setImage(self, imagePath, divideFormat = [1, 1, 0, 0], scaleSize = [1.0, 1.0, 1.0], isFlexible = True):
        self._imagePath = imagePath
        self._divideInfo = divideFormat
        self._isFlexible = isFlexible
        self._scaleSize = scaleSize

    def setBlend(self, useBlend=True, colorFunc = BlendType.COLOR_NONE.value, alphaFunc = BlendType.ALPHA_ONE_MINUS_SRC.value):
        self._useBlend = useBlend
        self._blendFunc = [colorFunc, alphaFunc]

    def setAngle(self, angle = 0.0, angleWork = [1, 0, 0]):
        self._rotateAngle = angle
        self._rotateWork = angleWork

    def setInitPos(self, pos = [0.0, 0.0, 0.0]):
        self._pos = pos

    #callback function for cpp
    def _cpp_getInitRenderInfo(self):
        return (self._imagePath, tuple(self._divideInfo), self._isFlexible)

    def _cpp_getScaleSize(self):
        return tuple(self._scaleSize)

    def _cpp_getRotateInfo(self):
        return (self._rotateAngle, tuple(self._rotateWork))

    def _cpp_getBlendInfo(self):
        return (self._useBlend, tuple(self._blendFunc))

    def _cpp_getUUID(self):
        return self._uuid

    def _cpp_getInitCoord(self):
        return tuple(self._pos)





