#!/usr/bin/env bash
# Roda todos os exemplos com as opções do Map2Check adequadas a cada caso.
# Uso: ./run_all.sh /caminho/para/pasta-do-map2check
# Requer Linux 64 bits (ou WSL2). Variável opcional: TIMEOUT (segundos, padrão 60).

set -u

M2C_DIR="${1:?Informe a pasta de instalação do Map2Check}"
TIMEOUT="${TIMEOUT:-60}"
HERE="$(cd "$(dirname "$0")" && pwd)"

if [ ! -x "$M2C_DIR/map2check" ]; then
    echo "Não encontrei o executável em: $M2C_DIR/map2check" >&2
    exit 1
fi

run() {
    local file="$1" flags="$2"
    echo "=== $(basename "$(dirname "$file")")/$(basename "$file")  (opções: $flags)"
    (cd "$M2C_DIR" && ./map2check $flags --timeout "$TIMEOUT" "$file") 2>&1 \
        | grep -E "VERIFICATION|Violated property" -A1 | head -6
    echo
}

for f in "$HERE"/01-asserts/*.c;     do run "$f" "--check-asserts"; done
for f in "$HERE"/02-overflow/*.c;    do run "$f" "--check-overflow"; done
for f in "$HERE"/03-limites-de-vetor/*.c "$HERE"/04-use-after-free/*.c; do
    run "$f" "--memtrack"
done
