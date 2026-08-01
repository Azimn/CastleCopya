from pathlib import Path

path = Path("upstream-cavern/Cavern/src/StateGame.c")
text = path.read_text(encoding="utf-8")

include_anchor = '#include "Math.h"\n'
include_block = '#include "Math.h"\n#include "VeilRuntime.h"\n'
if '#include "VeilRuntime.h"' not in text:
    if include_anchor not in text:
        raise SystemExit("StateGame include anchor not found")
    text = text.replace(include_anchor, include_block, 1)

start_anchor = 'void Start_StateGame() {\n'
if 'VeilRuntime_Init();' not in text:
    if start_anchor not in text:
        raise SystemExit("Start_StateGame anchor not found")
    text = text.replace(start_anchor, start_anchor + '\tVeilRuntime_Init();\n', 1)

update_anchor = 'void Update_StateGame() {\n'
if 'if (VeilRuntime_Update())' not in text:
    if update_anchor not in text:
        raise SystemExit("Update_StateGame anchor not found")
    text = text.replace(
        update_anchor,
        update_anchor + '\tif (VeilRuntime_Update()) {\n\t\treturn;\n\t}\n',
        1,
    )

path.write_text(text, encoding="utf-8")
print("Patched Cavern StateGame.c with Veil runtime hooks")
