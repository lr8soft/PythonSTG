from queue import PriorityQueue
from queue import Queue

__staticRenderQueue = PriorityQueue()
__stageInitList = Queue()
__playerList = Queue()


# static render queue function
def addStaticRenderItem(item):
    __staticRenderQueue.put(item)


def getStaticRenderItem():
    item = __staticRenderQueue.get()
    return item


def getStaticRenderSize():
    return __staticRenderQueue.qsize()


# game stage
def addStageItem(item):
    __stageInitList.put(item)


def getStageItem():
    item = __stageInitList.get()
    return item


def getStageItemSize():
    return __stageInitList.qsize()


# player item list
def addPlayerItem(item):
    __playerList.put(item)


def getPlayerItem():
    return __playerList.get()


def getPlayerItemSize():
    return __playerList.qsize()
