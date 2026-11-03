#!/bin/sh
# Program customer-key.cip into a sama7d65 Curiosity Pro in secure boot
# emulation mode. Run from anywhere; the key payload is taken from the
# directory this script lives in. Each sam-ba command is retried after one
# second until it succeeds, up to SAMBA_RETRIES attempts (default 10).

set -e

cd "$(dirname "$0")"

SAMBA_RETRIES="${SAMBA_RETRIES:-10}"

run() {
    n=1
    until sam-ba "$@"; do
        if [ "$n" -ge "$SAMBA_RETRIES" ]; then
            echo "sam-ba $*: failed after $n attempts" >&2
            exit 1
        fi
        echo "sam-ba $*: failed, retrying in 1 second ($n/$SAMBA_RETRIES)" >&2
        n=$((n + 1))
        sleep 1
    done
}

if [ ! -f customer-key.cip ]; then
    echo "customer-key.cip not found in $(pwd)" >&2
    exit 1
fi

run -p serial -d sama7d65 -a bootconfig -c writecfg:bscr:EMULATION_ENABLED
run -p serial -d sama7d65 -a bootconfig -c resetemul
run -p serial -d sama7d65 -a reset
run -p serial -d sama7d65 -a bootconfig -c writecfg:sbcp-emul:SECURE_BOOT_ENABLED
run -p serial -b sama7d65-curiosity -a reset
run -p secure -d sama7d65 -m write_customer_key_payload:customer-key.cip
