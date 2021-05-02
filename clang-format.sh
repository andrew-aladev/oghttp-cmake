#!/usr/bin/env bash
set -e

DIR=$(dirname "${BASH_SOURCE[0]}")
cd "$DIR"

find "checks" "generators" "src" \( -name "*.h" -o -name "*.c" \) -exec clang-format -i {} \;
