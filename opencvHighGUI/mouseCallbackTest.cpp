#include"all.h"

#define WINDOW_NAME "�����򴰿ڡ�"

Rect g_rectangle;
bool g_bDrawingBox = false;//�Ƿ���л���
RNG g_rng(12345);//�������RNG

//���ص���������������¼��Ĳ�ͬ���в�ͬ�Ĳ���
void on_MouseHandle(int event, int x, int y, int flags, void* param) {
	Mat& image = *(Mat*)param;
	switch (event)
	{
		//����ƶ���Ϣ
	case EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox) {//����Ƿ���л��Ƶı�ʾ��Ϊ�棬���¼�³��Ϳ���RECT�ͱ�����
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;
	//���������Ϣ
	case EVENT_LBUTTONDOWN:
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);//��¼��ʼ��
	}
	break;
	//���̧����Ϣ
	case EVENT_LBUTTONUP:
	{
		g_bDrawingBox = false;//�ñ�ʾ��Ϊfalse
		//���ڿ��͸�С��0���еĴ���
		if (g_rectangle.width < 0) {
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if (g_rectangle.height < 0) {
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//���ú������л���
		DrawRectangle(image, g_rectangle);
	}
	break;
	}
}

//�Զ���ľ��λ��ƺ���
void DrawRectangle(Mat& img, Rect box) {
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255),
		g_rng.uniform(0, 255), g_rng.uniform(0, 255)));//�����ɫ
}

void testMouseCallback() {
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);

	//�����������ص�����
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

	//������ѭ���������л��Ƶı�ʾ��Ϊ��ʱ�����л���
	while (1) {
		srcImage.copyTo(tempImage);//����Դͼ����ʱ����
		if (g_bDrawingBox)DrawRectangle(tempImage, g_rectangle);//�����л��Ƶı�ʾ��Ϊ��ʱ�����л���
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27) break;//����ESC�������˳�
	}
}