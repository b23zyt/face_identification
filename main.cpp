#include <QCoreApplication>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

bool DrawRect(Mat& src, vector<Rect>& face)
{
    //exist the function if no face detected (no red border displayed)
    if(face.empty())
        return false;

    //otherwise, display the red rect
    //face.size() return the number of objects, determine number of red rect
    //tl() returns a point
    for(unsigned int i = 0; i < face.size(); i++)
    {
        int x = face[i].tl().x;
        int y = face[i].tl().y;
        int width = face[i].width;
        int height = face[i].height;
        rectangle(src, Rect(x, y, width, height), Scalar(0, 0, 255), 3);
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    // Mat image = imread("/Users/b23zeng/Desktop/some photos/E7.jpeg", IMREAD_COLOR);
    // rectangle(image, Rect(100, 50, 150, 200), Scalar(0,0,255),3);
    // imshow("Building", image);
    // waitKey(0);

    //Task 1
    //Display the image and put a red border at a certain location
    // VideoCapture cap = VideoCapture("/Users/b23zeng/Desktop/face_scan/singing.mp4"); //read and store the video inside of cap
    // Mat img;
    // while(cap.read(img))    //read every pix of cap and store them in img.
    // {
    //     //4. 在视频里画方框
    //     rectangle(img, Rect(200, 100, 350, 450), Scalar(0, 0, 255), 3); //red board
    //     imshow("video", img);
    //     waitKey(30);
    // }
    // cap.release();  //release the video


    VideoCapture cap = VideoCapture(1); //open the diplay's external camera
    Mat img; //creates a matrix img that will store each frame of the video.
    vector<Rect> face; //defines a vector to store detected face rectangles
    CascadeClassifier object; // initializes an OpenCV classifier, object, to detect faces
    object.load("/Users/b23zeng/Desktop/face_scan/haarcascade_frontalface_alt.xml"); //loads a pre-trained Haar cascade classifier XML file, which contains data for frontal face detection.
    while(cap.read(img))    //Continuously read frames from the video into img
    {
        object.detectMultiScale(img, face);  //detect faces in img and stores them in the face vector
        DrawRect(img, face);  //calls the function to draw a rectangle around the boundary of face

        imshow("video", img); //display the frame
        waitKey(10); //waits for 10 milliseconds before moving to the next frame,
    }
    cap.release();  //release the video capture object

    cout << "Hello World!" << endl;
    return a.exec();


}
