from queue import PriorityQueue
from script.Object.RenderItem import RenderItem
#PySTG Init
winHeight = 720
winWidth = 1280
winTitle = "PySTG Test v0.1"

renderQueue = PriorityQueue()


#PySTG default function
def coreInitializer():
    print("Now Init.")
    return True
def coreFinalizer():
    print("Now End.")
def getRenderItem():
    __doc__ = "Return a tuple include size and items."
    info = []
    while not renderQueue.empty():
        info.append(renderQueue.get().translate())
    return tuple(info)
def getRenderItemCount():
    return renderQueue.qsize()
