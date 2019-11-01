from .CircleTypeBullet import CircleTypeBullet, BulletColor


class CircleBullet(CircleTypeBullet):
    def __init__(self):
        super().__init__()
        super()._setDivideInfo(divideType=[8, 1], divideOffset=[0.0, 0.0])
        super()._setSelectImage(coord=[6, 1])
        super()._setRenderSize([0.055, 0.055])
        super()._setCollideSize([0.05, 0.05, 0.05])
        super().setBulletImage("assets/Bullet/bullet0.png")

        super()._setReleaseParticleDensity(6)
        super()._setReleaseParticleLifeTime(0.5)
        super()._setReleaseParticleSize(15)
        super()._setReleaseParticleVelocity(0.6)

    def setBulletColor(self, color=BulletColor.BLUE):
        super()._setSelectImage(coord=[color.value, 1])
        self._circleBullet_setReleaseColor(color)
