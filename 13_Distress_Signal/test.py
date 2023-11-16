# I am considering solving the problem with Python to handle 
# mixed types lists. Might be easier :)


# Take the example input
example = '[1,1,3,1,1]\n[1,1,5,1,1]\n\n[[1],[2,3,4]]\n[[1],4]\n\n[9]\n[[8,7,6]]\n\n[[4,4],4,4]\n[[4,4],4,4,4]\n\n[7,7,7,7]\n[7,7,7]\n\n[]\n[3]\n\n[[[]]]\n[[]]\n\n[1,[2,[3,[4,[5,6,7]]]],8,9]\n[1,[2,[3,[4,[5,6,0]]]],8,9]'

# Obtain a list of all the lines (God this is more comfortamble than C++)
splitted_example = example.split('\n')

# Define an empty list that will contain the indexes of the open brackets
open_brackets = []

# Pair of lists
pair = [[]]
pairs_list = [[]]

# Define lists for the packets
packet = []
packet_list = []

# Variable used to print -----
packet_counter = 0

def create_packet_pairs(packets):
    packet_pairs = [packets[i:i+2] for i in range(0, len(packets), 2)]
    return packet_pairs

# Store the input string as data in lists to work with it
for p in splitted_example:

    # Avoid empty entries in packets list
    if len(p) == 0:
        continue

    # Update variable to take count of the pairs
    packet_counter += 1

    # Remove the first and last element --> They are always opening and closing brackets 
    p = p[1:-1]   

    # Iterate through the characters of the packet
    for i in range (len(p)):

        c = p[i]
        if(c == ','):
            continue
        elif(c == '['):
            open_brackets.append(i)
        elif(c == ']'): # I want to print the list 
            substring = p[open_brackets.pop() : i + 1]
            if len(open_brackets) == 0:
                packet.append(substring)
        else:
            if len(open_brackets) == 0:
                packet.append(c)
    
    # Add packet to a list of packets
    packet_list.append(packet.copy())   # What is this need of doing a copy not to rewrite the data in the list? Python is shit
    packet.clear()


