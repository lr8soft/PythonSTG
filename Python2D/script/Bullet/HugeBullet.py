from script.Bullet.CircleTypeBullet import CircleTypeBullet, BulletColor


class HugeBullet(CircleTypeBullet):
    def __init__(self):
        super().__init__()
        self.divideInfo = [4, 2, 1, 2]
        super()._setRenderSize([0.16, 0.16, 0.16])
        super()._setCollideSize([0.1, 0.1, 0.1])
        super().setBulletImage("assets/Bullet/hugeBullet.png")

        super()._setReleaseParticleDensity(15)
        super()._setReleaseParticleLifeTime(0.8)
        super()._setReleaseParticleSize(18)
        super()._setReleaseParticleVelocity(1.0)

    def setBulletColor(self, color=BulletColor.BLUE):
        super()._circleBullet_setReleaseColor(color)
        if color == BulletColor.RED:
            self.divideInfo = [4, 2, 1, 2]
        elif color == BulletColor.PURPLE:
            self.divideInfo = [4, 2, 2, 2]
        elif color == BulletColor.BLUE:
            self.divideInfo = [4, 2, 3, 2]
        elif color == BulletColor.LIGHTBLUE:
            self.divideInfo = [4, 2, 4, 2]
        elif color == BulletColor.LIGHTGREEN:
            self.divideInfo = [4, 2, 1, 1]
        elif color == BulletColor.YELLOW:
            self.divideInfo = [4, 2, 2, 1]
        elif color == BulletColor.ORANGE:
            self.divideInfo = [4, 2, 3, 1]
        elif color == BulletColor.WHITE:
            self.divideInfo = [4, 2, 4, 1]