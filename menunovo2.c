#include <stdio.h>
#include <stdlib.h>

typedef struct Pixel
{
    int R;
    int G;
    int B;
} RGB;

int main()
{
    char nomeArquivo[100];

    // Solicita ao ususrio que informe o nome do arquivo
    printf("Informe o nome do arquivo (copiando PATH ) para ler a imagem: ");
    scanf("%s", nomeArquivo);

    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    char formato[3];
    fscanf(fp, "%s", formato);
    int coluna, linha, valor;
    fscanf(fp, "%d %d", &coluna, &linha);
    fscanf(fp, "%d", &valor);

    RGB **matriz = (RGB **)malloc(linha * sizeof(RGB *));
    for (int i = 0; i < linha; i++)
    {
        matriz[i] = (RGB *)malloc(coluna * sizeof(RGB));
        for (int j = 0; j < coluna; j++)
        {
            fscanf(fp, "%d %d %d", &matriz[i][j].R, &matriz[i][j].G, &matriz[i][j].B);
        }
    }
    fclose(fp);

    int opcao;
    do
    {
        printf("\nMenu de Opcoes:\n");
        printf("1. Gerar uma imagem em tons de cinza\n");
        printf("2. Gerar imagem negativa\n");
        printf("3. Aumentar o brilho\n");
        printf("4. Diminuir o brilho\n");
        printf("5. Rotacionar a imagem\n");
        printf("6. Envelhecimento da imagem\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            FILE *fp_novo = fopen("imgCinza.ppm", "w"); // Cria a nova imagem
            if (!fp_novo)
            {
                printf("Erro ao criar o arquivo");
                return 1;
            }

            fprintf(fp_novo, "P3\n%d %d\n%d\n", coluna, linha, valor);
            for (int j = 0; j < linha; j++)
            {
                for (int i = 0; i < coluna; i++)
                {

                    int cinza = (int)(matriz[j][i].R * 0.30 + matriz[j][i].G * 0.59 + matriz[j][i].B * 0.11);
                    fprintf(fp_novo, "%d %d %d\n", cinza, cinza, cinza);
                }
            }
            fclose(fp_novo); // Fecha o arquivo

            printf("Imagem convertida em tons de cinza salva com sucesso.\n");
            break;
        }

        case 2: // Gerar imagem negativa
        {
            FILE *fp_novo1 = fopen("imgNegativa.ppm", "w"); // Cria a nova imagem
            if (!fp_novo1)
            {
                printf("Erro ao criar o arquivo");
                return 1;
            }

            fprintf(fp_novo1, "P3\n%d %d\n%d\n", coluna, linha, valor);
            for (int j = 0; j < linha; j++)
            {
                for (int i = 0; i < coluna; i++)
                {
                    int red = 255 - matriz[j][i].R;
                    int green = 255 - matriz[j][i].G;
                    int blue = 255 - matriz[j][i].B;

                    fprintf(fp_novo1, "%d %d %d\n", red, green, blue);
                }
            }
            fclose(fp_novo1); // Fecha o arquivo

            printf("Imagem negativa gerada com sucesso.\n");
            break;
        }

        case 3: // Aumentar o brilho   - multiplica por 1.30
        {
            FILE *fp_novo2 = fopen("imgBrilho.ppm", "w"); // Cria a nova imagem
            if (!fp_novo2)
            {
                printf("Erro ao criar o arquivo");
                return 1;
            }

            fprintf(fp_novo2, "P3\n%d %d\n%d\n", coluna, linha, valor);
            for (int j = 0; j < linha; j++)
            {
                for (int i = 0; i < coluna; i++)
                {
                    // Multiplica cada componente de cor por 1.3
                    int red = (int)(matriz[j][i].R * 1.3);
                    int green = (int)(matriz[j][i].G * 1.3);
                    int blue = (int)(matriz[j][i].B * 1.3);

                    // Limita os valores a 255
                    if (red > 255)
                    {
                        red = 255;
                    }
                    if (green > 255)
                    {
                        green = 255;
                    }
                    if (blue > 255)
                    {
                        blue = 255;
                    }

                    fprintf(fp_novo2, "%d %d %d\n", red, green, blue);
                }
            }
            fclose(fp_novo2); // Fecha o arquivo

            printf("Imagem com brilho aumentado salva com sucesso.\n");
            break;
        }
        case 4: // Diminuir o brilho -- multiplica por 0.7
        {
            FILE *fp_novo3 = fopen("imgBrilhoDiminuido.ppm", "w"); // Cria a nova imagem
            if (!fp_novo3)
            {
                printf("Erro ao criar o arquivo");
                return 1;
            }

            fprintf(fp_novo3, "P3\n%d %d\n%d\n", coluna, linha, valor);
            for (int j = 0; j < linha; j++)
            {
                for (int i = 0; i < coluna; i++)
                {
                    // Diminui o brilho multiplicando cada componente de cor por 0.7
                    int red = (int)(matriz[j][i].R * 0.7);
                    int green = (int)(matriz[j][i].G * 0.7);
                    int blue = (int)(matriz[j][i].B * 0.7);

                    // Limita os valores a 255
                    if (red > 255)
                    {
                        red = 255;
                    }
                    if (green > 255)
                    {
                        green = 255;
                    }
                    if (blue > 255)
                    {
                        blue = 255;
                    }

                    fprintf(fp_novo3, "%d %d %d\n", red, green, blue);
                }
            }
            fclose(fp_novo3); // Fecha o arquivo

            printf("Imagem com brilho diminuído salva com sucesso.\n");
            break;
        }

        case 5: // Rotacionar imagem colorida 90 graus no sentido horario
        {
            FILE *fp_novo4 = fopen("imgRotacionada.ppm", "w"); // Cria a nova imagem
            if (!fp_novo4)
            {
                printf("Erro ao criar o arquivo");
                return 1;
            }

            fprintf(fp_novo4, "P3\n%d %d\n%d\n", linha, coluna, valor);

            for (int i = coluna - 1; i >= 0; i--)
            {
                for (int j = 0; j < linha; j++)
                {
                    fprintf(fp_novo4, "%d %d %d\n", matriz[j][i].R, matriz[j][i].G, matriz[j][i].B);
                }
            }
            fclose(fp_novo4); // Fecha o arquivo

            printf("Imagem rotacionada 90 graus salva com sucesso.\n");
            break;
        }

        case 6: // Envelhecimento da imagem - diminuir cada pixel de 20
        {
            FILE *fp_novo2 = fopen("imgEnvelhecida.ppm", "w"); // Cria a nova imagem
            if (!fp_novo2)
            {
                printf("Erro ao criar o arquivo");
                return 1;
            }

            fprintf(fp_novo2, "P3\n%d %d\n%d\n", coluna, linha, valor);
            for (int j = 0; j < linha; j++)
            {
                for (int i = 0; i < coluna; i++)
                {
                    int red = matriz[j][i].R - 20;   // Diminuir 20 do componente vermelho
                    int green = matriz[j][i].G - 20; // Diminuir 20 do componente verde
                    int blue = matriz[j][i].B - 20;  // Diminuir 20 do componente azul

                    // Verifica se os valores ficaram abaixo de 0 e ajusta para 0
                    if (red < 0)
                    {
                        red = 0;
                    }
                    if (green < 0)
                    {
                        green = 0;
                    }
                    if (blue < 0)
                    {
                        blue = 0;
                    }

                    fprintf(fp_novo2, "%d %d %d\n", red, green, blue);
                }
            }
            fclose(fp_novo2); // Fecha o arquivo

            printf("Imagem envelhecida gerada com sucesso.\n");
            break;
        }
        case 0:
            printf("Fechando o programa...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    for (int i = 0; i < linha; i++)
    {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}