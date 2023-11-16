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

def get_result(packet_pairs):

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

            
            # TODO: It fails when comparing int and nested list. I'm only converting 
            # once int to list. More comprobations needed

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

    return result
