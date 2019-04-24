#include<iostream>
#include<cmath>
#include<vector>
#include<ctime>
using namespace std;

//ToDo :: Make a graph of time complexity vs size for both the methods comparison

// function to add two matrixes
vector<vector<int>> add(vector<vector<int>> A, vector<vector<int>> B, int n)
{
	vector<vector<int>> C(n, vector<int>(n, 0));
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	return C;
}

// function to subtract two matrixes
vector<vector<int>> subtract(vector<vector<int>> A, vector<vector<int>> B, int n)
{
	vector<vector<int>> C(n, vector<int>(n, 0));
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
	return C;
}

// Two Conditions:
// Both the matrix should be square matrixes
// n should be a power of 2 which is the size of both matrixes
vector<vector<int>> Strassen(vector<vector<int>> A, vector<vector<int>> B, int n)
{
	vector<vector<int>> C(n, vector<int>(n, 0));
	
	if(n == 1)
	{
		vector<int> row;
		row.push_back(A[0][0]*B[0][0]);
		C.push_back(row);
	}
	
	else if(n == 2)
	{
		int m1= (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
		int m2= (A[1][0] + A[1][1]) * B[0][0];
		int m3= A[0][0] * (B[0][1] - B[1][1]);
		int m4= A[1][1] * (B[1][0] - B[0][0]);
		int m5= (A[0][0] + A[0][1]) * B[1][1];
		int m6= (A[1][0] - A[0][0]) * (B[0][0]+B[0][1]);
		int m7= (A[0][1] - A[1][1]) * (B[1][0]+B[1][1]);
		 
		C[0][0] = m1 + m4- m5 + m7;
		C[0][1] = m3 + m5;
		C[1][0] = m2 + m4;
		C[1][1] = m1 - m2 + m3 + m6;
	}
	
	else
	{
		vector<vector<int>> a1(n/2, vector<int>(n/2, 0));
		vector<vector<int>> a2(n/2, vector<int>(n/2, 0));
		vector<vector<int>> a3(n/2, vector<int>(n/2, 0));
		vector<vector<int>> a4(n/2, vector<int>(n/2, 0));
	
		vector<vector<int>> b1(n/2, vector<int>(n/2, 0));
		vector<vector<int>> b2(n/2, vector<int>(n/2, 0));
		vector<vector<int>> b3(n/2, vector<int>(n/2, 0));
		vector<vector<int>> b4(n/2, vector<int>(n/2, 0));
		
		for(int i = 0;i<n/2;i++)
		{
			for(int j = 0;j<n/2;j++)
			{
				a1[i][j] = A[i][j];
				b1[i][j] = B[i][j];
			}
		}
		
		for(int i = 0;i<n/2;i++)
		{
			for(int j = n/2;j<n;j++)
			{
				a2[i][j-n/2] = A[i][j];
				b2[i][j-n/2] = B[i][j];
			}
		}
		
		for(int i = n/2;i<n;i++)
		{
			for(int j = 0;j<n/2;j++)
			{
				a3[i-n/2][j] = A[i][j];
				b3[i-n/2][j] = B[i][j];
			}
		}
		
		for(int i = n/2;i<n;i++)
		{
			for(int j = n/2;j<n;j++)
			{
				a4[i-n/2][j-n/2] = A[i][j];
				b4[i-n/2][j-n/2] = B[i][j];
			}
		}
		
		vector<vector<int>> m1(n/2, vector<int>(n/2, 0));
		vector<vector<int>> m2(n/2, vector<int>(n/2, 0));
		vector<vector<int>> m3(n/2, vector<int>(n/2, 0));
		vector<vector<int>> m4(n/2, vector<int>(n/2, 0));
		vector<vector<int>> m5(n/2, vector<int>(n/2, 0));
		vector<vector<int>> m6(n/2, vector<int>(n/2, 0));
		vector<vector<int>> m7(n/2, vector<int>(n/2, 0));
		
		m1 = Strassen(add(a1, a4, n/2), add(b1, b4, n/2), n/2);
		m2 = Strassen(add(a3, a4, n/2), b1, n/2);
		m3 = Strassen(a1, subtract(b2, b4, n/2), n/2);
		m4 = Strassen(a4, subtract(b3, b1, n/2), n/2);
		m5 = Strassen(add(a1, a2, n/2), b4, n/2);
		m6 = Strassen(subtract(a3, a1, n/2), add(b1, b2, n/2), n/2);
		m7 = Strassen(subtract(a2, a4, n/2), add(b3, b4, n/2), n/2);
		
		vector<vector<int>> c1(n/2, vector<int>(n/2, 0));
		vector<vector<int>> c2(n/2, vector<int>(n/2, 0));
		vector<vector<int>> c3(n/2, vector<int>(n/2, 0));
		vector<vector<int>> c4(n/2, vector<int>(n/2, 0));
		
		c1 = subtract(add(add(m1, m4, n/2), m7, n/2), m5, n/2);
		c2 = add(m3, m5, n/2);
		c3 = add(m2, m4, n/2);
		c4 = subtract(add(add(m1, m3, n/2), m6, n/2), m2, n/2);
		
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<n;j++)
			{
				if(i<n/2 && j<n/2)
				{
					C[i][j] = c1[i][j];
				}
				else if(i<n/2)
				{
					C[i][j] = c2[i][j-n/2];
				}
				else if(j<n/2)
				{
					C[i][j] = c3[i-n/2][j];
				}
				else
				{
					C[i][j] = c4[i-n/2][j-n/2];
				}
			}
		}
	}
	
	return C;
}

// Normal Matrix multiplication
vector<vector<int>> MProd(vector<vector<int>> A, vector<vector<int>> B)
{
	int n = A.size();
	vector<vector<int>> C(n, vector<int>(n, 0));
	
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			int x = 0;
			for(int k = 0;k<n;k++)
			{
				x = x + A[i][k]*B[k][j];
			}
			C[i][j] = x;
		}
	}
	
	return C;
}

// function to generate random matrix of size n
vector<vector<int>> randmat(int n)
{
	vector<vector<int>> v(n, vector<int>(n, 0));
	
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			v[i][j] = rand();
		}
	}
	
	return v;
}
int main()
{
	int n;
	cout<<"Size :";
	cin>>n;
	
	clock_t time_normal, time_strassen;
	
	vector<vector<int>> A(n, vector<int>(n, 0));
	vector<vector<int>> B(n, vector<int>(n, 0));
	vector<vector<int>> C(n, vector<int>(n, 0));
	
	cout<<"Matrix A\n";
	A = randmat(n);
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			//cin>>A[i][j];
			cout<<A[i][j];
			cout<<" ";
		}
		cout<<endl;
	}
	
	cout<<"Matrix B\n";
	B = randmat(n);
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			//cin>>B[i][j];
			cout<<B[i][j];
			cout<<" ";
		}
		cout<<endl;
	}
	
	time_strassen = clock();
	C = Strassen(A, B, n);
	time_strassen = clock()-time_strassen;
	
	cout<<"Matrix C"<<endl;

	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			cout<<C[i][j];
			cout<<" ";
		}
		cout<<endl;
	}
	
	vector<vector<int>> D(n, vector<int>(n, 0));
	
	time_normal = clock();
	D = MProd(A, B);
	time_normal = clock() - time_normal;
	
	cout<<"Matrix D"<<endl;
	
	bool same = true;

	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			cout<<D[i][j];
			cout<<" ";
			if(D[i][j] != C[i][j])
			{
				same = false;
			}
		}
		cout<<endl;
	}	
	
	if(same == true)
	{
		cout<<"Multiplicatoin is Right!"<<endl;
	}
	else
	{
		cout<<"Multiplication is Wrong!"<<endl;
	}
	
	cout<<"Normal Multiplication time is "<<(float)time_normal/CLOCKS_PER_SEC<<endl;
	cout<<"Strassen Multiplication time is "<<(float)time_strassen/CLOCKS_PER_SEC<<endl;
	
}
