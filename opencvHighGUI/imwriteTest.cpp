 #include"all.h"

//生成一副透明png图片
void createAlphaMat(Mat &mat) {
	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			Vec4b &rgba = mat.at<Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
			rgba[2] = saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
			rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}

void imwriteTest() {
	//创建带Alpha通道的Mat
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	vector<int>compression_params;
	//设置图片格式，此处设置为PNG与主函数的imwrite中的相对应
	//compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);//OPENCV2版
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);//OPENCV3版
	compression_params.push_back(9);//设置图片尺寸，值越小压缩时间越长，PNG默认值为3，JPEG为95，PPM，PGM或PBM为1，仅有0或1

	try{
		imwrite("透明Alpha值图.png", mat, compression_params);//缺少compression_params参数运行错误
		imshow("生成的PNG图",mat);
		fprintf(stdout, "PNG图片文件的alpha数据保存完毕~\n可以在工程目录下查看有imwrite函数生成的图片\n");
		waitKey(0);
	}
	catch (runtime_error& ex){
		fprintf(stderr, "图像转换成PNG格式发生错误：%s\n", ex.what());
	}
}