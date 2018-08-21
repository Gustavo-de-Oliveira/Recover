/*
	Programa que irá recuperar imagens no formato JPEG de cartões de memória no formato FAT.
	Trabalho 1 - ICC2
	Gustavo de Oliveira Silva - ICMC/USP	
	22/08/2018
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){
	char nome[8];
	//nome: Armazena o nome do arquivo JPG recuperado
	unsigned char  imagem[512] = {0}, c;
	//imagem: Guarda um bloco de 512 bytes da imagem a ser recuperada
	//c: Verifica se esta no final do arquivo
	int k = 0;
	//k: Usado para contar o número de imagens recuperadas
	FILE* imagem_arq = NULL;
	//imagem_arq: guarda o endereço do arquivo jpg criado

	while(fread(&c, 1, 1, stdin) > 0){//Enquanto o número de bytes lidos for diferente de 0 continua no loop, caso contrário acabou o arquivo
		imagem[0] = c;//Recebe o primeiro byte já lido
		for(int i = 1; i < 3; ++i){
			fread(&imagem[i], 1, 1, stdin);//Lê os pŕoximos 2 bytes
		}

		if(imagem[0] == 0xff && imagem[1] == 0xd8 && imagem[2] == 0xff){//Se os três bytes lidos forem iguais aos de um cabeçalho de jpg
			if(imagem_arq != NULL) fclose(imagem_arq);//Se houver algum arquivo aberto o fechamos
			sprintf(nome, "%03d", k);
			strcat(nome, ".jpg");
			imagem_arq = fopen(nome, "wb");
			k++;
			//Cria um arquivo no formato 000.jpg, mantém ele aberto e incrementa k
		}

		for(int i = 3; i < 512; ++i){//Lê o resto do bloco de 512 bytes, ou seja, os próximos 509 bytes
			fread(&imagem[i], 1, 1, stdin);
		}
		if(imagem_arq != NULL)fwrite(imagem, 1, 512, imagem_arq);//Se houver algum arquivo aberto escreve o bloco no arquivo
	}
	if(k == 0) printf("Could not find pictures\n");//Se k = 0 não houveram imagens a serem recuperadas
	return 0;
}