from queue import PriorityQueue
from queue import Queue
from script.RenderItem.TranslateItem import TranslateItem
from script.Object.XCItem import XCItem
from script.RenderItem.DynamicItem import DynamicItem
__staticRenderQueue = PriorityQueue()
__dynamicInitList = Queue()

#static render queue function
def addStaticRenderItem(item):
    __staticRenderQueue.put(item)
def getStaticRenderItem():
    item = __staticRenderQueue.get()
    return item

def getStaticRenderSize():
    return __staticRenderQueue.qsize()

#dynamic render init list
def addInitDynamicRenderItem(item):
    __dynamicInitList.put(item)

def getInitDynamicRenderItem():
    item =__dynamicInitList.get()
    return item

def getInitDynamicRenderItemSize():
    return __dynamicInitList.qsize()
