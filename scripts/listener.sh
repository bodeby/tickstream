#!/usr/bin/env bash

set -euo pipefail

echo "Listening on UDP port 5000..."

exec socat -u UDP4-RECV:5000 STDOUT
