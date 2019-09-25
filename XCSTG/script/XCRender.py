from queue import PriorityQueue
from queue import Queue
from script.RenderItem.TranslateItem import TranslateItem
from script.Object.XCItem import XCItem
from script.RenderItem.DynamicItem import DynamicItem
__staticRenderQueue = PriorityQueue()
__dynamicRenderList = Queue()

#static render queue function
def addStaticRenderItem(item):
    __staticRenderQueue.put(item)
def getStaticRenderItem():
    item = __staticRenderQueue.get()
    if isinstance(item, TranslateItem):
        return item.translate()
    else:
        print("[ERROR]Item isn't an standard RenderImageItem.")
        return tuple()
def getStaticRenderSize():
    return __staticRenderQueue.qsize()

#dynamic render list
def addDynamicRenderItem(item):
    __dynamicRenderList.put(item)

def initDynamicRenderItem():
    return __dynamicRenderList.get()
def initDynamicRenderItemSize():
    return __dynamicRenderList.qsize()

def dynamicTFunc():
    item = XCItem()
    addDynamicRenderItem(item)