import random

from script.Bullet.Bullet import BulletColor
from script.Bullet.CircleBullet import CircleBullet
from script.Bullet.HugeBullet import HugeBullet
from script.Bullet.RiceBullet import RiceBullet
from script.Stage.Task import Task, TaskUnit
from script.Stage.TaskEnemy import TaskEnemy
from script.Stage.XCStage import XCStage


# demo show how to create a custom stage
# 演示如何创建并返回一个自定义关卡
def setupMyStage():
    stage0 = XCStage("Stage TEST")
    # task 0
    enemyTest = TaskEnemy(durationFrame=-1, intervalFrame=0)
    enemyTest.setInitCoord([0.0, 1.0, 0.0])
    enemyTest.setAngle(270.0)
    enemyTest.setVelocity(0.2)
    # bullet group 0
    unit0 = TaskUnit(waitFrame=60, repeatTime=3)
    for j in range(0, 36):
        bullet = CircleBullet()
        bullet.setVelocity(0.6)
        bullet.setAngle(j * 10)
        bullet.setBulletColor(BulletColor.BLUE)
        unit0.addBullet(bullet)
    enemyTest.addUnit(unit0)
    # bullet group 1
    enemyTest2 = TaskEnemy(durationFrame=-1, intervalFrame=0)
    enemyTest2.setAngle(270.0)
    enemyTest2.setVelocity(0.2)
    enemyTest2.setInitCoord([-0.5, 1.0, 0.0])

    unit1 = TaskUnit(waitFrame=120, repeatTime=3)
    unit2 = TaskUnit(waitFrame=120, repeatTime=3)
    for i in range(0, 72):
        if i % 2 == 0:
            bullet = CircleBullet()
            bullet.setInitCoord([0.5, 0.5, 0.0])
            bullet.setVelocity(0.6)
            bullet.setBulletColor(BulletColor.ORANGE)
            bullet.setAngle(i * 5)
            bullet.setAngleAcceleration(20)
            unit1.addBullet(bullet)
        else:
            bullet = CircleBullet()
            bullet.setInitCoord([-0.5, -0.5, 0.0])
            bullet.setVelocity(0.6)
            bullet.setBulletColor(BulletColor.PURPLE)
            bullet.setAngle(i * 10)
            bullet.setAngleAcceleration(-20)
            unit2.addBullet(bullet)
    enemyTest2.addUnit(unit1)

    enemyTest3 = TaskEnemy(durationFrame=-1, intervalFrame=0)
    enemyTest3.setAngle(270.0)
    enemyTest3.setVelocity(0.2)
    enemyTest3.addUnit(unit2)
    enemyTest3.setInitCoord([0.5, 1.0, 0.0])

    stage0.addTask(enemyTest)
    stage0.addTask(enemyTest2)
    stage0.addTask(enemyTest3)

    # task 2
    taskAfter = Task(durationFrame=-1, intervalFrame=0, targetUuid=enemyTest.getUuid())
    unit2_0 = TaskUnit()
    for j in range(0, 36):
        bullet = HugeBullet()
        bullet.setVelocity(0.8)
        bullet.setAngle(j * 10)
        bullet.setAngleAcceleration(65)
        bullet.setBulletColor(BulletColor.LIGHTBLUE)
        bullet.setRebound(3)
        unit2_0.addBullet(bullet)

    unit2_1 = TaskUnit(waitFrame=360)
    for k in range(0, 180):
        bullet = RiceBullet()
        bullet.setVelocity(0.9)
        bullet.setAngle(k * 2)
        bullet.setAngleAcceleration(-5)
        bullet.setBulletColorLight(True)
        if k % 2 == 0:
            bullet.setBulletColor(BulletColor.LIGHTBLUE)
            bullet.setAcceleration(0.1)
            bullet.setRebound(3)
        else:
            bullet.setBulletColor(BulletColor.LIGHTGREEN)
            bullet.setAcceleration(-0.1)
            bullet.setRebound(10)

        unit2_1.addBullet(bullet)
    taskAfter.addUnit(unit2_0)
    taskAfter.addUnit(unit2_1)
    stage0.addTask(taskAfter)

    # task 3
    taskAimPlayer = Task(durationFrame=-1, intervalFrame=0, targetUuid=taskAfter.getUuid())
    for i in range(1, 100):
        unit = TaskUnit(waitFrame=i * 15)
        bullet = CircleBullet()
        bullet.setBulletColor(BulletColor.LIGHTBLUE)
        bullet.setInitCoord([0.5, 1.0, 0.0])
        bullet.setVelocity(0.9)
        bullet.setAimToPlayer(True)
        unit.addBullet(bullet)

        bullet2 = CircleBullet()
        bullet2.setBulletColor(BulletColor.LIGHTGREEN)
        bullet2.setInitCoord([-0.5, 1.0, 0.0])
        bullet2.setVelocity(0.9)
        bullet2.setAimToPlayer(True)
        unit.addBullet(bullet2)
        taskAimPlayer.addUnit(unit)

    for j in range(1, 100):
        unit = TaskUnit(waitFrame=j * 15)
        bullet = CircleBullet()
        bullet.setBulletColor(BulletColor.LIGHTBLUE)
        bullet.setInitCoord([1.0, 0.5, 0.0])
        bullet.setVelocity(0.9)
        bullet.setAimToPlayer(True)
        unit.addBullet(bullet)

        bullet2 = CircleBullet()
        bullet2.setBulletColor(BulletColor.LIGHTGREEN)
        bullet2.setInitCoord([-1.0, 0.5, 0.0])
        bullet2.setVelocity(0.9)
        bullet2.setAimToPlayer(True)
        unit.addBullet(bullet2)
        taskAimPlayer.addUnit(unit)

    for k in range(1, 80):
        unit = TaskUnit(waitFrame=k * 25)
        for c in range(1, 10):
            bullet = CircleBullet()
            bullet.setBulletColor(BulletColor.BLUE)
            bullet.setRebound(1)
            if c % 2 == 0:
                bullet.setInitCoord([0.5, 1.0, 0.0])
            else:
                bullet.setInitCoord([-0.5, 1.0, 0.0])
            bullet.setAngle( (180 + c * 18) * random.random())
            bullet.setVelocity(0.6)
            unit.addBullet(bullet)
        taskAimPlayer.addUnit(unit)

    stage0.addTask(taskAimPlayer)
    return stage0 #返回创建的关卡
