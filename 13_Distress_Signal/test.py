# I am considering solving the problem with Python to handle 
# mixed types lists. Might be easier :)


# Take the example input
example = '[1,1,3,1,1]\n[1,1,5,1,1]\n\n[[1],[2,3,4]]\n[[1],4]\n\n[9]\n[[8,7,6]]\n\n[[4,4],4,4]\n[[4,4],4,4,4]\n\n[7,7,7,7]\n[7,7,7]\n\n[]\n[3]\n\n[[[]]]\n[[]]\n\n[1,[2,[3,[4,[5,6,7]]]],8,9]\n[1,[2,[3,[4,[5,6,0]]]],8,9]'

# Obtain a list of all the lines (God this is more comfortamble than C++)
packets = example.split('\n')

# Define an empty list that will contain the indexes of the open brackets
open_brackets = []

# Pair of lists
pair = []

# Define lists for the packets
packet_list = []

# Variable used to print -----
packet_counter = 0

# Store the input string as data in lists to work with it
for packet in packets:

    # Avoid empty entries in packets list
    if len(packet) == 0:
        continue

    # Update variable to take count of the pairs
    packet_counter += 1

    # Remove the first and last element --> They are always opening and closing brackets 
    packet = packet[1:-1]   

    # Iterate through the characters of the packet
    for i in range (len(packet)):

        c = packet[i]
        if(c == ','):
            continue
        elif(c == '['):
            open_brackets.append(i)
        elif(c == ']'): # I want to print the list 
            substring = packet[open_brackets.pop() : i + 1]
            if len(open_brackets) == 0:
                packet_list.append(substring)
        else:
            if len(open_brackets) == 0:
                packet_list.append(c)

    # Debug: print the packet
    print(packet_list)
    packet_list.clear()

    if packet_counter == 2:
        print('-------------')
        packet_counter = 0

