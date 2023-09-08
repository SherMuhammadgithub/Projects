from PIL import Image

def convert_jpg_to_png(input_path, output_path):
    try:
        image = Image.open(input_path)
        if image.mode != 'RGBA':
            image = image.convert('RGBA')
        output_path_with_extension = output_path if output_path.lower().endswith('.png') else output_path + '.png'
        image.save(output_path_with_extension, format='PNG')
        print(f"Converted {input_path} to {output_path_with_extension}")
    except Exception as e:
        print(f"Error converting {input_path}: {e}")

if __name__ == "__main__":
    input_file = "player.jpg"  # Change this to your input JPG file path
    output_file = "player.png"  # Change this to your output PNG file path

    convert_jpg_to_png(input_file, output_file)
