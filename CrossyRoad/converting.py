from PIL import Image

def convert_to_bmp(input_path, output_path):
    try:
        # Open the image file
        img = Image.open(input_path)

        # Save as BMP
        img.save(output_path, "BMP")

        print(f"Image saved as {output_path}")
    except Exception as e:
        print(f"Error: {e}")

# Example usage
# Replace "input.jpg" with the path to your input image
# Replace "output.bmp" with the desired output BMP file path
convert_to_bmp("20231116_crossyroad-02.png", "NEWGAME.bmp")