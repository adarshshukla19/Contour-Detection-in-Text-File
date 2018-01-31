//#include <opencv2/core.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//#define w 400
//
//using namespace cv;
//
//void MyEllipse( Mat img, double angle );
//void MyFilledCircle( Mat img, Point center );
//
//int main( void ){
//
//	 char atom_window[] = "Drawing 1: Atom";
//
//	//char atom_window[] = "Drawing 1: Atom";
//	 Mat atom_image0 = Mat::zeros( w, w, CV_8UC3 );
//	 Mat atom_image1 = Mat::zeros( w, w, CV_8UC3 );
//	 Mat atom_image2 = Mat::zeros( w, w, CV_8UC3 );
//	 Mat atom_image3 = Mat::zeros( w, w, CV_8UC3 );
//	 Mat atom_image4 = Mat::zeros( w, w, CV_8UC3 );
//
//
//	 MyEllipse( atom_image0, 90 );
//	 MyEllipse( atom_image1, 0 );
//	 MyEllipse( atom_image2, 45 );
//	 MyEllipse( atom_image3, -45 );
//
//	 MyFilledCircle( atom_image0, Point( w/2, w/2) );
//
//
//	 imshow( "img", atom_image0 );
//	 waitKey( 0 );
//	 imshow( "img1", atom_image1);
//	 waitKey( 0 );
//	 imshow( "img2", atom_image2 );
//	 waitKey( 0 );
//	 imshow( "img3", atom_image3 );
//	 waitKey( 0 );
//	 moveWindow( "img4", 0, 200 );
//	 waitKey( 0 );
//
//	 Mat atom_image = Mat::zeros( w, w, CV_8UC3 );
//	 MyEllipse( atom_image, 90 );
//	  MyEllipse( atom_image, 0 );
//	  MyEllipse( atom_image, 45 );
//	MyEllipse( atom_image, -45 );
//	imshow( atom_window, atom_image );
//	moveWindow( atom_window, 0, 200 );
//	 waitKey( 0 );
//
//
//	 MyFilledCircle( atom_image0, Point( w/2, w/2) );
//	 imshow( "img", atom_image0 );
//	 	 waitKey( 0 );
//
//
//}
//void MyEllipse( Mat img, double angle )
//	 {
//	   int thickness = 2;
//	   int lineType = 8;
//
//	   ellipse( img,
//	        Point( w/2, w/2 ),
//	        Size( w/4, w/16 ),
//	        angle,
//	        0,
//	        360,
//	        Scalar( 255, 0, 0 ),
//	        thickness,
//	        lineType );
//	 }
//
//void MyFilledCircle( Mat img, Point center )
//{
//  circle( img,
//      center,
//      w/32,
//      Scalar( 0, 0, 255 ),
//      FILLED,
//      LINE_8 );
//}
