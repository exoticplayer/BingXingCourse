#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <fstream>
using namespace std;
int*a;
long long sum;
int scale=10;
void recursion(int n)
 {
     if (n == 1)
        return;
     else
     {
         for (int i = 0; i < n / 2; i++)
            a[i]+=a[n-i-1];
         n = n / 2;
         recursion(n);
    }
 }
void init(int N)
{
    sum=0;
    a=new int[N];
    for(int i=0;i<N;i++)
    {
        a[i]=i+1;
    }
}
int main()
{
    while(scale<100000)
    {
        init(scale);
        //common
        cout<<"数据规模为"<<scale<<":"<<endl;
        if(scale<1000)
        {
            struct timeval tv_begin,tv_end;
            gettimeofday(&tv_begin,NULL);
            int repeat=0;
            while(repeat<100)
            {
                for(int i=0;i<scale;i++)
                sum+=a[i];
                repeat++;
            }
            gettimeofday(&tv_end,NULL);
            double space = 1000000 * (tv_end.tv_sec-tv_begin.tv_sec)+ tv_end.tv_usec-tv_begin.tv_usec;
            space=space/1000.0/repeat;
            cout<<"平凡算法 "<<space<<endl;

            //cache
            struct timeval tv_begin2,tv_end2;
            gettimeofday(&tv_begin2,NULL);
            repeat=0;
            while(repeat<100)
            {
                long sum1 = 0;
                long sum2 = 0;
                for (int i = 0;i < scale; i += 2)
                {
                    sum1 += a[i];
                    sum2 += a[i + 1];
                }
                sum = sum1 + sum2;
                repeat++;
            }
            gettimeofday(&tv_end2,NULL);
            double space1 = 1000000 * (tv_end2.tv_sec-tv_begin2.tv_sec)+ tv_end2.tv_usec-tv_begin2.tv_usec;
            space1=space1/1000.0/repeat;
            cout<<"链式算法 "<<space1<<endl;
            //递归
            struct timeval tv_begin3,tv_end3;
            gettimeofday(&tv_begin3,NULL);
            repeat=0;
            while(repeat<100)
            {
                recursion(scale);
                repeat++;
            }
            gettimeofday(&tv_end3,NULL);
            double space2 = 1000000 * (tv_end3.tv_sec-tv_begin3.tv_sec)+ tv_end3.tv_usec-tv_begin3.tv_usec;
            space2=space2/1000.0/repeat;
            cout<<"链式算法 "<<space2<<endl;

        }
        //<1000
        else
        {
            struct timeval tv_begin,tv_end;
            gettimeofday(&tv_begin,NULL);
                for(int i=0;i<scale;i++)
                    sum+=a[i];

             gettimeofday(&tv_end,NULL);
            double space = 1000000 * (tv_end.tv_sec-tv_begin.tv_sec)+ tv_end.tv_usec-tv_begin.tv_usec;
            space=space/1000.0;
            cout<<"平凡算法 "<<space<<endl;

            //cache
            struct timeval tv_begin2,tv_end2;
            gettimeofday(&tv_begin2,NULL);

                long sum1 = 0;
                long sum2 = 0;
                for (int i = 0;i < scale; i += 2)
                {
                    sum1 += a[i];
                    sum2 += a[i + 1];
                }
                sum = sum1 + sum2;

            gettimeofday(&tv_end2,NULL);
            double space1 = 1000000 * (tv_end2.tv_sec-tv_begin2.tv_sec)+ tv_end2.tv_usec-tv_begin2.tv_usec;
            space1=space1/1000.0;
            cout<<"链式算法 "<<space1<<endl;
            //递归
            struct timeval tv_begin3,tv_end3;
            gettimeofday(&tv_begin3,NULL);
            recursion(scale);

            gettimeofday(&tv_end3,NULL);
            double space2 = 1000000 * (tv_end3.tv_sec-tv_begin3.tv_sec)+ tv_end3.tv_usec-tv_begin3.tv_usec;
            space2=space2/1000.0;
            cout<<"递归算法 "<<space2<<endl;

        }

        scale+=scale;
    }

    return 0;
}
