#include<opencv2\opencv.hpp>
#include<vector>
#include<opencv2/core/core.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

void createAlphaMat(Mat &mat);
void imwriteTest();
void imwriteGUI();
void on_Trackbar(int, void*);
void testTrackbar();