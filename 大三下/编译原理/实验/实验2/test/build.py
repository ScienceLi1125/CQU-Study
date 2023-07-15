import os, platform, subprocess, shutil, sys

def build_compiler():
    is_windows = platform.system() == "Windows"
    bin_dir = "../bin/"
    build_dir = "../build/"

    if not os.path.exists(bin_dir):
        os.mkdir(bin_dir)
    else:
        shutil.rmtree(bin_dir)
        os.mkdir(bin_dir)

    if not os.path.exists(build_dir):
        os.mkdir(build_dir)
    else:
        shutil.rmtree(build_dir)
        os.mkdir(build_dir)
        
    if is_windows:
        os.system("cd ..\\build && cmake -G \"MinGW Makefiles\" .. && make") 
    else:
        os.system("cd ../build && cmake .. && make")
        
if __name__ == "__main__":
    build_compiler()