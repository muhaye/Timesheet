#!/usr/bin/env python3
import sys
import datetime
import pdfkit
from prettytable import PrettyTable

now        = datetime.date.today()
lastMonth  = now.replace(month=now.month-1)
FROM       = int(sys.argv[1])
TO         = int(sys.argv[2])
startDate  = lastMonth.replace(day=FROM)
endDate    = lastMonth.replace(day=TO)

ioStreamTableContainer                  = PrettyTable()
ioStreamTableContainer.border           = False
ioStreamTableContainer.header           = False
ioStreamTableColumn                     = [PrettyTable(),PrettyTable(),PrettyTable()]
ioStreamTableContainer.add_row(ioStreamTableColumn)
data                                    = []

def isWeekend(date):
    return  date.weekday() >4 

for dayNum in range(FROM, TO+1):
    day = lastMonth.replace(day=dayNum)
    hours = 0.0 if isWeekend(day) else 7.5 
    data.append((dayNum,hours)) 

sumHours = sum(x[1] for x in data) 

def ioStreamPrint(data) :
    #Add header for the day hours
    for i in range(0, len(ioStreamTableColumn) -1 ) :
        ioStreamTableColumn[i].field_names = ["Day", "Hours"]
    
    ioStreamTableColumn[-1].field_names = ["Total Hours"]
    
    for (dayNum, hours) in data:
        ioStreamTableColumn[1 if dayNum > 15 else 0 ].add_row([dayNum, hours])
    
    ioStreamTableColumn[2].add_row([sumHours])

    print(ioStreamTableContainer)


def htmlRow(dh) :
    return "<td>%d</td><td>%.1f</td>" % (dh[0], dh[1])

def htmlFromTotal(total) :
    return ("<table border=1>" 
                + "<th>Total Hours</th>"
                + "<tr><td> %s </td></tr></table>" % total )

def htmlFromData(data) :
    day      = [htmlRow(x) for x in data]
    headers  = ["Day","Hours"]
    return ("<table border=1>" 
                + "<th>Day</th><th>Hours</th>"
                + "<tr>"
                + "</tr><tr>".join(day) 
                + "</tr></table>")

print("Timesheet for %s -> %s"% (startDate, endDate))
ioStreamPrint(data)

#print("Consultant Signature:___________________\n")
#print("Client Signature:___________________\n")
col    = [
        htmlFromData(data[:15]),
        htmlFromData(data[15:]),
        htmlFromTotal(sumHours)
        ]

resultHtml =  ("<table><tr><td>" 
        + "</td><td>".join(col) 
        + "</td></tr></table>")

pdfkit.from_string( resultHtml , 'out.pdf')

