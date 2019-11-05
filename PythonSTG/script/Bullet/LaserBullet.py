from .LaserTypeBullet import  LaserTypeBullet, BulletColor


class LaserBullet(LaserTypeBullet):
    def __init__(self):
        super().__init__()
        super()._setDivideInfo(divideType=[1, 16], divideOffset=[0.0, 0.0])
        super()._setSelectImage(coord=[1, 6])
        super().setBulletImage("assets/Bullet/laserBullet.png")

        super()._setReleaseParticleDensity(10)
        super()._setReleaseParticleLifeTime(0.5)
        super()._setReleaseParticleSize(15)
        super()._setReleaseParticleVelocity(0.6)

        self.setLaserLength()

        self.isLight = False

    def setBulletColor(self, color=BulletColor.BLUE):
        if self.isLight:
            super()._setSelectImage(coord=[1,  color.value * 2])
        else:
            super()._setSelectImage(coord=[1, color.value * 2 + 1])
        self._laserBullet_setReleaseColor(color)

    def setBulletColorLight(self, isLight):
        lastValue = self.isLight
        self.isLight = isLight
        if (not lastValue) and self.isLight:
            super()._setSelectImage(coord=[1, super()._getSelectImage()[1] + 1])
        elif lastValue and (not self.isLight):
            super()._setSelectImage(coord=[1, super()._getSelectImage()[1] - 1])
