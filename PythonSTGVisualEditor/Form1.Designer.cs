using System;

namespace PythonSTGVisualEditor
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Task");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("TaskType", new System.Windows.Forms.TreeNode[] {
            treeNode1});
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("CircleBullet");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("OvalBullet");
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("RiceBullet");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("CardBullet");
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("BulletType", new System.Windows.Forms.TreeNode[] {
            treeNode3,
            treeNode4,
            treeNode5,
            treeNode6});
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("FairyEnemy");
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("ButterflyFairyEnemy");
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("EnemyType", new System.Windows.Forms.TreeNode[] {
            treeNode8,
            treeNode9});
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("Stage Group");
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileFToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打开OToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.保存SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.另存为AToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.退出XToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.编辑EToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.撤销UToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.重做RToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.剪切TToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.复制CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.粘贴PToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.删除XToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.测试SToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.运行RToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.带控制台运行CToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.帮助HToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.检查更新UToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关于AToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mainContainer = new System.Windows.Forms.SplitContainer();
            this.toolContainer = new System.Windows.Forms.SplitContainer();
            this.ComponentTree = new System.Windows.Forms.TreeView();
            this.AttributeBox = new System.Windows.Forms.GroupBox();
            this.AttributeList = new System.Windows.Forms.ListView();
            this.scriptContext = new System.Windows.Forms.TreeView();
            this.menuStrip1.SuspendLayout();
            this.mainContainer.Panel1.SuspendLayout();
            this.mainContainer.Panel2.SuspendLayout();
            this.mainContainer.SuspendLayout();
            this.toolContainer.Panel1.SuspendLayout();
            this.toolContainer.Panel2.SuspendLayout();
            this.toolContainer.SuspendLayout();
            this.AttributeBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileFToolStripMenuItem,
            this.编辑EToolStripMenuItem,
            this.测试SToolStripMenuItem,
            this.帮助HToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(834, 28);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileFToolStripMenuItem
            // 
            this.fileFToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.打开OToolStripMenuItem,
            this.保存SToolStripMenuItem,
            this.另存为AToolStripMenuItem,
            this.toolStripMenuItem1,
            this.退出XToolStripMenuItem});
            this.fileFToolStripMenuItem.Name = "fileFToolStripMenuItem";
            this.fileFToolStripMenuItem.Size = new System.Drawing.Size(69, 24);
            this.fileFToolStripMenuItem.Text = "文件(F)";
            this.fileFToolStripMenuItem.Click += new System.EventHandler(this.fileFToolStripMenuItem_Click);
            // 
            // 打开OToolStripMenuItem
            // 
            this.打开OToolStripMenuItem.Name = "打开OToolStripMenuItem";
            this.打开OToolStripMenuItem.Size = new System.Drawing.Size(150, 26);
            this.打开OToolStripMenuItem.Text = "打开(O)";
            // 
            // 保存SToolStripMenuItem
            // 
            this.保存SToolStripMenuItem.Name = "保存SToolStripMenuItem";
            this.保存SToolStripMenuItem.Size = new System.Drawing.Size(150, 26);
            this.保存SToolStripMenuItem.Text = "保存(S)";
            // 
            // 另存为AToolStripMenuItem
            // 
            this.另存为AToolStripMenuItem.Name = "另存为AToolStripMenuItem";
            this.另存为AToolStripMenuItem.Size = new System.Drawing.Size(150, 26);
            this.另存为AToolStripMenuItem.Text = "另存为(A)";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(147, 6);
            // 
            // 退出XToolStripMenuItem
            // 
            this.退出XToolStripMenuItem.Name = "退出XToolStripMenuItem";
            this.退出XToolStripMenuItem.Size = new System.Drawing.Size(150, 26);
            this.退出XToolStripMenuItem.Text = "退出(X)";
            this.退出XToolStripMenuItem.Click += new System.EventHandler(this.退出XToolStripMenuItem_Click);
            // 
            // 编辑EToolStripMenuItem
            // 
            this.编辑EToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.撤销UToolStripMenuItem,
            this.重做RToolStripMenuItem,
            this.toolStripMenuItem2,
            this.剪切TToolStripMenuItem,
            this.复制CToolStripMenuItem,
            this.粘贴PToolStripMenuItem,
            this.删除XToolStripMenuItem});
            this.编辑EToolStripMenuItem.Name = "编辑EToolStripMenuItem";
            this.编辑EToolStripMenuItem.Size = new System.Drawing.Size(69, 24);
            this.编辑EToolStripMenuItem.Text = "编辑(E)";
            // 
            // 撤销UToolStripMenuItem
            // 
            this.撤销UToolStripMenuItem.Name = "撤销UToolStripMenuItem";
            this.撤销UToolStripMenuItem.Size = new System.Drawing.Size(135, 26);
            this.撤销UToolStripMenuItem.Text = "撤销(U)";
            // 
            // 重做RToolStripMenuItem
            // 
            this.重做RToolStripMenuItem.Name = "重做RToolStripMenuItem";
            this.重做RToolStripMenuItem.Size = new System.Drawing.Size(135, 26);
            this.重做RToolStripMenuItem.Text = "重做(R)";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(132, 6);
            // 
            // 剪切TToolStripMenuItem
            // 
            this.剪切TToolStripMenuItem.Name = "剪切TToolStripMenuItem";
            this.剪切TToolStripMenuItem.Size = new System.Drawing.Size(135, 26);
            this.剪切TToolStripMenuItem.Text = "剪切(T)";
            // 
            // 复制CToolStripMenuItem
            // 
            this.复制CToolStripMenuItem.Name = "复制CToolStripMenuItem";
            this.复制CToolStripMenuItem.Size = new System.Drawing.Size(135, 26);
            this.复制CToolStripMenuItem.Text = "复制(C)";
            // 
            // 粘贴PToolStripMenuItem
            // 
            this.粘贴PToolStripMenuItem.Name = "粘贴PToolStripMenuItem";
            this.粘贴PToolStripMenuItem.Size = new System.Drawing.Size(135, 26);
            this.粘贴PToolStripMenuItem.Text = "粘贴(P)";
            // 
            // 删除XToolStripMenuItem
            // 
            this.删除XToolStripMenuItem.Name = "删除XToolStripMenuItem";
            this.删除XToolStripMenuItem.Size = new System.Drawing.Size(135, 26);
            this.删除XToolStripMenuItem.Text = "删除(D)";
            // 
            // 测试SToolStripMenuItem
            // 
            this.测试SToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.运行RToolStripMenuItem,
            this.带控制台运行CToolStripMenuItem});
            this.测试SToolStripMenuItem.Name = "测试SToolStripMenuItem";
            this.测试SToolStripMenuItem.Size = new System.Drawing.Size(70, 24);
            this.测试SToolStripMenuItem.Text = "测试(S)";
            // 
            // 运行RToolStripMenuItem
            // 
            this.运行RToolStripMenuItem.Name = "运行RToolStripMenuItem";
            this.运行RToolStripMenuItem.Size = new System.Drawing.Size(194, 26);
            this.运行RToolStripMenuItem.Text = "运行(R)";
            // 
            // 带控制台运行CToolStripMenuItem
            // 
            this.带控制台运行CToolStripMenuItem.Name = "带控制台运行CToolStripMenuItem";
            this.带控制台运行CToolStripMenuItem.Size = new System.Drawing.Size(194, 26);
            this.带控制台运行CToolStripMenuItem.Text = "带控制台运行(C)";
            // 
            // 帮助HToolStripMenuItem
            // 
            this.帮助HToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.检查更新UToolStripMenuItem,
            this.关于AToolStripMenuItem});
            this.帮助HToolStripMenuItem.Name = "帮助HToolStripMenuItem";
            this.帮助HToolStripMenuItem.Size = new System.Drawing.Size(73, 24);
            this.帮助HToolStripMenuItem.Text = "帮助(H)";
            // 
            // 检查更新UToolStripMenuItem
            // 
            this.检查更新UToolStripMenuItem.Name = "检查更新UToolStripMenuItem";
            this.检查更新UToolStripMenuItem.Size = new System.Drawing.Size(165, 26);
            this.检查更新UToolStripMenuItem.Text = "检查更新(U)";
            // 
            // 关于AToolStripMenuItem
            // 
            this.关于AToolStripMenuItem.Name = "关于AToolStripMenuItem";
            this.关于AToolStripMenuItem.Size = new System.Drawing.Size(165, 26);
            this.关于AToolStripMenuItem.Text = "关于(A)";
            // 
            // mainContainer
            // 
            this.mainContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainContainer.Location = new System.Drawing.Point(0, 28);
            this.mainContainer.Name = "mainContainer";
            // 
            // mainContainer.Panel1
            // 
            this.mainContainer.Panel1.Controls.Add(this.toolContainer);
            // 
            // mainContainer.Panel2
            // 
            this.mainContainer.Panel2.Controls.Add(this.scriptContext);
            this.mainContainer.Size = new System.Drawing.Size(834, 472);
            this.mainContainer.SplitterDistance = 200;
            this.mainContainer.TabIndex = 2;
            // 
            // toolContainer
            // 
            this.toolContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolContainer.Location = new System.Drawing.Point(0, 0);
            this.toolContainer.Name = "toolContainer";
            this.toolContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // toolContainer.Panel1
            // 
            this.toolContainer.Panel1.Controls.Add(this.ComponentTree);
            // 
            // toolContainer.Panel2
            // 
            this.toolContainer.Panel2.Controls.Add(this.AttributeBox);
            this.toolContainer.Size = new System.Drawing.Size(200, 472);
            this.toolContainer.SplitterDistance = 250;
            this.toolContainer.TabIndex = 0;
            // 
            // ComponentTree
            // 
            this.ComponentTree.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ComponentTree.Location = new System.Drawing.Point(0, 0);
            this.ComponentTree.Name = "ComponentTree";
            treeNode1.Name = "TaskNode";
            treeNode1.Text = "Task";
            treeNode2.Name = "TaskRoot";
            treeNode2.Text = "TaskType";
            treeNode3.Name = "CircleBulletNode";
            treeNode3.Text = "CircleBullet";
            treeNode4.Name = "OvalBulletNode";
            treeNode4.Text = "OvalBullet";
            treeNode5.Name = "RiceBulletNode";
            treeNode5.Text = "RiceBullet";
            treeNode6.Name = "CardBulletNode";
            treeNode6.Text = "CardBullet";
            treeNode7.Name = "BulletNodeRoot";
            treeNode7.Text = "BulletType";
            treeNode8.Name = "FairyEnemyNode";
            treeNode8.Text = "FairyEnemy";
            treeNode9.Name = "ButterflyFairyEnemyNode";
            treeNode9.Text = "ButterflyFairyEnemy";
            treeNode10.Name = "EnemyTypeRoot";
            treeNode10.Text = "EnemyType";
            this.ComponentTree.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode2,
            treeNode7,
            treeNode10});
            this.ComponentTree.Size = new System.Drawing.Size(200, 250);
            this.ComponentTree.TabIndex = 0;
            this.ComponentTree.DoubleClick += new System.EventHandler(this.ComponentTree_DoubleClick);
            // 
            // AttributeBox
            // 
            this.AttributeBox.Controls.Add(this.AttributeList);
            this.AttributeBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AttributeBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.AttributeBox.Location = new System.Drawing.Point(0, 0);
            this.AttributeBox.Name = "AttributeBox";
            this.AttributeBox.Size = new System.Drawing.Size(200, 218);
            this.AttributeBox.TabIndex = 0;
            this.AttributeBox.TabStop = false;
            this.AttributeBox.Text = "属性";
            // 
            // AttributeList
            // 
            this.AttributeList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AttributeList.HideSelection = false;
            this.AttributeList.Location = new System.Drawing.Point(3, 21);
            this.AttributeList.Name = "AttributeList";
            this.AttributeList.Size = new System.Drawing.Size(194, 194);
            this.AttributeList.TabIndex = 0;
            this.AttributeList.UseCompatibleStateImageBehavior = false;
            // 
            // scriptContext
            // 
            this.scriptContext.Dock = System.Windows.Forms.DockStyle.Fill;
            this.scriptContext.Location = new System.Drawing.Point(0, 0);
            this.scriptContext.Margin = new System.Windows.Forms.Padding(30);
            this.scriptContext.Name = "scriptContext";
            treeNode11.Name = "StageGroupRoot";
            treeNode11.Text = "Stage Group";
            this.scriptContext.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode11});
            this.scriptContext.Size = new System.Drawing.Size(630, 472);
            this.scriptContext.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(834, 500);
            this.Controls.Add(this.mainContainer);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "PySTG VisualEditor";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.mainContainer.Panel1.ResumeLayout(false);
            this.mainContainer.Panel2.ResumeLayout(false);
            this.mainContainer.ResumeLayout(false);
            this.toolContainer.Panel1.ResumeLayout(false);
            this.toolContainer.Panel2.ResumeLayout(false);
            this.toolContainer.ResumeLayout(false);
            this.AttributeBox.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileFToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 打开OToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 保存SToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 另存为AToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 退出XToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 编辑EToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 测试SToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 帮助HToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 撤销UToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 重做RToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem 剪切TToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 复制CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 粘贴PToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 删除XToolStripMenuItem;
        private System.Windows.Forms.SplitContainer mainContainer;
        private System.Windows.Forms.TreeView scriptContext;
        private System.Windows.Forms.SplitContainer toolContainer;
        private System.Windows.Forms.GroupBox AttributeBox;
        private System.Windows.Forms.TreeView ComponentTree;
        private System.Windows.Forms.ListView AttributeList;
        private System.Windows.Forms.ToolStripMenuItem 运行RToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 带控制台运行CToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 检查更新UToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关于AToolStripMenuItem;
    }
}

