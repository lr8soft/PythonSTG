from .CircleTypeBullet import CircleTypeBullet, BulletColor


class HugeBullet(CircleTypeBullet):
    def __init__(self):
        super().__init__()
        super()._setDivideInfo(divideType=[4, 2], divideOffset=[0.0, 0.0])
        super()._setSelectImage(coord=[4, 2])
        super()._setRenderSize([0.16, 0.16])
        super()._setCollideSize([0.1, 0.1, 0.1])
        super().setBulletImage("assets/Bullet/hugeBullet.png")

        super()._setReleaseParticleDensity(15)
        super()._setReleaseParticleLifeTime(0.8)
        super()._setReleaseParticleSize(18)
        super()._setReleaseParticleVelocity(1.0)

    def setBulletColor(self, color=BulletColor.BLUE):
        super()._circleBullet_setReleaseColor(color)
        if color == BulletColor.RED:
            super()._setSelectImage(coord=[1, 2])
        elif color == BulletColor.PURPLE:
            super()._setSelectImage(coord=[2, 2])
        elif color == BulletColor.BLUE:
            super()._setSelectImage(coord=[3, 2])
        elif color == BulletColor.LIGHTBLUE:
            super()._setSelectImage(coord=[4, 2])
        elif color == BulletColor.LIGHTGREEN:
            super()._setSelectImage(coord=[1, 1])
        elif color == BulletColor.YELLOW:
            super()._setSelectImage(coord=[2, 1])
        elif color == BulletColor.ORANGE:
            super()._setSelectImage(coord=[3, 1])
        elif color == BulletColor.WHITE:
            super()._setSelectImage(coord=[4, 1])
