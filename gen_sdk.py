# ======================================================================================
# File         : gen_sdk.py
# Author       : Wu Jie 
# Last Change  : 08/24/2010 | 09:37:29 AM | Tuesday,August
# Description  : 
# ======================================================================================

#/////////////////////////////////////////////////////////////////////////////
# imports
#/////////////////////////////////////////////////////////////////////////////

import os
import os.path
import shutil
import re

# settings
exlibs_path = "./src/exlibs/"
dest_path = "e:/projects/Client/sdk/exlibs/"

#/////////////////////////////////////////////////////////////////////////////
# functions
#/////////////////////////////////////////////////////////////////////////////

# ------------------------------------------------------------------ 
# Desc: 
# ------------------------------------------------------------------ 

def gen_include ():
    dest_inc = os.path.join(dest_path,"include")
    pattern = re.compile(r'.*\.h$|.*\.hpp$|.*\.inl$')
    for root, dirs, files in os.walk(exlibs_path):
        rel_path = re.sub( exlibs_path, '', root )

        # remove unwanted directory
        if '.svn' in dirs:
            dirs.remove('.svn')
        if '.git' in dirs:
            dirs.remove('.git')

        # get dest sub-path 
        dest_sub_path = os.path.join(dest_inc,rel_path)
        if os.path.isdir(dest_sub_path) == False:
            os.makedirs (dest_sub_path)

        # copy the files to the dest sub-path
        for name in files:
            re_result = pattern.match(name)
            if re_result:
                filepath = os.path.join(rel_path, name)
                shutil.copy ( os.path.join(root,name), os.path.join(dest_inc,filepath) )
                print "%s: %s copied" % (dest_sub_path, name)

# ------------------------------------------------------------------ 
# Desc: 
# ------------------------------------------------------------------ 

def gen_lib ():
    # debug
    if os.path.isdir("./sln/vc8/_bin/debug"):
        dest_dir = os.path.join(dest_path,"lib/debug")
        if os.path.isdir(dest_dir) == False: 
            os.makedirs(dest_dir)
        shutil.copy("./sln/vc8/_bin/debug/exlibs.lib", os.path.join(dest_dir,"exlibs.lib") )
        print "debug/exlibs.lib copied"
        shutil.copy("./sln/vc8/_bin/debug/exlibs.pdb", os.path.join(dest_dir,"exlibs.pdb") )
        print "debug/exlibs.pdb copied"

    # release
    if os.path.isdir("./sln/vc8/_bin/release"):
        dest_dir = os.path.join(dest_path,"lib/release")
        if os.path.isdir(dest_dir) == False: 
            os.makedirs(dest_dir)
        shutil.copy("./sln/vc8/_bin/release/exlibs.lib", os.path.join(dest_dir,"exlibs.lib") )
        print "release/exlibs.lib copied"

# ------------------------------------------------------------------ 
# Desc: 
# ------------------------------------------------------------------ 

def main():
    # clean the destpath first.
    if os.path.isdir(dest_path):
        shutil.rmtree(dest_path)
    # now create the include and lib
    gen_include()
    gen_lib()

#/////////////////////////////////////////////////////////////////////////////
# run
#/////////////////////////////////////////////////////////////////////////////

if __name__ == "__main__":
    import sys
    exit_status = int(not main())
    sys.exit(exit_status)

