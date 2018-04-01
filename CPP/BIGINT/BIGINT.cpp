#include<iostream>
#include<vector>

using namespace std;

class BigInt {

	public:
		vector <char> data;
		vector <char> result;
		int size;

    BigInt(){

    	data.push_back('0');
    	//data[0] = '0';

    }

	BigInt(long long int input)
	{
		size = 0;
		//cout << "long long"<<endl;
		int carry,rem,n = input;
		while(n){
			data.push_back(n%10 + '0');
			n = n/10;
			size ++;
		}
		//data.push_back(input%10 + '0');		

	}	

	BigInt(string num)
	{
		size = 0;
		//cout << "Strung"<<endl;
		int len = num.size();
		for(int i=len-1;i>=0;i--){
			size++;
			data.push_back(num[i]);
		}

	}
	void printvalue(){
		int len = data.size();
		if(len == 0) cout << " " << 0 << " " ;
		//cout<<len<<endl;
		for(int i=len-1; i>=0; i--){
			//cout << "hi";
			cout<<" "<< data[i]<<" ";
		}
		cout<<endl;
	}

	void addition(BigInt & obj1 , BigInt & obj2);

	void addition(BigInt & obj);
};

void BigInt:: addition(BigInt & obj){

	//addition(this,obj);

	int l,i,j,sum=0,carry=0;
	l = obj.size;
	i=0;
	while(l > 0){
		sum = (obj.data[i] - '0') + (data[i] - '0') + carry;
		carry =  sum/10;
		sum = sum %10;
		data.push_back(sum + '0');
		l--;
		i++;
	}

	if (carry){
		data.push_back(carry + '0');
	}

}

void BigInt::addition(BigInt & obj1 , BigInt & obj2){
		//cout <<obj1.data[1]<<endl;
		int l1 = obj1.size, l2= obj2.size;
		int sum,carry,i,j,k;
		i = 0;
		carry =0;
		while(l1>0 && l2 >0 ){
			sum = (obj1.data[i] - '0' )  + (obj2.data[i] - '0') + carry;
			carry = sum /10;
			sum = sum%10;
			//cout<< "Debug: "<< sum  << " " << carry <<  obj1.data[i] << " " << obj2.data[i] << " " <<endl  ;

			data.push_back(sum + '0');
			//cout << "PushBack" << endl ;
			l1--;
			l2--;
			i++;
		}

		while( l1 > 0 ){
            sum = (obj1.data[i++] - '0') + carry;
            carry = sum /10;
            sum = sum %10;
            data.push_back(sum + '0');
            l1--;
		}
		while( l2 > 0 ){
            sum = (obj2.data[i++] - '0') + carry;
            carry = sum /10;
            sum = sum %10;
            data.push_back(sum + '0');
            l2--;
		}
		
		if(carry){
			data.push_back(carry + '0');
			//cout << "PB" << endl;;
		}

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
	int4.printvalue();
	return 0;
}
