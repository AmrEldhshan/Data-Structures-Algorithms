#!/usr/bin/env bash
#
# Compile every header on its own. This catches missing includes and
# broken include guards before they surprise a learner.
#
# Usage: scripts/check_headers.sh <repo-root> <c++-compiler>

set -euo pipefail

root="${1:?repo root required}"
compiler="${2:?c++ compiler required}"

tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT

failed=0

while IFS= read -r -d '' header; do
    rel="${header#"$root"/src/}"
    printf '#include "%s"\nint main() { return 0; }\n' "$rel" > "$tmp/check.cpp"
    if ! "$compiler" -std=c++20 -I"$root/src" -fsyntax-only "$tmp/check.cpp"; then
        echo "FAIL: $rel"
        failed=1
    fi
done < <(find "$root/src" -name '*.h' -print0 | sort -z)

if [[ $failed -eq 0 ]]; then
    echo "All headers compile independently."
fi

exit $failed
