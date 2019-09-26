import script.XCRender as XCRender
from script.RenderItem.RenderImageItem import RenderImageItem
from script.RenderItem.RenderColorItem import RenderColorItem
from script.Object.XCItem import XCItem
from script.Object.Player import Player
#PySTG Init
winHeight = 720
winWidth = 1280
winTitle = "PyTest v0.5"

player = Player()

#PySTG default function
def coreInitializer():
    UiInit()
    ItemInit()
    PlayerInit()
    print("[XCCore]Now basic ui init.")
    return True

def coreKeyCallback(key, scancode, action, mods):
    global player
    player.keyCheckCallBack(key, action)

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


def ItemInit():
    item  = XCItem()
    item.setImage("assets/Item/fairy.png",[1,1,0,0],[0.065,0.1,1.0],False)
    XCRender.addInitDynamicRenderItem(item)

def PlayerInit():
    global player
    player.setImage("assets/Item/player.png",[8,3,0,0],[0.055,0.1,0.1],True)
    XCRender.addInitDynamicRenderItem(player)
