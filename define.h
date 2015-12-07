//
//  define.h
//  SOMver1
//
//  Created by Takumo Maeda on 2014/10/29.
//  Copyright (c) 2014年 Takumo Maeda. All rights reserved.
//

#ifndef SOMver1_define_h
#define SOMver1_define_h

#include <opencv2/opencv.hpp>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <time.h>
#include <sys/stat.h>


using namespace cv;
using namespace std;

const int gridRow = 5;
const int gridCol = 5;
const int multiplyRate = 50;//default 10
const int featureNum = 2;//dimension number   1(all): 6, 2(location): 2, 3(face_ori): 2,4(rri): 2
const double xMax = 1280.0;
const double yMax = 960.0;
const double ori1max = 1.0;
const double ori2max = 1.0;
const double rriMax = 2.5;
const double hfMax = 3.0;
const double nodeMax[6] = {xMax,yMax,ori1max,ori2max,rriMax*2,hfMax*2};

const double stdX = 110.9927733;
const double stdY = 68.8386322;
const double x_ave = 391.4141151;
const double y_ave = 468.164867;
const double rri_ave = 0.84801309;
const double stdRRI = 0.113147914;



#endif
