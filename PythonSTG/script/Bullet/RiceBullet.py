from .CircleTypeBullet import CircleTypeBullet, BulletColor


class RiceBullet(CircleTypeBullet):
    def __init__(self):
        super().__init__()
        super()._setDivideInfo(divideType=[1, 16], divideOffset=[0.0, 0.0])
        super()._setSelectImage(coord=[1, 6])
        super()._setRenderSize([0.033, 0.033])
        super()._setCollideSize([0.033, 0.033, 0.033])
        self.isLight = False
        super().setBulletImage("assets/Bullet/riceBullet.png")

        super()._setReleaseParticleDensity(2)
        super()._setReleaseParticleLifeTime(0.4)
        super()._setReleaseParticleSize(10)
        super()._setReleaseParticleVelocity(0.3)

    def setBulletColor(self, color=BulletColor.BLUE):
        super()._circleBullet_setReleaseColor(color)
        if self.isLight:
            super()._setSelectImage(coord=[1,  color.value * 2])
        else:
            super()._setSelectImage(coord=[1, color.value * 2 + 1])

    def setBulletColorLight(self, isLight):
        lastValue = self.isLight
        self.isLight = isLight
        if (not lastValue) and self.isLight:
            super()._setSelectImage(coord=[1, super()._getSelectImage()[1] + 1])
        elif lastValue and (not self.isLight):
            super()._setSelectImage(coord=[1, super()._getSelectImage()[1] - 1])











