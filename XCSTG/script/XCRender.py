from queue import PriorityQueue
from script.Object.RenderItem import RenderItem
__renderQueue = PriorityQueue()

#Render queue function
def addRenderItem(item):
    __renderQueue.put(item)
def getRenderItem():
    item = __renderQueue.get()
    if isinstance(item, RenderItem):
        return item.translate()
    else:
        print("Item isn't an standard RenderItem.")
        return tuple()
def getRenderSize():
    return __renderQueue.qsize()

def abc():
    item = RenderItem()
    item.ImagePath = "assets/123.png"
    addRenderItem(item)

if __name__ == "__main__":
    abc()