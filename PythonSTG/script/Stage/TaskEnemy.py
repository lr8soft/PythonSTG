from .Task import Task
from ..Helper.DropItemHelper import DropItemHelper, DropItem
from enum import Enum
from queue import Queue


class EnemyColor(Enum):
    Yellow = 1
    Blue = 2
    Green = 3
    Red = 4


class TaskEnemy(Task, DropItemHelper):
    def __init__(self, durationFrame=0, intervalFrame=0, waitFrame=0):
        Task.__init__(self, durationFrame, intervalFrame, waitFrame)
        DropItemHelper.__init__(self)

        self.isEnemyTask = True

        self.renderImage = "assets/Item/fairy.png"
        self.scaleInfo = [0.06, 0.06, 0.06]
        self.divideInfo = [12, 4]
        self.colorType = EnemyColor.Red  # row
        self.imageStandBy = [1, 5]  # start - end (column)
        self.imageWalk = [6, 12]  # start - end (column)

        self.position = [0.0, 0.0, 0.0]
        self.movingTime = -1.0
        self.acceleration = 0.0
        self.velocity = 0.3
        self.angle = 0.0
        self.incAngle = 0.0
        self.enemyHealth = 5.0

    def _setEnemyImage(self, path="assets/Item/fairy.png"):
        self.renderImage = path

    def setColorType(self, color=EnemyColor.Red):
        self.colorType = color

    def setInitCoord(self, coord=[0.0, 0.0, 0.0]):
        self.position = coord

    def setAcceleration(self, a):
        self.acceleration = a

    def setVelocity(self, v):
        self.velocity = v

    def setMovingTime(self, movingTime=-1.0):
        self.movingTime = movingTime

    def setAngle(self, angle=0.0):
        if angle >= 360:
            angle -= 360
        elif angle < 0:
            angle += 360
        self.angle = angle

    def setAngleAcceleration(self, increaseAngle=0.0):
        self.incAngle = increaseAngle

    def setHealthValue(self, value=5.0):
        self.enemyHealth = value

    def _cpp_getTaskInfo(self):
        return self.uuid, self.duration, self.intervalFrame, self.waitFrame, self.isEnemyTask

    def _cpp_getRenderInfo(self):
        return self.renderImage, tuple(self.divideInfo), tuple(self.scaleInfo), tuple(self.imageStandBy), tuple(
            self.imageWalk), self.colorType.value

    def _cpp_getEnemyInfo(self):
        return tuple(
            self.position), self.velocity, self.movingTime, self.acceleration, self.angle, self.incAngle, self.enemyHealth
