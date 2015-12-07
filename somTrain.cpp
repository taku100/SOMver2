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
    
    cout << "SELECT MODE" << endl;
    cout << "1:all(x,y,face_ori1,face_ori2,rri_raw,rri_std)" << endl;
    cout << "2:locatin(x,y)" << endl;
    cout << "3:face_ori1,face_ori2" << endl;
    cout << "4:rri_raw,rri_std" << endl;
    cin >> mode;
    
    if( mode == 1 )
    {
        //--------node initialization--------------
        for(int i=0;i<gridRow;i++)
        {
            for(int j=0;j<gridCol;j++)
            {
                
                w[i][j][0] = (rand()/(double)RAND_MAX-0.5)*2.0; //-1〜1
                w[i][j][1] = (rand()/(double)RAND_MAX-0.5)*2.0; //-1〜1
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
        
        
        //--------data input------------------------
        stringstream ss;
        char filename[256] = "../20151028/allData_std_lp.csv";
        ss << filename;
        ifstream ifs(ss.str().c_str());
        
        int time_id;
        float x1,y1;
        float rri_raw,rri_std;
        float rri_lp;
        int ori1,ori2;
        char split;
        long int count =0;
        long int valid =0;
        
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
                
            }
            valid++;
        }
        cout << "input size = " << input.size() << endl;
        sampleNum = input.size();
        
    }
    
    else if(mode == 2)
    {
        //node initialization
        for(int i=0;i<gridRow;i++)
        {
            for(int j=0;j<gridCol;j++)
            {
                w[i][j][0] = (rand()/(double)RAND_MAX-0.5)*2.0; //-1〜1
                w[i][j][1] = (rand()/(double)RAND_MAX-0.5)*2.0; //-1〜1
                
                win[i][j]=0;
            }
        }
        
        //--------data input------------------------
        stringstream ss;
        char filename[256] = "../input/training/location/loc_all.csv";
        ss << filename;
        ifstream ifs(ss.str().c_str());
        
        int time_id;
        int x,y;
        float x_std,y_std;
        char split;
        long int count =0;
        long int valid =0;
        
        while(!ifs.eof())
        {
            
            ifs >> time_id >> split >> x >> split >> y >> split >> x_std >> split >> y_std;
            
            if(ifs.fail())
                break;
            
            if(x != 0)
            {
                time_id_vec.push_back(time_id);
                
                vector<double> temp(2);
                temp[0] = (double)x_std;
                temp[1] = (double)y_std;
                
                count ++;
                
                input.push_back(temp);
                validNum.push_back(valid);
    
            }
            valid++;
        }
        cout << "input size = " << input.size() << endl;
        sampleNum = input.size();
    }
    
    else if(mode == 3)
    {
        //node initialization
        for(int i=0;i<gridRow;i++)
        {
            for(int j=0;j<gridCol;j++)
            {
                w[i][j][0] = (rand()/(double)RAND_MAX-0.5)*2.0;
                
                if(rand()%2 == 0)
                    w[i][j][1] = sqrt(1-w[i][j][0]*w[i][j][0]);
                else
                    w[i][j][1] = -sqrt(1-w[i][j][0]*w[i][j][0]);
                
                win[i][j]=0;
            }
        }
        
        //--------data input------------------------
        stringstream ss;
        char filename[256] = "../input/training/face_ori/face_ori_all.csv";
        ss << filename;
        ifstream ifs(ss.str().c_str());
        
        int time_id;
        float ori1,ori2;
        char split;
        long int count =0;
        long int valid =0;
        
        while(!ifs.eof())
        {
            
            ifs >> time_id >> split >> ori1 >> split >> ori2;
            
            if(ifs.fail())
                break;
        
            time_id_vec.push_back(time_id);
            
            vector<double> temp(2);
            temp[0] = (double)ori1;
            temp[1] = (double)ori2;
            
            count ++;
            
            input.push_back(temp);
            validNum.push_back(valid);
            
            valid++;
        }
        cout << "input size = " << input.size() << endl;
        sampleNum = input.size();
        
    }
    
    else if(mode == 4)
    {
        //node initialization
        for(int i=0;i<gridRow;i++)
        {
            for(int j=0;j<gridCol;j++)
            {
                w[i][j][0] = (rand()/(double)RAND_MAX-0.5)*2.0; //-1〜1
                w[i][j][1] = (rand()/(double)RAND_MAX-0.5)*2.0; //-1〜1
                
                win[i][j]=0;
            }
        }
        
        //--------data input------------------------
        stringstream ss;
        char filename[256] = "../input/training/rri_lp/rri_lp_all.csv";
        ss << filename;
        ifstream ifs(ss.str().c_str());
        
        int time_id;
        float rri_raw,rri_std,rri_lp;
        char split;
        long int count =0;
        long int valid =0;
        
        while(!ifs.eof())
        {
            
            ifs >> time_id >> split >> rri_raw >> split >> rri_std >> split >> rri_lp;
            
            if(ifs.fail())
                break;
            
            time_id_vec.push_back(time_id);
            
            vector<double> temp(2);
            temp[0] = (double)rri_std;
            temp[1] = (double)rri_lp;
            
            count ++;
            
            input.push_back(temp);
            validNum.push_back(valid);
            
            valid++;
        }
        cout << "input size = " << input.size() << endl;
        sampleNum = input.size();
        
    }
    
    else
    {
        cout << "MODE SELECT UNCOMPLETED" << endl;
    }
    
    
    
    
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
    oss << output_directory << "/all_vote.csv";
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
                                
                //data output
                
                if(yorn == 'y')
                {
                    
                    //-----------all--------------
                    if(mode == 1)
                    {
                        
                        all_vote << time_id_vec[sampleNumber] << "," << input[sampleNumber][0]*stdX+x_ave << "," << input[sampleNumber][1]*stdY+y_ave << "," << input[sampleNumber][2] << "," << input[sampleNumber][3]  << "," << input[sampleNumber][4]*stdRRI+rri_ave  << "," << input[sampleNumber][5] << "," << labelcol+1 << "," << labelrow+1 <<endl;
                        
                    }
                    
                    //-----------all end----------
                    
                    
                    
                    //---------location--------------
                    if(mode == 2)
                    {
                        all_vote << time_id_vec[sampleNumber] << "," << input[sampleNumber][0]*stdX+x_ave << "," << input[sampleNumber][1]*stdY+y_ave << "," << labelcol+1 << "," << labelrow+1 <<endl;
                    }
                    
                    //---------location end----------
                    
                    
                    //---------face ori--------------
                    if(mode == 3)
                    {
                        all_vote << input[sampleNumber][0] << "," << input[sampleNumber][1] << "," << labelcol+1 << "," << labelrow+1 <<endl;
                    }
                    
                    //---------face ori end----------
                    
                    //---------rri lp----------------
                    if(mode == 4)
                    {
                        all_vote << time_id_vec[sampleNumber] << ","  << input[sampleNumber][0]*stdRRI+rri_ave  << "," << input[sampleNumber][1] << "," << labelcol+1 << "," << labelrow+1 <<endl;
                    }
                    
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
    
    stringstream wss;
    wss << output_directory << "/node.csv";
    ofstream node(wss.str().c_str());
    
    if(mode == 1)
    {
        node << "x_ave" << "," << x_ave << endl;
        node << "y_ave" << "," << y_ave << endl;
        node << "rri_ave" << "," << rri_ave << endl;
        node << "x_std" << "," << stdX << endl;
        node << "y_std" << "," << stdY << endl;
        node << "rri_std" << "," << stdRRI << endl;
        
    }
    
    else if(mode == 2)
    {
        node << "x_ave" << "," << x_ave << endl;
        node << "y_ave" << "," << y_ave << endl;
        node << "x_std" << "," << stdX << endl;
        node << "y_std" << "," << stdY << endl;
    }
    
    else if(mode == 4)
    {
        node << "rri_ave" << "," << rri_ave << endl;
        node << "rri_std" << "," << stdRRI << endl;
    }
    
    for(int i=0;i<gridRow;i++)
    {
        cout << "{";
        for(int j=0;j<gridCol;j++)
        {
            cout << "{";
            for(int k=0;k<featureNum;k++)
            {
                cout << " " <<w[i][j][k] << " ";
                
                node << w[i][j][k];
                
                if(k == featureNum-1)
                    node << endl;
                else if(k != featureNum-1)
                    node << ",";
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