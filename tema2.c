#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void sterge_newline (char *sir) {
	char *poz;

	if ((poz = strchr(sir, '\n')) != NULL) {
		*poz = '\0';
	}
}

void sterge_spatii (char s[1000]) {
	int i, j;

	for (i = 0; i < strlen (s); i++) {
		//daca doua caractere consecutive sunt spatii, se sterge unul din ele
		if (s[i] == ' ' && s[i + 1] == ' ') {
			for (j = i + 1; j < strlen(s); j++) {
				s[j] = s[j + 1];
			}
		//intoarce la spatiul precedent, pentru a verifica daca urmeaza spatiu
			i--;
		}
	}
}

void sterge_tab (char *s) {
	char *poz = strchr (s, '\t');

	if (poz != NULL) {
		*poz = '\n';
		*(poz + 1) = '\0';
	}
}

//verifica daca o linie contine numai spatii, sau este vida
int numai_spatii (char sir[1000]) {
	int i;

	if (sir [0] == '\0' || sir [0] == '\n') {
		return 1;
	}

	for (i = 0; i <= strlen (sir); i++) {
		if (sir[i] != ' ' || sir[i] != '\n' || sir[i] != '\0') {
			return 0;
		}
	}

	return 1;
}

// verifica daca un sir este trunchiat la o anumita pozitie
int trunchiat (char sir[1000], int pozitie) {

	if (sir[pozitie] != ' ' && sir[pozitie - 1] != ' ') {
		return 1;
	}

	return 0;
}

//pozitia maxima de la care se poate face wrap
//functia se aplica pentru fiecare linie
int poz_max (char sir[1000], int lungMax) {
	int pozitie = lungMax;

	while (trunchiat (sir, pozitie) == 1) {
			pozitie--;
	}

	return pozitie;
}

//de cate ori poate fi impartita o linie
int linie_impartita (char *linie, int lungMax) {
	int impartiri = 0, lungime;
	//stringul care ramane dupa fiecare impartire
	char *verifica;
	verifica = linie;
	//la ce pozitie se poate imparti linia
	lungime = poz_max (linie, lungMax);

	while (strlen (verifica) > lungMax ) {
		//la ce pozitie se poate imparti stringul ramas
		lungime = poz_max (verifica, lungMax);
		impartiri++;
		verifica  = verifica + lungime;
	}

	return impartiri;
}

char *wrap (char sir[1000], int lungMax) {
	char rezultat[1000];
	int pozitie;
	pozitie = lungMax;

	//cat timp linia e trunchiata in pozitia respectiv
	while (trunchiat (sir, pozitie) == 1) {
		pozitie--;
	}

	strncpy(rezultat, sir, pozitie);
	rezultat[pozitie] = '\0';
	return strdup (rezultat);
}

void leading_whitespace (char *sir) {
	int index, i;
	index = 0;
	//memoreaza pozitia la care incepe primul caracter care nu e spatiu
	while (sir[index] == ' ' || sir[index] == '\t') {
		index++;
	}

	if(index != 0) {
		i = 0;
		//elimina leading whitespace-ul, mutand toate
		while (sir[i + index] != '\0') {
	    	sir[i] = sir[i + index];
	    	i++;
		}

		sir[i] = '\0';
	}
}

void trailing_whitespace (char * sir) {
	int index, i;
	index = -1;
	i = 0;

	//afla pozitia la care se afla ultimul caracter care nu e spatiu
	while(sir[i] != '\0') {
		if(sir[i] != ' ' && sir[i] != '\n') {
			index = i;
		}

		i++;
	}

	sir[index + 1] = '\0';
}

//strcpy care sterge leading si trailing whitespace
void sstrcpy (char s[1000], char d[1000]) {
	strcpy (s, d);
	trailing_whitespace(s);
	leading_whitespace(d);
	trailing_whitespace(d);
}

//modifica parametrii comenzilor L, R, J
void parametri_1(int *start, int *end, int orig, char com[1000][1000]) {
	*start = 0;
	*end = orig + 1;
	//daca nu se specifica linia de la care se incepe
	if (atoi(com[1]) != 0) {
		*start = atoi (com[1]);
	}

	//daca nu se specifica linia pana la care se aplica operatia
	if (strcmp(com[2], "")) {
		*end = atoi (com[2]);
	}	
}

//modifica parametrii comenzii P
void parametri_2 (int *start, int *end, int *indent, 
				int orig, char com[1000][1000]) {
	*start = 0;
	*end = orig + 1;
	*indent = atoi (com[1]);

	if (atoi (com[2]) != 0) {
		*start = atoi (com[2]);
	}

	if (strcmp (com[3],"")) {
		*end = atoi (com[3]);
	}	
}

//pentru comanda I
void parametri_3(int *start, int *end, int orig, char com[1000][1000]) {
	*start = 0;
	*end = orig + 1;

	if (atoi (com[3]) != 0) {
		*start = atoi (com[3]);
	}

	if (strcmp (com[4],"")) {
		*end = atoi (com[4]);
	}	
}

//pentru comanda O
void parametri_4(int *start, int *end, int orig, char com[1000][1000]) {
	*start = 0;
	*end = orig + 1;

	if (atoi (com[4]) != 0) {
		*start = atoi (com[4]);
	}

	if (strcmp (com[5],"")) {
		*end = atoi (com[5]);
	}	
}		

//afla cea mai mare dimensiune a liniilor
int max_strlen (char s[1000][1000], int orig) {
	int lungime = strlen (s[0]);
	int i, lung_string;
	for (i = 0; i < orig; i++) {
		lung_string = strlen (s[i]);
		if (lung_string > lungime) {
			lungime = lung_string;
		}
	}	
	return lungime;
}

//copiaza continutul vectorului original in vectorul result
void copie_result (char s[1000][1000], char d[1000][1000], int org, int *res) {
	int len, i;
	for (i = 0; i < org; i++) {
		strcpy(d[i], s[i]);
		trailing_whitespace (d[i]);
		len = strlen(d[i]);
		d[i][len] = '\n';
		d[i][len + 1] = '\0';
	}

	*res = org;
}

//face o copie exacta a vectorului original
void copie_exacta (char s[1000][1000], char d[1000][1000], int org, int *res) {
	int i;

	for (i = 0; i < org; i++) {
		strcpy (d[i], s[i]);
	}

	*res = org;
}

//actualizeaza vectorul original dupa efectuarea unei operatii
void actualizare (char s[1000][1000], char d[1000][1000], int *org, int res) {
	int i;
	for (i = 0; i < res; i++) {
		strcpy (s[i], d[i]);
	}

	*org = res;
}

//lungimea cuvantului celui mai lung dintr-un string
int lungime_max_linie (char s[1000]) {
	//vector in care stocam lungimile cuvintelor de pe o linie
	int lung_cuvant = 0;
	//vectorul in care se salveaza lungimile cuvintelor
	int lungimi[1000], nr_lungimi = 0;
	int i;

	//parcurgem stringul 
	for (i = 0; s[i] != '\0'; i++) {
		lung_cuvant = 0;

		//memoreaza lungimea unui cuvant
		while (s[i] != ' ' && s[i] != '\n') {
			lung_cuvant++;
			i++;
		}

		//salveaza lungimea intr-un vector
		if (lung_cuvant != 0) {
			lungimi[nr_lungimi] = lung_cuvant;
			nr_lungimi++;
		}
	}

	//calculeaza lungimea maxima de pe linie
	int lungime_max = lungimi[0];
	for (i = 1; i < nr_lungimi; i++) {
		if (lungimi[i] > lungime_max) {
			lungime_max = lungimi[i];
		}
	}

	return lungime_max;
}

//lungimea celui mai lung cuvant din fisier
//verifica daca este mai mare decat argumentul functiei Wrap
int lungime_max_fisier (char s[1000][1000], int line) {
	int i, lungime;
	lungime = lungime_max_linie(s[0]);

	for (i = 1; i < line; i++) {
		if (lungime_max_linie(s[i]) > lungime) {
			lungime = lungime_max_linie(s[i]);
		}
	}

	return lungime;
}

void center (char s[1000], int lung_max) {
	int i, len = strlen(s);
	while (len < lung_max) {
		len++;

		//muta caracterele cu cate o pozitie in fata
		for (i = strlen(s); i > 0; i--) {
			s[i] = s[i - 1];
		}

		//adauga cate un spatiu atat la inceput, cat si la sfarsit
		s[0] = ' ';
		s[len] = ' ';
		len++;
	}
	s[len + 1] = '\0';
}

char* align_left (char s[1000]) {
	leading_whitespace (s);
	return strdup (s);
}

void align_right (char s[1000], int lung_max) {
	int i, len = strlen(s);
	//cat timp lungimea liniei nu e egala cu lungimea maxima din fisier
	//adauga un spatiu la inceputul liniei
	while (len < lung_max) {
		len++;

		for (i = strlen(s); i > 0; i--) {
			s[i] = s[i - 1];
		}

		s[0] = ' ';
	}

	s[len + 1] = '\0';
}

//adauga un caracter la inceputul unui sir
void adauga_caracter (char s[1000], char c) {
	int i, len = strlen (s);

	for (i = strlen(s); i > 0; i--) {
		s[i] = s[i - 1];
	}

	s[0] = c;
	s[len + 1] = '\0';
}

//adauga un caracter incepand de la o anumita pozitie
void adauga_caracter_pozitie (char s[1000], char c, int poz) {
	int i, len = strlen (s);

	for (i = strlen(s); i > poz; i--) {
		s[i] = s[i - 1];
	}

	s[poz] = c;
	s[len + 1] = '\0';
}

//verifica daca mai exista un spatiu dupa o anumita pozitie
int spatiu_pozitie (char s[1000], int poz) {
	int i;

	for (i = poz; i < strlen (s); i++) {
		if (s[i] == ' ') return 1;
	}

	return 0;
}

void justify (char s[1000], int lungMax) {
	//aliniaza la stanga
	align_left (s);
	leading_whitespace(s);
	//pozitie arata
	//cate_spatii arata numarul de spatii dintre doua cuvinte
	int pozitie = 0, cate_spatii = 1;
	int i = pozitie, len = strlen (s);
	while (len < lungMax && i < len) {

		//daca nu mai urmeaza niciun spatiu pe linie, o ia de la capat
		if (spatiu_pozitie (s, pozitie) == 0) {
			cate_spatii++;
			pozitie = 0;
			i = 0;
		}

		//daca gaseste un spatiu, adauga inca un spatiu acolo
		if (s[i] == ' ') {
			adauga_caracter_pozitie(s, ' ', i);
			len++;
			//sare peste spatiile adaugate
			pozitie = i + cate_spatii + 1;
			i = pozitie;
		} else {
			i++;
		}
	}
}

void paragraph (char s[1000], int indent) {
	int i, len = strlen(s);
	int j = 0;

	//adauga spatii la inceput
	while (j < indent) {
		len++;

		for (i = strlen(s); i > 0; i--) {
			s[i] = s[i - 1];
		}

		s[0] = ' ';
		j++;
	}
	s[len + 1] = '\0';
}

void list (char r[1000][1000], int r_line, char t, char s, int st, int e) {
	int i, numar = 0;
	char litera = t;
	char string[100]; //pentru a retine numerele ca string-uri

	for (i = st; i <= e; i++) {
		leading_whitespace (r[i]);

		if (t == 'b') {
			adauga_caracter (r[i], ' ');
			adauga_caracter (r[i], s);
		} else if (t == 'n') {
			adauga_caracter (r[i], ' ');
			adauga_caracter (r[i], s);
			numar++;
			sprintf (string, "%d", numar);
			strcat (string, r[i]);
			strcpy (r[i], string);
		} else if (t == 'a' || t == 'A') {
			adauga_caracter (r[i], ' ');
			adauga_caracter (r[i], s);
			adauga_caracter (r[i], litera);
			litera++;
		}
	}

	for (i = 0; i < r_line; i++) {
		sterge_newline (r[i]);
		int len = strlen (r[i]);
		r[i][len] = '\n';
		r[i][len +  1] = '\0';
	}
}

void order_list (char r[1000][1000], int r_line, 
	char t, char s, char o, int st, int e) {
	int i, j, end;

	//ignora ultima linie a fisierului, care nu contine caractere
	if (e == r_line + 1) {
		end = e - 2;
	} else {
		end = e;
	}

	char aux[1000];
	int len;
	if (o == 'a') {

		for (i = st; i <= end; i++) {

			for (j = i + 1; j <= end; j++) {
					if (strcmp (r[i], r[j]) > 0) {
						strcpy (aux, r[i]);
						strcpy (r[i], r[j]);
						strcpy (r[j], aux);
					}
			}
		}

	} else if (o == 'z') {

		for (i = st; i <= end; i++) {
			if (e == r_line) {
					end = r_line;
				}

			for (j = i + 1; j <= end; j++) {
				if (strcmp (r[i], r[j]) < 0) {
					strcpy (aux, r[i]);
					strcpy (r[i], r[j]);
					strcpy (r[j], aux);
				}
			}
		}
	}

	for (i = st; i <= e; i++) {
		leading_whitespace (r[i]);
	}

	for (i = 0; i < r_line; i++) {
		sterge_newline (r[i]);
		len = strlen (r[i]);
		r[i][len] = '\n';
		r[i][len +  1] = '\0';
	}

	list (r, r_line, t, s, st, e);
}

int main(int argc, char *argv[]) {
	char buf[1000],
	original[1000][1000],
	result[1000][1000],
	copie[1000][1000]; 
	int original_line_count = 0,  // number of lines in the input file
	result_line_count = 0,    // number of lines in the output file
	copie_line = 0;
	int i, j, len, start_line, end_line, indent, lung_max, lung_fisier;
	int cate_comenzi = 0;

	if (argc != 4) {  // invalid number of arguments
		fprintf(stderr,
	   		"Usage: %s operations_string input_file output_file\n",
			argv[0]);
		return -1;
	}

	// Open input file for reading
	FILE *input_file = fopen(argv[2], "r");

	if (input_file == NULL) {
		fprintf(stderr, "File \"%s\" not found\n", argv[2]);
		return -2;
	}

	// Read data in file line by line
	while (fgets(buf, 1000, input_file)) {
		strcpy(original[original_line_count], buf);
		original_line_count++;
	}

	fclose(input_file);

	FILE *output_file = fopen(argv[3], "w");

	if (output_file == NULL) {
		fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
		return -2;
	}

	//face o copie a vectorului original
	for (i = 0; i < original_line_count; i++) {
		strcpy(copie[i],original[i]);
	}

	copie_line = original_line_count;

	char *comanda;
	char comenzi[1000][1000];
	int nr_comenzi, k;


	//pentru a verifica daca o comanda este separata de altceva decat virgula
	int poz = 0;
	for (i = 0; i < strlen (argv[1]); i++) {
		poz = i;
		if (argv[1][i] == 'W' || argv[1][i] == 'C' ||
			argv[1][i] == 'L' || argv[1][i] == 'R' ||
			argv[1][i] == 'J' || argv[1][i] == 'P' ||
			argv[1][i] == 'I' || argv[1][i] == 'O') {
				while (argv[1][i - 1] == ' ') {
					i -= 2;
				}

				if (argv[1][i] != ',' && i != 0) {
					copie_exacta (copie, result, copie_line, 
								&result_line_count);
					printf ("Invalid operation!\n");

					for (i = 0; i < result_line_count; i++) {
					fputs(result[i], output_file);
				}

				return -9;
				}
		}

		i = poz;
	}

	//imparte comenzile dupa virgula
	comanda = strtok (argv[1],",");

	while (comanda != NULL) {
		cate_comenzi++;
		if (cate_comenzi > 10) {
			puts(comanda);
			printf("Too many operations! Only the first 10 will be applied.\n");
			break;
		}

		//initializeaza vectorul cu un string vid
		//pentru a nu ramane caractere de la impartirea precedenta
		for (i = 0; i < nr_comenzi; i++) {
			strcpy (comenzi[i], "");
		}

		nr_comenzi = 0; k = 0;
		//sterge leading whitespace
		leading_whitespace (comanda);
		//transforma spatiile consecutive intr-unul singur
		sterge_spatii (comanda);

		//salveaza fiecare parametru al comenzii, ca string, in vectorul comenzi
		for (i = 0; i <= strlen(comanda); i++) {
			if (comanda[i] == ' ' || comanda[i] == '\0') {
				comenzi[nr_comenzi][k] = '\0';
				nr_comenzi++;
				k = 0;
			} else {
				comenzi[nr_comenzi][k] = comanda[i];
				k++;
			}
		}

		//executa operatiile pentru fiecare comandas
		if (strcmp(comenzi[0], "W") == 0 || strcmp(comenzi[0], "w") == 0) {
			lung_fisier = lungime_max_fisier (original, original_line_count);
			result_line_count = 0;

			//daca se da un parametru in plus la wrap
			if (atoi(comenzi[2]) != 0) {
				copie_exacta (copie, result, copie_line, &result_line_count);
				printf ("Invalid operation!\n");

				for (i = 0; i < result_line_count; i++) {
					fputs(result[i], output_file);
				}

				return -4;	
			}

			//daca cel mai lung cuvant e mai mare decat parametrul comenzii
			if (lung_fisier > atoi(comenzi[1])) {
				copie_exacta (copie, result, copie_line, &result_line_count);
				printf ("Cannot wrap!\n");

				for (i = 0; i < result_line_count; i++) {
					fputs(result[i], output_file);
				}

				return -3;
			}

			int i, lungMax;
			lungMax = atoi (comenzi[1]);

			for (i = 0; i < original_line_count; i++) {
				//salveaza in stringul s liniile din original
				//care se afla intre doua linii goale
				char *s = original[i];
				while (numai_spatii (original[i]) == 0) {
					i++;
					if (numai_spatii (original[i]) == 0 
						&& numai_spatii (original[i - 1]) == 0) {
							leading_whitespace (original[i]);
					}
					trailing_whitespace (s);
					strcat(strcat(s," "), original[i]);
				}

				//daca paragraful e mai mare decat parametrul comenzii wrap
				if (strlen (s) > lungMax) {
					//afla de cate ori poate fi impartit
					int impartiri = linie_impartita(s, lungMax);
					char *string;
					string = s;

					for (j = 0; j <= impartiri; j++) {
						if (j != 0) {
							//ignora liniile deja impartite
							string = string + poz_max (string, lungMax);
							leading_whitespace (string);
						}

						//la ultima impartire, retine ce a ramas neimpartit
						if (j == impartiri) {
							sstrcpy (result[result_line_count], string);
							len = strlen(result[result_line_count]);
							result[result_line_count][len]= '\n';
							result_line_count++;

						//in rest, imparte vectorul string
						} else {
							sstrcpy (result [result_line_count], 
									wrap(string, lungMax));
							len = strlen(result[result_line_count]);
							result[result_line_count][len]= '\n';
							result_line_count++;
						}
					}

				//daca paragraful e mai mic, se retine asa cum este
				//dar fara trailing whitespace
				} else if (strlen(s) < lungMax) {
					trailing_whitespace(s);
					strcat (s, "\n");
					strcpy (result[result_line_count], s);
					len = strlen(result[result_line_count]);
					result[result_line_count][len]= '\n';
					result[result_line_count][len + 1]= '\0';
					result_line_count++;
				}
			}

			sterge_newline (result[result_line_count - 1]);
			strcpy (result[result_line_count], "\n");
			result_line_count++;

			//actualizeaza vectorul original, pentru operatii ulterioare
			actualizare (original, result, 
						&original_line_count, result_line_count);


		} else if (strcmp(comenzi[0], "C") == 0 
				|| strcmp(comenzi[0], "c") == 0) {
			parametri_1(&start_line, &end_line, original_line_count, comenzi);

			//daca linia de inceput e negativa
			if (start_line < 0) {
				printf("Invalid operation!\n");
				copie_exacta (copie, result, copie_line, &result_line_count);

				for (i = 0; i < result_line_count; i++) {
					fputs(result[i], output_file);
				}

				return -3;  			
			}

			//daca linia de inceput e mai mare decat cea de final
			if (start_line > end_line) {
				printf("Invalid operation!\n");
				copie_exacta (copie, result, copie_line, &result_line_count);

				for (i = 0; i < result_line_count; i++) {
					fputs(result[i], output_file);
				}

				return -3;
			}

			copie_result (original, result, 
						original_line_count, &result_line_count);
			lung_max = max_strlen (original, original_line_count);

			for (i = start_line; i <= end_line; i++) {
					if (numai_spatii (result[i]) == 1) {
						continue;
					} else {
						center (result[i], lung_max);
						trailing_whitespace (result[i]);
						len = strlen(result [i]);
						result[i][len] = '\n';
						result[i][len + 1] = '\0';
					}
				}

			actualizare (original, result, 
						&original_line_count, result_line_count);

		} else if (strcmp(comenzi[0], "L") == 0 
				|| strcmp(comenzi[0], "l") == 0) {
			parametri_1(&start_line, &end_line, original_line_count, comenzi);

			if (atoi (comenzi[1]) < 0 || atoi (comenzi[2]) < 0) {
				printf("Invalid operation!\n");
				copie_exacta (copie, result, copie_line, &result_line_count);

			for (i = 0; i < result_line_count; i++) {
					fputs(result[i], output_file);
			}

			return -5;
		}

			copie_result (original, result, 
						original_line_count, &result_line_count);

			for (i = start_line; i <= end_line; i++) {
					if (numai_spatii (result[i]) == 1) {
						continue;
					} else {
						align_left (result[i]);
						trailing_whitespace (result[i]);
						sterge_newline (result[i]);
						len = strlen(result [i]);
						result[i][len] = '\n';
						result[i][len + 1] = '\0';
					}
			}

			actualizare (original, result, 
						&original_line_count, result_line_count);

		} else if (strcmp(comenzi[0], "R") == 0 
				|| strcmp(comenzi[0], "r") == 0) {
			parametri_1(&start_line, &end_line, original_line_count, comenzi);

			//daca se dau mai multi parametri functiei align right
			if (atoi(comenzi[4]) != 0) {
				printf("Invalid operation!\n");
				copie_exacta (copie, result, copie_line, &result_line_count);

				for (i = 0; i < result_line_count; i++) {
						fputs(result[i], output_file);
				}

				return -7;
			}
			copie_result (original, result, 
						original_line_count, &result_line_count);
			lung_max = max_strlen (original, original_line_count);

			for (i = start_line; i <= end_line; i++) {
				if (numai_spatii (result[i]) == 1) {
					continue;
				} else {
					align_right (result[i], lung_max);
					trailing_whitespace (result[i]);
					sterge_newline (result[i]);
					len = strlen(result [i]);
					result[i][len] = '\n';
					result[i][len + 1] = '\0';
				}
			}

			actualizare (original, result, 
							&original_line_count, result_line_count);

		} else if (strcmp(comenzi[0], "J") == 0 
				|| strcmp(comenzi[0], "j") == 0) {
			parametri_1(&start_line, &end_line, original_line_count, comenzi);
			copie_result (original, result, 
						original_line_count, &result_line_count);
			//lungimea maxima din fisier
			lung_max = max_strlen (original, original_line_count);

			for (i = start_line; i < end_line; i++) {

				if (numai_spatii (result[i]) == 0) {
					justify (result[i], lung_max);
				} else {
					strcpy (result[i - 1], original[i - 1]);
					align_left (result[i - 1]);
				}

				strcpy (result[end_line], original[end_line]);
				align_left (result[end_line]);
			}

		} else if (strcmp(comenzi[0], "P") == 0 
				|| strcmp(comenzi[0], "p") == 0) {

			parametri_2(&start_line, &end_line, 
						&indent, original_line_count, comenzi);
			//daca nu se specifica cu cat sa se indenteze
			if (atoi(comenzi[1]) == 0) {
				printf("Invalid operation!\n");
				copie_exacta (copie, result, copie_line, &result_line_count);

				for (i = 0; i < result_line_count; i++) {
						fputs(result[i], output_file);
				}	

				return -8;
			}

			copie_result (original, result, 
						original_line_count, &result_line_count);

			for (i = start_line; i <= end_line; i++) {
				if (numai_spatii(result[i]) == 0 
					&& numai_spatii (result [i - 1]) == 1) {
						paragraph (result[i], indent);
				}
			}

			actualizare (original, result, 
						&original_line_count, result_line_count);

		} else if (strcmp(comenzi[0], "I") == 0 
				|| strcmp(comenzi[0], "i") == 0) {

			parametri_3(&start_line, &end_line, original_line_count, comenzi);
			
			//dac se ofera un parametru invalid
			if (strcmp (comenzi[2],"") == 0 
				|| (strcmp(comenzi[1], "a") 
				&& strcmp(comenzi[1], "A") 
				&& strcmp(comenzi[1], "b") 
				&& strcmp(comenzi[1], "n"))) {

				printf("Invalid operation!\n");
				copie_exacta (copie, result, copie_line, &result_line_count);

				for (i = 0; i < result_line_count; i++) {
						fputs(result[i], output_file);
				}

				return -9;
			}

			copie_result (original, result, 
						original_line_count, &result_line_count);
			list (result, result_line_count, comenzi[1][0], 
				comenzi[2][0], start_line, end_line);

			for (i = 0; i < result_line_count; i++) {
				if (numai_spatii (result[i]) == 0) {
					sterge_tab (result[i]);
				}
			}

			actualizare (original, result, 
						&original_line_count, result_line_count);

		} else if (strcmp(comenzi[0], "O") == 0 
				|| strcmp(comenzi[0], "o") == 0) {

			parametri_4(&start_line, &end_line, original_line_count, comenzi);

			//daca se ofera un parametru invalid pentru ordonare
			if (comenzi[3][0] != 'a' && comenzi[3][0] != 'z') {
				printf("Invalid operation!\n");
				copie_exacta (copie, result, copie_line, &result_line_count);

				for (i = 0; i < result_line_count; i++) {
						fputs(result[i], output_file);
				}

				return -3;
			}

			copie_result (original, result, 
						original_line_count, &result_line_count);
			order_list (result, result_line_count, comenzi[1][0], 
						comenzi[2][0], comenzi[3][0], start_line, end_line);

			//sterge tab-urile
			for (i = 0; i < result_line_count; i++) {
				if (numai_spatii (result[i]) == 0) {
					sterge_tab (result[i]);
				}
			}

			actualizare (original, result, 
						&original_line_count, result_line_count);

		//daca nu se da nicio comanda valida

		} else {
			printf("Invalid operation!\n");
			copie_exacta (copie, result, copie_line, &result_line_count);

			for (i = 0; i < result_line_count; i++) {
				fputs(result[i], output_file);
			}

			return -3;
		}

		comanda = strtok (NULL, ",");
	}

	for (i = 0; i < result_line_count; i++) {
		fputs(result[i], output_file);
	}

	fclose(output_file);

	return 0;
}