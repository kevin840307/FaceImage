#include "Detection.h"
#include "Bitmap.h"
#include <sstream>
namespace MNDT {
	namespace Detection {
		void PredictFeature(C_UCHAR* src
			, C_UINT32 width, C_UINT32 height
			, std::map<UINT32, Region>& R)
		{
			UCHAR* gray = new UCHAR[width * height];
			MNDT::ChangeColor(src, gray
				, width, height
				, ColerType::BGR2GRAY_8BIT);

			LBP lbp;
			UCHAR* feature = new UCHAR[width * height]{ 0 };
			lbp.EquivalentLBP(gray, feature
				, width, height);

			delete[] gray;
			gray = nullptr;

			Image featureImage(feature, width, height, MNDT::ImageType::GRAY_8BIT);
			C_UINT32 gridX = 8;
			C_UINT32 gridY = 8;
			C_UINT32 bin = 59;
			AdaBoost adaBoost;
			adaBoost.Read("D:\\train.txt");

			std::vector<UINT32> deleteLabel;
			int index = 0;
			Image srcImage(const_cast<UCHAR*>(src), width, height, MNDT::ImageType::BGR_24BIT);
			for (auto& node : R)
			{
				const Rect& rect = node.second.rect;

				UCHAR* rectData = new UCHAR[rect.Width() * rect.Height()]{ 0 };
				MNDT::Screenshot8bit(featureImage, rectData, rect);

				AdaBoostType::DATA histogram(adaBoost.DimensionSize(), 0);
				lbp.LBPHistogram(rectData, histogram
					, rect.Width(), rect.Height()
					, gridX, gridY, bin);

				delete[] rectData;
				rectData = nullptr;

				if (adaBoost.Predict(histogram) != 1)
				{
					deleteLabel.push_back(node.first);
				}
				//UCHAR* rectData2 = new UCHAR[rect.Width() * rect.Height() * 3];
				//Image purImage(rectData2, rect.Width(), rect.Height(), MNDT::ImageType::BGR_24BIT);
				//MNDT::Screenshot24bit(srcImage, purImage, rect);
				//Bitmap bit(rectData2, rect.Width(), rect.Height(), MNDT::ImageType::BGR_24BIT);
				//std::string str = "";
				//std::stringstream stream;
				//stream << index;
				//stream >> str;
				//str = "D:\\Data\\" + str + ".bmp";
				//bit.Save(str.c_str());
				//index++;
			}


			for (UINT32 index = 0; index < deleteLabel.size(); index++)
			{
				R.erase(deleteLabel[index]);
			}

			delete[] feature;
			feature = nullptr;
		}
	}
}
