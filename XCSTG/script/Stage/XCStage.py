from queue import PriorityQueue
from script.Object.XCItem import XCItem
class XCStage:
    def __init__(self, stageName = "Stage 0 No name"):
        self.__stageName = stageName
        self.__stageItem = PriorityQueue()

    def addItem(self, item):
        if isinstance(item, XCItem):
            self.__stageItem.put(item)
        else:
            raise Exception("Insert invalid item.")


    def _cpp_getStageName(self):
        return self.__stageName

    def _cpp_getItemSize(self):
        return self.__stageItem.qsize()

    def _cpp_getItem(self):
        return self.__stageItem.get()

