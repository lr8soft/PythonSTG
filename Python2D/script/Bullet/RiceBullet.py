from script.Bullet.CircleTypeBullet import CircleTypeBullet, BulletColor


class RiceBullet(CircleTypeBullet):
    def __init__(self, position = [0.0,0.0,0.0],velocity = 0.01, angle = 0.0):
        super().__init__(position, velocity, angle)
        self.divideInfo = [1,16,1,6]
        self.scaleSize = [0.033, 0.033, 0.033]
        self.isLight = False
        super().setBulletImage("assets/Bullet/riceBullet.png")

    # RED = 1
    # PURPLE = 2
    # BLUE = 3
    # LIGHTBLUE = 4
    # LIGHTGREEN = 5
    # YELLOW = 6
    # ORANGE = 7
    # WHITE = 8
    def setBulletColor(self, color=BulletColor.BLUE):
        if self.isLight:
            self.divideInfo[3] = color.value * 2
        else:
            self.divideInfo[3] = color.value * 2 + 1

    def setBulletColorLight(self, isLight):
        lastValue = self.isLight
        self.isLight = isLight
        if (not lastValue) and self.isLight:
            self.divideInfo[3] += 1
        elif lastValue and (not self.isLight):
            self.divideInfo[3] -= 1











