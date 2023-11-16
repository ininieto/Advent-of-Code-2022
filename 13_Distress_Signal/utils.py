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

