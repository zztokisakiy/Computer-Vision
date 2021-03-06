#include <iostream>
#include "MeanShift.h"
#include "Hough.h"
#include "PerspectiveTransform.h"
#include "ImageSegmentation.h"
#include <io.h>

bool compare(Point a, Point b) {
	return a.x < b.x;
}

int main() {

	const char *filename = "E:\\vs workspace\\MeanShiftSegmentation\\MeanShiftSegmentation\\testset\\*.bmp";
	vector<string> files;
	struct _finddata_t fileinfo;
	intptr_t handle;
	handle = _findfirst(filename, &fileinfo);
	if (handle == -1) cout << "fail..." << endl;
	else
		files.push_back(fileinfo.name);
	while (!_findnext(handle, &fileinfo))
	{
		files.push_back(fileinfo.name);
	}
	_findclose(handle);
	cout << files.size() << endl;

	for (int i = 0; i <files.size(); ++i) {
		cout << i << endl;
		//0,3,5
		string fileName = files[i];
		cout << fileName << endl;

		PerspectiveTransform temp;
		auto dest = temp.getTransform("testset/" + fileName);
		dest.save(("result/fixed/" + fileName).c_str());

		CImg<uchar> Img;
		Img.load(("result/fixed/" + fileName).c_str());
		auto grayscaled = Img.get_norm().normalize(0, 255);
		ImageSegmentation imageSegmentation(grayscaled);
		imageSegmentation.processBinaryImage();
		auto binaryImg = imageSegmentation.getBinaryImage();
		binaryImg.save(("result/binary/" + fileName).c_str());

		imageSegmentation.numberSegmentationMainProcess("result/number/"+fileName.substr(0,fileName.size()-4));

		auto dividingImg = imageSegmentation.getImageWithDividingLine();
		dividingImg.save(("result/divideY/" + fileName).c_str());

		auto NumberDividedCircledImg = imageSegmentation.getNumberDividedCircledImg();
		NumberDividedCircledImg.save(("result/divide/" + fileName).c_str());

		/*auto HistogramImage = imageSegmentation.getHistogramImage();
		HistogramImage.save("his.jpg");*/
	}

	return 0;
}