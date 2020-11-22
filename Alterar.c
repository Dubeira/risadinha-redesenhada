#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>                                                 /*permite usar palavras acentuadas;*/
#include <string.h>

typedef struct{                                                     /*define uma struct com os campos:*/
	char nome[8];                                                   /*nome: Onde fica o nome lido;*/
	int num;                                                        /*num: Onde fica o n�mero lido;*/
}NOME;
NOME nome[24];                                                      /*define um vetor do tipo da struct;*/


void escolha();

int main(){
	setlocale(LC_ALL,"portuguese");                                 /*define a L�ngua de acentua��o;*/

	printf("TROCAR NOMES\n\n");

	char nome_antigo[8],nome_actual[8];
	int n,m=1,ind,o;                                                /*ind: Guardara a posi��o do vetor*/

	FILE*f=fopen("alterar.txt","rb");                               /*abre um Arquivo em leitura Bin�ria;*/
    for(n=0;n<24;n++,m++){
    	fread(&nome[n],sizeof(NOME),1,f);                           /*l� os dados do Arquivo para o vetor;*/
    	if(n<9){                                                    /*d� uma apar�ncia mais suave ao programa*/
    		printf("[0%d]",nome[n].num);                            /*se o numero do nome for menor que 10...*/
    		printf("-%s\n",nome[n].nome);                           /*...acrescentasse um 0 antes dele;*/
		}
    	else{                                                       /*sen�o, escreve-se o numero tal como ele �;*/
    		printf("[%d]",nome[n].num);
        	printf("-%s\n",nome[n].nome);
		}
		fseek(f,m*sizeof(NOME),SEEK_SET);                           /*pula "m" apartir do inicio do Arquivo;*/
	}
	fclose(f);                                                      /*fecha o Arquivo em modo Leitura Bin�ria*/
	puts("\nPOSIÇÃO:");
	scanf("%d",&m);                                                 /*L� para m a posi��o desejada no vetor;*/
	ind=m;                                                          /*"ind" recebe uma c�pia do valor de "m";*/
	m--;                                                            /*diminui um valor a "m", suavisa a escrita;*/
	system("cls");                                                  /*limpa o ecr� do painel de comandos;*/

	if(m>=0&&m<24){                                                 /*trabalha apenas com posi��es existentes;*/
		strcpy(nome_antigo,nome[m].nome);                           /*copia o nome do vetor struct para outro vetor;*/

		fflush(stdin);                                              /*Esvazia o Buffer, diminui os problemas;*/
		puts("NOVO NOME:");
		gets(nome[m].nome);
		nome[m].nome[7]='\n';                                       /*coloca o car�cter '\n' antes do '\0';*/
		nome[m].num=ind;                                            /*recebe c�pia do valor de "n" para num;*/

        strcpy(nome_actual,nome[m].nome);
	}
    else{
    	fflush(stdin);
    	main();                                                     /*chama a fun��o "main" se n�o cumprir o "if";*/
	}

    FILE*fn=fopen("alterar.txt","wb");                              /*abre o Arquivo em Escrita Bin�ria;*/

	   	for(n=0;n<24;n++)
		fwrite(&nome[n],sizeof(NOME),1,fn);                         /*Guarda os elementos do vetor um a um no Arquivo;*/
    	fclose(fn);

	    system("cls");

	    printf("Nome Antigo: %s\n",nome_antigo);
	    printf("Nome Actual: %s\n\n",nome_actual);

	    FILE*fs=fopen("alterar.txt","rb");
		m=1;

    for(n=0;n<24;n++){
    	fread(nome[n].nome,sizeof(NOME),1,fs);
    	if(n<9){
    	printf("[0%d]",nome[n].num);
    	printf("-%s",nome[n].nome);
    		if(nome[n].num==ind){                                   /*se o "num" em "n" for igual ao "ind":*/
    		printf("  <<<<<<\n");                                   /*"ind"ica o novo nome na posi��o selecionada;*/
			}
			else
    	    putchar('\n');
		}
    	else{
    		printf("[%d]",nome[n].num);
    		printf("-%s",nome[n].nome);
    		if(nome[n].num==ind){
    		printf("  <<<<<<\n");
			}
			else
    	    putchar('\n');
		}
		fseek(f,m*sizeof(NOME),SEEK_SET);
		m++;
	}
	fclose(fs);

	putchar('\n');
	system("pause");                                               /*pausa o programa at� ser clicada qualquer tecla;*/

	escolha();
	return 4000000;
}
void escolha(){
	fflush(stdin);

	char r;
	system("cls");
	printf("Deseja Continuar(?)");
	printf("\n[s]-SIM");
	printf("\n[n]-N�O\n");
	printf("\nR.: ");

	scanf("%c",&r);

	r=tolower(r);                                                /*torna a letra selecionada em min�scula;*/

	if(r=='s'){
		system("cls");
		main();
	}
    else if(r=='n'){
    	system("cls");
    	printf("\a\t\t\t\t\t\t\tPROGRAMA TERMINADO\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    	exit(1);                                                 /*ordena o encerramento imediato do programa;*/
	}
	else
	escolha();
}
