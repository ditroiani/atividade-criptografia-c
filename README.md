# 🔐 Criptografia em C com SHIFT + Sequências Matemáticas

> Projeto acadêmico desenvolvido para a disciplina de **Algoritmos e Pensamento Computacional**.

Este projeto implementa um sistema de criptografia em **duas camadas**, combinando a **Cifra de César (SHIFT)** com sequências matemáticas como **Progressão Aritmética, Progressão Geométrica, Fibonacci e números primos**.

## ✨ Funcionalidades

- 🔤 Entrada de texto com até **50 caracteres**
- 🔠 Suporte a letras maiúsculas e minúsculas
- 🔣 Uso de caracteres ASCII imprimíveis
- 🔐 Criptografia com **SHIFT**
- ➕ Progressão Aritmética (PA)
- ✖️ Progressão Geométrica (PG)
- 🌀 Fibonacci
- 🔢 Números primos
- 🔀 Opção para aplicar **todas as sequências**
- 🧩 Código modularizado em funções
- 📊 Geração de histórico em arquivo CSV
- 🕒 Registro de data e hora da execução

## 🧠 Conceito do projeto

O programa funciona em duas camadas:

```text
Texto Original
      ↓
SHIFT
      ↓
Sequência Matemática
      ↓
Texto Criptografado
```

### Camada 1 — SHIFT

O usuário informa um valor de deslocamento.

Os caracteres são movimentados dentro da faixa ASCII:

```text
33 até 126
```

A movimentação é circular:

```text
~ + 1 → !
```

A fórmula utilizada é:

```c
((caractere - 33 + deslocamento) % 94) + 33
```

## 🔢 Camada 2 — Sequências Matemáticas

O usuário pode escolher:

```text
0 - Nenhuma
1 - Progressão Aritmética (PA)
2 - Progressão Geométrica (PG)
3 - Fibonacci
4 - Primos
5 - Todas as sequências
```

Cada termo da sequência é utilizado como um deslocamento adicional para o caractere correspondente.

## ➕ Progressão Aritmética

Exemplo:

```text
Primeiro termo: 3
Razão: 2
```

Sequência:

```text
3, 5, 7, 9, 11...
```

## ✖️ Progressão Geométrica

Exemplo:

```text
Primeiro termo: 2
Razão: 3
```

Sequência:

```text
2, 6, 18, 54, 162...
```

Os valores utilizados no deslocamento são ajustados com `% 94`.

## 🌀 Fibonacci

A sequência utilizada é:

```text
1, 1, 2, 3, 5, 8, 13...
```

O projeto utiliza `long long` para aumentar a capacidade de armazenamento dos termos.

## 🔢 Números Primos

A sequência começa em:

```text
2, 3, 5, 7, 11, 13, 17...
```

O programa possui uma função própria para verificar se um número é primo.

## 🔀 Opção “Todas”

Ao selecionar a opção `5`, o fluxo é:

```text
SHIFT
  ↓
PA
  ↓
PG
  ↓
Fibonacci
  ↓
Primos
  ↓
Resultado Final
```

## 🧩 Organização do código

O projeto foi dividido em funções para separar responsabilidades:

```c
menuSequencia()
movimentarASCII()
aplicarShift()
aplicarPA()
aplicarPG()
aplicarFibonacci()
aplicarPrimos()
ehPrimo()
removerEspacos()
removerQuebraLinha()
validarTexto()
salvarCSV()
nomeMetodo()
```

## 📊 Log em CSV

Ao final de cada execução, o programa registra os dados em:

```text
./output/dados_criptografados.csv
```

O arquivo armazena:

- Data e hora
- Texto original
- Texto após SHIFT
- Resultado final
- Valor do SHIFT
- Método utilizado
- Primeiro termo e razão da PA
- Primeiro termo e razão da PG

Exemplo:

```text
Data/Hora;Texto Original;Texto apos SHIFT;Resultado Final;SHIFT;Metodo;PA Primeiro Termo;PA Razao;PG Primeiro Termo;PG Razao
01/10/2026 23:15:00;DIEGO;KPLNV;Rc!-HwG};7;Todas;2;5;2;4
```

## 📁 Estrutura

```text
atividade-criptografia-c/
│
├── atividade02.c
├── README.md
│
└── output/
    └── dados_criptografados.csv
```

# 🎓 Objetivos de aprendizagem

O projeto aplica conceitos de:

- Linguagem C
- Algoritmos
- Funções
- Strings
- Vetores
- Condicionais
- Laços de repetição
- Tabela ASCII
- Progressões matemáticas
- Manipulação de arquivos
- Modularização

---

## 👨‍💻 Autor
**Diego Troiani**
Projeto acadêmico desenvolvido para fins de estudo em **Algoritmos e Pensamento Computacional**.
