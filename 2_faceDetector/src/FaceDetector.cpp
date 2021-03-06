#include <iostream>
#include <stdio.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

/** Constants used for detectAndDisplay */

double min_face_size=50;
double max_face_size=250;

/** Function Headers */

Mat detectAndDisplay( Mat frame, string window_name, int frame_number, string video_string, int demo_mode, int &current_label, std::vector<std::vector<Rect> >& array_of_faces, std::vector<std::vector<int> >& array_of_faces_labeling);

string NumberToString ( int Number );

/** Global variables */
//String face_cascade_name = "src/others/haarcascade_frontalface_alt.xml";
//String profile_cascade_name = "src/others/haarcascade_profileface.xml";
String homkrun_cascade_name = "cascade/cascadeClassifier3Stage22.xml";

CascadeClassifier face_cascade;
CascadeClassifier profile_cascade;
CascadeClassifier homkrun_cascade;
void help()
{
    cout << "This software is supposed to be used indirectly, within the script generate_database.sh. Please read the readme file." << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        help();
        return -1;
    }
    string video_string_with_slashes = argv[1];
    int demo_mode = atoi(argv[2]);
    
    string video_string=video_string_with_slashes;
    for (int i=0; i<video_string.size();i++)
    {
        if (video_string[i] == '/' || video_string[i] == ' ')
            video_string[i]='-';
    }
    
    //if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
    //if( !profile_cascade.load( profile_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
    if( !homkrun_cascade.load( homkrun_cascade_name ) ){ printf("--(!)Error loading cascade\n"); return -1; };
    VideoCapture cap(video_string_with_slashes);
    if(!cap.isOpened())
        return -1;
    
    Mat edges;
    if (demo_mode)
    {
        namedWindow("Result",WINDOW_NORMAL);
        namedWindow("Initial",WINDOW_NORMAL);
    }
    VideoWriter outputVideo;
    
    string command1 = "mkdir Database/"+video_string+";";
    system(command1.c_str());
    if (demo_mode)
    {
        string command2 = "mkdir Database/"+video_string+"/video;";
        system(command2.c_str());
        const string VIDEO_NAME = "Database/"+video_string+"/video/"+"detected_faces.avi";
        int ex = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));
        double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
        double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
        Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
        outputVideo.open(VIDEO_NAME, ex /*CV_FOURCC('P','I','M','1') FOR WEBCAM PURPOSE */ /* Use ex if I am using a file instead of webcam*/, cap.get(CV_CAP_PROP_FPS), frameSize, true);
    }
    Mat frame;
    // First frame number is zero.
    int frame_number = 0;
    Mat outputFrame;
    cout << video_string << "'s face detection engaged. Be patient, the process may take from several minutes to few hours.\n" << endl;
    int total_number_of_frames = cap.get(CV_CAP_PROP_FRAME_COUNT);
    int current_label = 0;
    std::vector<std::vector<Rect> > array_of_faces;
    std::vector<std::vector<int> > array_of_faces_labeling;
    int current_frame;
    
    while(1)
    {
        current_frame = cap.get(CV_CAP_PROP_POS_FRAMES);
        cout << (float)current_frame/(float)total_number_of_frames*100 << "%" << endl;
        cap >> frame; // get a new frame from the video
        if(frame.empty())
        {
            break;
        }
        if (demo_mode)
            imshow("Initial", frame);
        outputFrame = detectAndDisplay(frame, "Result", frame_number, video_string, demo_mode, current_label, array_of_faces, array_of_faces_labeling);
        if (demo_mode)
            outputVideo.write(outputFrame);
        frame_number++;
        if(waitKey(10) >= 0) break;
    }
    
    cout << video_string << "is Done.\n" << endl;
    return 0;
}

Mat detectAndDisplay( Mat frame, string window_name, int frame_number, string video_string, int demo_mode, int &current_label, std::vector<std::vector<Rect> >& array_of_faces, std::vector<std::vector<int> >& array_of_faces_labeling)
{
    
    std::vector<Rect> faces;
    std::vector<Rect> faces_profile;
    std::vector<Rect> homkrun;
    
    int label;
    Mat frame_gray;
    Mat Rect_ROI;
    cvtColor( frame, frame_gray, CV_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    string filename;
    //-- Detect faces
    //face_cascade.detectMultiScale( frame, faces, 1.05, 3, 0|CV_HAAR_SCALE_IMAGE, Size(min_face_size, min_face_size),Size(max_face_size, max_face_size) );
    //profile_cascade.detectMultiScale( frame, faces_profile, 1.05,3, 0|CV_HAAR_SCALE_IMAGE, Size(min_face_size, min_face_size),Size(max_face_size, max_face_size) );
    homkrun_cascade.detectMultiScale( frame, homkrun, 1.325,8, 0|CV_HAAR_SCALE_IMAGE, Size(min_face_size, min_face_size),Size(max_face_size, max_face_size) );
    
    // Faces becomes all the faces. The ones which are detected as profile faces and the others.
    //faces.insert( faces.end(), faces_profile.begin(), faces_profile.end());
    faces.insert( faces.end(), homkrun.begin(), homkrun.end());
    
    array_of_faces.push_back(faces); //array_of_faces[frame_number]=faces;
    int faces_size = faces.size();
    array_of_faces_labeling.push_back(std::vector<int>(faces_size,0));
    bool happened;
    double distance;
    int k_best, l_best;
    int border;
    // For each face of the current frame
    for( int i = 0; i < faces_size; i++ )
    {
        happened = false;
        distance=abs(frame.size().height)+abs(frame.size().width);
        k_best=0;
        l_best=0;
        Rect_ROI = Mat(frame,faces[i]);
        if (array_of_faces.size() >= 3) // ie it is at least the 5th frame because counting starts at 0
            border = array_of_faces.size()-3;
        else
            border = 0;
        // For the five previous frames and also the current one
        for (int k=border; k<array_of_faces.size(); k++)
        {
            // For each face of these frames
            for (int l=0; l<array_of_faces[k].size();l++)
            {
                if (k==array_of_faces.size()-1 && l==i)
                {
                    break;
                }
                if( (abs(faces[i].x - array_of_faces[k][l].x) < Rect_ROI.rows && abs(faces[i].y - array_of_faces[k][l].y) < Rect_ROI.rows))
                {
                    happened = true;
                    
                    if ( (abs(faces[i].x - array_of_faces[k][l].x)+abs(faces[i].y - array_of_faces[k][l].y))<=distance )
                    {
                        distance = abs(faces[i].x - array_of_faces[k][l].x)+abs(faces[i].y - array_of_faces[k][l].y);
                        k_best = k;
                        l_best = l;
                    }
                }
            }
        }
        // If at least one candidate for corresponding face was found, we choose the label of the best one
        if (happened==true)
        {
            label = array_of_faces_labeling[k_best][l_best];
            array_of_faces_labeling[frame_number][i] = label;
            if (i<faces_size)
                filename = "Database/"+video_string+"/"+"Label"+NumberToString(label)+"Frame"+NumberToString(frame_number)+"Face"+NumberToString(i)+".jpg";
            else
                filename = "Database/"+video_string+"/"+"Label"+NumberToString(label)+"Frame"+NumberToString(frame_number)+"Face"+NumberToString(i)+"|Profile|.jpg";
            imwrite(filename,Rect_ROI);
            if (demo_mode)
                rectangle(frame, faces[i],Scalar( 255, 0, 255 ),3,8,0);
        }
        // If there is no corresponding face, then it is a new face and we create a new label
        else
        {
            current_label++;
            label = current_label;
            array_of_faces_labeling[frame_number][i] = label;
            if (i<faces_size)
                filename = "Database/"+video_string+"/"+"Label"+NumberToString(label)+"Frame"+NumberToString(frame_number)+"Face"+NumberToString(i)+".jpg";
            else
                filename = "Database/"+video_string+"/"+"Label"+NumberToString(label)+"Frame"+NumberToString(frame_number)+"Face"+NumberToString(i)+"|Profile|.jpg";
            imwrite(filename,Rect_ROI);
            if (demo_mode)
                rectangle(frame, faces[i],Scalar( 255, 0, 255 ),3,8,0);
        }
        
        
    }
//-- Show what you got
if (demo_mode)
    imshow( window_name, frame );
return frame;
}

string NumberToString ( int Number )
{
    stringstream ss;
    ss << Number;
    return ss.str();
}
