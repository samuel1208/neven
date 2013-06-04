#include "neven.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
    int width, height;
    int max_faces = 10;
    IplImage *src = NULL;
    IplImage *gray = NULL;
    struct neven_env *env = NULL;
    int num_faces= 0;
    int i=0;
    src = cvLoadImage(argv[1], 1);
    gray = cvCreateImage(cvSize(src->width, src->height), 8, 1);
    gray->widthStep = src->width;
    cvNamedWindow("test",0);

    cvCvtColor(src, gray, CV_RGB2GRAY);
    cvShowImage("test", gray); 
    cvWaitKey(0);

    width = src->width;
    height = src->height;

    env = neven_create(width, height, max_faces);
    num_faces = neven_detect(env, gray->imageData); 
    
    
    for (i = 0; i < num_faces; i++) 
    {
        struct neven_face face;
        neven_get_face(env, &face, i);
        cvCircle(src, cvPoint((int)face.midpointx, (int)face.midpointy),
                 (int)face.eyedist, CV_RGB(0,255,0), -1, 8, 0 );
        
    }
    
    cvShowImage("test", src); 
    cvWaitKey(0);
    neven_destroy(env);
    cvReleaseImage(&gray);
    cvReleaseImage(&src);
    return 0;
}
