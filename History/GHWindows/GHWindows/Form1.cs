using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Emgu.CV;
using Emgu.CV.Structure;
using Emgu.Util;
using System.Threading;
using Emgu.CV.CvEnum;
using System.Drawing.Imaging;

namespace GHWindows
{
    public partial class Form1 : Form
    {

        private Capture _capProp;
        private static string FILE_NAME = "C:\\Users\\USER\\Desktop\\1.jpg";
        private Bitmap g_fileImage = new Bitmap(FILE_NAME);
        private Bitmap g_nowImage = new Bitmap(FILE_NAME);

        public Form1()
        {
            InitializeComponent();
            _capProp = new Capture(0);
            Application.Idle += Application_Idle;
        }

        void Application_Idle(object sender, EventArgs e)
        {
            // Image<Bgr, Byte> frame = _capProp.QueryFrame().Bitmap; // 去query該畫面
            //Bitmap image = YCbCrChangeFace(_capProp.QueryFrame().Bitmap);
            //image = YCbCr2BWFace(BGR2YCbCr(image));
            //Bitmap image = Sobel(_capProp.QueryFrame().Bitmap);
            //pic_show.Image = image; // 把畫面轉換成bitmap型態，在餵給pictureBox元件
        }

        private void SetImage(Bitmap image)
        {
            pic_show.Image = image;
        }

        private void btn_test_Click(object sender, EventArgs e)
        {
        }

        private void btn_time_Click(object sender, EventArgs e)
        {
        }

        private void btn_gray_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = null;

            stopwatch.Reset();
            stopwatch.Start();

            image = BGR2Gray(g_fileImage);

            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        //public delegate void VDalegate(Bitmap image);
        //public VDalegate VDMethed;
        //VDMethed = new VDalegate(SetImage);
        //BeginInvoke(VDMethed, gray);
        private Bitmap BGR2Gray(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().BGR2Gray(image);
            return grayImage;
        }

        private Bitmap BGR2Gray8b(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().BGR2Gray8b(image);
            return grayImage;
        }

        private void btn_hsv_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = null;

            stopwatch.Reset();
            stopwatch.Start();

            image = BGR2HSV(g_fileImage);

            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap BGR2HSV(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().BGR2HSV(image);
            return grayImage;
        }

        private void btn_rbg_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2HSV(g_fileImage);

            stopwatch.Reset();
            stopwatch.Start();

            image = HSV2BGR(image); ;

            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap HSV2BGR(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().HSV2BGR(image);
            return grayImage;
        }

        private void btn_init_Click(object sender, EventArgs e)
        {
            SetImage(g_fileImage);
        }

        private void btn_gray_bw_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray(g_fileImage);

            stopwatch.Reset();
            stopwatch.Start();

            image = ThresholdingOTSU(image); ;

            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap ThresholdingOTSU(Bitmap image)
        {
            CallGHLibrary callGHLibrarynew = new CallGHLibrary();
            Bitmap grayImage = null;
            int scale = 0;

            scale = callGHLibrarynew.GetThresholdingScale(image);
            grayImage = callGHLibrarynew.ThresholdingOTSU(image, scale);
            return grayImage;
        }

        private void btn_hsv_bw_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2HSV(g_fileImage);

            stopwatch.Reset();
            stopwatch.Start();

            image = HSV2BWFace(image); ;

            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap HSV2BWFace(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().HSV2BWFace(image);
            return grayImage;
        }

        private void btn_sobel_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray(g_fileImage);
            Bitmap imageSbel = null;

            stopwatch.Reset();
            stopwatch.Start();
            imageSbel = Sobel(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();

            lab_time.Text = result;
            SetImage(imageSbel);
        }

        private Bitmap Sobel(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().Sobel(image, 1);
            return grayImage;
        }

        private void btn_expansion_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray8b(g_fileImage);
            stopwatch.Reset();
            stopwatch.Start();
            image = Expansion(image); ;
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();

            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap Expansion(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().Expansion(image);
            return grayImage;
        }

        private void btn_erosion_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray8b(g_fileImage);
            stopwatch.Reset();
            stopwatch.Start();
            image = Erosion(image); ;
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();

            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap Erosion(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().Erosion(image);
            return grayImage;
        }

        private void btn_exp_sub_ero_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray(g_fileImage);
            Bitmap imageExpansion = Expansion(image);
            Bitmap imageErosion = Erosion(image);

            stopwatch.Reset();
            stopwatch.Start();
            image = Sub(imageExpansion, imageErosion); ;
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();

            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap Sub(Bitmap image1, Bitmap image2)
        {
            Bitmap grayImage = new CallGHLibrary().Sub(image1, image2);
            return grayImage;
        }

        private void btn_blur_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray(g_fileImage);

            stopwatch.Reset();
            stopwatch.Start();
            image = Blur(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();

            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap Blur(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().Blur(image);
            return grayImage;
        }

        private void btn_rbg_ycbcr_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = null;

            stopwatch.Reset();
            stopwatch.Start();
            image = BGR2YCbCr(g_fileImage);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap BGR2YCbCr(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().BGR2YCbCr(image);
            return grayImage;
        }

        private void btn_ycbcr_rbg_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2YCbCr(g_fileImage);

            stopwatch.Reset();
            stopwatch.Start();
            image = YCbCr2BGR(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap YCbCr2BGR(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().YCbCr2BGR(image);
            return grayImage;
        }

        private void btn_ycbcr_bw_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2YCbCr(g_fileImage);

            stopwatch.Reset();
            stopwatch.Start();
            image = YCbCr2BWFace(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap YCbCr2BWFace(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().YCbCr2BWFace(image);
            return grayImage;
        }

        private void btn_ycbcr_c_face_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = g_fileImage;

            stopwatch.Reset();
            stopwatch.Start();
            image = YCbCrChangeFace(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap YCbCrChangeFace(Bitmap faceImage)
        {
            Bitmap ycbcrImage = BGR2YCbCr(faceImage);
            Bitmap ycbcr2BWFace = YCbCr2BWFace(ycbcrImage);
            Bitmap grayImage = new CallGHLibrary().BWChangeFace(faceImage, ycbcr2BWFace);
            return grayImage;
        }

        private void btn_hsv_c_face_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = g_fileImage;

            stopwatch.Reset();
            stopwatch.Start();
            image = HSVChangeFace(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap HSVChangeFace(Bitmap faceImage)
        {
            Bitmap hsvImage = BGR2HSV(faceImage);
            Bitmap hsv2BWFace = HSV2BWFace(hsvImage);
            Bitmap grayImage = new CallGHLibrary().BWChangeFace(faceImage, hsv2BWFace);
            return grayImage;
        }

        private void btn_haar_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray(g_fileImage);//Bitmap image = BGR2Gray(g_fileImage);

            stopwatch.Reset();
            stopwatch.Start();
            image = Haar(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            //image.Save("C:\\Users\\USER\\Desktop\\2.jpg");
            SetImage(image);
        }

        private Bitmap Haar(Bitmap image)
        {
            Bitmap grayImage = new CallGHLibrary().Haar(image);
            return grayImage;
        }

        private void btn_contour_frame_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = YCbCrChangeFace(g_fileImage);
            image = BGR2Gray(image);
            image = ThresholdingOTSU(image);
            image = Expansion(image);
            image = Erosion(image);
            image = Sobel(image);
            stopwatch.Reset();
            stopwatch.Start();
            image = new CallGHLibrary().ContourFrame(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;

            SetImage(image);
        }

        private void btn_gamma_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray(g_fileImage);
            stopwatch.Reset();
            stopwatch.Start();
            image = Gamma(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;

            SetImage(image);
        }

        private Bitmap Gamma(Bitmap image)
        {
            Bitmap gammaImage = new CallGHLibrary().Gamma(image);
            return gammaImage;
        }

        private void btnLBP_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray8b(g_fileImage);
            stopwatch.Reset();
            stopwatch.Start();
            image = LBPFeature(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;

            SetImage(image);
        }

        private Bitmap LBPFeature(Bitmap image)
        {
            Bitmap featureImage = new CallGHLibrary().LBPFeature(image);
            return featureImage;
        }

        private void btnLBP2_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray8b(g_fileImage);
            image = LBPFeature(image);
            stopwatch.Reset();
            stopwatch.Start();
            image = LBPInvariant(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;

            SetImage(image);
        }

        private Bitmap LBPInvariant(Bitmap image)
        {
            Bitmap invariantImage = new CallGHLibrary().LBPInvariant(image);
            return invariantImage;
        }

        private void btnLBP3_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray8b(g_fileImage);
            image = LBPFeature(image);
            image = LBPEquivalence(image);
            //image = LBPInvariant(image);
            stopwatch.Reset();
            stopwatch.Start();

            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap LBPEquivalence(Bitmap image)
        {
            Bitmap equivalenceImage = new CallGHLibrary().LBPEquivalence(image);
            return equivalenceImage;
        }

        private void btnLBP4_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray8b(g_fileImage);
            stopwatch.Reset();
            stopwatch.Start();
            image = MBLBPFeature(image);
            image = GeneralLBP(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap MBLBPFeature(Bitmap image)
        {
            Bitmap MBLBPImage = new CallGHLibrary().MBLBPFeature(image);
            return MBLBPImage;
        }

        private Bitmap GeneralLBP(Bitmap image)
        {
            Bitmap generalImage = new CallGHLibrary().GeneralLBP(image);
            return generalImage;
        }

        private void btnLBP5_Click(object sender, EventArgs e)
        {
            Bitmap fileImage = new Bitmap("C:\\Users\\Ghost\\Desktop\\images3.jpg");
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = BGR2Gray(fileImage);
            image = MBLBPFeature(image);
            image = GeneralLBP(image);
            stopwatch.Reset();
            stopwatch.Start();
            image = SEMBLBPFeature(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap SEMBLBPFeature(Bitmap image)
        {
            Bitmap SEMBLBPImage = new CallGHLibrary().SEMBLBPFeature(image);
            return SEMBLBPImage;
        }

        private void btn_contour_Click(object sender, EventArgs e)
        {
            string result = "";
            System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
            Bitmap image = g_fileImage;

            stopwatch.Reset();
            stopwatch.Start();
            image = YCbCrChangeFace(image);
            image = BGR2Gray8b(image);
            image = ThresholdingOTSU(image);
            image = Expansion(image);
            image = Erosion(image);
            image = Sobel(image);
            image = Tailoring(image);
            image = new CallGHLibrary().ContourFrame(image);
            result = stopwatch.Elapsed.TotalMilliseconds.ToString();
            lab_time.Text = result;
            SetImage(image);
        }

        private Bitmap Tailoring(Bitmap image)
        {
            Bitmap imageTailoring = new CallGHLibrary().Tailoring(image, image.Width - 8, image.Height - 4);
            return imageTailoring;
        }
    }
}
