import script.XCInit as XCInit
from script.RenderItem.RenderImageItem import RenderImageItem
from script.RenderItem.RenderColorItem import RenderColorItem
from script.Object.XCItem import XCItem
from script.Stage.XCStage import XCStage
from script.Object.Player import Player

from script.Stage.Task import Task, TaskUnit
from script.Bullet.CircleBullet import CircleBullet
from script.Bullet.Bullet import BulletColor

# PySTG Init
winHeight = 720
winWidth = 1280
winTitle = "Python2D v0.18"
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
    #task 0
    taskTest = Task(durationFrame=-1,intervalFrame=0)
    #bullet group 0
    unit0 = TaskUnit(waitFrame=240)
    for j in range(0, 36):
        bullet = CircleBullet([0.0,0.0,0.0],0.006)
        bullet.setAngle(j*10, 0.001)
        unit0.addBullet(bullet)
    taskTest.addUnit(unit0)
    #bullet group 1
    unit1 = TaskUnit(waitFrame=300)
    for i in range(0,36):
        if i % 2==0:
            bullet = CircleBullet([0.5, 0.5, 0.0], 0.01)
            bullet.setBulletColor(BulletColor.ORANGE)
            bullet.setAngle(i*10)
            unit1.addBullet(bullet)
        else:
            bullet = CircleBullet([-0.5, -0.5, 0.0], 0.01)
            bullet.setBulletColor(BulletColor.PURPLE)
            bullet.setAngle(i*10)
            unit1.addBullet(bullet)
    taskTest.addUnit(unit1)
    stage0.addTask(taskTest)

    #task 2
    taskAfter = Task(durationFrame=-1, intervalFrame=0,targetUuid=taskTest.getUuid())
    unit2_0 = TaskUnit()
    for j in range(0, 360):
        bullet = CircleBullet([0.0, 0.0, 0.0], 0.006)
        bullet.setAngle(j)
        bullet.setBulletColor(BulletColor.LIGHTBLUE)
        bullet.setRebound(1)
        unit2_0.addBullet(bullet)
    taskAfter.addUnit(unit2_0)
    stage0.addTask(taskAfter)
    XCInit.addStageItem(stage0)
    print("[XCCore]Stage info init.")


def PlayerInit():
    rin = Player()
    rin.setPlayerImage("assets/Item/player.png", [8, 3], [0.06, 0.08, 1.0], 3, 2, 1)
    rin.setPlayerData(1.45, 0.1, 1.0)
    XCInit.addPlayerItem(rin)
    print("[XCCore]Player info init.")
