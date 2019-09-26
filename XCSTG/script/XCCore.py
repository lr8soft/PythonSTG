import script.XCRender as XCRender
from script.RenderItem.RenderImageItem import RenderImageItem
from script.RenderItem.RenderColorItem import RenderColorItem
from script.Object.XCItem import XCItem
#PySTG Init
winHeight = 720
winWidth = 1280
winTitle = "PyTest v0.5"

#PySTG default function
def coreInitializer():
    UiInit()
    TestInit()
    print("[XCCore]Now basic ui init.")
    return True

def coreKeyCallback(key, scancode, action, mods):
    print("Now key:", key, " Now action:", action)

def coreFinalizer():
    print("[XCCore]Now End.")


#UI Init
def UiInit():
    background = RenderImageItem()
    background.IsFlexible = False
    background.ImagePath = "assets/background/123.jpeg"
    background.renderPos = [0.0,0.0,0.0]
    background.priority = 6
    XCRender.addStaticRenderItem(background)

    gameScene = RenderColorItem()
    gameScene.renderPos = [0.0,0.0,0.0]
    gameScene.renderSize = [0.5,0.95,1.0]
    gameScene.colorValue = [1.0,1.0,1.0,1.0]
    background.priority = 7
    XCRender.addStaticRenderItem(gameScene)


def TestInit():
    item  = XCItem()
    item.setImage("assets/Item/fairy.png",[1,1,0,0],[0.065,0.1,1.0],False)
    XCRender.addInitDynamicRenderItem(item)
