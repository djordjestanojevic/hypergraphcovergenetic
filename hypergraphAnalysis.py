
outputfile = open("C:/Users/Djordje/OneDrive/Desktop/hpgAnalysis.txt", "a")

counter = {3:0,4:0,5:0,6:0,7:0}
numVertices = {3:0,4:0,5:0,6:0,7:0}
numEdges = {3:0,4:0,5:0,6:0,7:0}
def readFile(graph):
    f = open("C:/Users/Djordje/OneDrive/Desktop/demofile{}.txt".format( graph), "r")
    numVertices[graph] = int(f.readline())

    for x in f:
        line = x.split(", ")
        counter[graph] += len(line)
        numEdges[graph] += 1


for filename in range(3,8):
    readFile(filename)


for k in counter:
    outputfile.write(str(k) + "Avg vert deg " + str(counter[k]/numVertices[k]) + "Avg edge deg " + str(counter[k]/numEdges[k]) + "\n")
