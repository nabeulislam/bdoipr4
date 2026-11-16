#!/usr/bin/env bash

set -euo pipefail

script_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
data_file="${1:-${script_dir}/gen/data}"
output_file="${2:-${script_dir}/polygon.script}"

if [[ ! -f "${data_file}" ]]; then
    printf 'Error: generator data not found: %s\n' "${data_file}" >&2
    exit 1
fi

manual_count="$(awk '$1 == "manual" { count++ } END { print count + 0 }' "${data_file}")"
first_generated_index=$((manual_count + 1))
output_dir="$(dirname -- "${output_file}")"
mkdir -p "${output_dir}"

temporary_output="$(mktemp "${output_file}.tmp.XXXXXX")"
cleanup() {
    rm -f -- "${temporary_output}"
}
trap cleanup EXIT

awk -v first_index="${first_generated_index}" '
    NF && $1 !~ /^@/ && $1 != "manual" && $1 !~ /^#/ {
        print $0 " > " first_index + generated_count
        generated_count++
    }
' "${data_file}" > "${temporary_output}"

generated_count="$(wc -l < "${temporary_output}")"
last_index=$((first_generated_index + generated_count - 1))

awk -v first_index="${first_generated_index}" '
    { if ($NF != first_index + NR - 1) exit 1 }
' "${temporary_output}"

mv -- "${temporary_output}" "${output_file}"
trap - EXIT

printf 'Generated %s: %s generated tests, targets %s..%s; %s manual test(s) reserved.\n' \
    "${output_file}" "${generated_count}" "${first_generated_index}" "${last_index}" "${manual_count}"
