from PIL import Image
import json

def image_to_rgb_json(image_path, output_json_path, num_pixels, num_columns):
    image = Image.open(image_path)
    image = image.resize((num_columns, num_pixels))  # 원하는 크기로 이미지 조정
    image = image.convert('RGB')  # RGB 모드로 변환

    rgb_data = []
    for y in range(num_pixels):
        row = []
        for x in range(num_columns):
            pixel = image.getpixel((x, y))
            row.append(list(pixel))  # RGB 값을 리스트로 변환
        rgb_data.append(row)

    # JSON 파일로 저장
    with open(output_json_path, 'w') as json_file:
        json.dump({"colors": rgb_data}, json_file)

# 이미지 경로와 출력 JSON 파일 경로 지정
image_to_rgb_json('input_image.png', 'output_colors.json',
                  num_pixels=8, num_columns=120)
