/* Emircan KİREZ - Ch3rry */
/* Son Güncelleme - 18/09/2022 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int *createIndexArray(int size);
char *createLettersArray(char *word);
void printFile(char *letters, int *index, int size, FILE *fPtr);
void checkAndUpdate(int i, int *index, int size);

int main(){
	char word[20];
	printf("Kelimeyi yaziniz: ");
	scanf("%s", word);

	int size = strlen(word);
	char *letters = createLettersArray(word); //kelimeyi hem küçük hem de büyük harfleriyle sakladığım dizi
	int *index = createIndexArray(size); // letters dizisinden hangi indeksleri kullanacağımızı saklar
	
	FILE *fPtr = fopen("combinations.txt", "w"); 

	int i;
	int limit = pow(2, size);
	for(i = 1; i <= limit; i++){
		printFile(letters, index, size, fPtr);
		checkAndUpdate(i, index, size);	
	}

	// yapılması gereken son işlemler
	fclose(fPtr);
	free(index);
	free(letters);
	return 0;
}

int *createIndexArray(int size){
	int i;
	int *array = (int *)malloc(sizeof(int) * size);
	for(i = 0; i < size; i++){
		array[i] = i;
	}
	return array;
}

char *createLettersArray(char *word){
	int i, size = strlen(word), limit = size * 2;
	char *array = (char *)malloc(sizeof(char) * limit);
	for(i = 0; i < size; i++){ //küçük harfleri ekliyorum
		array[i] = word[i];
	}

	for(; i < limit; i++){ //harfleri büyük harf yapıp ekliyorum
		array[i] = toupper(word[i % size]);
	}
	return array;
}

void printFile(char *letters, int *index, int size, FILE *fPtr){
	int i;
	for(i = 0; i < size; i++)
		fputc(letters[index[i]], fPtr); //karakter karakter dosyaya yazar
	fprintf(fPtr, "\n");
}

void checkAndUpdate(int iteration, int *index, int size){
	// doğruluk tablosu yaparken kullandığımız mantık aklıma geldi ve onu burada kullandım
	/* 
       	0 0 0 // birler basamağı her iterasyonda değişir
		0 0 1 // 2ler basamağı her 2 iterasyonda bir değişir
		0 1 0 // 4ler basamağı her 4 iterasyonda bir değişir
		0 1 1
		1 0 0
	*/

	int carpan = 1;
	int j;
	for(j = size - 1; j >= 0; j--){ // bütün indeksler için büyük/küçük harf değişim gerekliliği kontrolü
		if(iteration % carpan == 0) // her indeks için iterasyon kontrolü - eğer doğruysa demekki değişim zamanı
			if(index[j] == j) // eğer kendisi ise büyük yap - bu yüzden küçük ve büyük harflerden oluşan bir dizi (letters) oluşturdum.
				index[j] += size;
			else
				index[j] = j;
		carpan *= 2;
	}
}
