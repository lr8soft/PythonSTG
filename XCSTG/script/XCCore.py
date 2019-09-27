import script.XCInit as XCInit
from script.RenderItem.RenderImageItem import RenderImageItem
from script.RenderItem.RenderColorItem import RenderColorItem
from script.Object.XCItem import XCItem
from script.Stage.XCStage import XCStage
#PySTG Init
winHeight = 720
winWidth = 1280
winTitle = "PyTest v0.5"
winResize = True
winScaleToMonitor = True

#PySTG default function
def coreInitializer():
    UiInit()
    print("[XCCore]Now basic ui init.")
    return True


def coreFinalizer():
    print("[XCCore]Now End.")

#UI Init
def UiInit():
    background = RenderImageItem()
    background.IsFlexible = False
    background.ImagePath = "assets/background/123.jpeg"
    background.renderPos = [0.0,0.0,0.0]
    background.priority = 6
    XCInit.addStaticRenderItem(background)

    gameScene = RenderColorItem()
    gameScene.renderPos = [0.0,0.0,0.0]
    gameScene.renderSize = [0.5,0.95,1.0]
    gameScene.colorValue = [1.0,1.0,1.0,1.0]
    background.priority = 7
    XCInit.addStaticRenderItem(gameScene)

def StageInit():
    stage0 = XCStage("Stage TEST")

    itemTest = XCItem()
    stage0.addItem(itemTest)
    XCInit.addStageItem(stage0)

