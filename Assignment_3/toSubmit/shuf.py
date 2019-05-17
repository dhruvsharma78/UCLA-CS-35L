#!/usr/bin/python

import random, sys
from optparse import OptionParser

class randline:
    def __init__(self, filename=None, minV=None, maxV=None, use_stdin=False):
        self.lines = [ ]
        if use_stdin:
            for line in sys.stdin:
                self.lines.append(line)
        elif filename != None:
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()
        else:
            f = range(minV,maxV+1)
            for num in f:
                self.lines.append(str(num)+"\n")

    def chooseline(self):
        return random.choice(self.lines)

    def permute(self, n=None):
        if n == None or n > len(self.lines):
            n = len(self.lines)
        pLines = random.sample(self.lines, n)
        for line in pLines:
            sys.stdout.write(line)

    def randomize(self, n=None):
        if n == None or n > len(self.lines):
            while True:
                sys.stdout.write(self.chooseline())
        else:
            for i in range(0,n):
                sys.stdout.write(self.chooseline())
                
def main():
    version_msg = "%prog 1.0"
    usage_msg = """%prog [OPTION]... [FILE]
  or:  shuf -e [OPTION]... [ARG]...
  or:  shuf -i LO-HI [OPTION]...
Write a random permutation of the input lines to standard output.

With no FILE, or when FILE is -, read standard input."""

    fileSet = True
    count   = None
    use_stdin = False
    
    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-i", "--input-range",
                      action = "store",
                      dest   = "input_range",
                      metavar= "lo-hi",
                      help   = "treat each number LO through HI as an input"+
                               " line")

    parser.add_option("-n", "--head-count",
                      action = "store",
                      dest   = "count",
                      help   = "output at most COUNT lines")

    parser.add_option("-r", "--repeat",
                      action = "store_true",
                      dest   = "repeatSet",
                      help   = "output lines can be repeated")

    options, args = parser.parse_args(sys.argv[1:])

    #Check for head count
    try:
        if options.count != None:
            count = int(options.count)
            if count < 0:
                parser.error("invalid line count: {0}".format(options.count))
    except:
        parser.error("invalid line count: {0}".format(options.count))

    #Check for range 
    try:
        if options.input_range != None:
            input_range_str = str(options.input_range)
            input_range = input_range_str.split("-")
            minV = int(input_range[0])
            maxV = int(input_range[1])
            input_range = [minV,maxV]
            fileSet = False 
    except:
        parser.error("invalid input range: {0}".format(options.input_range))

    if options.input_range != None and input_range[1] < input_range[0]:
        parser.error("invalid input range: {0}".format(options.input_range))
        
    #Set repeat value
    repeatSet = bool(options.repeatSet)

    if (len(args) == 0 or args[0] == '-') and options.input_range == None:
        use_stdin = True
    if len(args) >= 1 and options.input_range != None:
        parser.error("extra operand {0}".format(args[0]))
        
    try:
        if use_stdin:
            generator = randline(use_stdin=True)
        elif fileSet:
            generator = randline(args[0])
        else:
            generator = randline(None,input_range[0], input_range[1])

        if repeatSet:
            generator.randomize(count)
        else:
            generator.permute(count)
    except IOError as e:
        errno, strerror = e.args
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))
        


if __name__ == "__main__":
    main()
