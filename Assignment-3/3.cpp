#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
void hit_miss_rates(int size, int block_size, int n, string filename)
{
	double h1 = 0, h2 = 0, h3 = 0 ,h4 = 0 ,h5 = 0,h6 = 0, m1 = 0, m2 = 0, m3 = 0, m4 = 0, m5 = 0, m6 = 0;
	int r1 = size * 1024 / block_size; 
	long long int c1[r1];
	long long int t1[r1];
	int8_t v1[r1];
	int i;
	for(i = 0; i < r1;i++)
	{
		v1[i] = 0;
	}
	//reading trace file	
	char ch; 
	FILE *fp;
	char fp_name[n];
	fp_name[n] = '\n';
	strcpy(fp_name, filename.c_str());
	fp = fopen(fp_name,"rb");
	while(1)
	{
		ch = getc(fp);
		if(ch == EOF)
		{
			break;
		}
		char add[8];
		int temp[8];
		if(ch == 'x')
		{
			long long int address = 0;
			fread(&add, 8, 1, fp);
			for(i = 0;i < 8;i++)
			{
				switch(add[i])
				{
					case ('0'):
						temp[i] = 0;
						break;
					case ('1'):
						temp[i] = 1;
						break;
					case ('2'):
						temp[i] = 2;
						break;
					case ('3'):
						temp[i] = 3;
						break;
					case ('4'):
						temp[i] = 4;
						break;
					case ('5'):
						temp[i] = 5;
						break;
					case ('6'):
						temp[i] = 6;
						break;
					case ('7'):
						temp[i] = 7;
						break;
					case ('8'):
						temp[i] = 8;
						break;
					case ('9'):
						temp[i] = 9;
						break;
					case ('a'):
						temp[i] = 10;
						break;
					case ('b'):
						temp[i] = 11;
						break;
					case ('c'):
						temp[i] = 12;
						break;
					case ('d'):
						temp[i] = 13;
						break;
					case ('e'):
						temp[i] = 14;
						break;
					case ('f'):
						temp[i] = 15;
						break;
				}
				address+=temp[i]*pow(16,7-i);
			}
		//for part A
			int offset_bits = log(block_size) / log(2);
			int index_bits = log(r1) / log(2);
			int tag_bits = 32 - offset_bits - index_bits;
			long long int tb = address >> (32 - tag_bits);
			long long int temporary = tb << (32 - tag_bits);
			long long int temp2 = address - temporary;
			long long int index = temp2 >> offset_bits;
			if(v1[index]==0)
			{
				m1++;
				v1[index] = 1;
				t1[index] = tb;
			}
			else
			{
				if(t1[index] == tb)
				{
					h1++;
				}
				else
				{
					m1++;
					t1[index] = tb;
				}

			}
		}
	}
	fclose(fp);
	cout << "hit rate = " << h1/(h1+m1) << " miss rate = "<< m1/(h1+m1)<< endl;
}
int main()
{
	cout << "File gcc.trace" << endl;
	hit_miss_rates(64, 4, 10, "gcc.trace");
	hit_miss_rates(512, 4, 10, "gcc.trace");
	hit_miss_rates(64, 1, 10, "gcc.trace");
	hit_miss_rates(64, 8, 10, "gcc.trace");
	hit_miss_rates(64, 16, 10, "gcc.trace");
	hit_miss_rates(64, 32, 10, "gcc.trace");
	cout << "File gzip.trace" << endl;
	hit_miss_rates(64, 4, 11, "gzip.trace");
	hit_miss_rates(512, 4, 11, "gzip.trace");
	hit_miss_rates(64, 1, 11, "gzip.trace");
	hit_miss_rates(64, 8, 11, "gzip.trace");
	hit_miss_rates(64, 16, 11, "gzip.trace");
	hit_miss_rates(64, 32, 11, "gzip.trace");
	cout << "File mcf.trace" << endl;
	hit_miss_rates(64, 4, 10, "mcf.trace");
	hit_miss_rates(512, 4, 10, "mcf.trace");
	hit_miss_rates(64, 1, 10, "mcf.trace");
	hit_miss_rates(64, 8, 10, "mcf.trace");
	hit_miss_rates(64, 16, 10, "mcf.trace");
	hit_miss_rates(64, 32, 10, "mcf.trace");
	cout << "swim.trace" << endl;
	hit_miss_rates(64, 4, 11, "swim.trace");
	hit_miss_rates(512, 4, 11, "swim.trace");
	hit_miss_rates(64, 1, 11, "swim.trace");
	hit_miss_rates(64, 8, 11, "swim.trace");
	hit_miss_rates(64, 16, 11, "swim.trace");
	hit_miss_rates(64, 32, 11, "swim.trace");
	cout << "twolf.trace" << endl;
	hit_miss_rates(64, 4, 12, "twolf.trace");
	hit_miss_rates(512, 4, 12, "twolf.trace");
	hit_miss_rates(64, 1, 12, "twolf.trace");
	hit_miss_rates(64, 8, 12, "twolf.trace");
	hit_miss_rates(64, 16, 12, "twolf.trace");
	hit_miss_rates(64, 32, 12, "twolf.trace");
	return 0;
}  