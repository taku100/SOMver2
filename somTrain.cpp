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
    
    //int tm=0;

    
    srand((unsigned int)time(NULL));

    
    for(int i=0;i<gridRow;i++)
    {
        for(int j=0;j<gridCol;j++)
        {
//                for(int k=0;k<featureNum;k++)
//                {
//                    double test1 = 1000.0;
//                    
//                    if(k%6 == 1)
//                    {
//                        while(test1>320.0)
//                        {
//                            w[i][j][k-1] = (rand()/(double)RAND_MAX)*1200;
//                            w[i][j][k] = (rand()/(double)RAND_MAX)*960;
//                            test1 = sqrt((w[i][j][k-1]-600.0)*(w[i][j][0]-600.0)+(w[i][j][k]-480.0)*(w[i][j][1]-480.0));
//                        }
//                    }
//                    
//                    if(k%6 == 2)
//                        w[i][j][k] = (rand()/(double)RAND_MAX-0.5)*2;
//                    if(k%6 == 3)
//                    {
//                        if(rand()%2 == 0)
//                        w[i][j][k] = sqrt(1-w[i][j][k-1]*w[i][j][k-1]);
//                        else
//                        w[i][j][k] = -sqrt(1-w[i][j][k-1]*w[i][j][k-1]);
//
//                    }
//                    if(k%6 == 4)
//                        w[i][j][k] = (rand()/(double)RAND_MAX-0.5)*2*2;
//                    if(k%6 == 5)
//                        w[i][j][k] = (rand()/(double)RAND_MAX-0.5)*2*3;
//                    
//                    
//
//                }
            
            w[i][j][0] = (rand()/(double)RAND_MAX-0.5)*2.0; //-1〜1
            w[i][j][1] = (rand()/(double)RAND_MAX-0.5)*2.0; //-1〜1
//            tm = rand();
//            if(tm%4 == 0)
//            {
//                w[i][j][2] = -1;
//                w[i][j][3] =0;
//            }
//            else if(tm%4 == 1)
//            {
//                w[i][j][2] = 0;
//                w[i][j][3] =1;
//            }
//            else if(tm%4 == 2)
//            {
//                w[i][j][2] = 0;
//                w[i][j][3] =-1;
//            }
//            else if(tm%4 == 3)
//            {
//                w[i][j][2] = 1;
//                w[i][j][3] =0;
//            }
            
            w[i][j][2] = (rand()/(double)RAND_MAX-0.5)*2.0;
            
            if(rand()%2 == 0)
                w[i][j][3] = sqrt(1-w[i][j][2]*w[i][j][2]);
            else
                w[i][j][3] = -sqrt(1-w[i][j][2]*w[i][j][2]);
            
            w[i][j][4] = (rand()/(double)RAND_MAX-0.5)*2.0;
            
            w[i][j][5] = (rand()/(double)RAND_MAX-0.5)*2.0;
            
            
            win[i][j]=0;
        }
    }
    //data input
    
    stringstream ss;
    char filename[256] = "../20151028/allData_std_lp.csv";
    ss << filename;
    ifstream ifs(ss.str().c_str());
    
    //----new
    int time_id;
    float x1,y1;
    float rri_raw,rri_std;
    float rri_lp;
    
    //----new-----end
    
    //int x1,y1;
    int ori1,ori2;
    //float RRI1,HF1;
    char split;
    long int count =0;
    long int valid =0;
    
    
    
    //select mode
    //mode 1: x,y,ori1,ori2,RRI,HF
    //mode 2: x,y,ori1,ori2,RRI,HF
    //mode 3: x,y,ori1,ori2,RRI,HF
    //mode 4: x,y,ori1,ori2,RRI,HF
    //mode 5: x,y,ori1,ori2,RRI,HF
    
    
    while(!ifs.eof())
    {
    
        ifs >> time_id >> split >> x1 >> split >> y1 >> split >> ori1 >> split >> ori2 >> split >> rri_raw >> split >> rri_std >> split >> rri_lp;
        
        if(ifs.fail())
            break;
        
        if(x1 != 0)
        {
            time_id_vec.push_back(time_id);
            
            //----------all-----------------
            
            vector<double> temp(6);
            temp[0] = (double)x1;
            temp[1] = (double)y1;
            temp[2] = (double)ori1;
            temp[3] = (double)ori2;
            temp[4] = (double)rri_std;
            temp[5] = (double)rri_lp;
            
            count ++;
        
            input.push_back(temp);
            validNum.push_back(valid);
            
            //---------all end---------------
            
            
            //---------location--------------
            
            //            vector<double> temp(2);
            //            temp[0] = (double)x1;
            //            temp[1] = (double)y1;
            
            //---------location end----------
            
            
            //---------face ori--------------
            
            //            vector<double> temp(2);
            //            temp[0] = (double)ori1;
            //            temp[1] = (double)ori2;
            
            //---------face ori end----------
            
            //---------rri lp----------------
            
            //            vector<double> temp(2);
            //            temp[0] = (double)rri_std;
            //            temp[1] = (double)rri_lp;
            
            //---------rri lp end------------
            
            
            
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


void somTrain::training(string output_directory)
{
    
    int iterations = 0;
    
    //winning node cordinates
    int labelrow = 0;
    int labelcol = 0;
    
    //data output Q
    char yorn;
    cout << "create all_vote.csv? y or n" << endl;
    cin >> yorn;
    
    stringstream oss;
    oss << output_directory << "/all_vote6re.csv";
    ofstream all_vote(oss.str().c_str());
    
    if(yorn != 'y')
    {
        cout << "dont create csv" << endl;
    }
    
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
            
            
            //---FINAL MAP
            if(iterations == 101)
            {
                double x_ave = 391.4141151;
                double y_ave = 468.164867;
                double rri_ave = 0.84801309;
                double stdX = 110.9927733;
                double stdY = 68.8386322;
                double stdRRI = 0.113147914;
                
                
                //data output
                
                if(yorn == 'y')
                {
                    
                    //-----------all--------------
                    
                    all_vote << time_id_vec[sampleNumber] << "," << input[sampleNumber][0]*stdX+x_ave << "," << input[sampleNumber][1]*stdY+y_ave << "," << input[sampleNumber][2] << "," << input[sampleNumber][3]  << "," << input[sampleNumber][4]*stdRRI+rri_ave  << "," << input[sampleNumber][5] << labelcol+1 << "," << labelrow+1 <<endl;
                    
                    //-----------all end----------
                    
                    
                    
                    //---------location--------------
                    
//                    all_vote << time_id_vec[sampleNumber] << "," << input[sampleNumber][0]*stdX+x_ave << "," << input[sampleNumber][1]*stdY+y_ave << "," << labelcol+1 << "," << labelrow+1 <<endl;
                    
                    //---------location end----------
                    
                    
                    //---------face ori--------------
                    
//                    all_vote << input[sampleNumber][0] << "," << input[sampleNumber][1] << "," << labelcol+1 << "," << labelrow+1 <<endl;
                    
                    //---------face ori end----------
                    
                    //---------rri lp----------------
                    
//                    all_vote << time_id_vec[sampleNumber] << ","  << input[sampleNumber][0]*stdRRI+rri_ave  << "," << input[sampleNumber][1] << "," << labelcol+1 << "," << labelrow+1 <<endl;
                    
                    //---------rri lp end------------
                    
                }
                //-----------data output fin
                
                
                for(int i=0;i<gridRow;i++)
                {
                    for(int j=0;j<gridCol;j++)
                    {
                        
                        if(i == labelrow && j == labelcol)
                            win[i][j] += 1;
                    }
                }
                cout << "-------------------------------------------" << endl;
                cout << "sample[" << sampleNumber+1 << "]" << "(col,row)" << "(" << labelcol+1 << "," << labelrow+1 << ")" << endl;
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
                d[i][j] += sqrt(pow((w[i][j][k] - input[sampleNumber][k]), 2));
                //d[i][j] += sqrt(pow((w[i][j][k]/nodeMax[k%6] - input[sampleNumber][k]/nodeMax[k%6]), 2));
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