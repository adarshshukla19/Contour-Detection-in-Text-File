#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include<string>
#include<cfloat>
#include<iomanip>

using namespace cv;
using namespace std;


int main()
{
	// Read the image file
	// Load source image
	Mat src = imread("/home/adarsh/Downloads/single page img/axis-1.tif",0);

	 Mat rsz;
	 Size size(800, 900);
	 //resize(src, rsz, size);
	 rsz=src;
	     imshow("rsz", rsz);
	 	// Transform source image to gray if it is not
	 	Mat gray;

	 	if (rsz.channels() == 3)
	 	{
	 		cvtColor(rsz, gray, CV_BGR2GRAY);
	 	}
	 	else
	 	{
	 		gray = rsz;
	 	}

	 	 //Show gray image

	 	//resize(gray, rsz, size);
	 	 imshow("gray", gray);
	 	 waitKey(0); // Wait for any keystroke in the window
	 	 Mat bw;
	 		adaptiveThreshold(~gray, bw, 255, CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	 		resize(rsz, bw, size);
	 		imshow("binary", bw);
	 		waitKey(0);
	 		Mat horizontal = bw.clone();
	 			Mat vertical = bw.clone();

	 			int scale = 15; // play with this variable in order to increase/decrease the amount of lines to be detected

	 			// Specify size on horizontal axis
	 			int horizontalsize = horizontal.cols / scale;
	 			cout<<"horizontalsize : "<<horizontalsize<<endl;

	 			// Create structure element for extracting horizontal lines through morphology operations
	 			Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontalsize,1));

	 			// Apply morphology operations
	 			erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
	 			dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));
	 			//    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1)); // expand horizontal lines

	 			// Show extracted horizontal lines
	 			imshow("horizontal", horizontal);
	 			waitKey(0);

	 		    // Specify size on vertical axis
	 		    int verticalsize = vertical.rows / scale;

	 		    // Create structure element for extracting vertical lines through morphology operations
	 		    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size( 1,verticalsize));

	 		    // Apply morphology operations
	 		    erode(vertical, vertical, verticalStructure, Point(-1, -1));
	 		    dilate(vertical, vertical, verticalStructure, Point(-1, -1));
	 		    dilate(vertical, vertical, verticalStructure, Point(-1, -1)); // expand vertical lines

	 		    // Show extracted vertical lines
	 		    imshow("vertical", vertical);
	 			waitKey(0);
	 			// create a mask which includes the tables
	 			    Mat mask = horizontal + vertical;
	 			    imshow("mask", mask);
	 				waitKey(0);

	 				// Find external contours from the mask, which most probably will belong to tables or to images
	 				    vector<Vec4i> hierarchy;
	 				    std::vector<std::vector<cv::Point> > contours;
	 				    cv::findContours(mask, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	 				    //CV_EXPORTS_W void findContours( InputOutputArray image, OutputArrayOfArrays contours,OutputArray hierarchy, int mode,int method, Point offset = Point());

	 				   vector<vector<Point> > contours_poly( contours.size() );
	 				      vector<Rect> boundRect( contours.size() ),boundRect_row;
	 				      Rect current_row;
	 				      cout<<"contours.size() : "<<contours.size()<<endl;
	 				      vector<Mat> rois,rois_row;
	 				     Mat joints;

	 				    for (size_t i = 0; i < contours.size(); i++)
	 				    {
	 				        // find the area of each contour
	 				        double area = contourArea(contours[i]);
	 				        cout<<"contours "<<i <<"\tsize : "<<contours[i].size()<<endl ;
	 				        for (int j=0;j<contours[i].size();j++)
	 				        {
	 				        	cout<<"point "<<j<<"\tx: "<<contours[i][j].x<<"\ty : "<<contours[i][j].y<<endl;
	 				        }
	 				        cout<<"countor["<<i<<"] area : "<<area<<endl;

	 				       // filter individual lines of blobs that might exist and they do not represent a table

	 				        if(area < 100) // value is randomly chosen, you will need to find that by yourself with trial and error procedure
	 				            continue;

	 				        approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
	 				        cout<<"Contours_poly [i] .size()"<<contours_poly[i].size()<<endl;
	 				                for (int j=0;j<contours_poly[i].size();j++)
	 				                {
	 				                	cout<<"point "<<j<<"\t x: "<<contours_poly[i][j].x<<"\ty : "<<contours_poly[i][j].y<<endl;
	 				                }
	 				        boundRect[i] = boundingRect( Mat(contours_poly[i]) );

	 				        // find the number of joints that each table has
	 				        Mat roi = joints(boundRect[i]);

	 				        vector<vector<Point> > joints_contours;
	 				        findContours(roi, joints_contours, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

	 				        // if the number is not more than 5 then most likely it not a table
	 				        if(joints_contours.size() <= 4)
	 				        continue;
	 				        cout<<"pushing boundRect : x "<<boundRect[i].x<<"\t boundRect.y : "<<boundRect[i].y<<"\tboundRect[i].height : "<<boundRect[i].height<<"\tboundRect[i].width : "<<boundRect[i].width<<endl;
	 				        rois.push_back(rsz(boundRect[i]).clone());

	 				        drawContours( rsz, contours, i, Scalar(0, 0, 255), CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
	 				        rectangle( rsz, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 0, 0), 2, 8, 0 ); //Scalar(0, 0, 0) - black ; RGB color schema
	 				    }
	 				    cout<<"boundRect.size() : "<<boundRect.size()<<endl;

	 				    //create rows
	 				    int prevY=boundRect[boundRect.size()-1].y;
	 				    for(int i=boundRect.size()-1;i>=0;i--)
	 				    {
	 				    	if(prevY==boundRect[i].y && i!=0)
	 				    	{
	 				    		//update current row rectangle
	 				    		current_row.y=boundRect[i].y;
	 				    		current_row.height=boundRect[i].height;
	 				    		current_row.width+=boundRect[i].width;
	 				    	}
	 				    	else if (i==0){
	 				    		cout<<"executing for i=0	----------------------------------------------------------"<<endl;
	 				    		current_row.x=boundRect[i].x;
	 				    		current_row.y=boundRect[i].y;
	 				    		current_row.height=boundRect[i].height;
	 				    		current_row.width+=boundRect[i].width;
	 				    		cout<<"values for last rows are :"<<endl<<"current_row.x : "<<current_row.x<<"\tcurrent_row.y : "<<current_row.y
	 				    				<<"\t current_row.height : "<<current_row.height<<"\tcurrent_row.width"<<current_row.width<<endl;
	 				    		boundRect_row.push_back(current_row);
	 				    		cout<<"pushed to boundRect_row"<<endl;
	 				            imshow("last row ", (rsz(current_row).clone()));
	 				            waitKey();
	 				    		rois_row.push_back(rsz(current_row).clone());
	 				    		cout<<"pushed to rois_row"<<endl;


	 				    	}
	 				    	else
	 				    	{
	 				    		//push current row rectangle
	 				    		cout<<"changin row here =============================================="<<endl;


	 				    		current_row.x=boundRect[i].x; // updating last x read in sequence (this should be beginning of row)
	 				    		boundRect_row.push_back(current_row);
	 				    		rois_row.push_back(rsz(current_row).clone());
	 				    		cout<<"values for current rows are :"<<endl<<"current_row.x : "<<current_row.x<<"\tcurrent_row.y : "<<current_row.y
	 				    		    				<<"\t current_row.height : "<<current_row.height<<"\tcurrent_row.width"<<current_row.width<<endl;



	 				        	cout<<"\t and y = "<<boundRect[i].y<<endl;

	 				        	prevY=boundRect[i].y;

	 				        	current_row.width=0;// reset current row width

	 				        	//update first cell of new row
	 				    		current_row.y=boundRect[i].y;
	 				    		current_row.height=boundRect[i].height;
	 				    		current_row.width+=boundRect[i].width;
	 				    	}
	 				    	cout<<"updating rois_row for i : "<<i<<endl;


	 				    }






	return 0;
}
