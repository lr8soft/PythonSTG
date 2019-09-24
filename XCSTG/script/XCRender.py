from queue import PriorityQueue
from script.Object.RenderImageItem import RenderImageItem
from script.Object.RenderColorItem import RenderColorItem
from script.Object.TranslateItem import TranslateItem
__staticRenderQueue = PriorityQueue()

#Render queue function
def addStaticRenderItem(item):
    __staticRenderQueue.put(item)
def getStaticRenderItem():
    item = __staticRenderQueue.get()
    if isinstance(item, TranslateItem):
        return item.translate()
    else:
        print("Item isn't an standard RenderImageItem.")
        return tuple()
def getStaticRenderSize():
    return __staticRenderQueue.qsize()
