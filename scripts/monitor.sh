#!/usr/bin/env bash

set -euo pipefail

echo "Monitoring TCP/UDP dump..."

exec sudo tcpdump -i lo -nn udp port 5000
