# Veil of Neverwinter Cavern Integration Status

## Current milestone

The branch now contains the first compile-targeted Veil overlay for the pinned Cavern-GB foundation.

Implemented in the overlay:

- Versioned campaign state for twelve missions.
- Race, class, narrative approach, background, and active companion fields.
- Nine independent companion trust values stored in four-bit ranges.
- Eight faction reputation values stored in signed compact ranges.
- Structural story and side-quest flags.
- Save-state checksum and validation routines.
- Data-driven scene, condition, option, and effect records.
- M01 public or secret Vaelith rescue branch.
- Dwarf, Rogue, and Noble conditional routes in the M01 shell.
- Trust, faction, story flag, and mission progression effects.

## Foundation retained from Cavern

The build continues to use Cavern's existing player movement, jumping, upgrades, melee attack, beam attack, enemies, bosses, collision, rooms, HUD, save points, graphics, animation, music, and sound systems.

## Next milestone

The next milestone is to connect the Veil campaign initialization and M01 scene runner to Cavern's main menu and first playable room, then extend SRAM saving without breaking Cavern's existing save data. After that, the first room will be converted into Ashes in Blacklake using documented temporary art and audio assets.

## Verification state

The source overlay and CI build workflow are committed. A playable Veil ROM is not considered verified until the GitHub Actions job completes and publishes a ROM artifact.
