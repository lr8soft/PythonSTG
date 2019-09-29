from abc import abstractmethod
from enum import Enum


class BulletColor(Enum):
    RED = 1
    PURPLE = 2
    BLUE = 3
    LIGHTBLUE = 4
    LIGHTGREEN = 5
    YELLOW = 6
    ORANGE = 7
    WHITE = 8


class Bullet:
    def __init__(self, position=[0.0, 0.0, 0.0], velocity=0.0, acceleration=0.0, angle=0.0, increaseAnglePerTick=0.0):
        self.position = position
        self.acceleration = acceleration
        self.velocity = velocity
        self.angle = angle
        self.incAngle = increaseAnglePerTick
        self.bulletColor = BulletColor.BLUE
        self.rotateAngle = 0.0
        self.rotateWork = [0, 0, 1]
        self.aimToPlayer = False

    def setAcceleration(self, a):
        self.acceleration = a

    def setVelocity(self, v):
        self.velocity = v

    def setAngle(self, angle, increaseAngle = 0.0):
        self.angle = angle
        self.incAngle = increaseAngle

    def setAimToPlayer(self, aimToPlayer):
        self.aimToPlayer = aimToPlayer

    def setBulletColor(self, color=BulletColor.BLUE):
        self.bulletColor = color

    #recall function for cpp init
    def _cpp_getInitCoord(self):
        return tuple(self.position)

    def _cpp_getGenerateInfo(self):
        return self.velocity, self.acceleration, self.angle, self.incAngle, self.aimToPlayer

    def _cpp_getBulletColor(self):
        return self.bulletColor.value

    @abstractmethod
    def _cpp_getInitRenderInfo(self):
        pass
    # return self.bulletType, tuple(self.divideInfo), tuple(self.scaleSize)

