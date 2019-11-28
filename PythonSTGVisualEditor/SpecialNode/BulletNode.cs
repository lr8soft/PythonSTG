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
        public Bullet currentBullet { get; set; }
        public BulletNode(string varName, string className) : base() {
            currentBullet = new Bullet();
            currentBullet.bulletVarName =  varName;
            currentBullet.bulletClassName = className;
            updateNodeInfo();
        }

        public BulletNode(Bullet bullet) : base()
        {
            currentBullet = bullet;
            updateNodeInfo();
        }

        public void updateNodeInfo() {
            Name = currentBullet.bulletVarName;
            Text = string.Format("[变量名称:{0} 类型:{1} 初始坐标:({2},{3}) 速度:{4} 加速度:{5} 角度:{6} 角速度:{7} 颜色:{8}]",
                Name, currentBullet.bulletClassName, currentBullet.posX, currentBullet.posY, 
                currentBullet.velocity, currentBullet.Acceleration, currentBullet.angle, currentBullet.angleAcceleration,
                currentBullet.bulletColor.ToString());
        }
    }
}
