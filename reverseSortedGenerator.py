# Reverse number generator for file

import random
import sys
import getopt

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
  print("Unsorted List: ", unsortedList)
  reverseSortedList = sorted(unsortedList, reverse=True)
  print("Reverse Sorted List: ", reverseSortedList)
  
  print("Outputting to: [", outputFile,"]", sep = "")
  myFile.write(str(numberToGenerate) + " ")
  for i in range(numberToGenerate):
    myFile.write(str(reverseSortedList[i]) + " ")

  myFile.close()

main(sys.argv[1:])