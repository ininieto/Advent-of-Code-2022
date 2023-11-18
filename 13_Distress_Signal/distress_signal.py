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
# Dealing with mixed type lists in C++ was kind of a pain

from utils import read_from_file, store_packets, create_packet_pairs, checkOrder

# Take the example input
example = read_from_file("example.txt")
input = read_from_file("input.txt")

# Obtain a list of all the lines (God this is more comfortamble than C++)
splitted_example = example.split('\n')

# Store the input string as data in lists to work with it
packets_list = store_packets(splitted_example)

# Create the pairs
packet_pairs = create_packet_pairs(packets_list)

# Compare the pairs and get the result
result = 0

for i in range(len(packet_pairs)):  # I perform a C-style loop because I need to keep track of the indexes
    pair = packet_pairs[i]

    if checkOrder(pair):
        print("Index: " + str(i + 1))
        result += (i + 1)


print("The result is " + str(result))
