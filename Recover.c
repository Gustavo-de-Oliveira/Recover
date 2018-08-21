#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){
	char nome[10];
	unsigned char cabecalho[3] = {0xff, 0xd8, 0xff}, imagem[512] = {0}, c;
	int flag = 0, k = 0;
	FILE* imagem_arq = NULL;

	while(fread(&c, 1, 1, stdin) > 0){
		imagem[0] = c;
		for(int i = 1; i < 3; ++i){
			fread(&imagem[i], 1, 1, stdin);
		}

		if(imagem[0] == cabecalho[0] && imagem[1] == cabecalho[1] && imagem[2] == cabecalho[2]){
			if(imagem_arq != NULL) fclose(imagem_arq);
			sprintf(nome, "%03d", k);
			strcat(nome, ".jpg");
			imagem_arq = fopen(nome, "wb");
			k++;
		}

		for(int i = 3; i < 512; ++i){
			fread(&imagem[i], 1, 1, stdin);
		}
		if(imagem_arq != NULL)fwrite(imagem, 1, 512, imagem_arq);
	}
	if(k == 0) printf("Could not find pictures\n");
	return 0;
}