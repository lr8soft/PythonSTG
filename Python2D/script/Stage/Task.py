from queue import PriorityQueue, Queue
from script.Stage.TaskUnit import TaskUnit
import uuid


class Task:
    def __init__(self, durationFrame=0, intervalFrame=0):
        self.taskUnitQueue = PriorityQueue()
        self.targetUuid = Queue()
        self.uuid = str(uuid.uuid1())
        self.duration = durationFrame
        self.intervalFrame = intervalFrame


    def addUnit(self, unit):
        if isinstance(unit, TaskUnit):
            self.taskUnitQueue.put(unit)
        else:
            raise Exception("Invalid task unit!")

    def setWorkInfo(self, repeatTime, intervalFrame):
        self.repeatTime = repeatTime
        self.intervalFrame = intervalFrame

    def addTargetUuid(self, targetUuid):
        self.targetUuid.put(targetUuid)

    def getUuid(self):
        return self.uuid

    def renewUuid(self):
        self.uuid = str(uuid.uuid1())

    def _cpp_getUnitSize(self):
        return self.taskUnitQueue.qsize()

    def _cpp_getUnitItem(self):
        return self.taskUnitQueue.get()

    def _cpp_getTaskInfo(self):
        return self.uuid, self.duration, self.intervalFrame

    def _cpp_getTargetUuidSize(self):
        return self.targetUuid.qsize()

    def _cpp_getTargetUuidSingle(self):
        return self.targetUuid.get()
