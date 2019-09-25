from abc import abstractmethod
from script.RenderItem.DynamicItem import DynamicItem
import uuid
class XCItem(DynamicItem):
    def __init__(self):
        self.__isInit = False
        self.__pos = [0.0, 0.0, 0.0]
        self.__uuid = str(uuid.uuid1())

    def getInit(self):
        return self.__isInit;
    def setInit(self, value):
        self.__isInit = value

    def getPos(self):
        return tuple(self.__pos)
    def setPos(self, x, y, z):
        self.__pos[0] = x
        self.__pos[1] = y
        self.__pos[2] = z

    def getUUID(self):
        return self.__uuid

    def collide(self):
        pass

    def renderInit(self):
        pass




