#!usr/local/cs/bin/python
import random, sys, string, locale
from optparse import OptionParser

locale.setlocale(locale.LC_ALL, 'C')

class getlines:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def getList(self):
        order1=[]
        for str in self.lines:
            order1.append(str.strip())
        return order1

def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2
Outputs Differences between FILE1 and FILE2."""
    
     parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1", action="store_true", dest="s1"
                      , default=False)
    parser.add_option("-2", action="store_true", dest="s2"
                      , default=False)
    parser.add_option("-3", action="store_true", dest="s3"
                      , default=False)
    parser.add_option("-u", action="store_true", dest="sort"
                      , default=False)
    options, args = parser.parse_args()
    if len(args) != 2:
        parser.error("Error: 2 arguements needed")
    input1 = args[0]
    input2 = args[1]
    if len(args) != 2:
        parser.error("wrong number of operands")
    lead1 = ""
    lead2 = ""
    if options.column_1 == False:
        lead1 += "\t"
    if options.column_2 == False:
        lead2 += "\t"
    
    input_file = args[0]
    input_file2 = args[1]
    try:
        generator = comm(input_file, input_file2)
    except IOError as err:
        parser.error("I/O error"). 
            format(err.errno, err.sterror))
    order1 = generator.readLines1()
    order2 = generator.readLines2()
    number1 = 0
    number2 = 0
    total = len(generator.readLines2()) + len(generator.readLines1())
    while number1 < len(order1):
            sys.stdout.write(order1[number1] + "\n")
            number1 += 1
        if options.column_2 == False:
            while number2 < len(order2):
                if options.column_1 == False and options.column_2 == False:
                    sys.stdout.write("\t")
                sys.stdout.write(order2[number2] + "\n")
                number2 += 1
    if options.unsorted == True:            
        for cur in order1:                   
            if cur in order2:
                if options.column_3 == False:
                    sys.stdout.write(lead1)
                    sys.stdout.write(lead2)
                    sys.stdout.write(cur)
                    sys.stdout.write("\n")
                order2.remove(cur)
            else:
                if options.column_1 == False:
                    sys.stdout.write(cur)
                    sys.stdout.write("\n")
        for current in order2:
            if options.column_2 == False:
                sys.stdout.write(lead1)
                sys.stdout.write(current)
                sys.stdout.write("\n")
                    
    else:
        for index in range(total):
            if number1 < len(order1) and number2 < len(order2):
                if locale.strcoll(order1[number1],
                                  order2[number2]) < 0:
                    if options.column_1 == False:
                        sys.stdout.write(order1[number1])
                        sys.stdout.write("\n")
                    number1 += 1
                elif locale.strcoll(order1[number1], 
                    order2[number2]) == 0:
                    if options.column_3 == False:
                        sys.stdout.write(lead1)
                        sys.stdout.write(lead2)
                        sys.stdout.write(order1[number1])
                        sys.stdout.write("\n")
                    number1 += 1 
                    number2 += 1       
                elif locale.strcoll(order1[number1], 
                    order2[number2]) > 0:
                    if options.column_1 == False and options.column_2 == False:
                        sys.stdout.write(lead1)
                    if options.column_2 == False:
                        sys.stdout.write(order2[number2])
                        sys.stdout.write("\n")
                    number2 += 1      
        
if __name__ == "__main__":
    main()