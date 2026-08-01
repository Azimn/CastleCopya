# Yurivania 2 Integration Plan

## Source lock

The integration source is `mxashlynn/Yurivania-2` at commit `e95a78c86184b0185769249feb327240d1a6e980`.

The uploaded archive contains 312 files: 165 PNG graphics, 54 TMX maps, 33 C files, 28 headers, 7 assembly files, 7 MOD music tracks, 5 TSX tilesets, one GB Studio project, design notes, scripts, and distribution material.

## License handling

Yurivania 2 permits use, study, copying, merging, embedding, modification, redistribution, and sale of modified copies, provided the licensed files are not sold by themselves and the copyright notice and license remain included. Any Yurivania-derived files distributed with Veil remain under the Yurivania 2 license. Paige Ashlynn's name may be used only for attribution, not endorsement. The source may not be used for machine-learning training or included in training datasets.

The full upstream `LICENSE.txt` must remain in the final source and distribution notices whenever any Yurivania-derived component is present.

## Systems selected for study or adaptation

The project contains a complete GB Studio engine snapshot with actor, bank, camera, collision, data, input, music, palette, projectile, script, scroll, sprite, trigger, UI, and state modules. These are not dropped directly into ZGB because their runtime model differs from Cavern. They will be treated as implementation donors and ported behind Veil interfaces where useful.

Priority systems are the menu and inventory flow, world map presentation, NPC conversation staging, trigger organization, resource gathering and choice state, palette management, music routing, and compact scene organization.

## Assets selected for temporary integration

The first temporary asset pool includes the ASCII font, dialogue frame, cursor, map marker, checkmark, pause and prompt effects, inventory icons, seven MOD tracks, and selected environment tiles or backgrounds that can be retiled without confusing the setting.

Character-specific Yurivania portraits, narrative scenes, names, dialogue, and distinctive finished locations are excluded from direct Veil use unless deliberately transformed and separately logged. Generic UI, environmental materials, effects, and technical assets have the highest reuse value.

## Conversion boundary

Cavern remains the executable ZGB foundation. Yurivania PNG and MOD resources will be copied into a staging area by CI, then converted or referenced through explicit Veil adapters. No upstream file is silently overwritten. Every incorporated file receives a ledger entry with source path, destination, modification notes, checksum, and replacement priority.

## First implementation sequence

1. Preserve Yurivania 2 and its license at a pinned commit.
2. Generate a complete SHA-256 vendor manifest.
3. Port the dialogue frame, cursor, ASCII font, map marker, and inventory icon conventions into a Veil UI resource bank.
4. Add a pause menu with Map, Inventory, Companion, Journal, Controls, and Save entries.
5. Add a compact world-map state inspired by Yurivania's map screen but populated with Veil mission regions.
6. Route one temporary MOD track through Cavern's music system for the M01 Blacklake district.
7. Add NPC interaction triggers and conversation presentation around the first Cavern room conversion.
8. Validate ROM size, bank use, sprite limits, and SRAM compatibility after each imported group.

## Replacement policy

All imported material is acceptable for the free noncommercial build when its license and attribution are preserved. Assets marked `replace-later` are production placeholders that should eventually receive Veil-specific redraws or compositions. Code ports may remain when their provenance and license are retained.
