#include <iostream>
#include <stdlib.h>
#include <gmp.h>
void multmod(mpz_t result,mpz_t num,mpz_t num2,mpz_t mod);
void powermod(mpz_t result,mpz_t num,mpz_t exp,mpz_t mod);
bool test(mpz_t pubexp,mpz_t priexp, mpz_t mod);
 int main() {
	mpz_t testnumber;
	mpz_init_set_ui(testnumber,2);
	mpz_t testnumber2;
	mpz_init_set_ui(testnumber2,3);
	mpz_t mod;
	mpz_init_set_str(mod,"145906768007583323230186939349070635292401872375357164399581871019873438799005358938369571402670149802121818086292467422828157022922076746906543401224889672472407926969987100581290103199317858753663710862357656510507883714297115637342788911463535102712032765166518411726859837988672111837205085526346618740053",10);
	mpz_t pubexp;
	mpz_init_set_str(pubexp,"65537",10);
	mpz_t priexp;
	mpz_init_set_str(priexp,"-1",10);
	mpz_t rsanum;
	mpz_init(rsanum);
	powermod(rsanum,testnumber,pubexp,mod);
	mpz_t temp;
	mpz_t temp1;
	mpz_init_set(temp,rsanum);
	mpz_init_set_ui(temp1,1);
	mpz_t result;
	mpz_init(result);
	bool done = false;
	
	while(!done) {
		multmod(temp,temp,rsanum,mod);
		mpz_add_ui(temp1,temp1,1);
		std::cout<<mpz_get_si(temp1)<<":"<<mpz_get_si(temp)<<"    "<<mpz_get_si(testnumber)<<std::endl;
		if(mpz_cmp(temp,testnumber)==0) {
			std::cout<<mpz_get_si(temp1)<<":"<<mpz_get_si(temp)<<"    "<<mpz_get_si(testnumber)<<std::endl;
			powermod(result,rsanum,temp1,mod);			
			if(mpz_cmp(result,testnumber)==0){
				std::cout<<mpz_get_si(temp1)<<":"<<mpz_get_si(temp)<<"    "<<mpz_get_si(testnumber)<<std::endl;
				if(test(pubexp,temp1,mod)){
					std::cout<<mpz_get_si(temp1)<<":"<<mpz_get_si(temp)<<"    "<<mpz_get_si(testnumber)<<std::endl;
					mpz_set(priexp,temp1);
					done=true;
				}	
			}
			
		}
		//std::cout<<temp1<<":"<<temp<<std::endl;

	}
	std::cout<<"The d of ("<<mod<<","<<pubexp<<") is "<<priexp<<std::endl;
	return 0;
}
void multmod(mpz_t result,mpz_t num,mpz_t num2,mpz_t mod){
	
	mpz_mul(result,num,num2);
	mpz_mod(result,result,mod);
	

}
void powermod(mpz_t result,mpz_t num,mpz_t exp,mpz_t mod){
	mpz_powm(result,num,exp,mod);
	

}
bool test(mpz_t pubexp,mpz_t priexp, mpz_t mod){
	mpz_t num;
	mpz_init_set_ui(num,2);
	mpz_t orgnum;
	mpz_init_set_si(orgnum,-1);
	mpz_t rsanum;
	mpz_init_set_si(rsanum,-1);
	mpz_t i;
	mpz_init_set_ui(i,0);
	mpz_t newmod;
	mpz_init(newmod);
	mpz_sub_ui(newmod,mod,2);
	mpz_t result;
	mpz_init(result);
	
	for(;mpz_cmp(i,newmod)<0;mpz_add_ui(i,i,1)){
		mpz_set(orgnum,num);
		powermod(rsanum,orgnum,pubexp,mod);
		//std::cout<<num<<std::endl;
		powermod(result,rsanum,priexp,mod);
		if(mpz_cmp(result,orgnum)!=0){
			mpz_clear(num);
			mpz_clear(orgnum);
			mpz_clear(i);
			mpz_clear(rsanum);
			mpz_clear(newmod);
			mpz_clear(result);
			return false;
		}
		
		mpz_add_ui(num,num,1);

	}
	mpz_clear(num);
	mpz_clear(orgnum);
	mpz_clear(i);
	mpz_clear(rsanum);
	mpz_clear(newmod);
	mpz_clear(result);
	return true;


}
