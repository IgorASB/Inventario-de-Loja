# Inventário de Loja 📦

> Programa de controle de estoque em linguagem C, com persistência em arquivo texto e alocação dinâmica de memória.

## ℹ️ Sobre o Projeto

Este programa permite gerenciar o inventário de uma loja diretamente pelo terminal. Os dados são salvos em um arquivo `inventario.txt` para que as informações persistam entre as execuções.

## ⚙️ Funcionalidades

- [📝] Cadastrar novos produtos com ID único, nome, quantidade e preço
- [📋] Listar todos os produtos do inventário
- [🔄] Atualizar estoque (entrada ou saída de unidades)
- [💾] Salvar automaticamente ao encerrar o programa
- [✅] Validação de ID duplicado e estoque insuficiente

## 📚 Conceitos Utilizados

| Conceito | Aplicação no projeto |
|----------|----------------------|
| `struct` | Modelagem do produto com campos `id`, `nome`, `quantidade` e `preco` |
| Ponteiros | Passagem por referência para modificar o vetor dinamicamente |
| `realloc` | Crescimento do vetor com estratégia de dobramento de capacidade |
| F/S em arquivo | Persistência dos dados em `inventario.txt` entre execuções |
| Validação | Verificação de ID duplicado, estoque negativo e erros de memória |

## 🚀 Como Usar

### Pré-requisitos

- Compilador C (GCC recomendado)

### Compilação e Execução

```bash
# Compilar
gcc inventario.c -o inventario

# Executar (Linux/macOS)
./inventario

# Executar (Windows)
inventario.exe
```

### Menu do Programa

```
=== INVENTARIO DE LOJA ===
1 - Cadastrar produto
2 - Listar produtos
3 - Atualizar estoque
4 - Salvar e sair
```

## 📁 Estrutura do Projeto

```
inventario-de-loja/
├── inventario.c       # código-fonte principal
├── inventario.txt     # arquivo gerado automaticamente ao salvar
└── README.md
```

## Tecnologia

![Linguagem C](https://img.shields.io/badge/Linguagem-C-00599c?style=flat&logo=c&logoColor=white)
![Plataforma](https://img.shields.io/badge/Plataforma-Linux%20%7C%20Windows%20%7C%20macOS-000000?style=flat)

## 👤 Autor

Feito por [Igor](https://github.com/IgorASB) - Estudante de Ciência da Computação
