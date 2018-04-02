#include<iostream>
#include<vector>

using namespace std;

class BigInt {

	public:
		vector <char> data;
		//vector <char> result;
		
    BigInt(){
    	data.push_back('0');
    }

	BigInt(long long int input)
	{
		int carry,rem,n = input;
		while(n){
			data.push_back(n%10 + '0');
			n = n/10;
		}
	}	

   void operator=(long long v) {
        data.clear();
        for (; v > 0; v = v / 10)
            data.push_back(v % 10 + '0');
	}

	BigInt(string num)
	{
		int len = num.size();
		for(int i=len-1;i>=0;i--){
			data.push_back(num[i]);
		}

	}
	void printvalue(){
		int len = data.size();
		if(len == 0) cout << " " << 0 << " " ;
		for(int i=len-1; i>=0; i--){
			cout<<" "<< data[i]<<" ";
		}
		cout<<endl;
	}

	void addition(BigInt & obj1 , BigInt & obj2);

	void addition(BigInt & obj);

	void multiplication(BigInt & obj1 , BigInt & obj2);

	void multiplication(BigInt & obj);

};

void BigInt:: addition(BigInt & obj){         
         std::vector<char> data2;
		int l1 = obj.data.size(), l2= data.size();
		int sum,carry,i,j,k;
		i = 0;
		carry =0;
		while(l1>0 && l2 >0 ){
			sum = (obj.data[i] - '0' )  + (data[i] - '0') + carry;
			carry = sum /10;
			sum = sum%10;
			data2.push_back(sum + '0');
			l1--;
			l2--;
			i++;
		}

		while( l1 > 0 ){
            sum = (obj.data[i++] - '0') + carry;
            carry = sum /10;
            sum = sum %10;
            data2.push_back(sum + '0');
            l1--;
		}
		while( l2 > 0 ){
            sum = (data[i++] - '0') + carry;
            carry = sum /10;
            sum = sum %10;
            data2.push_back(sum + '0');
            l2--;
		}
		
		if(carry){
			data2.push_back(carry + '0');
		}

		std::vector<char> temp=data;
		data=data2;
		temp.clear();	
}

void BigInt:: multiplication(BigInt & obj){         
         std::vector<char> data2;
		int l1 = obj.data.size(), l2= data.size();
		int sum,carry,i,j,k;

		if(l1 == 0 || l2 == 0){
			std::vector<char> temp=obj.data;
			data=obj.data;
			temp.clear();
			return;		
		}

		int in1 = 0,in2 = 0;

		for( i = l2-1; i>= 0; i--){
			
			int carry = 0;
			int x = data[i] - '0';
			in2 = 0;
			
			for(j=l1-1; j>=0; j--){
				int y = obj.data[j] - '0';

				int sum = x*y + data2[in1+ in2]+ carry;

				carry = sum /10;

				data2[in1 + in2] = sum %10;

				in2 ++;

			}

			if(carry){
				data2[in1 + in2] = carry;
			}

			in1 ++;

		}

		std::vector<char> temp=data;
		data=data2;
		temp.clear();	
}


void BigInt::addition(BigInt & obj1 , BigInt & obj2){
		this->addition(obj1);
		this->addition(obj2);
}

void BigInt::multiplication(BigInt & obj1 , BigInt & obj2){
		this->multiplication(obj1);
		this->multiplication(obj2);
}


int main()
{
	BigInt int1= BigInt(1002);
	BigInt int2= BigInt("198");
	BigInt int3;
	BigInt int4;

	int1.printvalue();
	int2.printvalue();
	int3.printvalue();
	int3.addition(int1, int2);
	int3.printvalue();

	int4.printvalue();
	int4.addition(int1);
	int4.addition(int2);

	int2 = 100;
	BigInt int5;
	int5.addition(int2, int3);

	int5.printvalue();

	BigInt int6 = BigInt(50);
	int3 = 2;
	int6.multiplication(int3);
	int6.printvalue();

	return 0;
}
