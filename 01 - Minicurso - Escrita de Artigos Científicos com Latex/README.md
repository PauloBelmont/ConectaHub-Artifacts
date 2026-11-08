> Parte do material do minicurso "Minicurso: Escrita de Artigos Científicos com LaTeX" (Conecta Hub)
# Minicurso – Escrita de Artigos Científicos com LaTeX

Templates simples, organizados do básico ao artigo completo. Cada pasta tem um `main.tex` que pode ser compilado sozinho.

| Pasta | Assunto |
|-------|---------|
| `01-basico` | Estrutura mínima de um documento `.tex` |
| `02-texto-formatacao` | Seções, listas, ênfase, caracteres especiais |
| `03-matematica` | Equações inline, em destaque e alinhadas |
| `04-figuras-tabelas` | Tabelas e figuras com legenda e referência cruzada |
| `05-referencias-bibtex` | Bibliografia com BibTeX (`referencias.bib`) |
| `06-artigo-modelo` | Modelo de artigo científico completo |

## Como compilar

Com um editor como Overleaf (recomendado para iniciantes) ou localmente:

```bash
pdflatex main.tex
```

Para as pastas com bibliografia (`05` e `06`), a sequência completa é:

```bash
pdflatex main.tex
bibtex main
pdflatex main.tex
pdflatex main.tex
```

Dica: no Overleaf basta clicar em **Recompile**; ele executa tudo automaticamente.
