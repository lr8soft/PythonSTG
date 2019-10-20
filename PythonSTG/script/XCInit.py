from queue import Queue

__stageInitList = Queue()
__playerList = Queue()


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
