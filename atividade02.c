/**
 * Atividade Proposta 02 - Cifra de César + Sequências Matemáticas
 * Autor: Diego Troiani
 * Professor: Prof. Francisco de Assis Cavallaro
 * Disciplina: Algoritmos e Pensamento Computacional
 *
 * O sistema fará a criptografia de um texto enviado pelo usuário em 2 camadas.
 * A senha pode ser:
 * -> Entre 4 a 50 caracteres
 * -> Letras maiúsculas e minúsculas
 * -> Caracteres da tabela ASCII
 *
 * 1. CAMADA = Aplicar a Cifra César com o Shift informado pelo usuário (entre 1
 * e 50)
 * 2. CAMADA = Aplicar uma ou todas sequências matemáticas (PA, PG, Primos ou
 * Fibonacci)
 *
 * Obs: O sitema gera um .csv de log com o texto original, o texto com shift e o
 * texto final criptografado e quais foram as sequências aplicadas com data e
 * hora da execução.
 *
 */

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>

// Funções Protótipo
int menuSequencia();
char movimentarASCII(char caractere, int deslocamento);
void aplicarShift(char texto[], int shift);
void aplicarPA(char texto[], int primeiroTermo, int razao);
void aplicarPG(char texto[], int primeiroTermo, int razao);
void aplicarFibonacci(char texto[]);
void aplicarPrimos(char texto[]);
int ehPrimo(int numero);
void removerEspacos(char text[]);
void removerQuebraLinha(char texto[]);
int validarTexto(char texto[]);
void salvarCSV(char textoOriginal[], char textoShift[], char textoFinal[],
               int shift, int opcao, int primeiroTermoPA, int razaoPA,
               int primeiroTermoPG, int razaoPG);
char* nomeMetodo(int opcao);

int main() {
  char texto[52];
  char textoOriginal[52];
  char textoShift[52];
  int shift;

  // =========================
  // ENTRADA DO TEXTO
  // =========================
  do {
    printf("Digite um texto entre 4 e 50 caracteres: ");
    fgets(texto, sizeof(texto), stdin);

    // Tratamento
    removerQuebraLinha(texto);
    removerEspacos(texto);

    // Validação
    if (!validarTexto(texto)) {
      printf("Texto invalido. Digite entre 4 e 50 caracteres.\n\n");
    }
  } while (!validarTexto(texto));

  // =========================
  // ENTRADA DO SHIFT
  // =========================
  int leitura;
  do {
    printf("Digite o valor do SHIFT entre 1 e 50: ");
    leitura = scanf("%d", &shift);

    // Valida se shift é um número
    if (leitura != 1) {
      printf("Valor de SHIFT invalido. Digite um numero entre 1 e 50.\n\n");
      while (getchar() != '\n');
    } else if (shift < 1 || shift > 50) {
      printf("Valor de SHIFT invalido. Digite entre 1 e 50.\n\n");
    }
  } while (leitura != 1 || shift < 1 || shift > 50);

  // =========================
  // MOSTRA TEXTO ORIGINAL
  // =========================
  printf("\nTexto original: %s\n", texto);

  // Salva o texto original para o log
  strcpy(textoOriginal, texto);

  // =========================
  // CAMADA 1 - SHIFT
  // =========================
  aplicarShift(texto, shift);
  int opcao = menuSequencia();

  // Guarda o resultado da primeira camada SHIFT para o log
  strcpy(textoShift, texto);

  // CAMADA 2 - APLICAR SEQUÊNCIAS MATEMÁTICAS
  // ============================
  int primeiroTermoPA = 0;
  int razaoPA = 0;

  int primeiroTermoPG = 0;
  int razaoPG = 0;

  switch (opcao) {
    case 0:
      printf("Nenhuma sequencia aplicada.\n");
      break;

    case 1: {
      printf("\n --- Progressao Aritmetica (PA) ---\n");

      // Primeiro Termo
      printf("Digite o primeiro termo da PA: ");
      scanf("%d", &primeiroTermoPA);

      // Razão
      printf("Digite a razao da PA: ");
      scanf("%d", &razaoPA);

      aplicarPA(texto, primeiroTermoPA, razaoPA);
      break;
    }
    case 2: {
      printf("\n --- Progressao Geometrica (PG) ---\n");

      printf("Digite o primeiro termo da PG: ");
      scanf("%d", &primeiroTermoPG);

      printf("Digite a razao da PG: ");
      scanf("%d", &razaoPG);

      aplicarPG(texto, primeiroTermoPG, razaoPG);
      break;
    }
    case 3:
      aplicarFibonacci(texto);
      break;

    case 4:
      aplicarPrimos(texto);
      break;

    case 5: {
      printf("\n--- Aplicar todas as sequencias ---\n");

      // PA
      printf("\nDigite o primeiro termo da PA: ");
      scanf("%d", &primeiroTermoPA);

      printf("Digite a razao da PA: ");
      scanf("%d", &razaoPA);

      // PG
      printf("\nDigite o primeiro termo da PG: ");
      scanf("%d", &primeiroTermoPG);

      printf("Digite a razao da PG: ");
      scanf("%d", &razaoPG);

      // Aplicação das sequências
      aplicarPA(texto, primeiroTermoPA, razaoPA);
      aplicarPG(texto, primeiroTermoPG, razaoPG);
      aplicarFibonacci(texto);
      aplicarPrimos(texto);

      break;
    }
  }

  // Saída final
  printf("Resultado final: %s\n", texto);

  // Salvar log em CSV
  salvarCSV(textoOriginal, textoShift, texto, shift, opcao, primeiroTermoPA,
            razaoPA, primeiroTermoPG, razaoPG);

  return 0;
}

// Menu
int menuSequencia() {
  int opcao;
  int leitura;

  do {
    printf("\nEscolha a segunda camada:\n");
    printf("0. Nenhuma\n");
    printf("1. Progressao Aritmetica (PA)\n");
    printf("2. Progressao Geometrica (PG)\n");
    printf("3. Fibonacci\n");
    printf("4. Primos\n");
    printf("5. Todas as sequencias\n");

    printf("Digite a opcao desejada: ");
    leitura = scanf("%d", &opcao);

    if (leitura != 1) {
      printf("Opcao invalida. Digite apenas numeros.\n\n");

      while (getchar() != '\n');

    } else if (opcao < 0 || opcao > 5) {
      printf("Opcao invalida. Digite um numero entre 0 e 5.\n\n");
    }
  } while (leitura != 1 || opcao < 0 || opcao > 5);

  return opcao;
}

// Função para movimentar o caractere na tabela ASCII
char movimentarASCII(char caractere, int deslocamento) {
  if (caractere >= 33 && caractere <= 126) {
    deslocamento =
        deslocamento %
        94;  // Mantém o deslocamento dentro do intervalo de 94 caracteres
    return ((caractere - 33 + deslocamento) % 94) + 33;
  }
  return caractere;
}

// SHIFT
void aplicarShift(char texto[], int shift) {
  int tamanho = strlen(texto);

  for (int i = 0; i < tamanho; i++) {
    texto[i] = movimentarASCII(texto[i], shift);
  }
}

// Sequências Matemáticas
// PA - Progressão Aritmética
void aplicarPA(char texto[], int primeiroTermo, int razao) {
  int tamanho = strlen(texto);

  for (int i = 0; i < tamanho; i++) {
    int termo =
        (primeiroTermo + (i * razao)) %
        94;  // Mantém o deslocamento dentro da faixa de 94 caracteres ASCII
    texto[i] = movimentarASCII(texto[i], termo);
  }
}

// PG - Progressão Geométrica
void aplicarPG(char texto[], int primeiroTermo, int razao) {
  int tamanho = strlen(texto);
  int termo = primeiroTermo % 94;

  for (int i = 0; i < tamanho; i++) {
    texto[i] = movimentarASCII(texto[i], termo);
    termo = (termo * razao) %
            94;  // Mantém o deslocamento dentro da faixa de 94 caracteres ASCII
  }
}

// Fibonacci
void aplicarFibonacci(char texto[]) {
  int tamanho = strlen(texto);

  long long fib1 = 1, fib2 = 1;

  for (int i = 0; i < tamanho; i++) {
    long long termo;

    if (i == 0 || i == 1) {
      termo = 1;
    } else {
      termo = fib1 + fib2;
      fib1 = fib2;
      fib2 = termo;
    }

    termo = termo % 94;

    texto[i] = movimentarASCII(texto[i], (int)termo);
  }
}

// Primos
void aplicarPrimos(char texto[]) {
  int tamanho = strlen(texto);

  int numero = 2;

  for (int i = 0; i < tamanho; i++) {
    while (!ehPrimo(numero)) {
      numero++;
    }

    texto[i] = movimentarASCII(texto[i], numero % 94);

    numero++;
  }
}

// Verifica se um número é primo
int ehPrimo(int numero) {
  if (numero < 2) {
    return 0;
  }

  for (int i = 2; i < numero; i++) {
    if (numero % i == 0) {
      return 0;
    }
  }

  return 1;
}

// Remover espaços em branco
void removerEspacos(char text[]) {
  int i, j = 0;

  for (i = 0; text[i] != '\0'; i++) {
    if (text[i] != ' ') {
      text[j] = text[i];
      j++;
    }
  }
  text[j] = '\0';  // Adiciona o caractere nulo no final da string
}

// Remover quebra de linha
void removerQuebraLinha(char texto[]) {
  int tamanho = strlen(texto);

  if (tamanho > 0 && texto[tamanho - 1] == '\n') {
    texto[tamanho - 1] = '\0';
  }
}

// Validar tamanho do texto
int validarTexto(char texto[]) {
  int tamanho = strlen(texto);

  if (tamanho >= 4 && tamanho <= 50) {
    return 1;
  }

  return 0;
}

// Salvar log em CSV
void salvarCSV(char textoOriginal[], char textoShift[], char textoFinal[],
               int shift, int opcao, int primeiroTermoPA, int razaoPA,
               int primeiroTermoPG, int razaoPG) {
// Verifica qual sistema operacional está sendo usado e cria a pasta "output" se
// não existir
#ifdef _WIN32
  _mkdir("./output");
#else
  mkdir("./output", 0777);
#endif

  // Cria ou abre o arquivo CSV para escrita
  FILE* arquivo;
  FILE* verificacao;
  int arquivoExiste = 0;

  // Verofica se o arquivo já existe
  verificacao = fopen("./output/dados_criptografados.csv", "r");

  if (verificacao != NULL) {
    arquivoExiste = 1;
    fclose(verificacao);
  }

  // Abre o arquivo CSV em modo de escrita (append)
  arquivo = fopen("./output/dados_criptografados.csv", "a");

  // Verifica se arquivo existe
  if (arquivo == NULL) {
    printf("Erro ao criar o arquivo CSV.\n");
    return;
  }

  // Se o arquivo ainda não existia, cria o cabeçalho
  if (!arquivoExiste) {
    // Coloca UTF-8 BOM no início do arquivo para suportar caracteres especiais
    fprintf(arquivo, "\xEF\xBB\xBF");

    fprintf(arquivo,
            "Data/Hora;Texto Original;Texto apos SHIFT;Resultado "
            "Final;SHIFT;Metodo;"
            "PA Primeiro Termo;PA Razao;PG Primeiro Termo;PG Razao\n");
  }

  // Captura a data e hora atual
  time_t agora = time(NULL);
  struct tm* dataHora = localtime(&agora);

  // Escreve os dados no arquivo CSV
  fprintf(arquivo, "%02d/%02d/%04d %02d:%02d:%02d;%s;%s;%s;%d;%s;%d;%d;%d;%d\n",
          dataHora->tm_mday, dataHora->tm_mon + 1, dataHora->tm_year + 1900,
          dataHora->tm_hour, dataHora->tm_min, dataHora->tm_sec, textoOriginal,
          textoShift, textoFinal, shift, nomeMetodo(opcao), primeiroTermoPA,
          razaoPA, primeiroTermoPG, razaoPG);

  // Fecha o arquivo CSV
  fclose(arquivo);

  printf("\nHistorico salvo em ./output/dados_criptografados.csv\n");
}

char* nomeMetodo(int opcao) {
  switch (opcao) {
    case 0:
      return "Nenhuma";

    case 1:
      return "Progressão Aritmética (PA)";

    case 2:
      return "Progressão Geométrica (PG)";

    case 3:
      return "Fibonacci";

    case 4:
      return "Primos";

    case 5:
      return "Todas";

    default:
      return "Desconhecido";
  }
}