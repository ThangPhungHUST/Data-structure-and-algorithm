# Thiết kể giải thuật: Sử dụng Couting Sort
# - B1: Duyệt qua mảng và sử dụng các biến đếm để đếm số lần xuất hiện của từng màu
# - B2: Duyệt qua mảng và gán giá trị cho mảng theo thứ tự đỏ, trắng, xanh bằng cách giảm các biến đếm qua mỗi lần gán giá tị. Nếu biến đếm bằng 0 thì chuyển qua màu khác hoặc kết thúc

colors = ['xanh', 'do', 'xanh', 'do', 'do', 'trang', 'do', 'xanh', 'trang']

def sort_colors(colors):
    c_red = 0
    c_green = 0
    c_white = 0
    for i in range(len(colors)):
        if (colors[i] == 'do'):
            c_red += 1
        elif (colors[i] == 'trang'):
            c_white += 1
        else:
            c_green += 1
        
    for j in range(len(colors)):
        if (c_red != 0):
            colors[j] = 'do'
            c_red -= 1
            continue
        if (c_white != 0):
            colors[j] = 'trang'
            c_white -= 1
            continue
        if (c_green != 0):
            colors[j] = 'xanh'
            c_green -= 1
    return colors        

colors = sort_colors(colors)            
print(colors)
