from .Bullet import Bullet, BulletColor, abstractmethod


class RectangleTypeBullet(Bullet):
    def __init__(self):
        super().__init__()
        super()._setCollideSize([0.055, 0.0275])
        super()._setRenderSize([0.055, 0.055])
        self.bulletType = "rectangleTypeBullet"

    @abstractmethod
    def setBulletColor(self, color=BulletColor.BLUE):
        pass

    def _cpp_getBulletInfo(self):
        return self.bulletType

    def _ovalBullet_setReleaseColor(self, color=BulletColor.BLUE):
        if color == BulletColor.LIGHTGREEN:
            super()._setReleaseParticleColor([0.58, 0.72, 0.15, 1.0])
        elif color == BulletColor.RED:
            super()._setReleaseParticleColor([1.0, 0.0, 0.0, 1.0])
        elif color == BulletColor.BLUE:
            super()._setReleaseParticleColor([0.0, 0.0, 1.0, 1.0])
        elif color == BulletColor.YELLOW:
            super()._setReleaseParticleColor([1.0, 0.85, 0.15, 1.0])
        elif color == BulletColor.LIGHTBLUE:
            super()._setReleaseParticleColor([0.0, 1.0, 1.0, 1.0])
        elif color == BulletColor.ORANGE:
            super()._setReleaseParticleColor([1.0, 0.55, 0.27, 1.0])
        elif color == BulletColor.PURPLE:
            super()._setReleaseParticleColor([1.0, 0.35, 1.0, 1.0])
        elif color == BulletColor.WHITE:
            super()._setReleaseParticleColor([0.76, 0.76, 0.76, 1.0])
        else:
            super()._setReleaseParticleColor([0.8, 0.8, 0.8, 1.0])
