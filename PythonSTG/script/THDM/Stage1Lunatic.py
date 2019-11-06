import random

from ..Bullet.Bullet import BulletColor
from ..Bullet.CircleBullet import CircleBullet
from ..Bullet.HugeBullet import HugeBullet
from ..Bullet.RiceBullet import RiceBullet
from ..Bullet.OvalBullet import OvalBullet
from ..Bullet.CardBullet import CardBullet

from ..Stage.Task import Task, TaskUnit
from ..Stage.Enemy.FairyEnemy import FairyEnemy, EnemyColor, DropItem
from ..Stage.Enemy.DarkButterflyFairy import DarkButterflyFairyEnemy
from ..Stage.XCStage import XCStage, StageRank, StageBackGround
from ..Stage.Boss import Boss, SpellCard

def getStage():
    stage0 = XCStage("Stage 1")

    return stage0