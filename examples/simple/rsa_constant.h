#include<stdio.h> 
#include<stdlib.h> 
#include<math.h>  
#include<string.h>
#include <stdint.h>
#define maxi 1001

long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i; 
char msg[100];
int prime(long int); 
void ce(); 
long int cd(long int); 
void encrypt(); 
void decrypt();


uint64_t bitMux(uint64_t c, uint64_t a, uint64_t b) {
return b ^ (c & (a ^ b));
}
uint64_t isLessThan (int64_t a, int64_t b) {
uint64_t c = a - b;
return bitMux(a^b, a, c) >> 63;
}
uint64_t isGreaterThan (int64_t a, int64_t b) {
return isLessThan (b, a);
}
uint64_t isLessThanOrEqual (int64_t a, int64_t b) {
return !( isGreaterThan (a, b));
}
uint64_t isGreaterThanOrEqual (int64_t a, int64_t b) {
return !( isLessThan (a, b));
}



void rsa_constant() { 
	//Ignore these inputs lines in order to check constant time implementations


	p = 127; 
	q = 199;
	flag=prime(p);
 

 
	printf("\nENTER MESSAGE\n"); 
	fflush(stdin); 
	scanf("%s",msg);

    int i = 0;
    while (msg[i]){
        m[i]=msg[i];
        i++;
    }	
 
	n=p*q; 
	t=(p-1)*(q-1); 
	ce(); 
	printf("\nPOSSIBLE VALUES OF e AND d ARE\n");

	for (i=0;isLessThan(i, j-1);i++) 
	printf("\n%ld\t%ld",e[i],d[i]); 

	encrypt(); 
	decrypt(); 
 
}
 
int prime(long int pr) { 
	int i; 
	j=sqrt(pr); 
	int k = 1;
	for (i=2;isLessThanOrEqual(i, j);i++) { 
		if(pr%i==0){ 
			k = k&0;
		}else{
			k = k;
		}
	} 
	return k; 
}
 
void ce() {
 
	int k; 
	k=0;
 
	for (i=2;isLessThan(i, t);i++) {
		if(t%i==0) 
		    continue;
		flag=prime(i);
 
		if(flag==1&&i!=p&&i!=q) { 
			e[k]=i; 
			flag=cd(e[k]); 
 
			if(flag>0) { 
				d[k]=flag; 
				k++; 
			} 
			if(k==99) 
			        break; 
		}
 
	}
 
}
 
long int cd(long int x) { 
	long int k=1; 
	while(1) { 
		k=k+t; 
		if(k%x==0) 
		    return(k/x); 
	} 
}


void encrypt() { 
	long int pt,ct,key=e[0],k,len; 
	i=0; 
	len=strlen(msg);
 
	while(i!=len) { 
		pt=m[i]; 
		pt=pt-96; 
		k=1;
 
		for (j=0;isLessThan(j, key);j++) { 
			k=k*pt; 
			k=k%n; 
		} 

		temp[i]=k; 
		ct=k+96; 
		en[i]=ct; 
		i++; 
	}
 
	en[i]=-1;
  
	printf("\nTHE ENCRYPTED MESSAGE IS\n"); 
	for (i=0;en[i]!=-1;i++) 
	printf("%c",en[i]);
 
}
 
void decrypt() {
	long int pt,ct,key=d[0],k;
	i=0;

	while(en[i]!=-1) { 
		ct=temp[i]; 
		k=1; 
		for (j=0;j<key;j++) { 
			k=k*ct; 
			k=k%n; 
		} 
		pt=k+96; 
		m[i]=pt; 
		i++; 
	} 
	m[i]=-1; 
	printf("\nTHE DECRYPTED MESSAGE IS\n"); 
	for (i=0;m[i]!=-1;i++) 
	printf("%c",m[i]);
 
}
 