from queue import PriorityQueue
from queue import Queue
from script.Object.XCItem import XCItem
from script.Bullet.Bullet import Bullet
import uuid
class XCStage:
    def __init__(self, stageName = "Stage 0 No name"):
        self.__stageName = stageName
        self.__stageItem = PriorityQueue()
        self.__stageBullet = Queue()
        self.__uuid = str(uuid.uuid1())

    def addItem(self, item):
        if isinstance(item, XCItem):
            self.__stageItem.put(item)
        else:
            raise Exception("Insert invalid item.")

    def addBullet(self, bullet):
        if isinstance(bullet, Bullet):
            self.__stageBullet.put(bullet)
        else:
            raise Exception("Insert invalid bullet.")

    def _cpp_getStageName(self):
        return self.__stageName

    def _cpp_getItemSize(self):
        return self.__stageItem.qsize()

    def _cpp_getItem(self):
        return self.__stageItem.get()

    def _cpp_getBulletSize(self):
        return self.__stageBullet.qsize()

    def _cpp_getBullet(self):
        return self.__stageBullet.get()

    def _cpp_getUuid(self):
        return self.__uuid

