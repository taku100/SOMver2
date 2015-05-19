//
//  somTrain.cpp
//  SOMver1
//
//  Created by Takumo Maeda on 2014/10/29.
//  Copyright (c) 2014年 Takumo Maeda. All rights reserved.
//

//ver1:somTrain::testing() available
//ver2:delete somTrain::testing() and new test

#include "somTrain.h"


somTrain::somTrain()
{
    //init
    
    maxClusters = gridRow * gridCol;
    decayRate = 0.96;
    minAlpha = 0.01;
    alpha = 0.6;
    sigma = 1.0;
    
    srand((unsigned int)time(NULL));

    
    for(int i=0;i<gridRow;i++)
    {
        for(int j=0;j<gridCol;j++)
        {
                for(int k=0;k<featureNum;k++)
                {
                    double test1 = 1000.0;
                    
                    if(k%6 == 1)
                    {
                        while(test1>320.0)
                        {
                            w[i][j][k-1] = (rand()/(double)RAND_MAX)*1200;
                            w[i][j][k] = (rand()/(double)RAND_MAX)*960;
                            test1 = sqrt((w[i][j][k-1]-600.0)*(w[i][j][0]-600.0)+(w[i][j][k]-480.0)*(w[i][j][1]-480.0));
                        }
                    }
                    
                    if(k%6 == 2)
                        w[i][j][k] = (rand()/(double)RAND_MAX-0.5)*2;
                    if(k%6 == 3)
                    {
                        if(rand()%2 == 0)
                        w[i][j][k] = sqrt(1-w[i][j][k-1]*w[i][j][k-1]);
                        else
                        w[i][j][k] = -sqrt(1-w[i][j][k-1]*w[i][j][k-1]);

                    }
                    if(k%6 == 4)
                        w[i][j][k] = (rand()/(double)RAND_MAX-0.5)*2*2;
                    if(k%6 == 5)
                        w[i][j][k] = (rand()/(double)RAND_MAX-0.5)*2*3;
                }
            win[i][j]=0;
        }
    }
    //data input
    
    stringstream ss;
    char filename[256] = "../person/person2/person2face_all.csv";
    ss << filename;
    ifstream ifs(ss.str().c_str());
    int x1,y1;
    int ori1,ori2;
    float RRI1,HF1;
    char split;
    long int count =0;
    long int valid =0;
    
    while(!ifs.eof())
    {
        ifs >> x1 >> split >> y1 >> split >> ori1 >> split >> ori2 >> split >> RRI1 >> split >> HF1;
    
        if(ifs.fail())
            break;
        
        if(x1 != 0)
        {
            vector<double> temp(6);
            temp[0] = (double)x1;
            temp[1] = (double)y1;
            temp[2] = (double)ori1;
            temp[3] = (double)ori2;
            temp[4] = (double)RRI1;
            temp[5] = (double)HF1;
            
            count ++;
        
            input.push_back(temp);
            validNum.push_back(valid);
        }
        valid++;
    }
    cout << "input size = " << input.size() << endl;
    sampleNum = input.size();
    
}

somTrain::~somTrain()
{
    input.clear();
}


void somTrain::training()
{
    
    int iterations = 0;
    
    //winning node cordinates
    int labelrow = 0;
    int labelcol = 0;
    
    do {
        iterations += 1;
        cout << iterations << endl;
        for(int sampleNumber = 0; sampleNumber < sampleNum; sampleNumber++)
        {
            
            //Compute input. fix distance(d[][])
            computeInput(sampleNumber);
            double dMin = 1000000;
            
            //See which is smaller, d[0] or d[1]?
            for(int i=0;i<gridRow;i++)
            {
                for(int j=0;j<gridCol;j++)
                {
                    
                    //cout << "d[" << i << "]" << "[" << j << "] = " << d[i][j] << endl;
                    
                    dMin = minimum(dMin, d[i][j]);
                    
                    //cout << "dMin = " << dMin << "   " << "d[" << i << "]" << "[" << j << "] = " << d[i][j] << endl;
                    if(dMin == d[i][j])
                    {
                        labelrow = i;
                        labelcol = j;
                    }
                    
                }
            }
            
            //see what label id is right
            
            //cout << "iteration:" << iterations << "  sample number:" << sampleNumber+1 << "  winrow:" << labelrow << ",wincol:" << labelcol << endl;
            
            //--------------Update the weights on the winning unit.
            for(int i = 0; i < featureNum; i++)
            {
                //w[dMin][i] = w[dMin][i] + (alpha * (pattern[vecNum][i] - w[dMin][i]));
                for(int j=0;j<gridRow;j++)
                {
                    for(int k=0;k<gridCol;k++)
                    {
                        w[j][k][i] = w[j][k][i] + exp(-((labelrow-j)*(labelrow-j)+(labelcol-k)*(labelcol-k))/(2*(sigma*sigma)))*(alpha * (input[sampleNumber][i] - w[j][k][i]));
                    }
                }
                
            }//-------------------update the weights
            
            if(iterations == 101)
            {
                for(int i=0;i<gridRow;i++)
                {
                    for(int j=0;j<gridCol;j++)
                    {
                        if(i == labelrow && j == labelcol)
                            win[i][j] += 1;
                    }
                }
                cout << "-------------------------------------------" << endl;
                cout << "sample[" << sampleNumber+1 << "]" << "(" << labelcol+1 << "," << labelrow+1 << ")" << endl;
                for(int k=0;k<featureNum;k++)
                {
                    cout << input[sampleNumber][k] << endl;
                }
                
                vector<int> tp(2);
                tp[0] = labelrow;
                tp[1] = labelcol;
                winlabel.push_back(tp);
            }
            
            
        }
        
        //Reduce the learning rate.
        alpha = decayRate * alpha;
        
    } while(alpha > minAlpha);
    
    
    
    for(int i=0;i<gridRow;i++)
    {
        cout << "{";
        for(int j=0;j<gridCol;j++)
        {
            cout << "{";
            for(int k=0;k<featureNum;k++)
            {
                cout << " " <<w[i][j][k] << " ";
            }
            cout << "}";
        }
        cout << "}" << endl << endl;
    }
    cout << "Iterations: " << iterations << "\n\n";
    
    for(int i=0;i<gridRow;i++)
    {
        cout << "{";
        for(int j=0;j<gridCol;j++)
        {
           cout << " " <<win[i][j] << " ";
        }
        cout << "}" << endl;
    }
}


void somTrain::computeInput(long int sampleNumber)
{
    //distance init
    for(int i = 0;i<gridRow;i++)
    {
        for(int j=0;j<gridCol;j++)
        {
            d[i][j] = 0.0;
        }
    }
    
    for(int i = 0; i <gridRow; i++)
    {
        for(int j=0;j<gridCol;j++)
        {
            for(int k = 0; k < featureNum; k++)
            {
                d[i][j] += sqrt(pow((w[i][j][k]/nodeMax[k%6] - input[sampleNumber][k]/nodeMax[k%6]), 2));
                //cout << "D= " << d[i][j] << "\n";
            } // j
        }
    } // i
}

double somTrain::minimum(double valueA, double valueB)
{
    if(valueA > valueB)
    {
        return valueB;
    }
    else
    {
        return valueA;
    }
}