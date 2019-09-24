from queue import PriorityQueue
from queue import Queue
from script.RenderItem.TranslateItem import TranslateItem
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
    item = __dynamicRenderList.get()
    if isinstance(item, DynamicItem):
        return item.init()
    else:
        print("[ERROR]Item isn't an standard DynamicRenderItem.")
        return tuple()
def initDynamicRenderItemSize():
    return __dynamicRenderList.qsize()

