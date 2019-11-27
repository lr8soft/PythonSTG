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

        private Task currentTask;
        private static long taskCount = 0;
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
            currentTask.taskVarName = "task" + (taskCount++);
            currentTask.taskDuration = -1;
            currentTask.taskInterval = 0;
            currentTask.taskWaitFrame = 0;
        }

        private void updateTaskInfo(string rootName, string lastValue, string value) {
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
        private TreeNode durationNode;
        private TreeNode intervalNode;
        private TreeNode waitframeNode;
        private TreeNode targetNodeParent;
        private void InitCustomizedComponent() {
            varNameNode = new TreeNode("task0");
            TreeNode treeNode2 = new TreeNode("Task变量名", new TreeNode[] {
            varNameNode});
            durationNode = new TreeNode("-1");
            TreeNode treeNode4 = new TreeNode("持续帧数(-1永久持续)", new TreeNode[] {
            durationNode});
            intervalNode = new TreeNode("0");
            TreeNode treeNode6 = new TreeNode("间隔帧数", new TreeNode[] {
            intervalNode});
            waitframeNode = new TreeNode("0");
            TreeNode treeNode8 = new TreeNode("等待帧数", new TreeNode[] {
            waitframeNode});
            targetNodeParent = new TreeNode("等待目标变量");

            varNameNode.Name = "varName";
            varNameNode.Text = "task0";
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
            this.TaskAttributeTree.Nodes.AddRange(new TreeNode[] {
            treeNode2,
            treeNode4,
            treeNode6,
            treeNode8,
            targetNodeParent});
        }
    }
}
