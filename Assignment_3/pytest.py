#! /usr/bin/python


from optparse import OptionParser
import sys
import string

def main():

    version_msg = "%prog 1.0"
    usage_msg   = "option msg..."

    parser = OptionParser(version=version_msg, usage = usage_msg)

    parser.add_option("-n", "--numlines",
                      action="store",
                      dest  ="numlines",
                      default = 1,
                      help    = "output NUMLINES (default=1)")
    options, args = parser.parse_args(sys.argv[1:])
    print(options.numlines)
if __name__ == "__main__":
    main()
