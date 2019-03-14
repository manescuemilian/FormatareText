#include <stdio.h>
#include <string.h>

void cuvant_linie (char s[1000]) {
	//vector in care stocam lungimile cuvintelor de pe o linie
	/*int len_words = 0, lungime;
	int i;
	for (i = 0; i < o_line; i++) {
		len_words = 0;
		while (s != ' ' && s != '\n' && s!= '\0') {
			len_words++;
		}
	}*/
	int lungime;
	char *words = strtok (s, " ");
	lungime = strlen (words);
	while (words != NULL) {
		if (lungime < strlen(words)) {
			lungime = strlen (words);
		}
		words = strtok (NULL, " ");
	}

	printf("%d\n", lungime);
}

int main () {
	char s[1000] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque a nunc";
	puts (s);
	cuvant_linie (s);
}