import os

FIFO_FILENAME = './fifo.txt'

while True:
    if os.path.exists(FIFO_FILENAME):
        print("detect file")
        fp_fifo = open(FIFO_FILENAME, 'r')
        while True:
            line = fp_fifo.readline()
            if not line:
                break
            print(line)
        fp_fifo.close()
        os.system('rm %s' % FIFO_FILENAME)
    else:
        continue