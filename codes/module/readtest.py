f = open("detect.txt", "rw")

for i in range(2):
    if f.readline() == "detect!\n":
        print("read \"detect!\"")
    else:
        print("something not \"detect!\"")

f.close()
