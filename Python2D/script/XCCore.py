import script.XCInit as XCInit
from script.Object.Player import Player

# demo stage 演示关卡
import script.TestStage as TestStage

# PySTG Init
# GameRANK show while winWidth / winHeight >= (16:10)
winWidth = 1280
winHeight = 720

winTitle = "Python2D v0.29x"
winScaleToMonitor = False
winResize = False
winFullScreen = False

# PySTG default function
def coreInitializer():
    StageInit()
    PlayerInit()


def coreFinalizer():
    print("[XCCore]Now interpreter stop.")


def StageInit():
    stageTest = TestStage.setupMyStage()
    XCInit.addStageItem(stageTest)
    print("[XCCore]Stage info init.")


def PlayerInit():
    rin = Player()
    rin.setPlayerImage("assets/Item/player.png", [8, 3], [0.06, 0.08, 1.0], 3, 2, 1)
    rin.setPlayerData(1.45, 0.1, 1.0)
    XCInit.addPlayerItem(rin)
    print("[XCCore]Player info init.")