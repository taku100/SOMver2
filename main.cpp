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

//time
time_t nt = time(NULL);
struct tm *ltm = localtime(&nt);


    int yy = ltm->tm_year + 1900;
    int mo = ltm->tm_mon +1;
    int dd = ltm->tm_mday;
    int hh = ltm->tm_hour;
    int mi = ltm->tm_min;
    int sec = ltm->tm_sec;




int main(int argc, const char * argv[])
{
    //output file directry
    
    stringstream n_time;
    stringstream output_dir;
    
    n_time << yy << "_" << mo << "_" <<dd << "_" << hh << "_" << mi;
    
    cout << n_time.str().c_str() << endl;
    
    output_dir << "../output/" << n_time.str().c_str();
    
    

    
    //投票された行動分類
    somVis pc;
    somVis phone;
    somVis talk;
    somVis eat;
    
    somVis all;
    
    somTrain train;
    
    if(train.mode == 1)
    {
        output_dir << "all";
    }
    else if(train.mode == 2)
    {
        output_dir << "location";
    }
    else if(train.mode == 3)
    {
        output_dir << "face_ori";
    }
    else if(train.mode == 4)
    {
        output_dir << "rri";
    }
    
    
    mkdir(output_dir.str().c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IXOTH | S_IXOTH);
    
    
    train.training(output_dir.str().c_str());
    char winname[25];
    all.histgram(train);
    int count =0;
    for(int i =0;i<gridRow;i++)
    {
        for(int j=0;j<gridCol;j++)
        {
            sprintf(winname, "[%d,%d]",i,j);
            imshow(winname, all.histgrams[count]);
            count++;
        }
    }
    
    //---------------show & write all png file
    
    stringstream imgAll;
    imgAll << output_dir.str().c_str() << "/all.png";
    imshow("all", all.histMap);
    imwrite(imgAll.str().c_str(), all.histMap);
    
    //---------------show tag vote
    char yn;
    cout << "want tag vote? y or n?" << endl;
    cin >> yn;
    
    if(yn == 'y')
    {
        char *talkname = "../input/all_std_lp/class1.csv";
        talk.vote(talkname, train);
        char *eatname = "../input/all_std_lp/class2.csv";
        eat.vote(eatname, train);
        char *pcname = "../input/all_std_lp/class3.csv";
        pc.vote(pcname, train);
        char *phonename = "../input/all_std_lp/class4.csv";
        phone.vote(phonename, train);
        
        
        talk.visualize();
        eat.visualize();
        pc.visualize();
        phone.visualize();
        
        stringstream imgTalk;
        imgTalk << output_dir.str().c_str() << "/talkSOM.png";
        stringstream imgEat;
        imgEat << output_dir.str().c_str() << "/eatSOM.png";
        stringstream imgPC;
        imgPC << output_dir.str().c_str() << "/pcSOM.png";
        stringstream imgPhone;
        imgPhone << output_dir.str().c_str() << "/phoneSOM.png";
        
        imwrite(imgTalk.str().c_str(),talk.map);
        imwrite(imgEat.str().c_str(), eat.map);
        imwrite(imgPC.str().c_str(),pc.map);
        imwrite(imgPhone.str().c_str(), phone.map);
        
        imshow("talkSOM", talk.map);
        imshow("eatSOM", eat.map);
        imshow("pcSOM", pc.map);
        imshow("phoneSOM", phone.map);
        
        return 0;
    }
    
    else if(yn != 'y' )
        return 0;
    
    //---------------show & write png file---------------end
    
    //return 0;
    
//    char filename[256];
//    char text[256];
//    Mat img;
//    
//    
//    cv::Rect roi;
//    roi.width = multiplyRate;
//    roi.height = multiplyRate;
//    
//    Point pt;
    
    //----------------visualization movie & SOM
//    for(long int i=0;i<train.sampleNum;i++)
//    {
//        Mat map = cv::Mat::zeros(multiplyRate*gridRow, multiplyRate*gridCol, CV_8UC3);
//        for(int i=1;i<gridCol;i++)
//        {
//            cv::line(map, Point(i*multiplyRate,0), Point(i*multiplyRate,map.rows), Scalar(255,255,255));
//        }
//        for(int j=1;j<gridRow;j++)
//        {
//            cv::line(map, Point(0,j*multiplyRate), Point(map.cols,j*multiplyRate), Scalar(255,255,255));
//        }
//        
//        
//        sprintf(filename, "output/img%lu.png",train.validNum[i]);
//        sprintf(text, "(%d,%d)",train.winlabel[i][0],train.winlabel[i][1]);
//        roi.x = multiplyRate*train.winlabel[i][1];
//        roi.y = multiplyRate*train.winlabel[i][0];
//        Mat roiSOM(map,roi);
//        roiSOM = Scalar(0,255,0);
//        cv::putText(roiSOM, text, cv::Point(20,20), cv::FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255));
//        
//        img = imread(filename);
//        pt.x = train.input[i][0]/2;
//        pt.y = train.input[i][1]/2;
//        cv::circle(img, pt, 3, Scalar(255,0,0),-1);
//        
//        imshow("img",img);
//        imshow("map",map);
//        waitKey(1);
//    }
    
}
