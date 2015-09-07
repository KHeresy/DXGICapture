#include <chrono>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "DXGIManager.h"

int main(int argc, char** argv)
{
	CoInitialize(NULL);

	DXGIManager mDXGIManager;
	mDXGIManager.SetCaptureSource(CSMonitor1);

	RECT rcDim;
	mDXGIManager.GetOutputRect(rcDim);

	DWORD dwWidth = rcDim.right - rcDim.left;
	DWORD dwHeight = rcDim.bottom - rcDim.top;

	printf("dwWidth=%d dwHeight=%d\n", dwWidth, dwHeight);

	cv::Mat mScreen(dwHeight, dwWidth, CV_8UC4);

	cv::namedWindow("Screen");
	while (true)
	{
		if (mDXGIManager.GetOutputBits(mScreen.data, rcDim) == S_OK)
		{
			cv::Mat mShowImg;
			cv::resize(mScreen, mShowImg, cv::Size(mScreen.cols / 3, mScreen.rows / 3));
			cv::imshow("Screen", mShowImg);
		}
		if (cv::waitKey(30) == 'q')
		{
			break;
		}
	}
}
