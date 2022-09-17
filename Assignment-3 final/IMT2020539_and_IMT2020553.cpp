#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;
//function for calulating hit and miss rates
//size -> size of cache 
//block_size -> size of block
//n -> no of characters in filename + 1 , used for calulating the size of array for filename
//filename -> name of the trace file
void hit_miss_rates(int size, int block_size, int n, string filename)
{
	//hit and miss store the no of hits and miss
	double hit = 0, miss = 0;
	//calculating no of lines of a cache
	int lines = size * 1024 / block_size; 
	//array for cache
	long long int cache[lines];
	//array for tag 
	long long int tag[lines];
	//array for valid
	int8_t valid[lines];
	int i;
	for(i = 0; i < lines;i++)
	{
		valid[i] = 0;
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
			//reading 8 digits after x basically after 0x ,
			//the 8 digits are basically the 32 bit addres
			fread(&add, 8, 1, fp);
			for(i = 0;i < 8;i++)
			{
				//but as the hexadecimal address has been readed in the form of char ,
				//converting that char address into decimal value of corresponding address
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
				//address stores the decimal value of the hexadecimal address being read from the trace file
				address+=temp[i]*pow(16,7-i);
			}
			//calculating no of offset bits
			int offset_bits = log(block_size) / log(2);
			//calculating no of index bits
			int index_bits = log(lines) / log(2);
			//calculating no of tag bits
			int tag_bits = 32 - offset_bits - index_bits;
			//calculating exact value of tag
			long long int tb = address >> (32 - tag_bits);
			long long int temporary = tb << (32 - tag_bits);
			long long int temp2 = address - temporary;
			//calculating exact value of index
			long long int index = temp2 >> offset_bits;
			//now checking for hit and miss
			if(valid[index]==0)
			{
				miss++;
				valid[index] = 1;
				tag[index] = tb;
			}
			else
			{
				if(tag[index] == tb)
				{
					hit++;
				}
				else
				{
					miss++;
					tag[index] = tb;
				}

			}
		}
	}
	fclose(fp);
	//printing hit rate and miss rate
	cout << "hit rate = " << hit/(hit+miss) << " miss rate = "<< miss/(hit+miss)<< endl<< endl;
}
int main()
{
	cout << "Part A cache of size 64kB block size 4 bytes" << endl<< endl<<endl;

	cout << "File gcc.trace" << endl ;
	hit_miss_rates(64, 4, 10, "gcc.trace");
	cout << "File gzip.trace" << endl;
	hit_miss_rates(64, 4, 11, "gzip.trace");
	cout << "File mcf.trace" << endl;
	hit_miss_rates(64, 4, 10, "mcf.trace");
	cout << "File swim.trace" << endl;
	hit_miss_rates(64, 4, 11, "swim.trace");
	cout << "File twolf.trace" << endl;
	hit_miss_rates(64, 4, 12, "twolf.trace");

	cout << endl << "Part B cache of size 512kB block size 4 bytes" << endl<< endl<<endl;

	cout << "File gcc.trace" << endl ;	
	hit_miss_rates(512, 4, 10, "gcc.trace");
	cout << "File gzip.trace" << endl;
	hit_miss_rates(512, 4, 11, "gzip.trace");
	cout << "File mcf.trace" << endl;
	hit_miss_rates(512, 4, 10, "mcf.trace");
	cout << "File swim.trace" << endl;
	hit_miss_rates(512, 4, 11, "swim.trace");
	cout << "File twolf.trace" << endl;
	hit_miss_rates(512, 4, 12, "twolf.trace");


	cout <<endl <<  "Part C cache of size 64kB block size 1 bytes" << endl<< endl<<endl;

	cout << "File gcc.trace" << endl ;
	hit_miss_rates(64, 1, 10, "gcc.trace");
	cout << "File gzip.trace" << endl;
	hit_miss_rates(64, 1, 11, "gzip.trace");
	cout << "File mcf.trace" << endl;
	hit_miss_rates(64, 1, 10, "mcf.trace");
	cout << "File swim.trace" << endl;
	hit_miss_rates(64, 1, 11, "swim.trace");
	cout << "File twolf.trace" << endl;
	hit_miss_rates(64, 1, 12, "twolf.trace");

	cout << endl << "Part C cache of size 64kB block size 4 bytes" << endl<< endl<<endl;

	cout << "File gcc.trace" << endl ;
	hit_miss_rates(64, 4, 10, "gcc.trace");
	cout << "File gzip.trace" << endl;
	hit_miss_rates(64, 4, 11, "gzip.trace");
	cout << "File mcf.trace" << endl;
	hit_miss_rates(64, 4, 10, "mcf.trace");
	cout << "File swim.trace" << endl;
	hit_miss_rates(64, 4, 11, "swim.trace");
	cout << "File twolf.trace" << endl;
	hit_miss_rates(64, 4, 12, "twolf.trace");


	cout << endl << "Part C cache of size 64kB block size 8 bytes" << endl<< endl<<endl;

	cout << "File gcc.trace" << endl ;
	hit_miss_rates(64, 8, 10, "gcc.trace");
	cout << "File gzip.trace" << endl;
	hit_miss_rates(64, 8, 11, "gzip.trace");
	cout << "File mcf.trace" << endl;
	hit_miss_rates(64, 8, 10, "mcf.trace");
	cout << "File swim.trace" << endl;
	hit_miss_rates(64, 8, 11, "swim.trace");
	cout << "File twolf.trace" << endl;
	hit_miss_rates(64, 8, 12, "twolf.trace");


	cout << endl << "Part C cache of size 64kB block size 16 bytes" << endl<< endl<<endl;

	cout << "File gcc.trace" << endl ;
	hit_miss_rates(64, 16, 10, "gcc.trace");
	cout << "File gzip.trace" << endl;
	hit_miss_rates(64, 16, 11, "gzip.trace");
	cout << "File mcf.trace" << endl;
	hit_miss_rates(64, 16, 10, "mcf.trace");
	cout << "File swim.trace" << endl;
	hit_miss_rates(64, 16, 11, "swim.trace");
	cout << "File twolf.trace" << endl;
	hit_miss_rates(64, 16, 12, "twolf.trace");


	cout << endl << "Part C cache of size 64kB block size 32 bytes" << endl<< endl<<endl;

	cout << "File gcc.trace" << endl ;
	hit_miss_rates(64, 32, 10, "gcc.trace");
	cout << "File gzip.trace" << endl;
	hit_miss_rates(64, 32, 11, "gzip.trace");
	cout << "File mcf.trace" << endl;
	hit_miss_rates(64, 32, 10, "mcf.trace");
	cout << "File swim.trace" << endl;
	hit_miss_rates(64, 32, 11, "swim.trace");
	cout << "File twolf.trace" << endl;
	hit_miss_rates(64, 32, 12, "twolf.trace");

	return 0;
}  