from PIL import Image

image = Image.open(r"C:\Users\최웅준\OneDrive\바탕 화면\사랑해.jpg")

rgb_image = image.convert('RGB')

width, height = rgb_image.size

x_step = width // 60

neo_pixel_love = [[] for _ in range(8)]

for i in range(60):
    x_start = i * x_step
    x_end = (i + 1) * x_step if i < 60 else width
    
    for neo_pixel_index in range(8):
        y_position = (neo_pixel_index * height) // 8
        r, g, b = rgb_image.getpixel((x_start + (x_end - x_start) // 2, y_position))
        
        neo_pixel_love[neo_pixel_index].append((r, g, b))

with open('neo_pixel_love.txt', 'w') as file:
    for neo_pixel_index, colors in enumerate(neo_pixel_love):
        file.write(f'NeoPixel {neo_pixel_index+1} Colors:\n')
        for idx, color in enumerate(colors):
            file.write(f'  Column {idx+1}: R={color[0]}, G={color[1]}, B={color[2]}\n')
        file.write('\n')

def convert_to_arduino_format(input_file, output_file):
    with open(input_file, "r") as file:
        lines = file.readlines()

    # 네오픽셀 데이터 저장용 리스트
    neo_pixel_love = [[] for _ in range(8)]

    # 데이터를 처리하여 각 네오픽셀의 컬러 값을 리스트에 저장
    current_pixel = -1
    for line in lines:
        if "NeoPixel" in line:  # 네오픽셀 번호 찾기
            current_pixel += 1
        elif "Column" in line:  # 컬러 데이터 처리
            parts = line.strip().split(":")[1].split(",")
            r = int(parts[0].split("=")[1])
            g = int(parts[1].split("=")[1])
            b = int(parts[2].split("=")[1])
            neo_pixel_love[current_pixel].append([r, g, b])

    # 아두이노 배열 형식으로 변환하여 출력
    with open(output_file, "w") as file:
        file.write("uint8_t colors[8][60][3] = {\n")
        for i, pixel_data in enumerate(neo_pixel_love):
            file.write("  {")
            for j, color in enumerate(pixel_data):
                file.write(f"{{{color[0]}, {color[1]}, {color[2]}}}")
                if j < len(pixel_data) - 1:
                    file.write(", ")
            file.write("}")
            if i < len(neo_pixel_love) - 1:
                file.write(",\n")
        file.write("\n};\n")

# 입력 파일과 출력 파일 경로 지정
input_file = "neo_pixel_love.txt"
output_file = "neo_pixel_for_love_60.txt"

# 변환 실행
convert_to_arduino_format(input_file, output_file)

print(f"데이터가 {output_file} 파일로 저장되었습니다.")
