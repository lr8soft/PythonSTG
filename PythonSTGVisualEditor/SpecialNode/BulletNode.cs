using PythonSTGVisualEditor.Sturcture;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PythonSTGVisualEditor.SpecialNode
{
    public class BulletNode:TreeNode
    {
        private Bullet currentBullet;
        public BulletNode(string varName, string className) : base() {
            currentBullet = new Bullet(varName, className);
            updateNodeInfo();
        }

        public BulletNode(Bullet bullet) : base()
        {
            currentBullet = bullet;
            updateNodeInfo();
        }

        public Bullet GetBullet() {
            return currentBullet;
        }

        public void updateNodeInfo() {
            Name = currentBullet.getVarName();
            Text = string.Format("[变量名称:{0} 类型:{1} 初始坐标:({2},{3}) 速度:{4} 加速度:{5} 角度:{6} 角速度:{7} 颜色:{8}]",
                Name, currentBullet.getClassName(), currentBullet.posX, currentBullet.posY, 
                currentBullet.velocity, currentBullet.Acceleration, currentBullet.angle, currentBullet.angleAcceleration,
                currentBullet.bulletColor.ToString());
        }
    }
}
