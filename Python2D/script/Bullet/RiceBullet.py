from script.Bullet.CircleTypeBullet import CircleTypeBullet, BulletColor


class RiceBullet(CircleTypeBullet):
    def __init__(self, position = [0.0,0.0,0.0],velocity = 0.01, angle = 0.0):
        super().__init__(position, velocity, angle)
        self.divideInfo = [1,16,1,6]
        self.scaleSize = [0.033, 0.033, 0.033]
        self.isLight = False
        super().setBulletImage("assets/Bullet/riceBullet.png")

    def setBulletColor(self, color=BulletColor.BLUE):
        if self.isLight:
            self.divideInfo[3] = color.value * 2
        else:
            self.divideInfo[3] = color.value * 2 + 1

    def setBulletColorLight(self, isLight):
        self.isLight = isLight









