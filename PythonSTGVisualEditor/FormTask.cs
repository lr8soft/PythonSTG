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
    }
}
