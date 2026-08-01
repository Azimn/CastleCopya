#!/usr/bin/env bash
set -euo pipefail

Y2_REPO="https://github.com/mxashlynn/Yurivania-2.git"
Y2_COMMIT="e95a78c86184b0185769249feb327240d1a6e980"
DEST="${1:-vendor/yurivania2}"

rm -rf "$DEST"
git clone --filter=blob:none "$Y2_REPO" "$DEST"
git -C "$DEST" checkout "$Y2_COMMIT"

mkdir -p gameboy-veil/vendor-manifests
find "$DEST" -type f -print0 \
  | sort -z \
  | xargs -0 sha256sum \
  > gameboy-veil/vendor-manifests/yurivania2.sha256

{
  echo "repository=mxashlynn/Yurivania-2"
  echo "commit=$Y2_COMMIT"
  echo "license=$DEST/LICENSE.txt"
  echo "file_count=$(find "$DEST" -type f | wc -l | tr -d ' ')"
} > gameboy-veil/vendor-manifests/yurivania2.properties
