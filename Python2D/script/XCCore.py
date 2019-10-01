import script.XCInit as XCInit
from script.RenderItem.RenderImageItem import RenderImageItem
from script.RenderItem.RenderColorItem import RenderColorItem
from script.Object.XCItem import XCItem
from script.Stage.XCStage import XCStage
from script.Object.Player import Player
from script.Bullet.CircleBullet import CircleBullet
from script.Bullet.Bullet import BulletColor
# PySTG Init
winHeight = 720
winWidth = 1280
winTitle = "Python2D v0.16"
winScaleToMonitor = True

# PySTG default function
def coreInitializer():
    UiInit()
    StageInit()
    PlayerInit()
    print("[XCCore]Now basic system init.")


def coreFinalizer():
    print("[XCCore]Now interpreter stop.")


# UI Init
def UiInit():
    background = RenderImageItem()
    background.IsFlexible = False
    background.ImagePath = "assets/background/123.jpeg"
    background.renderPos = [0.0, 0.0, 0.0]
    background.priority = 6
    XCInit.addStaticRenderItem(background)

    gameScene = RenderColorItem()
    gameScene.renderPos = [0.0, 0.0, 0.0]
    gameScene.renderSize = [1.0, 1.0, 1.0]
    gameScene.colorValue = [0.0, 0.0, 0.0, 1.0]
    gameScene.isFlexible = True
    background.priority = 7
    XCInit.addStaticRenderItem(gameScene)


def StageInit():
    stage0 = XCStage("Stage TEST")
    itemTest = XCItem()
    itemTest.setImage("assets/Item/point.png", [1, 1, 0, 0], [0.04, 0.04, 0.04])
    itemTest.setBlend()
    itemTest.setInitPos([0.0, 0.0, 0.0])
    for i in range(0,10):
        stage0.addItem(itemTest)

    for j in range(0, 1800):
        bullet = CircleBullet([0.0,0.0,0.0])
        bullet.setAngle(j, j / 1800)
        bullet.setBulletColor(BulletColor.LIGHTBLUE)
        bullet.setRebound(5)
        stage0.addBullet(bullet)

    XCInit.addStageItem(stage0)


def PlayerInit():
    rin = Player()
    rin.setPlayerImage("assets/Item/player.png", [8, 3], [0.06, 0.08, 1.0], 3, 2, 1)
    rin.setPlayerData(1.45, 0.1, 1.0)
    XCInit.addPlayerItem(rin)
