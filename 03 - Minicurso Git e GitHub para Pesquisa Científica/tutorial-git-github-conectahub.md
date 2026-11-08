> Parte do material do minicurso "Minicurso: Git e GitHub para Pesquisa Científica" (Conecta Hub)

# Tutorial de Git e GitHub para Pesquisa Científica

Material do minicurso, dividido em partes.

## Sumário

- [Parte 1 – O que é Git e GitHub](#parte-1--o-que-é-git-e-github)
- [Parte 2 – Instalação e configuração (`git config`)](#parte-2--instalação-e-configuração-git-config)
- [Parte 3 – Chave SSH no GitHub](#parte-3--chave-ssh-no-github)
- [Parte 4 – Comandos básicos (`git init`, `add`, `commit`, `status`, `log`)](#parte-4--comandos-básicos)
- [Parte 5 – Branches (`git branch`, `switch`, `merge`)](#parte-5--branches)
- [Parte 6 – Repositórios remotos (`clone`, `push`, `pull`, `fetch`)](#parte-6--repositórios-remotos)
- [Parte 7 – `.gitignore`, desfazer e conflitos](#parte-7--gitignore-desfazer-e-conflitos)
- [Parte 8 – Fluxo de trabalho para um artigo](#parte-8--fluxo-de-trabalho-para-um-artigo)
- [Cola rápida de comandos](#cola-rápida-de-comandos)

> **Convenção:** os blocos `bash` são comandos para digitar no terminal (Git Bash, PowerShell, Terminal do VS Code etc.). Onde aparecer `Seu Nome` ou `seu-email@exemplo.com`, substitua pelos seus dados.

---

## Parte 1 – O que é Git e GitHub

- **Git**: sistema de controle de versão que roda no seu computador. Ele guarda o histórico de cada alteração dos arquivos de um projeto.
- **GitHub**: serviço na nuvem que hospeda repositórios Git e permite colaboração (compartilhar, revisar, publicar).

Conceitos principais:

| Termo | Significado |
|-------|-------------|
| **Repositório** | Pasta de projeto controlada pelo Git (contém a pasta oculta `.git`) |
| **Commit** | "Foto" do projeto em um momento, com uma mensagem descritiva |
| **Branch** | Linha paralela de desenvolvimento |
| **Remote** | Cópia do repositório em outro lugar (normalmente o GitHub), chamada `origin` por padrão |
| **Working directory / staging / histórico** | Arquivos modificados → área de preparação (`add`) → commit no histórico |

---

## Parte 2 – Instalação e configuração (`git config`)

### 2.1 Instalar

- Windows: baixe em <https://git-scm.com> (o instalador traz o **Git Bash**).
- Linux: `sudo apt install git`

Verifique:

```bash
git --version
```

### 2.2 Configurar identidade

Essas informações aparecem em cada commit. Use o mesmo e-mail da sua conta no GitHub.

```bash
git config --global user.name "Seu Nome"
git config --global user.email "seu-email@exemplo.com"
```

### 2.3 Outras configurações úteis

```bash
git config --global init.defaultBranch main     # nome padrão da branch principal
git config --global core.editor "code --wait"   # usa o VS Code como editor de mensagens
git config --global core.autocrlf true          # Windows: converte finais de linha
git config --global pull.rebase false           # comportamento padrão do pull
```

### 2.4 Ver e consultar configurações

```bash
git config --list                # todas as configurações
git config --global --list       # só as globais
git config user.name             # consulta um valor específico
```

As configurações ficam no arquivo `~/.gitconfig`. Configurações **sem** `--global` valem só para o repositório atual (`.git/config`).

---

## Parte 3 – Chave SSH no GitHub

Desde 2021 o GitHub não aceita senha de conta para operações Git pela linha de comando. Você pode usar um **token** (HTTPS) ou uma **chave SSH**. A chave SSH é mais prática: configure uma vez e não precisa digitar nada depois.

### 3.1 Verificar se já existe uma chave

```bash
ls -al ~/.ssh
```

Se existir `id_ed25519.pub` (ou `id_rsa.pub`), você já tem uma chave. Pode pular para o passo 3.3.

### 3.2 Gerar uma nova chave

```bash
ssh-keygen -t ed25519 -C "seu-email@exemplo.com"
```

- Pressione **Enter** para aceitar o caminho padrão (`~/.ssh/id_ed25519`).
- Defina uma **senha (passphrase)** para proteger a chave, ou deixe em branco.

### 3.3 Iniciar o agente SSH e adicionar a chave

```bash
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
```

> No Windows, se o `ssh-agent` estiver desativado, abra o PowerShell como administrador e execute:
> `Get-Service ssh-agent | Set-Service -StartupType Automatic` e depois `Start-Service ssh-agent`.

### 3.4 Copiar a chave pública

Linux/macOS/Git Bash:

```bash
cat ~/.ssh/id_ed25519.pub
```

Copie **toda** a linha que começa com `ssh-ed25519`. Nunca compartilhe a chave **privada** (arquivo sem `.pub`).

### 3.5 Cadastrar no GitHub

1. Entre no GitHub e clique na sua foto → **Settings**.
2. No menu lateral, **SSH and GPG keys** → **New SSH key**.
3. Em *Title* coloque um nome (ex.: `Notebook pessoal`), em *Key* cole a chave e clique em **Add SSH key**.

### 3.6 Testar a conexão

```bash
ssh -T git@github.com
```

Na primeira vez aparecerá um aviso de *fingerprint*; digite `yes`. A resposta esperada é algo como:

```
Hi seu-usuario! You've successfully authenticated, but GitHub does not provide shell access.
```

### 3.7 Usar SSH nos repositórios

Um repositório clonado por HTTPS usa a URL `https://github.com/usuario/repo.git`. Para trocar para SSH:

```bash
git remote set-url origin git@github.com:usuario/repo.git
```

Problemas comuns:

- `Permission denied (publickey)`: a chave não foi adicionada ao agente (repita 3.3) ou não foi cadastrada no GitHub (3.5).
- Chave errada sendo usada: crie `~/.ssh/config` com:

```
Host github.com
    HostName github.com
    User git
    IdentityFile ~/.ssh/id_ed25519
```

---

## Parte 4 – Comandos básicos

### 4.1 Criar um repositório: `git init`

```bash
mkdir meu-artigo
cd meu-artigo
git init
```

Isso cria a pasta oculta `.git`. Para conferir: `ls -a`.

### 4.2 Ver o estado: `git status`

```bash
git status
```

Mostra arquivos novos (*untracked*), modificados e prontos para commit. Use-o sempre antes de commitar.

### 4.3 Preparar alterações: `git add`

```bash
git add arquivo.tex          # um arquivo
git add secao/               # uma pasta
git add .                    # tudo que foi modificado nesta pasta
```

### 4.4 Gravar no histórico: `git commit`

```bash
git commit -m "Adiciona introdução do artigo"
```

Boas mensagens são curtas e no imperativo: "Corrige tabela 2", "Adiciona referências de Silva (2020)".

Para escrever uma mensagem mais longa, omita `-m` e o editor abrirá.

#### Tipos de commit (Conventional Commits)

Um padrão comum é começar a mensagem com um **tipo**, seguido de dois-pontos e da descrição:

```
<tipo>(<escopo opcional>): <descrição curta no imperativo>
```

| Tipo | Quando usar | Exemplo |
|------|-------------|---------|
| `feat` | Nova funcionalidade ou nova seção de conteúdo | `feat(artigo): adiciona seção de metodologia` |
| `fix` | Correção de erro | `fix(tabela): corrige alinhamento da tabela 2` |
| `docs` | Mudança só na documentação ou no texto | `docs(readme): explica como compilar o PDF` |
| `style` | Formatação, sem mudar o conteúdo (espaços, indentação, quebras de linha) | `style(tex): padroniza indentação das equações` |
| `refactor` | Reorganiza o código ou o texto sem mudar o resultado | `refactor(bib): reordena referências por autor` |
| `test` | Adiciona ou corrige testes e exemplos de verificação | `test(map2check): adiciona caso de overflow` |
| `chore` | Tarefas de manutenção que não mudam o conteúdo (configuração, `.gitignore`, atualizações de ferramentas) | `chore(gitignore): ignora arquivos auxiliares do LaTeX` |
| `build` | Mudanças no processo de compilação ou dependências | `build(latex): troca biblatex por natbib` |
| `ci` | Mudanças em integração contínua (arquivos de workflow) | `ci(github): adiciona verificação de compilação` |
| `perf` | Melhoria de desempenho | `perf(figuras): reduz resolução das imagens` |
| `revert` | Desfaz um commit anterior | `revert: desfaz "feat(artigo): adiciona seção de metodologia"` |

Exemplos de uso no terminal:

```bash
git commit -m "feat(artigo): adiciona introdução"
git commit -m "fix(bib): corrige ano da referência de Silva"
git commit -m "chore: atualiza .gitignore"
```

Dicas:

- Use o **escopo** entre parênteses quando ajudar a localizar a mudança (`artigo`, `bib`, `tabela`).
- Adicione `!` depois do tipo (ex.: `feat!: ...`) ou um rodapé `BREAKING CHANGE:` quando a mudança quebrar algo que já funcionava.
- Escolha um tipo por commit. Se a mudança mistura dois tipos, quebre em dois commits.

### 4.5 Ver o histórico: `git log`

```bash
git log                     # completo
git log --oneline           # uma linha por commit
git log --oneline --graph   # com ramificações desenhadas
```

### 4.6 Ver diferenças: `git diff`

```bash
git diff                    # alterações ainda não preparadas
git diff --staged           # alterações preparadas (já com git add)
```

### 4.7 Exemplo completo

```bash
git init
git config --global user.name "Seu Nome"        # se ainda não fez
echo "\\section{Introdução}" > artigo.tex
git status
git add artigo.tex
git commit -m "Cria esqueleto do artigo"
git log --oneline
```

---

## Parte 5 – Branches

Branches permitem testar ideias sem mexer na versão principal (`main`). Use um branch para cada nova seção, revisão ou experimento.

### 5.1 Listar e criar: `git branch`

```bash
git branch                  # lista branches locais (* indica a atual)
git branch revisao-2       # cria um branch novo (sem trocar)
git branch -a               # lista também branches remotos
```

### 5.2 Trocar de branch: `git switch` / `git checkout`

```bash
git switch revisao-2        # troca para o branch
git switch -c metodologia   # cria e troca de uma vez
```

`git checkout` faz coisas parecidas e ainda aparece em muitos tutoriais: `git checkout -b nome` equivale a `git switch -c nome`.

### 5.3 Juntar branches: `git merge`

```bash
git switch main
git merge revisao-2
```

Se as mudanças não se sobrepõem, o merge é automático. Caso contrário, veja a Parte 7 (conflitos).

### 5.4 Apagar branch já mesclado

```bash
git branch -d revisao-2
```

---

## Parte 6 – Repositórios remotos

### 6.1 Criar o repositório no GitHub

1. No GitHub, clique em **+** → **New repository**.
2. Dê um nome, escolha público ou privado e **não** marque "Add a README" (o projeto local já tem histórico).
3. Copie a URL SSH (`git@github.com:usuario/nome.git`).

### 6.2 Conectar o local ao remoto: `git remote`

```bash
git remote add origin git@github.com:usuario/meu-artigo.git
git remote -v                       # confere as URLs
```

### 6.3 Enviar: `git push`

```bash
git branch -M main                  # garante que o branch se chama main
git push -u origin main             # envia e define o upstream (só na primeira vez)
```

Depois disso, basta `git push`.

### 6.4 Baixar: `git fetch` e `git pull`

```bash
git fetch origin                    # baixa as informações sem alterar seus arquivos
git pull                            # fetch + merge do branch atual
```

### 6.5 Clonar um repositório existente: `git clone`

```bash
git clone git@github.com:usuario/repo.git
cd repo
```

Para clonar em uma pasta com outro nome: `git clone <url> minha-pasta`.

---

## Parte 7 – `.gitignore`, desfazer e conflitos

### 7.1 Ignorar arquivos: `.gitignore`

Crie um arquivo chamado `.gitignore` na raiz do projeto. Para projetos LaTeX, um exemplo é:

```gitignore
# Arquivos gerados pelo LaTeX
*.aux
*.log
*.out
*.toc
*.bbl
*.blg
*.synctex.gz
*.fls
*.fdb_latexmk

# PDF compilado (opcional; remova esta linha se quiser versionar o PDF)
*.pdf
```

Arquivos já versionados não são ignorados retroativamente. Para parar de versionar um arquivo que já está no repositório: `git rm --cached arquivo`.

### 7.2 Desfazer alterações

```bash
git restore arquivo.tex             # descarta alterações não preparadas (CUIDADO: perde o trabalho)
git restore --staged arquivo.tex    # tira do git add, mantém a alteração
git commit --amend -m "Nova msg"    # corrige a mensagem do último commit (ainda não enviado)
git revert <hash>                   # cria um commit que desfaz outro, sem apagar o histórico
```

### 7.3 Conflitos

Conflito acontece quando duas pessoas (ou dois branches) alteram as mesmas linhas. O Git marca o arquivo assim:

```
<<<<<<< HEAD
Texto da sua versão
=======
Texto da outra versão
>>>>>>> revisao-2
```

Para resolver: edite o arquivo mantendo o texto correto, remova as marcações, depois:

```bash
git add arquivo.tex
git commit
```

---

## Parte 8 – Fluxo de trabalho para um artigo

Rotina recomendada:

```bash
git pull                                  # 1. atualiza antes de começar
git switch -c secao-resultados            # 2. branch para a tarefa
# ... escreva e compile o LaTeX ...
git status                                # 3. confira o que mudou
git add -p                                # 4. escolha trechos (ou git add arquivo.tex)
git commit -m "Escreve resultados da tabela 2"
git push -u origin secao-resultados       # 5. envia o branch
git switch main && git merge secao-resultados   # 6. integra
git push                                  # 7. envia a main atualizada
```

Boas práticas:

- Commits pequenos e frequentes, com mensagem clara.
- Um assunto por branch.
- Nunca faça `git push --force` na branch compartilhada.
- Versione o `.tex`, `.bib` e figuras-fonte; ignore arquivos temporários.

---

## Cola rápida de comandos

| Ação | Comando |
|------|---------|
| Configurar nome | `git config --global user.name "Seu Nome"` |
| Configurar e-mail | `git config --global user.email "seu-email@exemplo.com"` |
| Criar repositório | `git init` |
| Clonar | `git clone <url>` |
| Ver estado | `git status` |
| Preparar arquivo | `git add <arquivo>` |
| Commitar | `git commit -m "mensagem"` |
| Ver histórico | `git log --oneline --graph` |
| Ver diferenças | `git diff` / `git diff --staged` |
| Listar branches | `git branch` |
| Criar branch | `git branch <nome>` |
| Trocar de branch | `git switch <nome>` |
| Criar e trocar | `git switch -c <nome>` |
| Mesclar branch | `git merge <nome>` |
| Conectar remoto | `git remote add origin <url>` |
| Enviar | `git push -u origin <branch>` |
| Baixar e integrar | `git pull` |
| Baixar sem integrar | `git fetch` |
| Testar SSH | `ssh -T git@github.com` |
