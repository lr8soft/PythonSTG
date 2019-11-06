from ..TaskEnemy import TaskEnemy, EnemyColor, DropItem


class DarkButterflyFairyEnemy(TaskEnemy):
    def __init__(self, durationFrame=0, intervalFrame=0, waitFrame=0):
        super().__init__(durationFrame, intervalFrame, waitFrame)
        super()._setImagePath("assets/Enemy/darkButterflyFairy.png")
        super()._setZoomInfo([0.12, 0.12])
        super()._setDivideInfo(divideType=[12, 1], divideOffset=[0.0, 0.0])
        super()._setSpecialColumn(specialCol1=[1, 5], specialCol2=[6, 12])  # start - end (column)
        super()._setSelectImage(coord=[1, 1])
