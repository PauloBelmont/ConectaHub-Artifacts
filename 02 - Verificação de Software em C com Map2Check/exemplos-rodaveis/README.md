# Exemplos rodáveis do Map2Check

Pequenos programas em C para mostrar o que o Map2Check detecta. Cada caso tem duas versões:

- `unsafe.c`: contém um erro que o Map2Check deve encontrar (resultado esperado: **FALSE**, com contraexemplo).
- `safe.c`: a mesma lógica com a correção (resultado esperado: **TRUE**).

Os valores de entrada são gerados com `__VERIFIER_nondet_int()`, a convenção do SV-COMP que o Map2Check reconhece. Ela representa "qualquer inteiro", então o Map2Check explora os casos possíveis.

| Pasta | O que testa | Opção do Map2Check |
|-------|-------------|--------------------|
| `01-asserts` | `assert` que pode falhar | `--check-asserts` |
| `02-overflow` | estouro de inteiro com sinal | `--check-overflow` |
| `03-limites-de-vetor` | escrita fora dos limites de um `malloc` | `--memtrack` |
| `04-use-after-free` | uso de ponteiro depois de `free` | `--memtrack` |

## Requisitos

O Map2Check roda apenas em **Linux 64 bits** (o README do projeto recomenda Ubuntu 22.04). No Windows, use WSL2:

```bash
wsl --install -d Ubuntu-22.04
```

Dentro do Ubuntu:

```bash
sudo apt update
sudo apt install python3 libc6-dev
```

Baixe o pacote oficial em <https://github.com/hbgit/Map2Check/releases> e extraia-o. A pasta de instalação contém o executável `map2check`.

## Como rodar

Ao lado desta pasta, o script `run_all.sh` roda todos os exemplos. Informe a pasta onde está o `map2check`:

```bash
chmod +x run_all.sh
./run_all.sh ~/map2check-vX.Y.Z
```

Para rodar um arquivo específico, dentro da pasta do Map2Check:

```bash
./map2check --check-asserts --timeout 60 /caminho/para/01-asserts/unsafe.c
```

O timeout padrão do script é 60 segundos. Para mudar: `TIMEOUT=120 ./run_all.sh ...`.

## Como ler a saída

- `VERIFICATION FAILED` com `Violated property`: o Map2Check achou um erro e mostra a linha e a propriedade violada.
- `VERIFICATION SUCCESSFUL`: nenhuma violação foi encontrada para as entradas exploradas.
- `VERIFICATION UNKNOWN`: a análise não terminou dentro do tempo; aumente o `--timeout`.

## Observação

Estes exemplos foram escritos para demonstrar as opções. Os resultados esperados vêm da lógica de cada programa; confirme-os rodando o script no seu ambiente Linux/WSL, porque ele não pôde ser executado no Windows onde o material foi criado.
