//
//  somTrain.h
//  SOMver1
//
//  Created by Takumo Maeda on 2014/10/29.
//  Copyright (c) 2014年 Takumo Maeda. All rights reserved.
//

#ifndef __SOMver1__somTrain__
#define __SOMver1__somTrain__

#include <stdio.h>
#include "define.h"

class somTrain {
private:
    
    vector<int> time_id_vec;
    
    
public:
    somTrain();
    ~somTrain();
    
    int mode;
    int maxClusters;
    long int sampleNum; //sample number
    double decayRate;
    double minAlpha;
    
    vector<long int> validNum;
    
    double alpha;
    int elemNum;//Number of elements
    
    double d[gridRow][gridCol]; //distance
    long int win[gridRow][gridCol];
    
    vector< vector<double> > input;
    vector< vector<int> > winlabel;
    
    double w[gridRow][gridCol][featureNum];
    
    double sigma;
    
    void training(string output_directory);
    //void testing();
    void computeInput(long int sampleNumber);
    double minimum(double valueA, double valueB);
    
    
};

#endif /* defined(__SOMver1__somTrain__) */
