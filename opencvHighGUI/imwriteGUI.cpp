#include"all.h"

void imwriteGUI() {
	
	//ͼ����������ʾ
	Mat girl = imread("girl.jpg");
	namedWindow("[1]����ͼ");
	imshow("[1]����ͼ", girl);
	
	//����ͼ����
	Mat image = imread("dota.jpg", 199);//����ͼƬ
	Mat logo = imread("dota_logo.jpg");
	namedWindow("[2]ԭ��ͼ");
	imshow("[2]ԭ��ͼ", image);//��ʾ
	
	namedWindow("[3]logoͼ");
	imshow("[3]logoͼ", logo);
	
	Mat imageROI;//���ڴ����Ȥ����ROI
	imageROI = image(Rect(800, 350, logo.cols, logo.rows));//����һ
	//imageROI = image(Range(350, 350 + logo.rows), Range(800, 800 + logo.cols));//������

	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);//��logo�ӵ�ԭͼ�ϣ���Ȩ�أ�

	namedWindow("[4]ԭ��+logoͼ");
	imshow("[4]ԭ��+logoͼ", image);//��ʾ���

	//��һ�������ʽ��ָ����������imwrite�ĵ�����������������debugģʽ���������У���release��Ҳ������������
	vector<int>compression_params;
	compression_params.push_back(IMWRITE_JPEG_CHROMA_QUALITY);//OPENCV3��
	compression_params.push_back(99);
	try {
		//����������ͼ�񵽱����ļ�����ʽΪjpg
		imwrite("��imwrite���ɵ�ͼƬ.jpg", image, compression_params);
		waitKey(0);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "ͼ��ת����JPG��ʽ��������%s\n", ex.what());
	}
	/*
	//�ڶ��������ʽ����ָ��imwrite��������������debug�����б���ȡ�쳣���󣬵���release����������
	//����������ͼ�񵽱����ļ�����ʽΪjpg
	imwrite("��imwrite���ɵ�ͼƬ.jpg", image);
	waitKey(0);
	*/
}