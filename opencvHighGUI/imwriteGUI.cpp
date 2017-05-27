#include"all.h"

void imwriteGUI() {
	
	//图像的载入和显示
	Mat girl = imread("girl.jpg");
	namedWindow("[1]动漫图");
	imshow("[1]动漫图", girl);
	
	//初级图像混合
	Mat image = imread("dota.jpg", 199);//载入图片
	Mat logo = imread("dota_logo.jpg");
	namedWindow("[2]原画图");
	imshow("[2]原画图", image);//显示
	
	namedWindow("[3]logo图");
	imshow("[3]logo图", logo);
	
	Mat imageROI;//用于存放兴趣区域ROI
	imageROI = image(Rect(800, 350, logo.cols, logo.rows));//方法一
	//imageROI = image(Range(350, 350 + logo.rows), Range(800, 800 + logo.cols));//方法二

	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);//将logo加到原图上，（权重）

	namedWindow("[4]原画+logo图");
	imshow("[4]原画+logo图", image);//显示结果

	//第一种输出方式：指定并设置了imwrite的第三个参数，可以在debug模式下正常运行，在release下也可以正常运行
	vector<int>compression_params;
	compression_params.push_back(IMWRITE_JPEG_CHROMA_QUALITY);//OPENCV3版
	compression_params.push_back(99);
	try {
		//输出操作后的图像到本地文件，格式为jpg
		imwrite("由imwrite生成的图片.jpg", image, compression_params);
		waitKey(0);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "图像转换成JPG格式发生错误：%s\n", ex.what());
	}
	/*
	//第二种输出方式：不指定imwrite第三个参数，在debug下运行报读取异常错误，但在release下运行正常
	//输出操作后的图像到本地文件，格式为jpg
	imwrite("由imwrite生成的图片.jpg", image);
	waitKey(0);
	*/
}