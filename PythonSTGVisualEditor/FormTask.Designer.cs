namespace PythonSTGVisualEditor
{
    partial class FormTask
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("testTask");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("Task变量名", new System.Windows.Forms.TreeNode[] {
            treeNode1});
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("-1");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("持续帧数(-1永久持续)", new System.Windows.Forms.TreeNode[] {
            treeNode3});
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("0");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("间隔帧数", new System.Windows.Forms.TreeNode[] {
            treeNode5});
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("300");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("等待帧数", new System.Windows.Forms.TreeNode[] {
            treeNode7});
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("testTask1");
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("等待目标变量", new System.Windows.Forms.TreeNode[] {
            treeNode9});
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormTask));
            this.TaskAttributeTree = new System.Windows.Forms.TreeView();
            this.SuspendLayout();
            // 
            // TaskAttributeTree
            // 
            this.TaskAttributeTree.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TaskAttributeTree.Location = new System.Drawing.Point(0, 0);
            this.TaskAttributeTree.Name = "TaskAttributeTree";
            treeNode1.Name = "varName";
            treeNode1.Text = "testTask";
            treeNode2.Name = "TaskName";
            treeNode2.Text = "Task变量名";
            treeNode3.Name = "duration";
            treeNode3.Text = "-1";
            treeNode4.Name = "TaskDuration";
            treeNode4.Text = "持续帧数(-1永久持续)";
            treeNode5.Name = "interval";
            treeNode5.Text = "0";
            treeNode6.Name = "TaskInterval";
            treeNode6.Text = "间隔帧数";
            treeNode7.Name = "waitFrame";
            treeNode7.Text = "300";
            treeNode8.Name = "TaskWaitFrame";
            treeNode8.Text = "等待帧数";
            treeNode9.Name = "targetVar";
            treeNode9.Text = "testTask1";
            treeNode10.Name = "TaskTarget";
            treeNode10.Text = "等待目标变量";
            this.TaskAttributeTree.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode2,
            treeNode4,
            treeNode6,
            treeNode8,
            treeNode10});
            this.TaskAttributeTree.Size = new System.Drawing.Size(500, 403);
            this.TaskAttributeTree.TabIndex = 0;
            this.TaskAttributeTree.DoubleClick += new System.EventHandler(this.TaskAttributeTree_DoubleClick);
            // 
            // FormTask
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(500, 403);
            this.Controls.Add(this.TaskAttributeTree);
            this.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "FormTask";
            this.Text = "Task configurator";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TreeView TaskAttributeTree;
    }
}