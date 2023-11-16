#################################################################
#
#    Advent of Code 2022 - 13.12.2022
#
#    Link to the problem: https://adventofcode.com/2022/day/13
#
#    Author of the solution: Íñigo Nieto Cuadrado
#
#################################################################

from utils import store_packets, create_packet_pairs

# Take the example input
example = "[1,1,3,1,1]\n[1,1,5,1,1]\n\n[[1],[2,3,4]]\n[[1],4]\n\n[9]\n[[8,7,6]]\n\n[[4,4],4,4]\n[[4,4],4,4,4]\n\n[7,7,7,7]\n[7,7,7]\n\n[]\n[3]\n\n[[[]]]\n[[]]\n\n[1,[2,[3,[4,[5,6,7]]]],8,9]\n[1,[2,[3,[4,[5,6,0]]]],8,9]"

# Obtain a list of all the lines (God this is more comfortamble than C++)
splitted_example = example.split('\n')

# Store the input string as data in lists to work with it
packets_list = store_packets(splitted_example)

# Create the pairs
packet_pairs = create_packet_pairs(packets_list)

for pair in packet_pairs:
    for packet in pair:
        print(str(packet) + "  Length: " + str(len(packet)))
    print("-----------")

