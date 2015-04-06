//
//  main.cpp
//  SOMver2
//
//  Created by Takumo Maeda on 1/19/15.
//  Copyright (c) 2015 Takumo Maeda. All rights reserved.
//

#include <iostream>
#include "define.h"
#include "somTrain.h"
#include "somVis.h"

int main(int argc, const char * argv[])
{
//    Mat map = cv::Mat::zeros(multiplyRate*gridRow, multiplyRate*gridCol, CV_8UC3);
//    for(int i=1;i<gridCol;i++)
//    {
//        cv::line(map, Point(i*multiplyRate,0), Point(i*multiplyRate,map.rows), Scalar(255,255,255));
//    }
//    for(int j=1;j<gridRow;j++)
//    {
//        cv::line(map, Point(0,j*multiplyRate), Point(map.cols,j*multiplyRate), Scalar(255,255,255));
//    }
//    
//    for(int i=20;i<30;i++)
//    {
//        for(int j=10;j<20;j++)
//        {
//            map.at<Vec3b>(i,j)[0] =255;
//            map.at<Vec3b>(i,j)[1] =255;
//            map.at<Vec3b>(i,j)[2] = 0;
//        }
//    }
//    imshow("test",map);
//    waitKey(0);
    
    //投票された行動分類
    somVis pc;
    somVis phone;
    somVis talk;
    somVis eat;
    
    
    
    somTrain train;
    train.training();
    
    char *talkname = "all/person2/class1.csv";
    talk.vote(talkname, train);
    char *eatname = "all/person2/class2.csv";
    eat.vote(eatname, train);
    char *pcname = "all/person2/class3.csv";
    pc.vote(pcname, train);
    char *phonename = "all/person2/class4.csv";
    phone.vote(phonename, train);
    
    
    talk.visualize();
    eat.visualize();
    pc.visualize();
    phone.visualize();
    
    //imwrite("talkSOM.png",talk.map);
    //imwrite("eatSOM.png", eat.map);
    //imwrite("pcSOM.png",pc.map);
    //imwrite("phoneSOM.png", phone.map);
    
    imshow("talkSOM", talk.map);
    imshow("eatSOM", eat.map);
    imshow("pcSOM", pc.map);
    imshow("phoneSOM", phone.map);
    waitKey(0);
    
    return 0;
    
    char filename[256];
    char text[256];
    Mat img;
    
    
    cv::Rect roi;
    roi.width = multiplyRate;
    roi.height = multiplyRate;
    
    Point pt;
    
    //----------------visualization movie & SOM
    for(long int i=0;i<train.sampleNum;i++)
    {
        Mat map = cv::Mat::zeros(multiplyRate*gridRow, multiplyRate*gridCol, CV_8UC3);
        for(int i=1;i<gridCol;i++)
        {
            cv::line(map, Point(i*multiplyRate,0), Point(i*multiplyRate,map.rows), Scalar(255,255,255));
        }
        for(int j=1;j<gridRow;j++)
        {
            cv::line(map, Point(0,j*multiplyRate), Point(map.cols,j*multiplyRate), Scalar(255,255,255));
        }
        
        
        sprintf(filename, "output/img%lu.png",train.validNum[i]);
        sprintf(text, "(%d,%d)",train.winlabel[i][0],train.winlabel[i][1]);
        roi.x = multiplyRate*train.winlabel[i][1];
        roi.y = multiplyRate*train.winlabel[i][0];
        Mat roiSOM(map,roi);
        roiSOM = Scalar(0,255,0);
        cv::putText(roiSOM, text, cv::Point(20,20), cv::FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255));
        
        img = imread(filename);
        pt.x = train.input[i][0]/2;
        pt.y = train.input[i][1]/2;
        cv::circle(img, pt, 3, Scalar(255,0,0),-1);
        
        imshow("img",img);
        imshow("map",map);
        waitKey(1);
    }
    
    return 0;
}
