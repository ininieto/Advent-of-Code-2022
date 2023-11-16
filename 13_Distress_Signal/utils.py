# Function that processes the input data and stores it in lists

def store_packets(splitted_example):

    # Define an empty list that will contain the indexes of the open brackets
    open_brackets = []

    # Define lists for the packets
    packet = []
    packets_list = []

    for p in splitted_example:

        # Avoid empty entries in packets list
        if len(p) == 0:
            continue

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
        packets_list.append(packet.copy())   # What is this need of doing a copy not to rewrite the data in the list? Python is shit
        packet.clear()
    
    return packets_list

# Function that arranges these lists in pairs

def create_packet_pairs(packets_list):
    packet_pairs = [packets_list[i:i+2] for i in range(0, len(packets_list), 2)]
    return packet_pairs

