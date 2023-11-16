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

from utils import read_from_file, store_packets, create_packet_pairs

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


for i in range(len(packet_pairs)):

    pair = packet_pairs[i]

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
    for j in range(lower_length):
        element_first_packet = first_packet[j]
        element_second_packet = second_packet[j]

        # TODO: Check the type of the elements. Must be aware of comparing lists        

        if type(element_first_packet) != type(element_second_packet):
            if type(element_first_packet) == int:
                element_first_packet = [element_first_packet]
            else:
                element_second_packet = [element_second_packet]


        # This way of comparing also works with lists :)
        if element_first_packet < element_second_packet:
            print("Right order")
            result += (i + 1)
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
            result += (i + 1)

print("The result is " + str(result))
