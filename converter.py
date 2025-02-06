# Online Python compiler (interpreter) to run Python online.
# Write Python 3 code in this online editor and run it.
f = open("s1238.txt", "r")
f2 = open("demofile7.txt", "a")
nodeMap = {}
hyperedges = []
currentCount = 0

f.readline()
f.readline()
for x in f:
  nodesString =  x[x.index("(")+1:x.index(")")]
  hyperedge = []
  for node in nodesString.split(", "):
      if node not in nodeMap:
          nodeMap[node] = currentCount
          currentCount += 1
      
      hyperedge.append(nodeMap[node])
  hyperedges.append(hyperedge)
  

f.close()
#print (currentCount)
#print (hyperedges)
    
f2.write(str(currentCount) + "\n")
for hyperedge in hyperedges:
    line = str(hyperedge).translate({ord(c): None for c in '[]'})
    f2.write(line + "\n")
f2.close()
    
  
  
#f.close()  
#f2.write("Now the file has more content!")
#f2.close()
  
