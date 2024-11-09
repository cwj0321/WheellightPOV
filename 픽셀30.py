from PIL import Image

image = Image.open(r"C:\Users\최웅준\OneDrive\바탕 화면\사랑해.jpg")

rgb_image = image.convert('RGB')

width, height = rgb_image.size

x_step = width//30

neo_pixel_30 = [[] for _ in range(8)]

for i in range(30):
    x_start = i * x_step
    x_end = (i+1) * x_step if i<29 else width

    for neo_pixel_index in range(8):
        y_position = (neo_pixel_index*height)//8
        r,g,b=rgb_image.getpixel((x_start+(x_end-x_start)//2,y_position))

        neo_pixel_30[neo_pixel_index].append((r,g,b))

with open('neo_pixel_30.txt', 'w') as file:
    for neo_pixel_index, colors in enumerate(neo_pixel_30):
        file.write(f'NeoPixel {neo_pixel_index+1} Colors:\n')
        for idx, color in enumerate(colors):
            file.write(f'  Column {idx+1}: R={color[0]}, G={color[1]}, B={color[2]}\n')
        file.write('\n')
    
