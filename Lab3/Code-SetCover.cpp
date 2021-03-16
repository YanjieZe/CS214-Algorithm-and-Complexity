#include <iostream>

using namespace std;

void quickSort(int s[], int l, int r)
{
    if (l< r)
    {
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j]>= x)
                j--;
            if(i < j)
                s[i++] = s[j];
            while(i < j && s[i]< x)
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quickSort(s, l, i - 1);
        quickSort(s, i + 1, r);
    }
}

int Greedy(int x[], int k, int n)
{
    quickSort(x, 0, n-1);
    int i=0, num=0;

    //for(int i=0;i<7;++i)cout<<x[i]<<'\n';

    while(i<n-1)
    {
        int a_i = i;
        int interval = x[i] + k;
        int m=0;
        while(i<n-1)
        {   
            i++;
            if(x[i]<=interval)
                {              
                    m++;
                }
            else {
                break;
            }
        }
        num++;
        i=a_i+m;
        if(i==n-1)
            return num;
        i++;
        if(i==n-1)
            return num+1;      
    }
    return 0;  
}

int main()
{
    //x is the point set P with n=7 nodes in total, and the length of intervals is k=3.
    int x[7]={1,2,3,4,5,6,-2};
    int k=3;
    int n= sizeof(x) / sizeof(x[0]);
    int num_interval=Greedy(x,k,n);
    cout << num_interval << endl;
    return 0;
}
