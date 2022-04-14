#include <iostream>
#include <xmmintrin.h> //SSE
#include <emmintrin.h> //SSE2
#include <pmmintrin.h> //SSE3
#include <tmmintrin.h> //SSSE3
#include <smmintrin.h> //SSE4.1
#include <nmmintrin.h> //SSSE4.2
#include <windows.h>
#include <immintrin.h> //AVX、AVX2
#include<fstream>
using namespace std;
int n=50;
float **B;
void m_reset(int n)
{

    B=new float*[n];
    for(int i=0;i<n;i++)
        B[i]=new float[n];
  for(int i=0;i<n;i++)
  {
      for(int j=0;j<i;j++)
        B[i][j]=0;
      B[i][i]=1.0;
      for(int j=i+1;j<n;j++)
      {
         B[i][j]=rand();
      }

  }
  for(int k=0;k<n;k++)
  {

      for(int i=k+1;i<n;i++)
      {
          for(int j=0;j<n;j++)
            B[i][j]+=B[k][j];
      }
  }

}
void chuanxing(ofstream &result,float **A)
{
    long long head,tail,freq ; // timers
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq );
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for (int k = 0; k < n; k++)
    {
		for (int j = k + 1; j < n; j++)
		{
			A[k][j] /= A[k][k];
		}
		A[k][k] = 1.0;
		for (int i = k + 1; i < n; i++)
		{
			for (int j = k + 1; j < n; j++)
			{
				A[i][j] -= A[i][k] * A[k][j];
			}
			A[i][k] = 0;
		}
	}
	QueryPerformanceCounter((LARGE_INTEGER *)&tail );
	//cout <<(tail-head)*1000.0/freq<<"ms"<<endl;
	result << (tail-head)*1000.0 / (1000.0*freq)<<"      ";
}
void two_paerll(ofstream &result,float **A)
{
    long long head,tail,freq ; // timers
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq );
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for(int k=0;k<n;k++)
    {
         __m256 vt = _mm256_set1_ps(A[k][k]); // 存储的四个 float32 都初始化为A[k][k]
        int j;
        for(j=k+1;j+8<=n;j+=8)
        {
            __m256 va= _mm256_loadu_ps(&A[k][j]);
            va= _mm256_div_ps(va,vt);
            _mm256_storeu_ps(&A[k][j], va);// 将 q0 中 4 个 float32，赋值给以 d1 为起始地址的 4 个 float32


        }
        while(j<n)
            {
                A[k][j]=A[k][j]/A[k][k];
                j++;
            }
        A[k][k]=1.0;
        for(int i=k+1;i<n;i++)
        {
            for(int j=k+1;j<n;j++)
                A[i][j]-=A[i][k]*A[k][j];
            A[i][k]=0;
        }

    }
    QueryPerformanceCounter((LARGE_INTEGER *)&tail );
	//cout <<(tail-head)*1000.0 / freq<<"ms"<<endl;
	result << (tail-head)*1000.0 / (freq*1000.0)<<"         ";

}
void three_paerll(ofstream &result,float **A)
{
    long long head,tail,freq ; // timers
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq );
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for(int k=0;k<n;k++)
    {
        for(int j=k+1;j<n;j++)
            A[k][j]/=A[k][k];
        A[k][k]=1.0;
        for(int i=k+1;i<n;i++)
        {
            __m256 vaik=_mm256_set1_ps(A[i][k]);
            int j=k+1;
            for(j=k+1;j+8<=n;j+=8)
            {
                __m256 vakj=_mm256_loadu_ps(&A[k][j]);
                __m256 vaij=_mm256_loadu_ps(&A[i][j]);
                __m256 vx=_mm256_mul_ps(vakj,vaik);
                vaij=_mm256_sub_ps(vaij,vx);

                _mm256_storeu_ps(&A[i][j], vaij);

            }
            while(j<n)
            {
                A[i][j]-=A[k][j]*A[i][k];
                j++;
            }
            A[i][k]=0;

        }

    }
   QueryPerformanceCounter((LARGE_INTEGER *)&tail );
	//cout <<(tail-head)*1000.0 / freq<<"ms"<<endl;
	result << (tail-head)*1000.0 / (1000.0*freq)<<"      ";


}
void all_paerll(ofstream &result,float **A)
{
    long long head,tail,freq ; // timers
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq );
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for(int k=0;k<n;k++)
    {
        __m256 vt = _mm256_set1_ps(A[k][k]); // 存储的四个 float32 都初始化为A[k][k]
        int j;
        for(j=k+1;j+8<=n;j+=8)
        {
              __m256 va= _mm256_loadu_ps(&A[k][j]);
            va= _mm256_div_ps(va,vt);
            _mm256_storeu_ps(&A[k][j], va);// 将 q0 中 4 个 float32，赋值给以 d1 为起始地址的 4 个 float32

        }
        while(j<n)
            {
                A[k][j]=A[k][j]/A[k][k];
                j++;
            }
        A[k][k]=1.0;
      for(int i=k+1;i<n;i++)
        {
             __m256 vaik=_mm256_set1_ps(A[i][k]);
            int j=k+1;
            for(j=k+1;j+8<=n;j+=8)
            {
                __m256 vakj=_mm256_loadu_ps(&A[k][j]);
                __m256 vaij=_mm256_loadu_ps(&A[i][j]);
                __m256 vx=_mm256_mul_ps(vakj,vaik);
                vaij=_mm256_sub_ps(vaij,vx);

                _mm256_storeu_ps(&A[i][j], vaij);
            }
            while(j<n)
            {
                A[i][j]-=A[k][j]*A[i][k];
                j++;
            }
            A[i][k]=0;

        }

    }
    QueryPerformanceCounter((LARGE_INTEGER *)&tail );
	//cout << (tail-head)*1000.0 / freq<<"ms"<<endl;
    result << (tail-head)*1000.0 / (1000.0*freq)<<"      ";
}
void all_paerll_duiqi(ofstream &result,float **A)//全并行的对齐
{
    long long head,tail,freq ; // timers
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq );
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for(int k=0;k<n;k++)
    {
         __m256 vt = _mm256_set1_ps(A[k][k]); // 存储的四个 float32 都初始化为A[k][k]
         int j=k+1;
        while(j%8!=0)
        {
            A[k][j] /= A[k][k];
            j++;
        }
        for(;j+8<=n;j+=8)
        {
            __m256 va= _mm256_loadu_ps(&A[k][j]);
            va= _mm256_div_ps(va,vt);
            _mm256_storeu_ps(&A[k][j], va);// 将 q0 中 4 个 float32，赋值给以 d1 为起始地址的 4 个 float32


        }
        while(j<n)
            {
                A[k][j]=A[k][j]/A[k][k];
                j++;
            }
        A[k][k]=1.0;
      for(int i=k+1;i<n;i++)
        {
             __m256 vaik=_mm256_set1_ps(A[i][k]);
            int j=k+1;
            while(j%8!=0)
            {
                A[i][j] -= A[i][k] * A[k][j];
                j++;
            }
            for(;j+8<=n;j+=8)
            {
                __m256 vakj=_mm256_loadu_ps(&A[k][j]);
                __m256 vaij=_mm256_loadu_ps(&A[i][j]);
                __m256 vx=_mm256_mul_ps(vakj,vaik);
                vaij=_mm256_sub_ps(vaij,vx);

                _mm256_storeu_ps(&A[i][j], vaij);
            }
            while(j<n)
            {
                A[i][j]-=A[k][j]*A[i][k];
                j++;
            }
            A[i][k]=0;


        }

    }
    QueryPerformanceCounter((LARGE_INTEGER *)&tail );
	//cout << (tail-head)*1000.0 / freq<<"ms"<<endl;
    result << (tail-head)*1000.0 / (1000.0*freq)<<"      ";

}
int main()
{
    ofstream result("C:\\Users\\26937\\Desktop\\SIMDX86_AVX.txt");
    while(n<1500)
    {
        m_reset(n);
        //cout<<"n="<<n<<":"<<endl;
        float **A=new float*[n];
        for(int i=0;i<n;i++)
            A[i]=new float[n];
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<i;j++)
                A[i][j]=B[i][j];

        }

        result<<n<<"        ";
        chuanxing(result,A);
        two_paerll(result,A);
        three_paerll(result,A);
        all_paerll(result,A);
        all_paerll_duiqi(result,A);
        result<<endl;
        n+=100;
    }
}

