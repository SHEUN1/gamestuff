#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/gpu/gpu.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>


using namespace cv;
using namespace std;

double otsu(vector<int> histogram, int total) {
    double sum = 0;
    for (double i = 1; i < histogram.size(); ++i) //normally it will be 255 but sometimes we want to change step **histogram.size().width + 1
        sum += i * histogram[i];
    double sumB = 0;
    double wB = 0;
    double wF = 0;
    double mB;
    double mF;
    double max = 0.0;
    double between = 0.0;
    double threshold1 = 0.0;
    double threshold2 = 0.0;
    for (double i = 0; i < histogram.size(); ++i) {
        wB += histogram[i];
        if (wB == 0)
            continue;
        wF = total - wB;
        if (wF == 0)
            break;
        sumB += i * histogram[i];
        mB = sumB / wB;
        mF = (sum - sumB) / wF;
        between = wB * wF * (mB - mF) * (mB - mF);
        if ( between >= max ) {
            threshold1 = i;
            if ( between > max ) {
                threshold2 = i;
            }
            max = between;
        }
    }
    return ( threshold1 + threshold2 ) / 2.0;
}

int main()
{/** GPU VERSION ************************************************************
	//VideoCapture cap("/home/sheun/Pictures/transistorVideo1.mp4"); // open the default camera
	//    if(!cap.isOpened())  // check if we succeeded
	//        return -1;
	   Mat cap;
	   cap = imread("/home/sheun/Pictures/transistor/Transistor3.jpg");

	    gpu::GpuMat img2, BW1, BW2, blur, blur2;

	    for(;;)
	    {
		//Mat imgBeforeGpu; //UNCOMMENT FOR VIDEO
	    Mat imgBeforeGpu= imread("/home/sheun/Pictures/transistor/Transistor3.jpg"); //UNCOMMENT FOR IMAGE ONLY
		//cap >> imgBeforeGpu; //UNCOMMENT FOR VIDEO
	        gpu::GpuMat img;
		cvtColor( imgBeforeGpu, imgBeforeGpu, CV_BGR2GRAY );
	        img.upload(imgBeforeGpu);
		/// Convert to grayscale
		//Mat img2, BW1, BW2, blur, blur2;
		gpu:: equalizeHist( img, img2);
		gpu:: GaussianBlur(img, blur, Size(5, 5), 0, 0);
		gpu:: GaussianBlur(img2, blur2, Size(5, 5), 0, 0);
		gpu:: threshold(blur, BW1, 100, 255,  CV_THRESH_BINARY);
	    gpu:: threshold(blur2, BW2, 100, 255,  CV_THRESH_BINARY_INV);
		//gpu::adaptiveThreshold(blur, BW1, 255,  ADAPTIVE_THRESH_GAUSSIAN_C, 5, 11);//;(InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
		//gpu::adaptiveThreshold(blur2, BW2, 255,  ADAPTIVE_THRESH_GAUSSIAN_C, 5, 11);

		Mat imageAfterGpu, imageAfterGpu2;
		BW1.download(imageAfterGpu);
		BW2.download(imageAfterGpu2);
		if(waitKey(30) >= 0) break;
		 imshow("opencvtest1",imageAfterGpu);
		 imshow("opencvtest2",imageAfterGpu2);
	    }
	    // the camera will be deinitialized automatically in VideoCapture destructor
	    return 1;
	    */
//** CPU VERSION************************************
	//VideoCapture cap("/home/sheun/Pictures/transistorVideo1.mp4"); // open the default camera
		   // if(!cap.isOpened())  // check if we succeeded
		     //   return -1;
			Mat img2, BW1, BW2, blur, blur2, cap, hist;
		    //cap = imread("/home/sheun/Pictures/transistor/Transistor3.jpg");



		  for(;;)
		    {
// DicomImage DCM_image("/home/sheun/promedical/Training Set/Patients/009/CT/00030044");
	//	    cv::Mat img(int(DCM_image.getWidth()), int(DCM_image.getHeight()), CV_8U, (uchar*)DCM_image.getOutputData(8));
			Mat img = imread("/home/sheun/Pictures/transistor/Transistor3.jpg"); //UNCOMMENT FOR IMAGE ONLY;
			int total = (img.size().width)*(img.size().height);
		//	cap >> img;
			cvtColor( img, img, CV_BGR2GRAY );
		        //img.upload(imgBeforeGpu);
			/// Convert to grayscale
			//Mat img2, BW1, BW2, blur, blur2;
			//equalizeHist( img, img2); //

			 // Quantize the hue to 30 levels
			    // and the saturation to 32 levels
			    int hbins = 30, sbins = 32;
			    int histSize[] = {hbins, sbins};
			    // hue varies from 0 to 179, see cvtColor
			    float hranges[] = { 0, 180 };
			    // saturation varies from 0 (black-gray-white) to
			    // 255 (pure spectrum color)
			    float sranges[] = { 0, 256 };
			    const float* ranges[] = { hranges, sranges };
			    //Mat hist;
			    // we compute the histogram from the 0-th and 1-st channels
			    int channels[] = {0, 1};

			   calcHist(&img, 1, channels, Mat(), // do not use mask
			             hist, 1, histSize, ranges,
			             true, // the histogram is uniform
			             false);

			GaussianBlur(img, blur, Size(5, 5), 0, 0);
			//GaussianBlur(img2, blur2, Size(5, 5), 0, 0);


			vector<int> array;
			if (hist.isContinuous()) {
			  array.assign(hist.datastart, hist.dataend);
			} else {
			  for (int i = 0; i < hist.rows; ++i) {
			    array.insert(array.end(), hist.ptr<int>(i), hist.ptr<int>(i)+hist.cols);
			  }
			}

			double ostuValue = otsu(array, total);
			threshold(blur, BW1, ostuValue, 255,  CV_THRESH_BINARY);
			int getO = threshold(blur, BW1, ostuValue, 255,  CV_THRESH_BINARY);
			//threshold(blur, BW1, 100, 255,  CV_THRESH_BINARY | CV_THRESH_OTSU);
		   // threshold(blur2, BW2, 100, 255,  CV_THRESH_BINARY | CV_THRESH_OTSU);
			//BW1.download(imageAfterGpu);
			if(waitKey(30) >= 0) break;
			/**for(int i=0; i<array.size();i++)
			{
				cout << array[i]<<" ";
			}
			//cout << array.size();
			imshow("opencvtest", BW1);
			cout<< ""<<endl;
			cout << array.size();*/

			imshow("opencvtest", BW1);
			cout<<getO<<endl;
		    }
		    // the camera will be deinitialized automatically in VideoCapture destructor
		    return 1;

}

