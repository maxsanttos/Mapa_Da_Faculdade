#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#define MAX 100
char dados[400];
typedef struct cadastro{
    int tipo,caixa;
    char titulo[50];
    char autor[30];
    char editora[50];
    int ano,quantidade,isbn,edicao;

}CADASTRO;
int i = 0;
void Cabecalho();
void Cadastra(CADASTRO rgt[]);
int lerArquivo(CADASTRO rgt[]);
void listarArquivo(CADASTRO rgt[]);
void listaLivro(CADASTRO rgt[]);
void listaRevista(CADASTRO rgt[]);
void PesquisarPorCaixa(CADASTRO rgt[]);

int main(void){
    setlocale(LC_ALL,"portuguese");
    CADASTRO rgt[MAX];
    int opcao;
    char resp;
    printf("\n*****************************");
    printf("\n   Max Suel Santos Batista   ");
    printf("\nCurso Engenharia de Software ");
    printf("\n********************************");
    Cabecalho();
    do
    {
        printf("\n            Menu             ");
        printf("\n*****************************");
        printf("\n1-Registro das obras");
        printf("\n2-Listar Livros");
        printf("\n3-Listar Revistas");
        printf("\n4-Por Caixas");
        printf("\n5-Ler arquivo");
        printf("\n0-Sair");
        printf("\n*****************************");
        printf("\nOpcao: ");
        scanf("%d",&opcao);
        switch (opcao)
        {
        case 1:
            Cabecalho();
            resp='s';
            while((resp=='S')||(resp=='s')){
                i++;
                system("cls");
                Cadastra(rgt);
                printf("Deseja cadastrar novo produto[S][N]: ");
                fflush(stdin);
                scanf("%c",&resp);
            }
            
            break;
        case 2:
            Cabecalho();
            listaLivro(rgt);
            break;
        case 3:
            Cabecalho();
            listaRevista(rgt);
            break;
        case 4:
            Cabecalho();
            PesquisarPorCaixa(rgt);
            break;
        case 5:
            Cabecalho();
            listarArquivo(rgt);
            break;
        case 0:
            printf("\nSAINDO DO SYSTEMA!!\n");
            getch();
            break;
        default:
            printf("\nOPÇÃO INVALIDA!!\n");
            getch();
            break;
        }
    } while (opcao !=0);
    return 0;

}
void Cabecalho(){       // CABEÇALHO DO PROJETO
    printf("\n---------------------------------------------------------");
    printf("\n                    Planilha Eletronica                  ");
    printf("\n---------------------------------------------------------");
}
void Cadastra(CADASTRO rgt[]){      //CADASTRA NOVOS LIVROS E REVISTA 
    FILE *arq;
    arq =fopen("cadastroPlanilha.txt","a");
    if (arq != NULL)
    {
        printf("\n1 - LIVRO |\t2 - REVISTA\n");
        fflush(stdin);
        scanf("%d",&rgt[i].tipo);
        printf("\nTitulo\n");
        fflush(stdin);
        gets(rgt[i].titulo);
        printf("\nAutor\n");
        fflush(stdin);
        gets(rgt[i].autor);
        printf("\nEditora\n");
        fflush(stdin);
        gets(rgt[i].editora);
        printf("\nIsbn\n");
        fflush(stdin);
        scanf("%d",&rgt[i].isbn);
        printf("\nQuantidade\n");
        fflush(stdin);
        scanf("%d",&rgt[i].quantidade);
        printf("\nEdição\n");
        fflush(stdin);
        scanf("%d",&rgt[i].edicao);
        printf("\nAno\n");
        fflush(stdin);
        scanf("%d",&rgt[i].ano);
        printf("\nCaixa\n");
        fflush(stdin);
        scanf("%d",&rgt[i].caixa);
        fwrite(&rgt[i] , sizeof(CADASTRO),1,arq);
    }
    else{
        printf("\nErro ao abrir o arquivo para leitura! \n");
        exit(1);
    }
    fclose(arq);
}
int lerArquivo(CADASTRO rgt[]){        //   FAZ A LEITURA DO ARQUIVO LINHA POR LINHA
    FILE *arq = fopen("cadastroPlanilha.txt", "r");
    if(arq != NULL){
        int i = 0;
        while(1){
            CADASTRO c;
            size_t r = fread(&c, sizeof(CADASTRO), 1,arq);
            if(r < 1)
                break;
            else
                rgt[i++] = c;
        }
        fclose(arq);
        return i;
    }
    else{
       printf("\nErro ao abrir o arquivo para leitura! \n");
        exit(1);
    }
}
void listarArquivo(CADASTRO rgt[]){     //IMPRIMIR A LEITURA NA TELA 
    FILE *arq;
    arq = fopen("cadastroPlanilha.txt", "r");

    fread(rgt, sizeof(int), 10, arq);

    int len_vet = lerArquivo(rgt);

    int j;

    printf("\n>>> Lista de Livros e Revistas <<<\n");
    printf("\n-----------------------------------------------------------------------------\n");
    for(j = 0; j < len_vet; j++){
        printf("\n-----------------------------------------------------------------------------\n");
        printf("\n1-Livro|2-Revista: %d\nTitulo %s\nAutor %s\nEditora %s\nIsbn %d\nQuantidade %d\nEdição %d\nAno %d\nCaixa %d\n",rgt[j].tipo,rgt[j].titulo,rgt[j].autor,rgt[j].editora,rgt[j].isbn,rgt[j].quantidade,rgt[j].edicao,rgt[j].ano,rgt[j].caixa);    
        printf("\n-----------------------------------------------------------------------------\n");
        fclose(arq);
        getch();
    }
}
void listaLivro(CADASTRO rgt[]){        // LISTA E IMPRIMIR OS LIVROS
    FILE *arq = fopen("cadastroPlanilha.txt","r");
    int livro = 1;
    if (arq !=NULL)
    {
        while (fread(&rgt[i],sizeof(CADASTRO),1,arq)==1)
        {
            if (livro == rgt[i].tipo)
            {
                printf("\n-----------------------------------------------------------------------------\n");
                printf("\n1-Livro|2-Revista: %d\nTitulo %s\nAutor %s\nEditora %s\nIsbn %d\nQuantidade %d\nEdição %d\nAno %d\nCaixa %d\n",rgt[i].tipo,rgt[i].titulo,rgt[i].autor,rgt[i].editora,rgt[i].isbn,rgt[i].quantidade,rgt[i].edicao,rgt[i].ano,rgt[i].caixa);    
                printf("\n-----------------------------------------------------------------------------\n");
            }
            
        }
        
    }
    else
    {
        printf("\nError na abertura do arquivo!!\n");
        getch();
    }
    fclose(arq);
    getch();
}
void listaRevista(CADASTRO rgt[]){      // LISTA E IMPRIMIR AS REVISTAS
    FILE *arq = fopen("cadastroPlanilha.txt","r");
    int revista = 2;
    if (arq !=NULL)
    {
        while (fread(&rgt[i],sizeof(CADASTRO),1,arq)==1)
        {
            if (revista == rgt[i].tipo)
            {
                printf("\n-----------------------------------------------------------------------------\n");
                printf("\n1-Livro|2-Revista: %d\nTitulo %s\nAutor %s\nEditora %s\nIsbn %d\nQuantidade %d\nEdição %d\nAno %d\nCaixa %d\n",rgt[i].tipo,rgt[i].titulo,rgt[i].autor,rgt[i].editora,rgt[i].isbn,rgt[i].quantidade,rgt[i].edicao,rgt[i].ano,rgt[i].caixa);    
                printf("\n-----------------------------------------------------------------------------\n");
            }
            
        }
        
    }
    else
    {
        printf("\nError na abertura do arquivo!!\n");
        getch();
    }
    fclose(arq);
    getch();
}
void PesquisarPorCaixa(CADASTRO rgt[]){    // FAZ A LEITURA POR CAIXA
    FILE *arq = fopen("cadastroPlanilha.txt","r");
    int caixa;
    if (arq != NULL)
    {
       printf("\nPor Caixa >> [1] caixa | [2] caixa | [3] caixa : ");
       scanf("%d",&caixa);
       while (fread(&rgt[i],sizeof(CADASTRO),1,arq)==1);
       {
           if (caixa == rgt[i].caixa)
           {    
               printf("\n-----------------------------------------------------------------------------\n");
               printf("\n1-Livro|2-Revista: %d\nTitulo %s\nAutor %s\nEditora %s\nIsbn %d\nQuantidade %d\nEdição %d\nAno %d\nCaixa %d\n",rgt[i].tipo,rgt[i].titulo,rgt[i].autor,rgt[i].editora,rgt[i].isbn,rgt[i].quantidade,rgt[i].edicao,rgt[i].ano,rgt[i].caixa);    
               printf("\n-----------------------------------------------------------------------------\n");
            }
           
        }
       
    }
    else
    {
        printf("\nError na abertura do arquivo!!\n");
        getch();
    }
    fclose(arq);
    getch();

}
