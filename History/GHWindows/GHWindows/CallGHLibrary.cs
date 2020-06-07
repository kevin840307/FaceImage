using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Collections;

namespace GHWindows
{
    class CallGHLibrary
    {
        private ColorPalette _colorPalette;

        public CallGHLibrary()
        {
            using (Bitmap bitmap = new Bitmap(1, 1, PixelFormat.Format8bppIndexed))
            {
                _colorPalette = bitmap.Palette;
            }
            for (int i = 0; i < 256; i++)
            {
                _colorPalette.Entries[i] = Color.FromArgb(i, i, i);
            }
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnBGR2Gray(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap BGR2Gray(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, purposeImage.Width, purposeImage.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnBGR2Gray(sourceStream, purposeStream, sourceImage.Height, sourceImage.Width);
            }

            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnBGR2Gray8b(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap BGR2Gray8b(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height, PixelFormat.Format8bppIndexed);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, purposeImage.Width, purposeImage.Height), ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnBGR2Gray8b(sourceStream, purposeStream, sourceImage.Height, sourceImage.Width);
            }
            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnBGR2HSV(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap BGR2HSV(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, purposeImage.Width, purposeImage.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnBGR2HSV(sourceStream, purposeStream, sourceImage.Height, sourceImage.Width);
            }

            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnHSV2BGR(byte* cSource, byte* cPurpose, int iRows, int iCols, double dVBase);

        public Bitmap HSV2BGR(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, purposeImage.Width, purposeImage.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnHSV2BGR(sourceStream, purposeStream, sourceImage.Height, sourceImage.Width, 1.0);
            }

            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnThresholdingOTSU(byte* cSource, byte* cPurpose, int iRows, int iCols, int iScale);

        public Bitmap ThresholdingOTSU(Bitmap sourceImage, int scale)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnThresholdingOTSU(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height, scale);
            }
            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern int fnGetThresholdingScale(byte* cSource, int iRows, int iCols);

        public int GetThresholdingScale(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;
            int scale = 0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                scale = fnGetThresholdingScale(sourceStream, sourceImage.Width, sourceImage.Height);
            }

            sourceImage.UnlockBits(sourceData);
            return scale;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnHSV2BWFace(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap HSV2BWFace(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnHSV2BWFace(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }

            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnSobel(byte* cSource, byte* cPurpose, int iRows, int iCols, double dScale);

        //8位元
        public Bitmap Sobel(Bitmap sourceImage, double scale = 1)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnSobel(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height, scale);
            }
            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnExpansion(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap Expansion(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnExpansion(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }
            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnErosion(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap Erosion(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnErosion(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }
            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnSub(byte* cSource1, byte* cSource2, byte* cPurpose, int iRows, int iCols);

        public Bitmap Sub(Bitmap source1Image, Bitmap source2Image)
        {
            BitmapData source1Data = source1Image.LockBits(new Rectangle(0, 0, source1Image.Width, source1Image.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr source1Ptr = source1Data.Scan0;

            BitmapData source2Data = source2Image.LockBits(new Rectangle(0, 0, source1Image.Width, source1Image.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr source2Ptr = source2Data.Scan0;

            Bitmap purposeImage = new Bitmap(source1Image.Width, source1Image.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, source1Image.Width, source1Image.Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* source1Stream = (byte*)source1Ptr.ToPointer();
                byte* source2Stream = (byte*)source2Ptr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnSub(source1Stream, source2Stream, purposeStream, source1Image.Width, source1Image.Height);
            }

            source1Image.UnlockBits(source1Data);
            source2Image.UnlockBits(source2Data);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnBlur(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap Blur(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnBlur(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }

            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnBGR2YCbCr(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap BGR2YCbCr(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnBGR2YCbCr(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }

            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnYCbCr2BGR(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap YCbCr2BGR(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnYCbCr2BGR(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }

            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnYCbCr2BWFace(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap YCbCr2BWFace(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnYCbCr2BWFace(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }

            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        public Bitmap BWChangeFace(Bitmap faceImage, Bitmap bwImage)
        {
            BitmapData faceData = faceImage.LockBits(new Rectangle(0, 0, faceImage.Width, faceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr facePtr = faceData.Scan0;

            BitmapData bwData = bwImage.LockBits(new Rectangle(0, 0, bwImage.Width, bwImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr bwPtr = bwData.Scan0;

            Bitmap purposeImage = new Bitmap(faceImage.Width, faceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, faceImage.Width, faceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;
            unsafe
            {
                byte* faceStream = (byte*)facePtr.ToPointer();
                byte* bwStream = (byte*)bwPtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                int indexMax = faceImage.Width * faceImage.Height * 3;

                for (int index = 0; index < indexMax; index++)
                {
                    if (bwStream[0] == 255)
                    {
                        purposeStream[0] = faceStream[0];
                    }
                    faceStream++;
                    bwStream++;
                    purposeStream++;
                }
            }

            faceImage.UnlockBits(faceData);
            bwImage.UnlockBits(bwData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnHaar(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap Haar(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;
            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnHaar(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnContourFrame(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap ContourFrame(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;
            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnContourFrame(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnGamma(byte* cSource, byte* cPurpose, int iRows, int iCols, double dGamma);

        public Bitmap Gamma(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);
            IntPtr purposePtr = purposeData.Scan0;
            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnGamma(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height, 1);
            }
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnLBPFeature(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap LBPFeature(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height, PixelFormat.Format8bppIndexed);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnLBPFeature(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }

            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);

            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnLBPInvariant(byte* cPurpose, int iRows, int iCols);

        public Bitmap LBPInvariant(Bitmap purposeImage)
        {
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, purposeImage.Width, purposeImage.Height), ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;
            unsafe
            {
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnLBPInvariant(purposeStream, purposeImage.Width, purposeImage.Height);
            }
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnLBPEquivalence(byte* cPurpose, int iRows, int iCols);

        public Bitmap LBPEquivalence(Bitmap purposeImage)
        {
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, purposeImage.Width, purposeImage.Height), ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;
            unsafe
            {
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnLBPEquivalence(purposeStream, purposeImage.Width, purposeImage.Height);
            }
            purposeImage.UnlockBits(purposeData);
            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnMBLBPFeature(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap MBLBPFeature(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height, PixelFormat.Format8bppIndexed);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnMBLBPFeature(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }

            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);

            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnGeneralLBP(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap GeneralLBP(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height, PixelFormat.Format8bppIndexed);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnGeneralLBP(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }

            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);

            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnSEMBLBPFeature(byte* cSource, byte* cPurpose, int iRows, int iCols);

        public Bitmap SEMBLBPFeature(Bitmap sourceImage)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(sourceImage.Width, sourceImage.Height, PixelFormat.Format8bppIndexed);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;

            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnSEMBLBPFeature(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height);
            }

            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);

            return purposeImage;
        }

        [DllImport("D:/GHLibrary.dll")]
        unsafe private static extern void fnTailoring(byte* cSource, byte* cPurpose, int iORows, int iOCols, int iRows, int iCols);

        public Bitmap Tailoring(Bitmap sourceImage, int rows, int cols)
        {
            BitmapData sourceData = sourceImage.LockBits(new Rectangle(0, 0, sourceImage.Width, sourceImage.Height), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            IntPtr sourcePtr = sourceData.Scan0;

            Bitmap purposeImage = new Bitmap(rows, cols, PixelFormat.Format8bppIndexed);
            BitmapData purposeData = purposeImage.LockBits(new Rectangle(0, 0, rows, cols), ImageLockMode.WriteOnly, PixelFormat.Format8bppIndexed);
            IntPtr purposePtr = purposeData.Scan0;
            
            unsafe
            {
                byte* sourceStream = (byte*)sourcePtr.ToPointer();
                byte* purposeStream = (byte*)purposePtr.ToPointer();
                fnTailoring(sourceStream, purposeStream, sourceImage.Width, sourceImage.Height, rows, cols);
            }

            purposeImage.Palette = _colorPalette;
            sourceImage.UnlockBits(sourceData);
            purposeImage.UnlockBits(purposeData);

            return purposeImage;
        }
    }
}
