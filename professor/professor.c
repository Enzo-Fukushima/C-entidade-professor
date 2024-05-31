#include <stdio.h>
#include <string.h> // manipula��o de string
#include <stdlib.h> // limpar terminal e pausa no sistema

//fun��o para pausar o programa
void pausar(){
	printf("Pressione qualquer tecla para continuar...");
	getchar();
}

//fun��o para exibir a ajuda
void exibir_ajuda() {
    printf("\n**************************************\n");
    printf("Ajuda do Programa:\n");
    printf("1 - Definir avaliacoes: Permite definir os criterios de avaliacao.\n");
    printf("	1.1 - Avalia��es: Define a quantida de avalia��es que desejar.\n");
    printf("	1.2 - Peso*: Escolha o peso que deseja para as avaliacoes.\n");
    printf("	*Obs.: Por padrao os pesos sao definidos como 1.\n");
    printf("2 - Atribuir notas: Permite atribuir notas aos alunos.\n");
    printf("3 - Realizar chamada: Permite fazer a chamada dos alunos.\n");
    printf("4 - Fechamento da materia: Permite realizar o fechamento da materia.\n");
    printf("5 - Sair: Encerra o programa.\n");
    printf("A qualquer momento, digite '/ajuda' para exibir esta mensagem.\n");
	printf("**************************************\n");
	pausar();
}

void definir_avaliacoes(){
	//abre o arquivo de avalia��es
	FILE *file = fopen("avaliacoes.txt", "r+");
	if(!file){
		//se o arquivo n�o existir, entra na condicionar
		//e cria o arquivo
		file = fopen("avaliacoes.txt", "w+");
		if(!file){
			//caso n�o abra o arquivo
			//avisa ao usu�rio
			printf("Erro ao abrir o arquivo!");
			pausar();
			return;
		}
	}
	//posiciona o ponteiro em um posi��o espec�fica
	//nesse caso posiciona no final do arquivo
	fseek(file, 0, SEEK_END);
	
	//define a vari�vel 'file_size' e atribui
	//o tamanho do arquivo para ela com a fun��o
	//ftell()
	long file_size = ftell(file);
	
	//confere se o arquivo est� vazio
	//se estiver vazio entra no loop
	if(file_size == 0){
		int num_avaliacoes;
        char definir_pesos;
        char entrada[100];
        
		//enquanto o usu�rio digitar '/ajuda' ou uma entrada
		//inv�lida, o loop continua    
        while (1) {
            printf("Defina o numero de avaliacoes: ");
            //fun��o para pegar a entrada do usu�rio
            fgets(entrada, sizeof(entrada), stdin);
            //substitui o "\n" por um caracter nulo "\0"
            entrada[strcspn(entrada, "\n")] = 0;
			
			//compara a entrada com '/ajuda' se for igual exibe
			// a fun��o ajuda
            if (strcmp(entrada, "/ajuda") == 0) {
                exibir_ajuda();
                continue;
            }
			
			//converte a entrada em inteiro
            num_avaliacoes = atoi(entrada);
            if (num_avaliacoes > 0) break;
			
			//se o numero de avalia��o for in�lido ou <= a zero 
			//exibe mensagem de erro
            printf("Entrada inv�lida. Tente novamente.\n");
        }

		//enquanto o usu�rio digitar '/ajuda' ou uma entrada
		//inv�lida, o loop continua
        while (1) {
            printf("Deseja definir pesos para as avaliacoes? (S/N): ");
            //fun��o para pegar a entrada do usu�rio
            //3 par�metros: vari�vel de entrada, tamanho e m�todo
			fgets(entrada, sizeof(entrada), stdin);
            //substitui o "\n" por um caracter nulo "\0"
			entrada[strcspn(entrada, "\n")] = 0;

			//compara a entrada com '/ajuda' se for igual exibe
			// a fun��o ajuda
            if (strcmp(entrada, "/ajuda") == 0) {
                exibir_ajuda();
                continue;
            }
			
			//verifica se o usu�rio deseja definir peso ou n�o
			//definir peso assumi "s";"S";"n" ou "N"
            definir_pesos = entrada[0];
            if (definir_pesos == 'S' || definir_pesos == 's' || definir_pesos == 'N' || definir_pesos == 'n') break;

            printf("Entrada inv�lida. Tente novamente.\n");
        }
 
        //come�a a escrever no arquivo
        fprintf(file, "%d\n", num_avaliacoes);
        //entra no loop para escrever as avalia��es e pesos no arquivo
        for (int i = 1; i <= num_avaliacoes; i++) {
        	//se o usu�rio escolheu definir peso, entra no na condi��o
            if (definir_pesos == 'S' || definir_pesos == 's') {
                float peso;

                while (1) {
                    printf("Defina o peso da avaliacao %d: ", i);
                    //fun��o para pegar a entrada do usu�rio
            		//3 par�metros: vari�vel de entrada, tamanho e m�todo
					fgets(entrada, sizeof(entrada), stdin);
                    //substitui o "\n" por um caracter nulo "\0"
					entrada[strcspn(entrada, "\n")] = 0;

					//compara a entrada com '/ajuda' se for igual exibe
					//a fun��o ajuda
                    if (strcmp(entrada, "/ajuda") == 0) {
                        exibir_ajuda();
                        continue;
                    }
					
					//converte a entrada em inteiro
                    peso = atof(entrada);
                    if (peso > 0) break;

                    printf("Entrada inv�lida. Tente novamente.\n");
                }
				//exibe/grava as avali��es com os pesos definidos pelo usu�rio
                fprintf(file, "Avaliacao %d: %.2f\n", i, peso);
            } else {
            	//exibe/grava as avalia��es com peso padr�o = 1
                fprintf(file, "Avaliacao %d: 1\n", i); // Peso padr�o 1
            }
        }
        printf("Avaliacoes definidas com sucesso!\n");
	}else{
		// Arquivo n�o est� vazio, exibir e perguntar se deseja alterar
        //volta o ponteiro para o in�cio do arquivo
		rewind(file);
        char linha[100];
        //exibe as avalia��es e pesos existentes no arquivo
        printf("Avaliacoes definidas:\n");
        //cria o loop para exibir todas as avalia��es e pesos nos arquivo
        while (fgets(linha, sizeof(linha), file)) {
            printf("%s", linha);
        }
        
        char alterar;
        
        //pergunta se o usu�rio deseja alterar os dados existentes
		while (1) {
            printf("Deseja alterar as avaliacoes? (S/N): ");
            //fun��o para pegar a entrada do usu�rio
            //3 par�metros: vari�vel de entrada, tamanho e m�todo
			fgets(linha, sizeof(linha), stdin);
            //substitui o "\n" por um caracter nulo "\0"
			linha[strcspn(linha, "\n")] = 0;

			//compara a entrada com '/ajuda' se for igual exibe
			//a fun��o ajuda
            if (strcmp(linha, "/ajuda") == 0) {
                exibir_ajuda();
                continue;
            }

            alterar = linha[0];
            if (alterar == 'S' || alterar == 's' || alterar == 'N' || alterar == 'n') break;

            printf("Entrada inv�lida. Tente novamente.\n");
        }

        if (alterar == 'S' || alterar == 's') {
            freopen("avaliacoes.txt", "w+", file);
            int num_avaliacoes;
            char definir_pesos;
            char entrada[100];

            while (1) {
                printf("Defina o numero de avaliacoes: ");
                fgets(entrada, sizeof(entrada), stdin);
                entrada[strcspn(entrada, "\n")] = 0;

                if (strcmp(entrada, "/ajuda") == 0) {
                    exibir_ajuda();
                    continue;
                }

                num_avaliacoes = atoi(entrada);
                if (num_avaliacoes > 0) break;

                printf("Entrada inv�lida. Tente novamente.\n");
            }

            while (1) {
                printf("Deseja definir pesos para as avaliacoes? (S/N): ");
                fgets(entrada, sizeof(entrada), stdin);
                entrada[strcspn(entrada, "\n")] = 0;

                if (strcmp(entrada, "/ajuda") == 0) {
                    exibir_ajuda();
                    continue;
                }

                definir_pesos = entrada[0];
                if (definir_pesos == 'S' || definir_pesos == 's' || definir_pesos == 'N' || definir_pesos == 'n') break;

                printf("Entrada inv�lida. Tente novamente.\n");
            }

            fprintf(file, "%d\n", num_avaliacoes);
            for (int i = 1; i <= num_avaliacoes; i++) {
                if (definir_pesos == 'S' || definir_pesos == 's') {
                    float peso;

                    while (1) {
                        printf("Defina o peso da avaliacao %d: ", i);
                        fgets(entrada, sizeof(entrada), stdin);
                        entrada[strcspn(entrada, "\n")] = 0;

                        if (strcmp(entrada, "/ajuda") == 0) {
                            exibir_ajuda();
                            continue;
                        }

                        peso = atof(entrada);
                        if (peso > 0) break;

                        printf("Entrada inv�lida. Tente novamente.\n");
                    }

                    fprintf(file, "Avaliacao %d: %.2f\n", i, peso);
                } else {
                    fprintf(file, "Avaliacao %d: 1\n", i); // Peso padr�o 1
                }
            }
            printf("Avaliacoes redefinidas com sucesso!\n");
        } else {
            printf("Manter as avaliacoes atuais.\n");
        }
    }

    fclose(file);
    pausar();
}

int main(){
	int opcao;
	int sair;
	char confirmacao;
	char entrada[10];
	sair = 0;
	
	printf("**************************************");
	printf("\nCase precise de ajuda digite: /ajuda");
	printf("\n**************************************");
	printf("\n");
	
	printf("\nBem vindo {Professor}.\nO que deseja fazer hoje?");
	
	do{
		printf("\n1 - Definir avaliacoes\n2 - Atribuir notas\n3 - Realizar chamada\n4 - Fechamento da materia\n5 - Sair");
		printf("\nEntre com a opcao desejada ou digite /ajuda:");
		
		fgets(entrada,sizeof(entrada),stdin);//Le a entrada, nesse caso, entrada do teclado
		//fgets(array a ser 'lido',tamanho do array, fluxo da onde vem a entrada(teclado))
		
		//procura o caractere de nova linha "\n"
		//ao achar, retorna o indice da 1� ocorr�ncia
		//'= 0' substitui por caractere nulo '\0'
		//removendo o caractere de nova linha do fgets()
		entrada[strcspn(entrada, "\n")] = 0;
		
		//strcmp compara duas strings
		//no caso a entrada com '/ajuda'
		//a fun��o retorna 3 possibilidade
		//0 se forem iguais
		//< 0 se entrada menor que '/ajuda'
		//> 0 se entrada maior que '/ajuda'
		if (strcmp(entrada, "/ajuda") == 0) {
    		//se for 0 exibe a ajuda
			exibir_ajuda();
    		continue;
		}
		
		//fun��o atoi() converte uma string em um inteiro
		//converte entrada em inteiro
		opcao = atoi(entrada);
		
		switch (opcao){
			default:
				printf("Opcao invalida, tente novamente!\n");
				pausar();
				system("cls");
				break;
			case 1:
				printf("Avaliacoes\n");
				definir_avaliacoes();
				system("cls");
				break;
			case 2:
				printf("Notas\n");
				pausar();
				system("cls");
				break;
			case 3:
				printf("Chamada\n");
				pausar();
				system("cls");
				break;
			case 4:
				printf("Fechamento\n");
				pausar();
				system("cls");
				break;
			case 5:
				printf("Deseja realmente sair? (S/N): ");
				scanf(" %c", &confirmacao);
				fflush(stdin);
				if (confirmacao == 'S' || confirmacao == 's') {
					printf("Saindo...\n");
					sair = 1;
				} else {
					system("cls");
				}
				break;
		}
	}while(sair == 0);
	
}
