from PIL import Image

image = Image.open("CR_background.jpg")
width, height = image.size

with open("image.txt", "w") as color_file:
    for y in range(height):
        for x in range(width):
            pixel = image.getpixel((x, y))
            hex_color = "#{:02X}{:02X}{:02X}".format(pixel[0], pixel[1], pixel[2])
            color_file.write(hex_color + " ")

        color_file.write("\n") 
