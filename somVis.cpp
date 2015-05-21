//
//  somVis.cpp
//  SOMver1
//
//  Created by Takumo Maeda on 2014/10/29.
//  Copyright (c) 2014年 Takumo Maeda. All rights reserved.
//

#include "somVis.h"


somVis::somVis()
{
    
    //各グリッドのヒストグラムイメージ
    for(int i=0;i<gridRow;i++)
    {
        for(int j=0;j<gridCol;j++)
        {
            Mat hist_img(Size(smMap_width,smMap_height*2),CV_8UC3,Scalar::all(255));
            histgrams.push_back(hist_img);
        }
    }
    
    histMap = cv::Mat::zeros(smMap_height*2*gridRow, smMap_width*gridCol, CV_8UC3);
    
    color[0] = Scalar(255,0,0);
    color[1] = Scalar(255,120,0);
    color[2] = Scalar(255,255,0);
    color[3] = Scalar(120,255,0);
    color[4] = Scalar(0,255,0);
    color[5] = Scalar(0,255,120);
    color[6] = Scalar(0,255,255);
    color[7] = Scalar(0,120,255);
    color[8] = Scalar(0,0,255);
    
    
    map = cv::Mat::zeros(multiplyRate*gridRow, multiplyRate*gridCol, CV_8UC3);
    
    for(int i=0;i<gridRow;i++)
    {
        for(int j=0;j<gridCol;j++)
        {
            actionVote[i][j] = 0;
        }
    }
    for(int i=1;i<gridCol;i++)
    {
        cv::line(map, Point(i*multiplyRate,0), Point(i*multiplyRate,map.rows), Scalar(255,255,255));
    }
    for(int j=1;j<gridRow;j++)
    {
        cv::line(map, Point(0,j*multiplyRate), Point(map.cols,j*multiplyRate), Scalar(255,255,255));
    }

    
}

somVis::~somVis()
{
    map.release();
}

void somVis::visualize()
{
    double max=0.0;
    double cl =0.0;
    
    for(int i=0;i < gridRow;i++)
    {
        for(int j=0;j < gridCol;j++)
        {
            if((double)actionVote[i][j]>max)
                max = (double)actionVote[i][j];
        }
    }
    
    
    for(int i=0;i < gridRow;i++)
    {
        for(int j=0;j < gridCol;j++)
        {
            cl = (double)actionVote[i][j]/max;
            if(cl>0.88)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), color[8], -1, CV_AA );

            }
            
            if(0.88 >= cl && cl > 0.77)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), color[7], -1, CV_AA );

            }
                
            if(0.77 >= cl && cl > 0.66)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), color[6], -1, CV_AA );

            }
                
            if(0.66 >= cl && cl > 0.55)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), color[5], -1, CV_AA );

            }
            
            if(0.55 >= cl && cl > 0.44)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), color[4], -1, CV_AA );

            }
                
            if(0.44 >= cl && cl > 0.33)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), color[3], -1, CV_AA );

            }
                
            if(0.33 >= cl && cl > 0.22)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), color[2], -1, CV_AA );

            }
                
            if(0.22 >= cl && cl > 0.11)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), color[1], -1, CV_AA );

            }
                
            if(0.11 >= cl && cl > 0.0)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), color[0], -1, CV_AA );

            }
                
            if(cl == 0.0)
            {
                cv::rectangle( map, cv::Rect( j*multiplyRate, i*multiplyRate, multiplyRate,multiplyRate), Scalar(0,0,0), -1, CV_AA );

            }
            
        }
        
    }
    
    
}

void somVis::vote(char *filename,somTrain &som)
{
    ifstream ifs(filename);
    int x,y;
    int ori1,ori2;
    double RRI,HF;
    char split;
    long int count = 0;
    vector< vector<double> > input;
    double distance = 1000000.0;
    
    while(!ifs.eof())
    {
        ifs >> x >> split >> y >> split >> ori1 >> split >> ori2 >> split >> RRI >> split >> HF;
        
        if(ifs.fail())
            break;
        
        if(x != 0)
        {
            vector<double> temp(4);
            temp[0] = (double)x;
            temp[1] = (double)y;
            temp[2] = (double)ori1;
            temp[3] = (double)ori2;
            temp[4] = (double)RRI;
            temp[5] = (double)HF;
            
            count ++;
            
            input.push_back(temp);
        }
        
    }
    
    
    for(int z=0;z<input.size();z++)
    {
        int labelrow = 0;
        int labelcol = 0;
        distance = 1000000.0;
        
        for(int i=0;i<gridRow;i++)
        {
            for(int j=0;j<gridCol;j++)
            {
                double temp2 = 0.0;
                for(int k=0;k<featureNum;k++)
                {
                    temp2 += sqrt((som.w[i][j][k]/nodeMax[k]-input[z][k]/nodeMax[k])*(som.w[i][j][k]/nodeMax[k]-input[z][k]/nodeMax[k]));
                }
                
                if(temp2<distance)
                {
                    distance = temp2;
                    labelrow = i;
                    labelcol = j;
                }
            }
        }
        
        actionVote[labelrow][labelcol] += 1;
    }
    
    for(int i =0;i<gridRow;i++)
    {
        for(int j=0;j<gridCol;j++)
        {
            cout << actionVote[i][j]<< "  ";
        }
        cout << endl;
    }
    
}

void somVis::histgram(somTrain &train)
{
    int count = 0;
    for(int i = 0;i<gridRow;i++)
    {
        for(int j=0;j<gridCol;j++)
        {
            for(int k = 0;k<featureNum;k++)
            {
                cv::rectangle(histgrams[count], Point(k*smMap_width/featureNum,smMap_height), Point((k+1)*smMap_width/featureNum-1,smMap_height+(-1)*smMap_height*train.w[i][j][k]/nodeMax[k]), Scalar(0,255,0));
                
            }
            
            Rect rect(j*smMap_width,i*smMap_height*2,smMap_width,smMap_height*2);
            Mat subdst = histMap(rect);
            histgrams[count].copyTo(subdst);
            count++;
            
        }
    }
    
    for(int i = 0;i < gridRow*smMap_height*2;i++)
    {
        for(int j =0;j<gridCol*smMap_width;j++)
        {
            if(i%(smMap_height*2) == 0)
                histMap.at<Vec3b>(i,j) = 0;
            
            else if(j%smMap_width == 0)
                histMap.at<Vec3b>(i,j) = 0;
        }
    }
    
}
