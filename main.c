#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct clientes
{
    char nome[100];
    int conta;
    float saldo;
}typedef clientes;

int cadastra();
void acessa();
void cancela();

int main()
{
    FILE *arquivo;
    arquivo = fopen("arq.txt","a");
    if(arquivo == NULL)
    {
        printf("\nERRO AO ABRIR ARQUIVO\n");
    }
    fclose(arquivo);
    clientes cliente;
    int opcao;
    do
    {
    system("cls");
    printf("\n(1)CADASTRAR CONTA\n(2)ACESSAR CONTA\n(3)CANCELAR CONTA\n(4)ENCERRAR\n");
    printf("\nOPCAO: ");
    scanf("%d",&opcao);
    if(opcao == 1)
    {
        cadastra(arquivo,&cliente);
    }
    if(opcao == 2)
    {
        acessa(arquivo,&cliente);
    }
    if(opcao == 3)
    {
        cancela(arquivo,&cliente);
    }
    }while(opcao != 4);
    return 0;
}

int cadastra(FILE *ptarquivo,clientes *ptcliente)
{
    char auxnome[100];
    ptarquivo = fopen("arq.txt","r");
    if(ptarquivo == NULL)
    {
        printf("\nERRO AO ABRIR ARQUIVO\n");
    }
    system("cls");
    printf("\nNOME: ");
    scanf(" %s",auxnome);
    while(!feof(ptarquivo))
    {
        fscanf(ptarquivo," %s %d %f",ptcliente->nome,&ptcliente->conta,&ptcliente->saldo);
        if(strcmp(ptcliente->nome,auxnome) == 0)
        {
            printf("\nJA EXISTE UMA CONTA COM ESSE NOME\n");
            printf("\nAPERTE QUALQUER TECLA PARA CONTINUAR... ");
            getch();
            return 0;
        }
    }
    fclose(ptarquivo);
    fopen("arq.txt","a");
    if(ptarquivo == NULL)
    {
        printf("\nERRO AO ABRIR ARQUIVO\n");
    }
    srand(time(NULL));
    ptcliente->conta = rand() % 8999 + 1000;
    ptcliente->saldo = 0.0;
    strcpy(ptcliente->nome,auxnome);
    fprintf(ptarquivo,"%s %d %f\n",ptcliente->nome,ptcliente->conta,ptcliente->saldo);
    fclose(ptarquivo);
    printf("\n*************** CADASTRADO COM SUCESSO ***************\n");
    printf("\nAPERTE QUALQUER TECLA PARA CONTINUAR... ");
    getch();
}

void acessa(FILE *ptarquivo,clientes *ptcliente)
{
    system("cls");
    ptarquivo = fopen("arq.txt","r");
    if(ptarquivo == NULL)
    {
        printf("\nERRO AO ABRIR ARQUIVO\n");
    }
    char auxnome[100];
    int i=1;
     printf("\nNOME: ");
     scanf(" %s",auxnome);
    while(!feof(ptarquivo))
    {
        fscanf(ptarquivo," %s %d %f",ptcliente->nome,&ptcliente->conta,&ptcliente->saldo);
        if(strcmp(ptcliente->nome,auxnome) == 0)
        {
            system("cls");
            printf("\n*************** BEM-VINDO ***************\n");
            printf("\n-----------------------------------\n");
             printf("\nCLIENTE: %s",ptcliente->nome);
             printf("\n\nNUMERO DA CONTA: %d\n",ptcliente->conta);
             printf("\nSALDO: %f",ptcliente->saldo);
            printf("\n\n-----------------------------------\n\n");
            i = 0;
            printf("\nAPERTE QUALQUER TECLA PARA CONTINUAR... ");
            getch();
            break;
        }
    }
    if(i == 1)
    {
        printf("\nCONTA INEXISTENTE\n");
        printf("\nAPERTE QUALQUER TECLA PARA CONTINUAR... ");
        getch();
    }
    fclose(ptarquivo);
}

void cancela(FILE *ptarquivo,clientes *ptcliente)
{
    FILE *novoarquivo;
    novoarquivo = fopen("temp.txt","w");
    if(ptarquivo == NULL)
    {
        printf("\nERRO AO ABRIR ARQUIVO\n");
    }
    ptarquivo = fopen("arq.txt","r");
    if(ptarquivo == NULL)
    {
        printf("\nERRO AO ABRIR ARQUIVO\n");
    }
    char auxnome[100];
    int i = 1;
    printf("\nNOME: ");
    system("cls");
    printf("\nNOME: ");
    scanf(" %s",auxnome);
    while(!feof(ptarquivo))
    {
        fscanf(ptarquivo," %s %d %f",ptcliente->nome,&ptcliente->conta,&ptcliente->saldo);
        if(strcmp(ptcliente->nome,auxnome) != 0)
        {
            fprintf(novoarquivo,"%s %d %f\n",ptcliente->nome,ptcliente->conta,ptcliente->saldo);
        }
    }
    fclose(ptarquivo);
    fclose(novoarquivo);

    fopen("temp.txt","r");
    fopen("arq.txt","w");
    while(!feof(novoarquivo))
    {
        fscanf(novoarquivo," %s %d %f",ptcliente->nome,&ptcliente->conta,&ptcliente->saldo);
        fprintf(ptarquivo,"%s %d %f\n",ptcliente->nome,ptcliente->conta,ptcliente->saldo);
    }
    fclose(novoarquivo);
    fclose(ptarquivo);
    remove("arq.txt");
    rename("temp.txt","arq.txt");
    printf("\nCONTA CANCELADA\n");
    printf("\nAPERTE QUALQUER TECLA PARA CONTINUAR... ");
    getch();
}
// "YOU NEVER WALK ALONE", ASSINADO: CAFÉ.
