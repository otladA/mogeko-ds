#!/usr/bin/env bash

set -euo pipefail

img="${1:?Use: reduce_colors.sh <image.png>}"

convert "$img" -colors 255 -dither none PNG8:"$img"
echo "OK: $(identify -format '%k colors\n' "$img")"