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
    def __init__(self):
        self.position = [0.0, 0.0, 0.0]
        self.acceleration = 0.0
        self.velocity = 0.3
        self.angle = 0.0
        self.incAngle = 0.0
        self.bulletColor = BulletColor.BLUE
        self.rotateAngle = 0.0
        self.rotateWork = [0, 0, 1]
        self.aimToPlayer = False
        self.reboundCount = 0

        self.releaseParticleColor = [0.0, 0.0, 1.0, 1.0]  # RGBA, default color Blue
        self.releaseParticleDensity = 3  # Generate 3 particles after release
        self.releaseParticleLifeTime = 0.5
        self.releaseParticleVelocity = 0.6
        self.releaseParticleSize = 15

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

    def setAimToPlayer(self, aimToPlayer):
        self.aimToPlayer = aimToPlayer

    @abstractmethod
    def setBulletColor(self, color=BulletColor.BLUE):
        pass

    def setRebound(self, rebound=0):
        self.reboundCount = rebound

    def _setReleaseParticleColor(self, color=[0.0, 0.0, 1.0, 1.0]):
        self.releaseParticleColor = color

    def _setReleaseParticleDensity(self, count=3):
        self.releaseParticleDensity = count

    def _setReleaseParticleLifeTime(self, lifeTime=0.5):
        self.releaseParticleLifeTime = lifeTime

    def _setReleaseParticleVelocity(self, v=0.6):
        self.releaseParticleVelocity = v

    def _setReleaseParticleSize(self, size=15):
        self.releaseParticleSize = size

    def _setRenderSize(self, size=[0.1, 0.1, 0.1]):
        self.scaleSize = size

    def _setCollideSize(self, size):
        self.collideSize = size

    # recall function for cpp init
    def _cpp_getInitCoord(self):
        return tuple(self.position)

    def _cpp_getGenerateInfo(self):
        return self.velocity, self.acceleration, self.angle, self.incAngle, self.reboundCount, self.aimToPlayer

    @abstractmethod
    def _cpp_getInitRenderInfo(self):
        pass

    # return self.bulletType, tuple(self.divideInfo), tuple(self.scaleSize)

    def _cpp_getReleaseParticleInfo(self):
        return self.releaseParticleDensity, self.releaseParticleLifeTime, self.releaseParticleVelocity, self.releaseParticleSize, \
               tuple(self.releaseParticleColor)
