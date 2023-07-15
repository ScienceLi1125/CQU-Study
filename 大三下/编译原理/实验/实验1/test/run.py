import os, platform, subprocess, shutil, sys

def run_compiler(arg1):
    record = {}

    is_windows = platform.system() == "Windows"
    
    oftype = ""
    step = "-" + arg1
    if step == "-s0":
        oftype = "tk"
    elif step == "-s1":
        oftype = "json"
    elif step == "-s2":
        oftype = "ir"
    else:
        print("illegal input")
        exit()

    bin_dir = "../bin/"
    testcase_base = "./testcase/"
    output_base = "./output/"
    compiler_path = bin_dir + ("compiler.exe" if is_windows else "compiler")

    if not os.path.exists(compiler_path):
        exit()

    if not os.path.exists(output_base):
        os.mkdir(output_base)

    for i in ["basic", "function"]:
        testcase_dir = testcase_base + i + '/'
        output_dir = output_base + i + '/'
        if os.path.exists(output_dir):
            shutil.rmtree(output_dir)
        os.mkdir(output_dir)
        if os.path.exists(testcase_dir):
            files = os.listdir(testcase_dir)
            src_files = [f for f in files if f[-3:] == ".sy" ]
            for src in src_files:
                fname, ftype = src.split('.')
                cmd = ' '.join([compiler_path, testcase_dir + src, step, "-o", output_dir + fname + "." + oftype])
                if is_windows:
                    cmd = cmd.replace('/','\\')
                cp = subprocess.run(cmd, shell=True, stderr=subprocess.PIPE, stdout=subprocess.DEVNULL)
                if cp.returncode != 0:
                    record[src] = {"retval": cp.returncode, "err_detail": cp.stderr}
                else:
                    record[src] = {"retval": 0}
                print(src, record[src])
        else:
            print("dir", testcase_dir, "not exist")

if __name__ == "__main__":
    assert(len(sys.argv) == 2)
    run_compiler(sys.argv[1])