"""Embed the display-sized PNG icons in the firmware."""

from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
ICONS = ("x", "github", "peachtech")
output = ["#pragma once", "", "#include <stdint.h>", ""]

for name in ICONS:
    data = (ROOT / "assets" / "icons" / f"{name}.png").read_bytes()
    output.append(f"static const uint8_t icon_{name}[] = {{")
    for offset in range(0, len(data), 12):
        values = ", ".join(f"0x{byte:02x}" for byte in data[offset : offset + 12])
        output.append(f"    {values},")
    output.extend(
        (
            "};",
            f"static constexpr unsigned int icon_{name}_size = sizeof(icon_{name});",
            "",
        )
    )

(ROOT / "src" / "apps" / "qr_manager" / "icons.h").write_text("\n".join(output))
