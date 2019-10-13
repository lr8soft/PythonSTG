from script.Stage.TaskUnit import TaskUnit
from enum import Enum


class EnemyColor(Enum):
    Yello = 1
    Blue = 2
    Green = 3
    Red = 4


class EnemyTaskUnit(TaskUnit):
    def __init__(self, priority=6, waitFrame=0, workInterval=0, repeatTime=1):
        super().__init__(priority, waitFrame, workInterval, repeatTime)
        self.isEnemyUnit = True

        self.renderImage = "assets/Item/fairy.png"
        self.scaleInfo = [0.5, 0.5, 0.5]
        self.divideInfo = [12, 4]
        self.colorType = EnemyColor.Red # row
        self.imageStandBy = [1, 5]  # start - end (column)
        self.imageWalk = [6, 12]  # start - end (column)

        self.position = [0.0, 0.0, 0.0]
        self.acceleration = 0.0
        self.velocity = 0.3
        self.angle = 0.0
        self.incAngle = 0.0
        self.enemyHealth = 5

    def _setEnemyImage(self, path="assets/Item/fairy.png"):
        self.renderImage = path

    def setColorType(self, color = EnemyColor.Red ):
        self.colorType = color

    def setInitCoord(self, coord=[0.0, 0.0, 0.0]):
        self.position = coord

    def setAcceleration(self, a):
        self.acceleration = a

    def setVelocity(self, v):
        self.velocity = v

    def setAngle(self, angle = 0.0):
        if angle >= 360:
            angle -= 360
        elif angle < 0:
            angle += 360
        self.angle = angle

    def setAngleAcceleration(self, increaseAngle=0.0):
        self.incAngle = increaseAngle

    def _cpp_getUnitInfo(self):
        return self.waitFrame, self.workInterval, self.repeatTime, self.isEnemyUnit

    def _cpp_getRenderInfo(self):
        return self.renderImage, tuple( self.divideInfo),  tuple(self.scaleInfo), tuple(self.imageStandBy), tuple(self.imageWalk), self.colorType.value

    def _cpp_getEnemyInfo(self):
        return tuple(self.position), self.velocity, self.acceleration,  self.angle, self.incAngle


