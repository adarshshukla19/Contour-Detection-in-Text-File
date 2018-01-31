////#include <opencv2/opencv.hpp>
//#include "opencv2/imgcodecs.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//
//
//#include <iostream>
//#include<string>
//#include<cfloat>
//#include<iomanip>
//
//using namespace cv;
//using namespace std;
//
//float compute_skew(const char* filename)
//{
//	cout<<__func__<<endl;
//   // Load in grayscale.
//   cv::Mat src = cv::imread(filename, 0);
//   // resizing for practical reasons
////   Mat src;
////   Size size1(400, 450);
////   resize(img, src, size1);
//   cv::Size size = src.size(); //size : [2550 x 3300] , image size
//   cout<<"size.width : "<<size.width<<endl<<"size.height : "<<size.height<<endl;
//   if(!size.empty())
//   {
//   cv::bitwise_not(src, src);
//   std::vector<cv::Vec4i> lines;
//   /*HoughLinesP parameters
//    * src 		- source image
//    * lines		- vector of 4 points
//    * 1			- Distance resolution of the accumulator in pixels.
//    * CV_PI/180	- 1 degree to radient
//    * size.width / 2.f	-minimum length size.width : 2550 , 2.f is 2.0 as float
//    */
//   cv::HoughLinesP(src, lines, 1, CV_PI/180, 100, size.height/1.1f, 20);
//   cv::Mat disp_lines(size, CV_8UC1, cv::Scalar(0, 0, 0));
//   double angle = 0.,current_angle=0.,y_axis=0.,x_axis=0.;
//   unsigned nb_lines = lines.size();
//   int vertical_lines=0,delta_x_max=0;
//   cout<<"nb_lines : "<<nb_lines<<"\t\t"<<endl;
//   for (unsigned i = 0; i < nb_lines; ++i)
//   {
//	   //void line(InputOutputArray img, Point pt1, Point pt2, const Scalar& color,
//	   	   	   //int thickness = 1, int lineType = LINE_8, int shift = 0);
//	   //draw a line
//       cv::line(disp_lines, cv::Point(lines[i][0], lines[i][1]),
//                cv::Point(lines[i][2], lines[i][3]), cv::Scalar(255, 0 ,0));
//      cout<<"Line["<<i<<"]"<<endl<<"X0 : "<<lines[i][0]<<"\tY0 : "<<lines[i][1]<<"\n"<<"X1 : "<<lines[i][2]<<"\tY1 : "<<lines[i][3]<<"\t"<<endl;
//
//       y_axis=(double)lines[i][3] - lines[i][1];
//       x_axis=(double)lines[i][2] - lines[i][0];
//       //__MATHCALL (atan2,, (_Mdouble_ __y, _Mdouble_ __x));
//       current_angle= atan2(y_axis,x_axis);
//       cout<<"current angle "<<current_angle<<"\ty_axis : "<<y_axis<<"\tx_axis : "<<x_axis<<"\n\n";
//       angle+=current_angle;
//       if(delta_x_max<x_axis && (y_axis<200))
//    	   delta_x_max=x_axis;
//       if(x_axis<150)
//    	   vertical_lines++;
//
//   }
//   cout<<"vertical lines : "<<vertical_lines<<"\t delta x max : "<<delta_x_max<<endl;
//   angle /= nb_lines; // mean angle, in radians.
//
//   std::cout <<"compute skew : "<<endl<< "File " << filename << ": " << angle * 180 / CV_PI << std::endl;
//
//   cv::imshow(filename, disp_lines);
//   cv::waitKey(0);
//   cv::destroyWindow(filename);
//   return (angle * 180 / CV_PI);
//   }
//   else
//	   cout<<"size is empty"<<endl;
//   return 0;
//}
//
//void deskew(const char* filename, double angle)
//{
//	cout<<"deskew() : angl : "<<angle<<endl;
//  cv::Mat img = cv::imread(filename, 0);
//      // resizing for practical reasons
////      Mat img;
////      Size size(400, 450);
////      resize(src, img, size);
//
//  cv::bitwise_not(img, img);
//
//  std::vector<cv::Point> points;
//  cv::Mat_<uchar>::iterator it = img.begin<uchar>();
//  cv::Mat_<uchar>::iterator end = img.end<uchar>();
//  for (; it != end; ++it)
//    if (*it)
//      points.push_back(it.pos());
//
//  cv::RotatedRect box = cv::minAreaRect(cv::Mat(points));
//  cv::Mat rot_mat = cv::getRotationMatrix2D(box.center, angle, 1);
//  cv::Mat rotated;
//  cv::warpAffine(img, rotated, rot_mat, img.size(), cv::INTER_CUBIC);
//  cv::Size box_size = box.size;
//  if (box.angle < -45.)
//    std::swap(box_size.width, box_size.height);
//  cv::Mat cropped;
//  cv::getRectSubPix(rotated, box_size, box.center, cropped);
//  cv::imshow("Original", img);
//  cv::waitKey(0);
//  cv::imshow("Rotated", rotated);
//  cv::waitKey(0);
//  cv::imshow("Cropped", cropped);
//  cv::waitKey(0);
//  cv::bitwise_not(rotated, rotated);
//  //imwrite("/home/saumitra/Test_pdf/rotated.jpg",rotated);
//}
//int detect_table(const char* filename)
//{
//
//	Mat src = imread(filename,1);
//	   cv::Size size1 = src.size(); //size : [2550 x 3300] , image size
//	   cout<<"size.width : "<<size1.width<<endl<<"size.height : "<<size1.height<<endl;
//
//	cout<<"no of columns in the image read "<<src.cols<<endl;
//
//	// Check for failure
//	if (!src.data)
//	{
//		cout << "Could not open or find the image" << endl;
//		cin.get(); //wait for any key press
//		return -1;
//	}
//
//    // resizing for practical reasons
//    Mat rsz;
//   // Size size(800, 900);
//    //resize(src, rsz, size);
//rsz=src;
//    imshow("rsz", rsz);
//	// Transform source image to gray if it is not
//	Mat gray;
//
//	if (rsz.channels() == 3)
//	{
//		cvtColor(rsz, gray, CV_BGR2GRAY);
//	}
//	else
//	{
//		gray = rsz;
//	}
//
//	 //Show gray image
//	 imshow("gray", gray);
//	 waitKey(0); // Wait for any keystroke in the window
//
//	// Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
//	Mat bw;
//	adaptiveThreshold(~gray, bw, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
//	imshow("binary", bw);
//	waitKey(0);
//
//	// Create the images that will use to extract the horizonta and vertical lines
//	Mat horizontal = bw.clone();
//	Mat vertical = bw.clone();
//
//	int scale = 3; // play with this variable in order to increase/decrease the amount of lines to be detected
//
//	// Specify size on horizontal axis
//	int horizontalsize = horizontal.cols / scale;
//	cout<<"horizontalsize : "<<horizontalsize<<endl;
//
//	// Create structure element for extracting horizontal lines through morphology operations
//	Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize,1));
//
//	// Apply morphology operations
//	erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
//	dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
//	//    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1)); // expand horizontal lines
//
//	// Show extracted horizontal lines
//	imshow("horizontal", horizontal);
//	waitKey(0);
//
//    // Specify size on vertical axis
//    int verticalsize = vertical.rows / scale;
//
//    // Create structure element for extracting vertical lines through morphology operations
//    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size( 1,verticalsize));
//
//    // Apply morphology operations
//    erode(vertical, vertical, verticalStructure, Point(-1, -1));
//    dilate(vertical, vertical, verticalStructure, Point(-1, -1));
////    dilate(vertical, vertical, verticalStructure, Point(-1, -1)); // expand vertical lines
//
//    // Show extracted vertical lines
//    imshow("vertical", vertical);
//	waitKey(0);
//
//    // create a mask which includes the tables
//    Mat mask = horizontal + vertical;
//    imshow("mask", mask);
//	waitKey(0);
//
//    // find the joints between the lines of the tables, we will use this information in order to descriminate tables from pictures (tables will contain more than 4 joints while a picture only 4 (i.e. at the corners))
//    Mat joints;
//    bitwise_and(horizontal, vertical, joints);
//    imshow("joints", joints);
//	waitKey(0);
//
//
//    // Find external contours from the mask, which most probably will belong to tables or to images
//    vector<Vec4i> hierarchy;
//    std::vector<std::vector<cv::Point> > contours;
//    cv::findContours(mask, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//    //CV_EXPORTS_W void findContours( InputOutputArray image, OutputArrayOfArrays contours,OutputArray hierarchy, int mode,int method, Point offset = Point());
//
//
//    vector<vector<Point> > contours_poly( contours.size() );
//    vector<Rect> boundRect( contours.size() ),boundRect_row;
//    Rect current_row;
//    cout<<"contours.size() : "<<contours.size()<<endl;
//    vector<Mat> rois,rois_row;
//
//    for (size_t i = 0; i < contours.size(); i++)
//    {
//        // find the area of each contour
//        double area = contourArea(contours[i]);
//        cout<<"contorus "<<i <<"size : "<<contours[i].size()<<endl ;
////        for (int j=0;j<contours[i].size();j++)
////        {
////        	cout<<"point "<<j<<"\tx: "<<contours[i][j].x<<"\ty : "<<contours[i][j].y<<endl;
////        }
//        //cout<<"countor["<<i<<"] area : "<<area<<endl;
//
////        // filter individual lines of blobs that might exist and they do not represent a table
//
//        if(area < 100) // value is randomly chosen, you will need to find that by yourself with trial and error procedure
//            continue;
//
//        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
//        cout<<"Contorus_poly [i] .size()"<<contours_poly[i].size()<<endl;
//                for (int j=0;j<contours_poly[i].size();j++)
//                {
//                	cout<<"point "<<j<<"\tx: "<<contours_poly[i][j].x<<"\ty : "<<contours_poly[i][j].y<<endl;
//                }
//        boundRect[i] = boundingRect( Mat(contours_poly[i]) );
//
//        // find the number of joints that each table has
//        Mat roi = joints(boundRect[i]);
//
//        vector<vector<Point> > joints_contours;
//        findContours(roi, joints_contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//
//        // if the number is not more than 5 then most likely it not a table
////        if(joints_contours.size() <= 4)
////            continue;
//        cout<<"pushing boundRect : x "<<boundRect[i].x<<"\t boundRect.y : "<<boundRect[i].y<<"\tboundRect[i].height : "<<boundRect[i].height<<"\tboundRect[i].width : "<<boundRect[i].width<<endl;
//        rois.push_back(rsz(boundRect[i]).clone());
//
////        drawContours( rsz, contours, i, Scalar(0, 0, 255), CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
//        rectangle( rsz, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 0, 0), 2, 8, 0 ); //Scalar(0, 0, 0) - black ; RGB color schema
//    }
//    cout<<"boundRect.size() : "<<boundRect.size()<<endl;
//
//    //create rows
//    int prevY=boundRect[boundRect.size()-1].y;
//    for(int i=boundRect.size()-1;i>=0;i--)
//    {
//    	if(prevY==boundRect[i].y && i!=0)
//    	{
//    		//update current row rectangle
//    		current_row.y=boundRect[i].y;
//    		current_row.height=boundRect[i].height;
//    		current_row.width+=boundRect[i].width;
//    	}
//    	else if (i==0){
//    		cout<<"executing for i=0	----------------------------------------------------------"<<endl;
//    		//current_row.x=boundRect[i].x;
//    		current_row.y=boundRect[i].y;
//    		current_row.height=boundRect[i].height;
//    		current_row.width+=boundRect[i].width;
//    		cout<<"values for last rows are :"<<endl<<"current_row.x : "<<current_row.x<<"\tcurrent_row.y : "<<current_row.y
//    				<<"\t current_row.height : "<<current_row.height<<"\tcurrent_row.width"<<current_row.width<<endl;
//    		boundRect_row.push_back(current_row);
//    		cout<<"pushed to boundRect_row"<<endl;
//            imshow("last row ", (rsz(current_row).clone()));
//            waitKey();
//    		rois_row.push_back(rsz(current_row).clone());
//    		cout<<"pushed to rois_row"<<endl;
//
//
//    	}
//    	else
//    	{
//    		//push current row rectangle
//    		cout<<"changin row here =============================================="<<endl;
//
//
//    		current_row.x=boundRect[i].x; // updating last x read in sequence (this should be beginning of row)
//    		boundRect_row.push_back(current_row);
//    		rois_row.push_back(rsz(current_row).clone());
//    		cout<<"values for current rows are :"<<endl<<"current_row.x : "<<current_row.x<<"\tcurrent_row.y : "<<current_row.y
//    		    				<<"\t current_row.height : "<<current_row.height<<"\tcurrent_row.width"<<current_row.width<<endl;
//
//
//
//        	cout<<"\t and y = "<<boundRect[i].y<<endl;
//
//        	prevY=boundRect[i].y;
//
//        	current_row.width=0;// reset current row width
//
//        	//update first cell of new row
//    		current_row.y=boundRect[i].y;
//    		current_row.height=boundRect[i].height;
//    		current_row.width+=boundRect[i].width;
//    	}
//    	cout<<"updating rois_row for i : "<<i<<endl;
//
//
//    }
//
//
////    for(int i = rois.size()-1; i >=0 ; --i)
////    {
////        /* Now you can do whatever post process you want
////         * with the data within the rectangles/tables. */
////    	const string roi_win="ROI";
////        imshow(roi_win, rois[i]);
////        waitKey();
////    }
//    cout<<"rois_row.size() : "<<rois_row.size()<<endl;
//    for(int  i = 0; i <rois.size() ; i++)
//    {
//        /* Now you can do whatever post process you want
//         * with the data within the rectangles/tables. */
//    	const string roi_win="ROI";
//        imshow(roi_win, rois[i]);
//        waitKey();
//        string img_file="/home/saumitra/Pdf_Bank_Statements/cell_out/Cell-"+std::to_string(i)+".jpg";
//
//
//        imwrite( img_file.c_str(), rois[i]);
//    }
//
//    imshow("contours", rsz);
//    waitKey();
//    return 0;
//}
//
////int main(int argc, char** argv)
////{
////	// Read the image file
////	// Load source image
////	float angl=0.0f;
////	//string filename = "/home/saumitra/Test_pdf/3_1out-3.jpg";
////	//	angl=compute_skew("/home/saumitra/Test_pdf/3_1out-1.jpg");
////	//	waitKey(0);
////	//	deskew("/home/saumitra/Test_pdf/3_1out-1.jpg",angl);
////
////
////	string filename = "/home/adarsh/Downloads/Row1.jpg";//good scanned image
////	//string filename = "/home/saumitra/Test_pdf/rotated.jpg"; //rotated image 5 deg
////	//deskew(filename.c_str(),2);
////
////	//angl=compute_skew(filename.c_str());
////	//cout<<"angl returned : "<<angl<<endl;
////	//angl=(angl+90);
//////	if(angl){
//////		cout<<"Deskewing the file  : "<<endl;
//////		deskew(filename.c_str(),angl);
//////
//////	}
////	detect_table(filename.c_str());
////	cout<<setprecision (4)<<"cout angle of image : "<<angl;
////	return 0;
////}
