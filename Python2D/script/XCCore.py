import script.XCInit as XCInit
from script.RenderItem.RenderImageItem import RenderImageItem
from script.RenderItem.RenderColorItem import RenderColorItem
from script.Object.XCItem import XCItem
from script.Stage.XCStage import XCStage
from script.Object.Player import Player
from script.Bullet.CircleBullet import CircleBullet
from script.Bullet.Bullet import BulletColor

# PySTG Init
winHeight = 800
winWidth = 1440
winTitle = "Python2D v0.16"
winScaleToMonitor = True


# PySTG default function
def coreInitializer():
    UiInit()
    StageInit()
    PlayerInit()


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
    print("[XCCore]UI init.")


def StageInit():
    stage0 = XCStage("Stage TEST")
    XCInit.addStageItem(stage0)
    print("[XCCore]Stage info init.")


def PlayerInit():
    rin = Player()
    rin.setPlayerImage("assets/Item/player.png", [8, 3], [0.06, 0.08, 1.0], 3, 2, 1)
    rin.setPlayerData(1.45, 0.1, 1.0)
    XCInit.addPlayerItem(rin)
    print("[XCCore]Player info init.")
