#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
//=================================================
char nome[20][100];
char senha[20][100];
char op,op2;
int totuser = 0;
//=================================================
void menu();
void inserir();
void alterar();
void excluir();
void listar(int tp);
void creditos();
void classifica();
bool senhaValida(char s[]);
void cripto(char s[]);
int buscaUsuario(char chave[]);
void arquivo(int tp);
void gerenciar();
//=================================================
int main(){
	setlocale(LC_ALL, "portuguese");
	arquivo(0);
	classifica();
	menu();
	return 0;
}
//=================================================
void gerenciar() {
    char usuario[] = "grupoaep", usu2[100];
    char senha[] = "1234", sen2[50];
    char op2;
 
    system("cls");
    printf("|           GERENCIAR           |\n");
    printf("|-------------------------------|\n");
    do{
        printf(" >> Usuario ADM: ");
        fgets(usu2, sizeof(usu2), stdin);
        usu2[strcspn(usu2, "\n")] = '\0';
        	
        if (strcmp(usu2, usuario) != 0) {
        	printf("!! Usuario Invalido !!\n");
        	getch();
        }
        	
	} while (strcmp(usu2, usuario) != 0);

	do{
		printf("Senha: ");
        fgets(sen2, sizeof(sen2), stdin);
        sen2[strcspn(sen2, "\n")] = '\0';

    	if (strcmp(sen2, senha) != 0) {
        	printf("!! Senha incorreta !!\n");
        	getch();
    	}
    		
    } while (strcmp(sen2, senha) != 0);
    	
		
    do {
    	system("cls");
    	printf("|           GERENCIAR           |\n");
        printf("|-------------------------------|\n");
        printf("| (1) Usuarios criptografado    |\n");
        printf("| (2) Usuarios descriptografado |\n");
        printf("| (3) Voltar para Menu          |\n");
        op2 = getch();

        switch(op2){
        case '1':	
        	listar(0);
        	break;
        
        case '2':	
        	listar(1);
        	break;
        
        case '3':
        	menu();	
        	break;
        
        default:
        	printf(" Opção inválida! Tente novamente.\n");
        	getch();
        
        }
    }while(op2 != '3');
    
}
//=================================================

void menu(){
	
    do{
        system("cls");
        printf("|    M E N U    |\n");
        printf("|---------------|\n");
        printf("| (1) Inserir   |\n");
        printf("| (2) Alterar   |\n");
        printf("| (3) Excluir   |\n");
        printf("| (4) Listar    |\n");
        printf("| (5) Créditos  |\n");
        printf("| (6) Gerenciar |\n"); 
        printf("| (7) Fim       |\n");
        printf("|_______________|\n");
        
        printf("\n");
        
        op = getch();

        switch (op){
        case '1':
        	inserir();
            break;
    
        case '2':
            alterar();
            break;

        case '3':
            excluir(); 
            break;

        case '4':
            listar(2);//Mostra somente os usuarios
            break;

        case '5': 
            creditos();
            break;

         case '6': //Mostra usuarios e senhas descriptografados
        	gerenciar();
        	break;

        case '7':
            printf("\nSaindo... Ate logo!\n");
            
		}
    } while (op != '7');
}
//=================================================
void inserir(){
	char confirma_senha[100], sel = 0, s;
	bool senha_valida, espaco;
	int p, tam, i;
	
	while (sel < 1){
		
		if (totuser == 20){
			system("cls");
			printf("O limite de usuários foi atingido!\n");
			printf("\nPressione qualquer tecla para voltar ao menu...");
			getch();
			return;
		}else {
			do{
				do{
					system("cls");
        			printf("|   INSERIR   |\n");
        			printf("|-------------|\n");
        			espaco = false;
        			printf("<< Usuario: ");
        			fgets(nome[totuser], sizeof(nome[totuser]), stdin);
        			nome[totuser][strcspn(nome[totuser], "\n")] = '\0'; 
        			tam = strlen(nome[totuser]);
        	
        			for (i = 0;  i < tam; i++){
        				if (nome[totuser][i] == ' '){
        					espaco = true;
						}
					}
			
					if (espaco){
						printf("Não é permitido espaço no nome\n");
						getch();
					}	
				} while(espaco); 
			
				p = buscaUsuario(nome[totuser]);
		
				if (p != -1){
					printf("Usuário já cadastrado!\n");
					getch();
				}
			} while (p != -1 || strlen(nome[totuser]) <= 3 || strlen(nome[totuser]) >= 12);
	
			do{
				printf("<< Senha: ");
				fgets(senha[totuser], sizeof(senha[totuser]), stdin);
        		senha[totuser][strcspn(senha[totuser], "\n")] = '\0'; 
		
				senha_valida = senhaValida(senha[totuser]);
        		if (!senha_valida) {
            		printf("\n!! Senha inválida !!\n>> Use entre 8 e 12 caracteres, com uma letra maiúscula, uma minúscula, um número e um símbolo especial.\n\n");
        			getch();
				}	
			} while (!senha_valida);
	
			do{
				printf("<< Confirme a senha: ");
        		fgets(confirma_senha, sizeof(confirma_senha), stdin);
        		confirma_senha[strcspn(confirma_senha, "\n")] = '\0'; 

        		if (strcmp(senha[totuser], confirma_senha) != 0) {
            		printf("\n!! As senhas não coincidem !! \n>> Por favor, verifique e tente novamente.\n\n");
       	 			getch();
				}
			} while (strcmp(senha[totuser], confirma_senha) != 0);
	
			totuser++;
			arquivo(1);
			classifica();
			printf("\n!! Usuário cadastrado com sucesso !! \n<< Teclar Espaço para continuar / Enter para voltar ao Menu >>\n");
			s = getch();
	
			if (s != ' '){
				sel = 1;
			}
		}
	}
}
//=================================================
void alterar(){
	char csenha[100], usuario[100], s;
	bool vsenha;
	int p;
	
	system("cls");
    printf("|              ALTERAR             |\n");
    printf("|----------------------------------|\n");
    printf("|Tecle ESPAÇO para Exibir Lista	   |\n");
    printf("|Tecle ENTER para Continuar    	   |\n");
    printf("|Tecle ESC para Voltar para o Menu |\n");
    printf("|----------------------------------|\n");
    s = getch();
    
	switch (s){
		case 32: 
			listar(2);
			alterar();
			break;
			
		case 13: 
			do{
				system("cls");
        		printf("|           ALTERAR            |\n");
        		printf("|------------------------------|\n");
				printf("<< Usuario: ");
				fgets(usuario, sizeof(usuario), stdin);
				usuario[strcspn(usuario, "\n")] = '\0';
				p = buscaUsuario(usuario);
		
				if (p == -1){
					printf("!! Usuário Inválido !!");
					getch();
				
				}
			} while (p == -1);
	
			do{
				printf("<< Insira a nova senha: ");
				fgets(senha[p], sizeof(senha[p]), stdin);
				senha[p][strcspn(senha[p], "\n")] = '\0';

        		vsenha = senhaValida(senha[p]);
        		if (!vsenha) {
            	printf("!! Senha inválida !! \n-Use entre 8 e 12 caracteres, letra maiúscula, no mínimo uma minúscula, números e um símbolo especial\n");
        		}
			} while (!vsenha);
	
			do{
				printf("Confirme a senha: ");
				fgets(csenha, sizeof(csenha), stdin);
				csenha[strcspn(csenha, "\n")] = '\0';
				if (strcmp(senha[p], csenha) != 0) {
        			printf("\n!! As senhas não coincidem !! \n>> Por favor, verifique e tente novamente.\n\n");
       			}
			} while (strcmp(senha[p], csenha) != 0);
	
			arquivo(1);
			printf("Senha alterada com sucesso!\n");
			getch();
			break;
			
		case 27:
			menu();
			break;
		
		default: 
			printf("\n");
        	printf("!! Opção inválida !! \n");
        	printf(">> Tecle novamente << \n");
        	getch();	
			alterar();
			
	}    

}
//=================================================
void excluir(){
	char parada, usuario[100], s, confirm;
	int x, p;
	
	system("cls");
    printf("|               EXCLUIR            |\n");
    printf("|----------------------------------|\n");
	printf("|Tecle ESPACO para Exibir Lista    |\n");
    printf("|Tecle ENTER para Continuar    	   |\n");
    printf("|Tecle ESC para Voltar para o Menu |\n");
    printf("|----------------------------------|\n");
    s = getch();
    
    switch (s)
	{
    case 32:
		listar(2);
		excluir();
		break; 
		
	case 13:
		do{
			system("cls");
			printf("|               EXCLUIR            |\n");
    		printf("|----------------------------------|\n");
			printf("Nome do Usuário: ");
			fgets(usuario, sizeof(usuario), stdin);
			usuario[strcspn(usuario, "\n")] = '\0';
			p = buscaUsuario(usuario);
		
			if (p == -1){
				printf("!! Usuário Inválido !!");
				getch();
			}
		} while (p == -1);
	
		printf("Você tem certeza que deseja excluir o usuário %s? (S/N): ", usuario);
    	confirm = getch();
	
		if (confirm == 'S' || confirm == 's'){
			for (x = p; x < totuser - 1; x++){
				strcpy(nome[x], nome[x + 1]);
				strcpy(senha[x], senha[x + 1]);
			}
			totuser--;
			arquivo(1);
			printf("\n!! Usuário excluído com sucesso !!\n");
		}else {
			printf("\nExclusão cancelada.\n");
		}
		getch();
		break;
		
	case 27: 
		menu();
		break;
		
	default: 
		printf("\n");
        printf("!! Opção inválida !! \n");
        printf(">> Tecle novamente << \n");
        getch();	
		alterar();
		
	}
	
}
//=================================================
void listar(int tp){
	int x;
	char nomeTemp[100];
	char senhaTemp[100];
		
	system("cls");
	
	if (totuser < 1){
		printf("!! Não há usuários cadastrados !!");
		getch();
	}else {
		printf("---------------------------------------------------------\n");
		printf("%-25s %-25s\n", "Usuário", "Senha");
		printf("---------------------------------------------------------\n");
	
		for (x = 0; x < totuser; x++){
		
			char s[] = "*******";
		
			strcpy(nomeTemp, nome[x]);
			strcpy(senhaTemp, senha[x]);
		
		
			switch (tp)
			{
			case 0: 
				cripto(nomeTemp);
				cripto(senhaTemp);
				printf("%-25s %-25s\n", nomeTemp, senhaTemp);
				break;
			
			case 1:
				printf("%-25s %-25s\n", nome[x], senha[x]);
				break;
			
			case 2: 
				printf("%-25s %-25s\n", nome[x], s);
				break;
			
			}
		}
		printf("---------------------------------------------------------\n");
		printf("<< Tecle qualquer tecla para sair >>\n");
		getch();	
	}
	
}
//=================================================
void creditos(){
	
	system("cls");
    printf("------------------------------------------------------------\n");
    printf("|                                                          |\n");
    printf("|             PROJETO AEP - GERENCIADOR DE CONTAS          |\n");
    printf("|                                                          |\n");
    printf("------------------------------------------------------------\n\n");

    printf("Este programa foi desenvolvido como Projeto AEP \n");
    printf("Curso: Engenharia de Software - ESOFT2-SA.\n");
    printf("\n");
    printf("Participantes:\n");
    printf("- Gustavo Beneton - RA: 24053841-2\n");
    printf("- Bruno Fujisaki  - RA: 24094977-2\n");
    printf("- Eric Leite 	  - RA: 24023654-2\n");
    printf("- Lucas Vinicius  - RA: 24034814-2\n");
    printf("\n");
    printf("Objetivo:\n");
    printf("\n");
    printf("Este sistema foi criado para facilitar a gestão de contas, \n");
    printf("permitindo a inserção, alteração, listagem e exclusão de \n");
    printf("contas com segurança e criptografia de senhas, garantindo \n");
    printf("a proteção de informações sensíveis.\n");
    printf("\n");
    printf("------------------------------------------------------------\n");
    printf("|            Obrigado por utilizar nosso programa!         |\n");
    printf("|                                                          |\n");
    printf("|         Pressione qualquer tecla para continuar...       |\n");
    printf("------------------------------------------------------------\n");
    getch();
    
}
//=================================================
void classifica() { //selection sort
	int i, j;
    for (i = 0; i < totuser - 1; i++) {
        for (j = i + 1; j < totuser; j++) {
            if (strcmp(nome[i], nome[j]) > 0) {
                char temp_nome[50];
                char temp_senha[50];
                
                strcpy(temp_nome, nome[i]);
                strcpy(nome[i], nome[j]);
                strcpy(nome[j], temp_nome);
                
                strcpy(temp_senha, senha[i]);
                strcpy(senha[i], senha[j]);
                strcpy(senha[j], temp_senha);
            }
        }
    }
}
//=================================================
int buscaUsuario(char chave[]){
	int x;
	
	
	for (x = 0; x < totuser; x++){
		if (strcmp(chave, nome[x]) == 0){
			return x;
		}
	}	
	
	return -1;
}
//=================================================
bool senhaValida(char s[]){
	bool v1 = 0, v2 = 0, v3 = 0, v4 = 0;
    int i;
    
    if (strlen(s) < 8 || strlen(s) > 12){
        return 0;
    }else {
        for (i = 0; i < strlen(s); i++)
        {
            if (s[i] >= 65 && s[i] <= 90){
                v1 = 1; //verifica se tem maiuscula
            }else if (s[i] >= 97 && s[i] <= 122)
            {
                v2 = 1; //verifica se tem minuscula
            }else if (s[i] >= 48 && s[i] <= 57)
            {
                v3 = 1; //verifica se tem numero
            }else if ((s[i] >= 33 && s[i] <= 47) || (s[i] >= 58 && s[i] <= 64) || (s[i] >= 91 && s[i] <= 96) || (s[i] >= 123 && s[i] <= 126))
            {
                v4 = 1; //verifica se tem  especial
            }
        }

        if (v1 && v2 && v3 && v4){
            return 1;
        }else return 0;
    }
}
//=================================================
void cripto(char s[]){
	
	int i, x, aux, fim;
	int tam = strlen(s);
    char c;
    
    for (x = 0; x < strlen(s); x++){
        c = s[x];
        i = (int)c;
        c = (char)(i + x + 8);
        s[x] = c;
    } //soma o valor asc do caractere com a posicao de x + 8
    
    fim = tam - 1;
    for (i = 0; i < tam/2; i++){
    	aux = s[i];
    	s[i] = s[fim];
    	s[fim] = aux;
    	fim--;
	} //inverte a string
    
}
//=================================================
void descripto(char s[]){
	
	int i, x, aux, fim;
	int tam = strlen(s);
    char c;
    
    fim = tam - 1;
    for (i = 0; i < tam/2; i++){
    	aux = s[i];
    	s[i] = s[fim];
    	s[fim] = aux;
    	fim--;
	} 
    
    for (x = 0; x < strlen(s); x++){
        c = s[x];
        i = (int)c;
        c = (char)(i - x - 8);
        s[x] = c;
    }

}
//=================================================
void arquivo(int tp){ //0 - leitura / 1 - gravacao
  char linha[15], tmp[15]; 
  int x;
  FILE *file;

    file = fopen("NomeArq.txt", "r"); //abre o arquivo para leitura
    if (file != NULL && tp == 0) { 
        totuser = 0;
        x = 0;
        
        while (fgets(linha, sizeof(linha), file) != NULL) { 
          linha[strlen(linha)-1]='\0';  //remove o '\n' ao final da linha, se houver
          descripto(linha);

          if (x % 2 == 0) { //linhas pares: nome
              strcpy(nome[totuser], linha);
          } else {           //linhas ímpares: senha
              strcpy(senha[totuser], linha);
              totuser++;
          }
          x++;
        }
        fclose(file);
    } else { //modo de gravação
    file = fopen("NomeArq.txt", "w"); //abre o arquivo para gravação
    if (file != NULL) {
        for (x = 0; x < totuser; x++) { 
          strcpy(tmp, nome[x]); //copia o nome[x] em tmp
          cripto(tmp);
          fprintf(file, "%s\n", tmp);

          strcpy(tmp, senha[x]); //copia a senha[x] em tmp 
          cripto(tmp);
          fprintf(file, "%s\n", tmp);
        }
        fclose(file); 
    }
  }
}

