#include "ITR.h"

ITR::ITR(DataGeneration &data)
{
    var_Type = data.getVarType();
    sample_Size = data.getSampleSize();
    var_Size = data.getVariateSize();
    action_Size = data.getActionSize();
    y_Size = data.getYSize();
    T0 = data.getSumT0();

    var_X = new int*[sample_Size] {};
    var_A = new int*[sample_Size] {};
    var_Y = new double*[sample_Size];
    table_X = new bool**[var_Size] {};
    cut_Size = new int[var_Size] {};

    info = new DataInfo[var_Size];
    for(int i=0; i<var_Size; ++i)
    {
        info[i].load_DataInfo(i,var_Type[i],data.getDataSet()[i]);
    }
    load_Range();

    for(int i=0; i<sample_Size; ++i)
    {
        var_X[i] = new int[var_Size] {};
        var_A[i] = new int[action_Size] {};
        var_Y[i] = new double[y_Size] {};
    }
    load_X(data.getDataSet());
    load_Action(data.getActions());
    load_Y(data.getY());


    for(int i=0; i<var_Size; ++i)
    {
        table_X[i] = new bool*[cut_Size[i]] {};
        for(int j=0; j<cut_Size[i]; ++j)
        {
            table_X[i][j] = new bool[sample_Size] {};
        }
    }
    load_table_X(data.getDataSet());
}

ITR::~ITR()
{
    //dtor
    cleanAll();
}

/// Get
int ITR::getSampleSize()
{
    return sample_Size;
}
int ITR::getVarSize()
{
    return var_Size;
}
int ITR::getActionSize()
{
    return action_Size;
}
int ITR::getYSize()
{
    return y_Size;
}

/// Print
void ITR :: print_X()
{
    for(int i=0; i<sample_Size; ++i)
    {
        for(int j=0; j<var_Size; ++j)
        {
            cout<<var_X[i][j]<<' ';
        }
        cout<<endl;
    }
}

void ITR :: print_Action()
{
    for(int i=0; i<sample_Size; ++i)
    {
        for(int j=0; j<action_Size; ++j)
        {
            cout<<var_A[i][j]<<' ';
        }
        cout<<endl;
    }
}

void ITR :: print_Y()
{
    for(int i=0; i<sample_Size; ++i)
    {
        for(int j=0; j<y_Size; ++j)
        {
            cout<<var_Y[i][j]<<' ';
        }
        cout<<endl;
    }
}

void ITR :: print_All()
{
    for(int i=0; i<sample_Size; ++i)
    {
        cout<<"X: ";
        for(int x=0; x<var_Size; ++x)
        {
            cout<<var_X[i][x]<<' ';
        }
        cout<<" Action: ";
        for(int y=0; y<action_Size; ++y)
        {
            cout<<var_A[i][y]<<' ';
        }
        cout<<" Y: ";
        for(int z=0; z<y_Size; ++z)
        {
            cout<<var_Y[i][z]<<' ';
        }
        cout<<endl;
    }
}

void ITR :: print_Range()
{
    cout<<"Cut range:\n";
    for(int i=0; i<var_Size; ++i)
    {
        cout<<cut_Size[i]<<' ';
    }
}

void ITR :: print_Type()
{
    cout<<"Covariant type:\n";
    for(int i=0; i<var_Size; ++i)
    {
        cout<<var_Type[i]<<' ';
    }
}

void ITR :: print_CutTable()
{
    for(int i=0; i<var_Size; ++i)
    {
        cout<<"Var: "<<i
            <<"\tType: "<<var_Type[i]
            <<"\tCut Size: "<<cut_Size[i]
            <<endl;
        cout<<"\t ";


        for(int xi=0; xi<sample_Size; ++xi)
        {
            cout<<var_X[xi][i]<<' ';
        }
        cout<<endl;
        for(int j=0; j<cut_Size[i]; ++j)
        {
            if(var_Type[i]==2)
            {
                cout<<info[i].getRange(j)<<":";
                info[i].printSet(j);
            }
            else
            {
                cout<<info[i].getRange(j)<<":\t";
            }
            for(int k=0; k<sample_Size; ++k)
            {
                cout<<table_X[i][j][k]<<' ';
            }
            cout<<endl;
        }
        cout<<endl;
    }
}

void ITR :: print_VarInfo(int i)
{
    info[i].printVarInfo();
}

void ITR :: print_VarInfo()
{
    for(int i=0; i<var_Size; ++i)
    {
        info[i].printVarInfo();
        cout<<endl;
    }
}


/// Load
void ITR :: load_Range()
{
    for(int i=0; i<var_Size; ++i)
    {
        cut_Size[i] = info[i].getCutSize();
    }
}


void ITR :: load_X(vector<vector<int>> x)
{
    for(int i=0; i<sample_Size; ++i)
    {
        for(int j=0; j<var_Size; ++j)
        {
            var_X[i][j] = x[j][i];
        }
    }
}

void ITR :: load_Action(vector<vector<int>> a)
{
    for(int i=0; i<sample_Size; ++i)
    {
        for(int j=0; j<action_Size; ++j)
        {
            var_A[i][j] = a[j][i];
        }
    }
}

void ITR :: load_Y(vector<vector<double>> y)
{
    for(int i=0; i<sample_Size; ++i)
    {
        for(int j=0; j<y_Size; ++j)
        {
            var_Y[i][j] = y[j][i];
        }
    }
}


void ITR :: load_table_X(vector<vector<int>> x)
{
    for(int i=0; i<var_Size; ++i)
    {
        for(int j=0; j<sample_Size; ++j)
        {
            for(int k=0; k<cut_Size[i]; ++k)
            {
                table_X[i][k][j] = (var_Type[i] == 2)?info[i].nomContains(x[i][j],k):x[i][j] < info[i].getRange(k);
            }
        }
    }
}

void ITR :: cleanAll()
{
    for(int i=0; i<sample_Size; ++i)
    {
        delete [] var_X[i];
        delete [] var_A[i];
        delete [] var_Y[i];
    }
    delete var_X;
    delete var_A;
    delete var_Y;

    for(int i=0; i<var_Size; ++i)
    {
        for(int j=0; j<cut_Size[i]; ++j)
        {
            delete [] table_X[i][j];
        }
        delete [] table_X[i];
    }
    delete table_X;
    delete [] cut_Size;
    delete [] info;
}


void ITR :: threeDepthPrint()
{
    double v[16];
    double sum[8];

    bool*  x1c;
    bool*  x2c;
    bool*  x3c;

    int* row_A;
    double* row_Y;

    double bestLocal;
    int bestIndexLocal;
    int indexi, indexj, indexk;
    int cuti, cutj, cutk;


    for(int i=0; i<var_Size; ++i)   // loop1
    {
        for(int j=i+1; j<var_Size; ++j)    // loop2
        {
            for(int k=j+1; k<var_Size; ++k)    // loop3
            {
                bestLocal = 0.0;
                bestIndexLocal = 0;
                indexi = 0, indexj = 0, indexk = 0;
                cuti = 0, cutj = 0, cutk = 0;

                for(int xi=0; xi<cut_Size[i]; ++xi) // loop4
                {
                    x1c = table_X[i][xi];
                    for(int xj=0; xj<cut_Size[j]; ++xj)        // loop5
                    {

                        x2c = table_X[j][xj];
                        for(int xk=0; xk<cut_Size[k]; ++xk) // loop6
                        {
                            x3c = table_X[k][xk];

                            std::fill_n(v,16,0.0);
                            for(int p=0; p<sample_Size; ++p)
                            {
                                row_Y = var_Y[p];
                                row_A = var_A[p];
                                v[x1c[p]*8+x2c[p]*4+x3c[p]*2 + *row_A] =  *row_Y;
                            }

                            sum[0] = v[0]-v[1];
                            sum[1] = v[2]-v[3];
                            sum[2] = v[4]-v[5];
                            sum[3] = v[6]-v[7];
                            sum[4] = v[8]-v[9];
                            sum[5] = v[10]-v[11];
                            sum[6] = v[12]-v[13];
                            sum[7] = v[14]-v[15];

                            const auto ptr = max_element(sum,sum+8);
                            double temp = *ptr + T0;

                            if(temp > bestLocal)
                            {
                                bestLocal = temp;
                                bestIndexLocal = distance(sum, ptr);
                                indexi = i;
                                indexj = j;
                                indexk = k;
                                cuti = xi;
                                cutj = xj;
                                cutk = xk;
                            }
                        } // end loop 6
                    } // end loop 5
                } // end loop 4
                cout<<bestLocal*2/sample_Size<<" Index: "
                    <<"["<<indexi<<" "<<cuti<<" "
                    <<"] ["<<indexj<<" "<<cutj<<" "
                    <<"] ["<<indexk<<" "<<cutk<<" "
                    <<"]"<<bestIndexLocal<<endl;
            } // end loop 3
        } // end loop 2
    } // end loop 1
} // end threeDepthPrint()




vector<Result *> ITR :: threeDepth()
{
    vector<Result *> solutions;
    solutions.reserve(20000000);
    double v[16];

    bool*  x1c;
    bool*  x2c;
    bool*  x3c;

    int* row_A;
    double* row_Y;

    for(int i=0; i<var_Size; ++i)   // loop1
    {

        for(int j=i+1; j<var_Size; ++j)    // loop2
        {

            for(int k=j+1; k<var_Size; ++k)    // loop3
            {
                for(int xi=0; xi<cut_Size[i]; ++xi)            // loop4
                {
                    x1c = table_X[i][xi];
                    for(int xj=0; xj<cut_Size[j]; ++xj)        // loop5
                    {
                        x2c = table_X[j][xj];
                        for(int xk=0; xk<cut_Size[k]; ++xk)    // loop6
                        {
                            x3c = table_X[k][xk];

                            std::fill_n(v,16,0.0);
                            for(int p=0; p<sample_Size; ++p)
                            {
                                row_Y = var_Y[p];
                                row_A = var_A[p];
                                v[x1c[p]*8+x2c[p]*4+x3c[p]*2 + *row_A] =  *row_Y;
                            }

                            solutions.push_back(new Result(T0+v[0]-v[1],i,xi,0,j,xj,0,k,xk,0));
                            solutions.push_back(new Result(T0+v[2]-v[3],i,xi,0,j,xj,0,k,xk,1));
                            solutions.push_back(new Result(T0+v[4]-v[5],i,xi,0,j,xj,1,k,xk,0));
                            solutions.push_back(new Result(T0+v[6]-v[7],i,xi,0,j,xj,1,k,xk,1));
                            solutions.push_back(new Result(T0+v[8]-v[9],i,xi,1,j,xj,0,k,xk,0));
                            solutions.push_back(new Result(T0+v[10]-v[11],i,xi,1,j,xj,0,k,xk,1));
                            solutions.push_back(new Result(T0+v[12]-v[13],i,xi,1,j,xj,1,k,xk,0));
                            solutions.push_back(new Result(T0+v[14]-v[15],i,xi,1,j,xj,1,k,xk,1));
                        } // end loop 6
                    } // end loop 5
                } // end loop 4
            } // end loop 3
        } // end loop 2
    } // end loop 1
    return solutions;
}
