#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// MUHAMMET KURSAT ACIKGOZ
// 150116020

/*
* This code reads file which name is taken from user
* takes input to form options are little and big
* lastly takes size of output from user 1 2 3 or 4
* converts signed int and unsigned int to binary with 16 bit constontly
* output.txt will be created and printing will be there 
*/

int string_length(char s[]);
int binary2decimal(char n[]);
void binaryToHexaBigEndian(char *n);
void binaryToHexaLittleEndian(char *n);
char printHexDigit(int d);
void floatToIEEE(float num, int byte, int type);
char* intToBinary(int data, int bit);
char *mantissaToBinary (float fvalue);
void combine(char sign,char *exponentPart,char *numbin,int bit, int type);
char* roundMantissa(char *temp, int bit);


FILE* file_ptr =NULL; // file object created for output.txt

int main() {

    char c[20];
    FILE *fptr; // file object created
    char *s=malloc(256);
    printf("input file name: ");
    scanf("%255s", s);
	
    char orderingType[7];
    printf("byte ordering type(print \"Little\" or \"Big\"): ");
    scanf("%7s", orderingType);

    int type = 1; //This means Big endian
    if(strcmp(orderingType, "Little")==0){
        type = 0; //This Means Little Endian
    }

    int byte; // size of byte for float inputs
    printf("floating point size: ");
    scanf("%d", &byte);

    if ((fptr = fopen(s, "r")) == NULL) {
        printf("Error! opening file");
        // Program exits if file pointer returns NULL.
        return 1;
    }

    free(s);

    char* bin;
	file_ptr = fopen("output.txt", "w"); // output.txt created to write in
	
    while(fscanf(fptr, "%s", c) != EOF){
        int i;
        int test = 0; // 0 = signed int // 1 is float // 2 is unsigned

        for(i = 0; c[i] != '\000'; i++){
            if(c[i] == '.'){
                //this mean it is float and test will be 1
                test = 1;
                break;
            }else if(c[i] == 'u'){
                //this mean it is an unsigned int value test's value will be 2
                test = 2;
            }
        }//if code continues without break conditions this mean value is signed int
	
		
		
		// this guide num as float int or unsigned int
        switch(test){
            case 0: // signed int
                sscanf(c, "%d", &i); // read string as int
                bin = intToBinary(i,16); // int converted to binary in 16 bits
                if(type == 1 || byte == 1){ // type 1 means big Endian and
											// for 1 byte big and little endian outputs will be same 
                    binaryToHexaBigEndian(bin); // called binaryToHexaBigEndian method to print in hexa form
                }else{ // for Little Endian type binaryToHexaLittleEndian function called 
                    binaryToHexaLittleEndian(bin);
                }

                break;
            case 1: // float
                fprintf(file_ptr, "");
                float num;
                num = atof(c); // converted to float from string

                floatToIEEE(num,byte,type); // floatToIEEE is called with needed args

                break;
            case 2: // unsigned
                sscanf(c, "%d", &i);  // read string as int
                bin = intToBinary(abs(i),16); // int converted to binary in 16 bits

                if(type == 1 || byte == 1){ // type 1 means big Endian and
											// for 1 byte big and little endian outputs will be same
                    binaryToHexaBigEndian(bin);
                }else{ // for Little Endian type binaryToHexaLittleEndian function called 
                    binaryToHexaLittleEndian(bin);
                }
                break;
        }

        fprintf(file_ptr, "\n");
    }

    free(bin);

    return 0;
}


/*
*	This funtion converts string which is *n to binary
*	and print it to output.txt file
*/
void binaryToHexaBigEndian(char *n){
    int i,j,d,l;
    char temp[strlen(n)]; // temp char array created
    for(i=j=0;i<string_length(n)%4;++i,++j){ // n is coppied to temp to do not change something in
        temp[j]=n[i];
    }


    temp[j]='\0'; // last element must be null to understand end

    d=binary2decimal(temp); // int d is decimal value of binary

    char hexa[(int)(strlen(n)/4)]; // hexas size must be quarter size of binary size
    
    l=0;
    
    if(d!=0) hexa[l++]=printHexDigit(d); // if d is not equal to 0 hexa digit will be added to char array
    
    while(n[i]!='\0'){ // this loop will be iterate to end of char array
        for(j=0;j<4;++i,++j) // temp holds 4 char of string
            temp[j]=n[i];

        temp[j]='\0'; // last element must be null to understand end

        d=binary2decimal(temp); // int d is decimal value of binary
        hexa[l++]=printHexDigit(d); // hexa digit will be added to char array
    } 
    
    hexa[l] = '\0'; // last element must be null to understand end

    for(i = 0; i<strlen(hexa);){ // hexa value is printed
        fprintf(file_ptr, "%c%c ",hexa[i],hexa[i+1]);
        i=i+2;
    }

    fprintf(file_ptr, "\n"); // end of printing
}

/*
*	This function converts binary to hexa and then 
* 	convert it to Little Endian form. Lastly print it
* 	to output.txt
*/
void binaryToHexaLittleEndian(char *n){
    int i,j,d,l;
    char temp[strlen(n)]; // temp char array created
    for(i=j=0;i<string_length(n)%4;++i,++j){ // n is coppied to temp to do not change something in
        temp[j]=n[i];
    }


    temp[j]='\0'; // last element must be null to understand end

    d=binary2decimal(temp); // int d is decimal value of binary
 
    char hexa[(int)(strlen(n)/4)]; // hexas size must be quarter size of binary size
    
    l=0;
    
    if(d!=0) hexa[l++]=printHexDigit(d); // if d is not equal to 0 hexa digit will be added to char array
    
    while(n[i]!='\0'){ // this loop will be iterate to end of char array
        for(j=0;j<4;++i,++j) // temp holds 4 char of string
            temp[j]=n[i];

        temp[j]='\0'; // last element must be null to understand end

        d=binary2decimal(temp); // int d is decimal value of binary
        hexa[l++]=printHexDigit(d); // hexa digit will be added to char array
    }
    
    hexa[l] = '\0'; // last element must be null to understand end
    
    for(i = strlen(hexa)-1; i>=0;){ // hexa value is printed
        fprintf(file_ptr, "%c%c ",hexa[i-1],hexa[i]);
        i=i-2;
    }

    fprintf(file_ptr, "\n");
}

// this function converts from binary (sting) to decimal value
int binary2decimal(char n[]){
    int i,decimal,mul=0;

    for(decimal=0,i=string_length(n)-1;i>=0;--i,++mul)
        decimal+=(n[i]-48)*(1<<mul);

    return decimal;
}

// returns size of char array
int string_length(char s[]){
    int i=0;

    while(s[i]!='\0')
        i++;

    return i;
}

// returns value of int in hexa as char
char printHexDigit(int d){
    if(d<10) return d+'0';
    else if(d==10) return 'A';
    else if(d==11) return 'B';
    else if(d==12) return 'C';
    else if(d==13) return 'D';
    else if(d==14) return 'E';
    else if(d==15) return 'F';
}

/*
*	This function converts from float to IEEE form with num (float number) 
* 	arg byte (size) and type (big or Little)
*/
void floatToIEEE(float num, int byte, int type){
	// This if statemant decides to first digit of ieee 
	// as checking sign
    char sign = '0';
    if(num < 0) {
        sign = '1';
    }
	
	// Called inToBinary function for 16 bits. num will be returned as binary
    char *bin = intToBinary(abs((int)num),16);

	// to crop 0s beginning of the binary string found index of first 1
    int i;
    for(i=0;i<strlen(bin);i++){
        if(bin[i]=='1'){
            break;
        }
    }
	
	// bin is editted without beninning zeros
    char *subBin = malloc(strlen(bin)-i);
    memcpy( subBin, &bin[i+1], strlen(bin)-i );
    subBin[strlen(bin)-i+1] = '\0';
	
	// exp value founded
    int ex = strlen(bin)-i-1;

	// numbin is created to hold mantissa and binary of decimal part
    char *mantissaBin = mantissaToBinary((float)fabs(num));
    char *numBin = malloc(strlen(subBin) + strlen(mantissaBin) + 1);

	// this means decimal part is 0
    if(ex==-1){
        ex++;
        // ex part is calculated again to check mantissa 
        for(i=0;i<strlen(mantissaBin);i++){
            ex--;
            if(mantissaBin[i]=='1'){
                break;
            }
        }
		// numbin defined 
        memcpy( mantissaBin, &mantissaBin[abs(ex)-1], strlen(mantissaBin)-(abs(ex)-1) );
        mantissaBin[strlen(mantissaBin)-(abs(ex)-1)] = '\0';
        strcpy(numBin, mantissaBin);
        
    }else{
    	// numbin defined 
        strcpy(numBin, subBin);
        strcat(numBin, mantissaBin);
    }

    int bias;
	
	// size will be chaecking with if and if else conditions
	// bias and exponantial part will be calculated 
	// combine function called with sign exponent part size and type(little big)
    if(byte == 1){
        bias = pow(2,4-1)-1;
        ex +=  bias;
        char* exponentPart = intToBinary(ex,4);
        combine(sign,exponentPart,numBin,byte*8,type);

    }else if(byte == 2){
        bias = pow(2,6-1)-1;
        ex +=  bias;
        char* exponentPart = intToBinary(ex,6);
        combine(sign,exponentPart,numBin,byte*8,type);


    }else if(byte == 3){
        bias = pow(2,8-1)-1;
        ex +=  bias;
        char* exponentPart = intToBinary(ex,8);
        char *rounded = (char*)malloc(14);
        rounded = roundMantissa(numBin,13);
        combine(sign,exponentPart,rounded,byte*8,type);
        free(rounded);

    }else if(byte == 4){
        bias = pow(2,10-1)-1;
        ex +=  bias;
        char* exponentPart = intToBinary(ex,10);
        char *rounded = (char*)malloc(14);
        rounded = roundMantissa(numBin,13);
        combine(sign,exponentPart,rounded,byte*8,type);
        free(rounded);

    }else{
        exit(1);
    }




    free(mantissaBin);
    free(bin);
    free(numBin);


}

/*
* this function rounds num to needed bit size
*/
char* roundMantissa(char *temp, int bit){
    char *final = (char*)malloc(bit);

    if(temp[bit-1] == '0'){
        memcpy( final, &temp[0], bit );
        final[bit] = '\0';
    }else{
        memcpy( final, &temp[0], bit );
        final[bit] = '\0';
        final = intToBinary(binary2decimal(final) + 1, bit);
    }

    return final;
}

// combine all binary nums and binaryToHexaBigEndian or binaryToHexaLittleEndian
// function with type arg checking. 
void combine(char sign,char *exponentPart,char *numbin,int bit, int type){
    char *final = (char*)malloc(bit+1);
    final[0] = sign;
    final[1] = '\0';

    strcat(final,exponentPart);
    strcat(final,numbin);
    int i;
    for(i = 0; i<bit; i++){
        if(final[i] != '0' && final[i] != '1'){
            final[i] = '0';
        }
    }
    final[i] = '\0';

    if(final[bit-2]!='0'){
        final = intToBinary(binary2decimal(final)+1,bit);

    }

    if(type==1 || bit == 8){
        binaryToHexaBigEndian(final);
    }else{
        binaryToHexaLittleEndian(final);
    }

    final[bit-1] = '\0' ;
}

/*
* 	This function converts int data to string binary
*	with bit size 
*/
char* intToBinary(int data, int bit){
    const size_t BITS = bit;
    char *bin_str =(char*) malloc(BITS+1);
    unsigned int i;
    for(i=0; i<BITS; i++){
        unsigned int mask = 1u << (BITS - 1 - i);
        bin_str[i] = (data & mask) ? '1' : '0';
    }
    bin_str[BITS] = '\0';

    return bin_str;
}

/*
*	this function returns string (char ptr) 
*	fvalue is tho float part of num which is after point
*	it will be converted to binary form
*/
char *mantissaToBinary (float fvalue){
    int mantissaBit = 23;
    char *p = (char*)malloc(mantissaBit);

    float fv = fvalue > 1.0 ? fvalue - (int)fvalue : fvalue;
    if(fv == 0){
        p[0] ='0';
        p[1] = '\0';
        return p;
    }

    unsigned char it;

    for(it = 0;fv > 0 && it < mantissaBit + 1; it++ ){
        fv = fv * 2.0;
        if((int)fv == 0){
            p[it] = '0';
        }else{
            p[it] = '1';
        }
        p[it+1] = 0;

        fv = ((int)fv >= 1) ? fv - 1.0 : fv;
    }

    return p;
}



