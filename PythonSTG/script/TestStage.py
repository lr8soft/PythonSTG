import random

from .Bullet.Bullet import BulletColor
from .Bullet.CircleBullet import CircleBullet
from .Bullet.HugeBullet import HugeBullet
from .Bullet.RiceBullet import RiceBullet
from .Bullet.OvalBullet import OvalBullet
from .Bullet.CardBullet import CardBullet
from .Bullet.LaserBullet import LaserBullet
from .Stage.Task import Task, TaskUnit
from .Stage.TaskEnemy import TaskEnemy, EnemyColor, DropItem
from .Stage.XCStage import XCStage, StageRank
from .Stage.Boss import Boss, SpellCard


# demo show how to create a custom stage
# 演示如何创建并返回一个自定义关卡
# 方法说明请阅读文档 PythonSTG 使用手册
def setupMyStage():
    stage0 = XCStage("Stage TEST")
    stage0.setBackGroundMusic("assets/Media/stage1.wav")
    stage0.setStageRank(StageRank.Lunatic)
    # task 0
    enemyTest = TaskEnemy(durationFrame=-1, intervalFrame=0, waitFrame=60)
    enemyTest.addItemDrop(DropItem.MoonPoint, 15)
    enemyTest.addItemDrop(DropItem.Power, 15)
    enemyTest.setInitCoord([0.0, 1.0, 0.0])
    enemyTest.setMovingTime(2.0)
    enemyTest.setAngle(270.0)
    enemyTest.setVelocity(0.2)
    # bullet group 0
    unit0 = TaskUnit(waitFrame=60, repeatTime=3)
    for j in range(0, 36):
        bullet = OvalBullet()
        bullet.setVelocity(0.6)
        bullet.setAngle(j * 10)
        bullet.setBulletColor(BulletColor.BLUE)
        unit0.addBullet(bullet)
    enemyTest.addUnit(unit0)
    # bullet group 1
    enemyTest2 = TaskEnemy(durationFrame=-1, intervalFrame=0)
    enemyTest2.addItemDrop(DropItem.MoonPoint, 15)
    enemyTest2.addItemDrop(DropItem.Power, 15)
    enemyTest2.setMovingTime(2.0)
    enemyTest2.setAngle(270.0)
    enemyTest2.setVelocity(0.2)
    enemyTest2.setInitCoord([-0.5, 1.0, 0.0])

    unit1 = TaskUnit(waitFrame=120, repeatTime=3)
    unit2 = TaskUnit(waitFrame=120, repeatTime=3)
    for i in range(0, 72):
        if i % 2 == 0:
            bullet = OvalBullet()
            bullet.setInitCoord([0.5, 0.5, 0.0])
            bullet.setVelocity(0.6)
            bullet.setBulletColor(BulletColor.ORANGE)
            bullet.setAngle(i * 5)
            bullet.setAngleAcceleration(20)
            unit1.addBullet(bullet)
        else:
            bullet = OvalBullet()
            bullet.setInitCoord([-0.5, -0.5, 0.0])
            bullet.setVelocity(0.6)
            bullet.setBulletColor(BulletColor.PURPLE)
            bullet.setAngle(i * 10)
            bullet.setAngleAcceleration(-20)
            unit2.addBullet(bullet)
    enemyTest2.addUnit(unit1)

    enemyTest3 = TaskEnemy(durationFrame=-1, intervalFrame=0)
    enemyTest3.addItemDrop(DropItem.MoonPoint, 15)
    enemyTest3.addItemDrop(DropItem.Power, 15)
    enemyTest3.setMovingTime(2.0)
    enemyTest3.setAngle(270.0)
    enemyTest3.setVelocity(0.2)
    enemyTest3.addUnit(unit2)
    enemyTest3.setInitCoord([0.5, 1.0, 0.0])

    stage0.addTask(enemyTest)
    stage0.addTask(enemyTest2)
    stage0.addTask(enemyTest3)

    # task 2
    taskAfter = TaskEnemy(durationFrame=-1, intervalFrame=0)
    taskAfter.addItemDrop(DropItem.MoonPoint, 15)
    taskAfter.addItemDrop(DropItem.Power, 35)
    taskAfter.setColorType(EnemyColor.Blue)
    taskAfter.setInitCoord([0.0, 1.0, 0.0])
    taskAfter.setMovingTime(2.0)
    taskAfter.setVelocity(0.5)
    taskAfter.setHealthValue(20)
    taskAfter.setAngle(270)

    taskAfter.addTargetUuid(enemyTest.getUuid())
    taskAfter.addTargetUuid(enemyTest2.getUuid())
    taskAfter.addTargetUuid(enemyTest3.getUuid())
    unit2_0 = TaskUnit(waitFrame=120)
    for j in range(0, 18):
        bullet = HugeBullet()
        bullet.setVelocity(0.8)
        bullet.setAngle(j * 20)
        bullet.setAngleAcceleration(65)
        bullet.setBulletColor(BulletColor.LIGHTBLUE)
        bullet.setRebound(3)
        unit2_0.addBullet(bullet)

    unit2_1 = TaskUnit(waitFrame=480)
    for k in range(0, 90):
        bullet = RiceBullet()
        bullet.setVelocity(0.9)
        bullet.setAngle(k * 4)
        bullet.setAngleAcceleration(-5)
        bullet.setBulletColorLight(True)
        if k % 2 == 0:
            bullet.setBulletColor(BulletColor.LIGHTBLUE)
            bullet.setAcceleration(0.06)
            bullet.setRebound(2)
        else:
            bullet.setBulletColor(BulletColor.LIGHTGREEN)
            bullet.setAcceleration(-0.06)
            bullet.setRebound(4)

        unit2_1.addBullet(bullet)
    taskAfter.addUnit(unit2_0)
    taskAfter.addUnit(unit2_1)
    stage0.addTask(taskAfter)


    #spellcard test
    unit_spellcard = TaskUnit(repeatTime=60,waitFrame=20)
    for j in range(0, 36):
        bullet = CardBullet()
        bullet.setVelocity(0.6*(1+random.random()))
        bullet.setAngle(j * 10)
        bullet.setBulletColor(BulletColor.RED)
        if j %2 == 0:
            bullet.setBulletColorLight(True)
        unit_spellcard.addBullet(bullet)

    task_spellcard = Task(durationFrame=-1)
    task_spellcard.addUnit(unit_spellcard)

    spellcard = SpellCard()
    spellcard.addItemDrop(DropItem.Life, 1)
    spellcard.setSpellCardHealthPoint(30.0)
    spellcard.addTask(task_spellcard)

    unit_spellcard2 =TaskUnit(repeatTime=60,waitFrame=20)
    for j in range(0, 36):
        bullet = CardBullet()
        bullet.setVelocity(0.6)
        bullet.setAngle(j * 10)
        bullet.setBulletColor(BulletColor.RED)
        if j % 2 == 0:
            bullet.setBulletColorLight(True)
        unit_spellcard2.addBullet(bullet)

    task_spellcard2 = Task(durationFrame=-1)
    task_spellcard2.addUnit(unit_spellcard2)

    spellcard2 = SpellCard()
    spellcard2.addItemDrop(DropItem.Bomb, 1)
    spellcard2.setSpellCardHealthPoint(30.0)
    spellcard2.setBossMovePosition([0.0, 0.0])
    spellcard2.setSpellCardName("TestSpellCard ~ Lunatic")
    spellcard2.addTask(task_spellcard2)

    #boss
    boss = Boss()
    boss.SetBossName("Fujiwara no Mokou")
    boss.SetBossMusic("assets/Media/boss1.wav")
    boss.AddTargetUuid(taskAfter.getUuid())
    boss.AddSpellCard(spellcard)
    boss.AddSpellCard(spellcard2)
    stage0.addBoss(boss)

    # task 3
    lastuuid = task_spellcard2.getUuid()
    lastuuid2 = task_spellcard2.getUuid()
    for i in range(1, 10):
        enemyAimPlayer = TaskEnemy(durationFrame=-1, intervalFrame=0)
        enemyAimPlayer.addItemDrop(DropItem.MoonPoint, 3)
        enemyAimPlayer.setHealthValue(1.0)
        enemyAimPlayer.setInitCoord([0.5, 1.0, 0.0])
        enemyAimPlayer.setVelocity(1.0)
        enemyAimPlayer.setAngle(225.0)
        enemyAimPlayer.setAngleAcceleration(-20)
        enemyAimPlayer.addTargetUuid(lastuuid)
        lastuuid = enemyAimPlayer.getUuid()

        enemyAimPlayer2 = TaskEnemy(durationFrame=-1, intervalFrame=0)
        enemyAimPlayer2.addItemDrop(DropItem.MoonPoint, 3)
        enemyAimPlayer2.setInitCoord([-0.5, 1.0, 0.0])
        enemyAimPlayer2.setHealthValue(1.0)
        enemyAimPlayer2.setVelocity(1.0)
        enemyAimPlayer2.setAngle(315.0)
        enemyAimPlayer2.setAngleAcceleration(20)
        enemyAimPlayer2.addTargetUuid(lastuuid2)
        lastuuid2 = enemyAimPlayer2.getUuid()

        unit = TaskUnit(waitFrame=15)
        unit2 = TaskUnit(waitFrame=15)
        bullet = CircleBullet()
        bullet.setBulletColor(BulletColor.LIGHTBLUE)
        bullet.setVelocity(1.2)
        bullet.setAimToPlayer(True)
        unit.addBullet(bullet)

        bullet2 = CircleBullet()
        bullet2.setBulletColor(BulletColor.LIGHTGREEN)
        bullet2.setVelocity(1.2)
        bullet2.setAimToPlayer(True)
        unit2.addBullet(bullet2)
        enemyAimPlayer.addUnit(unit)
        enemyAimPlayer2.addUnit(unit2)

        unit = TaskUnit(waitFrame=15)
        unit2 = TaskUnit(waitFrame=15)
        bullet = CircleBullet()
        bullet.setBulletColor(BulletColor.LIGHTBLUE)
        bullet.setVelocity(1.5)
        bullet.setAimToPlayer(True)
        unit.addBullet(bullet)

        bullet2 = CircleBullet()
        bullet2.setBulletColor(BulletColor.LIGHTGREEN)
        bullet2.setVelocity(1.5)
        bullet2.setAimToPlayer(True)
        unit2.addBullet(bullet2)
        enemyAimPlayer.addUnit(unit)
        enemyAimPlayer2.addUnit(unit2)

        stage0.addTask(enemyAimPlayer)
        stage0.addTask(enemyAimPlayer2)

    taskAimPlayer = Task(durationFrame=-1, intervalFrame=0)
    taskAimPlayer.addTargetUuid(task_spellcard2.getUuid())
    for k in range(1, 40):
        unit = TaskUnit(waitFrame=k * 25)
        for c in range(1, 10):
            bullet = CircleBullet()
            bullet.setBulletColor(BulletColor.BLUE)
            bullet.setRebound(1)
            if c % 2 == 0:
                bullet.setInitCoord([0.5, 1.0, 0.0])
            else:
                bullet.setInitCoord([-0.5, 1.0, 0.0])
            bullet.setAngle((180 + c * 18) * random.random())
            bullet.setVelocity(0.6)
            unit.addBullet(bullet)
        taskAimPlayer.addUnit(unit)

    stage0.addTask(taskAimPlayer)


    return stage0 #返回创建的关卡
