FIFO_FILENAME = './fifo.txt'

fp_fifo = open(FIFO_FILENAME, 'w')

for i in range(128):
    fp_fifo.write("Send Test {}\n".format(i))
    fp_fifo.write("")

fp_fifo.close()
