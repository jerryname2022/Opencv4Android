#include <iostream>
#include <opencv2\opencv.hpp>
#include <jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <vector>
#include <thread>
#include <android/log.h>

#define TAG "ORBCompute" // 这个是自定义的LOG的标识
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define MIN_KEYPOINT_NUM 450

using namespace std;
using namespace cv;

/*bool compute(Mat& img_object) {
 //-- Step 1: Detect the keypoints using SURF Detector
 Ptr<FeatureDetector> detector = ORB::create();

 std::vector<KeyPoint> keypoints_object;

 detector->detect(img_object, keypoints_object);

 return keypoints_object.size() >= MIN_KEYPOINT_NUM;
 }
 */

extern "C" {
JNIEXPORT jboolean JNICALL Java_com_org_opencv_imp_OpenCVImp_findFeatures(
		JNIEnv *, jclass, jlong);

JNIEXPORT jboolean JNICALL Java_com_org_opencv_imp_OpenCVImp_findFeatures(
		JNIEnv *, jclass, jlong addrRgba) {
	Mat& mRgb = *(Mat*) addrRgba;

	jboolean issatisfy = false;

	Ptr<FeatureDetector> detector = ORB::create();
	std::vector<KeyPoint> keypoints_object;
	detector->detect(mRgb, keypoints_object);

	//return keypoints_object.size() >= MIN_KEYPOINT_NUM;

	issatisfy = (MIN_KEYPOINT_NUM <= keypoints_object.size());

	//LOGI("keypoints_object.size ... %d issatisfy  ... %d", keypoints_object.size(), issatisfy);

	for (unsigned int i = 0; i < keypoints_object.size(); i++) {
		const KeyPoint& kp = keypoints_object[i];
		circle(mRgb, Point(kp.pt.x, kp.pt.y), 10, Scalar(158, 144, 233, 255));
	}

	return issatisfy;
}
}

