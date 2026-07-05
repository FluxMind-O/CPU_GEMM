#!/bin/bash
set -e

# run_nsys.sh - 自动化抓取 nsys profile 的脚本
# 用法: ./scripts/run_nsys.sh <可执行文件> [额外参数]

EXECUTABLE=$1
shift

if [ -z "$EXECUTABLE" ]; then
    echo "Usage: $0 <executable> [args...]"
    exit 1
fi

OUTPUT_DIR="nsys-rep"
mkdir -p "$OUTPUT_DIR"

TIMESTAMP=$(date +%Y%m%d_%H%M%S)
REPORT_NAME="${OUTPUT_DIR}/report_${TIMESTAMP}"

echo "Running nsys profile for: $EXECUTABLE"
nsys profile --output="$REPORT_NAME" "$EXECUTABLE" "$@"

echo "Report saved to: ${REPORT_NAME}.nsys-rep"
