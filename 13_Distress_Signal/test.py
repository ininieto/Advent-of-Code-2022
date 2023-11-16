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

from utils import store_packets, create_packet_pairs

# Take the example input
example = "[1,1,3,1,1]\n[1,1,5,1,1]\n\n[[1],[2,3,4]]\n[[1],4]\n\n[9]\n[[8,7,6]]\n\n[[4,4],4,4]\n[[4,4],4,4,4]\n\n[7,7,7,7]\n[7,7,7]\n\n[]\n[3]\n\n[[[]]]\n[[]]\n\n[1,[2,[3,[4,[5,6,7]]]],8,9]\n[1,[2,[3,[4,[5,6,0]]]],8,9]"

# Obtain a list of all the lines (God this is more comfortamble than C++)
splitted_example = example.split('\n')

# Store the input string as data in lists to work with it
packets_list = store_packets(splitted_example)

# Create the pairs
packet_pairs = create_packet_pairs(packets_list)

# Now comes the funny part hahaha compare the lists

for pair in packet_pairs:

    first_packet = pair[0]
    second_packet = pair[1]

    decision_made = False

    # Find the lower length of both pairs
    if len(first_packet) == len(second_packet):
        lower_length = len(first_packet)
    elif len(first_packet) > len(second_packet):
        lower_length = len(second_packet)
    else:
        lower_length = len(first_packet)
    
    # Iterate the packets at the same time
    for i in range(lower_length):
        element_first_packet = first_packet[i]
        element_second_packet = second_packet[i]

        # TODO: Check the type of the elements. Must be aware of comparing lists

        if element_first_packet < element_second_packet:
            print("Right order")
            decision_made = True
            break
        elif element_first_packet > element_second_packet:
            print("Wrong order")
            decision_made = True
            break
    
    # If there hasn't been a decision so far, the smaller list should be first

    if not decision_made:
        if len(first_packet) > len(second_packet):
            print("Wrong order")
        else:
            print("Right order")
