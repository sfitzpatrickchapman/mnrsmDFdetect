import sys

userFile = sys.argv[1]
rawFile = open(userFile, 'r')

lineCount = 0
successColumn = 4
i = 0
firstLine = True

for line in rawFile:
    row = line.split(",")
    if row[successColumn] == "1":
        lineCount += 1
rawFile.close()
fileName = sys.argv[1][0: -4] + "_MODIFIED.csv"
modifiedFile = open(fileName, 'w')
modifiedFile.write(str(lineCount) + "\n")
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
            lineToAdd += str(int(float(row[x]))) + ","
        lineToAdd += "\n"
        modifiedFile.write(lineToAdd)

modifiedFile.close()
rawFile.close()
