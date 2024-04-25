# Jogo da cobrinha simples feito em C

Este jogo foi feito para a disciplina de Estrutura de Dados em C, do Curso de Engenharia da Computação do IFPB-CG. 
Ministrada pelo Professor Victor André Oliveira no semestre de 2024.1.

Código feito para rodar inicialmente no Terminal Unix. Desenvolvido no Pop OS 22.04, distribuição Linux inspirada no Ubuntu 22.04.

Para Compilar o código use o comando:

```
gcc -o main main.c
```

E para executar o jogo utilize o comando: 

```
./main
```

## Objetivo Principal:
Desenvolver o jogo da cobrinha utilizando as bibliotecas padrões da linguagem C e utilizando o conceito de lista com vetor (array). 

A lista está implementado tanto dentro da struct "LISTA", no campo "vetor" e "tamanhoAtual", quando em funções paralelas no código. 

## Obejteivos Secundários:
- [x] Múltiplas Comidas no mapa
  - [ ] Otimizar aleatorização das Comidas
  - [ ] Melhores configurações de incrimento de Comidas
  - [ ] Comidas Douradas (Valem mais e são maiores)
- [ ] Adicionar Pontuação
- [x] Modularização do Código
- [x] Adicionar Cores (Implementado com ASCI Escope Codes)
- [ ] Adicionar Alocação Dinâmica
- [ ] Organização e separação do código em arquivos
  - [ ] Para melhor legibilidade
  - [ ] Para mais customizações de variáveis
- [ ] Criações de Menus para melhor interação com o Terminal
- [ ] Copatibilizar o Jogo com o Windows
- [ ] Tornar o jogo mais dinâmico (removendo a biblioteca padrão que precisa aplicar o Enter para processar as entradas)
