import io

from PIL import Image, ImageDraw, ImageFont, features

assert features.check("zlib")
assert features.check("libtiff")
assert features.check("freetype2")

font = ImageFont.load_default(size=12)
assert isinstance(font, ImageFont.FreeTypeFont)

image = Image.new("RGB", (64, 48), (10, 20, 30))
draw = ImageDraw.Draw(image)
draw.rectangle((8, 8, 40, 30), fill=(200, 100, 50), outline=(255, 255, 255))
draw.text((4, 32), "Pillow", font=font, fill=(255, 255, 0))
assert image.getpixel((20, 20)) == (200, 100, 50)

for image_format, save_options in (("PNG", {}), ("TIFF", {"compression": "tiff_lzw"})):
    buffer = io.BytesIO()
    image.save(buffer, format=image_format, **save_options)
    buffer.seek(0)
    with Image.open(buffer) as loaded:
        loaded.load()
        assert loaded.format == image_format
        assert loaded.size == image.size
        assert loaded.tobytes() == image.tobytes(), image_format
