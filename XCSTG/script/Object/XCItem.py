from abc import abstractmethod
from script.RenderItem.DynamicItem import DynamicItem
import uuid
class XCItem(DynamicItem):
    def __init__(self):
        self.__pos = [0.0, 0.0, 0.0]
        self.__uuid = str(uuid.uuid1())
        self.__imagePath = "assets/Item/fairy.png"
        self.__divideInfo = [1, 1, 0, 0]
        self.__scaleSize = [1.0, 1.0, 1.0]
        self.__isFlexible = False

    def setImage(self, imagePath, divideFormat = [1, 1, 0, 0], scaleSize = [1.0, 1.0, 1.0], isFlexible = False):
        self.__imagePath = imagePath
        self.__divideInfo = divideFormat
        self.__isFlexible = isFlexible
        self.__scaleSize = scaleSize

    def getPos(self):
        return tuple(self.__pos)

    def setPos(self, x, y, z):
        self.__pos[0] = x
        self.__pos[1] = y
        self.__pos[2] = z

    def collide(self):
        pass
    #callback function for cpp
    def _cpp_getInitRenderInfo(self):
        return (self.__imagePath, tuple(self.__divideInfo), self.__isFlexible)

    def _cpp_getImageDivideFormat(self):
        return tuple(self.__divideInfo);

    def _cpp_getScaleSize(self):
        return tuple(self.__scaleSize)

    def _cpp_doRenderWork(self):
        pass

    def _cpp_getUUID(self):
        return self.__uuid





