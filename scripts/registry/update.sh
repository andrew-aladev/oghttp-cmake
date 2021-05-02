#!/usr/bin/env bash
set -e

DIR=$(dirname "${BASH_SOURCE[0]}")
cd "$DIR"

cd "../../registry"

wget "https://www.iana.org/assignments/http-status-codes/http-status-codes.xml" \
  -O "http-status-codes.xml"

wget "https://www.iana.org/assignments/http-warn-codes/http-warn-codes.xml" \
  -O "http-warn-codes.xml"

wget "https://www.iana.org/assignments/message-headers/message-headers.xml" \
  -O "message-headers.xml"
