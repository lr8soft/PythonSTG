from script.Bullet.Bullet import Bullet, BulletColor
class HugeBullet(Bullet):
    def __init__(self, position = [0.0,0.0,0.0],velocity = 0.01, angle = 0.0):
        super().__init__(position, velocity, angle)
        self.divideInfo = [4,2,1,2]
        self.scaleSize = [0.16,0.16,0.16]
        self.bulletType = "hugeBullet"

    def setBulletColor(self, color=BulletColor.BLUE):
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

    def _cpp_getInitRenderInfo(self):
        return (self.bulletType, tuple(self.divideInfo), tuple(self.scaleSize))







