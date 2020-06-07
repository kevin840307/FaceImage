namespace GHWindows
{
    partial class Form1
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置 Managed 資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.pic_show = new System.Windows.Forms.PictureBox();
            this.btn_test = new System.Windows.Forms.Button();
            this.lab_test = new System.Windows.Forms.Label();
            this.btn_time = new System.Windows.Forms.Button();
            this.lab_time = new System.Windows.Forms.Label();
            this.btn_gray = new System.Windows.Forms.Button();
            this.btn_hsv_rgb = new System.Windows.Forms.Button();
            this.btn_rbg_hsv = new System.Windows.Forms.Button();
            this.btn_init = new System.Windows.Forms.Button();
            this.btn_gray_bw = new System.Windows.Forms.Button();
            this.btn_hsv_bw = new System.Windows.Forms.Button();
            this.btn_sobel = new System.Windows.Forms.Button();
            this.btn_expansion = new System.Windows.Forms.Button();
            this.btn_erosion = new System.Windows.Forms.Button();
            this.btn_exp_sub_ero = new System.Windows.Forms.Button();
            this.btn_blur = new System.Windows.Forms.Button();
            this.btn_ycbcr_rbg = new System.Windows.Forms.Button();
            this.btn_rbg_ycbcr = new System.Windows.Forms.Button();
            this.btn_ycbcr_bw = new System.Windows.Forms.Button();
            this.btn_ycbcr_c_face = new System.Windows.Forms.Button();
            this.btn_hsv_c_face = new System.Windows.Forms.Button();
            this.btn_haar = new System.Windows.Forms.Button();
            this.btn_contour_frame = new System.Windows.Forms.Button();
            this.btn_gamma = new System.Windows.Forms.Button();
            this.btnLBP = new System.Windows.Forms.Button();
            this.btnLBP2 = new System.Windows.Forms.Button();
            this.btnLBP3 = new System.Windows.Forms.Button();
            this.btnLBP4 = new System.Windows.Forms.Button();
            this.btnLBP5 = new System.Windows.Forms.Button();
            this.btn_contour = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pic_show)).BeginInit();
            this.SuspendLayout();
            // 
            // pic_show
            // 
            this.pic_show.Location = new System.Drawing.Point(12, 12);
            this.pic_show.Name = "pic_show";
            this.pic_show.Size = new System.Drawing.Size(450, 450);
            this.pic_show.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pic_show.TabIndex = 0;
            this.pic_show.TabStop = false;
            // 
            // btn_test
            // 
            this.btn_test.Location = new System.Drawing.Point(582, 12);
            this.btn_test.Name = "btn_test";
            this.btn_test.Size = new System.Drawing.Size(75, 23);
            this.btn_test.TabIndex = 1;
            this.btn_test.Text = "測試";
            this.btn_test.UseVisualStyleBackColor = true;
            this.btn_test.Click += new System.EventHandler(this.btn_test_Click);
            // 
            // lab_test
            // 
            this.lab_test.AutoSize = true;
            this.lab_test.Location = new System.Drawing.Point(611, 47);
            this.lab_test.Name = "lab_test";
            this.lab_test.Size = new System.Drawing.Size(37, 15);
            this.lab_test.TabIndex = 2;
            this.lab_test.Text = "測試";
            // 
            // btn_time
            // 
            this.btn_time.Location = new System.Drawing.Point(582, 112);
            this.btn_time.Name = "btn_time";
            this.btn_time.Size = new System.Drawing.Size(75, 25);
            this.btn_time.TabIndex = 3;
            this.btn_time.Text = "碼表計時";
            this.btn_time.UseVisualStyleBackColor = true;
            this.btn_time.Click += new System.EventHandler(this.btn_time_Click);
            // 
            // lab_time
            // 
            this.lab_time.AutoSize = true;
            this.lab_time.Location = new System.Drawing.Point(582, 144);
            this.lab_time.Name = "lab_time";
            this.lab_time.Size = new System.Drawing.Size(37, 15);
            this.lab_time.TabIndex = 4;
            this.lab_time.Text = "時間";
            // 
            // btn_gray
            // 
            this.btn_gray.Location = new System.Drawing.Point(680, 212);
            this.btn_gray.Name = "btn_gray";
            this.btn_gray.Size = new System.Drawing.Size(100, 35);
            this.btn_gray.TabIndex = 5;
            this.btn_gray.Text = "灰階";
            this.btn_gray.UseVisualStyleBackColor = true;
            this.btn_gray.Click += new System.EventHandler(this.btn_gray_Click);
            // 
            // btn_hsv_rgb
            // 
            this.btn_hsv_rgb.Location = new System.Drawing.Point(680, 253);
            this.btn_hsv_rgb.Name = "btn_hsv_rgb";
            this.btn_hsv_rgb.Size = new System.Drawing.Size(100, 35);
            this.btn_hsv_rgb.TabIndex = 6;
            this.btn_hsv_rgb.Text = "RGB轉HSV";
            this.btn_hsv_rgb.UseVisualStyleBackColor = true;
            this.btn_hsv_rgb.Click += new System.EventHandler(this.btn_hsv_Click);
            // 
            // btn_rbg_hsv
            // 
            this.btn_rbg_hsv.Location = new System.Drawing.Point(680, 294);
            this.btn_rbg_hsv.Name = "btn_rbg_hsv";
            this.btn_rbg_hsv.Size = new System.Drawing.Size(100, 35);
            this.btn_rbg_hsv.TabIndex = 7;
            this.btn_rbg_hsv.Text = "HSV轉RGB";
            this.btn_rbg_hsv.UseVisualStyleBackColor = true;
            this.btn_rbg_hsv.Click += new System.EventHandler(this.btn_rbg_Click);
            // 
            // btn_init
            // 
            this.btn_init.Location = new System.Drawing.Point(680, 171);
            this.btn_init.Name = "btn_init";
            this.btn_init.Size = new System.Drawing.Size(100, 35);
            this.btn_init.TabIndex = 8;
            this.btn_init.Text = "原圖";
            this.btn_init.UseVisualStyleBackColor = true;
            this.btn_init.Click += new System.EventHandler(this.btn_init_Click);
            // 
            // btn_gray_bw
            // 
            this.btn_gray_bw.Location = new System.Drawing.Point(680, 335);
            this.btn_gray_bw.Name = "btn_gray_bw";
            this.btn_gray_bw.Size = new System.Drawing.Size(100, 35);
            this.btn_gray_bw.TabIndex = 9;
            this.btn_gray_bw.Text = "灰階二值化";
            this.btn_gray_bw.UseVisualStyleBackColor = true;
            this.btn_gray_bw.Click += new System.EventHandler(this.btn_gray_bw_Click);
            // 
            // btn_hsv_bw
            // 
            this.btn_hsv_bw.Location = new System.Drawing.Point(680, 376);
            this.btn_hsv_bw.Name = "btn_hsv_bw";
            this.btn_hsv_bw.Size = new System.Drawing.Size(100, 35);
            this.btn_hsv_bw.TabIndex = 10;
            this.btn_hsv_bw.Text = "HSV二值化";
            this.btn_hsv_bw.UseVisualStyleBackColor = true;
            this.btn_hsv_bw.Click += new System.EventHandler(this.btn_hsv_bw_Click);
            // 
            // btn_sobel
            // 
            this.btn_sobel.Location = new System.Drawing.Point(680, 417);
            this.btn_sobel.Name = "btn_sobel";
            this.btn_sobel.Size = new System.Drawing.Size(100, 35);
            this.btn_sobel.TabIndex = 11;
            this.btn_sobel.Text = "邊緣檢測";
            this.btn_sobel.UseVisualStyleBackColor = true;
            this.btn_sobel.Click += new System.EventHandler(this.btn_sobel_Click);
            // 
            // btn_expansion
            // 
            this.btn_expansion.Location = new System.Drawing.Point(680, 458);
            this.btn_expansion.Name = "btn_expansion";
            this.btn_expansion.Size = new System.Drawing.Size(100, 35);
            this.btn_expansion.TabIndex = 12;
            this.btn_expansion.Text = "膨脹";
            this.btn_expansion.UseVisualStyleBackColor = true;
            this.btn_expansion.Click += new System.EventHandler(this.btn_expansion_Click);
            // 
            // btn_erosion
            // 
            this.btn_erosion.Location = new System.Drawing.Point(680, 499);
            this.btn_erosion.Name = "btn_erosion";
            this.btn_erosion.Size = new System.Drawing.Size(100, 35);
            this.btn_erosion.TabIndex = 13;
            this.btn_erosion.Text = "侵蝕";
            this.btn_erosion.UseVisualStyleBackColor = true;
            this.btn_erosion.Click += new System.EventHandler(this.btn_erosion_Click);
            // 
            // btn_exp_sub_ero
            // 
            this.btn_exp_sub_ero.Location = new System.Drawing.Point(680, 540);
            this.btn_exp_sub_ero.Name = "btn_exp_sub_ero";
            this.btn_exp_sub_ero.Size = new System.Drawing.Size(100, 35);
            this.btn_exp_sub_ero.TabIndex = 14;
            this.btn_exp_sub_ero.Text = "膨脹-侵蝕";
            this.btn_exp_sub_ero.UseVisualStyleBackColor = true;
            this.btn_exp_sub_ero.Click += new System.EventHandler(this.btn_exp_sub_ero_Click);
            // 
            // btn_blur
            // 
            this.btn_blur.Location = new System.Drawing.Point(680, 581);
            this.btn_blur.Name = "btn_blur";
            this.btn_blur.Size = new System.Drawing.Size(100, 35);
            this.btn_blur.TabIndex = 15;
            this.btn_blur.Text = "平滑";
            this.btn_blur.UseVisualStyleBackColor = true;
            this.btn_blur.Click += new System.EventHandler(this.btn_blur_Click);
            // 
            // btn_ycbcr_rbg
            // 
            this.btn_ycbcr_rbg.Location = new System.Drawing.Point(680, 663);
            this.btn_ycbcr_rbg.Name = "btn_ycbcr_rbg";
            this.btn_ycbcr_rbg.Size = new System.Drawing.Size(100, 35);
            this.btn_ycbcr_rbg.TabIndex = 16;
            this.btn_ycbcr_rbg.Text = "YCbCr轉RBG";
            this.btn_ycbcr_rbg.UseVisualStyleBackColor = true;
            this.btn_ycbcr_rbg.Click += new System.EventHandler(this.btn_ycbcr_rbg_Click);
            // 
            // btn_rbg_ycbcr
            // 
            this.btn_rbg_ycbcr.Location = new System.Drawing.Point(660, 622);
            this.btn_rbg_ycbcr.Name = "btn_rbg_ycbcr";
            this.btn_rbg_ycbcr.Size = new System.Drawing.Size(129, 35);
            this.btn_rbg_ycbcr.TabIndex = 16;
            this.btn_rbg_ycbcr.Text = "RBG轉YCbCr";
            this.btn_rbg_ycbcr.UseVisualStyleBackColor = true;
            this.btn_rbg_ycbcr.Click += new System.EventHandler(this.btn_rbg_ycbcr_Click);
            // 
            // btn_ycbcr_bw
            // 
            this.btn_ycbcr_bw.Location = new System.Drawing.Point(660, 704);
            this.btn_ycbcr_bw.Name = "btn_ycbcr_bw";
            this.btn_ycbcr_bw.Size = new System.Drawing.Size(129, 35);
            this.btn_ycbcr_bw.TabIndex = 17;
            this.btn_ycbcr_bw.Text = "YCbCr二值化";
            this.btn_ycbcr_bw.UseVisualStyleBackColor = true;
            this.btn_ycbcr_bw.Click += new System.EventHandler(this.btn_ycbcr_bw_Click);
            // 
            // btn_ycbcr_c_face
            // 
            this.btn_ycbcr_c_face.Location = new System.Drawing.Point(528, 704);
            this.btn_ycbcr_c_face.Name = "btn_ycbcr_c_face";
            this.btn_ycbcr_c_face.Size = new System.Drawing.Size(129, 35);
            this.btn_ycbcr_c_face.TabIndex = 18;
            this.btn_ycbcr_c_face.Text = "YCbCr轉換膚色";
            this.btn_ycbcr_c_face.UseVisualStyleBackColor = true;
            this.btn_ycbcr_c_face.Click += new System.EventHandler(this.btn_ycbcr_c_face_Click);
            // 
            // btn_hsv_c_face
            // 
            this.btn_hsv_c_face.Location = new System.Drawing.Point(545, 255);
            this.btn_hsv_c_face.Name = "btn_hsv_c_face";
            this.btn_hsv_c_face.Size = new System.Drawing.Size(129, 35);
            this.btn_hsv_c_face.TabIndex = 19;
            this.btn_hsv_c_face.Text = "HSV轉換膚色";
            this.btn_hsv_c_face.UseVisualStyleBackColor = true;
            this.btn_hsv_c_face.Click += new System.EventHandler(this.btn_hsv_c_face_Click);
            // 
            // btn_haar
            // 
            this.btn_haar.Location = new System.Drawing.Point(574, 296);
            this.btn_haar.Name = "btn_haar";
            this.btn_haar.Size = new System.Drawing.Size(100, 35);
            this.btn_haar.TabIndex = 20;
            this.btn_haar.Text = "Haar小波";
            this.btn_haar.UseVisualStyleBackColor = true;
            this.btn_haar.Click += new System.EventHandler(this.btn_haar_Click);
            // 
            // btn_contour_frame
            // 
            this.btn_contour_frame.Location = new System.Drawing.Point(557, 622);
            this.btn_contour_frame.Name = "btn_contour_frame";
            this.btn_contour_frame.Size = new System.Drawing.Size(100, 35);
            this.btn_contour_frame.TabIndex = 21;
            this.btn_contour_frame.Text = "二值化框框";
            this.btn_contour_frame.UseVisualStyleBackColor = true;
            this.btn_contour_frame.Click += new System.EventHandler(this.btn_contour_frame_Click);
            // 
            // btn_gamma
            // 
            this.btn_gamma.Location = new System.Drawing.Point(574, 337);
            this.btn_gamma.Name = "btn_gamma";
            this.btn_gamma.Size = new System.Drawing.Size(100, 35);
            this.btn_gamma.TabIndex = 22;
            this.btn_gamma.Text = "Gamma";
            this.btn_gamma.UseVisualStyleBackColor = true;
            this.btn_gamma.Click += new System.EventHandler(this.btn_gamma_Click);
            // 
            // btnLBP
            // 
            this.btnLBP.Location = new System.Drawing.Point(557, 581);
            this.btnLBP.Name = "btnLBP";
            this.btnLBP.Size = new System.Drawing.Size(100, 35);
            this.btnLBP.TabIndex = 23;
            this.btnLBP.Text = "LBP測試";
            this.btnLBP.UseVisualStyleBackColor = true;
            this.btnLBP.Click += new System.EventHandler(this.btnLBP_Click);
            // 
            // btnLBP2
            // 
            this.btnLBP2.Location = new System.Drawing.Point(528, 540);
            this.btnLBP2.Name = "btnLBP2";
            this.btnLBP2.Size = new System.Drawing.Size(129, 35);
            this.btnLBP2.TabIndex = 24;
            this.btnLBP2.Text = "LBP旋轉不變";
            this.btnLBP2.UseVisualStyleBackColor = true;
            this.btnLBP2.Click += new System.EventHandler(this.btnLBP2_Click);
            // 
            // btnLBP3
            // 
            this.btnLBP3.Location = new System.Drawing.Point(557, 499);
            this.btnLBP3.Name = "btnLBP3";
            this.btnLBP3.Size = new System.Drawing.Size(100, 35);
            this.btnLBP3.TabIndex = 25;
            this.btnLBP3.Text = "LBP等價";
            this.btnLBP3.UseVisualStyleBackColor = true;
            this.btnLBP3.Click += new System.EventHandler(this.btnLBP3_Click);
            // 
            // btnLBP4
            // 
            this.btnLBP4.Location = new System.Drawing.Point(557, 458);
            this.btnLBP4.Name = "btnLBP4";
            this.btnLBP4.Size = new System.Drawing.Size(100, 35);
            this.btnLBP4.TabIndex = 26;
            this.btnLBP4.Text = "LBP多尺度";
            this.btnLBP4.UseVisualStyleBackColor = true;
            this.btnLBP4.Click += new System.EventHandler(this.btnLBP4_Click);
            // 
            // btnLBP5
            // 
            this.btnLBP5.Location = new System.Drawing.Point(528, 417);
            this.btnLBP5.Name = "btnLBP5";
            this.btnLBP5.Size = new System.Drawing.Size(129, 35);
            this.btnLBP5.TabIndex = 27;
            this.btnLBP5.Text = "LBP多尺度等價";
            this.btnLBP5.UseVisualStyleBackColor = true;
            this.btnLBP5.Click += new System.EventHandler(this.btnLBP5_Click);
            // 
            // btn_contour
            // 
            this.btn_contour.Location = new System.Drawing.Point(557, 663);
            this.btn_contour.Name = "btn_contour";
            this.btn_contour.Size = new System.Drawing.Size(100, 35);
            this.btn_contour.TabIndex = 28;
            this.btn_contour.Text = "框框";
            this.btn_contour.UseVisualStyleBackColor = true;
            this.btn_contour.Click += new System.EventHandler(this.btn_contour_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(801, 744);
            this.Controls.Add(this.btn_contour);
            this.Controls.Add(this.btnLBP5);
            this.Controls.Add(this.btnLBP4);
            this.Controls.Add(this.btnLBP3);
            this.Controls.Add(this.btnLBP2);
            this.Controls.Add(this.btnLBP);
            this.Controls.Add(this.btn_gamma);
            this.Controls.Add(this.btn_contour_frame);
            this.Controls.Add(this.btn_haar);
            this.Controls.Add(this.btn_hsv_c_face);
            this.Controls.Add(this.btn_ycbcr_c_face);
            this.Controls.Add(this.btn_ycbcr_bw);
            this.Controls.Add(this.btn_rbg_ycbcr);
            this.Controls.Add(this.btn_ycbcr_rbg);
            this.Controls.Add(this.btn_blur);
            this.Controls.Add(this.btn_exp_sub_ero);
            this.Controls.Add(this.btn_erosion);
            this.Controls.Add(this.btn_expansion);
            this.Controls.Add(this.btn_sobel);
            this.Controls.Add(this.btn_hsv_bw);
            this.Controls.Add(this.btn_gray_bw);
            this.Controls.Add(this.btn_init);
            this.Controls.Add(this.btn_rbg_hsv);
            this.Controls.Add(this.btn_hsv_rgb);
            this.Controls.Add(this.btn_gray);
            this.Controls.Add(this.lab_time);
            this.Controls.Add(this.btn_time);
            this.Controls.Add(this.lab_test);
            this.Controls.Add(this.btn_test);
            this.Controls.Add(this.pic_show);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pic_show)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pic_show;
        private System.Windows.Forms.Button btn_test;
        private System.Windows.Forms.Label lab_test;
        private System.Windows.Forms.Button btn_time;
        private System.Windows.Forms.Label lab_time;
        private System.Windows.Forms.Button btn_gray;
        private System.Windows.Forms.Button btn_hsv_rgb;
        private System.Windows.Forms.Button btn_rbg_hsv;
        private System.Windows.Forms.Button btn_init;
        private System.Windows.Forms.Button btn_gray_bw;
        private System.Windows.Forms.Button btn_hsv_bw;
        private System.Windows.Forms.Button btn_sobel;
        private System.Windows.Forms.Button btn_expansion;
        private System.Windows.Forms.Button btn_erosion;
        private System.Windows.Forms.Button btn_exp_sub_ero;
        private System.Windows.Forms.Button btn_blur;
        private System.Windows.Forms.Button btn_ycbcr_rbg;
        private System.Windows.Forms.Button btn_rbg_ycbcr;
        private System.Windows.Forms.Button btn_ycbcr_bw;
        private System.Windows.Forms.Button btn_ycbcr_c_face;
        private System.Windows.Forms.Button btn_hsv_c_face;
        private System.Windows.Forms.Button btn_haar;
        private System.Windows.Forms.Button btn_contour_frame;
        private System.Windows.Forms.Button btn_gamma;
        private System.Windows.Forms.Button btnLBP;
        private System.Windows.Forms.Button btnLBP2;
        private System.Windows.Forms.Button btnLBP3;
        private System.Windows.Forms.Button btnLBP4;
        private System.Windows.Forms.Button btnLBP5;
        private System.Windows.Forms.Button btn_contour;
    }
}

