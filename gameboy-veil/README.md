# Veil of Neverwinter Game Boy Integration

This branch stages the Game Boy Color version of Veil of Neverwinter on top of TheGreatGallus/Cavern-GB.

The build workflow fetches the pinned Cavern-GB commit `f412101f0d29e402f2975ab8f04ef50740de9b33`, applies files from `gameboy-veil/overlay/`, builds with GBDK-2020 through the bundled modified ZGB engine, and uploads the resulting ROM as a GitHub Actions artifact.

## Foundation strategy

Cavern supplies the executable action foundation: scrolling rooms, collision, player movement, jumping, double jump, wall grip, shrinking, dash behavior, melee attacks, beam attacks, enemies, projectiles, bosses, upgrades, save points, HUD behavior, animation, music, and sound effects.

The Veil prototype supplies campaign content and higher-level state: twelve missions, character identity tags, deterministic checks, companion trust, faction reputation, consequential choices, side-quest returns, modular epilogues, and validation requirements.

Yurivania 1 and 2 are secondary donors for interaction structure, NPC-heavy exploration, inventory puzzles, maps, and compact quest presentation. No imported file should be described as integrated until it appears in `THIRD_PARTY_LEDGER.csv` with its exact source and destination.

## Current milestone

The first milestone is deliberately conservative: reproduce an unmodified, buildable Cavern ROM from a pinned upstream commit. Once that artifact is verified, Veil systems will be introduced through small overlay commits so regressions can be isolated.

## Build

Run the `Build Veil Game Boy Foundation` GitHub Actions workflow. The downloadable artifact is named `veil-cavern-gameboy-build`.

## Repository note

This branch currently lives in `Azimn/CastleCopya` only because the connected GitHub tool cannot create a new repository. The Game Boy work is isolated under `gameboy-veil/` and its own workflow so it can be moved into a dedicated repository without carrying over the Godot project.
