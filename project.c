#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

// +=-10001		-=-10002 	*=-10003 	/ = -10004 		^ = -10005 		sin = -10006 	cos =  -10007 	tan = -10008 	cot = -10009	( = -100020 	) = -10021
// arcsin = -100010 	arccos =  -100011 	arctan = -100012 	arccot = -100013  	log = -100014    ln = -100015
      
int flag=0;

float maxF(float a,float b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}
      
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
  
float f(char str[], float x) {
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
    if(b==0){
    	return operators[b];
	}else{
		return -11111;
	}	
}

void bisection(){
    char str[100];
    float a, b, c, e;
	int ite=1,max;
    system("cls");
    printf("Bisection yontemiyle kokunun bulunmasini istediginiz fonksiyonu giriniz: ");
    scanf("%s", str);
    printf("Koku icerisine alan iki deger giriniz :");
    scanf("%f %f", &a, &b);
    printf("Epsilon degerini giriniz :");
    scanf("%f", &e);
    printf("Max iterasyon degerini giriniz :");
    scanf("%d", &max);
    c = (a + b) / 2;

    if (f(str, a) * f(str, b) < 0) {
        if (b > a) {
            float temp = a;
            a = b;
            b = temp;
        }
        printf("\n%d. iterasyon\n",ite);
        printf("ust = %f => f(ust) = %f\n", a, f(str, a));
        printf("orta = %f => f(orta) = %f\n", (a+b)/2, f(str, (a+b)/2));
        printf("alt = %f => f(alt) = %f\n", b, f(str, b));
        printf("hata = %f\n",(a - b)/pow(2, ite));
        max--;
        while ((a - b)/pow(2, ite) >= e  && f(str, c) != 0 && max != 0) {
            c = (a + b) / 2;
            if (f(str, c) * f(str, a) < 0) {
                b = c;
            } else {
                a = c;
            }
            ite++;
            max--;
            printf("\n%d. iterasyon\n",ite);
		    printf("ust = %f => f(ust) = %f\n", a, f(str, a));
		    printf("orta = %f => f(orta) = %f\n", (a+b)/2, f(str, (a+b)/2));
		    printf("alt = %f => f(alt) = %f\n", b, f(str, b));
		    printf("hata = %f\n",(a - b)/pow(2, ite));
        }
    } else {
        printf("Girmis oldugunuz degerler arasinda kok bulunmamaktadir.\n");
    }
    
    printf("\ngirmis oldugunuz denklemin yaklasik koku %f'dir\n", (a+b)/2);
}

void regulaFalsi(){
	char str[100];
    float a, b, c, e;
	int ite=1,max,n=1;
    system("cls");
    printf("Regula-Falsi yontemiyle kokunun bulunmasini istediginiz fonksiyonu giriniz: ");
    scanf("%s", str);
    printf("Koku icerisine alan iki deger giriniz :");
    scanf("%f %f", &a, &b);
    printf("Epsilon degerini giriniz :");
    scanf("%f", &e);
    printf("Max iterasyon degerini giriniz :");
    scanf("%d", &max);
    c = (b*f(str, a) - a*f(str, b)) / (f(str, a)-f(str, b));

    if (f(str, a) * f(str, b) < 0) {
        if (b > a) {
            float temp = a;
            a = b;
            b = temp;
        }
        printf("\n%d. iterasyon\n",ite);
        printf("ust = %f => f(ust) = %f\n", a, f(str, a));
        printf("alt = %f => f(alt) = %f\n", b, f(str, b));
        printf("x%d = %f => f(x%d) = %f\n", n, c,n,f(str,c));
        printf("fark = %f\n",(a - b)/pow(2, ite));
        max--;
        while ((a - b)/pow(2, ite) >= e  && f(str, c) != 0 && max != 0) {
            if (f(str, c) * f(str, a) < 0) {
                b = c;
            } else {
                a = c;
            }
            c = (b*f(str, a) - a*f(str, b)) / (f(str, a)-f(str, b));
            n++;

            ite++;
            max--;
            printf("\n%d. iterasyon\n",ite);
	        printf("ust = %f => f(ust) = %f\n", a, f(str, a));
	        printf("alt = %f => f(alt) = %f\n", b, f(str, b));
	        printf("x%d = %f => f(x%d) = %f\n", n, c,n,f(str,c));
	        printf("fark = %f\n",(a - b)/pow(2, ite));
        }
    } else {
        printf("Girmis oldugunuz degerler arasinda kok bulunmamaktadir.\n");
    }
    
    printf("\ngirmis oldugunuz denklemin yaklasik koku %f'dir\n", c);
}

void newtonRaphson(){
	char str[100];
    float a, c, e;
	int ite=1,max,n=1;
    system("cls");
    printf("Newton Raphson yontemiyle kokunun bulunmasini istediginiz fonksiyonu giriniz: ");
    scanf("%s", str);
    printf("Baslangic degeri giriniz :");
    scanf("%f", &a);
    printf("Epsilon degerini giriniz :");
    scanf("%f", &e);
    printf("Max iterasyon degerini giriniz :");
    scanf("%d", &max);
    c = a-f(str,a)/((f(str,a+0.000001)-f(str,a))/0.000001); // x1 = x0-(f(x0)/f'(x0)) 

    printf("\n%d. iterasyon\n",ite);
    printf("x%d = %f => f(x%d) = %f\n",n,c,n, f(str, c));
    printf("fark = %f\n",maxF(a-c,c-a));
    max--;
    while (maxF(a-c,c-a) >= e  && f(str, c) != 0 && max != 0) {
    	a = c;
        c = a-f(str,a)/((f(str,a+0.000001)-f(str,a))/0.000001);
        n++;

        ite++;
        max--;
        printf("\n%d. iterasyon\n",ite);
        printf("x%d = %f => f(x%d) = %f\n",n,c,n, f(str, c));
        printf("fark = %f\n",maxF(a-c,c-a));
    }
    
    printf("\ngirmis oldugunuz denklemin yaklasik koku %f'dir\n", c);
}

void matrisInvers(){
	system("cls");
	int i,j,k,boyut,alert,a,b;
	float matris[10][10], birim[10][10], sayi;
	printf("Tersinin bulunmasini istediginiz matrisin boyutunu giriniz: ");
	scanf("%d",&boyut);
	printf("Matrisin elemanlarini sirasiyla giriniz:\n");
	for(i=0;i<boyut;i++){
		for(j=0;j<boyut;j++){
			printf("matris[%d][%d]=> ",i+1,j+1);
			scanf("%f",&matris[i][j]);
			if(i==j){
				birim[i][j]=1;
			}else{
				birim[i][j]=0;
			}
		}
	}
	for(j=0;j<boyut;j++){
		alert=0;
		for(i=j+1;i<boyut;i++){
			if(matris[i][j]!=0){
				sayi=matris[i][j];
				for(k=0;k<boyut;k++){
					matris[i][k]=matris[i][k]/sayi*matris[j][j]-matris[j][k];
					birim[i][k]=birim[i][k]/sayi*matris[j][j]-birim[j][k];	
				}	
			}
			if(matris[i][i]==0 && i<boyut-1){
				alert=1; // kosegendeki elemanlarýn sifir olmasý ihtimalini dusundum.
				a=i+1,b=i;
			}
		}
		if(alert==1){
			while(matris[a][b]==0 && a<boyut){
			a++;
			}
			if(matris[a][b]!=0){
				for(k=0;k<boyut;k++){
					float temp=matris[a][k];
					matris[a][k]=matris[b][k];
					matris[b][k]=temp;
					temp=birim[a][k];
					birim[a][k]=birim[b][k];
					birim[b][k]=temp;
				}
			}
		}
	}
	for(i=0;i<boyut;i++){
		if(matris[i][i]!=0){
			sayi = matris[i][i];
			for(j=0;j<boyut;j++){
				matris[i][j]/=sayi;
				birim[i][j]/=sayi;
			}
		}	
	}
	for(j=boyut-1;j>=0;j--){
		for(i=j-1;i>=0;i--){
			if(matris[i][j]!=0){
				sayi=matris[i][j];
				for(k=0;k<boyut;k++){
					matris[i][j]=0;
					birim[i][k]=birim[i][k]-birim[j][k]*sayi;	
				}	
			}
		}
	}
	printf("\nGirmis oldugunuz matrisin tersi:\n");
	for(i=0;i<boyut;i++){
		for(j=0;j<boyut;j++){
			if (birim[i][j] == -0.0) {
                birim[i][j] = 0.0;
            }
			printf("%f ",birim[i][j]);
		}
		printf("\n");
	}
}

void gaussElemination(){
	system("cls");
	char katsayi='a';
	int i,j,k,boyut,alert,a,b;
	float matris[10][10],result[10], sayi;
	printf("Bilinmeyen sayisini giriniz: ");
	scanf("%d",&boyut);
	for(i=0;i<boyut;i++){
		for(j=0;j<boyut-1;j++){
			printf(" %c%d*x*%d +",katsayi++,i+1,j+1);
		}
		printf(" %c%d*x*%d = %c%d\n",katsayi,i+1,++j,katsayi+1,i+1);
		katsayi='a';
	}
	printf("\nMatrisin elemanlarini sirasiyla giriniz:");
	for(i=0;i<boyut;i++){
		printf("\n");
		for(j=0;j<boyut+1;j++){
			printf("%c%d=> ",katsayi++,i+1);
			scanf("%f",&matris[i][j]);
		}
		katsayi='a'; 
	}
	for(j=0;j<boyut;j++){
		alert=0;
		for(i=j+1;i<boyut;i++){
			if(matris[i][j]!=0){
				sayi=matris[i][j];
				for(k=0;k<boyut+1;k++){
					matris[i][k]=matris[i][k]/sayi*matris[j][j]-matris[j][k];
				}	
			}
			if(matris[i][i]==0 && i<boyut-1){
				alert=1; // kosegendeki elemanlarýn sýfýr olmasý ihtimalini dusundum.
				a=i+1,b=i;
			}
		}
		if(alert==1){
			while(matris[a][b]==0 && a<boyut){
			a++;
			}
			if(matris[a][b]!=0){
				for(k=0;k<boyut+1;k++){
					float temp=matris[a][k];
					matris[a][k]=matris[b][k];
					matris[b][k]=temp;
				}
			}
		}
	}
	for(i=0;i<boyut;i++){
		if(matris[i][i]!=0){
			sayi = matris[i][i];
			for(j=0;j<boyut+1;j++){
				matris[i][j]/=sayi;
			}
		}	
	}
	printf("\nGirilen matrisin son hali:\n");
	for(i=0;i<boyut;i++){
		for(j=0;j<boyut+1;j++){
			if (matris[i][j] == -0.0) {
                matris[i][j] = 0.0;
            }
            printf("%f ",matris[i][j]);
		}
		printf("\n");
	}
	for(i=boyut-1;i>=0;i--){
		for(j=boyut-1;j>=i;j--){
			if(i!=j){
				matris[i][boyut] = matris[i][boyut] - matris[i][j] * result[j];
			}else{
				result[j] = matris[i][boyut];
			}
		}
	}
	printf("\nSONUC:\n");
	for(i=0;i<boyut;i++){
		printf("x%d = %f\n",i+1,result[i]);
	}
	
}

void gaussSeidel() {
    system("cls");
    char katsayi = 'a';
    int i, k, j, boyut,maxIndex,flag=0,maxIte,ite=0;
    float matris[10][10], result[10], e,max,max1=1,max2=1,temp,before;
    printf("Bilinmeyen sayisini giriniz: ");
	scanf("%d",&boyut);
	for(i=0;i<boyut;i++){
		for(j=0;j<boyut-1;j++){
			printf(" %c%d*x*%d +",katsayi++,i+1,j+1);
		}
		printf(" %c%d*x*%d = %c%d\n",katsayi,i+1,++j,katsayi+1,i+1);
		katsayi='a';
	}
	printf("\nMatrisin elemanlarini sirasiyla giriniz:");
	for(i=0;i<boyut;i++){
		printf("\n");
		for(j=0;j<boyut+1;j++){
			printf("%c%d=> ",katsayi++,i+1);
			scanf("%f",&matris[i][j]);
		}
		katsayi='a'; 
	}
    printf("\nEpsilon degerini giriniz: ");
    scanf("%f", &e);
    printf("Max iterasyon degerini giriniz :");
    scanf("%d", &maxIte);
    printf("\nbaslangic degerlerini giriniz: \n");
    for (i = 0; i < boyut; i++) {
    	printf("x%d => ",i+1);
        scanf("%f",&result[i]);
    }
	
	for(j=0;j<boyut;j++){
		max = matris[j][j];
		for(i=j+1;i<boyut;i++){
			if(matris[i][j]>max){
				max=matris[i][j];
			}
		}
		max1 *= max;
	}
	for(j=boyut-1;j>=0;j--){
		max = matris[j][j];
		for(i=j-1;i>=0;i--){
			if(matris[i][j]>max){
				max=matris[i][j];
			}
		}
		max2 *= max;
	}
	if(max1>=max2){
		for(j=0;j<boyut;j++){
			max = matris[j][j];
	    	maxIndex = j;
			for(i=j+1;i<boyut;i++){
				if(matris[i][j]>max){
					max=matris[i][j];
					maxIndex=i;
				}
			}
			if(maxIndex != j){
				for(k=0;k<boyut+1;k++){
				temp=matris[maxIndex][k];
				matris[maxIndex][k]=matris[j][k];
				matris[j][k]=temp;
				}
			}
		}
	}else{
		for(j=boyut-1;j>=0;j--){
			max = matris[j][j];
	    	maxIndex = j;
			for(i=j-1;i>=0;i--){
				if(matris[i][j]>max){
					max=matris[i][j];
					maxIndex=i;
				}
			}
			if(maxIndex != j){
				for(k=0;k<boyut+1;k++){
				temp=matris[maxIndex][k];
				matris[maxIndex][k]=matris[j][k];
				matris[j][k]=temp;
				}
			}
		}
	}
	
	
	printf("\nGirilen matrisin son hali:\n");
	for(i=0;i<boyut;i++){
		for(j=0;j<boyut+1;j++){
			if (matris[i][j] == -0.0) {
                matris[i][j] = 0.0;
            }
            printf("%f ",matris[i][j]);
		}
		printf("\n");
	}
	
	while(flag!=boyut && ite<maxIte){
		flag=0;
		ite++;
		printf("\n");
		for (i = 0; i < boyut; i++) {
			before=result[i];
			result[i]=matris[i][boyut];
			for (j = 0; j < boyut; j++) {
				if(i!=j){
					result[i]-=matris[i][j]*result[j];
				}
    		}
    		result[i]/=matris[i][i];
    		printf("x%d = %f	,	|fark| = %f\n",i+1,result[i],fabs(before-result[i]));
    		if(fabs(before-result[i])<=e){
    			flag++;
			}
    	}
	}
    printf("\nSONUC:\n");
    for (i = 0; i < boyut; i++) {
        printf("x%d = %f\n", i + 1, result[i]);
    }
}

void numericalDerivative(){
	system("cls");
	typedef struct Turev{
		char str[100];
		float x;
		float h;
		float geriFark;
		float ileriFark;
		float merkeziFark;
	}Turev;
	Turev turev;
	int method;
	
	printf("Turevinin bulunmasini istediginiz fonksiyonu giriniz: ");
	scanf("%s", turev.str);
	printf("Turevinin bulunmasini istediginiz noktayi giriniz: ");
	scanf("%f", &turev.x);   
	printf("Fark(h) degerini giriniz: ");
	scanf("%f", &turev.h);
	
	printf("\n 1. Geri fark yontemi");
	printf("\n 2. Ileri fark yontemi");
	printf("\n 3. Merkezi fark yontemi");
	printf("\n Lutfen bir yontem seciniz: ");
	scanf("%d",&method);
	while(method!=1 && method!=2 && method!=3){
		printf("\n Lutfen gecerli bir deger giriniz: ");
		scanf("%d",&method);
	}
	if(method==1){
		turev.geriFark = (f(turev.str,turev.x)-f(turev.str,turev.x-turev.h))/turev.h;
		printf("\ngirilen noktanin geri fark yontemi ile turevi => %f \n", turev.geriFark);
	}else if(method==2){
		turev.ileriFark = (f(turev.str,turev.x+turev.h)-f(turev.str,turev.x))/turev.h;
		printf("\ngirilen noktanin ileri fark yontemi ile turevi => %f \n", turev.ileriFark);
	}else if(method==3){
		turev.merkeziFark = (f(turev.str,turev.x+turev.h)-f(turev.str,turev.x-turev.h))/(2*turev.h);
		printf("\ngirilen noktanin merkezi fark yontemi ile turevi => %f \n", turev.merkeziFark);
	}
	
}

void simpsonIntegral(){
	system("cls");
	char str[100];
	float alt, ust,n,alan=0,h;
	int i,method;
	printf("\n1. Simpson 1/3 kurali");
	printf("\n2. Simpson 3/8 kurali");
	printf("\nKullanmak istediginiz kurali seciniz: ");
	scanf("%d",&method);
	while(method!=1 && method!=2){
		printf("\n Lutfen gecerli bir deger giriniz (1 or 2): ");
		scanf("%d",&method);
	}
	
	printf("Integralinin bulunmasini istediginiz fonksiyonu giriniz: ");
	scanf("%s", str);
	printf("Alt ve ust sinirlari sirasiyla giriniz: ");
	scanf("%f %f", &alt, &ust);
	
	if(method==1){
		printf("Araligi kaca bolecegini belirten n degerini giriniz (n cift bir sayi olmalidir): ");
		scanf("%f",&n);
		while((int)n % 2 != 0){
			printf("\n n degeri cift bir sayi olmalidir! Gecerli bir n degeri giriniz: ");
			scanf("%f",&n);
		}
		h = (ust-alt)/n;
		alan=f(str,alt)+f(str,ust);
		for(i=1;i<n;i+=2){
			alan += 4*f(str,alt+i*h);
		}
		for(i=2;i<n-1;i+=2){
			alan += 2*f(str,alt+i*h);
		}
		alan *= h/3;
		printf("\nSONUC: %f \n", alan);	
		
	}else{
		printf("Araligi kaca bolecegini belirten n degerini giriniz (n, 3'un kati olan bir sayi olmalidir): ");
		scanf("%f",&n);
		while((int)n % 3 != 0){
			printf("\n n, 3'un kati olan bir sayi olmalidir! Gecerli bir n degeri giriniz: ");
			scanf("%f",&n);
		}
		h = (ust-alt)/n;
		alan=f(str,alt)+f(str,ust);
		for(i=1;i<n;i+=3){
			alan += 3*f(str,alt+i*h);
		}
		for(i=2;i<n-1;i+=3){
			alan += 3*f(str,alt+i*h);
		}
		for(i=3;i<n-2;i+=3){
			alan += 2*f(str,alt+i*h);
		}
		alan *= 3*h/8;
		printf("\nSONUC: %f \n", alan);
	}
}
	 
void trapezIntegral(){
	system("cls");
	char str[100];
	float alt, ust,n,alan=0,h;
	int i;
	
	printf("Integralinin trapez yontemiyle bulunmasini istediginiz fonksiyonu giriniz: ");
	scanf("%s", str);
	printf("Alt ve ust sinirlari sirasiyla giriniz: ");
	scanf("%f %f", &alt, &ust);
	
	printf("Araligi kaca bolecegini belirten n degerini giriniz: ");
	scanf("%f",&n);

	h = (ust-alt)/n;
	alan=f(str,alt)+f(str,ust);
	for(i=1;i<n;i++){
		alan += 2*f(str,alt+i*h);
	}

	alan *= h/2;
	printf("\nSONUC: %f \n", alan);
}	 
	
void gregoryNewton(){
	system("cls");
	float tanim[20],goruntu[20],eskiGoruntu[20],x,sum,h,farklarCarpimi,faktoriyel;
	int sayi, i,j;
	printf("\nEleman sayisini giriniz: ");
	scanf("%d", &sayi);
	for(i = 0; i < sayi; i++){
		printf("\n%d. elemani goruntusu ile birlikte giriniz: ", i+1);
		scanf(" %f %f", &tanim[i], &goruntu[i]);
	}
	printf("\nSonucunu bulmak istediginiz degeri giriniz: ");
	scanf("%f", &x);
	h = tanim[1] - tanim[0];
	sum=goruntu[0];
	
	for(i=1; i < sayi; i++){
		farklarCarpimi=1;
		faktoriyel=1;
		for(j = 0; j < i; j++){
			farklarCarpimi *= (x - tanim[j])/h;
			faktoriyel *= (j+1);
		}
		for(j=0; j<sayi-i-1;j++){
			goruntu[j]=goruntu[j+1] - goruntu[j];
		}
		goruntu[j+1]=0;
		sum += farklarCarpimi*goruntu[0]/faktoriyel;															
	}
	printf("\nSONUC: f(%f) = %f\n",x, sum);
}

void menu(){
	int method;
	system("cls");
	if(flag!=0){
		printf(" Lutfen gecerli bir deger giriniz[1-9]\n\n");
		flag=0;
	}
	printf(" 1. Bisection Yontemi					Cikmak  icin 0'a basiniz");
	printf("\n 2. Regula-Falsi Yontemi");
	printf("\n 3. Newton-Raphson Yontemi");
	printf("\n 4. NxN'lik bir matrisin tersi");
	printf("\n 5. Gauss Eleminasyon");
	printf("\n 6. Gauss Seidal Yontemi");
	printf("\n 7. Sayisal Turev Yontemleri");
	printf("\n 8. Simpson Yontemi");
	printf("\n 9. Trapez Yontemi");
	printf("\n 10. Gregory-Newton Enterpolasyonu\n");
	printf("\n Kullanmak istediginiz yontemi seciniz: ");
	scanf("%d", &method);
	
	switch(method){
		case 1:bisection();break;
		case 2:regulaFalsi();break;
		case 3:newtonRaphson();break;
		case 4:matrisInvers();break;
        case 5:gaussElemination();break;
		case 6:gaussSeidel();break;
		case 7:numericalDerivative();break;
		case 8:simpsonIntegral();break;
		case 9:trapezIntegral();break;
		case 10:gregoryNewton();break;
        case 0:exit(0);break;
        default:
        system("cls");	
		flag=1;
        menu();
	}
}

int main() {
    char choice = 'm';

    menu();
    while (choice == 'm') {
        printf("\nMenuye donmek icin m'ye, cikmak icin q'ya basin: ");
        scanf(" %c", &choice);

        while (choice != 'm' && choice != 'q') {
        	system("cls");
            printf("Lutfen gecerli bir islem giriniz!!\n");
            printf("Menuye donmek icin m'ye, cikmak icin q'ya basin: ");
            scanf(" %c", &choice);
        }
        if (choice == 'm') {
            menu();
        }
    }

    return 0;
}
