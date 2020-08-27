FIFO_FILENAME = './fifo.txt'

fp_fifo = open(FIFO_FILENAME, 'w')

for i in range(128):
    fp_fifo.write("Hello,MakeCode\n")
    fp_fifo.write("")

fp_fifo.close()