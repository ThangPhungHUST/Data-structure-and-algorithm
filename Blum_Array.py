# Thiết kế giải thuật:
# - B1: Nhập số N
# - B2: Khởi tạo mảng nửa nguyên tố (Blum) bằng cách sau:
#      + Khởi tạo mảng nguyên tố nhỏ hơn N prime_array bằng cách kiểm tra từng số x có chia hết cho các số từ 2 đến x - 1
#      + Duyệt qua mảng nguyên tố từ i = 0 đến N và trong vòng lặp duyệt từ j = i đến N để kiểm tra tích prime_array[i] * prime_array[j] có nhỏ hơn N không. Nếu có thì thêm vào mảng blum_array
#      + Sắp xếp blum_array bằng thuật toán sắp xếp chèn
# - B3: Kiểm tra số M có thuộc mảng blum_array đã tạo bằng cách duyệt mảng từ đầu đến cuối
# - B4: Tìm các cặp số Blum có tổng cũng là một số Blum bằng cách duyệt qua mảng blum_array từ i = 0 đến len(blum_array) và trong vòng lặp duyệt từ j = i + 1 đến len(blum_array) để kiểm tra tổng blum_array[i] + blum_array[j] có thuộc blum_array không. Nếu có thêm vào mảng blum_pairs

def is_prime(x):
    i = 2
    ans = x >= 2
    while(ans and (i * i <= x)):
        ans = x % i
        i += 1
    return ans

def init_prime_array(n):
    prime_array = []
    for i in range(int(n)):
        if (is_prime(i)):
            prime_array.append(i)
    return prime_array

def init_blum_array(prime_array):
    blum_array = []
    for i in range(len(prime_array)):
        for j in range(i, len(prime_array)):
            if (prime_array[i] * prime_array[j] < n):
                blum_array.append(prime_array[i] * prime_array[j])
    for k in range(len(blum_array)):
        x = blum_array[k]
        l = k
        while (l > 0 and blum_array[l - 1] > x):
            blum_array[l] = blum_array[l - 1]
            l -= 1
        blum_array[l] = x
    return blum_array

def is_in_array(num, array):
    for i in range(len(array)):
        if num == array[i]:
            return True
    return False

def find_blum_pairs(blum_array):
    blum_pairs = []
    for i in range(len(blum_array)):
        num1 = blum_array[i]
        for j in range(i + 1, len(blum_array)):
            num2 = blum_array[j]
            if is_in_array(num1 + num2, blum_array):
                blum_pairs.append((num1, num2))
    return blum_pairs

n = int(input("Nhap so N: "))

prime_array = init_prime_array(n)
blum_array = init_blum_array(prime_array)
blum_pairs = find_blum_pairs(blum_array)

print(blum_array)
print(blum_pairs)

m = int(input("Nhap so M de kiem tra co thuoc day Blum: "))
print(str(m), end = '')
if is_in_array(m, blum_array): 
    print(" co", end = '') 
else:
    print(" khong", end = '')
print(" thuoc day Blum.")
