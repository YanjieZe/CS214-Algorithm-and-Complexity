#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
/*
The process to calculate the dynamic can be divided into four steps:
1.Create an empty cost matrix DTW with X and Y labels as amplitudes of the two series to be compared.
2.Use the given state transition function to fill in the cost matrix.
3.Identify the warping path starting from top right corner of the matrix and traversing to bottom left. The traversal path is identified based on the neighbor with minimum value.
i.e., When we reach the point (i, j) in the matrix, the next position is to choose the point with the smallest cost among (i-1,j-1), (i,j-1), and (i-1,j),
For the sake of simplicity, when the cost is equal, the priority of the selection is (i-1,j-1), (i,j-1), and (i-1,j) in order.
4.Calculate th time normalized distance. We define it as the average cost of the selected points.
*/
using namespace std;

int min3(int a, int b, int c)
{
    vector<int> tmp;
    int array[]={a, b,c};
    for(int i=0;i<3;++i)
        if(array[i]!=-1)
            tmp.push_back(array[i]);
    int s = tmp.size();
    if(s==0)
        return 0;
    if(s==1)
        return tmp[0];
    if(s==2)
        return min(tmp[0],tmp[1]);
    if(s==3)
        return min(tmp[2],min(tmp[0],tmp[1]));
    return 0;

}

double distance(vector<int> x, vector<int> y, int window_constraint) {
    int n = x.size();
    int m = y.size();
    
    vector<vector<int> > DTW(n), cost_matrix(n);
    
    //Use the given state transition function to fill in the cost matrix.
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
        {
            cost_matrix[i].push_back(abs(x[i] - y[j]));
            DTW[i].push_back(-1);// initialize
        }
    
  
    int a,b,c;
    /* 
    a: DTW[i-1,j]
    b: DTW[i,j-1]
    c: DTW[i-1, j-1]
    */
    a=b=c=0;

    for(int j=0;j<m;++j)
        for(int i=0;i<n;++i)
        {
            if(abs(i-j)>window_constraint)
                continue;
            if(i==0)
                a=-1;
            else
                a=DTW[i-1][j];
            
            if(j==0)
                b=-1;
            else
                b=DTW[i][j-1];
            
            if(i==0||j==0)
                c=-1;
            else
                c=DTW[i-1][j-1];

            
            DTW[i][j] = cost_matrix[i][j] + min3(a,b,c);
            
        }


    //Identify the warping path.
    //like gradient descent
    vector<int> path;
    int i=n-1,j=m-1;
    int tmp=0;
    double result = 0;
    double count = 0;
  
    while(i>=0||j>=0)
    {
        result += cost_matrix[i][j];
        count ++;

        //choose direction
        if(i==0&&j==0)
            break;
        if(i==0)
        {
            j--;
            continue;
        }
        if(j==0)
        {
            i--;
            continue;
        }
        
        tmp = min3(DTW[i-1][j-1], DTW[i-1][j], DTW[i][j-1]);

        if(tmp==DTW[i-1][j-1])
        {
            i--;
            j--;
        }
        else if(tmp==DTW[i-1][j])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    

    //Calculate th time normalized distance
    result = result/count ; 

    return result;
}



int main(){
    int window_constraint = 1;
	vector<int> X,Y;
	//test case 1
	int array1[] = {37,37,38,42,25,21,22,33,27,19,31,21,44,46,28};
	int array2[] ={37,38,42,25,21,22,33,27,19,31,21,44,46,28,28};
    
    for(int i=0;i<15;++i)
        X.push_back(array1[i]), Y.push_back(array2[i]);

    //cout<<min3(-1,1,2)<<endl;   

	cout<<distance(X,Y, window_constraint)<<endl;
    
	//test case 2
	int array3[] = {11,14,15,20,19,13,12,16,18,14};
	int array4[] = {11,17,13,14,11,20,15,14,17,14};

    X.clear();
    Y.clear();

    for(int i=0;i<10;++i)
        X.push_back(array3[i]), Y.push_back(array4[i]);

	cout<<distance(X, Y, window_constraint)<<endl;
	//Remark: when you modify the code to add the window constraint, the distance function has thus three inputs: X, Y, and the size of window w.
	return 0;
}
