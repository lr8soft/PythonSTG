from abc import abstractmethod
from script.RenderItem.DynamicItem import DynamicItem
from multiprocessing import Lock
from enum import  Enum
import uuid
class BlendType(Enum):
    COLOR_NONE = 0
    COLOR_ONE_MINUS_SRC = 1
    COLOR_ONE = 2
    ALPHA_NONE = 3
    ALPHA_ONE_MINUS_SRC = 4
    ALPHA_ONE = 5
class XCItem(DynamicItem):
    def __init__(self):
        self._pos = [0.0, 0.0, 0.0]
        self._uuid = str(uuid.uuid1())
        self._imagePath = "assets/Item/fairy.png"
        self._divideInfo = [1, 1, 0, 0]
        self._scaleSize = [1.0, 1.0, 1.0]
        self._isFlexible = False
        self._rotateAngle = 0.0
        self._rotateWork = [ 1, 0, 0]
        self._divideInfo = [1, 1, 0, 0]
        self._useBlend = True
        self._blendFunc = [BlendType.COLOR_NONE.value, BlendType.ALPHA_ONE_MINUS_SRC.value]
        self._lock = Lock()

    def setImage(self, imagePath, divideFormat = [1, 1, 0, 0], scaleSize = [1.0, 1.0, 1.0], isFlexible = False):
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

    def getPos(self):
        self._lock.acquire()
        t = tuple(self._pos)
        self._lock.release()
        return t

    def setPos(self, x, y, z):
        self._lock.acquire()
        self._pos[0] = x
        self._pos[1] = y
        self._pos[2] = z
        self._lock.release()

    def collide(self):
        pass
    #callback function for cpp
    def _cpp_getInitRenderInfo(self):
        return (self._imagePath, tuple(self._divideInfo), self._isFlexible)

    def _cpp_getImageDivideFormat(self):
        return tuple(self._divideInfo);

    def _cpp_getScaleSize(self):
        return tuple(self._scaleSize)

    def _cpp_getRotateInfo(self):
        return (self._rotateAngle, tuple(self._rotateWork))

    def _cpp_getBlendInfo(self):
        return (self._useBlend, tuple(self._blendFunc))

    def _cpp_doRenderWork(self):
        pass

    def _cpp_getUUID(self):
        return self._uuid





