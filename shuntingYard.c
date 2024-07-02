#include<stdio.h>
#include<string.h>
#include<math.h> 

// +=-10001		-=-10002 	*=-10003 	/ = -10004 		^ = -10005 		sin = -10006 	cos =  -10007 	tan = -10008 	cot = -10009	( = -100020 	) = -10021
// arcsin = -100010 	arccos =  -100011 	arctan = -100012 	arccot = -100013  	log = -100014    ln = -100015
      
int getPrecedence(float i) { // islem önceligi
    if (i == -10001 || i == -10002)
        return 1;
    else if (i == -10003 || i == -10004)
        return 2;
    else if (i == -10005)
        return 3;
    else if (i == -10006 || i == -10007 || i == -10008 || i == -10009 || i == -100010 || i == -100011 || i == -100012 || i == -100013 || i == -100014  || i == -100015)
        return 4;
    else
        return -1;
}
  
float shuntingYard(char str[], float x) {
    int i,j,d=0,bases[5],base=0;
    float func[100];
    
    // string to float
    if(str[0] == '-'){
    	func[d++]=0;
	}
    for(i = 0; i < strlen(str); i++) {
        if (str[i] == 'x') {
            if(str[i-1] >= '0' && str[i-1]<='9'){
            	func[d++]=-10003;
            	func[d++]=x;
			}else{
				func[d++]=x;
			}
        }else if(str[i] == '+'){
        	func[d++]=-10001;
		}else if(str[i] == '-'){
        	func[d++]=-10002;
		}else if(str[i] == '*'){
        	func[d++]=-10003;
		}else if(str[i] == '/'){
        	func[d++]=-10004;
		}else if(str[i] == '^'){
        	func[d++]=-10005;
		}else if(str[i] == '('){
        	if(str[i-1] == ')'){
            	func[d++]=-10003;
            	func[d++]=-100020;
			}else{
				func[d++]=-100020;
			}
        	if(str[i+1] == '-'){
				func[d++]=0;
			}
		}else if(str[i] == ')'){
        	func[d++]=-100021;
		}else if(str[i] == 's' && str[i+1] == 'i' && str[i+2] == 'n'){
        	func[d++]=-10006;
        	i+=2;
		}else if(str[i] == 'c' && str[i+1] == 'o' && str[i+2] == 's'){
        	func[d++]=-10007;
        	i+=2;
		}else if(str[i] == 't' && str[i+1] == 'a' && str[i+2] == 'n'){
        	func[d++]=-10008;
        	i+=2;
		}else if(str[i] == 'c' && str[i+1] == 'o' && str[i+2] == 't'){
        	func[d++]=-10009;
        	i+=2;
		}else if(str[i] == 'a' && str[i+1] == 'r' && str[i+2] == 'c' && str[i+3] == 's' && str[i+4] == 'i' && str[i+5] == 'n'){
		    func[d++]=-100010;
		    i+=5;
		}else if(str[i] == 'a' && str[i+1] == 'r' && str[i+2] == 'c' && str[i+3] == 'c' && str[i+4] == 'o' && str[i+5] == 's'){
		    func[d++]=-100011;
		    i+=5;
		}else if(str[i] == 'a' && str[i+1] == 'r' && str[i+2] == 'c' && str[i+3] == 't' && str[i+4] == 'a' && str[i+5] == 'n'){
		    func[d++]=-100012;
		    i+=5;
		}else if(str[i] == 'a' && str[i+1] == 'r' && str[i+2] == 'c' && str[i+3] == 'c' && str[i+4] == 'o' && str[i+5] == 't'){
		    func[d++]=-100013;
		    i+=5;
		}else if(str[i] == 'l' && str[i+1] == 'o' && str[i+2] == 'g' && str[i+3] == '_' && str[i+4] >= '0' && str[i+4]<='9' && str[i+5] >= '0' && str[i+5]<='9'){
		    func[d++]=-100014;
		    bases[base]=(str[i+4]-'0')*10+(str[i+5]-'0');
		    base++;
		    i+=5;
		}else if(str[i] == 'l' && str[i+1] == 'o' && str[i+2] == 'g' && str[i+3] == '_' && str[i+4] >= '0' && str[i+4]<='9'){
		    func[d++]=-100014;
		    bases[base]=str[i+4]-'0';
		    base++;
		    i+=4;
		}else if(str[i] == 'l' && str[i+1] == 'o' && str[i+2] == 'g' && str[i+3] == '_' && str[i+4] == 'x'){
		    func[d++]=-100014;
		    bases[base]=x;
		    base++;
		    i+=4;
		}else if(str[i] == 'l' && str[i+1] == 'n'){
		    func[d++]=-100015;
		    i+=1;
		}else if (str[i] == 'e') {
            if(str[i-1] >= '0' && str[i-1]<='9'){
            	func[d++]=-10003;
            	func[d++]=exp(1);
			}else{
				func[d++]=exp(1);
			}
        }else if (str[i] == '.' && str[i+1] >= '0' && str[i+1] <= '9') {
		    float decimalPart = 0;
		    float placeValue = 0.1;
		    int k = 1;
		    while (str[i+k] >= '0' && str[i+k] <= '9' && i+k < strlen(str)) {
		        decimalPart += (str[i+k] - '0') * placeValue;
		        placeValue /= 10;
		        k++;
		    }
		    func[d-1] += decimalPart;
		    i += (k - 1);
		}else if(str[i] >= '0' && str[i]<='9' && str[i+1] >= '0' && str[i+1]<='9' && str[i+2] >= '0' && str[i+2]<='9' && str[i+3] >= '0' && str[i+3]<='9' && str[i+4] >= '0' && str[i+4]<='9' && str[i+5] >= '0' && str[i+5]<='9'){
			func[d++]=(str[i]-'0')*100000+(str[i+1]-'0')*10000+(str[i+2]-'0')*1000+(str[i+3]-'0')*100+(str[i+4]-'0')*10+(str[i+5]-'0');
			i+=5;
		}else if(str[i] >= '0' && str[i]<='9' && str[i+1] >= '0' && str[i+1]<='9' && str[i+2] >= '0' && str[i+2]<='9' && str[i+3] >= '0' && str[i+3]<='9' && str[i+4] >= '0' && str[i+4]<='9'){
			func[d++]=(str[i]-'0')*10000+(str[i+1]-'0')*1000+(str[i+2]-'0')*100+(str[i+3]-'0')*10+(str[i+4]-'0');
			i+=4;
		}else if(str[i] >= '0' && str[i]<='9' && str[i+1] >= '0' && str[i+1]<='9' && str[i+2] >= '0' && str[i+2]<='9' && str[i+3] >= '0' && str[i+3]<='9'){
			func[d++]=(str[i]-'0')*1000+(str[i+1]-'0')*100+(str[i+2]-'0')*10+(str[i+3]-'0');
			i+=3;
		}else if(str[i] >= '0' && str[i]<='9' && str[i+1] >= '0' && str[i+1]<='9' && str[i+2] >= '0' && str[i+2]<='9'){
			func[d++]=(str[i]-'0')*100+(str[i+1]-'0')*10+(str[i+2]-'0');
			i+=2;
		}else if(str[i] >= '0' && str[i]<='9' && str[i+1] >= '0' && str[i+1]<='9'){
			func[d++]=(str[i]-'0')*10+(str[i+1]-'0');
			i+=1;
		}else if(str[i] >= '0' && str[i]<='9'){
			func[d++]=str[i]-'0';
		}
    }
    	
    // Shunting Yard Algoritm
	
    int a=0,b=0;
    float output[d+1], operators[d+1],c; 
    for(i=0; i<d; i++) {
        c = func[i];
        if(c >= -10000) {
            output[a++] = c;
        } else if (c == -100020) {
            operators[b++] = c;
        } else if (c == -100021) {
            while (b != 0 && operators[b-1] != -100020) {
                output[a++] = operators[--b];
            }
            if (b == 0) {
                return -11111;
            }
            b--;
        } else {
            while (b != 0 && getPrecedence(c) <= getPrecedence(operators[b-1])) {
                output[a++] = operators[--b];
            }
            operators[b++] = c;
        }
    }
    while (b != 0) {
        if (operators[b-1] == -100020) {
            return -11111;
        }
        output[a++] = operators[--b];
    }
    int size=a;a=0;b=-1;int z=0;
    for(i=0; i<size; i++) {
        if(output[i]>=-10000){
        	operators[++b]=output[i];
		}else if(output[i]==-10001){
			operators[b-1]=operators[b-1]+operators[b];
			b--;
		}else if(output[i]==-10002){
			operators[b-1]=operators[b-1]-operators[b];
			b--;
		}else if(output[i]==-10003){
			operators[b-1]=operators[b-1]*operators[b];
			b--;
		}else if(output[i]==-10004){
			operators[b-1]=operators[b-1]/operators[b];
			b--;
		}else if(output[i]==-10005){
			operators[b-1]=pow(operators[b-1], operators[b]);
			b--;
		}else if(output[i]==-10006){
			double radians = operators[b] * M_PI / 180;
			operators[b]= sin(radians);
		}else if(output[i]==-10007){
			double radians = operators[b] * M_PI / 180;
			operators[b]= cos(radians);
		}else if(output[i]==-10008){
			double radians = operators[b] * M_PI / 180;
			operators[b]= tan(radians);
		}else if(output[i]==-10009){
			double radians = operators[b] * M_PI / 180;
			operators[b]= 1/tan(radians);
		}else if(output[i]==-100010){
		    float result = asin(operators[b]) * 180 / M_PI;
		    operators[b] = result;
		}else if(output[i]==-100011){
		    float result = acos(operators[b]) * 180 / M_PI;
		    operators[b] = result;
		}else if(output[i]==-100012){
		    float result = atan(operators[b]) * 180 / M_PI; 
		    operators[b] = result;
		}else if(output[i]==-100013){
		    float result = atan(1 / operators[b]) * 180 / M_PI;
		    operators[b] = result;
		}else if(output[i]==-100014){
			operators[b] = log(operators[b]) / log(bases[z++]);
		}else if(output[i]==-100015){
			operators[b] = log(operators[b]);  // math'ta log direkt e tabanýna eþitmiþ. 
		}

    }
    for(i=0; i<b+1; i++) {
        printf("\n%f\n",operators[i]);
    }
    if(b==0){
    	return operators[b];
	}else{
		return -11111;
	}	
}


int main() {
    char str[100];
	float x,result;

    printf("Bir string ifade girin: ");
    scanf("%s", str);

    printf("Kullanicidan alinacak sayi: ");
    scanf("%f", &x);
	
	result = shuntingYard(str, x);
	if (result == -11111) {
        printf("\nHata: Bu ifade geçersiz\n");
    } else {
        printf("\nSonuc: %f",result);
	}
    
    return 0;
}

