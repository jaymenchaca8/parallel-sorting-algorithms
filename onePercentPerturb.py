# 1% perturbed number generator for file

import random
import sys
import getopt
import math

def perturb(inList, perturbAmount):
  perterbPercent = perturbAmount/100

  #The size of the list
  listSize = len(inList)

  # Jump is the amount that the perterbed item will be shifted
  # we use the ceiling function both to obtain an integer and ensure that jump is non-zero
  jump = math.ceil(listSize / 4)

  swapElement = 0

  for i in range(listSize):
    if (perterbPercent >= random.random()):
      #print("List is being pertubed")
      #print("list [", i, "] = ", inList[i], sep = "")
      swapElement = (i+jump)%listSize
      #print("will swap with: [", swapElement, "] = ", inList[swapElement], sep="")
      temp = inList[i]
      inList[i] = inList[swapElement]
      inList[swapElement] = temp

  return inList



def main(argv):

  numberToGenerate = 10
  numberRange = 1000000
  outputFile = 0

  try:
    opts, args = getopt.getopt(argv, "hn:o:r:")
  except getopt.GetoptError:
    print("error: exception")
    sys.exit(2)

  for opt, arg in opts:
    if opt in ("-h"):
      print("Available Arguments:")
      print("-n <number of random numbers to generate> [default: 10]")
      print("-o <output file name> [default randomOutput.txt]")
      print("-r <random number range> [default 1,000,000]")
      sys.exit()
    elif opt in ("-n"):
      numberToGenerate = int(arg)
    elif opt in ("-o"):
      outputFile = arg
    elif opt in ("-r"):
      numberRange = int(arg)

  print("Generating ", numberToGenerate, " random numbers", sep = "")
  print("Possible random number range 1 -", numberRange)

  # open file, create if non existant
  myFile = open(outputFile, "wt")

  if (outputFile != 0):
    myFile.write(str(numberToGenerate) + " ")
  unsortedList = []
  for i in range(numberToGenerate):
    unsortedList.append(random.randrange(numberRange))
  #print("Unsorted List: ", unsortedList)
  sortedList = sorted(unsortedList)
  #print("Sorted List: ", sortedList)
  
  unsortedList = perturb(sortedList, 1)
  #print("Perturbed list: ", unsortedList)
  
  print("Outputting to: [", outputFile,"]", sep = "")
  myFile.write(str(numberToGenerate) + " ")
  for i in range(numberToGenerate):
    myFile.write(str(sortedList[i]) + " ")

  myFile.close()

main(sys.argv[1:])