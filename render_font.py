#!/usr/bin/env python3
"""
Рендерит каждый символ строки из TTF-шрифта в отдельные PNG-файлы.

Использование:
    python render_font.py <font.ttf> <размер_px> "<символы>" <выходная_папка>

Пример:
    python render_font.py tahoma.ttf 32 "abc" ./font
    # создаст:
    #   ./font/a_tahoma_32px.png
    #   ./font/b_tahoma_32px.png
    #   ./font/c_tahoma_32px.png
"""

import argparse
import os
import sys
from typing import Optional

from PIL import Image, ImageDraw, ImageFont


def safe_filename(char: str) -> str:
    """Возвращает безопасное для файловой системы имя для символа."""
    if char.isnumeric() == True:
        return char
    char_num = ord(char)
    if ord('a') <= char_num <= ord('z'):
        return f"{char}_low"
    if ord('A') <= char_num <= ord('Z'):
        return f"{char}_up"
    # Для не-буквенно-цифровых символов используем Unicode-код,
    # т.к. многие из них (например, '/', ':', '?') недопустимы в имени файла.
    return f"u{char_num:04X}"
    
    


def render_char(char: str, font: ImageFont.FreeTypeFont) -> Optional[Image.Image]:
    """
    Рендерит один символ в RGBA-изображение.
    Высота холста фиксирована (ascent + descent) и одинакова для всех символов,
    ширина — по видимой части глифа.
    """
    ascent, descent = font.getmetrics()
    height = ascent + descent

    bbox = font.getbbox(char)
    if bbox is None:
        return None

    left, _, right, _ = bbox
    width = right - left
    if width <= 0:
        return None  # пробел / пустой глиф

    img = Image.new("RGBA", (width, height), (0xff, 0xff, 0xff, 0xff))
    draw = ImageDraw.Draw(img)

    # Сдвигаем по X, чтобы левая граница глифа легла в x=0.
    # По Y оставляем 0 — тогда baseline окажется на y=ascent у всех символов,
    # а значит все изображения будут "стоять" на одной линии.
    draw.text((-left, 0), char, font=font, fill=(0, 0, 0, 255))
    return img


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(
        description="Рендерит символы TTF-шрифта в отдельные PNG-файлы."
    )
    parser.add_argument("font", help="путь к .ttf файлу шрифта")
    parser.add_argument("size", type=int, help="размер шрифта в пикселях")
    parser.add_argument("chars", help="строка символов для рендеринга")
    parser.add_argument("output", help="выходная папка")
    
    args = parser.parse_args(argv)
    print(args.font)
    print(args.size)
    print(args.chars)
    print(args.output)

    if not os.path.isfile(args.font):
        print(f"Ошибка: файл шрифта не найден: {args.font}", file=sys.stderr)
        return 1

    os.makedirs(args.output, exist_ok=True)

    font_name = os.path.splitext(os.path.basename(args.font))[0]

    try:
        font = ImageFont.truetype(args.font, args.size)
    except OSError as e:
        print(f"Ошибка загрузки шрифта: {e}", file=sys.stderr)
        return 1

    # Убираем дубликаты, сохраняя порядок
    chars = list(dict.fromkeys(args.chars))

    for char in chars:
        img = render_char(char, font)
        if img is None:
            print(f"Пропущен {char!r}: нет видимого глифа")
            continue

        filename = f"{safe_filename(char)}_{font_name}_{args.size}px.png"
        filepath = os.path.join(args.output, filename)
        img.save(filepath)
        print(f"Сохранён {filepath}")

    return 0


if __name__ == "__main__":
    str_for_font = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя0123456789+-=!?.,"
    fonts = [
        "russo_one",
        "tahoma"
    ]
    for f in fonts:
        main([f"./fonts/{f}.ttf", "32", str_for_font, f"./cip/{f}"])
    sys.exit(0)