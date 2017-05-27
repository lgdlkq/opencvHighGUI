 #include"all.h"

//����һ��͸��pngͼƬ
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
	//������Alphaͨ����Mat
	Mat mat(480, 640, CV_8UC4);
	createAlphaMat(mat);

	vector<int>compression_params;
	//����ͼƬ��ʽ���˴�����ΪPNG����������imwrite�е����Ӧ
	//compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);//OPENCV2��
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);//OPENCV3��
	compression_params.push_back(9);//����ͼƬ�ߴ磬ֵԽСѹ��ʱ��Խ����PNGĬ��ֵΪ3��JPEGΪ95��PPM��PGM��PBMΪ1������0��1

	try{
		imwrite("͸��Alphaֵͼ.png", mat, compression_params);//ȱ��compression_params�������д���
		imshow("���ɵ�PNGͼ",mat);
		fprintf(stdout, "PNGͼƬ�ļ���alpha���ݱ������~\n�����ڹ���Ŀ¼�²鿴��imwrite�������ɵ�ͼƬ\n");
		waitKey(0);
	}
	catch (runtime_error& ex){
		fprintf(stderr, "ͼ��ת����PNG��ʽ��������%s\n", ex.what());
	}
}