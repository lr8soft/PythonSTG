from queue import Queue
from enum import Enum


class DropItem(Enum):
    Point = 0
    Power = 1
    FullPower = 2
    Life = 3
    Bomb = 4


class DropItemHelper:
    def __init__(self):
        self.itemType = Queue()
        self.itemCount = Queue()

    def addItemDrop(self, item = DropItem.Point, count = 5):
        self.itemType.put(item.value)
        self.itemCount.put(count)

    def _cpp_getDropItemSize(self):
        return self.itemCount.qsize()

    def _cpp_getDropItem(self):
        return self.itemType.get(), self.itemCount.get()
