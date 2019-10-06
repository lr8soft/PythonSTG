from script.Bullet.Bullet import Bullet
class RiceBullet(Bullet):
    def __init__(self, position = [0.0,0.0,0.0],velocity = 0.01, angle = 0.0):
        super().__init__(position, velocity, angle)
        self.divideInfo = [1,16,1,6]
        self.scaleSize = [0.033, 0.033, 0.033]
        self.bulletType = "riceBullet"
        self.isLight = False

    def setBulletColorLight(self, isLight):
        self.isLight = isLight

    def _cpp_getBulletColor(self):
        if not self.isLight:
            return self.bulletColor.value * 2 + 1
        else:
            return self.bulletColor.value * 2

    def _cpp_getInitRenderInfo(self):
        return (self.bulletType, tuple(self.divideInfo), tuple(self.scaleSize))







