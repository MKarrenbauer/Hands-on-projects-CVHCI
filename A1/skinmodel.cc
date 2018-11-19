#include "skinmodel.h"
#include <cmath>
#include <iostream>

using namespace std;

/// Constructor
SkinModel::SkinModel()
{
}

/// Destructor
SkinModel::~SkinModel() 
{
}

/// Start the training.  This resets/initializes the model.
///
/// Implementation hint:
/// Use this function to initialize/clear data structures used for training the skin model.
void SkinModel::startTraining()
{
    //--- IMPLEMENT THIS ---//
	int* minB = 255, maxB = 0;
	int* minG = 255, maxG = 0;
	int* minR = 255, maxR = 0;
}

/// Add a new training image/mask pair.  The mask should
/// denote the pixels in the training image that are of skin color.
///
/// @param img:  input image
/// @param mask: mask which specifies, which pixels are skin/non-skin
void SkinModel::train(const cv::Mat3b& img, const cv::Mat1b& mask)
{
	//--- IMPLEMENT THIS ---//
	
	cv::Mat1b imgB = cv::Mat1b::zeros(img.rows, img.cols);
	cv::Mat1b imgG = cv::Mat1b::zeros(img.rows, img.cols);
	cv::Mat1b imgR = cv::Mat1b::zeros(img.rows, img.cols);

	for (int row = 0; row < img.rows; ++row) {
		for (int col = 0; col < img.cols; ++col) {
			cv::Vec3b bgr = img(row, col);
			if (mask(row, col) == 255) {
				minB = min(minB, bgr[0]);
				maxB = max(maxB, bgr[0]);
				minG = min(minG, bgr[1]);
				maxG = max(maxG, bgr[1]);
				minR = min(minR, bgr[2]);
				maxR = max(maxR, bgr[2]);
			}
		}
	}
}

/// Finish the training.  This finalizes the model.  Do not call
/// train() afterwards anymore.
///
/// Implementation hint:
/// e.g normalize w.r.t. the number of training images etc.
void SkinModel::finishTraining()
{
	//--- IMPLEMENT THIS ---//
}


/// Classify an unknown test image.  The result is a probability
/// mask denoting for each pixel how likely it is of skin color.
///
/// @param img: unknown test image
/// @return:    probability mask of skin color likelihood
cv::Mat1b SkinModel::classify(const cv::Mat3b& img)
{
    cv::Mat1b skin = cv::Mat1b::zeros(img.rows, img.cols);

	//--- IMPLEMENT THIS ---//
    for (int row = 0; row < img.rows; ++row) {
        for (int col = 0; col < img.cols; ++col) {

			cv::Vec3b bgr = img(row, col);
			
			if ((bgr[0] >= minB && bgr[0] <= maxB) && (bgr[1] >= minG && bgr[1] <= maxG) && (bgr[2] >= minR && bgr[2] <= maxR)) {
				skin(row, col) = 255
			}
			else {
				skin(row, col) = 0
			}		
					
			
			if (false)
				skin(row, col) = rand()%256;

			if (false)
				skin(row, col) = img(row,col)[2];

			if (false) {
			
				cv::Vec3b bgr = img(row, col);
				if (bgr[2] > bgr[1] && bgr[1] > bgr[0]) 
					skin(row, col) = 2*(bgr[2] - bgr[0]);
			}
        }
    }

    return skin;
}

