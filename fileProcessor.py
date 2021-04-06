# Author: Owen Walsh

# to run, command is:
#
#   python3 fileLoader.py *fileName.csv*
#
# creates a new file called "fileName_processed.txt"
# format has the line count as first line of the file, and next lines are all the values

import sys # for command line args

userFile = sys.argv[1]
rawFile = open(userFile, 'r')

lineCount = 0
successColumn = 4
i = 0
firstLine = True

# count amount of successful lines and store in the processed file
for line in rawFile:
    row = line.split(",")
    if row[successColumn] == "1":
        lineCount += 1
rawFile.close()
fileName = sys.argv[1][0: -4] + "_PROCESSED.txt"

# process file
processedFile = open(fileName, 'w')
processedFile.write(str(lineCount) + "\n")
rawFile = open(userFile, 'r')

for line in rawFile:
    row = line.split(",")
    if firstLine == True:
        firstLine = False
        continue
    if row[successColumn] == "0":
        continue
    else:
        lineToAdd = ""
        for x in range(696, 714):
            lineToAdd += str(int(float(row[x])))
        lineToAdd += "\n"
        processedFile.write(lineToAdd)

processedFile.close()
rawFile.close()
