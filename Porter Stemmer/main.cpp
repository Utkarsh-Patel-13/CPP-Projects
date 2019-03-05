#include<iostream>
#include<string.h>
#include<fstream>

using namespace std;

#define FALSE 0
#define TRUE 1

char b[50];							// b stores the word to be stemmend

int k0 = 0;							// k0 represent zeroth element of b
int j;								// j represents last elemnt of b


int isCons(int i){					// Will return TRUE is the letter b[i] is consonant otherwise returns FALSE
	
	switch(b[i]){
		
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u': return FALSE;
		case 'y':  
					if(i==k0){
						return TRUE;
					} 	
					else{
						return !isCons(i-1);
					}
	}	
}



int m()								// To calculate m where m is : <C>(VC)^m<V>, where C: string of consonants V: string of vowels
{
	int i=k0;
	int m_ = 0;

  while(TRUE){
	
	if(i>j) return m_;  			//for 1 letter words
	
	if(!isCons(i))      			//loop to skip V ie skip first vowel string if the word starts from vowel
		break;
		
	i++;
  }
  i++;						
  
  while(TRUE){
  	
  	while(TRUE){
	  	if(i>j) return m_;			//if i reaches end of string
	  	
	  	if(isCons(i)){
	  		break;	
		}
		i++;
	}
	i++;
	m_++;							//counting m
	
	while(TRUE){
		if(i>j) return m_;
		
		if(!isCons(i)){
			break;
		}
		i++;
	}	
  }
}


int vowelInStem(){					// Returns TRUE if the word has a vowel before the part which is to be stemmed
	for(int i=k0 ; i<j ; i++){
		if(!isCons(i)) return TRUE;
	}
	return FALSE;
}



int doubl(){						// Returns TRUE if last two letters of word are same eg: -tt, -pp, -ss etc.
	int k=strlen(b);
	if(b[k] == b[k-1]){
		return TRUE;
	}
	return FALSE;
}


int cvc(int i)						// Checks for 'cvc' in the string. This is to add e in small words eg : cav(e), lov(e), hop(e), crim(e), but not snow, box, tray.
{  
	if (strlen(b)>2 || !isCons(i) || isCons(i-1) || !isCons(i-2)) return FALSE;  
	
	int ch = b[i];
    if (ch == 'w' || ch == 'x' || ch == 'y') return FALSE;
    
   	return TRUE;
}


int stemEndsWith(char *str, int end_len){		// Cheks if the word(b) ends with string "str"
	
	int slen = strlen(b);
	
	slen -= end_len;
	
	if(slen<=0) return FALSE;
	
	for(int i=slen, q=0 ; b[i]!= '\0' ; i++, q++){
		if(b[i]!= str[q]){
			return FALSE;
		}
	}
	return TRUE;
}

void replace(char *str, int end_len){			// Replaces last end_len letters of b with str
	
	int i, q=0;
	int slen = strlen(b);
	slen -= end_len;
	
	if(strcmp(str, "")){
		b[slen] = '\0';
		return;
	}
	
	for(i=slen, q=0 ; str[q]!='\0'; i++, q++){		
		b[i] = str[q];		
	}
	b[i]='\0';
	
}



/*Step 1 deals with plurals and past participles*/

void step1a(){

	if(stemEndsWith("sses", 4))	replace("ss", 4);
	else if(stemEndsWith("ies", 3))	replace("i", 3);
	else if(stemEndsWith("s", 1))	replace("", 1);			//faulty

	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

void step1b(){
	
	if(m()>0 && stemEndsWith("eed", 3))	replace("ee", 3);
																		//faulty
	else if(vowelInStem() && stemEndsWith("ed", 2)){
		replace("", 2);
		
		if(stemEndsWith("at", 2))	replace("ate", 2);
		else if(stemEndsWith("bl", 2))	replace("ble", 2);	
		else if(stemEndsWith("iz", 2))	replace("ize", 2);	
		
		j = strlen(b);
		
		if(doubl()==1 && (b[j]!='l' || b[j]!='s'|| b[j]!='z')){
				j--;
				b[j] = '\0';
		}
		else if(m() == 1 && cvc(j)){
			replace("e", 0);
		}
	}	
	
	if(vowelInStem() && stemEndsWith("ing", 3)){
		replace("", 3);
		
		if(stemEndsWith("at", 2))	replace("ate", 2);
		else if(stemEndsWith("bl", 2))	replace("ble", 2);	
		else if(stemEndsWith("iz", 2))	replace("ize", 2);	
		
		j = strlen(b);
		
		if(doubl()==1 && (b[j]!='l' || b[j]!='s'|| b[j]!='z')){
				j--;
				b[j] = '\0';
		}
		else if(m() == 1 && cvc(j)){
			replace("e", 0);
		}
	}
	
	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

void step1c(){
	
	if(vowelInStem() && stemEndsWith("y", 1))	replace("i", 1);
	
	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

/* Step 2 */
 
void step2(){
	
	if(m()>0){
		
		if(stemEndsWith("ational", 7))		replace("ate", 7);
		if(stemEndsWith("tional", 6))		replace("tion", 6);
		if(stemEndsWith("enci", 4))		replace("ence", 4);
		if(stemEndsWith("anci", 4))		replace("ance", 4);
		if(stemEndsWith("izer", 4))		replace("ize", 4);
		if(stemEndsWith("abli", 4))		replace("able", 4);
		if(stemEndsWith("alli", 4))		replace("al", 4);
		if(stemEndsWith("entli", 5))		replace("ent", 5);
		if(stemEndsWith("eli", 3))		replace("e", 3);
		if(stemEndsWith("ousli", 5))		replace("ous", 5);
		if(stemEndsWith("ization", 7))		replace("ize", 7);
		if(stemEndsWith("ation", 5))		replace("ate", 5);
		if(stemEndsWith("alism", 5))		replace("al", 5);
		if(stemEndsWith("iveness", 7))		replace("ive", 7);
		if(stemEndsWith("fulness", 7))		replace("ent", 7);
		if(stemEndsWith("ousness", 7))		replace("ous", 7);
		if(stemEndsWith("aliti", 5))		replace("al", 5);
		if(stemEndsWith("iviti", 5))		replace("ive", 5);
		if(stemEndsWith("biliti", 6))		replace("ble", 6);		
	}
	
	j = strlen(b);
	b[j] ='\0';
	j--;
}

/* Step 3 */

void step3(){
	
	if(m()>0){
		if(stemEndsWith("icate", 5))		replace("ic", 5);
		if(stemEndsWith("ative", 5))		replace("", 5);
		if(stemEndsWith("alize", 5))		replace("al", 5);
		if(stemEndsWith("iciti", 5))		replace("ic", 5);
		if(stemEndsWith("ical", 4))		replace("ic", 4);
		if(stemEndsWith("ful", 3))		replace("", 3);
		if(stemEndsWith("ness", 4))		replace("", 3);
	}
	
	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

/* Step 4 */

void step4(){
	
	if(m()>1){
		if(stemEndsWith("al", 2))			replace("", 2);
		if(stemEndsWith("ance", 4))			replace("", 4);
		if(stemEndsWith("ence", 4))			replace("", 4);
		if(stemEndsWith("er", 2))			replace("", 2);
		if(stemEndsWith("ical", 4))			replace("", 4);
		if(stemEndsWith("ic", 2))			replace("", 2);
		if(stemEndsWith("able", 4))			replace("", 4);
		if(stemEndsWith("ible", 4))			replace("", 4);
		if(stemEndsWith("ant", 3))			replace("", 3);
		if(stemEndsWith("ement", 5))			replace("", 5);
		if(stemEndsWith("ment", 4))			replace("", 4);
		if(stemEndsWith("ent", 3))			replace('\0', 3);
		
		if(stemEndsWith("able", 4) && (b[j]=='s' || b[j]=='t'))
			replace('\0', 4);
			
		if(stemEndsWith("ou", 2))			replace("", 2);
		if(stemEndsWith("ism", 3))			replace("", 3);
		if(stemEndsWith("iti", 3))			replace("", 3);
		if(stemEndsWith("ous", 3))			replace("", 3);
		if(stemEndsWith("ive", 3))			replace("", 3);
		if(stemEndsWith("ize", 3))			replace("", 3);
	}
	
	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

/* Step 5 */

void step5a(){
	
	if(m()>1 && stemEndsWith("e", 1)){
		replace("", 1);
	}
	else if(m()==1 && !cvc(j) && stemEndsWith("e", 1)){
		replace("", 1);
	}
	
	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

void step5b(){								//wrong logic
	
	if(m()>1 && doubl()==1 && b[j]=='l'){
		b[j] = '\0';
	}
	
	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

/*	Stemming function */

void stem(){
	
	step1a();					
	step1b();
	step1c();
	
	if(m()>0)
	step2();	

	if(m()>0)	
	step3();						
	
	if(m()>1)	
	step4();						
	
	if(m()>=1)		
	step5a();						
		
//	if(m()>1)	
//	step5b();						//working but undesired output
//	cout<<b<<m()<<endl;
	
}


int main(){
	
	ifstream fin("word.txt");
	ofstream fout("new_word.txt");
	
	
	
	while(fin){
		fin>>b;
		if(fin){
			j=strlen(b)-1;
			stem();
			fout<<b<<" ";
		}
	}
	
	/*
	cin>>b;
	j=strlen(b)-1;
	
	stem();
		
	cout<<b<<endl;
*/	
	return 0;
}
