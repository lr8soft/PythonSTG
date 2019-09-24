from abc import abstractmethod
from script.RenderItem.DynamicItem import DynamicItem
import uuid
class XCItem(DynamicItem):
    def __init__(self):
        self.__isInit = False
        self.__pos = [0.0, 0.0, 0.0]
        self.__uuid = uuid.uuid1()

    def getInit(self):
        return self.__isInit;
    def setInit(self, value):
        self.__isInit = value
    isInit = property(getInit, setInit)

    def getPos(self):
        return self.__pos
    def setPos(self, x, y, z):
        self.__pos[0] = x
        self.__pos[1] = y
        self.__pos[2] = z
    pos = property(getPos, setPos)

    def getUUID(self):
        return self.__uuid

    @abstractmethod
    def collide(self):
        pass

    @abstractmethod
    def render(self):
        pass

    @abstractmethod
    def init(self):
        pass



