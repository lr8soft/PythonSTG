from queue import PriorityQueue
from script.Stage.TaskUnit import TaskUnit
from script.Stage.EnemyTaskUnit import EnemyTaskUnit, EnemyColor
import uuid


class Task:
    def __init__(self, durationFrame=0, intervalFrame=0, targetUuid=""):
        self.taskUnitQueue = PriorityQueue()
        self.uuid = str(uuid.uuid1())
        self.duration = durationFrame
        self.intervalFrame = intervalFrame
        self.targetUuid = targetUuid

    def addUnit(self, unit):
        if isinstance(unit, TaskUnit):
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
