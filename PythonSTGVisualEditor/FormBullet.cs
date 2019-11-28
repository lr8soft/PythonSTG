using PythonSTGVisualEditor.Sturcture;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Microsoft.VisualBasic;

namespace PythonSTGVisualEditor
{
    public partial class FormBullet : Form
    {
        public DialogResult Result { get; set; }
        private Bullet currentBullet;

        private static long bulletCount = 0;
        public FormBullet(string pythonClassName)
        {
            InitializeComponent();
            InitCustomizedComponent();

            currentBullet = new Bullet();
            currentBullet.bulletVarName = "testBullet" + (bulletCount++);
            currentBullet.bulletClassName = pythonClassName;

            currentBullet.velocity = 1.0f;
            currentBullet.Acceleration = 0.0f;
            currentBullet.angle = 270.0f;
            currentBullet.posX = 0.0f;
            currentBullet.posY = 0.5f;
            currentBullet.angleAcceleration = 0.0f;
            currentBullet.bulletColor = Bullet.BulletColor.BLUE;
            className.Text = pythonClassName;
        }

        public FormBullet(Bullet bullet)
        {
            InitializeComponent();
            InitCustomizedComponent();

            currentBullet = (Bullet)bullet.Clone();
            varName.Text = currentBullet.bulletVarName;
            className.Text = currentBullet.bulletClassName;
            velocity.Text = currentBullet.velocity.ToString();
            acceleration.Text = currentBullet.Acceleration.ToString();
            angle.Text = currentBullet.angle.ToString();
            angleVelocity.Text = currentBullet.angleAcceleration.ToString();
            aimToPlayer.Text = currentBullet.aimToPlayer.ToString();
            color.Text = currentBullet.bulletColor.ToString();
            reBound.Text = currentBullet.reBound.ToString();
            posX.Text = currentBullet.posX.ToString();
            posY.Text = currentBullet.posY.ToString();
        }

        private void btnSubmit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void BulletAttributeTree_DoubleClick(object sender, EventArgs e)
        {
            TreeView treeView = (TreeView)sender;
            TreeNode node = treeView.SelectedNode;
            if (node.Parent != null)
            {
                string currentValue = node.Text;
                string value = Interaction.InputBox("输入值:", "Input value", currentValue);
                if (value.Length > 0)
                {
                    string lastValue = node.Text;
                    node.Text = value;
                    updateTaskInfo(node.Name, lastValue, value);
                }
            }
        }

        private void updateTaskInfo(string name, string lastValue, string currentValue) {
            switch (name) {
                case "varName":
                    currentBullet.bulletVarName = currentValue; break;
                case "className":
                    currentBullet.bulletClassName = currentValue; break;
                case "velocity":
                    currentBullet.velocity = float.Parse(currentValue); break;
                case "acceleration":
                    currentBullet.Acceleration = float.Parse(currentValue); break;
                case "angle":
                    currentBullet.angle = float.Parse(currentValue); break;
                case "angleVelocity":
                    currentBullet.angleAcceleration = float.Parse(currentValue); break;
                case "aimToPlayer":
                    currentBullet.aimToPlayer = currentValue == "True" ? true : false; break;
                case "color":
                    switch (currentValue) {
                        case "RED":currentBullet.bulletColor = Bullet.BulletColor.RED;break;
                        case "WHITE": currentBullet.bulletColor = Bullet.BulletColor.WHITE; break;
                        case "YELLOW": currentBullet.bulletColor = Bullet.BulletColor.YELLOW; break;
                        case "BLUE": currentBullet.bulletColor = Bullet.BulletColor.BLUE; break;
                        case "LIGHTBLUE": currentBullet.bulletColor = Bullet.BulletColor.LIGHTBLUE; break;
                        case "LIGHTGREEN": currentBullet.bulletColor = Bullet.BulletColor.LIGHTGREEN; break;
                        case "ORANGE": currentBullet.bulletColor = Bullet.BulletColor.ORANGE; break;
                        case "PURPLE": currentBullet.bulletColor = Bullet.BulletColor.PURPLE; break;
                    }
                    break;
                case "reBound":
                    currentBullet.reBound = int.Parse(currentValue); break;
                case "posX":
                    currentBullet.posX = float.Parse(currentValue); break;
                case "posY":
                    currentBullet.posY = float.Parse(currentValue); break;

            }
        }

        public static Bullet Execute(string className)
        {
            using (var form = new FormBullet(className))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK)
                {
                    return form.currentBullet;
                }
                else
                {
                    return null;
                }
            }
        }

        public static Bullet Execute(Bullet bullet)
        {
            using (var form = new FormBullet(bullet))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK)
                {
                    return form.currentBullet;
                }
                else
                {
                    return null;
                }
            }
        }

        private TreeNode varName, className, velocity, acceleration, angle, angleVelocity, aimToPlayer, color, reBound, posX, posY;
        private void InitCustomizedComponent() {
            varName = new System.Windows.Forms.TreeNode("testBullet0");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("变量名称", new System.Windows.Forms.TreeNode[] {
            varName});
            className = new System.Windows.Forms.TreeNode("");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("Python类名", new System.Windows.Forms.TreeNode[] {
            className});
            velocity = new System.Windows.Forms.TreeNode("1.0");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("发射速度", new System.Windows.Forms.TreeNode[] {
            velocity});
            acceleration = new System.Windows.Forms.TreeNode("0.0");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("加速度", new System.Windows.Forms.TreeNode[] {
            acceleration});
            angle = new System.Windows.Forms.TreeNode("270.0");
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("发射角度(角度值)", new System.Windows.Forms.TreeNode[] {
            angle});
            angleVelocity = new System.Windows.Forms.TreeNode("0.0");
            System.Windows.Forms.TreeNode treeNode12 = new System.Windows.Forms.TreeNode("角速度", new System.Windows.Forms.TreeNode[] {
            angleVelocity});
            aimToPlayer = new System.Windows.Forms.TreeNode("False");
            System.Windows.Forms.TreeNode treeNode14 = new System.Windows.Forms.TreeNode("自机狙", new System.Windows.Forms.TreeNode[] {
            aimToPlayer});
            color = new TreeNode("BLUE");
            System.Windows.Forms.TreeNode treeNode15 = new System.Windows.Forms.TreeNode("弹幕颜色", new System.Windows.Forms.TreeNode[] {
            color});

            reBound = new TreeNode("0");
            System.Windows.Forms.TreeNode treeNode16 = new System.Windows.Forms.TreeNode("反弹次数", new System.Windows.Forms.TreeNode[] {
            reBound});

            posX = new TreeNode("0.0");
            System.Windows.Forms.TreeNode treeNode17 = new System.Windows.Forms.TreeNode("X", new System.Windows.Forms.TreeNode[] {
            posX});

            posY = new TreeNode("0.0");
            System.Windows.Forms.TreeNode treeNode18 = new System.Windows.Forms.TreeNode("Y", new System.Windows.Forms.TreeNode[] {
            posY});

            varName.Name = "varName";
            varName.Text = "testBullet0";
            treeNode2.Name = "节点1";
            treeNode2.Text = "变量名称";
            className.Name = "className";
            className.Text = "";
            treeNode4.Name = "节点7";
            treeNode4.Text = "Python类名";
            velocity.Name = "velocity";
            velocity.Text = "1.0";
            treeNode6.Name = "节点2";
            treeNode6.Text = "发射速度";
            acceleration.Name = "acceleration";
            acceleration.Text = "0.0";
            treeNode8.Name = "节点3";
            treeNode8.Text = "加速度";
            angle.Name = "angle";
            angle.Text = "270.0";
            treeNode10.Name = "节点4";
            treeNode10.Text = "发射角度(角度值)";
            angleVelocity.Name = "angleVelocity";
            angleVelocity.Text = "0.0";
            treeNode12.Name = "节点5";
            treeNode12.Text = "角速度";
            aimToPlayer.Name = "aimToPlayer";
            aimToPlayer.Text = "False";
            treeNode14.Name = "节点6";
            treeNode14.Text = "自机狙";
            color.Name = "color";
            color.Text = "BLUE";
            treeNode15.Name = "节点7";
            treeNode15.Text = "颜色";

            reBound.Name = "reBound";
            reBound.Text = "0";
            treeNode16.Name = "节点8";
            treeNode16.Text = "反弹次数";

            posX.Name = "posX";
            posX.Text = "0.0";
            treeNode17.Name = "节点9";
            treeNode17.Text = "X";

            posY.Name = "posY";
            posY.Text = "0.0";
            treeNode18.Name = "节点10";
            treeNode18.Text = "Y";
            this.BulletAttributeTree.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode2,
            treeNode4,
            treeNode6,
            treeNode8,
            treeNode10,
            treeNode12,
            treeNode14,
            treeNode15,
            treeNode16,
            treeNode17,
            treeNode18 });
        }
    }
}
