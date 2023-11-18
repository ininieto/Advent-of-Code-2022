import ast

# Function to read text from file

def read_from_file(input_file):

    with open(input_file) as f:
        data = f.read()
        
    return data

# Function that processes the input data and stores it in lists

def store_packets(splitted_example):

    # Final list that will store all the packets
    packets_list = []

    for packet in splitted_example:

        # Avoid empty entries in packets list
        if len(packet) == 0:
            continue
        
        # This is literal magic: converts string into lists and ints
        packets_list.append(ast.literal_eval(packet))

    return packets_list


# Function that arranges these lists in pairs

def create_packet_pairs(packets_list):
    packet_pairs = [packets_list[i:i+2] for i in range(0, len(packets_list), 2)]
    return packet_pairs

# The big boy. This function will perform all the logic of comparing the lists

# TODO: As the function is now recirsive, the idea of the indexes for summing up the result is not working
# In addition, must check when a pair is already compared. In Example 8 it works comparing the lists, but after
# giving a result, it jumps back and start comparing 8-8 and 9-9. Must fix that too

# I could try to define a subfunction called checkRightOrder() that only returns true when 
# right order. Later simply if checkRightOrder: result += i

def checkOrder(pair):

    first_packet = pair[0]
    second_packet = pair[1]

    decision_made = False
    result = False

    # Find the lower length of both pairs
    if len(first_packet) == len(second_packet):
        lower_length = len(first_packet)
    elif len(first_packet) > len(second_packet):
        lower_length = len(second_packet)
    else:
        lower_length = len(first_packet)
    
    # Iterate the packets at the same time
    for j in range(lower_length):

        # Obtain the elements of both packets with the same index
        element_first_packet = first_packet[j]
        element_second_packet = second_packet[j]

        # If both elements are int, just skip the type matching code

        # If one element is a list and the other an int, must convert the int to a list
        if type(element_first_packet) == list and type(element_second_packet) == int:
            element_second_packet = [element_second_packet]
            result = checkOrder([element_first_packet, element_second_packet])

        elif type(element_first_packet) == int and type(element_second_packet) == list:
            element_first_packet = [element_first_packet]
            result = checkOrder([element_first_packet, element_second_packet])

        # If they both are lists, I will call this same function recursively
        elif type(element_first_packet) == list and type(element_second_packet) == list:
            result = checkOrder([element_first_packet, element_second_packet])

        # If the order is already decided --> Probably fails, as just check if decides that the result is correct
        # if result:
        #    return result

        # Compare the numbers
        if type(element_first_packet) == int and type(element_second_packet) == int:
            if element_first_packet < element_second_packet:
                print("Right order")
                result = True
                decision_made = True
                return result
            elif element_first_packet > element_second_packet:
                print("Wrong order")
                decision_made = True
                break
    
    # If there hasn't been a decision so far, the smaller list should be first
    if not decision_made:
        if len(first_packet) > len(second_packet):
            print("Wrong order")
        elif len(second_packet) > len(first_packet):
            print("Right order")
            result = True
            return result

    return result
