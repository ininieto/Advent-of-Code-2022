#################################################################
#
#    Advent of Code 2022 - 13.12.2022
#
#    Link to the problem: https://adventofcode.com/2022/day/13
#
#    Author of the solution: Íñigo Nieto Cuadrado
#
#################################################################

# Sorry but I found way easier to solve this problem in Python
# Dealing with mixed-type lists in C++ was kind of a pain

from utils import read_from_file, store_packets, create_packet_pairs, checkOrder

# Take the example input
example = read_from_file("example.txt")
input = read_from_file("input.txt")

# Obtain a list of all the lines (God this is more comfortamble than C++)
splitted_example = input.split('\n')

# Store the input string as data in lists to work with it
packets_list = store_packets(splitted_example)
packets_list.append([[2]])
packets_list.append([[6]])

# Compare all the packets (bubble sort)
for i in range(len(packets_list)):  # I perform a C-style loop because I need to keep track of the indexes
    for j in range(len(packets_list) - 1 - i):
        if checkOrder([packets_list[j], packets_list[j + 1]]) == "wrong":
            temp = packets_list[j]
            packets_list[j] = packets_list[j + 1]
            packets_list[j + 1] = temp

# Get the result
result = 1

for i in range(len(packets_list)):
    packet = packets_list[i]
    if packet == [[2]] or packet == [[6]]:
        result *= (i + 1)

print("The result is " + str(result))
