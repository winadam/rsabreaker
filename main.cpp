#include <iostream>
long int powermod(long int num,long int exp,long int mod);
long int multmod(long int num,long int num2,long int mod);
bool test(long int pubexp,long int priexp, long int mod);
 int main() {
	long int testnumber = 2;
	long int testnumber2 = 2;
	long int mod = 11929;
	long int pubexp = 2879;
	long int priexp = -1;
	long int rsanum = powermod(testnumber,pubexp,mod);
	long int temp = rsanum;
	long int temp1 = 1;
	bool done = false;
	
	while(!done) {
		temp = multmod(temp,rsanum,mod);
		temp1++;
		if(temp==testnumber) {
						
			if(powermod(rsanum,temp1,mod)==testnumber){
				//std::cout<<temp1<<std::endl;
				if(test(pubexp,temp1,mod)){
					priexp=temp1;
					done=true;
				}	
			}
			
		}
		//std::cout<<temp1<<":"<<temp<<std::endl;

	}
	std::cout<<"The d of ("<<mod<<","<<pubexp<<") is "<<priexp<<std::endl;
	return 0;
}
long int multmod(long int num,long int num2,long int mod){
	return (num*num2)%mod;


}
long int powermod(long int num,long int exp,long int mod){
	long int orgnum=num;
	for(long int i=0;i<exp-1;i++) {
		num*=orgnum;
		num%=mod;
		

	}
	return num;

}
bool test(long int pubexp,long int priexp, long int mod){
	long int num = 2;
	long int orgnum = -1;
	long int rsanum = -1;
	for(long int i=0;i<mod-2;i++){
		orgnum=num;
		rsanum = powermod(orgnum,pubexp,mod);
		//std::cout<<num<<std::endl;
		if(powermod(rsanum,priexp,mod)!=orgnum){

			return false;
		}
		num++;

	}
	return true;


}
