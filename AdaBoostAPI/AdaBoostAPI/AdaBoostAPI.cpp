// AdaBoostAPI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AdaBoost.h"
#include "general.h"
#include "Bitmap.h"
#include "LBPFeature.h"
#include "Library.h"
#include <iostream>


void ReadAllData(AdaBoostType::DATAS& datas, AdaBoostType::LABELS& labels)
{
	std::ifstream file;
	std::string imgPath;

	file.open("D:\\Downloads\\secret_plan.txt", std::ios::in);

	// EquivalentLBP pixel max = 58;
	C_UINT32 gridX = 8;
	C_UINT32 gridY = 8;
	C_UINT32 bin = 59;
	LBPFeature feature(gridX, gridY, bin);

	while (file >> imgPath)
	{
		Bitmap bitmap(imgPath);
		AdaBoostType::LABEL label;

		file >> label;


		AdaBoostType::DATA histogram(gridX * gridY * bin, 0);

		if (bitmap.ImageType() == MNDT::ImageType::BGR_24BIT)
		{
			UCHAR* data = new UCHAR[bitmap.Width()* bitmap.Height()];

			MNDT::ChangeColor(bitmap.data, data
				, bitmap.Width(), bitmap.Height()
				, ColerType::BGR2GRAY_8BIT);

			feature.EquivalentLBPHistogram(data, histogram
				, bitmap.Width(), bitmap.Height());

			delete[] data;
			data = nullptr;
		}
		else
		{
			feature.EquivalentLBPHistogram(bitmap.data, histogram
				, bitmap.Width(), bitmap.Height());
		}

		datas.push_back(histogram);
		labels.push_back(label);
	}
	file.close();
}

using namespace concurrency;


int main()
{
	//Bitmap bitmap("C:\\Users\\services6\\Downloads\\AdaBoostss\\圖庫已處理2\\1.bmp");
	//Bitmap bitmap("C:\\Users\\services6\\Downloads\\AdaBoostss\\人臉已處理\\s1\\1.bmp");
	//Bitmap bitmap("C:\\Users\\services6\\Downloads\\123.bmp");
	//Bitmap bitmap("C:\\Users\\Ghost\\Desktop\\3.bmp");
	//Image img(bitmap.data, bitmap.Width(), bitmap.Height(), MNDT::ImageType(bitmap.ImageType()));
	//bitmap.PrintFileHeader();
	//bitmap.PrintInfoHeader();
	//for (UINT32 row = 0; row < 50; row++)
	//{
	//	for (UINT32 col = 0; col < bitmap.Width(); col++)
	//	{
	//		img.SetPixel(row, col, Pixel(255, 255, 0));
	//	}
	//}

	//bitmap.Save("C:\\Users\\Ghost\\Desktop\\Lenna2.bmp");
	//Bitmap bitmap("C:\\Users\\Ghost\\Desktop\\Lenna.bmp");
	//Bitmap bitmap("C:\\Users\\Ghost\\Desktop\\Lenna.bmp");
	////bitmap.PrintFileHeader();
	////bitmap.PrintInfoHeader();
	//LBPFeature feature(8, 8, 59);

	//UCHAR* data = new UCHAR[bitmap.Width()* bitmap.Height()];

	//MNDT::ChangeColor(bitmap.data, data
	//	, bitmap.Width(), bitmap.Height()
	//	, ColerType::BGR2GRAY_8BIT);

	//UCHAR* data3 = new UCHAR[bitmap.Width() * bitmap.Height() * MNDT::ImageType::BGR_24BIT]{ 0 };
	//Image img2(data, bitmap.Width(), bitmap.Height(), MNDT::ImageType::GRAY_8BIT);
	//Image img3(data3, bitmap.Width(), bitmap.Height(), MNDT::ImageType::BGR_24BIT);

	//for (UINT32 row = 0; row < bitmap.Height(); row++)
	//{
	//	for (UINT32 col = 0; col < bitmap.Width(); col++)
	//	{
	//		img3.SetPixel(row, col, img2.GetPixel(row, col));
	//	}
	//}
	//Bitmap b(data, bitmap.Width(), bitmap.Height(), MNDT::ImageType::GRAY_8BIT);

	//b.Save("C:\\Users\\Ghost\\Desktop\\Lenaa2.bmp");
	//Bitmap b2(data3, bitmap.Width(), bitmap.Height(), MNDT::ImageType::BGR_24BIT);

	//b2.Save("C:\\Users\\Ghost\\Desktop\\Lenna22.bmp");

	//delete[] data3;
	//delete[] data;

	AdaBoostType::DATAS datas;
	AdaBoostType::LABELS labels;
	std::cout << "得取特徵中..." << std::endl;
	ReadAllData(datas, labels);

	std::cout << "訓練特徵中..." << std::endl;
	AdaBoost adaBoost(datas, labels);
	//adaBoost.Train(100);
	//adaBoost.Save("D:\\train.txt");
	adaBoost.Read("D:\\train.txt");

	AdaBoostType::LABELS predictLabels = adaBoost.Predict(datas);
	for (UINT32 index = 0; index < predictLabels.size(); index++)
	{
		std::cout << predictLabels[index] << " ";
	}

	system("pause");
	return 0;
}

