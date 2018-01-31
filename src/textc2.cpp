#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>
using namespace std;
using namespace cv;

//int main ()
//{
//	cv::Mat my(cv::Size(800, 800), CV_64FC1, Scalar(255));
//    Rect b;
//    b.x=0;
//    b.y=0;
//    b.width=my.cols/2;
//    b.height=my.rows/2;
//    my = 255;
//    rectangle(my,b,Scalar(0,0,0),2);
////    imshow("5rects", my);
////    	waitKey();
//
//    	Rect c;
//    	c.x=b.width;
//    	c.y=b.height;
//    	c.width=my.cols;
//    	c.height=my.rows;
//    	rectangle(my,c,Scalar(0,0,0),2);
//    	    imshow("5rects", my);
//    	    	waitKey();
//}

//Mat3b dbg;
//
//vector<Rect> XYCut_projH(const Mat1b& src, Rect roi)
//{
//    rectangle(dbg, roi, Scalar(255, 0, 0));
//
//    Mat1b projH;
//    reduce(src(roi), projH, 1, CV_REDUCE_MAX);
//
//    vector<Rect> rects;
//
//    bool bOut = true;
//    vector<int> coords;
//
//    for (int i = 0; i < projH.rows; ++i)
//    {
//        if (bOut && projH(i) > 0)
//        {
//            coords.push_back(i);
//            bOut = false;
//        }
//        else if (!bOut && projH(i) == 0)
//        {
//            coords.push_back(i);
//            bOut = true;
//        }
//    }
//
//    if (!bOut)
//    {
//        coords.push_back(projH.rows);
//    }
//
//
//    for (int i = 0; i < coords.size() - 1; i += 2)
//    {
//        Rect r(0, coords[i], src.cols, coords[i + 1] - coords[i]);
//        r = (r + roi.tl()) & roi;
//        rects.push_back(r);
//
//        rectangle(dbg, r, Scalar(0, 255, 0));
//    }
//
//    if ((rects.size() == 1) && (rects[0] == roi))
//    {
//        return vector<Rect>();
//    }
//
//    return rects;
//}
//
//vector<Rect> XYCut_projV(const Mat1b& src, Rect roi)
//{
//    rectangle(dbg, roi, Scalar(255, 0, 0));
//
//    Mat1b projV;
//    reduce(src(roi), projV, 0, CV_REDUCE_MAX);
//
//    vector<Rect> rects;
//
//    bool bOut = true;
//    vector<int> coords;
//
//    for (int i = 0; i < projV.cols; ++i)
//    {
//        if (bOut && projV(i) > 0)
//        {
//            coords.push_back(i);
//            bOut = false;
//        }
//        else if (!bOut && projV(i) == 0)
//        {
//            coords.push_back(i);
//            bOut = true;
//        }
//    }
//
//    if (!bOut)
//    {
//        coords.push_back(projV.cols);
//    }
//
//    for (int i = 0; i < coords.size() - 1; i += 2)
//    {
//        Rect r(coords[i], 0, coords[i + 1] - coords[i], src.rows);
//        r = (r + roi.tl()) & roi;
//        rects.push_back(r);
//
//        rectangle(dbg, r, Scalar(0, 255, 0));
//    }
//
//    if ((rects.size() == 1) && (rects[0] == roi))
//    {
//        return vector<Rect>();
//    }
//
//    return rects;
//}
//
//void XYCut_step(const Mat1b& src, Rect roi, vector<Rect>& rects, bool bAlternate)
//{
//    vector<Rect> step;
//    if (bAlternate)
//    {
//        step = XYCut_projH(src, roi);
//
//        if (step.empty())
//        {
//            rects.push_back(roi);
//            return;
//        }
//    }
//    else
//    {
//        step = XYCut_projV(src, roi);
//
//        if (step.empty())
//        {
//            rects.push_back(roi);
//            return;
//        }
//    }
//
//    for (int i = 0; i < step.size(); ++i)
//    {
//        XYCut_step(src, step[i], rects, !bAlternate);
//    }
//}
//
//void XYCut(const Mat1b& src, vector<Rect>& rects)
//{
//    bool bAlternate = true;
//    Rect roi(0, 0, src.cols, src.rows);
//
//    XYCut_step(src, roi, rects, bAlternate);
//}
//
//int ed2(const Point& lhs, const Point& rhs)
//{
//    return (lhs.x - rhs.x)*(lhs.x - rhs.x) + (lhs.y - rhs.y)*(lhs.y - rhs.y);
//}
//
//int main()
//{
//    // Load image
//    //Mat1b img = imread("//home/adarsh/Downloads/image.png", IMREAD_GRAYSCALE);
//    //Mat1b img = imread("//home/adarsh/Downloads/page-1.jpg", IMREAD_GRAYSCALE);
//    //Mat1b img = imread("//home/adarsh/Downloads/Row.jpg", IMREAD_GRAYSCALE);
//
//	//Mat1b img = imread("//home/adarsh/Downloads/ZJpj2.png", IMREAD_GRAYSCALE);
//	//Mat1b img = imread("//home/adarsh/Downloads/temp.jpeg", IMREAD_GRAYSCALE);
//	//Mat1b img = imread("//home/adarsh/Downloads/Cell-4.jpeg", IMREAD_GRAYSCALE);
//	//Mat1b img = imread("//home/adarsh/Downloads/hi2.png", IMREAD_GRAYSCALE);
//	Mat1b img = imread("//home/adarsh/Downloads/Row1.jpg", IMREAD_GRAYSCALE);
//	//Mat1b img = imread("//home/adarsh/Downloads/23/CITIBANK/out.tif", IMREAD_GRAYSCALE);
//
//
//
//    cvtColor(img, dbg, COLOR_GRAY2BGR);
//
//    // invert image, if needed
//    img = ~img;
//    //Mat blurred;
//    // Apply XY Cut
//    vector<Rect> rects;
//    XYCut(img, rects);
//
//    // Show XY results
//    Mat3b xyres;
//    cvtColor(img, xyres, COLOR_GRAY2BGR);
//    for (int i = 0; i < rects.size(); ++i)
//    {
//        rectangle(xyres, rects[i], Scalar(0, 0, 255), 2);
//
//    }
//
//
////    Size size2(700, 800);
////    resize(xyres, xyres, size2);
//    imshow("XY-Cut Result", xyres);
//    waitKey();
//    ofstream of1("/home/adarsh/Downloads/text1.txt");
//    of1<<xyres;
//
//
//    Rect a;
//    a.width= xyres.cols;
//    a.height= xyres.rows;
//    cout<< "Height = "<<a.height<< "and Width = "<<a.width;
//
//    xyres.rows= a.height-5;
//
//    imshow("bottom border cut", xyres);
//    waitKey();
//
////    a.y= xyres.cols;
////    a.x= xyres.rows;
//    cout<<"the x coord of the table are: "<<a.x<<"and the y coord of the table are: "<<a.y;
//    xyres.cols= a.width-5;
////    imshow("side border cut", xyres);
////    waitKey();
//
//
//
////    for (int i = 0; i < rects.size(); ++i)
////       {
////    	rectangle(my, rects[i], Scalar(255, 0, 0), 2);
////       }
////    	imshow("border cut", my);
////    	waitKey();
//
//
//
//    // Remove small bounding boxes (noise)
//    int min_area = 10;
//    vector<Rect> filteredRects;
//
//    //vector iterator
//
////    std::vector<int> myvector;
////      for (int i=1; i<=5; i++) {
////
////    	  myvector.push_back(i);
////
////      }
//
//      //std::cout << "myvector contains:";
//      for (std::vector<Rect>::iterator it = rects.begin() ; it != rects.end(); ++it){
//    	  //std::cout << ' ' << *it;
//    	  if ((*it).area() > min_area)
//    	         {
//    		  	  	//  cout<<"the area is: " <<(*it).area<< endl;
//    	             filteredRects.push_back(*it);
//    	         }
//      }
//
//
//      std::cout << '\n';
//
//
////    for (const auto& r : rects)
////    {
////        if (r.area() > min_area)
////        {
////            filteredRects.push_back(r);
////        }
////    }
//
//    // Show Filtered results
//    Mat3b filtres;
//    cvtColor(img, filtres, COLOR_GRAY2BGR);
//    for (int i = 0; i < filteredRects.size(); ++i)
//    {
//        rectangle(filtres, filteredRects[i], Scalar(255, 0, 0), 2);
//    }
//
////    Size size(700, 800);
////        resize(filtres, filtres, size);
//    imshow("Filtered Result", filtres);
//    waitKey();
//
//
//
//    // Group near rectangles
//    int max_distance = 10;
//
//    vector<int> labels;
//    int max_distance2 = max_distance*max_distance;
//    int n_labels = partition(filteredRects, labels, [max_distance2](const Rect& lhs, const Rect& rhs)
//    {
//        if (ed2(lhs.tl(), Point(rhs.br().x, rhs.tl().y)) < max_distance2) { return true; }
//        if (ed2(rhs.tl(), Point(lhs.br().x, lhs.tl().y)) < max_distance2) { return true; }
//        return false;
//    });
//
//    // Make a bounding box for rects grouped together
//    vector<vector<Point>> pts(n_labels);
//    for (int i = 0; i < filteredRects.size(); ++i)
//    {
//        pts[labels[i]].push_back(filteredRects[i].tl());
//        pts[labels[i]].push_back(filteredRects[i].br());
//    }
//
//    // Show Grouped results
//    vector<Rect> groupedRects(n_labels);
//    for (int i = 0; i < pts.size(); ++i)
//    {
//        groupedRects[i] = boundingRect(pts[i]);
//    }
//
//
//    // Show Grouped results
//    Mat3b groupres;
//    cvtColor(img, groupres, COLOR_GRAY2BGR);
//    for (int i = 0; i < groupedRects.size(); ++i)
//    {
//        rectangle(groupres, groupedRects[i], Scalar(0, 255, 0), 2);
//    }
//
////    Size size1(700, 800);
////    resize(groupres, groupres, size1);
//    imshow("Grouped Result", groupres);
//
//
//    waitKey();
//
//
//
//    return 0;
//}
