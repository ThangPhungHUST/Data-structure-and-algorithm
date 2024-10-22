# Đọc từ file danso.txt
def print_range(dic, val):
	for key, value in dic.items():
		if value == val:
			print(key)

def read_file(start, end):
	danso = {}
	with open("danso.txt", "r") as file:
		year = file.read(4)
		people = int(file.readline().lstrip('\t').rstrip('\n'))
		while year != str(end):
			if int(year) < start:
				year = file.read(4)
				people = int(file.readline().lstrip('\t').rstrip('\n'))
			else:	
				danso[year] = people
				year = file.read(4)
				people = int(file.readline().lstrip('\t').rstrip('\n'))
		danso[year] = people
	return danso

def same_people(danso):
	for value in danso.values():
		c = 0
		a = []
		for k, v in danso.items():
			if v == value:
				c += 1
				a.append(k)
		if c > 1:
			print("So nam co cung {0} nguoi sinh la {1}: {2}".format(value, c, a))

def min_max(danso, start, end):
	max_ = min_ = danso[str(start)]
	for key, value in danso.items():
		if int(key) < start:
			continue
		if value < min_:
			min_ = value
		if value > max_:
			max_ = value
		if int(key) == end:
			break
	print("Nam co so nguoi sinh ra nho nhat la {0}: ".format(min_))
	print_range(danso, min_)
	print("Nam co so nguoi sinh ra lon nhat la {0}: ".format(max_))
	print_range(danso, max_)

def main():
	start = int(input("Enter start: "))
	end = int(input("Enter end: "))
	danso = read_file(start, end)
	print("----------")
	min_max(danso, start, end)
	print("----------")
	same_people(danso)

main()
