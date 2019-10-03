from queue import PriorityQueue
from queue import Queue
from script.Bullet.Bullet import Bullet
import uuid

class TaskUnit:
    def __init__(self, priority = 6, waitFrame = 0, workInterval = 0, repeatTime = 1):
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
        return  self.waitFrame, self.workInterval, self.repeatTime

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

class Task:
    def __init__(self, durationFrame=0, intervalFrame=0, targetUuid=""):
        self.taskUnitQueue = PriorityQueue()
        self.uuid = str(uuid.uuid1())
        self.duration = durationFrame
        self.intervalFrame = intervalFrame
        self.targetUuid = targetUuid

    def addUnit(self, unit):
        if isinstance(unit,TaskUnit):
            self.taskUnitQueue.put(unit)
        else:
            raise Exception("Invalid task unit!")

    def setWorkInfo(self, repeatTime, intervalFrame):
        self.repeatTime = repeatTime
        self.intervalFrame = intervalFrame

    def setTargetUuid(self, targetUuid):
        self.targetUuid = targetUuid

    def getUuid(self):
        return self.uuid

    def _cpp_getUnitSize(self):
        return self.taskUnitQueue.qsize()

    def _cpp_getUnitItem(self):
        return self.taskUnitQueue.get()

    def _cpp_getTaskInfo(self):
        return self.uuid, self.targetUuid, self.duration, self.intervalFrame

