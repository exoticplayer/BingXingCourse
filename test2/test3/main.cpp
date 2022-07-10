#include <iostream>
#include<sys/time.h>
#include <fstream>
using namespace std;


//const int n=1000;
const int Max=10000;
const int start=100;
const int mid=100;
const int start2=1000;
const int repeat1=50;
const int repeat2=2;
int main()
{
    //chusihau

    //static int a[n];
    //static int b[n][n];
    //static long long sum[n];
    //n<=1000
    ofstream file("bing1.1.txt");
    for(int n=start;n<=start2;)
    {
        cout << "n=" << n<<":"<<endl;

        struct timeval tv_begin,tv_end;
        long long time1=0;
        long long time2=0;
        for (int r=0;r<repeat1;r++)
        {
            int *a;
            int **b;
            long long *sum;
            a=new int[n];
            b=new int*[n];
            sum=new long long[n];
            for(int i=1;i<=n;i++)
            {
                a[i-1]=i;
                b[i-1]=new int[n];
            }
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                {
                    b[i-1][j-1]=i+j;
                }
            }
            //chushihuajieshu
            gettimeofday(&tv_begin,NULL);
            for(int i=0;i<n;i++)
            {

                sum[i]=0;
                for(int j=0;j<n;j++)
                {
                    sum[i]+=b[j][i]*a[j];
                }
            }

            gettimeofday(&tv_end,NULL);
            unsigned long diff;
            diff = 1000000 * (tv_end.tv_sec-tv_begin.tv_sec)+ tv_end.tv_usec-tv_begin.tv_usec;
            time1+=diff;


            struct timeval tv_begin2,tv_end2;
            gettimeofday(&tv_begin2,NULL);
            for(int i=0;i<n;i++)
            {
                sum[i]=0.0;
            }
            for(int j=0;j<n;j++)
            {

                for(int i=0;i<n;i++)
                {
                    sum[i]+=b[j][i]*a[j];
                }
            }
            gettimeofday(&tv_end2,NULL);
            unsigned long diff2;
            diff2 = 1000000 * (tv_end2.tv_sec-tv_begin2.tv_sec)+ tv_end2.tv_usec-tv_begin2.tv_usec;
            time2+=diff2;

        }
//        time1=time1/repeat1;
//        time2=time2/repeat1;
        file<<n<<" "<<time1/1000.0/repeat1<<" "<<time2/1000.0/repeat1<<" "<<(double)((time1/1000.0/repeat1)/(time2/1000.0/repeat1))<<endl;
        n+=mid;
//        cout<<"平凡算法"<<"时间 :"<<time1*1000.0/freq<<"ms"<<endl;
//        cout<<"cache算法"<<"时间 :"<<time2*1000.0/freq<<"ms"<<endl;
//        cout<<"Speedup ratio:"<<(double)((time1*1000.0/freq)/(time2*1000.0/freq))<<endl;
//        cout<<endl;
    }
    //n>1000
       for(int n=start2+mid;n<=Max;)
    {
        cout << "n=" << n<<":"<<endl;
        struct timeval tv_begin,tv_end;
        long long time1=0;
        long long time2=0;
        for (int r=0;r<repeat2;r++)
        {
            int *a;
            int **b;
            long long *sum;
            a=new int[n];
            b=new int*[n];
            sum=new long long[n];
            for(int i=1;i<=n;i++)
            {
                a[i-1]=i;
                b[i-1]=new int[n];
            }
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                {
                    b[i-1][j-1]=i+j;
                }
            }
            //chushihuajieshu
            gettimeofday(&tv_begin,NULL);
            for(int i=0;i<n;i++)
            {

                sum[i]=0;
                for(int j=0;j<n;j++)
                {
                    sum[i]+=b[j][i]*a[j];
                }
            }
            gettimeofday(&tv_end,NULL);
            unsigned long diff;
            diff = 1000000 * (tv_end.tv_sec-tv_begin.tv_sec)+ tv_end.tv_usec-tv_begin.tv_usec;
            time1+=diff;

            struct timeval tv_begin2,tv_end2;
            gettimeofday(&tv_begin2,NULL);
            for(int i=0;i<n;i++)
            {
                sum[i]=0.0;
            }
            for(int j=0;j<n;j++)
            {

                for(int i=0;i<n;i++)
                {
                    sum[i]+=b[j][i]*a[j];
                }
            }
            gettimeofday(&tv_end2,NULL);
            unsigned long diff2;
            diff2 = 1000000 * (tv_end2.tv_sec-tv_begin2.tv_sec)+ tv_end2.tv_usec-tv_begin2.tv_usec;
            time2+=diff2;


        }
        time1=time1/repeat2;
        time2=time2/repeat2;
        file<<n<<" "<<time1/1000.0<<" "<<time2/1000.0<<" "<<(double)((time1/1000.0)/(time2/1000.0))<<endl;
        n+=mid*10;
        cout<<"平凡算法"<<"时间 :"<<time1/1000.0/<<"ms"<<endl;
        cout<<"cache算法"<<"时间 :"<<time2/1000.0/<<"ms"<<endl;
        cout<<"Speedup ratio:"<<(double)((time1/1000.0)/(time2/1000.0))<<endl;
        cout<<endl;
    }


    return 0;
}
