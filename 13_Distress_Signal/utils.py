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
                    packet.append(int(c))

        # The lists are treated as strings. Until now

        aux_list = []
        formatted_packet = []
        
        for element in packet:
            if type(element) == str:
                for c in element:
                    if c != '[' and c != ']' and c != ',':
                        aux_list.append(int(c))
                    #elif type(c) == int:
                        #aux_list.append(c)
                formatted_packet.append(aux_list.copy())
                aux_list.clear()
            else:
                formatted_packet.append(element)

        packets_list.append(formatted_packet)
        packet.clear()
    
    return packets_list

# Function that arranges these lists in pairs

def create_packet_pairs(packets_list):
    packet_pairs = [packets_list[i:i+2] for i in range(0, len(packets_list), 2)]
    return packet_pairs

