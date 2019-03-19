# include<iostream>
#include<string.h>
#include<fstream>

using namespace std;

#define FALSE 0
#define TRUE 1

//char b[50];							// b stores the word to be stemmend

int k0 = 0;							// k0 represent zeroth element of b
//int j;								// j represents last elemnt of b

class extra{
public:

        virtual int isCons(int)=0;
		virtual int m()=0;
		virtual int vowelInStem()=0;
		virtual int doubl()=0;
		virtual int cvc(int)=0;
		virtual int stemEndsWith(char str[30], int end_len)=0;
		virtual void replace(char str[30], int end_len)=0;
		virtual void dbl()=0;

};

class Stem:public extra{
public:

char b[30];
	int j;

        int isCons(int);
		int m();
		int vowelInStem();
		int doubl();
		int cvc(int);
		int stemEndsWith(char str[30], int end_len);
		void replace(char str[30], int end_len);
		void dbl();

		void step1a();
		void step1b();
		void step1c();
		void step2();
		void step3();
		void step4();
		void step5a();
		void step5b();

		void stem();
		int search();
};


//int search();

int Stem::isCons(int i){					// Will return TRUE is the letter b[i] is consonant otherwise returns FALSE

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
						return (!isCons(i-1));
					}
		default : return TRUE;
	}
}



int Stem::m()								// To calculate m where m is : <C>(VC)^m<V>, where C: string of consonants V: string of vowels
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


int Stem::vowelInStem(){					// Returns TRUE if the word has a vowel before the part which is to be stemmed
	for(int i=k0 ; i<j ; i++){
		if(!isCons(i)) return TRUE;
	}
	return FALSE;
}



int Stem::doubl(){						// Returns TRUE if last two letters of word are same eg: -tt, -pp, -ss etc.

	if(b[j] == b[j-1]){
		return TRUE;
	}
	return FALSE;
}

void Stem::dbl(){						// Returns TRUE if last two letters of word are same eg: -tt, -pp, -ss etc.

	if(b[j] == b[j-1]){
		b[j] = '\0';
		j--;
	}


}


int Stem::cvc(int i)						// Checks for 'cvc' in the string. This is to add e in small words eg : cav(e), lov(e), hop(e), crim(e), but not snow, box, tray.
{
	if (strlen(b)>2 || !isCons(i) || isCons(i-1) || !isCons(i-2)) return FALSE;

	int ch = b[i];
    if (ch == 'w' || ch == 'x' || ch == 'y') return FALSE;

   	return TRUE;
}


int Stem::stemEndsWith(char str[30], int end_len){		// Cheks if the word(b) ends with string "str"

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

void Stem::replace(char str[30], int end_len){			// Replaces last end_len letters of b with str

	int i, q=0;
	int slen = strlen(b);
	slen -= end_len;
    i=slen;
	if(strcmp(str, "")==0){

		b[slen] = '\0';
		return;
	}

	for(i=slen, q=0 ; str[q]!='\0'; i++, q++){
		b[i] = str[q];
	}
	b[i]='\0';

}



/*Step 1 deals with plurals and past participles*/

void Stem::step1a(){

	if(stemEndsWith("sses", 4))	replace("ss", 4);
	else if(stemEndsWith("ies", 3))	replace("i", 3);
	else if(stemEndsWith("s", 1))	replace("", 1);

	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

void Stem::step1b(){

	if(m()>0 && stemEndsWith("eed", 3))	replace("ee", 3);

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

void Stem::step1c(){

	if(vowelInStem() && stemEndsWith("y", 1))	replace("i", 1);
	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

/* Step 2 */

void Stem::step2(){

	if(m()>0){

		if(stemEndsWith("ational", 7))			replace("ate", 7);
		else if(stemEndsWith("tional", 6))		replace("tion", 6);
		else if(stemEndsWith("enci", 4))	  	replace("ence", 4);
		else if(stemEndsWith("anci", 4))		replace("ance", 4);
		else if(stemEndsWith("izer", 4))		replace("ize", 4);
		else if(stemEndsWith("abli", 4))		replace("able", 4);
		else if(stemEndsWith("alli", 4))		replace("al", 4);
		else if(stemEndsWith("entli", 5))		replace("ent", 5);
		else if(stemEndsWith("eli", 3))			replace("e", 3);
		else if(stemEndsWith("ousli", 5))		replace("ous", 5);
		else if(stemEndsWith("ization", 7))		replace("ize", 7);
		else if(stemEndsWith("ation", 5))		replace("ate", 5);
		else if(stemEndsWith("alism", 5))		replace("al", 5);
		else if(stemEndsWith("iveness", 7))		replace("ive", 7);
		else if(stemEndsWith("fulness", 7))		replace("ent", 7);
		else if(stemEndsWith("ousness", 7))		replace("ous", 7);
		else if(stemEndsWith("aliti", 5))		replace("al", 5);
		else if(stemEndsWith("iviti", 5))		replace("ive", 5);
		else if(stemEndsWith("biliti", 6))		replace("ble", 6);
	}

	j = strlen(b);
	b[j] ='\0';
	j--;
}

/* Step 3 */

void Stem::step3(){

	if(m()>0){
		if(stemEndsWith("icate", 5))			replace("ic", 5);
		else if(stemEndsWith("ative", 5))		replace("", 5);
		else if(stemEndsWith("alize", 5))		replace("al", 5);
		else if(stemEndsWith("iciti", 5))		replace("ic", 5);
		else if(stemEndsWith("ical", 4))		replace("ic", 4);
		else if(stemEndsWith("ful", 3))			replace("", 3);
		else if(stemEndsWith("ness", 4))		replace("", 3);
	}

	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

/* Step 4 */

void Stem::step4(){

	if(m()>1){
		if(stemEndsWith("al", 2))					replace("", 2);
		else if(stemEndsWith("ance", 4))			replace("", 4);
		else if(stemEndsWith("ence", 4))			replace("", 4);
		else if(stemEndsWith("er", 2))				replace("", 2);
		else if(stemEndsWith("ical", 4))			replace("", 4);
		else if(stemEndsWith("ic", 2))				replace("", 2);
		else if(stemEndsWith("able", 4))			replace("", 4);
		else if(stemEndsWith("ible", 4))			replace("", 4);
		else if(stemEndsWith("ant", 3))				replace("", 3);
		else if(stemEndsWith("ement", 5))			replace("", 5);
		else if(stemEndsWith("ment", 4))			replace("", 4);
		else if(stemEndsWith("ent", 3))				replace("", 3);

		else if(stemEndsWith("able", 4) && (b[j]=='s' || b[j]=='t'))
			replace("", 4);

		else if(stemEndsWith("ou", 2))			replace("", 2);
		else if(stemEndsWith("ism", 3))			replace("", 3);
		else if(stemEndsWith("iti", 3))			replace("", 3);
		else if(stemEndsWith("ous", 3))			replace("", 3);
		else if(stemEndsWith("ive", 3))			replace("", 3);
		else if(stemEndsWith("ize", 3))			replace("", 3);
	}

	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

/* Step 5 */

void Stem::step5a(){

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

void Stem::step5b(){

	if(m()>1 && doubl()==1 && b[j]=='l'){
		b[j] = '\0';
	}

	j = strlen(b);
	b[j+1] ='\0';
	j--;
}

/*	Stemming function */

void Stem::stem(){

	char temp[20];

	strcpy(temp, b);
	int i;

	step1a();
	step1b();
	step1c();


	step2();

	step3();
/*	i = search();
	if(i == 0){
		strcpy(b, temp);
		return;
	}
	else{
		strcpy(temp, b);
	}

	step4();
	i = search();
	if(i == 0){
		strcpy(b, temp);
		return;
	}
	else{
		strcpy(temp, b);
	}

	step5a();
	step5b();
	i = search();
	if(i == 0){
		strcpy(b, temp);
		return;
	}

	cout<<"\n"<<i<<"\n";
*/
    step4();
    step5a();
    step5b();
}

int Stem::search(){

	int ch = b[0];
	char temp[20];
	char fname[] = "a.txt";

	fname[0] = ch;

	ifstream file(fname);

	while(file){
		file>>temp;
		if(strcmp(temp, b)==0){
			return TRUE;
		}
	}
	return FALSE;

}


int main(){
/*
	ifstream fin("file2.txt");
	ofstream fout("new_word.txt");



	while(fin){
		fin>>b;
		if(fin){
			j=strlen(b)-1;
			stem();
			fout<<b<<" ";
		}
	}

*/
	Stem obj;

	cin>>obj.b;
	obj.j = strlen(obj.b) - 1 ;

	obj.stem();

	cout<<obj.b;
    getchar();

	return 0;
}


