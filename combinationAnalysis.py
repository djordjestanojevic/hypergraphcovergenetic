# Online Python compiler (interpreter) to run Python online.
# Write Python 3 code in this online editor and run it.
from itertools import product
import math
outputfile = open("C:/Users/Djordje/OneDrive/Desktop/masterAnalysis3.txt", "a")



#runMap = {key: 0 for key in list(product(range(3,8), range(0,20), range(32)))}
#populationMap = {key: 0 for key in list(product(range(3,8), range(0,20), range(32)))}
#bestPopulationCounter = {key: {30:0,40:0,50:0} for key in range(33) }


combinationMaps = {0:{},30:{}, 40:{},50:{}}
globalMax = {3: -1, 4: -1, 5: -1, 6: -1, 7: -1}
globalComb = {3: -1, 4: -1, 5: -1, 6: -1, 7: -1}
goodResultCounter = {key: 0 for key in range(32)}
goodResultCounterPop = {30:0,40:0,50:0}
generationalMaximumsPerPopulation = {key: {} for key in list(product(range(30,51,10), range(3,8)))}
generationalAveragesPerPopulation = {key: {} for key in list(product(range(30,51,10), range(3,8)))}
generationalMaximumsPerCombination = {key: {} for key in list(product(range(32), range(3,8)))}
generationalAveragesPerCombination = {key: {} for key in list(product(range(32), range(3,8)))}
generationCounterPop = {key: {} for key in list(product(range(30,51,10), range(3,8)))}
generationCounterComb = {key: {} for key in list(product(range(32), range(3,8)))}
solidResultCounterComb = {key: 0 for key in range(32)}
solidResultCounterPop = {30:0,40:0,50:0}
solidResultSumComb = {key: 0 for key in range(32)}
solidResultSumPop = {30:0,40:0,50:0}

def readFile(populationSize, graph, i):
    f = open("C:/Users/Djordje/OneDrive/Desktop/Results/{}/{}/pop{}_{}_{}.csv".format(populationSize, graph, populationSize, graph, i), "r")
    f.readline()
    currentMax = 0
    bestComb = -1
    prevGoodComb = -1
    prevSolidComb = -1
    thisCombBest = 0
    for x in f:
        line = x.split(",")
        lineComb = int(line[0])
        lineGen = int(line[1])
        lineMax = int(math.floor(float(line[3])))
        lineAvg = int(math.floor(float(line[4])))
        if (lineGen % 10) == 0:
            if lineGen in generationCounterPop[(populationSize, graph)]:
                generationCounterPop[(populationSize, graph)][lineGen] += 1
            else:
                generationCounterPop[(populationSize, graph)][lineGen] = 1

            if lineGen in generationCounterComb[(lineComb, graph)]:
                generationCounterComb[(lineComb, graph)][lineGen] += 1
            else:
                generationCounterComb[(lineComb, graph)][lineGen] = 1

            if lineGen in generationalMaximumsPerPopulation[(populationSize,graph)]:
                generationalMaximumsPerPopulation[(populationSize,graph)][lineGen] += lineMax
                generationalAveragesPerPopulation[(populationSize,graph)][lineGen] += lineAvg
            else:
                generationalMaximumsPerPopulation[(populationSize, graph)][lineGen] = lineMax
                generationalAveragesPerPopulation[(populationSize, graph)][lineGen] = lineAvg
            if lineGen in generationalMaximumsPerCombination[(lineComb, graph)]:
                generationalMaximumsPerCombination[(lineComb, graph)][lineGen] +=  lineMax
                generationalAveragesPerCombination[(lineComb, graph)][lineGen] += lineAvg
            else:
                generationalMaximumsPerCombination[(lineComb, graph)][lineGen] =  lineMax
                generationalAveragesPerCombination[(lineComb, graph)][lineGen] = lineAvg

        if lineMax > currentMax:
            currentMax = lineMax
            bestComb = line[0]

        if (lineComb!= prevGoodComb) and (lineMax > 0.95*globalMax[graph]):
                goodResultCounter[lineComb] += 1
                goodResultCounterPop[populationSize] += 1
                prevGoodComb = lineComb
        if lineMax > 0.8 * globalMax[graph]:
            if lineComb != prevSolidComb:
                solidResultCounterComb[lineComb] += 1
                solidResultCounterPop[populationSize] += 1
                prevSolidComb = lineComb
                solidResultSumPop[populationSize] += lineGen
                solidResultSumComb[lineComb] += lineGen
                thisCombBest = lineGen
            else:
                solidResultSumPop[populationSize] += lineGen - thisCombBest
                solidResultSumComb[lineComb] += lineGen - thisCombBest
                thisCombBest = lineGen
            #if runMap[(graph,i,int(line[0]))] < int(line[3]):
            #    runMap[(graph, i, int(line[0]))] = int(line[3])
            #    populationMap[(graph,i, int(line[0]))] = populationSize


    if bestComb in combinationMaps[0]:
        combinationMaps[0][bestComb] += 1
    else:
        combinationMaps[0][bestComb] = 1
    if bestComb in combinationMaps[populationSize]:
        combinationMaps[populationSize][bestComb] += 1
    else:
        combinationMaps[populationSize][bestComb] = 1

    f.close()

def readMax(popSize, graph, i):
    f = open("C:/Users/Djordje/OneDrive/Desktop/Results/{}/{}/pop{}_{}_{}.csv".format(popSize, graph, popSize, graph, i), "r")
    f.readline()
    for x in f:
        line = x.split(",")
        lineComb = int(line[0])
        lineMax = int(math.floor(float(line[3])))
        if lineMax > globalMax[graph]:
            globalMax[graph] = lineMax
            globalComb[graph] = lineComb
    f.close()




for popSize in range(30,51,10):
    for filename in range(3,8):
        for i in range(20):
            readMax(popSize, filename, i)

for popSize in range(30,51,10):
    for filename in range(3,8):
        for i in range(20):
            readFile(popSize, filename, i)

#for (p1,p2, p3) in populationMap:
#    bestPopulationCounter[p3][p2] += 1
#    bestPopulationCounter[32][p2] += 1

generationalSumPop = {key: {} for key in range(30,51,10)}

#for (ps, fn) in generationCounterPop:
#    for (gen, counter) in generationCounterPop[(ps, fn)].items():
#        if counter != 0:
#            generationalMaximumsPerPopulation[(ps, fn)][gen] /= counter
#            generationalAveragesPerPopulation[(ps, fn)][gen] /= counter

#for (cb, fn) in generationCounterComb:
#    for (gen, counter) in generationCounterComb[(cb, fn)].items():
#        if counter != 0:
#            generationalMaximumsPerCombination[(cb, fn)][gen] /= counter
#            generationalAveragesPerCombination[(cb, fn)][gen] /= counter

for (k,v) in solidResultSumPop.items():
    if (solidResultCounterPop[k] != 0 ):
        solidResultSumPop[k] /= solidResultCounterPop[k]

for (k,v) in solidResultSumComb.items():
    if (solidResultCounterComb[k] != 0):
        solidResultSumComb[k] /= solidResultCounterComb[k]


#outputfile.write("Global max: {} for respective combination {}\n".format(globalMax, globalComb))
#outputfile.write("Good result counter per population: {}\n".format(goodResultCounterPop))
#outputfile.write("Good result counter per combination: {}\n".format(goodResultCounter))
outputfile.write("Number of iterations for solid result per population: {}\n".format(solidResultSumPop))
outputfile.write("Number of iterations for solid result per combination: {}\n".format(solidResultSumComb))

outputfile.write("Number of solid results per population: {}\n".format(solidResultCounterPop))
outputfile.write("Number of solid results per combination: {}\n".format(solidResultCounterComb))

#for ps in combinationMaps:
#    outputfile.write("Best combination for population{}: {}\n".format(ps,combinationMaps[ps]))

#for ps in range(30,51,10):
#    for fn in range(3,8):
        #outputfile.write("Generational counter for population size {} and file {}: {}\n".format(ps,fn,generationCounterPop[(ps,fn)]))

#for cb in range(32):
#    for fn in range(3,8):
        #outputfile.write("Generational counter for combination {} and file {}: {}\n".format(cb,fn,generationCounterComb[(cb,fn)]))


#for ps in range(30,51,10):
#    for fn in range(3,8):
#        outputfile.write("Generational maximums for population size {} and file {}: {}\n".format(ps,fn,generationalMaximumsPerPopulation[(ps,fn)]))

#for ps in range(30,51,10):
#    for fn in range(3,8):
#        outputfile.write("Generational averages for population size {} and file {}: {}\n".format(ps,fn,generationalAveragesPerPopulation[(ps,fn)]))

#for cb in range(32):
#    for fn in range(3,8):
#        outputfile.write("Generational maximums for combination {} and file {}: {}\n".format(cb,fn,generationalMaximumsPerCombination[(cb,fn)]))

#for cb in range(32):
#    for fn in range(3,8):
 #       outputfile.write("Generational averages for combination {} and file {}: {}\n".format(cb,fn,generationalAveragesPerCombination[(cb,fn)]))
# print (currentCount)
# print (hyperedges)

for ps in range(30,51,10):
    for fn in range(4,8):
        for (k,v) in generationalMaximumsPerPopulation[(ps,fn)].items():
            if k in generationalMaximumsPerPopulation[(ps,3)]:
                generationalMaximumsPerPopulation[(ps,3)][k] += v
            else:
                generationalMaximumsPerPopulation[(ps,3)][k] = v

for cb in range(32):
    for fn in range(4,8):
        for (k,v) in generationalMaximumsPerCombination[(cb,fn)].items():
            if k in generationalMaximumsPerCombination[(cb,3)]:
                generationalMaximumsPerCombination[(cb,3)][k] += v
            else:
                generationalMaximumsPerCombination[(cb,3)][k] = v

for ps in range(30,51,10):
    for fn in range(4,8):
        for (k,v) in generationalAveragesPerPopulation[(ps,fn)].items():
            if k in generationalAveragesPerPopulation[(ps,3)]:
                generationalAveragesPerPopulation[(ps,3)][k] += v
            else:
                generationalAveragesPerPopulation[(ps,3)][k] = v

for cb in range(32):
    for fn in range(4,8):
        for (k,v) in generationalAveragesPerCombination[(cb,fn)].items():
            if k in generationalAveragesPerCombination[(cb,3)]:
                generationalAveragesPerCombination[(cb,3)][k] += v
            else:
                generationalAveragesPerCombination[(cb,3)][k] = v

for ps in range(30, 51, 10):
    for fn in range(4, 8):
        for (k, v) in generationCounterPop[(ps, fn)].items():
            if k in generationCounterPop[(ps,3)]:
                generationCounterPop[(ps, 3)][k] += v
            else:
                generationCounterPop[(ps, 3)][k] = v

for cb in range(32):
    for fn in range(4, 8):
        for (k, v) in generationCounterComb[(cb, fn)].items():
            if k in generationCounterComb[(cb, 3)]:
                generationCounterComb[(cb, 3)][k] += v
            else:
                generationCounterComb[(cb, 3)][k] = v

groupedGenMaxPop = {ps : generationalMaximumsPerPopulation[(ps,3)] for ps in range(30,51,10)}
groupedGenAvgPop = {ps : generationalAveragesPerPopulation[(ps,3)] for ps in range(30,51,10)}
groupedGenMaxComb = {cb : generationalMaximumsPerCombination[(cb,3)] for cb in range(32)}
groupedGenAvgComb = {cb : generationalAveragesPerCombination[(cb,3)] for cb in range(32)}
groupedCounterPop = {ps : generationCounterPop[(ps,3)] for ps in range(30,51,10)}
groupedCounterComb = {cb : generationCounterComb[(cb,3)] for cb in range(32)}

for ps in range(30,51,10):
    for (k,v) in groupedCounterPop[ps].items():
        groupedGenMaxPop[ps][k] /= v
        groupedGenAvgPop[ps][k] /= v

#for ps in range(30,51,10):
#    outputfile.write("Generational maximums for population size {}: {}\n".format(ps,groupedGenMaxPop[ps]))
#    outputfile.write("Generational averages for population size {}: {}\n".format(ps,groupedGenAvgPop[ps]))


for cb in range(32):
    for (k, v) in groupedCounterComb[cb].items():
        groupedGenMaxComb[cb][k] /= v
        groupedGenAvgComb[cb][k] /= v

#for cb in range(32):
#    outputfile.write("Generational maximums for combination {}: {}\n".format(cb, groupedGenMaxComb[cb]))
#    outputfile.write("Generational averages for combination {}: {}\n".format(cb, groupedGenAvgComb[cb]))

        # f2.write(str(currentCount) + "\n")
# for hyperedge in hyperedges:
#    line = str(hyperedge).translate({ord(c): None for c in '[]'})
#    f2.write(line + "\n")
# f2.close()


# f.close()
# f2.write("Now the file has more content!")
# f2.close()

