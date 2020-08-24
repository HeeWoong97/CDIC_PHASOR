import os.path

FIFO_FILENAME = './fifo-gps'

if os.path.exists(FIFO_FILENAME):
    while True:
        with open(FIFO_FILENAME, 'r') as fifo:
            print("open")
            data = fifo.read()
            print(data)
            continue
            # line = data.split('\n')
            # for str in line:
            #    print(str)
