from script.Bullet.CircleTypeBullet import CircleTypeBullet, BulletColor


class CircleBullet(CircleTypeBullet):
    def __init__(self, position = [0.0,0.0,0.0],velocity = 0.01, angle = 0.0):
        super().__init__(position, velocity, angle)
        self.divideInfo = [8,1,6,1]
        super()._setRenderSize([0.055,0.055,0.055])
        super()._setCollideSize([0.055,0.055,0.055])
        super().setBulletImage("assets/Bullet/bullet0.png")

    def setBulletColor(self, color=BulletColor.BLUE):
        self.divideInfo[2] = color.value






