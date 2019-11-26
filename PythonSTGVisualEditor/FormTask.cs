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
    public partial class FormTask : Form
    {
        public DialogResult Result { get; set; }
        public Task TaskResult { get; set; }

        private Task currentTask;
        public FormTask(Task task)
        {
            InitializeComponent();
            InitCustomizedComponent();

            currentTask = (Task)task.Clone();

            varNameNode.Text = currentTask.taskVarName;
            durationNode.Text = currentTask.taskDuration.ToString();
            intervalNode.Text = currentTask.taskInterval.ToString();
            waitframeNode.Text = currentTask.taskWaitFrame.ToString();

            foreach (string varName in task.targetVarName) {
                targetNodeParent.Nodes.AddRange(new TreeNode[] {
                new TreeNode(varName)});
            }
        }

        public FormTask()
        {
            InitializeComponent();
            InitCustomizedComponent();

            currentTask = new Task();
            currentTask.taskVarName = "task1";
            currentTask.taskDuration = -1;
            currentTask.taskInterval = 0;
            currentTask.taskWaitFrame = 0;
        }

        private void updateTaskInfo(string rootName, string lastValue, string value) {
            TreeView treeView = TaskAttributeTree;
            switch (rootName) {
                case "TaskName":
                    currentTask.taskVarName = value;
                    break;
                case "TaskDuration":
                    currentTask.taskDuration = int.Parse(value);
                    break;
                case "TaskInterval":
                    currentTask.taskInterval = int.Parse(value);
                    break;
                case "TaskWaitFrame":
                    currentTask.taskWaitFrame = int.Parse(value);
                    break;
                case "TaskTarget":
                    currentTask.targetVarName.Remove(lastValue);
                    currentTask.targetVarName.Add(value);
                    break;

            }
        }

        private void TaskAttributeTree_DoubleClick(object sender, EventArgs e)
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
            else {
                if (node.Name == "TaskTarget")
                {
                    string value = Interaction.InputBox("输入值:", "Input value");
                    if (value.Length > 0) {
                        node.Nodes.AddRange(new TreeNode[] { new TreeNode(value) });
                        updateTaskInfo(node.Name, null, value);
                    }
                }
            }
        }

        public Task GetTask() {
            return currentTask;
        }

        private void btnSubmit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        public static Task Execute()
        {
            using (var form = new FormTask())
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK)
                {
                    return form.currentTask;
                }
                else
                {
                    return null;
                }
            }
        }

        public static Task Execute(Task task)
        {
            using (var form = new FormTask(task))
            {
                var result = form.ShowDialog();
                if (result == DialogResult.OK)
                {
                    return form.currentTask;
                }
                else
                {
                    return null;
                }
            }
        }



        private TreeNode varNameNode;
        private System.Windows.Forms.TreeNode durationNode;
        private System.Windows.Forms.TreeNode intervalNode;
        private System.Windows.Forms.TreeNode waitframeNode;
        private System.Windows.Forms.TreeNode targetNodeParent;
        private void InitCustomizedComponent() {
            varNameNode = new System.Windows.Forms.TreeNode("task1");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Task变量名", new System.Windows.Forms.TreeNode[] {
            varNameNode});
            durationNode = new System.Windows.Forms.TreeNode("-1");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("持续帧数(-1永久持续)", new System.Windows.Forms.TreeNode[] {
            durationNode});
            intervalNode = new System.Windows.Forms.TreeNode("0");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("间隔帧数", new System.Windows.Forms.TreeNode[] {
            intervalNode});
            waitframeNode = new System.Windows.Forms.TreeNode("0");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("等待帧数", new System.Windows.Forms.TreeNode[] {
            waitframeNode});
            targetNodeParent = new System.Windows.Forms.TreeNode("等待目标变量");

            varNameNode.Name = "varName";
            varNameNode.Text = "task1";
            treeNode2.Name = "TaskName";
            treeNode2.Text = "Task变量名";
            durationNode.Name = "duration";
            durationNode.Text = "-1";
            treeNode4.Name = "TaskDuration";
            treeNode4.Text = "持续帧数(-1永久持续)";
            intervalNode.Name = "interval";
            intervalNode.Text = "0";
            treeNode6.Name = "TaskInterval";
            treeNode6.Text = "间隔帧数";
            waitframeNode.Name = "waitFrame";
            waitframeNode.Text = "0";
            treeNode8.Name = "TaskWaitFrame";
            treeNode8.Text = "等待帧数";
            targetNodeParent.Name = "TaskTarget";
            targetNodeParent.Text = "等待目标变量";
            this.TaskAttributeTree.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode2,
            treeNode4,
            treeNode6,
            treeNode8,
            targetNodeParent});
        }
    }
}
