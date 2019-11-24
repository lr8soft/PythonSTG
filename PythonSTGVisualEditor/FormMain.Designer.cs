using System;

namespace PythonSTGVisualEditor
{
    partial class FormMain
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
            System.Windows.Forms.TreeNode treeNode1 = new System.Windows.Forms.TreeNode("Stage");
            System.Windows.Forms.TreeNode treeNode2 = new System.Windows.Forms.TreeNode("StageType", new System.Windows.Forms.TreeNode[] {
            treeNode1});
            System.Windows.Forms.TreeNode treeNode3 = new System.Windows.Forms.TreeNode("Task");
            System.Windows.Forms.TreeNode treeNode4 = new System.Windows.Forms.TreeNode("TaskType", new System.Windows.Forms.TreeNode[] {
            treeNode3});
            System.Windows.Forms.TreeNode treeNode5 = new System.Windows.Forms.TreeNode("CircleBullet");
            System.Windows.Forms.TreeNode treeNode6 = new System.Windows.Forms.TreeNode("OvalBullet");
            System.Windows.Forms.TreeNode treeNode7 = new System.Windows.Forms.TreeNode("RiceBullet");
            System.Windows.Forms.TreeNode treeNode8 = new System.Windows.Forms.TreeNode("CardBullet");
            System.Windows.Forms.TreeNode treeNode9 = new System.Windows.Forms.TreeNode("HugeBullet");
            System.Windows.Forms.TreeNode treeNode10 = new System.Windows.Forms.TreeNode("BulletType", new System.Windows.Forms.TreeNode[] {
            treeNode5,
            treeNode6,
            treeNode7,
            treeNode8,
            treeNode9});
            System.Windows.Forms.TreeNode treeNode11 = new System.Windows.Forms.TreeNode("FairyEnemy");
            System.Windows.Forms.TreeNode treeNode12 = new System.Windows.Forms.TreeNode("ButterflyFairyEnemy");
            System.Windows.Forms.TreeNode treeNode13 = new System.Windows.Forms.TreeNode("EnemyType", new System.Windows.Forms.TreeNode[] {
            treeNode11,
            treeNode12});
            System.Windows.Forms.TreeNode treeNode14 = new System.Windows.Forms.TreeNode("Stage Group");
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
            this.menuGroup = new System.Windows.Forms.MenuStrip();
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
            this.生成Python脚本GToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.menuGroup.SuspendLayout();
            this.mainContainer.Panel1.SuspendLayout();
            this.mainContainer.Panel2.SuspendLayout();
            this.mainContainer.SuspendLayout();
            this.toolContainer.Panel1.SuspendLayout();
            this.toolContainer.Panel2.SuspendLayout();
            this.toolContainer.SuspendLayout();
            this.AttributeBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuGroup
            // 
            this.menuGroup.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.menuGroup.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuGroup.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileFToolStripMenuItem,
            this.编辑EToolStripMenuItem,
            this.测试SToolStripMenuItem,
            this.帮助HToolStripMenuItem});
            this.menuGroup.Location = new System.Drawing.Point(0, 0);
            this.menuGroup.Name = "menuGroup";
            this.menuGroup.Padding = new System.Windows.Forms.Padding(7, 3, 0, 3);
            this.menuGroup.Size = new System.Drawing.Size(873, 30);
            this.menuGroup.TabIndex = 1;
            this.menuGroup.Text = "menuStrip1";
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
            this.打开OToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.打开OToolStripMenuItem.Text = "打开(O)";
            // 
            // 保存SToolStripMenuItem
            // 
            this.保存SToolStripMenuItem.Name = "保存SToolStripMenuItem";
            this.保存SToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.保存SToolStripMenuItem.Text = "保存(S)";
            // 
            // 另存为AToolStripMenuItem
            // 
            this.另存为AToolStripMenuItem.Name = "另存为AToolStripMenuItem";
            this.另存为AToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.另存为AToolStripMenuItem.Text = "另存为(A)";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(213, 6);
            // 
            // 退出XToolStripMenuItem
            // 
            this.退出XToolStripMenuItem.Name = "退出XToolStripMenuItem";
            this.退出XToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
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
            this.撤销UToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.撤销UToolStripMenuItem.Text = "撤销(U)";
            // 
            // 重做RToolStripMenuItem
            // 
            this.重做RToolStripMenuItem.Name = "重做RToolStripMenuItem";
            this.重做RToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.重做RToolStripMenuItem.Text = "重做(R)";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(213, 6);
            // 
            // 剪切TToolStripMenuItem
            // 
            this.剪切TToolStripMenuItem.Name = "剪切TToolStripMenuItem";
            this.剪切TToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.剪切TToolStripMenuItem.Text = "剪切(T)";
            // 
            // 复制CToolStripMenuItem
            // 
            this.复制CToolStripMenuItem.Name = "复制CToolStripMenuItem";
            this.复制CToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.复制CToolStripMenuItem.Text = "复制(C)";
            // 
            // 粘贴PToolStripMenuItem
            // 
            this.粘贴PToolStripMenuItem.Name = "粘贴PToolStripMenuItem";
            this.粘贴PToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.粘贴PToolStripMenuItem.Text = "粘贴(P)";
            // 
            // 删除XToolStripMenuItem
            // 
            this.删除XToolStripMenuItem.Name = "删除XToolStripMenuItem";
            this.删除XToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.删除XToolStripMenuItem.Text = "删除(D)";
            // 
            // 测试SToolStripMenuItem
            // 
            this.测试SToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.运行RToolStripMenuItem,
            this.带控制台运行CToolStripMenuItem,
            this.toolStripMenuItem3,
            this.生成Python脚本GToolStripMenuItem});
            this.测试SToolStripMenuItem.Name = "测试SToolStripMenuItem";
            this.测试SToolStripMenuItem.Size = new System.Drawing.Size(70, 24);
            this.测试SToolStripMenuItem.Text = "测试(S)";
            // 
            // 运行RToolStripMenuItem
            // 
            this.运行RToolStripMenuItem.Name = "运行RToolStripMenuItem";
            this.运行RToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.运行RToolStripMenuItem.Text = "运行(R)";
            // 
            // 带控制台运行CToolStripMenuItem
            // 
            this.带控制台运行CToolStripMenuItem.Name = "带控制台运行CToolStripMenuItem";
            this.带控制台运行CToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
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
            this.检查更新UToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.检查更新UToolStripMenuItem.Text = "检查更新(U)";
            // 
            // 关于AToolStripMenuItem
            // 
            this.关于AToolStripMenuItem.Name = "关于AToolStripMenuItem";
            this.关于AToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.关于AToolStripMenuItem.Text = "关于(A)";
            // 
            // mainContainer
            // 
            this.mainContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainContainer.Location = new System.Drawing.Point(0, 30);
            this.mainContainer.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.mainContainer.Name = "mainContainer";
            // 
            // mainContainer.Panel1
            // 
            this.mainContainer.Panel1.Controls.Add(this.toolContainer);
            // 
            // mainContainer.Panel2
            // 
            this.mainContainer.Panel2.Controls.Add(this.scriptContext);
            this.mainContainer.Size = new System.Drawing.Size(873, 532);
            this.mainContainer.SplitterDistance = 209;
            this.mainContainer.TabIndex = 2;
            // 
            // toolContainer
            // 
            this.toolContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.toolContainer.Location = new System.Drawing.Point(0, 0);
            this.toolContainer.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
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
            this.toolContainer.Size = new System.Drawing.Size(209, 532);
            this.toolContainer.SplitterDistance = 281;
            this.toolContainer.SplitterWidth = 5;
            this.toolContainer.TabIndex = 0;
            // 
            // ComponentTree
            // 
            this.ComponentTree.Dock = System.Windows.Forms.DockStyle.Fill;
            this.ComponentTree.HideSelection = false;
            this.ComponentTree.Location = new System.Drawing.Point(0, 0);
            this.ComponentTree.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.ComponentTree.Name = "ComponentTree";
            treeNode1.Name = "StageNode";
            treeNode1.Text = "Stage";
            treeNode2.Name = "StageRoot";
            treeNode2.Text = "StageType";
            treeNode3.Name = "TaskNode";
            treeNode3.Text = "Task";
            treeNode4.Name = "TaskRoot";
            treeNode4.Text = "TaskType";
            treeNode5.Name = "CircleBulletNode";
            treeNode5.Text = "CircleBullet";
            treeNode6.Name = "OvalBulletNode";
            treeNode6.Text = "OvalBullet";
            treeNode7.Name = "RiceBulletNode";
            treeNode7.Text = "RiceBullet";
            treeNode8.Name = "CardBulletNode";
            treeNode8.Text = "CardBullet";
            treeNode9.Name = "HugeBulletNode";
            treeNode9.Text = "HugeBullet";
            treeNode10.Name = "BulletNodeRoot";
            treeNode10.Text = "BulletType";
            treeNode11.Name = "FairyEnemyNode";
            treeNode11.Text = "FairyEnemy";
            treeNode12.Name = "ButterflyFairyEnemyNode";
            treeNode12.Text = "ButterflyFairyEnemy";
            treeNode13.Name = "EnemyTypeRoot";
            treeNode13.Text = "EnemyType";
            this.ComponentTree.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode2,
            treeNode4,
            treeNode10,
            treeNode13});
            this.ComponentTree.Size = new System.Drawing.Size(209, 281);
            this.ComponentTree.TabIndex = 0;
            this.ComponentTree.DoubleClick += new System.EventHandler(this.ComponentTree_DoubleClick);
            // 
            // AttributeBox
            // 
            this.AttributeBox.Controls.Add(this.AttributeList);
            this.AttributeBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AttributeBox.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.AttributeBox.Location = new System.Drawing.Point(0, 0);
            this.AttributeBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.AttributeBox.Name = "AttributeBox";
            this.AttributeBox.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.AttributeBox.Size = new System.Drawing.Size(209, 246);
            this.AttributeBox.TabIndex = 0;
            this.AttributeBox.TabStop = false;
            this.AttributeBox.Text = "属性";
            // 
            // AttributeList
            // 
            this.AttributeList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.AttributeList.HideSelection = false;
            this.AttributeList.Location = new System.Drawing.Point(3, 24);
            this.AttributeList.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.AttributeList.Name = "AttributeList";
            this.AttributeList.Size = new System.Drawing.Size(203, 218);
            this.AttributeList.TabIndex = 0;
            this.AttributeList.UseCompatibleStateImageBehavior = false;
            // 
            // scriptContext
            // 
            this.scriptContext.Dock = System.Windows.Forms.DockStyle.Fill;
            this.scriptContext.HideSelection = false;
            this.scriptContext.Location = new System.Drawing.Point(0, 0);
            this.scriptContext.Margin = new System.Windows.Forms.Padding(34, 40, 34, 40);
            this.scriptContext.Name = "scriptContext";
            treeNode14.Name = "StageGroupRoot";
            treeNode14.Text = "Stage Group";
            this.scriptContext.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
            treeNode14});
            this.scriptContext.Size = new System.Drawing.Size(660, 532);
            this.scriptContext.TabIndex = 0;
            // 
            // 生成Python脚本GToolStripMenuItem
            // 
            this.生成Python脚本GToolStripMenuItem.Name = "生成Python脚本GToolStripMenuItem";
            this.生成Python脚本GToolStripMenuItem.Size = new System.Drawing.Size(216, 26);
            this.生成Python脚本GToolStripMenuItem.Text = "生成Python脚本(G)";
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(213, 6);
            // 
            // FormMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(873, 562);
            this.Controls.Add(this.mainContainer);
            this.Controls.Add(this.menuGroup);
            this.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuGroup;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "FormMain";
            this.Text = "PySTG VisualEditor";
            this.menuGroup.ResumeLayout(false);
            this.menuGroup.PerformLayout();
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
        private System.Windows.Forms.MenuStrip menuGroup;
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
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem 生成Python脚本GToolStripMenuItem;
    }
}

