from script.Bullet.Bullet import Bullet, BulletColor, abstractmethod


class CircleTypeBullet(Bullet):
    def __init__(self, position=[0.0, 0.0, 0.0], velocity=0.01, angle=0.0):
        super().__init__(position, velocity, angle)
        self.divideInfo = [1, 1, 1, 1]
        super()._setRenderSize([0.01,0.01,0.01])
        super()._setCollideSize([0.01, 0.01, 0.01])
        self.bulletType = "circleTypeBullet"
        self.bulletImage = ""

    @abstractmethod
    def setBulletColor(self, color=BulletColor.BLUE):
        pass

    def setBulletImage(self, bulletImagePath):
        self.bulletImage = bulletImagePath

    def _cpp_getInitRenderInfo(self):
        return self.bulletImage, self.bulletType, tuple(self.divideInfo), tuple(self.scaleSize), tuple(self.collideSize)
