#!/usr/bin/env python3
import argparse
import os

def main():
  p = argparse.ArgumentParser(description="Timesheet manager")
  p.add_argument('--show', '-s')
  p.add_argument('--add', '-a')
  p.add_argument('--period', '-p', default="month")
  arguments = p.parse_args()
  print ('New Timesheep for the mtypeonth of:  %s %s'% (arguments.period, arguments.add))

  if arguments.period == 'month' :
          os.system("exec ./tSheet.py 1 29")
 
if __name__ == '__main__':
  main()
