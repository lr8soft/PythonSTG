from script.Bullet.Bullet import BulletColor
from script.Bullet.CircleBullet import CircleBullet
from script.Stage.Task import Task
from script.Stage.TaskUnit import TaskUnit
from script.Stage.XCStage import XCStage, StageBackGround, StageRank


def getStage():
    # First step: create a new stage
    stage = XCStage("My First Stage")
    stage.setBackGroundMusic("assets/Media/stage1.wav")
    stage.setBackGround(background=StageBackGround.river)
    stage.setStageRank(StageRank.Lunatic)

    # create new Task and attach unit on it
    testTask = Task(durationFrame=-1, intervalFrame=0)
    testUnit = TaskUnit(waitFrame=300, repeatTime=3)

    # add bullet to target unit
    bullet = CircleBullet()
    bullet.setBulletColor(BulletColor.BLUE)
    bullet.setRebound(1)
    bullet.setInitCoord([0.0, 1.0, 0.0])
    bullet.setAngle(270.0)
    bullet.setVelocity(0.6)

    testUnit.addBullet(bullet)
    testTask.addUnit(testUnit)

    stage.addTask(testTask)
    return stage


