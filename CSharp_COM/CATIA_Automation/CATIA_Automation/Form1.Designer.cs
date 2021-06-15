namespace CATIA_Automation
{
    partial class FormSelect
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
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.textBoxSelect = new System.Windows.Forms.TextBox();
            this.buttonSelect = new System.Windows.Forms.Button();
            this.buttonInitCatia = new System.Windows.Forms.Button();
            this.buttonRename = new System.Windows.Forms.Button();
            this.buttonCreatePoint = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textBoxSelect
            // 
            this.textBoxSelect.Location = new System.Drawing.Point(12, 51);
            this.textBoxSelect.Name = "textBoxSelect";
            this.textBoxSelect.Size = new System.Drawing.Size(229, 21);
            this.textBoxSelect.TabIndex = 0;
            this.textBoxSelect.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // buttonSelect
            // 
            this.buttonSelect.Location = new System.Drawing.Point(247, 49);
            this.buttonSelect.Name = "buttonSelect";
            this.buttonSelect.Size = new System.Drawing.Size(25, 23);
            this.buttonSelect.TabIndex = 1;
            this.buttonSelect.Text = "...";
            this.buttonSelect.UseVisualStyleBackColor = true;
            this.buttonSelect.Click += new System.EventHandler(this.buttonSelect_Click);
            // 
            // buttonInitCatia
            // 
            this.buttonInitCatia.Location = new System.Drawing.Point(197, 227);
            this.buttonInitCatia.Name = "buttonInitCatia";
            this.buttonInitCatia.Size = new System.Drawing.Size(75, 23);
            this.buttonInitCatia.TabIndex = 2;
            this.buttonInitCatia.Text = "Launch";
            this.buttonInitCatia.UseVisualStyleBackColor = true;
            this.buttonInitCatia.Click += new System.EventHandler(this.buttonInitCatia_Click);
            // 
            // buttonRename
            // 
            this.buttonRename.Location = new System.Drawing.Point(197, 195);
            this.buttonRename.Name = "buttonRename";
            this.buttonRename.Size = new System.Drawing.Size(75, 23);
            this.buttonRename.TabIndex = 3;
            this.buttonRename.Text = "Rename";
            this.buttonRename.UseVisualStyleBackColor = true;
            this.buttonRename.Click += new System.EventHandler(this.buttonRename_Click);
            // 
            // buttonCreatePoint
            // 
            this.buttonCreatePoint.Location = new System.Drawing.Point(197, 160);
            this.buttonCreatePoint.Name = "buttonCreatePoint";
            this.buttonCreatePoint.Size = new System.Drawing.Size(75, 23);
            this.buttonCreatePoint.TabIndex = 4;
            this.buttonCreatePoint.Text = "Create Points";
            this.buttonCreatePoint.UseVisualStyleBackColor = true;
            this.buttonCreatePoint.Click += new System.EventHandler(this.buttonCreatePoint_Click);
            // 
            // FormSelect
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.buttonCreatePoint);
            this.Controls.Add(this.buttonRename);
            this.Controls.Add(this.buttonInitCatia);
            this.Controls.Add(this.buttonSelect);
            this.Controls.Add(this.textBoxSelect);
            this.Name = "FormSelect";
            this.Text = "Test";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxSelect;
        private System.Windows.Forms.Button buttonSelect;
        private System.Windows.Forms.Button buttonInitCatia;
        private System.Windows.Forms.Button buttonRename;
        private System.Windows.Forms.Button buttonCreatePoint;
    }
}

