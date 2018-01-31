//#include "opencv2/imgproc.hpp"
////#include <opencv2/imgcodecs.hpp>
//#include "opencv2/highgui.hpp"
//#include "opencv2/core/core.hpp"
//#include "opencv2/opencv.hpp"
//#include <iostream>
////#include<string>
////#include<cfloat>
////#include<iomanip>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//    // Read image
//   Mat3b img = imread("/home/adarsh/Downloads/temp1.jpeg");
//    //Mat3b img = imread("/home/adarsh/Downloads/Row.jpg");
//
//	//Mat3b img = imread("/home/adarsh/Downloads/Cell-13.jpg");
//	//Mat3b img = imread("/home/adarsh/Downloads/image.png");
//
//
//
//    // Binarize image. Text is white, background is black
//    Mat1b bin;
//    cvtColor(img, bin, COLOR_BGR2GRAY);
//    bin = bin < 200;
//    imshow("bin",bin);
//    //Size size(800, 900);
//    //resize(bin, bin, size);
//    waitKey();
//
//
//    // Find all white pixels
//    vector<Point> pts;
//    findNonZero(bin, pts);
////    for (int i = 0; i < pts.size(); i++) {
////               cout << "the value of points are "<<pts[i] << "\n ";
////           }
//
//    // Get rotated rect of white pixels
//   RotatedRect box = minAreaRect(pts);
//   //if (box.size.width > box.size.height)
//   if (box.size.height > box.size.width)
//    {
//        swap(box.size.width, box.size.height);
//        box.angle += 90.f;
//        cout<<"the size of the box is:"<<box.size.width <<","<<box.size.height;
//    }
//
//
//    Point2f vertices[4];
//    box.points(vertices);
//
//    for (int i = 0; i < 4; ++i)
//    {
//        line(img, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0));
//        cout<<"the vertices for the box found are:"<<vertices[i]<< ","<<"\n";
//    }
//
//    // Rotate the image according to the found angle
//    Mat1b rotated;
//    Mat M = getRotationMatrix2D(box.center, box.angle, 1.0);
//    warpAffine(bin, rotated, M, bin.size());
//    imshow("a",bin);
//    waitKey();
//
//
//    // Compute horizontal projections
//    Mat1f horProj;
//    reduce(rotated, horProj, 1, CV_REDUCE_AVG);
//    imshow("d",horProj);
//    waitKey();
//
//
//    // Remove noise in histogram. White bins identify space lines, black bins identify text lines
//    float th = 0;
//    Mat1b hist = horProj <= th;
//
//    // Get mean coordinate of white white pixels groups
//    vector<int> ycoords;
//    int y = 0;
//    int count = 0;
//    bool isSpace = false;
//    for (int i = 0; i < rotated.rows; ++i)
//    {
//        if (!isSpace)
//        {
//            if (hist(i))
//            {
//                isSpace = true;
//                count = 1;
//                y = i;
//            }
//        }
//        else
//        {
//            if (!hist(i))
//            {
//                isSpace = false;
//                ycoords.push_back(y / count);
//            }
//            else
//            {
//                y += i;
//                count++;
//            }
//        }
//    }
//
//    // Draw line as final result
//    Mat3b result;
//    cvtColor(rotated, result, COLOR_GRAY2BGR);
//    cout<<"ycoords.size() : "<<ycoords.size()<<endl;
//    for (int i = 0; i < ycoords.size(); ++i)
//    {
//    	cout<<"for i= "<<i<<endl;
//    	cout<<"x1 : 0"<<"\ty1 : "<<ycoords[i]<<"\tx2 : "<<result.cols<<"\ty2 : "<<ycoords[i]<<endl;
//        line(result, Point(0, ycoords[i]), Point(result.cols, ycoords[i]), Scalar(0, 255, 0));
//        imshow("result",result);
//        waitKey();
//    }
//
//
////     Size size(800, 900);
////     resize(result, result, size);
//
//    imshow("result",result);
//    waitKey();
//    return 0;
//}
