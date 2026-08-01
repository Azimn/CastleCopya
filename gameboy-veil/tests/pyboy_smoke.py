#!/usr/bin/env python3
"""Boot the playtest ROM in PyBoy and capture deterministic smoke-test evidence."""

from __future__ import annotations

import argparse
from pathlib import Path

from pyboy import PyBoy


def run_frames(pyboy: PyBoy, count: int) -> None:
    for _ in range(count):
        if not pyboy.tick(render=False):
            raise RuntimeError("Emulator stopped before the smoke test completed")


def tap(pyboy: PyBoy, button: str, hold_frames: int = 2) -> None:
    pyboy.button_press(button)
    run_frames(pyboy, hold_frames)
    pyboy.button_release(button)
    run_frames(pyboy, 8)


def save_frame(pyboy: PyBoy, path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    pyboy.screen.image.save(path)


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("rom", type=Path)
    parser.add_argument("--output", type=Path, default=Path("playtest-evidence"))
    args = parser.parse_args()

    pyboy = PyBoy(str(args.rom), window="null", sound_emulated=False)
    try:
        run_frames(pyboy, 240)
        save_frame(pyboy, args.output / "01_boot.png")

        tap(pyboy, "start")
        run_frames(pyboy, 90)
        save_frame(pyboy, args.output / "02_after_start.png")

        tap(pyboy, "start")
        run_frames(pyboy, 30)
        tap(pyboy, "right", 20)
        tap(pyboy, "a")
        run_frames(pyboy, 120)
        save_frame(pyboy, args.output / "03_gameplay.png")

        tap(pyboy, "start")
        run_frames(pyboy, 30)
        save_frame(pyboy, args.output / "04_veil_menu.png")

        tap(pyboy, "down")
        tap(pyboy, "down")
        tap(pyboy, "down")
        tap(pyboy, "a")
        run_frames(pyboy, 30)
        save_frame(pyboy, args.output / "05_journal.png")

        if pyboy.frame_count < 500:
            raise RuntimeError("Unexpectedly short emulator run")
    finally:
        pyboy.stop(save=False)

    print(f"PyBoy smoke test passed through frame {pyboy.frame_count}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
