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
        private Task currentTask;
        public FormTask(Task task)
        {
            InitializeComponent();
            currentTask = task;
        }

        public FormTask()
        {
            InitializeComponent();
            currentTask = new Task();
        }

        private void updateTaskInfo(string rootName, string value) {
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
                string value = Interaction.InputBox("输入值:","Input value", currentValue);
                if (value.Length > 0) {
                    node.Text = value;
                    updateTaskInfo(node.Parent.Name, value);
                }
            }
        }

        public Task GetTask() {
            return currentTask;
        }
    }
}
