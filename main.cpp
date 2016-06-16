#include<core.hpp>
#include <highgui.hpp>
#include<imgproc.hpp>
#include<iostream>
#include<math.h>
using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("D:/image/radon.tif",0);
    double t = getTickCount();
    //下面是不加边的算法，方阵就可以不加边
    Mat dst = src.clone();
    //注释的是加边的算法，是为了构造方阵，同时计算安全
//    int row = src.rows;
//    int col = src.cols;
//    //    int radius = ((row<col)?row:col)/2;
//    double diagonal = sqrt(2)*((row>col)?row:col);
//    int pad_height = ceil(diagonal-row);
//    int pad_width = ceil(diagonal-col);
//    int new_center_height = (row+pad_height)/2;
//    int new_center_width = (col+pad_width)/2;
//    int old_center_height = row/2;
//    int old_center_width = col/2;
//    //确定所加的边数
//    int pad_top = new_center_height-old_center_height;
//    int pad_left = new_center_width - old_center_width;
//    int pad_bottom = pad_height - pad_top;
//    int pad_right = pad_width - pad_left;
//    Mat dst;
//    copyMakeBorder(src,dst,pad_top,pad_bottom,pad_left,pad_right,BORDER_CONSTANT,Scalar::all(0));
    dst.convertTo(dst,CV_32FC1);
    int angle=360;
    Mat radon_image = Mat(dst.rows,angle,CV_32FC1);
    int center = dst.rows/2;

    float shift0[] = {  1, 0, -center,
                        0, 1, -center,
                        0, 0, 1};
    float shift1[] = {  1, 0, center,
                        0, 1, center,
                        0, 0, 1};
    Mat m0 = Mat(3,3,CV_32FC1,shift0);
    Mat m1 = Mat(3,3,CV_32FC1,shift1);
    float *theta = new float[angle];//旋转角度
    for(int t=0;t<360;t++)
    {
        theta[t]=t*CV_PI/angle;
        float R[] = {cos(theta[t]), sin(theta[t]), 0,
                     -sin(theta[t]), cos(theta[t]), 0,
                     0, 0, 1};
        Mat mR = Mat(3,3,CV_32FC1,R);
        Mat rotation = m1*mR*m0;
        Mat rotated;
        warpPerspective(dst,rotated,rotation,Size(dst.rows,dst.cols),WARP_INVERSE_MAP);
        for(int j=0;j<rotated.cols;j++)
        {
            float *p1 = radon_image.ptr<float>(j);
            for(int i=0;i<rotated.rows;i++)
            {
                float *p2 = rotated.ptr<float>(i);
                p1[t] += p2[j];
            }
        }


    }
    cout<< (double)(getTickCount()-t)/getTickFrequency()<<endl;
    normalize(radon_image,radon_image,0,1,CV_MINMAX);
    imshow("My Radon Transform",radon_image);
    waitKey();
    destroyAllWindows();

}
