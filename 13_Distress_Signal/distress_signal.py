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

from utils import read_from_file, store_packets, create_packet_pairs, get_result

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
result = get_result(packet_pairs)

print("The result is " + str(result))
