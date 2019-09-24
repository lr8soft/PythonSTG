from abc import abstractmethod
from script.Object.XCItem import XCItem
class Bullet(XCItem):
    def __init__(self):
        super().__init__()

    def collide(self):
        return True

    def render(self):
        pass


    def init(self):
        return (self)