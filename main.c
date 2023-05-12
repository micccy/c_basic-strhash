#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

const char conv[]="???1GJ2HX3IY4L?5M?6N?7O?8P?9Q?AR0BS?CKTDUWEV?FZ?";		//Conversion table

int isval(char c){
	if(c=='\0' || c=='\n') return 0;										//End of string (stop)
	else if(c>'\0' && c<' ') return 1;										//Control character (ignore)
	else if((c>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z')) return 2;	//Alphanumeric character (process as usual)
	else return 3;															//Other character (xor nibbles. if consecutive add together before)
}

int main(int argc,char *argv[]){
	int len,last;
	char *cur,sum,wlst,c;
	uint8_t *pool;
	uint64_t xorcomb;
	if (argc==2){															//If a string is provided
		len=0;																//Initialize
		last=4;
		cur=argv[1];
		while(isval(*cur)){													//Find out max size of result
			if(isval(*cur)==2||(isval(*cur)==3&&last!=isval(*cur))) len++;
			last=isval(*cur);
			cur++;
		};
		if((pool=malloc(((len/16)+((len%16)?1:0))*8))){						//Allocate mem for enough 64bit ints
			len=0;
			cur=argv[1];
			sum=0;
			wlst=0x10;
			last=4;
			while(isval(*cur)){												//convert
				printf("\n %c = ",*cur);
				if(last==3 && last!=isval(*cur)){							//Add one character
					c=sum;
					c^=(c>>4);												//Xor nibbles together
					c&=0x0F;
					if(c!=wlst){
						//Add to string
						printf("%x,",c);
						if((len%2)==0) pool[len/2]=0;
						pool[len/2]|=((c&0x0F)<<((len%2)?4:0));
						len++;
						wlst=c;
					};
					sum=0;
				};
				if(isval(*cur)==2){
					c=*cur;
					if(c>='a') c&=0xDF;										//Force uppercase
					while(conv[(int)sum]!=c && conv[(int)sum]!='\0') sum++;	//Convert
					sum/=3;
					sum&=0x0F;
					if(sum!=wlst){
						//Add to string
						printf("%x",sum);
						if((len%2)==0) pool[len/2]=0;
						pool[len/2]|=((sum&0x0F)<<((len%2)?4:0));
						len++;
						wlst=sum;
					};
					sum=0;
				}else if(isval(*cur)==3) sum+=*cur;							//Add to sum
				last=isval(*cur);
				cur++;
			};
			printf("\nChars: %i", len);
			if(len%2) len+=1;
			len/=2;
			printf(" Size: %i\n", len);
			if(len%8){
				for(int i=0;i<(8-(i%8));i++) pool[len+i]=0;
			};
			xorcomb=0;
			for(int i=0;i<len;i++){
				if(i) printf(",");
				printf("%u",pool[i]);
				xorcomb^=pool[i];
			};
			printf("\t(xor:%u)\n",(uint8_t)xorcomb);
			xorcomb=0;
			if(len%2) len+=1;
			len/=2;
			for(int i=0;i<len;i++){
				if(i) printf(",");
				printf("%u",*((uint16_t*)pool+i));
				xorcomb^=*((uint16_t*)pool+i);
			};
			printf("\t(xor:%u)\n",(uint16_t)xorcomb);
			xorcomb=0;
			if(len%2) len+=1;
			len/=2;
			for(int i=0;i<len;i++){
				if(i) printf(",");
				printf("%u",*((uint32_t*)pool+i));
				xorcomb^=*((uint32_t*)pool+i);
			};
			printf("\t(xor:%u)\n",(uint32_t)xorcomb);
			xorcomb=0;
			if(len%2) len+=1;
			len/=2;
			for(int i=0;i<len;i++){
				if(i) printf(",");
				printf("%lu",*((uint64_t*)pool+i));
				xorcomb^=*((uint64_t*)pool+i);
			};
			printf("\t(xor:%lu)\n",(uint64_t)xorcomb);
			xorcomb=0;
			free(pool);														//Free mem
		}else printf("Memory not available!\n");
	}else{
		printf("\tUSAGE: TODO\n");
	};
	return 0;
}
