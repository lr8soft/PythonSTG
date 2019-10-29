from .RectangleTypeBullet import RectangleTypeBullet, BulletColor

class CardBullet(RectangleTypeBullet):
    def __init__(self):
        super().__init__()
        self.divideInfo = [1, 16, 1, 6]
        self.isLight = False
        super()._setCollideSize([0.0352, 0.02, 0.055])
        super()._setRenderSize([0.0352, 0.044, 0.055])
        super().setBulletImage("assets/Bullet/cardBullet.png")

        super()._setReleaseParticleDensity(10)
        super()._setReleaseParticleLifeTime(0.5)
        super()._setReleaseParticleSize(15)
        super()._setReleaseParticleVelocity(0.6)

    def setBulletColor(self, color=BulletColor.BLUE):
        if self.isLight:
            self.divideInfo[3] = 16 - color.value * 2
        else:
            self.divideInfo[3] = 16 - color.value * 2 + 1
        self._ovalBullet_setReleaseColor(color)

    def setBulletColorLight(self, isLight):
        lastValue = self.isLight
        self.isLight = isLight
        if (not lastValue) and self.isLight:
            self.divideInfo[3] += 1
        elif lastValue and (not self.isLight):
            self.divideInfo[3] -= 1
