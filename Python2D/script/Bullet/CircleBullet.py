from script.Bullet.Bullet import Bullet
class CircleBullet(Bullet):
    def __init__(self, position = [0.0,0.0,0.0],velocity = 0.2, angle = 0.0):
        super().__init__(position, velocity, angle)
        self.divideInfo = [8,1,6,1]
        self.scaleSize = [0.055,0.055,0.055]
        self.bulletType = "circleBullet"

    def _cpp_getInitRenderInfo(self):
        return (self.bulletType, tuple(self.divideInfo), tuple(self.scaleSize))







