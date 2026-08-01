# Veil of Neverwinter First Playtest

## Build under test

Use the ROM from the `veil-of-neverwinter-playtest` GitHub Actions artifact. Keep the included validation report, screenshots, checksum file, licenses, and manifests with the ROM so the exact build remains identifiable.

## Supported emulators

The automated smoke test uses PyBoy. Human testing should also be performed in SameBoy or BGB, then on original Game Boy Color hardware or an accurate FPGA implementation when available. Do not treat browser-only behavior as hardware validation.

## Controls

The Cavern controller remains active during action play. The directional pad moves. A jumps and confirms. B attacks and backs out of Veil interfaces. START opens or closes the Veil menu. During dialogue, Up and Down change the selected response and A confirms it.

## Required mission route

Begin a new game and confirm that the player can move, jump, attack, take damage, change rooms, and return without a crash. In room 1, enter the eastern Blacklake objective zone and confirm that `CULT CELL FOUND` appears. Open the Journal and confirm that the objective changes to `SPEAK WITH VAELITH`.

Approach the Vaelith interaction zone and confirm that `A TALK` appears only while nearby. Open the conversation, advance to the decision, select public recruitment, and confirm that the dialogue completes. Open the Companion page and confirm that Vaelith is marked public and her trust increased. Return to the western gate and confirm that the mission-complete notice appears and the Journal advances.

Reset the save and repeat the mission using concealed recruitment. Confirm that the alternate dialogue appears, the Companion page reports concealed status, and the mission still completes. Reopen Vaelith dialogue after deciding and confirm that trust and faction values cannot be farmed by repeating the conversation.

## Interface checks

Open and close the Veil menu from standing, jumping, near an enemy, near Vaelith, and after the objective notice. Confirm that gameplay pauses while the menu or dialogue is visible, that the original Cavern HUD returns afterward, and that no stale text remains on the window layer.

Visit Map, Inventory, Companion, Journal, Controls, and Save. Confirm that cursor wrapping works in both directions, B closes safely, and the campaign-dependent pages reflect the current mission flags.

## Stability checks

Play for at least fifteen minutes while repeatedly moving between rooms, fighting enemies, opening the menu, and talking to Vaelith. Watch for softlocks, disappearing sprites, corrupted tiles, audio lockups, delayed input, invalid room transitions, or unexpected resets.

Save at a Cavern save point, reset the emulator, and reload. Confirm that the original Cavern position, upgrades, and health progression survive. Veil campaign SRAM persistence is not yet complete, so separately record whether campaign flags survive. A failure here is expected until the expanded save block is connected, but it must not corrupt Cavern's existing save data.

## Evidence to retain

For every defect, retain the ROM checksum, emulator and version, save file when relevant, exact room number, player coordinates if known, input sequence, expected result, actual result, and a screenshot or short recording. Classify the defect as build failure, crash, softlock, progression block, save corruption, visual defect, audio defect, input defect, performance issue, or text issue.

## Exit criteria

This build is ready for broader playtesting only after the ROM passes automated header validation, boots through the emulator smoke test, completes both M01 recruitment routes, survives reset and room traversal without corruption, preserves Cavern saves, and has no known progression-blocking defect in the Blacklake sequence.
