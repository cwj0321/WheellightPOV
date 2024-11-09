def convert_to_arduino_format(input_file, output_file):
    with open(input_file, "r") as file:
        lines = file.readlines()

    # 네오픽셀 데이터 저장용 리스트
    neo_pixel_30 = [[] for _ in range(8)]

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
            neo_pixel_30[current_pixel].append([r, g, b])

    # 아두이노 배열 형식으로 변환하여 출력
    with open(output_file, "w") as file:
        file.write("uint8_t colors[8][30][3] = {\n")
        for i, pixel_data in enumerate(neo_pixel_30):
            file.write("  {")
            for j, color in enumerate(pixel_data):
                file.write(f"{{{color[0]}, {color[1]}, {color[2]}}}")
                if j < len(pixel_data) - 1:
                    file.write(", ")
            file.write("}")
            if i < len(neo_pixel_30) - 1:
                file.write(",\n")
        file.write("\n};\n")

# 입력 파일과 출력 파일 경로 지정
input_file = "neo_pixel_30.txt"
output_file = "neo_pixel_for_arduino30.txt"

# 변환 실행
convert_to_arduino_format(input_file, output_file)

print(f"데이터가 {output_file} 파일로 저장되었습니다.")
