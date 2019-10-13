from queue import Queue
from script.Bullet.Bullet import Bullet


class TaskUnit:
    def __init__(self, priority=6, waitFrame=0, workInterval=0, repeatTime=1):
        self.priority = priority;
        self.waitFrame = waitFrame
        self.workInterval = workInterval
        self.repeatTime = repeatTime
        self.bulletGroup = Queue()

    def addBullet(self, bullet):
        if isinstance(bullet, Bullet):
            self.bulletGroup.put(bullet)
        else:
            raise Exception("Insert invalid bullet.")

    def _cpp_getUnitInfo(self):
        return self.waitFrame, self.workInterval, self.repeatTime

    def _cpp_getBulletSize(self):
        return self.bulletGroup.qsize()

    def _cpp_getBulletItem(self):
        return self.bulletGroup.get()

    def __eq__(self, other):
        try:
            return self.priority == other.priority;
        except AttributeError:
            return NotImplemented

    def __lt__(self, other):
        try:
            return self.priority < other.priority;
        except AttributeError:
            return NotImplemented
