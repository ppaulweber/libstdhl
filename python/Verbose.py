# 
# Copyright (c) 2014 Philipp Paulweber
# 
# This file is part of the 'libverbose' project which is released under a NCSA
# open source software license. For more information, see the LICENSE.txt 
# file in the project root directory.
#

import sys
import os
import re


# "asdf %(red|rrrr %(bold|rbrb%) rrrr%) asdf"

_CSI = "\x1B["

_SRG = \
       { "c"        : 0 # clear
       , "clear"    : 0
       
       , "b"        : 1 # bold       
       , "bold"     : 1
       
       , "u"        : 2 # underline
       , "single"   : 2
       
       , "l"        : 5 # blink
       , "blink"    : 5
       
       , "black"    : 30 # foreground color sequences
       , "red"      : 31
       , "green"    : 32
       , "yellow"   : 33
       , "blue"     : 34
       , "magenta"  : 35
       , "cyan"     : 36
       , "white"    : 37
       
       , "Black"    : 40 # background color sequences
       , "Red"      : 41
       , "Green"    : 42
       , "Yellow"   : 43
       , "Blue"     : 44
       , "Magenta"  : 45
       , "Cyan"     : 46
       , "White"    : 47
       }

_matcher = re.compile( "(\%\{)|(:)|(\%\})" )
_ignore  = re.compile( "[ \t]" )

def preprocess( text ) :
    
    state = []
    stack = []
    
    def generate_sequence( ) :
        seq = _CSI + "0;"

        if len(state) > 0 :
            for s in state :
                seq = "%s%d;" % ( seq, s, )
            
        seq = seq[:-1] + "m"
        
        print( seq )
        return seq
    # end def
    
    print( text )
    
    i = _matcher.finditer( text )
    
    valid = None
    
    result = ""
    
    for e in i :
        if e.group(1) is not None :
            valid = e.span()
            
            print( "v=1,beg@" )
            print( e.span() )
            continue
        
        elif e.group(2) is not None \
         and valid      is not None :

            options = _ignore.sub( "", text[ valid[1] : e.span()[0] ] ).split( "," )
            
            for option in options :
                try :
                    state.append( _SRG[ option ] )
                except KeyError :
                    assert( 0 and "invalid option used" )
            
            stack.append( len( options ) )
            
            result = "%s" % ( result, )
            
            generate_sequence()
            
            valid = None
            
            print( "v=0,sep@" )
            print( e.span() )
            
        elif e.group(3) is not None :
            if valid is not None :
                assert( 0 and "LIBVERBOSE: need a seperator in color format" )
            
            for i in range( stack.pop() ) :
                print(i)
                state.pop()
            
            generate_sequence()
            
            print( "end@" )
            print( e.span() )
        
        print( "--------------------> %s" % state )
        print( "--------------------> %s" % stack )

    
    return _matcher.sub("", text)
# end def


def printf( message, *args ) :
    
    message = preprocess( message )
    print( message % args )
# end def


def verbose( message, *args ) :
    
    printf( message, args )
    
# end def

def error( message, *args ) :
    
    printf( message, args )
    
    sys.exit( -1 )
# end def



