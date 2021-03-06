// color transfer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "CImg.h"
#include <iostream>

using namespace std;
using namespace cimg_library;
typedef unsigned char uchar;

int main()
{
	CImg<uchar> srcImg;
	srcImg.load("result2/picture5/src.jpg");
	auto srcLab = srcImg.get_RGBtoLab();

	CImg<uchar> destImg;
	destImg.load("result2/picture5/dest.jpg");
	auto destLab = destImg.get_RGBtoLab();

	float size1 = srcLab.size() / 3;
	float size2 = destLab.size() / 3;

	float srcMean0, srcMean1, srcMean2, destMean0, destMean1, destMean2;	//均值
	srcMean0 = srcMean1 = srcMean2 = destMean0 = destMean1 = destMean2 = 0;
	cimg_forXY(srcLab, x, y) {
		srcMean0 += srcLab(x, y, 0);
		srcMean1 += srcLab(x, y, 1);
		srcMean2 += srcLab(x, y, 2);

	}

	cout <<size1<< endl;
	cout << size2 << endl;

	srcMean0 /= size1;
	srcMean1 /= size1;
	srcMean2 /= size1;


	cimg_forXY(destLab, x, y) {
		destMean0 += destLab(x, y, 0);
		destMean1 += destLab(x, y, 1);
		destMean2 += destLab(x, y, 2);
	}

	destMean0 /= size2;
	destMean1 /= size2;
	destMean2 /= size2;

	cout << destMean0 << " " << destMean1 << " " << destMean2 << endl;


	float s0, s1, s2, d0, d1, d2;	//方差
	s0 = s1 = s2 = d0 = d1 = d2 = 0;

	cimg_forXY(srcLab, x, y) {
		s0 += sqrt(pow(srcLab(x, y, 0) - srcMean0, 2));
		s1 += sqrt(pow(srcLab(x, y, 1) - srcMean1, 2));
		s2 += sqrt(pow(srcLab(x, y, 2) - srcMean2, 2));
	}

	s0 /= size1;
	s1 /= size1;
	s2 /= size1;

	cimg_forXY(destLab, x, y) {
		d0 += sqrt(pow(destLab(x, y, 0) - destMean0, 2));
		d1 += sqrt(pow(destLab(x, y, 1) - destMean1, 2));
		d2 += sqrt(pow(destLab(x, y, 2) - destMean2, 2));
	}

	d0 /= size2;
	d1 /= size2;
	d2 /= size2;

	//转换
	cimg_forXY(srcLab, x, y) {
		srcLab(x, y, 0) = (srcLab(x, y, 0) - srcMean0)*d0 / s0 + destMean0;
		srcLab(x, y, 1) = (srcLab(x, y, 1) - srcMean1)*d1 / s1 + destMean1;
		srcLab(x, y, 2) = (srcLab(x, y, 2) - srcMean2)*d2 / s2 + destMean2;
	}


	CImg<uchar> res = srcLab.get_LabtoRGB();
	//res.display();
	res.save("result2/picture5/res.jpg");
}

