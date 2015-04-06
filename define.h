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
#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;

const int gridRow = 25;
const int gridCol = 25;
const int multiplyRate = 10;
const int vecLen = 4;//dimension number
const int featureNum = 4;
const double xMax = 1280.0;
const double yMax = 960.0;
const double rriMax = 2.5;
const double hfMax = 3.0;
const double nodeMax[4] = {xMax,yMax,rriMax*2,hfMax*2};

#endif
