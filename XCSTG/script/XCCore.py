import script.XCRender as XCRender
#PySTG Init
winHeight = 720
winWidth = 1280
winTitle = "PyTest v0.4"
__collisionItem = []
#PySTG default function
def coreInitializer():
    UiInit()
    print("[XCCore]Now basic ui init.")
    return True
def coreFinalizer():
    print("[XCCore]Now End.")


#UI Init
def UiInit():
    background = XCRender.RenderImageItem()
    background.IsFlexible = False
    background.ImagePath = "assets/background/222.jpeg"
    background.renderPos = [0.0,0.0,0.0]
    background.priority = 3
    XCRender.addStaticRenderItem(background)

    gameScene = XCRender.RenderColorItem()
    gameScene.renderPos = [0.0,0.0,0.0]
    gameScene.renderSize = [0.6,0.8,1.0]
    gameScene.colorValue = [0.0,0.0,0.0,1.0]
    background.priority = 1
    XCRender.addStaticRenderItem(gameScene)