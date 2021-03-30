#include <iostream>

using namespace std;

#define MAX 10000

const int n = 7;
double p[n + 1] = {0,0.04,0.06,0.08,0.02,0.10,0.12,0.14}; // 相当于p是从1开始数的
double q[n + 1] = {0.06,0.06,0.06,0.06,0.05,0.05,0.05,0.05};//q是从0开始数的

int root[n + 1][n + 1];//Record the root node of the optimal subtree
double e[n + 2][n + 2];//Record the expected cost of the subtree
double w[n + 2][n + 2];//Record the probability sum of the subtree

double cost_sum(int i, int j)
{
    // check out

    if(i>j)
        cout<<"Cost sum error: i>j\n";
    double sum=0;
    for(int k=i;k<=j;k++)
        sum += p[k];
    for(int k=i-1;k<=j;k++)
        sum += q[k];
    //cout<<i<<j<<' '<<sum<<endl;
    return sum;
}


double min_root_find(int i, int k)
{
    if(k==0){
        root[i][i] = i;
        return w[i][i]+q[i-1]+q[i];
    }
        
    int r=i;
    double min_cost=1000;
    double current_cost=0;

    while(r<=i+k)
    {   
        current_cost = e[i][r-1] + e[r+1][i+k] + w[i][i+k];

        if(current_cost<=min_cost)
        {
            min_cost = current_cost;
            root[i][i+k] = r;
        }

        r++;     
    }
    
    
    return min_cost;
}

void optimal_binary_search_tree(double *p,double *q,int n)
{

    for(int i=0;i<=n;++i)
        {
            e[i+1][i] = q[i];
            w[i+1][i] = q[i];
        }

    for(int i=0;i<=n;++i)
        root[i+1][i] = -1;

    for(int i=1;i<=n;++i)
    {
        
        for(int j=i;j<=n;++j)
        {
            //cout<<"j:"<<j<<'\n';
            w[i][j] = cost_sum(i,j);
        }
    }


    for(int k=0;k<=n-1;k++)
    {
        for(int i=1;i<=n-k;i++)
            {
                e[i][i+k] = min_root_find(i, k);
                //cout<<e[i][i+k]<<endl;
            }
    }
}

/*
You can print the structure of the optimal binary search tree based on root[][]
The format of printing is as follows:
k2 is the root
k1 is the left child of k2
d0 is the left child of k1
d1 is the right child of k1
k5 is the right child of k2
k4 is the left child of k5
k3 is the left child of k4
d2 is the left child of k3
d3 is the right child of k3
d4 is the right child of k4
d5 is the right child of k5
*/
void construct_optimal_bst(int i, int j, int r)
{
    if(i>j)
        return;
    if(i==1&&j==n)
        printf("k%d is the root\n", r);

    int left_child = root[i][r-1];
    int right_child = root[r+1][j];
    if(left_child!=-1)
        printf("k%d is the left child of k%d\n",left_child, r);
    if(right_child!=-1)
        printf("k%d is the right child of k%d\n",right_child, r);
    if(left_child==-1)
        printf("d%d is the left child of k%d\n", r-1, r);
    if(i==j||right_child==-1)
        printf("d%d is the right child of k%d\n", r, r);

    construct_optimal_bst(i,r-1, left_child);
    construct_optimal_bst(r+1, j, right_child);
    
}

int main()
{
    
    optimal_binary_search_tree(p,q,n);
    cout<<"The cost of the optimal binary search tree is: "<<e[1][n]<<endl;
    cout << "The structure of the optimal binary search tree is: " << endl;
    int r = root[1][n];
    construct_optimal_bst(1, n, r);
    //cout<<root[4][3]<<endl;
    
}
