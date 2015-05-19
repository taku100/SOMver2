//
//  somVis.h
//  SOMver1
//
//  Created by Takumo Maeda on 2014/10/29.
//  Copyright (c) 2014年 Takumo Maeda. All rights reserved.
//

#ifndef __SOMver1__somVis__
#define __SOMver1__somVis__

#include <stdio.h>
#include "define.h"
#include "somTrain.h"

class somVis {
private:
    
    
    
public:
    somVis();
    ~somVis();
    
    Mat map;
    Mat frame;
    cv::Scalar color[9];
    cv::Mat histgrams[gridRow*gridCol];
    
    int actionVote[gridRow][gridCol];
    void vote(char *filename,somTrain &som);
    
    void visualize();
    
};



#endif /* defined(__SOMver1__somVis__) */
