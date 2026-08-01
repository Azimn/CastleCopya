#!/usr/bin/env python3
"""Validate a Game Boy ROM before publishing it for playtesting."""

from __future__ import annotations

import argparse
import hashlib
from pathlib import Path

NINTENDO_LOGO = bytes.fromhex(
    "CEED6666CC0D000B03730083000C000D"
    "0008111F8889000EDCCC6EE6DDDDD999"
    "BBBB67636E0EECCCDDDC999FBBB9333E"
)


def header_checksum(data: bytes) -> int:
    value = 0
    for byte in data[0x134:0x14D]:
        value = (value - byte - 1) & 0xFF
    return value


def global_checksum(data: bytes) -> int:
    return (sum(data) - data[0x14E] - data[0x14F]) & 0xFFFF


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("rom", type=Path)
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()

    data = args.rom.read_bytes()
    failures: list[str] = []

    if len(data) < 0x150:
        failures.append("ROM is smaller than the minimum Game Boy header size")
    else:
        if len(data) % 0x4000 != 0:
            failures.append("ROM size is not aligned to a 16 KiB bank boundary")
        if data[0x104:0x134] != NINTENDO_LOGO:
            failures.append("Nintendo logo bytes are invalid")

        expected_header = data[0x14D]
        calculated_header = header_checksum(data)
        if expected_header != calculated_header:
            failures.append(
                f"Header checksum mismatch: stored {expected_header:02X}, calculated {calculated_header:02X}"
            )

        expected_global = (data[0x14E] << 8) | data[0x14F]
        calculated_global = global_checksum(data)
        if expected_global not in (0, calculated_global):
            failures.append(
                f"Global checksum mismatch: stored {expected_global:04X}, calculated {calculated_global:04X}"
            )

    title = data[0x134:0x144].split(b"\0", 1)[0].decode("ascii", errors="replace") if len(data) >= 0x144 else ""
    report = "\n".join(
        [
            f"ROM: {args.rom.name}",
            f"Title: {title}",
            f"Size: {len(data)} bytes ({len(data) // 0x4000} banks)",
            f"Cartridge type: 0x{data[0x147]:02X}" if len(data) > 0x147 else "Cartridge type: unavailable",
            f"ROM size code: 0x{data[0x148]:02X}" if len(data) > 0x148 else "ROM size code: unavailable",
            f"RAM size code: 0x{data[0x149]:02X}" if len(data) > 0x149 else "RAM size code: unavailable",
            f"SHA-256: {hashlib.sha256(data).hexdigest()}",
            f"Validation: {'FAIL' if failures else 'PASS'}",
            *[f"Failure: {failure}" for failure in failures],
        ]
    ) + "\n"

    print(report, end="")
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(report, encoding="utf-8")

    return 1 if failures else 0


if __name__ == "__main__":
    raise SystemExit(main())
