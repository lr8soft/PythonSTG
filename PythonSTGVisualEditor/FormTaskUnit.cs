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
    public partial class FormTaskUnit : Form
    {
        public DialogResult Result { get; set; }
        private TaskUnit currentUnit;

        private static long unitCount = 0;
        public FormTaskUnit()
        {
            InitializeComponent();
            InitCustomizedComponent();

            currentUnit = new TaskUnit();
            currentUnit.unitVarName = "unit" + (unitCount++);
            currentUnit.waitFrame = 0;
            currentUnit.repeatTime = 1;
        }

        public FormTaskUnit(TaskUnit unit)
        {
            InitializeComponent();
            InitCustomizedComponent();
            currentUnit = (TaskUnit)unit.Clone();

            varName.Text = currentUnit.unitVarName;
            repeatTime.Text = currentUnit.repeatTime.ToString();
            waitFrame.Text = currentUnit.waitFrame.ToString();
        }

        private void btnSubmit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        public static TaskUnit Execute()
        {
            using (var form = new FormTaskUnit())
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK)
                {
                    return form.currentUnit;
                }
                else
                {
                    return null;
                }
            }
        }

        public static TaskUnit Execute(TaskUnit unit)
        {
            using (var form = new FormTaskUnit(unit))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK)
                {
                    Console.WriteLine(form.currentUnit.unitVarName);
                    return form.currentUnit;
                }
                else
                {
                    return null;
                }
            }
        }

        private void UnitAttributeTree_DoubleClick(object sender, EventArgs e)
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
                    updateTaskInfo(node.Parent.Name, lastValue, value);
                }
            }
        }

        private void updateTaskInfo(string rootName, string lastValue, string value)
        {
            TreeView treeView = UnitAttributeTree;
            switch (rootName)
            {
                case "UnitName":
                    currentUnit.unitVarName = value;
                    break;
                case "UnitRepeatTime":
                    currentUnit.repeatTime = int.Parse(value);
                    break;
                case "UnitWaitFrame":
                    currentUnit.waitFrame = int.Parse(value);
                    break;
            }
        }

        private System.Windows.Forms.TreeNode varName;
        private System.Windows.Forms.TreeNode repeatTime;
        private System.Windows.Forms.TreeNode waitFrame;
        private void InitCustomizedComponent()
        {
            varName = new System.Windows.Forms.TreeNode("unit1");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("TaskUnit变量名", new System.Windows.Forms.TreeNode[] {
            varName});
            repeatTime = new System.Windows.Forms.TreeNode("1");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("循环次数", new System.Windows.Forms.TreeNode[] {
            repeatTime});
            waitFrame = new System.Windows.Forms.TreeNode("0");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("等待帧数", new System.Windows.Forms.TreeNode[] {
            waitFrame});

            varName.Name = "varName";
            varName.Text = "taskunit1";
            treeNode2.Name = "UnitName";
            treeNode2.Text = "TaskUnit变量名";
            repeatTime.Name = "repeatTime";
            repeatTime.Text = "1";
            treeNode4.Name = "UnitRepeatTime";
            treeNode4.Text = "循环次数";
            waitFrame.Name = "waitFrame";
            waitFrame.Text = "0";
            treeNode6.Name = "UnitWaitFrame";
            treeNode6.Text = "等待帧数";
            this.UnitAttributeTree.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode2,
            treeNode4,
            treeNode6});

        }
    }
}
