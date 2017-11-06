#!/usr/bin/env python3
import sys
import datetime
from prettytable import PrettyTable
from xhtml2pdf import pisa

now        = datetime.date.today()
lastMonth  = now.replace(month=now.month-1)
FROM       = int(sys.argv[1])
TO         = int(sys.argv[2])
startDate  = lastMonth.replace(day=FROM)
endDate    = lastMonth.replace(day=TO)

print("Timesheet for %s -> %s"% (startDate, endDate))

tContainer                  = PrettyTable()
tContainer.border           = False
tContainer.header           = False
tColumn                     = [PrettyTable(),PrettyTable(),PrettyTable()]
tContainer.add_row(tColumn)
data                        = []

#Add header for the day hours
for i in range(0, len(tColumn) -1 ) :
    tColumn[i].field_names = ["Day", "Hours"]

tColumn[-1].field_names = ["Total Hours"]

def isWeekend(date):
    return  date.weekday() >4 

for dayNum in range(FROM, TO+1):
    day = lastMonth.replace(day=dayNum)
    hours = 0.0 if isWeekend(day) else 7.5 
    data.append((dayNum,hours)) 

for (dayNum, hours) in data:
    tColumn[1 if dayNum > 15 else 0 ].add_row([dayNum, hours])

tColumn[2].add_row([sum(row[1] for row in data)])

print(tContainer)

print("Consultant Signature:___________________\n")
print("Client Signature:___________________\n")


html = tContainer.get_html_string()
# Define your data
sourceHtml = "<html><body><p>Timesheet to PDF</p>"+ html +"</body></html>"
outputFilename = "ttest.pdf"

# Utility function
def convertHtmlToPdf(sourceHtml, outputFilename):
    # open output file for writing (truncated binary)
    resultFile = open(outputFilename, "w+b")

    # convert HTML to PDF
    pisaStatus = pisa.CreatePDF(
            sourceHtml,                # the HTML to convert
            dest=resultFile)           # file handle to recieve result

    # close output file
    resultFile.close()                 # close output file

    # return True on success and False on errors
    return pisaStatus.err

# Main program
convertHtmlToPdf(sourceHtml, outputFilename)

