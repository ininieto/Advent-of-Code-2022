# I am considering solving the problem with Python to handle 
# mixed types lists. Might be easier :)


# Take the example input
example = '[1,1,3,1,1]\n[1,1,5,1,1]\n\n[[1],[2,3,4]]\n[[1],4]\n\n[9]\n[[8,7,6]]\n\n[[4,4],4,4]\n[[4,4],4,4,4]\n\n[7,7,7,7]\n[7,7,7]\n\n[]\n[3]\n\n[[[]]]\n[[]]\n\n[1,[2,[3,[4,[5,6,7]]]],8,9]\n[1,[2,[3,[4,[5,6,0]]]],8,9]\n\n'

# Obtain a list of all the lines (God this is more comfortamble than C++)
packet_list = example.split('\n')


# For every line in the input --> for every packet¡
for packet in packet_list:
    packet = packet[1:-1]   # Remove the first and last element
    for c in packet:
        if(c == ','):
            continue
        elif(c == '['):
            print('Llave abriendo')
        elif(c == ']'):
            print('Llave cerrando')
        else:
            print(c) # Print the number
        
    print('\n')
        